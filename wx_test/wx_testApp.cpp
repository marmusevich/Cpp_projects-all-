/***************************************************************
 * Name:      wx_testApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2016-06-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "wx_testApp.h"

//(*AppHeaders
#include "wx_testMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wx_testApp);

bool wx_testApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wx_testFrame* Frame = new wx_testFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}


