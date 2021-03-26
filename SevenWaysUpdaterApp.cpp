/***************************************************************
 * Name:      SevenWaysUpdaterApp.cpp
 * Purpose:   Code for Application Class
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

#include <wx/intl.h>
#include <wx/stdpaths.h>

#include "SevenWaysUpdaterApp.h"
#include "SevenWaysUpdaterMain.h"

wxLocale* locale;
long language;

void initLanguageSupport()
{
    language =  wxLANGUAGE_DEFAULT;

    // fake functions, use proper implementation
//    if( userWantsAnotherLanguageThanDefault() )
        //language = getUsersFavoriteLanguage();

    // load language if possible, fall back to english otherwise
    if(wxLocale::IsAvailable(language))
    {
        locale = new wxLocale( language);

        locale->AddCatalogLookupPathPrefix(wxT("."));

        #ifdef __WXGTK__
        // add locale search paths
        locale->AddCatalogLookupPathPrefix(wxT("/usr"));
        locale->AddCatalogLookupPathPrefix(wxT("/usr/local"));
        wxStandardPaths* paths = (wxStandardPaths*) &wxStandardPaths::Get();
        wxString prefix = paths->GetInstallPrefix();
        locale->AddCatalogLookupPathPrefix( prefix );
        #else
        #endif

        if (!locale->AddCatalog(wxT("SevenWaysUpdater")))
        {
            wxLogWarning(wxT("Translation is missing!"));
        }

        if(! locale->IsOk() )
        {
            wxLogWarning(wxT("selected language is wrong"));
            delete locale;
            locale = new wxLocale( wxLANGUAGE_ENGLISH );
            language = wxLANGUAGE_ENGLISH;
        }
    }
    else
    {
        wxLogWarning(wxT("The selected language is not supported by your system. Try installing support for this language." ));
        locale = new wxLocale( wxLANGUAGE_ENGLISH );
        language = wxLANGUAGE_ENGLISH;
    }

}

bool SevenWaysUpdaterApp::OnInit()
{
    initLanguageSupport();

    SevenWaysUpdaterFrame* frame = new SevenWaysUpdaterFrame(0L, _("7Ways maps updater"));
    frame->SetMinSize(wxSize(480, 320));
    #ifdef __WXGTK__
    #else
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    #endif // __WXGTK__
    frame->Show(true);

    return true;
}

IMPLEMENT_APP(SevenWaysUpdaterApp);
