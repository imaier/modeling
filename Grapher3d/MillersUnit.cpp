//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MillersUnit.h"
#include "Matrix.h"
#include "math.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TMillersIndexes::TMillersIndexes()
{
    h = 1;
    k = 0;
    l = 0;
}
TMillersIndexes::TMillersIndexes(TMillersIndexes& r)
{
    *this = r;
}
TMillersIndexes& TMillersIndexes::operator = (const TMillersIndexes& r)
{
    h = r.h;
    k = r.k;
    l = r.l;
    return *this;
}

TMillersIndexes TMillersIndexes::Perpend()
{
    TMillersIndexes Perp;

    TPoint3d Mill;//вектор миллера

    Mill.x = h;
    Mill.y = k;
    Mill.z = l;
    Mill.Normirate();//приведЄм к зноменателю

    //Mill

    TMatrix mtr_hkl, mtr_rotate;
    mtr_hkl.EMatrix();//изначальные координаты

    //mtr_rotate.RollY_ZOX(Mill.AngleTeta());
    //вокруг глобальной Y
    mtr_rotate.Roll(-Mill.AngleTeta(), TPoint3d(mtr_hkl.Item[1][0], mtr_hkl.Item[1][1], mtr_hkl.Item[1][2]));
    mtr_hkl = mtr_hkl * mtr_rotate;
    //mtr_rotate.RollX_YOZ(Mill.AnglePhi());
    //вокруг глобальной X
    mtr_rotate.Roll(-(Mill.AnglePhi()-M_PI/2), TPoint3d(mtr_hkl.Item[0][0], mtr_hkl.Item[0][1], mtr_hkl.Item[0][2]));
    mtr_hkl = mtr_hkl * mtr_rotate;

    //Perp =
    Perp.h = mtr_hkl.Item[0][0];
    Perp.k = mtr_hkl.Item[0][1];
    Perp.l = mtr_hkl.Item[0][2];

    return Perp;
}

double TMillersIndexes::Angle(TMillersIndexes& SecondIndex)
{
    TPoint3d a(h,k,l);
    TPoint3d b(SecondIndex.h, SecondIndex.k, SecondIndex.l);
    double angle = a.AngleBetwinVectors(b)*180/M_PI;
    return angle;
    //-4,37113900018644E-8
}
//---------------------------------------------------------------------------

TMillersForm *MillersForm;
//---------------------------------------------------------------------------
__fastcall TMillersForm::TMillersForm(TComponent* Owner)
    : TForm(Owner)
{
    m_bShowExeption = false;
    m_bCalcs = true;
}
//---------------------------------------------------------------------------
void __fastcall TMillersForm::FormShow(TObject *Sender)
{
    m_bCalcs = false;
    DirectIndexHEdit->Text = MI.h;
    DirectIndexKEdit->Text = MI.k;
    DirectIndexLEdit->Text = MI.l;
    m_bCalcs = true;
    DirectIndexHEditChange(Sender);
}
//---------------------------------------------------------------------------
bool TMillersForm::CalcIndex(void)
{
    bool bRet = true;
    AnsiString S;
    TEdit *pIndexEdit;
    try
    {
     if(DirectIndexHEdit->Text != ""
     && DirectIndexHEdit->Text != ""
     && DirectIndexHEdit->Text != "")
     {
      pIndexEdit = DirectIndexHEdit;
      MI.h = pIndexEdit->Text.ToDouble();
      pIndexEdit = DirectIndexKEdit;
      MI.k = pIndexEdit->Text.ToDouble();
      pIndexEdit = DirectIndexLEdit;
      MI.l = pIndexEdit->Text.ToDouble();

      TMillersIndexes PerpMI;
      PerpMI = MI.Perpend();
      PerpIndexHEdit->Text = AnsiString().sprintf("%.2f",PerpMI.h);
      PerpIndexKEdit->Text = AnsiString().sprintf("%.2f",PerpMI.k);
      PerpIndexLEdit->Text = AnsiString().sprintf("%.2f",PerpMI.l);

      if(AngleIndexHEdit->Text != ""
      && AngleIndexKEdit->Text != ""
      && AngleIndexLEdit->Text != "")
      {
       TMillersIndexes AngelMI;

       pIndexEdit = AngleIndexHEdit;
       AngelMI.h = pIndexEdit->Text.ToDouble();
       pIndexEdit = AngleIndexKEdit;
       AngelMI.k = pIndexEdit->Text.ToDouble();
       pIndexEdit = AngleIndexLEdit;
       AngelMI.l = pIndexEdit->Text.ToDouble();

       double dAngle = MI.Angle(AngelMI);
       AngleValueLabel->Caption = AnsiString().sprintf("%.2f",dAngle);//FloatToStrF(dAngle, AnsiString::sffGeneral, 5,2);
      }
     }
    }
    catch(EConvertError *EC)
    {
     bRet = false;
     if(m_bShowExeption == true)
     {
      S = pIndexEdit->Text;
      AnsiString Text = "¬ведено неправильное чиcловое значение '" + S + "'";
	  Application->MessageBox(_WST(Text),_WST("ќшибка"),MB_OK | MB_ICONEXCLAMATION);
      if(pIndexEdit->CanFocus())
	   pIndexEdit->SetFocus();
     }
	}
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TMillersForm::DirectIndexHEditChange(TObject *Sender)
{
    if(m_bCalcs == true)
    {
     CalcIndex();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMillersForm::OkButtonClick(TObject *Sender)
{
     m_bShowExeption = true;
     if(CalcIndex() == true)
     {
      ModalResult = mrOk;
     }
     m_bShowExeption = false;
}
//---------------------------------------------------------------------------

