/***************************************************************
 * Name:      SevenWaysUpdaterApp.h
 * Purpose:   Defines Application Class
 * Author:    RS-Soft (siziakov@mail.ru)
 * Created:   2020-05-10
 * Copyright: RS-Soft ()
 * License:
 **************************************************************/

#ifndef SEVENWAYSUPDATERAPP_H
#define SEVENWAYSUPDATERAPP_H

#include <wx/intl.h>
#include <wx/app.h>

class SevenWaysUpdaterApp : public wxApp
{
    public:
        virtual bool OnInit();
        SevenWaysUpdaterApp() { m_lang = wxLANGUAGE_UNKNOWN; }
protected:
    wxLanguage m_lang;  // language specified by user
    wxLocale m_locale;  // locale we'll be using
};

#endif // SEVENWAYSUPDATERAPP_H
