//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("ProgressUnit.cpp", ProgressForm);
USEFORM("DistributionUnit.cpp", DistributionForm);
USEFORM("QuantityByGroupeUnit.cpp", QuantityByGroupeForm);
USEFORM("InfoUnit.cpp", InfoForm);
USEFORM("MaskUnit.cpp", MaskForm);
USEFORM("PictUnit.cpp", PictuteForm);
USEFORM("MillersUnit.cpp", MillersForm);
USEFORM("Monitoring.cpp", MonitoringForm);
USEFORM("ProbalityUnit.cpp", ProbalityForm);
USEFORM("ProbSetModelUnit.cpp", ProbSetModelForm);
USEFORM("PropertyUnit.cpp", PropertyForm);
USEFORM("ScreenCopyUnit.cpp", ScreenCopyForm);
USEFORM("SurfaceUnit.cpp", SurfaceForm);
USEFORM("DefectUnit.cpp", DefectForm);
USEFORM("DefectEditUnit.cpp", DefectEditForm);
USEFORM("MaskEditUnit.cpp", MaskEditForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "Растворение";
         Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TMonitoringForm), &MonitoringForm);
		Application->CreateForm(__classid(TInfoForm), &InfoForm);
		Application->CreateForm(__classid(TSurfaceForm), &SurfaceForm);
		Application->CreateForm(__classid(TProbalityForm), &ProbalityForm);
		Application->CreateForm(__classid(TDistributionForm), &DistributionForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
