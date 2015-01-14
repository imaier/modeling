//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RNGsProbabilityDistributionUnit.h"
#include "QuantityByGroupeUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "TeeFunci"
#pragma resource "*.dfm"

TRNGsProbabilityDistributionForm *RNGsProbabilityDistributionForm;

void UpdateCallback(TForm *owner, ProbabilityDistributionData &data);

//---------------------------------------------------------------------------
__fastcall TRNGsProbabilityDistributionForm::TRNGsProbabilityDistributionForm(TComponent* Owner)
	: TForm(Owner)
{
	pdThread = NULL;

}
//---------------------------------------------------------------------------
void __fastcall TRNGsProbabilityDistributionForm::StartSpeedButtonClick(TObject *Sender)

{
	if (pdThread == NULL)
	{
		ProbabilityDistributionInputData input;
		input.Module = StrToInt(ModEdit->Text);
		input.InitRng = InitRNGCheckBox->Checked;
		input.UpdatePeriod = max(5000, input.Module*10);
		input.owner = this;
		input.CallbackFunc = &UpdateCallback;

		InitSeries(input.Module);

		pdThread = new ProbabilityDistributionThread(false,input);


	}
	else
	{
		if (pdThread->Suspended) {
		   pdThread->Suspended = false;
		}  else {
		   pdThread->Suspended = true;
		   pdThread->PerformCallback();
		}
	}
	UpdateControls();

}
//---------------------------------------------------------------------------
void  __fastcall TRNGsProbabilityDistributionForm::InitSeries(int Module)
{
	DistributionSeries->BeginUpdate();
	DistributionSeries->Clear();
	AnsiString strName;
	for(int i=0; i < Module; i++)
	{
	 DistributionSeries->AddXY(i+1, 0, strName, clTeeColor);
	}
	DistributionSeries->EndUpdate();
}
//---------------------------------------------------------------------------
void UpdateCallback(TForm *owner, ProbabilityDistributionData &data)
{
	TRNGsProbabilityDistributionForm *frm = (TRNGsProbabilityDistributionForm*)owner;
	float Total = data.RndCnt;
	frm->GenCntLabel->Caption = FormatFloat("### ### ### ##0", Total);

	bool Relative = frm->RelativeScaleCheckBox->Checked;

	frm->DistributionSeries->BeginUpdate();
	frm->DistributionSeries->Clear();

	int nCnt = data.DistributionVec.size();
	int Number;
	double val=0;
	double average = (double)data.RndCnt / max(nCnt,1);
	AnsiString strName;
	for(int i=0; i < nCnt; i++)
	{
	 Number = data.DistributionVec[i];
	 if(!Relative) {
		 val = (double)Number  ;// / data.RndCnt;
	 } else {
		 val = (double)Number / average - 1.0;
	 }
	 frm->DistributionSeries->AddXY(i, val, strName, clTeeColor);
	}
	frm->DistributionSeries->AddXY(nCnt, val, strName, clTeeColor);

	if(!Relative) {
		frm->DistributionSeries->UseYOrigin = true;
		frm->DistributionSeries->YOrigin = 0;
	}

	frm->DistributionSeries->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TRNGsProbabilityDistributionForm::UpdateControls()
{
	bool ThreadCreated = (pdThread != NULL);

	if(!ThreadCreated)
	{
		StartSpeedButton->Caption = "Начать";
		//GenCntLabel->Caption = "-";
	}
	else
	{
		if (pdThread->Suspended) {
			StartSpeedButton->Caption = "Продолжить";
		}
		else
		{
			StartSpeedButton->Caption = "Приостановить";
		}
	}

	StopSpeedButton->Enabled = ThreadCreated;

	ModEdit->Enabled = !ThreadCreated;
	InitRNGCheckBox->Enabled = !ThreadCreated;
}
//---------------------------------------------------------------------------
void __fastcall TRNGsProbabilityDistributionForm::FormShow(TObject *Sender)
{
	UpdateControls();
}
//---------------------------------------------------------------------------

void __fastcall TRNGsProbabilityDistributionForm::StopSpeedButtonClick(TObject *Sender)
{
	if (pdThread != NULL)
	{
		//pdThread->Suspended = true;
		//pdThread->PerformCallback();
		pdThread->Terminate();
		pdThread->Suspended = false;
		delete 	pdThread;
		pdThread = NULL;
	}
	UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TRNGsProbabilityDistributionForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	StopSpeedButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TRNGsProbabilityDistributionForm::RelativeScaleCheckBoxClick(TObject *Sender)
{
	if (pdThread != NULL)
	{
		pdThread->PerformCallback();
	}
}
//---------------------------------------------------------------------------

