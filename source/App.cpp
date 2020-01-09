#include "App.h"
#include "Window.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Window *Window = new Window(wxT("Settings"));
    Window->Show(true);

    return true;
}