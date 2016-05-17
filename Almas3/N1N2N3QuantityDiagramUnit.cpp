//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "N1N2N3QuantityDiagramUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
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

	//перва€ вкладка

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
	PopularTypeSeries->Title = "ѕопул€рный тип (" + IntToStr(vecSD.m_MostPopularTypeIndex+1) + ")";

	//втора€ вкладка
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

	Show();

	N1N2N3Chart->UndoZoom();
    QuantityDeletedAtomByAtomTypeChart->UndoZoom();
}
//---------------------------------------------------------------------------

