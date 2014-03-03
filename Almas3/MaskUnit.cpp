//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "MaskUnit.h"
#include <stdlib.h>
#include "Matrix.h"
#include <math.h>
//#include "Main.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMaskForm *MaskForm;
TMask *DefaultMask;
const double sqrt_2 = 1/sqrt(2.0);
const double sqrt_3 = 1/sqrt(3.0);
//Mtr - матрица преобразовани€ координат из нормальных в
//координаты образца (ромба), где
//точка 0 - сама€ лева€ точка (вершина) ромба
//X - ось, совпадающа€ с короткой диоганалью ромба, положительное направление  - справа
//Y - ось, параллельна€ длинной диоганали ромба, положительное направление - вверх
//Z - ось, направленна€ перпендикул€рно рисунку, положительное направление - вглубь (от нас)
const double Mtr[3][3]=
{
#ifdef Almas100
/*X*/ {( 1.0), (0.0), (0.0)},
/*Y*/ {( 0.0), (1.0), (0.0)},
/*Z*/ {( 0.0), (0.0), (1.0)}
#endif
#ifdef Almas110
/*X*/ { (1.0)*sqrt_2, (1.0)*sqrt_2, (0.0)},
/*Y*/ { (0.0),        (0.0),       (-1.0)},
/*Z*/ {(-1.0)*sqrt_2, (1.0)*sqrt_2, (0.0)}
#endif
#ifdef Almas111
/*X*/ {(2.0)*sqrt_2*sqrt_3, (-1.0)*sqrt_2*sqrt_3, (-1.0)*sqrt_2*sqrt_3},
/*Y*/ {(0),                 (1.0)*sqrt_2,         (-1.0)*sqrt_2       },
/*Z*/ {(1.0)*sqrt_3,        (1.0)*sqrt_3,         (1.0)*sqrt_3        }
#endif
};
const double Cxy = sqrt(2.0/3.0);
//Mtr2 - матрица преобразовани€ координат из нормальных в
//координаты образца (ромба), где
//точка 0 - сама€ лева€ точка (вершина) ромба
//X - ось, совпадающа€ со стороной ромба, проход€щей через точку 0, положительное направление  - вниз
//Y - ось, совпадающа€ со стороной ромба, проход€щей через точку 0, положительное направление  - вверх
//Z - ось, направленна€ перпендикул€рно рисунку, положительное направление - вглубь (от нас)
const double Mtr2[3][3]=
{
#ifdef Almas100
/*X*/ {( 4.0), (0.0), (0.0)},
/*Y*/ {( 0.0), (4.0), (0.0)},
/*Z*/ {( 0.0), (0.0), (4.0)}
#endif
#ifdef Almas110
/*X*/ {( 4.0), (4.0), (0.0)},//из семпловых координат в глобальные
/*Y*/ {( 0.0), (0.0),(-4.0)},
/*Z*/ {(-2.0), (2.0), (0.0)}
#endif
#ifdef Almas111
/*X*/ {(2.0), (-4.0),  (2.0)},
/*Y*/ {(2.0),  (2.0), (-4.0)},
/*Z*/ {(4.0),  (4.0),  (4.0)}
//в глобальных координатах точка начала отсчЄта €чейки с координатами (i,j,k) 
//(i*2+j*2+k*4, i*(-4)+j*2+k*4, i*2+j*(-4)+k*4)
#endif
};

#ifdef Almas100
//„исло семплов вдоль оси X
const int NumSemplsX = 4;
//„исло семплов вдоль оси Y
const int NumSemplsY = 4;
#endif
#ifdef Almas110
//„исло семплов вдоль оси X
const int NumSemplsX = 4;
//„исло семплов вдоль оси Y
const int NumSemplsY = 4;
#endif
#ifdef Almas111
//„исло семплов вдоль оси X
const int NumSemplsX = 3;
//„исло семплов вдоль оси Y
const int NumSemplsY = 3;
#endif

