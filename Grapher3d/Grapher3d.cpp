//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("MainUnit.cpp", MainForm);
USEFORM("ScreenCopyUnit.cpp", ScreenCopyForm);
USEFORM("MillersUnit.cpp", MillersForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TScreenCopyForm), &ScreenCopyForm);
		Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
