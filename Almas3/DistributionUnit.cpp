//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DistributionUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma resource "*.dfm"
TDistributionForm *DistributionForm;


//---------------------------------------------------------------------------
__fastcall TDistributionForm::TDistributionForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TDistributionForm::SetDataAndShow(TAtomCntBase &Layer, AnsiString strName)
{
	TAutoLock lock(m_cs);

	TWaitCursor wc;

	Hide();

	DistributionSeries->Clear();

	if(DistributionChart->Title->Text->Count > 1)
	{
		//DistributionChart->Title->Text->operator [](1) = strName;
		DistributionChart->Title->Text->Delete(1);
	}
	{
		DistributionChart->Title->Text->Add(strName);
	}

	IBaseProbSet *pPS = Layer.m_vnSortAttom.GetInterface();
	if(pPS != NULL)
	{
	 int nCnt = pPS->GetGlobalData().GetAllNumProbality();
	 int i, nVal;
	 AnsiString strName;
	 for(i=0; i < nCnt; i++)
	 {
		//pItem = pItems->Add();
		//pItem->Caption = pPS->GetGlobalData().GetProbName(i);
		nVal = (int)pPS->GetProbValue(i);
		//pItem->SubItems->Add(IntToStr(nVal));

		//DistributionSeries->Add(nVal, pPS->GetGlobalData().GetProbName(i), clTeeColor);

		strName = pPS->GetGlobalData().GetProbName(i);
		//strName = IntToStr(i+1);

		//DistributionSeries->Add(nVal, strName, clTeeColor);
		DistributionSeries->AddXY(i+1, nVal, strName, clTeeColor);
	 }
	}

	//pItem = pItems->Add();
	//pItem->Caption = "Четырёхсвязные атомы";
	//pItem->SubItems->Add(IntToStr(Layer.m_nFourLinkAtom));

	//DistributionSeries->Add(Layer.m_nFourLinkAtom, "Четырёхсвязные атомы", clTeeColor);

	//pItem = pItems->Add();
	//pItem->Caption = "Не удаляемые атомы";
	//pItem->SubItems->Add(IntToStr(Layer.m_nNoDelAtom));

	//DistributionSeries->Add(Layer.m_nNoDelAtom, "Не удаляемые атомы", clTeeColor);

	//pItem = pItems->Add();
	//pItem->Caption = "Удалённые атомы";
	//pItem->SubItems->Add(IntToStr(Layer.m_nDelAtom));

	//DistributionSeries->Add(Layer.m_nDelAtom, "Удалённые атомы", clTeeColor);

	Show();
}
//---------------------------------------------------------------------------
void __fastcall TDistributionForm::AutoScaleSpeedButtonClick(TObject *Sender)
{
	DistributionChart->UndoZoom();
}
//---------------------------------------------------------------------------
void __fastcall TDistributionForm::PrecentCheckBoxClick(TObject *Sender)
{
	DistributionSeries->Marks->Visible = PrecentCheckBox->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TDistributionForm::LegendCheckBoxClick(TObject *Sender)
{
	DistributionSeries->ShowInLegend = LegendCheckBox->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TDistributionForm::FormShow(TObject *Sender)
{
//	PrecentCheckBox->Checked = DistributionSeries->Marks->Visible;
//	LegendCheckBox->Checked = DistributionSeries->ShowInLegend;
//	ProbNameCheckBox->Checked = DistributionChart->TopAxis->Visible;

	PrecentCheckBoxClick(Sender);
	LegendCheckBoxClick(Sender);
	ProbNameCheckBoxClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TDistributionForm::ProbNameCheckBoxClick(TObject *Sender)
{
	DistributionChart->TopAxis->Visible = ProbNameCheckBox->Checked;
}
//---------------------------------------------------------------------------