//---------------------------------------------------------------------------
__fastcall TMaskForm::TMaskForm(TComponent* Owner)
	: TForm(Owner)
{
    AnsiString Digit = AnsiString(NumSemplsX);
    char cNumSemplsX = Digit[1];
    Digit = AnsiString(NumSemplsY);
    char cNumSemplsY = Digit[1];
    AnsiString Cpt;
    TLabel *Lbl;
    Lbl = RectangleXLabel;
    Cpt = Lbl->Caption;
    Cpt[Cpt.Length()-1] = cNumSemplsX;
    Lbl->Caption = Cpt;
    Lbl = RectangleYLabel;
    Cpt = Lbl->Caption;
    Cpt[Cpt.Length()-1] = cNumSemplsY;
    Lbl->Caption = Cpt;
    Lbl = RectangleWLabel;
    Cpt = Lbl->Caption;
    Cpt[Cpt.Length()-1] = cNumSemplsX;
    Lbl->Caption = Cpt;
    Lbl = RectangleHLabel;
    Cpt = Lbl->Caption;
    Cpt[Cpt.Length()-1] = cNumSemplsY;
    Lbl->Caption = Cpt;

    Lbl = CircleXLabel;
    Cpt = Lbl->Caption;
    Cpt[Cpt.Length()-1] = cNumSemplsX;
    Lbl->Caption = Cpt;
    Lbl = CircleYLabel;
    Cpt = Lbl->Caption;
    Cpt[Cpt.Length()-1] = cNumSemplsY;
    Lbl->Caption = Cpt;
}
//---------------------------------------------------------------------------
void __fastcall TMaskForm::InitForm(TMask &MaskInit)
{
//    if(MaskInit == NULL)
//    {
//     if(DefaultMask==NULL) Mask = new TMask;
//	 else Mask = new TMask(DefaultMask);
//    }
//	else Mask = new TMask(MaskInit);

    Mask.CopyMask(MaskInit);

    if(Mask.KindFig == kfRectangle)
    {
     RectangleRadioButton->Checked = true;
     SetKindFig (true);
    }
    else
    {
     CircleRadioButton->Checked = true;
     SetKindFig (false);
    }

     RectangleXEdit->Text = AnsiString((double)Mask.X);
     RectangleYEdit->Text = AnsiString((double)Mask.Y);
     RectangleWEdit->Text = AnsiString((double)Mask.W);
     RectangleHEdit->Text = AnsiString((double)Mask.H);
     RectangleAngleEdit->Text = AnsiString((double)Mask.Angle);

     CircleXEdit->Text = AnsiString((double)Mask.X);
     CircleYEdit->Text = AnsiString((double)Mask.Y);
     CircleREdit->Text = AnsiString((double)Mask.R);

     NOTCheckBox->Checked = Mask.Not;
     if(Mask.LogicFunction == lfAND) LogicComboBox->ItemIndex = 0;
     else if(Mask.LogicFunction == lfOR) LogicComboBox->ItemIndex = 1;
     	  else LogicComboBox->ItemIndex = 2;

     if(Mask.TypeSuperimproseMask == tsmmBoolean)
     {
      BoolRadioButton->Checked = true;
	  SetTypeSuperimproseMask(tsmmBoolean);
     }
     else
     {
      ImmediatelyRadioButton->Checked = true;
	  SetTypeSuperimproseMask(tsmmImmediately);
     }
     if( Mask.InsideFig == ifDeletedAtoms) DelRadioButton->Checked = true;
     else NoDelRadioButton->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TMaskForm::SetKindFig (bool IfRectangle)
{

	RectangleGroupBox->Enabled = IfRectangle;
     RectangleXEdit->Enabled = IfRectangle;
     RectangleXLabel->Enabled = IfRectangle;
     RectangleYEdit->Enabled = IfRectangle;
     RectangleYLabel->Enabled = IfRectangle;
     RectangleWEdit->Enabled = IfRectangle;
     RectangleWLabel->Enabled = IfRectangle;
     RectangleHEdit->Enabled = IfRectangle;
     RectangleHLabel->Enabled = IfRectangle;
     RectangleAngleEdit->Enabled = IfRectangle;
     RectangleAngleLabel->Enabled = IfRectangle;

    IfRectangle = !IfRectangle;

    CircleGroupBox->Enabled = IfRectangle;
     CircleXEdit->Enabled = IfRectangle;
     CircleXLabel->Enabled = IfRectangle;
     CircleYEdit->Enabled = IfRectangle;
     CircleYLabel->Enabled = IfRectangle;
     CircleREdit->Enabled = IfRectangle;
     CircleRLabel->Enabled = IfRectangle;
}
//---------------------------------------------------------------------------
void __fastcall TMaskForm::RectangleRadioButtonClick(TObject *Sender)
{
	SetKindFig(true);
}
//---------------------------------------------------------------------------
void __fastcall TMaskForm::CircleRadioButtonClick(TObject *Sender)
{
	SetKindFig(false);
}
//---------------------------------------------------------------------------
TMask::TMask()
{
	KindFig = kfRectangle;
    X = 0;
    Y = 0;
    H = 100;
    W = 100;
    Angle = 0;
    R = 100;
    Not = false;
    LogicFunction = lfAND;
    TypeSuperimproseMask = tsmmImmediately;
    InsideFig = ifNoDeletedAtoms;
}
//---------------------------------------------------------------------------
void __fastcall TMask::CopyMask(const TMask &Mask)
{
	KindFig  = Mask.KindFig ;
	X = Mask.X;
	Y = Mask.Y;
	H = Mask.H;
	W = Mask.W;
	Angle = Mask.Angle;
	R = Mask.R;
	Not = Mask.Not;
	LogicFunction = Mask.LogicFunction;
	TypeSuperimproseMask = Mask.TypeSuperimproseMask;
	InsideFig = Mask.InsideFig;
}
//---------------------------------------------------------------------------
TMask::TMask(const TMask &Mask)
{
	CopyMask(Mask);
}
//---------------------------------------------------------------------------

bool TMask::operator==(const TMask &Mask) const
{
	bool bRet = true;

	bRet &= KindFig == Mask.KindFig;
	bRet &= X == Mask.X;
	bRet &= Y == Mask.Y;
	bRet &= H == Mask.H;
	bRet &= W == Mask.W;
	bRet &= Angle == Mask.Angle;
	bRet &= R == Mask.R;
	bRet &= Not == Mask.Not;
	bRet &= LogicFunction == Mask.LogicFunction;
	bRet &= TypeSuperimproseMask == Mask.TypeSuperimproseMask;
	bRet &= InsideFig == Mask.InsideFig;

	return bRet;
}
//---------------------------------------------------------------------------
/*
bool TMask::operator<(const TMask &Mask)
{
	bool bRet = true;

	bRet &= KindFig < Mask.KindFig;
	bRet &= X < Mask.X;
	bRet &= Y < Mask.Y;
	bRet &= H < Mask.H;
	bRet &= W < Mask.W;
	bRet &= Angle < Mask.Angle;
	bRet &= R < Mask.R;
	bRet &= Not < Mask.Not;
	bRet &= LogicFunction < Mask.LogicFunction;
	bRet &= TypeSuperimproseMask < Mask.TypeSuperimproseMask;
	bRet &= InsideFig < Mask.InsideFig;

	return bRet;
}
*/
//---------------------------------------------------------------------------
AnsiString __fastcall TMask::TMaskToString()
{
	AnsiString Str;
	Str = AnsiString((double)X) + ",";
	Str += AnsiString((double)Y) + ",";
	if(KindFig  == kfRectangle)
	{
     Str = "ѕр€моугольник(" + Str;
     Str += AnsiString((double)W) + ",";
     Str += AnsiString((double)H) + ",";
     Str += AnsiString((double)Angle) + ",";
    }
    else
    {
     Str = " руг(" + Str;
     Str += AnsiString((double)R) + ",";
    }
    if(TypeSuperimproseMask == tsmmBoolean)
    {
     Str += "Ѕ”Ћ≈¬ќ,";
     if(Not == false) Str += "ѕ–яћќ…,";
     else Str += "»Ќ¬≈–—Ќџ…,";
     if(LogicFunction == lfAND) Str += "»)";
     else Str += "»Ћ»)";
    }
    else
    {
     Str += "Ќ≈ѕќ—–≈—“¬≈ЌЌќ,";
     if(InsideFig == ifDeletedAtoms) Str += "”ƒјЋя“№)";
     else Str += "Ќ≈ ”ƒјЋя“№)";
    }
    return Str;
}
//---------------------------------------------------------------------------
bool __fastcall TMask::IsIncludePoint(double x, double y,double z)
{
    if(TypeSuperimproseMask == tsmmBoolean)
    {
     if(KindFig  == kfRectangle) return (Not ^ IsIncludePointRectangle(x, y, z));
     else return (Not ^ IsIncludePointCircle(x, y, z));
    }
    else
    {
     if(KindFig  == kfRectangle) return IsIncludePointRectangle(x, y, z);
     else return IsIncludePointCircle(x, y, z);
    }
}
//---------------------------------------------------------------------------
bool __fastcall TMask::IsIncludePointCircle(double x, double y, double z)
{
    double xn,yn;
    double xc,yc;
    TMatrix FromSampleToPict;
    TMatrix FromSampleToOrtho;
    TMatrix FromOrthoToPict;
    TMatrix FromPictToSample;
    TMatrix FromPictToOrtho;
    TMatrix FromOrthoToSample;
    TMatrix FromBazeoToSample;
    int ii,jj;
    FromSampleToOrtho.EMatrix();
    FromOrthoToPict.EMatrix();
    FromPictToOrtho.EMatrix();
    FromBazeoToSample.EMatrix();
    FromOrthoToSample.EMatrix();
    for(ii=0;ii<3;ii++)
    {
     for(jj=0;jj<3;jj++)
     {
      FromSampleToOrtho.Item[ii][jj] = Mtr2[jj][ii];
      FromOrthoToPict.Item[ii][jj] = Mtr[ii][jj];
      FromPictToOrtho.Item[ii][jj] = Mtr[jj][ii];
     }
    }
    FromBazeoToSample.Item[0][0] = 1.0/NumSemplsX;
    FromBazeoToSample.Item[1][1] = 1.0/NumSemplsY;
    FromSampleToOrtho = FromSampleToOrtho * FromBazeoToSample;
    FromOrthoToSample = FromSampleToOrtho.BackMatrix332();
    FromSampleToPict = FromOrthoToPict * FromSampleToOrtho;
    FromPictToSample = FromOrthoToSample * FromPictToOrtho;
    TPoint3d PointOrtho(x,y,z);
    TPoint3d PointPict;
    TPoint3d PointSample(X,Y,0);
    PointPict = FromOrthoToPict * PointOrtho;
    xn = PointPict.x;
    yn = PointPict.y;
    PointPict = FromSampleToPict * PointSample;
    xc = PointPict.x;
    yc = PointPict.y;
	return ((pow(xn-xc, 2.0) + pow(yn-yc, 2.0)) < pow(R, 2.0))?true:false;
}
//---------------------------------------------------------------------------
bool __fastcall TMask::IsIncludePointRectangle(double x, double y, double z)
{
    //Convertion
 	double dX[4],dY[4],vdX,vdY;
    double PXp[4],PYp[4];
    int I;
    double An = (Angle*M_PI)/180;
	bool RetVar = true;

    double xn,yn;


	dY[0] = dY[1] = H/2;
	dY[2] = dY[3] = -dY[0];
	dX[1] = dX[2] = W/2;
	dX[0] = dX[3] = -dX[1];
    //семпловые координаты - координаты образца (€чеечные)
    //базовые координаты - тоже самое что и семпловые тока орты короче (не цела€ €чейка, а рассто€ние между столбцами)
    //картиночные координаты - координаты картинки (модуль ортов = 1)
    //орсо координаты - глобальные координаты
    TMatrix FromSampleToPict;
    TMatrix FromSampleToOrtho;
    TMatrix FromOrthoToPict;
    TMatrix FromPictToSample;
    TMatrix FromPictToOrtho;
    TMatrix FromOrthoToSample;
    TMatrix FromBazeoToSample;
    int ii,jj;
    FromSampleToOrtho.EMatrix();
    FromOrthoToPict.EMatrix();
    FromPictToOrtho.EMatrix();
    FromBazeoToSample.EMatrix();
    //FromOrthoToSample = FromOrthoToSample.EMatrix();
    FromOrthoToSample.EMatrix();
    for(ii=0;ii<3;ii++)
    {
     for(jj=0;jj<3;jj++)
     {
      FromSampleToOrtho.Item[ii][jj] = Mtr2[jj][ii];
      FromOrthoToPict.Item[ii][jj] = Mtr[ii][jj];
      FromPictToOrtho.Item[ii][jj] = Mtr[jj][ii];
     }
    }
    FromBazeoToSample.Item[0][0] = 1.0/NumSemplsX;
    FromBazeoToSample.Item[1][1] = 1.0/NumSemplsY;
    FromSampleToOrtho = FromSampleToOrtho * FromBazeoToSample;
    //FromOrthoToSample = FromSampleToOrtho.BackMatrixMTH();
    FromOrthoToSample = FromSampleToOrtho.BackMatrix332();
    FromSampleToPict = FromOrthoToPict * FromSampleToOrtho;
    FromPictToSample = FromOrthoToSample * FromPictToOrtho;
    TPoint3d PointOrtho(x,y,z);
    TPoint3d PointSample;
    PointSample = FromOrthoToSample * PointOrtho;
    xn = PointSample.x;
    yn = PointSample.y;

    for(I=0; I<4;I++)
    {
     vdX = FromSampleToPict.Item[0][0]*dX[I] + FromSampleToPict.Item[0][1]*dY[I];
     vdY = FromSampleToPict.Item[1][0]*dX[I] + FromSampleToPict.Item[1][1]*dY[I];
     dX[I] = vdX*cos(An) - vdY*sin(An);
     dY[I] = vdX*sin(An) + vdY*cos(An);
     vdX = FromPictToSample.Item[0][0]*dX[I] + FromPictToSample.Item[0][1]*dY[I];
     vdY = FromPictToSample.Item[1][0]*dX[I] + FromPictToSample.Item[1][1]*dY[I];
     dX[I] = vdX;
     dY[I] = vdY;

     PXp[I] = (X + dX[I]);
     PYp[I] = (Y + dY[I]);
    }
    for(I = 0; I < 4; I++ )
    {
     RetVar = RetVar && OnOutNorm(xn,yn,PXp[I],PYp[I],PXp[(I+1)%4],PYp[(I+1)%4]);
    }
	return RetVar;
}
//---------------------------------------------------------------------------
bool __fastcall TMask::OnOutNorm(double x, double y,double X0,double Y0,double X1,double Y1)
{
	return (((x-X0)*(Y1-Y0) - (y-Y0)*(X1-X0)) >= 0)?true:false;
}
//---------------------------------------------------------------------------
void __fastcall TMaskForm::OkButtonClick(TObject *Sender)
{
    char *endptr;

	if(RectangleRadioButton->Checked)
	{
	 Mask.KindFig  = kfRectangle;

	 Mask.X = strtod(_c_str(RectangleXEdit->Text), &endptr);
	 Mask.Y = strtod(_c_str(RectangleYEdit->Text), &endptr);
	 Mask.W = strtod(_c_str(RectangleWEdit->Text), &endptr);
	 Mask.H = strtod(_c_str(RectangleHEdit->Text), &endptr);
	 Mask.Angle = strtod(_c_str(RectangleAngleEdit->Text), &endptr);
	}
	else
	{
	 Mask.KindFig = kfCircle;
	 Mask.X = strtod(_c_str(CircleXEdit->Text), &endptr);
	 Mask.Y = strtod(_c_str(CircleYEdit->Text), &endptr);
	 Mask.R = strtod(_c_str(CircleREdit->Text), &endptr);
	}
	Mask.Not = NOTCheckBox->Checked;
	Mask.LogicFunction = lfAND;
	if(LogicComboBox->ItemIndex == 1) Mask.LogicFunction = lfOR;
	if(LogicComboBox->ItemIndex == 2) Mask.LogicFunction = lfXOR;
	//if(LogicComboBox->ItemIndex == 0) Mask.LogicFunction = lfAND;
	//else Mask.LogicFunction = lfOR;

    if(BoolRadioButton->Checked == true) Mask.TypeSuperimproseMask = tsmmBoolean;
    else Mask.TypeSuperimproseMask = tsmmImmediately;

    if(DelRadioButton->Checked == true) Mask.InsideFig = ifDeletedAtoms;
    else Mask.InsideFig = ifNoDeletedAtoms;
}
//---------------------------------------------------------------------------
void __fastcall TMaskForm::SetTypeSuperimproseMask(TTypeSuperimproseMask TSM)
{
    bool BooleanSuperimprose;
    //tsmmImmediately
	if(TSM == tsmmBoolean) BooleanSuperimprose = true;
    else BooleanSuperimprose = false;

	NOTCheckBox->Enabled = BooleanSuperimprose;
    LogicLabel->Enabled = BooleanSuperimprose;
    LogicComboBox->Enabled = BooleanSuperimprose;

    BooleanSuperimprose = !BooleanSuperimprose;

    DelRadioButton->Enabled = BooleanSuperimprose;
    NoDelRadioButton->Enabled = BooleanSuperimprose;
}
//---------------------------------------------------------------------------
void __fastcall TMaskForm::BoolRadioButtonClick(TObject *Sender)
{
	SetTypeSuperimproseMask(tsmmBoolean);
}
//---------------------------------------------------------------------------
void __fastcall TMaskForm::ImmediatelyRadioButtonClick(TObject *Sender)
{
	SetTypeSuperimproseMask(tsmmImmediately);
}
//---------------------------------------------------------------------------
bool TMask::SaveToFile(HANDLE hFile, int *pSeek)
{
	bool bRet;
    int nSeek = 0;
    DWORD NumberOfBytesToWrite, NumberOfBytesWritten;
    bool bwf = true;
    int i;

        NumberOfBytesToWrite = sizeof(TKindFig);
        bwf &= WriteFile(hFile,&(KindFig),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        NumberOfBytesToWrite = sizeof(float);
        bwf &= WriteFile(hFile,&(X),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        bwf &= WriteFile(hFile,&(Y),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        bwf &= WriteFile(hFile,&(H),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        bwf &= WriteFile(hFile,&(W),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        bwf &= WriteFile(hFile,&(Angle),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        bwf &= WriteFile(hFile,&(R),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        NumberOfBytesToWrite = sizeof(bool);
        bwf &= WriteFile(hFile,&(Not),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        NumberOfBytesToWrite = sizeof(TLogicFunction);
        bwf &= WriteFile(hFile,&(LogicFunction),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        NumberOfBytesToWrite = sizeof(TTypeSuperimproseMask);
        bwf &= WriteFile(hFile,&(TypeSuperimproseMask),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

        NumberOfBytesToWrite = sizeof(TInsideFig);
        bwf &= WriteFile(hFile,&(InsideFig),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

    if(pSeek != NULL)
    {
	 *pSeek += nSeek;
    }
    bRet = bwf;
    return bRet;
}
//---------------------------------------------------------------------------
bool TMask::LoadFromFile(HANDLE hFile, int *pSeek)
{
	bool bRet;
    int nSeek = 0;
    DWORD NumberOfBytesRead,NumberOfBytesReaded;
    int i;
    bool bwf = true;

         NumberOfBytesRead = sizeof(TKindFig);
         bwf &= ReadFile(hFile,&(KindFig),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         NumberOfBytesRead = sizeof(float);
         bwf &= ReadFile(hFile,&(X),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         bwf &= ReadFile(hFile,&(Y),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         bwf &= ReadFile(hFile,&(H),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         bwf &= ReadFile(hFile,&(W),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
		 bwf &= ReadFile(hFile,&(Angle),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         bwf &= ReadFile(hFile,&(R),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         NumberOfBytesRead = sizeof(bool);
         bwf &= ReadFile(hFile,&(Not),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         NumberOfBytesRead = sizeof(TLogicFunction);
         bwf &= ReadFile(hFile,&(LogicFunction),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         NumberOfBytesRead = sizeof(TTypeSuperimproseMask);
         bwf &= ReadFile(hFile,&(TypeSuperimproseMask),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
         NumberOfBytesRead = sizeof(TInsideFig);
         bwf &= ReadFile(hFile,&(InsideFig),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

    if(pSeek != NULL)
    {
	 *pSeek += nSeek;
    }
    bRet = bwf;
    return bRet;
}
//---------------------------------------------------------------------------
bool TMaskVec::SaveToFile(HANDLE hFile, int *pSeek)
{//сохранить вектор масок в файл
	bool bRet;
    int nSeek = 0;
    DWORD NumberOfBytesToWrite, NumberOfBytesWritten;
    bool bwf = true;
    int i, nCountMask;
    nCountMask = size();

       NumberOfBytesToWrite = sizeof(nCountMask);
       bwf &= WriteFile(hFile,&(nCountMask),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

    for(i=0; i < nCountMask && bwf; i++)
    {
        TMask &Mask = (*this)[i];
        bwf &= Mask.SaveToFile(hFile, &nSeek);
    }

    if(pSeek != NULL)
    {
	 *pSeek += nSeek;
    }
    bRet = bwf;
    return bRet;
}
//---------------------------------------------------------------------------
bool TMaskVec::LoadFromFile(HANDLE hFile, int *pSeek)
{//загрузить вектор масок из файла
    bool bRet = false;
    int nSeek = 0;
    DWORD NumberOfBytesRead,NumberOfBytesReaded;
    int i, nCountMask;
    bool bwf = true;
    clear();

        NumberOfBytesRead = sizeof(nCountMask);
        bwf &= ReadFile(hFile,&(nCountMask),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

    TMask Mask;
    for(i=0; i < nCountMask && bwf; i++)
    {
        bwf &= Mask.LoadFromFile(hFile, &nSeek);
        if(bwf == true)
            push_back(Mask);
    }

    if(pSeek != NULL)
    {
     *pSeek += nSeek;
    }
    bRet = bwf;
    return bRet;
}
//---------------------------------------------------------------------------

