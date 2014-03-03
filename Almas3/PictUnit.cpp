//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "PictUnit.h"
#include "SurfaceUnit.h"
#include "MaskUnit.h"
#include "Matrix.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TPictuteForm *PictuteForm;
//---------------------------------------------------------------------------
__fastcall TPictuteForm::TPictuteForm(TComponent* Owner)
	: TForm(Owner)
{
    PictPaintBox->Canvas->Pen->Color = clBlue ;
	PictPaintBox->Canvas->Pen->Mode = pmCopy ;
    PictPaintBox->Canvas->Pen->Style = psInsideFrame ;
	PictPaintBox->Canvas->Pen->Width = 1 ;
    PictPaintBox->Canvas->Brush->Color = clWhite ;
    PictPaintBox->Canvas->Brush->Style = bsSolid ;
    PictPaintBox->Canvas->CopyMode = cmSrcCopy;

    Painted = false;
}
//---------------------------------------------------------------------------
void __fastcall TPictuteForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	//Action = caFree;
	//delete Bmp;
	//PictuteForm = NULL;
	Action = caHide;
	m_vMask.clear();
	m_nWidth = 1;
	m_nHeight = 1;
}
//---------------------------------------------------------------------------
void __fastcall TPictuteForm::FormPaint(TObject *Sender)
{
	if(Painted)
	{
	 return;
	}

	PaintPicture(PictPaintBox, m_vMask, m_nWidth, m_nHeight);
	Painted = true;
}
//---------------------------------------------------------------------------
void __fastcall PaintPicture(TPaintBox* PB, TMaskVec &vMask, int nSizeX, int nSizeY)
{
	 if(nSizeX <= 0 || nSizeY <= 0)
	 {
      return;
	 }

	 int i,j,di,dj;
	 bool Visibled;
	 double SizeX,SizeY;
	 double W,H,x,y,SzXn,SzYn,xorto,yorto,zorto;

	 W = PB->ClientWidth;
	 H = PB->ClientHeight;
	 SizeX = nSizeX;
	 SizeY = nSizeY;

     TMatrix FromSampleToPict;
     TMatrix FromSampleToOrto,FromOrtoToSample;
	 TMatrix FromOrtoToPict,FromPictToOrto,bb,be;
	 TPoint3d P0,P00,P01,P11,P10,P00p,P01p,P11p,P10p,P00s,P01s,P11s,P10s;
     FromSampleToOrto.EMatrix();
     FromOrtoToPict.EMatrix();
     bb = be*0;
     be = bb;
	 P00s = TPoint3d(0*SizeX,0*SizeY,0);
     P01s = TPoint3d(1*SizeX,0*SizeY,0);
     P11s = TPoint3d(1*SizeX,1*SizeY,0);
     P10s = TPoint3d(0*SizeX,1*SizeY,0);
     for(i=0;i<3;i++)
	 {
      for(j=0;j<3;j++)
      {
       FromSampleToOrto.Item[i][j] = Mtr2[j][i];
	   FromOrtoToSample.Item[i][j] = Mtr2[i][j];
       FromOrtoToPict.Item[i][j] = Mtr[i][j];
       FromPictToOrto.Item[i][j] = Mtr[j][i];
	   //bb.Item[i][j] = Mtr[j][i];
      }
	 }
     //FromOrtoToPict = (FromPictToOrto.BackMatrixMTH());
	 //FromPictToOrto = (FromOrtoToPict.BackMatrixMTH());
     //be = bb*FromOrtoToPict;
     //be = FromOrtoToPict * FromPictToOrto;
     //be = (FromOrtoToPict.BackMatrix());
     //be = FromOrtoToPict * FromPictToOrto;
     //FromPictToOrto = (FromOrtoToPict.BackMatrix33());
     //bb = FromOrtoToPict * FromPictToOrto;
     //FromPictToOrto = (FromOrtoToPict.BackMatrixMTH());

     //FromSampleToOrto = FromSampleToOrto;// * (1.0/3.0);
     //FromSampleToPict = FromOrtoToPict * FromSampleToOrto;
     //xorto = FromSampleToOrto.Item[0][0]*SizeX + FromSampleToOrto.Item[0][1]*SizeY;
	 //yorto = FromSampleToOrto.Item[1][0]*SizeX + FromSampleToOrto.Item[1][1]*SizeY;
     //zorto = FromSampleToOrto.Item[2][0]*SizeX + FromSampleToOrto.Item[2][1]*SizeY;
     //P00 = FromSampleToOrto * P00s;
     //P01 = FromSampleToOrto * P01s;
	 //P11 = FromSampleToOrto * P11s;
     //P10 = FromSampleToOrto * P10s;
     //SzXn = FromOrtoToPict.Item[0][0]*xorto + FromOrtoToPict.Item[0][1]*yorto + FromOrtoToPict.Item[0][2]*zorto;
     //SzYn = FromOrtoToPict.Item[1][0]*xorto + FromOrtoToPict.Item[1][1]*yorto + FromOrtoToPict.Item[1][2]*zorto;
     //P00p = FromOrtoToPict * P00;
     //P01p = FromOrtoToPict * P01;
	 //P11p = FromOrtoToPict * P11;
     //P10p = FromOrtoToPict * P10;
     FromSampleToPict = FromOrtoToPict * FromSampleToOrto;
     P00p = FromSampleToPict * P00s;
     P01p = FromSampleToPict * P01s;
	 P11p = FromSampleToPict * P11s;
     P10p = FromSampleToPict * P10s;
     SzXn = (P11p-P00p).x;
	 SzYn = (P10p-P01p).y;
	 P0 = P11p*0.5;

	 if(SzXn/SzYn > W/H)
	 {
	  di = 0;
	  dj = floor(((H-SzYn*W/SzXn)/2.0)+0.5);
	 }
	 else
	 {
	  di = floor(((W-SzXn*H/SzYn)/2.0)+0.5);
	  dj = 0;
	 }


	 Graphics::TBitmap *Bmp;
	 Bmp = new Graphics::TBitmap;
	 Bmp->Height = H-2;
	 Bmp->Width = 1;
	 Bmp->Canvas->Pen->Color = clBlue ;
	 Bmp->Canvas->Pen->Mode = pmCopy ;
	 Bmp->Canvas->Pen->Style = psInsideFrame ;
	 Bmp->Canvas->Pen->Width = 1 ;
	 Bmp->Canvas->Brush->Color = clWhite ;
	 Bmp->Canvas->Brush->Style = bsSolid ;
	 Bmp->Canvas->CopyMode = cmSrcCopy;


	 PB->Canvas->MoveTo(0,0);
	 PB->Canvas->LineTo(0,H);
	 for(i = 1; i < W-1; i++)
	 {
	  PB->Canvas->MoveTo(i+1,0);
	  PB->Canvas->LineTo(i+1,H);
	  for(j = 0; j < H; j++)
	  {
	   Visibled = true;
	   x = (double)(i-di)*SzXn/(W-2*di) - SzXn/2.0;
	   y = (double)(H-j-dj)*SzYn/(H-2*dj) - SzYn/2.0;

	   xorto = FromPictToOrto.Item[0][0]*x + FromPictToOrto.Item[0][1]*y;
	   yorto = FromPictToOrto.Item[1][0]*x + FromPictToOrto.Item[1][1]*y;
	   zorto = FromPictToOrto.Item[2][0]*x + FromPictToOrto.Item[2][1]*y;
	   x = FromPictToOrto.Opred();
	   for(UINT k = 0; k < vMask.size(); k++)
	   {
		TMask &Mask = vMask[k];

		if(Mask.TypeSuperimproseMask == tsmmBoolean)
		{
		 if(Mask.LogicFunction == lfAND) Visibled = Visibled && (!Mask.IsIncludePoint(xorto, yorto,zorto));
		 else if(Mask.LogicFunction == lfOR) Visibled = Visibled || (!Mask.IsIncludePoint(xorto, yorto,zorto));
			  else Visibled = Visibled ^ (!Mask.IsIncludePoint(xorto, yorto,zorto));
		}
		else
		{
		 if( Mask.IsIncludePoint(xorto, yorto,zorto))
		 {
		  if(Mask.InsideFig == ifDeletedAtoms) Visibled = true;
			 else Visibled = false;
		 }
		}
	   }
	   if(Visibled)  Bmp->Canvas->Pixels[0][j] = clWhite;
	   else Bmp->Canvas->Pixels[0][j] = clRed;

	  }
	  PB->Canvas->Draw(i,1, Bmp);
	 }
	 x = (P00p-P0).x;
	 y = (P00p-P0).y;

	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->MoveTo(i,j);
	 x = (P01p-P0).x;
	 y = (P01p-P0).y;
	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->LineTo(i,j);

	 x = (P11p-P0).x;
	 y = (P11p-P0).y;
	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->LineTo(i,j);

	 x = (P10p-P0).x;
	 y = (P10p-P0).y;
	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->LineTo(i,j);

	 x = (P00p-P0).x;
	 y = (P00p-P0).y;
	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->LineTo(i,j);

	 //оси
	 TColor PenColor;
	 PB->Canvas->Pen->Mode = pmMergePenNot;
	 //	pmMergePenNot;
	 //pmNotXor;
	 PenColor = PB->Canvas->Pen->Color;
	 //X
	 PB->Canvas->Pen->Color = clRed;
	 x = ((P00p+P10p)*(1.0/2.0)-P0).x;
	 y = ((P00p+P10p)*(1.0/2.0)-P0).y;
	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->MoveTo(i,j);
	 x = ((P01p+P11p)*(1.0/2.0)-P0).x;
	 y = ((P01p+P11p)*(1.0/2.0)-P0).y;
	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->LineTo(i,j);
	 //Y
	 PB->Canvas->Pen->Color = clLime;
	 x = ((P00p+P01p)*(1.0/2.0)-P0).x;
	 y = ((P00p+P01p)*(1.0/2.0)-P0).y;
	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->MoveTo(i,j);
	 x = ((P10p+P11p)*(1.0/2.0)-P0).x;
	 y = ((P10p+P11p)*(1.0/2.0)-P0).y;
	 i = di + floor(((W-2*di)*(x+SzXn/2.0)/SzXn));
	 j = H-dj-floor(((H-2*dj)*(y+SzYn/2.0)/SzYn));
	 PB->Canvas->LineTo(i,j);

	 PB->Canvas->Pen->Color = PenColor;

	 delete Bmp;
}
//---------------------------------------------------------------------------
void __fastcall TPictuteForm::FormResize(TObject *Sender)
{
	Painted = false;
}
//---------------------------------------------------------------------------
void __fastcall TPictuteForm::PaintMask(TMaskVec &vMask, int nWidth, int nHeight)
{
	m_vMask = vMask;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	Painted = true;

	if(Visible == false)
	{
	 Show();
	}
	else
	{
	 BringToFront();
	}

	Painted = false;

	Repaint();
}
//---------------------------------------------------------------------------

