//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("ProbalityUnit.cpp", ProbalityForm);
USEFORM("PropertyUnit.cpp", PropertyForm);
USEFORM("ProbSetModelUnit.cpp", ProbSetModelForm);
USEFORM("MillersUnit.cpp", MillersForm);
USEFORM("PictUnit.cpp", PictuteForm);
USEFORM("Monitoring.cpp", MonitoringForm);
USEFORM("DefectUnit.cpp", DefectForm);
USEFORM("MaskEditUnit.cpp", MaskEditForm);
USEFORM("DefectEditUnit.cpp", DefectEditForm);
USEFORM("SurfaceUnit.cpp", SurfaceForm);
USEFORM("ScreenCopyUnit.cpp", ScreenCopyForm);
USEFORM("Main.cpp", MainForm);
USEFORM("MaskUnit.cpp", MaskForm);
USEFORM("InfoUnit.cpp", InfoForm);
USEFORM("QuantityByGroupeUnit.cpp", QuantityByGroupeForm);
USEFORM("DistributionUnit.cpp", DistributionForm);
USEFORM("ProgressUnit.cpp", ProgressForm);
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
