//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ScreenCopyUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TScreenCopyForm *ScreenCopyForm;
//---------------------------------------------------------------------------
__fastcall TScreenCopyForm::TScreenCopyForm(TComponent* Owner)
    : TForm(Owner)
{
    Semapore = false;//свободен
}
//---------------------------------------------------------------------------
void __fastcall TScreenCopyForm::OkButtonClick(TObject *Sender)
{
    try
    {
     SamHeight = HeightEdit->Text.ToInt();
     if(SamHeight < 2)
      throw Exception("Высота должна быть больше 2-х пикселей.");
     SamWidth = WidthEdit->Text.ToInt();
     if(SamWidth < 2)
      throw Exception("Ширина должна быть больше 2-х пикселей.");
     SamQuality = QualityEdit->Text.ToInt();
     if(SamQuality < 2)
      throw Exception("Количество граней атома должно быть больше трёх.");
     PrintIndex = PintIndexCheckBox->Checked;
     if(Sender == OkButton)
      ModalResult = mrOk;
    }
    catch(Exception &exception)
    {
     if(Sender == OkButton)
	  Application->ShowException(&exception);
    }
}
//---------------------------------------------------------------------------
void __fastcall TScreenCopyForm::HeightEditChange(TObject *Sender)
{
    if(RatioCheckBox->Checked == true)
    {
     if(Semapore == false)
     {
      Semapore = true;
      try
      {
       int Hg = HeightEdit->Text.ToInt();
       int Wg = Hg*OriginalWidth/OriginalHeight;
       WidthEdit->Text = IntToStr(Wg);
      }
      catch(Exception &exception)
      {
       if(Sender == OkButton)
        Application->ShowException(&exception);
      }
      Semapore = false;
     }
    }
}
//---------------------------------------------------------------------------
void __fastcall TScreenCopyForm::WidthEditChange(TObject *Sender)
{
    if(RatioCheckBox->Checked == true)
    {
     if(Semapore == false)
     {
      Semapore = true;
      try
      {
       int Wg = WidthEdit->Text.ToInt();
       int Hg = Wg*OriginalHeight/OriginalWidth;
       HeightEdit->Text = IntToStr(Hg);
      }
       catch(Exception &exception)
      {
       if(Sender == OkButton)
        Application->ShowException(&exception);
      }
      Semapore = false;
     }
    }
}
//---------------------------------------------------------------------------
void __fastcall TScreenCopyForm::FormShow(TObject *Sender)
{
    HeightEdit->Text = IntToStr(OriginalHeight);
    WidthEdit->Text = IntToStr(OriginalWidth);
}
//---------------------------------------------------------------------------
