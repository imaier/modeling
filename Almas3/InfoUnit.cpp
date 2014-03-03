//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "InfoUnit.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TInfoForm *InfoForm;
//---------------------------------------------------------------------------
__fastcall TInfoForm::TInfoForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TInfoForm::AddModelViewMatrix(float *Mtr)
{
    GL_MODELVIEW_MATRIXMemo->Lines->Clear();
    AnsiString S;
    for(int i=0; i<4; i++)
    {
     //GL_MODELVIEW_MATRIXMemo->Lines->Strings[i] = "";
     S = "";
     for(int j=0; j<4; j++)
     {
      S += AnsiString((float)(floor(1000*Mtr[i*4+j]+0.5)/1000)) + " ";
	  //S += S + "\t";
     }
     GL_MODELVIEW_MATRIXMemo->Lines->Add(S);
   }
}
//---------------------------------------------------------------------------
void TInfoForm::AddProjectionMatrix(float *Mtr)
{
    GL_PROJECTION_MATRIXMemo->Lines->Clear();
    AnsiString S;
    for(int i=0; i<4; i++)
    {
     //GL_PROJECTION_MATRIXMemo->Lines->Strings[i] = "";
     S = "";
     for(int j=0; j<4; j++)
     {
      S += AnsiString((float)(floor(1000*Mtr[i*4+j]+0.5)/1000)) + " ";
	  //S += S + "\t";
     }
     GL_PROJECTION_MATRIXMemo->Lines->Add(S);
    }
}
//---------------------------------------------------------------------------