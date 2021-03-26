/***************************************************************
 * Name:      SevenWaysUpdaterMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    RS-Soft (siziakov@mail.ru)
 * Created:   2020-05-10
 * Copyright: RS-Soft ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include <wx/treelist.h>
#include <wx/dir.h>
#include <wx/protocol/http.h>

#include "version.h"
#include "SevenWaysUpdaterMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(SevenWaysUpdaterFrame, wxFrame)
    EVT_CLOSE(SevenWaysUpdaterFrame::OnClose)
    EVT_MENU(idMenuQuit, SevenWaysUpdaterFrame::OnQuit)
    EVT_MENU(idMenuAbout, SevenWaysUpdaterFrame::OnAbout)

    EVT_BUTTON(idButtonOpen, SevenWaysUpdaterFrame::OnOpen)
    EVT_BUTTON(idButtonFastUpdate, SevenWaysUpdaterFrame::OnFastUpdate)
    EVT_BUTTON(idButtonAllMaps, SevenWaysUpdaterFrame::OnAllMaps)
    EVT_BUTTON(idButtonUpdate, SevenWaysUpdaterFrame::OnUpdate)

    EVT_TREELIST_ITEM_CHECKED(idTreeControlMaps, SevenWaysUpdaterFrame::OnTreeControlCheckedChanged)
END_EVENT_TABLE()

SevenWaysUpdaterFrame::SevenWaysUpdaterFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    maps = new Maps();

    wxBoxSizer *sizerMain = new wxBoxSizer(wxVERTICAL);

    wxGridSizer *sizerToolbar = new wxGridSizer(4);

    buttonOpen = new wxButton(this, idButtonOpen, _("Open"));
    sizerToolbar->Add(buttonOpen, 0, wxALL | wxEXPAND, 5);

    buttonFastUpdate = new wxButton(this, idButtonFastUpdate, _("Fast update"));
    buttonFastUpdate->Enable(false);
    sizerToolbar->Add(buttonFastUpdate, 0, wxALL | wxEXPAND, 5);

    buttonCheck = new wxButton(this, idButtonAllMaps, _("All maps"));
    buttonCheck->Enable(false);
    sizerToolbar->Add(buttonCheck, 0, wxALL | wxEXPAND, 5);

    buttonUpdate = new wxButton(this, idButtonUpdate, _("Update"));
    buttonUpdate->Enable(false);
    sizerToolbar->Add(buttonUpdate, 0, wxALL | wxEXPAND, 5);

    sizerMain->Add( sizerToolbar, 0, wxALL | wxEXPAND, 2);

    treeControl = new wxTreeListCtrl(this, idTreeControlMaps, wxDefaultPosition, wxSize(800, 500), wxTL_CHECKBOX);

    sizerMain->Add(treeControl, 10, wxALL | wxEXPAND);

    progressText = new wxStaticText(this, idProgressText, _("Press Open button to select 7Ways files"));
    sizerMain->Add(progressText, 0, wxALL | wxEXPAND | wxALIGN_BOTTOM, 5);

    progress = new wxGauge(this, idProgress , 100, wxDefaultPosition, wxSize(100, 10));
    sizerMain->Add(progress, 0, wxALL | wxEXPAND);
    progress->SetValue(0);


    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(1);
    SetStatusText(_("© RS-Soft: ") + AutoVersion::FULLVERSION_STRING, 0);

    this->SetSizer(sizerMain);
    this->Layout();
    sizerMain->Fit(this);
}


SevenWaysUpdaterFrame::~SevenWaysUpdaterFrame()
{
}

void SevenWaysUpdaterFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void SevenWaysUpdaterFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void SevenWaysUpdaterFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void SevenWaysUpdaterFrame::OnOpen(wxCommandEvent& event)
{
    if (maps == NULL) return;

    wxFileDialog * openFileDialog = new wxFileDialog(this, _("Open 7 Ways executable file"), "", "", "Executable files (*.exe)|*.exe", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if (openFileDialog->ShowModal() == wxID_OK)
    {
	    mapsOnDevice.clear();
	    wxString filename = openFileDialog->GetPath();
		mapFolder = wxPathOnly(filename) + wxString(wxFILE_SEP_PATH) + wxString(wxT("maps"));
		wxDir mapDir(mapFolder);
		wxArrayString files;
		mapDir.GetAllFiles(mapFolder, &files, wxString(_("*.7w")));
		total_size = 0;
		if (files.GetCount() > 0)
        {
            for (wxString file: files)
            {
                MapDescriptor md;
                if (maps->Find(file, md))
                {
                    md.SetFileLength(GetHttpFileSize(md.GetServer(), md.GetFile()));
                    total_size += md.Length;
                    mapsOnDevice.push_back(md);
                }
            }
            if (mapsOnDevice.size() > 0)
            {
                buttonFastUpdate->Enable(true);
            }
            UpdateProgress(wxString::Format("Found %i maps", (int)mapsOnDevice.size()));
        }
        buttonCheck->Enable(true);
    }
}

void SevenWaysUpdaterFrame::OnFastUpdate(wxCommandEvent& event)
{
    DoUpdate(mapFolder, mapsOnDevice, total_size);
}

void SevenWaysUpdaterFrame::OnAllMaps(wxCommandEvent& event)
{
    treeControl->AppendColumn(_("Maps"), 710);
    //treeControl->AppendColumn(_("Date"), 200, wxALIGN_RIGHT);
    treeControl->AppendColumn(_("Size"), 60, wxALIGN_RIGHT);
    treeControl->AppendColumn(_("ID"), 0, wxALIGN_RIGHT, wxCOL_HIDDEN);
    //treeControl->SetColumnWidth(2, 2);

    wxTreeListItem root = treeControl->GetRootItem();

    if (maps == NULL) return;
    int count = maps->count();

    UpdateProgress(0);
    int current = 0;
    for (MapGroup group: maps->Groups)
    {
        size_t sizeOfGroup = 0;
        wxTreeListItem groupId = treeControl->AppendItem(root, group.Name);
        bool wasFoundMap = false;
        for (MapDescriptor map: group.MapDescriptors)
        {
            wxTreeListItem mapId = treeControl->AppendItem(groupId, map.Name);
            map.SetFileLength(GetHttpFileSize(map.GetServer(), map.GetFile()));
            sizeOfGroup += map.Length;
            treeControl->SetItemText(mapId, 1, GetFileLength(map.Length));
            bool mapFounded = maps->Find(map.GetFile(), mapsOnDevice);
            treeControl->SetItemText(mapId, 2, wxString::Format("%i", map.GetID()));
            if (mapFounded) wasFoundMap = true;
            treeControl->CheckItem(mapId, mapFounded ? wxCHK_CHECKED : wxCHK_UNCHECKED);
            int percent = (int)(++current / (float)count * 100 + 0.5);
            UpdateProgress(percent, wxString::Format(_("Checking map: %s"), map.Name));
        }
        treeControl->SetItemText(groupId, 1, GetFileLength(sizeOfGroup));
        if (wasFoundMap) treeControl->Expand(groupId);
    }
    UpdateProgress(100, _("Updated information on available maps completed!"));
    buttonUpdate->Enable(true);
}

void SevenWaysUpdaterFrame::OnTreeControlCheckedChanged(wxTreeListEvent& event)
{
    wxTreeListItem item = event.GetItem();
    if (item != NULL)
    {
        wxCheckBoxState state = treeControl->GetCheckedState(item);
        // Если щелкнули по группе, то обрабатываем все внутри группы
        treeControl->CheckItemRecursively(item, state);
        wxTreeListItem parent = treeControl->GetItemParent(item);
        if (parent.IsOk())
        {
            bool isAllChecked = treeControl->AreAllChildrenInState(parent, wxCHK_CHECKED);
            treeControl->CheckItem(parent, isAllChecked ? wxCHK_CHECKED : wxCHK_UNCHECKED);
        }

        //wxTreeListItem nextItem = treeControl->GetNextItem(item);
        //while (nextItem.IsOk())
        //{
        //    wxTreeListItem parent = treeControl->GetItemParent(nextItem);
        //    if (parent != item) break;
        //    treeControl->CheckItem(nextItem, state);
        //    nextItem = treeControl->GetNextItem(nextItem);
        //}
        // Если щелкнули по элементу, то надо обновить состояние у группы
    }
}

void SevenWaysUpdaterFrame::OnUpdate(wxCommandEvent& event)
{
    mapsToUpdate.clear();
    total_size = 0;
    UpdateProgress(0);
    wxTreeListItem item = treeControl->GetFirstItem();
    while (item.IsOk())
    {
        if (treeControl->GetCheckedState(item) == wxCHK_CHECKED)
        {
            wxString idText = treeControl->GetItemText(item, 2);
            int id = wxAtoi(idText);
            MapDescriptor md;
            if (maps->Find(id, md))
            {
                md.SetFileLength(GetHttpFileSize(md.GetServer(), md.GetFile()));
                total_size += md.Length;
                mapsToUpdate.push_back(md);
            }
        }
        item = treeControl->GetNextItem(item);
    }
    UpdateProgress(100, _("Update is completed!"));
    if (mapsOnDevice.size() > 0)
    {
        mapsToDelete.clear();
        for (MapDescriptor deviceMap: mapsOnDevice)
        {
            if (!MapDescriptor::Contain(deviceMap.GetID(), mapsToUpdate)) mapsToDelete.push_back(deviceMap);
        }
        DoUpdate(mapFolder, mapsToUpdate, total_size);
        if (mapsToDelete.size() > 0)
        {
            // TODO: удалить ненужные карты
        }
    }
}

void SevenWaysUpdaterFrame::UpdateProgress(int percent)
{
    if (progress != NULL && percent >= 0 && percent <= 100) progress->SetValue(percent);
}

void SevenWaysUpdaterFrame::UpdateProgress(wxString text)
{
    if (progressText != NULL) progressText->SetLabel(text);
}

void SevenWaysUpdaterFrame::UpdateProgress(int percent, wxString text)
{
    UpdateProgress(percent);
    UpdateProgress(text);
}

size_t SevenWaysUpdaterFrame::GetHttpFileSize(wxString server, wxString path)
{
    size_t length = 0;
    wxHTTP http;
    http.SetHeader(_T("Content-Type"), _T("text/html; charset=utf-8"));
    http.SetTimeout(10);

    if (http.Connect(server, 80))
    {
        wxApp::IsMainLoopRunning();
        wxInputStream *stream = http.GetInputStream(path);
        if (stream != NULL)
        {
            length = stream->GetSize();
            wxDELETE(stream);
        }
    }
    http.Close();
    return length;
}

void SevenWaysUpdaterFrame::DoUpdate(wxString mapsFolder, std::list<MapDescriptor> mapsToUpdate, size_t total_size)
{
    UpdateProgress(0);
    downloaded = 0;
    for (MapDescriptor map: mapsToUpdate)
    {
        wxMemoryOutputStream memStream;
        if (GetHttpZipFile(map.GetServer(), map.GetFile(), memStream, total_size))
        {
            wxMemoryInputStream zipMemStream(memStream);
            wxZipInputStream zipStream(zipMemStream);
            wxZipEntry *entry = NULL;
            while (entry = zipStream.GetNextEntry())
            {
                zipStream.OpenEntry(*entry);
                wxString name = entry->GetInternalName();
                if (name.Contains(wxString(".7w")))
                {
                    wxString fileName = mapsFolder + wxString(wxFILE_SEP_PATH) + name;
                    wxFileOutputStream outFile(fileName);
                    zipStream.Read(outFile);
                }
            }
        }
    }
    UpdateProgress(100, _("Update completed!"));
}

bool SevenWaysUpdaterFrame::GetHttpZipFile(wxString server, wxString file, wxMemoryOutputStream &output, size_t total_size)
{
    bool result = false;
    wxHTTP http;
    http.SetHeader(_T("Content-Type"), _T("text/html; charset=utf-8"));
    http.SetTimeout(10);

    wxString filename = wxFileNameFromPath(file);
    if (http.Connect(server, 80))
    {
        wxApp::IsMainLoopRunning();
        wxInputStream *stream = http.GetInputStream(file);
        if (stream != NULL)
        {
            //size_t length = stream->GetSize();
            unsigned char buffer[204800];
            int bytesRead;
            while(!stream->Eof())
            {
                stream->Read(buffer, sizeof(buffer));
                bytesRead = stream->LastRead();
                output.Write(buffer, bytesRead);

                downloaded += bytesRead;
                int percent = (int)(downloaded / (float)total_size * 100.0 + 0.5);
                UpdateProgress(percent, wxString::Format(_("Downloaded: %s (%s), %s"), GetFileLength(downloaded), GetFileLength(total_size), filename));
                if (bytesRead <= 0)
                    break;
            }
            result = true;
            wxDELETE(stream);
        }
    }
    http.Close();
    return result;
}

wxString SevenWaysUpdaterFrame::GetFileLength(size_t size)
{
    if (size <= 0) return "";
    if (size < 24576L) return wxString::Format(wxT("%i B"), (int)(size / (float)1024));
    if (size < 1048576L) return wxString::Format(wxT("%i KB"), (int)(size / (float)24576));
    return size < 1073741824L ? wxString::Format(wxT("%i MB"), (int)(size / (float)1048576)): wxString::Format(wxT("%i GB"), (int)(size / (float)1073741824));
}
