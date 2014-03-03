//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ScreenCopyUnit.h"
//#include <FileCtrl.hpp>
#include "FileCtrl.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TScreenCopyForm *ScreenCopyForm;
//---------------------------------------------------------------------------
__fastcall TScreenCopyForm::TScreenCopyForm(TComponent* Owner)
    : TForm(Owner)
{
    Semapore = false;//��������
}
//---------------------------------------------------------------------------
void __fastcall TScreenCopyForm::OkButtonClick(TObject *Sender)
{
    try
    {
     SamHeight = HeightEdit->Text.ToInt();
     if(SamHeight < 2)
      throw Exception("������ ������ ���� ������ 2-� ��������.");
     SamWidth = WidthEdit->Text.ToInt();
     if(SamWidth < 2)
      throw Exception("������ ������ ���� ������ 2-� ��������.");
     SamQuality = QualityEdit->Text.ToInt();
     if(SamQuality < 2)
      throw Exception("���������� ������ ����� ������ ���� ������ ���.");
     PrintIndex = PintIndexCheckBox->Checked;

     m_bCapture = CaptureCheckBox->Checked;
     if(m_bCapture == true)
     {
      m_nFrom = FromEdit->Text.ToInt();
      if(m_nFrom < 0)
       throw Exception("���������� ��������� ������ ����� �������� ��������� �� ������ ���� �������������.");
      m_nStep = StepEdit->Text.ToInt();
      if(m_nStep < 1)
       throw Exception("���������� �������� ������ ����� �������� ������ ���� ������ ����.");
      m_nTo = ToEdit->Text.ToInt();
      if(m_nTo < 1)
       throw Exception("���������� �������� ������ \"��\" ����� ���� ������ \"�����\".");
      m_bSeveralOrn = SeveralOrnCheckBox->Checked;

      if(BaseNameEdit->Text.Length() == 0)
       throw Exception("������ ������� ��� �����.");
      m_strBaseName = BaseNameEdit->Text;

      if(DirEdit->Text.Length() == 0)
       throw Exception("������ ������� ����������.");
      m_strDir = DirEdit->Text;
     }
     else
     {
      m_nFrom = 0;
      m_nStep = 0;
      m_nTo= 0;
      m_bSeveralOrn = false;
      m_strBaseName= "";
      m_strDir= "";
     }

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
    if(m_bCapture == true)
    {
     CaptureCheckBox->Checked = m_bCapture;
     FromEdit->Text     = m_nFrom;
     StepEdit->Text     = m_nStep;
     ToEdit->Text       = m_nTo;
     BaseNameEdit->Text = m_strBaseName;
     DirEdit->Text      = m_strDir;
     SeveralOrnCheckBox->Checked = m_bSeveralOrn;
    }
    CaptureCheckBoxClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TScreenCopyForm::CaptureCheckBoxClick(TObject *Sender)
{
    SetEnabled(CaptureCheckBox->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TScreenCopyForm::SetEnabled(bool bEn)
{
    TColor StateColor = clWindow;
    if(bEn == false)
    {
        StateColor = clBtnFace;
    }

    CaptureGroupBox->Enabled = bEn;
    DelAtomGroupBox->Enabled = bEn;
    FromLabel->Enabled       = bEn;
    FromEdit->Enabled        = bEn;
    FromEdit->Color          = StateColor;
    StepEdit->Enabled        = bEn;
    StepEdit->Color          = StateColor;
    StepLabel->Enabled       = bEn;
    ToLabel->Enabled         = bEn;
    ToEdit->Enabled          = bEn;
    ToEdit->Color            = StateColor;
    BaseNameLabel->Enabled   = bEn;
    BaseNameEdit->Enabled    = bEn;
    BaseNameEdit->Color      = StateColor;
    DirLabel->Enabled        = bEn;
    DirButton->Enabled       = bEn;
    DirEdit->Enabled         = bEn;
    DirEdit->Color           = StateColor;
    SeveralOrnCheckBox->Enabled = bEn;
}
//---------------------------------------------------------------------------
void __fastcall TScreenCopyForm::DirButtonClick(TObject *Sender)
{
	 AnsiString strDir;
	 //
	 //bool bOk = SelectDirectory("����� �������� ���������� " , WideString(GetCurrentDir()), strDir);
	 strDir = DirEdit->Text;
	 if(strDir == "")
		 strDir = GetCurrentDir();
	 TSelectDirOpts SelectDirOpts;
	 SelectDirOpts << sdAllowCreate;
	 //bool bOk = SelectDirectory(strDir, SelectDirOpts,0);
	 //bool bOk = SelectDirectory("����� �������� ����������" , WideString(""), strDir);
	 //bool bOk = SelectDirectory("����� �������� ����������" , "", strDir);
	 //bool bOk = SelectDirectory(System::UnicodeString("����� �������� ����������"), WideString(""), strDir);
//extern PACKAGE bool __fastcall SelectDirectory(System::UnicodeString &Directory, TSelectDirOpts Options, int HelpCtx)/* overload */;
//extern PACKAGE bool __fastcall SelectDirectory(const System::UnicodeString Caption, const System::WideString Root, System::UnicodeString &Directory, TSelectDirExtOpts Options = (TSelectDirExtOpts() << sdNewUI ), Controls::TWinControl* Parent = (Controls::TWinControl*)(0x0))/* overload */;
	 System::UnicodeString ustrDir(strDir);
	 bool bOk = SelectDirectory(System::UnicodeString("����� �������� ����������"), System::WideString(""), ustrDir);

	 if(bOk == true)
	 {
		 strDir = ustrDir.t_str();
		 DirEdit->Text = strDir;
	 }
}
//---------------------------------------------------------------------------

