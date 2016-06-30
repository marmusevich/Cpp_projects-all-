/***************************************************************
 * Name:      wx_testMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2016-06-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WX_TESTMAIN_H
#define WX_TESTMAIN_H

//(*Headers(wx_testFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class wx_testFrame: public wxFrame
{
    public:

        wx_testFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wx_testFrame();

    private:

        //(*Handlers(wx_testFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(wx_testFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(wx_testFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WX_TESTMAIN_H
