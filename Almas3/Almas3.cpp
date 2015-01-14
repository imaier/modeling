//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("ProbSetModelUnit.cpp", ProbSetModelForm);
USEFORM("PropertyUnit.cpp", PropertyForm);
USEFORM("ProbalityUnit.cpp", ProbalityForm);
USEFORM("MillersUnit.cpp", MillersForm);
USEFORM("Monitoring.cpp", MonitoringForm);
USEFORM("ScreenCopyUnit.cpp", ScreenCopyForm);
USEFORM("MaskEditUnit.cpp", MaskEditForm);
USEFORM("DefectEditUnit.cpp", DefectEditForm);
USEFORM("N1N2N3QuantityDiagramUnit.cpp", N1N2N3QuantityDiagramForm);
USEFORM("DefectUnit.cpp", DefectForm);
USEFORM("SurfaceUnit.cpp", SurfaceForm);
USEFORM("Main.cpp", MainForm);
USEFORM("InfoUnit.cpp", InfoForm);
USEFORM("PictUnit.cpp", PictuteForm);
USEFORM("MaskUnit.cpp", MaskForm);
USEFORM("ProgressUnit.cpp", ProgressForm);
USEFORM("QuantityByGroupeUnit.cpp", QuantityByGroupeForm);
USEFORM("DistributionUnit.cpp", DistributionForm);
USEFORM("RNGsProbabilityDistributionUnit.cpp", RNGsProbabilityDistributionForm);
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
		Application->CreateForm(__classid(TN1N2N3QuantityDiagramForm), &N1N2N3QuantityDiagramForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
