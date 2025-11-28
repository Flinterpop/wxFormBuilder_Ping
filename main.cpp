#include <wx/wx.h>


#include "MainDialog.h"


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

/*
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};
*/

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    // Create an instance of the custom dialog on the stack
    MainDialog dialog(nullptr); //_T("My Dialog Application"));



    // Show the dialog modally. The program flow pauses here until the dialog is closed.
    if (dialog.ShowModal() == wxID_OK)
    {
        // Code here executes after the dialog is dismissed with OK
        //wxMessageBox(_T("Dialog closed with OK!"), _T("Info"));
    }
    else
    {
        // Code here executes if the user cancels or closes the dialog in another way
        //wxMessageBox(_T("Dialog cancelled."), _T("Info"));
    }

    // The application exits when OnInit returns false or all top-level windows are closed.
    // In a dialog-only app, you usually just return false after the dialog returns.

    return false;
}

