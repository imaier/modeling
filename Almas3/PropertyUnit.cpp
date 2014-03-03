//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "PropertyUnit.h"
#include "PictUnit.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TPropertyForm *PropertyForm;
//---------------------------------------------------------------------------
TExperimentProperty::TExperimentProperty()
{
    W =H = 0;

    m_vMask.clear();

    DelAtoms = 0;
    DeletedLayers = 0;
    DeletingLayers = 0;
    N1 = N2 = N3 = 0;
    Layers = 0;
    AverageSpeed = 0;
    EndTime = BeginTime = DissolutionTime = DissolutionTime.CurrentDateTime();

	Description = "";
}
//---------------------------------------------------------------------------
__fastcall TPropertyForm::TPropertyForm(TComponent* Owner)
	: TForm(Owner)
{
	ExpProperty = NULL;
    MaskPaintBox->Canvas->Pen->Color = clBlue ;
    MaskPaintBox->Canvas->Pen->Mode = pmCopy ;
    MaskPaintBox->Canvas->Pen->Style = psInsideFrame ;
    MaskPaintBox->Canvas->Pen->Width = 1 ;
    MaskPaintBox->Canvas->Brush->Color = clWhite ;
    MaskPaintBox->Canvas->Brush->Style = bsSolid ;
    MaskPaintBox->Canvas->CopyMode = cmSrcCopy;
}
//---------------------------------------------------------------------------
void TPropertyForm::InitPropertyForm(TExperimentProperty *ExpProp)
{
    UINT i;
    AnsiString Str;
	ExpProperty = ExpProp;
    XNumLabel->Caption = IntToStr(ExpProperty->W);
    YNumLabel->Caption = IntToStr(ExpProperty->H);
    //N1ProbabilityNumLabel->Caption = AnsiString(ExpProperty->N1Probability);
    //N2ProbabilityNumLabel->Caption = AnsiString(ExpProperty->N2Probability);
    //N3ProbabilityNumLabel->Caption = AnsiString(ExpProperty->N3Probability);
    N1ProbabilityNumLabel->Caption = "Не задано";
    N2ProbabilityNumLabel->Caption = "Не задано";
    N3ProbabilityNumLabel->Caption = "Не задано";
	MaskListBox->Items->Clear();
    if(ExpProperty->m_vMask.size() != 0)
    {
	 for(i = 0; i < ExpProperty->m_vMask.size(); i++)
     {
      MaskListBox->Items->Add(ExpProperty->m_vMask[i].TMaskToString());
     }
    }
    else
    {
     MaskListBox->Items->Add("Масок нет.");
    }
    DelAtomsNumLabel->Caption = IntToStr(ExpProperty->DelAtoms);
    DeletedLayersNumLabel->Caption = IntToStr(ExpProperty->DeletedLayers);
    DeletingLayersNumLabel->Caption = IntToStr(ExpProperty->DeletingLayers);
    N1NumLabel->Caption = IntToStr(ExpProperty->N1);
    N2NumLabel->Caption = IntToStr(ExpProperty->N2);
    N3NumLabel->Caption = IntToStr(ExpProperty->N3);
    NumOfAtomsInLayerListBox->Items->Clear();
    if(ExpProperty->DeletingLayers != 0)
	{
	 for(i = 0; i < (UINT)ExpProperty->DeletingLayers; i++)
     {
	  Str = "Слой #" + IntToStr((int)(i+ExpProperty->DeletedLayers+1))
       + " содержит " + IntToStr(ExpProperty->Layers[i]) + " атомов.";
      NumOfAtomsInLayerListBox->Items->Add(Str);
     }
    }
    else
    {
     NumOfAtomsInLayerListBox->Items->Add("Информация отсутствует.");
    }
    StartTimeNumLabel->Caption = ExpProperty->BeginTime.FormatString("yy.mm.dd")//DateString()
    				 + " "
    				 + ExpProperty->BeginTime.TimeString();
    DissolutionTimeNumLabel->Caption = ExpProperty->DissolutionTime.TimeString();
    if(floor((double)(ExpProperty->DissolutionTime)+0.5) > 0)
    {
     DissolutionTimeNumLabel->Caption =
      AnsiString(floor((double)(ExpProperty->DissolutionTime)+0.5))+
       " дней, " + DissolutionTimeNumLabel->Caption;
    }
    AverageSpeedNumLabel->Caption = AnsiString(ExpProperty->AverageSpeed);
    DescriptionMemo->Lines->Text = ExpProperty->Description;
	//Caption = "Свойства " + ExpProperty->EndTime.FormatString("yymmddhhnnss");//ddmmyyhhnnss
    Caption = "Свойства " + ExpProperty->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyForm::MaskPaintBoxPaint(TObject *Sender)
{
    int MinSize;
    MinSize = min(PaintPanel->ClientHeight,PaintPanel->ClientWidth);
    MinSize -= 2 * (PaintPanel->BorderWidth + PaintPanel->BevelWidth);
    MaskPaintBox->Top = (PaintPanel->ClientHeight - MinSize)/2;
    MaskPaintBox->Height = MinSize;
    MaskPaintBox->Left = (PaintPanel->ClientWidth - MinSize)/2;
    MaskPaintBox->Width = MinSize;
	MaskPaintBox->Canvas->Brush->Color = clBlack;
    MaskPaintBox->Canvas->Rectangle(0, 0, MaskPaintBox->ClientWidth, MaskPaintBox->ClientHeight);
}
//---------------------------------------------------------------------------
void __fastcall TPropertyForm::MaskPanelClick(TObject *Sender)
{
    MaskPanel->BevelOuter = bvLowered;
    MaskPanel->Repaint();
    AnsiString Cpt;
    Cpt = MaskPanel->Caption;
    if(ExpProperty->m_vMask.size() != 0)
    {
     PaintPicture(MaskPaintBox,ExpProperty->m_vMask, ExpProperty->W, ExpProperty->H);
     MaskPanel->Caption = Cpt;
    }
    else
    {
	 MaskPaintBox->Canvas->Brush->Color = clWhite;
     MaskPaintBox->Canvas->Rectangle(0, 0, MaskPaintBox->ClientWidth, MaskPaintBox->ClientHeight);
    }
    MaskPanel->BevelOuter = bvRaised;
    //MaskPanel->Repaint();

}
//---------------------------------------------------------------------------
void __fastcall TPropertyForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     //delete Bmp;
     Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TPropertyForm::SaveButtonClick(TObject *Sender)
{
    ExpProperty->Description = DescriptionMemo->Lines->Text;
}
//---------------------------------------------------------------------------
