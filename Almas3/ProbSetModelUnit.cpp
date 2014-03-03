//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProbSetModelUnit.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TProbSetModelForm::TProbSetModelForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TProbSetModelForm::InitForm(TProbPovider &SP)
{
    EditProb = SP;
    RetProb = &SP;
}
//---------------------------------------------------------------------------
void __fastcall TProbSetModelForm::FormShow(TObject *Sender)
{
    SufModelRadioGroup->Items->Clear();
    AnsiString strProbSetId;
	int nItemIndex = -1;

	if(EditProb.GetInterface()!= NULL)
	{
	 strProbSetId = EditProb.GetInterface()->GetGlobalData().GetProbSetIdString();
	}

	for(int i=0; i < EditProb.EnumirateGetCount(); i++)
	{
		SufModelRadioGroup->Items->Add(EditProb.EnumirateGetName(i));
		if(strProbSetId == EditProb.EnumirateGetIdString(i))
		{
		 nItemIndex = i;
		}
	}
	if(nItemIndex == -1 )
	{
	 nItemIndex = EditProb.EnumirateGetCount()-1;
	}

    SufModelRadioGroup->ItemIndex = nItemIndex;
    SufModelRadioGroupClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TProbSetModelForm::SufModelRadioGroupClick(TObject *Sender)
{
    int nItemIndex = SufModelRadioGroup->ItemIndex;
    if(nItemIndex >=0 && nItemIndex < EditProb.EnumirateGetCount())
    {
     InfoLabel->Caption = EditProb.EnumirateGetDiscrption(nItemIndex);
    }
    else
    {
     InfoLabel->Caption = "";
    }
}
//---------------------------------------------------------------------------
void __fastcall TProbSetModelForm::OkButtonClick(TObject *Sender)
{
    int nItemIndex = SufModelRadioGroup->ItemIndex;
    if(nItemIndex >=0 && nItemIndex < EditProb.EnumirateGetCount())
    {
     AnsiString strProbSetId = EditProb.EnumirateGetIdString(nItemIndex);
     EditProb.ClearInterface();
     EditProb.CreateInterfaceByIdString(strProbSetId);
     *RetProb = EditProb;
     ModalResult = mrOk;
    }
    else
    {
	 Application->MessageBox(_WST("Выберите модель поверхности"), _WST("Внимание"), MB_ICONERROR);
	 ModalResult = mrNone;
    }
}
//---------------------------------------------------------------------------

