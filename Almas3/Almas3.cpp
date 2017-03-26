//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("ProbSetModelUnit.cpp", ProbSetModelForm);
USEFORM("ProbalityUnit.cpp", ProbalityForm);
USEFORM("PropertyUnit.cpp", PropertyForm);
USEFORM("ScreenCopyUnit.cpp", ScreenCopyForm);
USEFORM("Monitoring.cpp", MonitoringForm);
USEFORM("DefectUnit.cpp", DefectForm);
USEFORM("N1N2N3QuantityDiagramUnit.cpp", N1N2N3QuantityDiagramForm);
USEFORM("SaveChartImageFormUnit.cpp", SaveChartImageForm);
USEFORM("SelectAtomKindsFormUnit.cpp", SelectAtomKindsForm);
USEFORM("SurfaceUnit.cpp", SurfaceForm);
USEFORM("MaskEditUnit.cpp", MaskEditForm);
USEFORM("DefectEditUnit.cpp", DefectEditForm);
USEFORM("Main.cpp", MainForm);
USEFORM("InfoUnit.cpp", InfoForm);
USEFORM("QuantityByGroupeUnit.cpp", QuantityByGroupeForm);
USEFORM("MaskUnit.cpp", MaskForm);
USEFORM("ProgressUnit.cpp", ProgressForm);
USEFORM("MillersUnit.cpp", MillersForm);
USEFORM("DistributionUnit.cpp", DistributionForm);
USEFORM("PictUnit.cpp", PictuteForm);
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
