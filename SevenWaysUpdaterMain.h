/***************************************************************
 * Name:      SevenWaysUpdaterMain.h
 * Purpose:   Defines Application Frame
 * Author:    RS-Soft (siziakov@mail.ru)
 * Created:   2020-05-10
 * Copyright: RS-Soft ()
 * License:
 **************************************************************/

#ifndef SEVENWAYSUPDATERMAIN_H
#define SEVENWAYSUPDATERMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/treelist.h>
#include "wx/treectrl.h"
#include "wx/zipstrm.h"
#include <wx/mstream.h>
#include <wx/wfstream.h>

#include "SevenWaysUpdaterApp.h"
#include "Maps.h"

class SevenWaysUpdaterFrame: public wxFrame
{
    DECLARE_EVENT_TABLE()

    public:
        SevenWaysUpdaterFrame(wxFrame *frame, const wxString& title);
        ~SevenWaysUpdaterFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idButtonOpen,
            idButtonFastUpdate,
            idButtonAllMaps,
            idButtonUpdate,
            idTreeControlMaps,
            idProgress,
            idProgressText,
            idMenuAbout
        };

        wxGauge *progress = NULL;
        wxStaticText *progressText = NULL;
        wxButton *buttonOpen = NULL;
        wxButton *buttonFastUpdate = NULL;
        wxButton *buttonCheck = NULL;
        wxButton *buttonUpdate = NULL;
        wxTreeListCtrl *treeControl = NULL;

        Maps *maps = NULL;

        wxString mapFolder;
        std::list<MapDescriptor> mapsOnDevice;
        std::list<MapDescriptor> mapsToUpdate;
        std::list<MapDescriptor> mapsToDelete;
        size_t total_size;
        size_t downloaded;

        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        void OnOpen(wxCommandEvent& event);
        void OnFastUpdate(wxCommandEvent& event);
        void OnAllMaps(wxCommandEvent& event);
        void OnUpdate(wxCommandEvent& event);

        void UpdateProgress(int percent);
        void UpdateProgress(wxString text);
        void UpdateProgress(int percent, wxString text);
        size_t GetHttpFileSize(wxString server, wxString path);
        void DoUpdate(wxString mapsFolder, std::list<MapDescriptor> mapsToUpdate, size_t total_size);
        bool GetHttpZipFile(wxString server, wxString file, wxMemoryOutputStream &output, size_t total_size);
        wxString GetFileLength(size_t size);

        void OnTreeControlCheckedChanged(wxTreeListEvent& event);

};


#endif // SEVENWAYSUPDATERMAIN_H
