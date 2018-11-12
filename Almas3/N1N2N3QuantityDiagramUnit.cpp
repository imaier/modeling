
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "N1N2N3QuantityDiagramUnit.h"
#include "SaveChartImageFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "TeeFunci"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TN1N2N3QuantityDiagramForm *N1N2N3QuantityDiagramForm;
//---------------------------------------------------------------------------
__fastcall TN1N2N3QuantityDiagramForm::TN1N2N3QuantityDiagramForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TN1N2N3QuantityDiagramForm::SetDataAndShow(const TStatisticsDataVec& vecSD)
{
	TAutoLock lock(m_cs);
	TWaitCursor wc;

	Hide();
	m_vecSD = vecSD;

	//������ �������

	OneLinkSeries->Clear();
	TwoLinkSeries->Clear();
	ThreeLinkSeries->Clear();
	PopularTypeSeries->Clear();
	nS_Series->Clear();


	int nCnt = vecSD.size();
	AnsiString strName;
	for(int i=0; i < nCnt; i++)
	{
	 const TStatisticsData &sd = vecSD[i];
	 OneLinkSeries->AddXY(sd.Deleted, sd.N1, strName, clTeeColor);
	 TwoLinkSeries->AddXY(sd.Deleted, sd.N2, strName, clTeeColor);
	 ThreeLinkSeries->AddXY(sd.Deleted, sd.N3, strName, clTeeColor);
	 PopularTypeSeries->AddXY(sd.Deleted, sd.MostPopularTypeCount, strName, clTeeColor);
	 if(sd.nS_Count < 0 && i == 0)
	 {
		nS_Series->Visible = false;
	 }
	 nS_Series->AddXY(sd.Deleted, sd.nS_Count, strName, clTeeColor);
	}
	PopularTypeSeries->Title = "���������� ��� (" + IntToStr(vecSD.m_MostPopularTypeIndex+1) + ")";

	//������ �������
	QuantityDeletedAtomByAtomTypeSeries->Clear();

	IBaseProbSet *pPS = vecSD.m_DeletedAtomKindsStatistics.GetInterface();
	if(pPS != NULL)
	{
	 int nProbCnt = pPS->GetGlobalData().GetAllNumProbality();
	 for(int i = 0; i < nProbCnt; i++)
	 {
	  double Value = pPS->GetProbValue(i);

	  int Index = QuantityDeletedAtomByAtomTypeSeries->AddXY(i+1, Value, pPS->GetGlobalData().GetProbName(i), clTeeColor);
	  /*
	  if(Value > 0)
	  {
	   QuantityDeletedAtomByAtomTypeSeries->Marks->Item[Index]->Text->Add(pPS->GetGlobalData().GetProbName(i));
	  }
	  else
	  {
	   QuantityDeletedAtomByAtomTypeSeries->Marks->Item[Index]->Text->Clear();
	  }
	  */
	 }
	}

	//������ �������

	UpdateParametri�Series();

	//��������� ������� - ������������� � �������
	RoughnessSeries->Clear();
	ThicknessSeries->Clear();
	// ����� ������� - ������� �������
	AverageLevelSeries->Clear();

	for(int i=0; i < nCnt; i++)
	{
	 const TStatisticsData &sd = vecSD[i];
	 RoughnessSeries->AddXY(sd.Deleted, sd.Roughness, strName, clTeeColor);
	 ThicknessSeries->AddXY(sd.Deleted, sd.Thickness, strName, clTeeColor);
	 AverageLevelSeries->AddXY(sd.Deleted, sd.AverageLevel, strName, clTeeColor);
	}



	Show();

	N1N2N3Chart->UndoZoom();
	QuantityDeletedAtomByAtomTypeChart->UndoZoom();
	Parametri�Chart->UndoZoom();
}
//---------------------------------------------------------------------------
void __fastcall TN1N2N3QuantityDiagramForm::SelectAtomKindsSpeedButtonClick(TObject *Sender)
{
	TSelectAtomKindsForm *Form = new TSelectAtomKindsForm(this);
	Form->EditData = SelectedAxes;
	if (Form->ShowModal() == mrOk)
	{
		SelectedAxes = Form->EditData;
		UpdateParametri�Series();
	}

	delete Form;
}
//---------------------------------------------------------------------------
void __fastcall TN1N2N3QuantityDiagramForm::UpdateParametri�Series(void)
{

	int nCnt = m_vecSD.size();
	Parametri�Series->Clear();
	for(int i=0; i < nCnt; i++)
	{
	 const TStatisticsData &sd = m_vecSD[i];
	 Parametri�Series->AddXY(SelectedAxes.GetXAxisCount(sd) , SelectedAxes.GetYAxisCount(sd), IntToStr(sd.Deleted) /*strName*/, clTeeColor);
	}

	Parametri�Chart->LeftAxis->Title->Caption = SelectedAxes.GetYAxisDiscription();
	Parametri�Chart->BottomAxis->Title->Caption = SelectedAxes.GetXAxisDiscription();

	//Parametri�Chart->UndoZoom();

}
//---------------------------------------------------------------------------
void __fastcall TN1N2N3QuantityDiagramForm::RemovMarksCheckBoxClick(TObject *Sender)
{
	Parametri�Series->Marks->Visible = !RemovMarksCheckBox->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TN1N2N3QuantityDiagramForm::SaveImageSpeedButtonClick(TObject *Sender)
{
	//StatisticPageControl;;;
	TStringList *ChartList = new TStringList();
	ChartList->AddObject(AtomQuantityByDeleteAtomQuantityTabSheet->Caption, N1N2N3Chart);
	ChartList->AddObject(QuantityDeletedAtomByAtomTypeTabSheet->Caption, QuantityDeletedAtomByAtomTypeChart);
	ChartList->AddObject(ParametricGraphTabSheet->Caption, Parametri�Chart);
	ChartList->AddObject(RoughnessTabSheet->Caption, RoughnessChart);
	ChartList->AddObject(AverageLevelTabSheet->Caption, AverageLevelChart);

	TSaveChartImageForm *SaveForm = new TSaveChartImageForm(this);
	SaveForm->InitAndShowDialog(ChartList);
    delete SaveForm;
	delete ChartList;
}
//---------------------------------------------------------------------------

