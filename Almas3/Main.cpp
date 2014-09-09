//---------------------------------------------------------------------------
// Добавить подсветку типов атомов при обрезании образца
//
//


#include <vcl\vcl.h>
#pragma hdrstop
#pragma warn -pck

//#define Almas100
//#define Almas111
//#define Almas110
//см. Project|Options... вкладка Directories/Conditionals строка Conditional defined

#include "KeysControl.h"
#include "Main.h"
#include "Dissolution.h"
#include "Monitoring.h"
#include "GLDrow.h"
#include "InfoUnit.h"
#include "SurfaceUnit.h"
#include "PropertyUnit.h"
#include "ScreenCopyUnit.h"
#include "QuantityByGroupeUnit.h"
//---------------------------------------------------------------------------
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glaux.h>
#include <math.h>
#include "Matrix.h"
#include <vcl\Clipbrd.hpp>
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
TDissolutionThread *DissolutionThread;
//---------------------------------------------------------------------------
//мксимальная длна имени ориентации
#define MAX_ORN_NAME 40
#define ORN_FILE_ID_STRING "This File is ORN Format v1.1"

//#define PROGNAME_AND_VER AnsiString("Образец 3 ")
#ifdef Almas100
#define PROGNAME_AND_VER AnsiString("Образец 3 100 ")
#endif
#ifdef Almas110
#define PROGNAME_AND_VER AnsiString("Образец 3 110 ")
#endif
#ifdef Almas111
#define PROGNAME_AND_VER AnsiString("Образец 3 111 ")
#endif

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	Caption = PROGNAME_AND_VER;
/*
#ifdef Almas100
	Caption = PROGNAME_AND_VER + "(поверхность 100)";
#endif
#ifdef Almas110
	Caption = PROGNAME_AND_VER + "(поверхность 110)";
#endif
#ifdef Almas111
	Caption = PROGNAME_AND_VER + "(поверхность 111)";
#endif
*/

#ifdef Almas100
	AbaFileIdString = "ABA3 100 format.";
#endif
#ifdef Almas110
	AbaFileIdString = "ABA3 110 format.";
#endif
#ifdef Almas111
	AbaFileIdString = "ABA3 111 format.";
#endif


	pMVM = (GLfloat*)ModelViewMatrix;
	Initialiseded = false;
    PaintCnt = 0;
    Alpha=Beta=0;
    SpeedAlpha = SpeedBeta = 100.0e5;
    Keys = new TKeysState;
    Position = 195;
    Min = 0;
    Max = 400;
    Application->OnIdle = AppOnIdle;
    IsListGen = false;
	IsSurfaceGen = false;
    ScaleStep = 1.1;

    EyeX = 0;
	EyeY = 0;
	EyeZ = 1000;
	CenterX = 0;
	CenterY = 0;
	CenterZ = 0;
	UpX = 0;
	UpY = 1;
	UpZ = 0;
    Near = 1;
    Far = 2000;
	StepDem = 1;
    Roll = 0;
    RollPhi=RollTeta=0.1;
	RollX = RollY = RollZ = 0;
    dRoll = 0.3;
    dDirection = 5;
   //Паралельная
    XPort = YPort = 10;
    PrintIndex = true;
   //Перспективная
    //XPort = YPort = 0.2;

    AlphaT = BetaT = GammaT = 0;
    AlphaG = BetaG = GammaG = 0;
    AlphaW = BetaW = GammaW = 90.0/16.0;//5;
    MultiAngle = 1;
    MulAngleLabel->Caption = "Угол x " + AnsiString(MultiAngle);//"Angle •" + AnsiString(MultiAngle);
    SpeedXT = SpeedYT = SpeedZT = 0;
    SpeedXW = SpeedYW = SpeedZW = 1;
    CenterXT = CenterYT = CenterZT = 0;
    MultiSpeed = 1;
    MulSpeedLabel->Caption = "Шаг x " + AnsiString(MultiSpeed);//"Move •" + AnsiString(MultiSpeed);
    AtomSize = 1.0;
    AtomSizeLabel->Caption = "Размер атома x " + AnsiString(AtomSize);//"Move •" + AnsiString(MultiSpeed);

	AxisX=AxisY=AxisZ=AxisCheckBox->Checked;//true;
	IsLinksVisibled = LinksCheckBox->Checked;
    MillersComboBox->ItemIndex = 0;
    SaveOrientationComboBox->ItemIndex = 0;
    AtomsColorsComboBox->ItemIndex = 0;
    AtomsColorsComboBoxChange(NULL);
    EnabledPaint = true;
    Scale = 1.0;
    LstTm = LstTm.CurrentDateTime();
    /*
    for(int i = 0; i < 3; i++)
    {
     KindAtoms[i] = NULL;
     NumberKindAtoms[i] = 0;
	 LinksFromKindAtoms[i][0] = NULL;
	 LinksFromKindAtoms[i][1] = NULL;
    }
    KindAtoms[4] = NULL;
    NumberKindAtoms[4] = 0;
	NoDeleteAtoms = NULL;
    NumberNoDeleteAtoms = 0;
    LinksFromNoDeleteAtoms[0] = NULL;
    LinksFromNoDeleteAtoms[1] = NULL;
	NumberLinksFromNoDeleteAtoms = 0;
    */
    Atoms = NULL;
    LinksFromAtoms[0] = NULL;
    LinksFromAtoms[1] = NULL;
    NumberAtoms = 0;
    NumberLinksFromAtoms = 0;


    ExperimentProperty = new TExperimentProperty;
    DsslExpPrprt = NULL;
    Application->HintHidePause = 100000;
    SetScaleLable();
    DissolutionParamsSet = false;
    ExternExpProp = false;
    StatPauseLabel->Enabled = StatStopPanel->Enabled;
    StatPauseLabel->Caption = StatStopPanel->Caption;
    //ApplyOrientaton = false;
    //ClearVisibledBit = false;
    MillersIndexesLabel->Caption = "(--;--;--)";
    OrthoMillersIndexesLabel->Caption = "|- (--;--;--)";
    PaintCntLabel->Caption = "OpenGL не инициализирован";
    Depth = DepthCheckBox->Checked;
    DelHoldSpeedButtonClick(NULL);
    ShowSurfPanelSpeedButtonClick(NULL);
    SelAtom.Type = 0;
    DefaultMask = NULL;
    Points = true;
    PointsCheckBoxClick(NULL);
    Qality = 10;
    SurfaceMode = false;

    InitSecondTypeComboBox();

    SelectAtomType = true;
    pQuantityByGroupeForm=NULL;

    SSD.m_bCapture = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::InitSecondTypeComboBox()
{//инициализация комбика типов атомов
    static AnsiString strProbId = "InitProb";
    AnsiString strNewProbId = "";
    IBaseProbSet *pBaseProbSet = NULL;
    if(DissolutionParamsSet)
    {
     pBaseProbSet = m_DssParams.SP.GetInterface();
     if(pBaseProbSet != NULL)
     {
      strNewProbId = pBaseProbSet->GetGlobalData().GetProbSetIdString();
     }
    }

    if(strNewProbId != strProbId)
    {
	 SecondTypeComboBox->Items->Clear();
     if(pBaseProbSet != NULL)
     {
      int nCnt = pBaseProbSet->GetGlobalData().GetAllNumProbality();
      AnsiString strKey;
      for(int i = 0; i < nCnt; i++)
      {
		strKey = pBaseProbSet->GetGlobalData().GetProbName(i);
		SecondTypeComboBox->Items->AddObject(strKey, (TObject*)i);
	  }
	 }
	 SecondTypeComboBox->Items->AddObject("(*) Все", (TObject*)-2);
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StatusBar1DrawPanel(TStatusBar *StatusBar,
	TStatusPanel *Panel, const TRect &Rect)
{
    TRect r = Rect;
	r.Left ++;
	r.Top++;
	r.Right -=15;
	r.Bottom--;
    StatusRect = r;
    DrowProgress();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TimerTimer(TObject *Sender)
{
	//Position++;
	//Position = Min + (Position-Min)%(Max-Min);
    Position = DissolutionThread->DeletedAtom;
    if(DissolutionThread->Finish)
    {
     Max = Position;
    }
	if((StatStopPanel->Caption == "Pause") == (DissolutionThread->Suspended))
    {
     StatStopPanelClick(Sender);
     Repaint();
    }
    //N1Label->Caption = "Число односвязных атомов: " + IntToStr(DissolutionThread->Sample->N1);
    //N2Label->Caption = "Число двусвязных атомов: " + IntToStr(DissolutionThread->Sample->N2);
    //N3Label->Caption = "Число трёхсвязных атомов: " + IntToStr(DissolutionThread->Sample->N3);

    //StatusBar1->Repaint();
    DrowProgress();
	fTimerEvent = true;


    if(DissolutionThread->Plane == DissolutionThread->DeletedAtom
    && DissolutionThread->Finish == true
    && SSD.m_nCaptureCode != 0
      )
    {
     //послать сообщение
     PostMessage(Handle,WM_CAPTUREVIDEO,1,0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrowProgress(void)
{
    static int oldPosition = Min-1,oldMin = Min,oldMax = Max;

    if((oldPosition != Position)||(oldMin != Min)||(oldMax != Max))
    {
     TRect r , PRect;
     AnsiString S;
     r = StatusRect;
     PRect = r;
     if((Max-Min) <= 0) S = "100.0 %" ;
     else
     {
       double dKeff = ((double)(Position-Min))/((double)(Max-Min));
       double dRight = (double)PRect.Left + ((double)(PRect.Right-PRect.Left))*dKeff;
       PRect.Right = (int)dRight;
       //PRect.Right = PRect.Left + (Position-Min)*(PRect.Right-PRect.Left)/(Max-Min);
       S = AnsiString((Position-Min)*100/(Max-Min)) + " %";
      //StatusBar1->Canvas->Rectangle(r.Left, r.Top, r.Right, r.Bottom);
     }
     StatusBar1->Canvas->Brush->Color = clRed;
	 StatusBar1->Canvas->Brush->Color = clLime;
     StatusBar1->Canvas->FillRect(PRect);
     PRect.Left = PRect.Right+1;
     PRect.Right = r.Right;
	 StatusBar1->Canvas->Brush->Color = clWhite;
     StatusBar1->Canvas->FillRect(PRect);
     StatusBar1->Canvas->Brush->Style = bsClear;
     StatusBar1->Canvas->TextOut(r.Left + (r.Right-r.Left)/2 - StatusBar1->Canvas->TextWidth(S)/2, //X
      							 r.Top + (r.Bottom-r.Top)/2 - StatusBar1->Canvas->TextHeight(S)/2, //Y
                                 S);
     StatusBar1->Canvas->Brush->Style = bsSolid;
	 StatusBar1->Canvas->Brush->Color = clBlack;
     StatusBar1->Canvas->FrameRect(r);

     oldPosition = Position;
    }
    if(DissolutionThread != NULL)
    {
     StatusBar1->Panels->Items[1]->Text = "Число удалённых атомов: " + IntToStr(Position);
     if(DissolutionThread->Suspended ||DissolutionThread->Finish) StatusBar1->Panels->Items[0]->Text = DissolutionTime.TimeString();
     //else StatusBar1->Panels->Items[0]->Text = (DissolutionTime.CurrentDateTime() - DissolutionThread->StartTime).TimeString();
     else StatusBar1->Panels->Items[0]->Text = (DissolutionTime = DissolutionTime.CurrentDateTime() - DissolutionThread->StartTime - PauseTime).TimeString();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StatStopPanelMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	StatStopPanel->BevelInner = bvLowered;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StatStopPanelMouseUp(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	StatStopPanel->BevelInner = bvRaised;
	//StatStopPanelClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MonitoringSpeedButtonClick(TObject *Sender)
{
	MonitoringForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StopPanelMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	StopPanel->BevelInner = bvLowered;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StopPanelMouseUp(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	StopPanel->BevelInner = bvRaised;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StopPanelClick(TObject *Sender)
{
    StatStopPanel->Caption = "Start";
    StatStopPanel->Enabled = false;
    StatPauseLabel->Enabled = StatStopPanel->Enabled;
    StatPauseLabel->Caption = StatStopPanel->Caption;
    StatPauseLabel->Repaint();
    ChangeSpeedButton->Caption = "Параметры";
	DissolutionParamsSet = false;
    StatStopPanel->Enabled = DissolutionParamsSet;
    if(DissolutionThread != NULL)
    {
     Timer->Enabled = false;
     //ChangeSpeedButton->Enabled = false;

     DissolutionThread->EnterCS();
     DissolutionThread->Terminate();
     DissolutionThread->LeaveCS();
     
     DissolutionThread->Suspended = false;
     DissolutionThread->WaitFor();
     DissolutionThread = NULL;
  	 //delete DissolutionThread;
    }
    DelComboBox->Items->Clear();
    DelComboBox->Text = "Пусто.";
    HoldComboBox->Items->Clear();
    HoldComboBox->Text = "Пусто.";
    DefaultMask = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AppOnIdle(TObject *Sender,bool &R)
{
    if(Initialiseded)
    {
 	 if(EnabledPaint) FormPaint(Sender);//Repaint();
     if( Keys->PressingKeyCount !=0) R = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Display(void)
{
    LstTm = LstTm.CurrentDateTime();

    GLfloat ProjectionMatrix[4][4], *pMatix;
    pMatix = (GLfloat*)ProjectionMatrix;

	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //AnalisateKey();

	//вращаемся вокруг локальных осей Y, X, Z
    glRotated(AlphaT, 0,1,0);
    glRotated(BetaT, 1,0,0);
    glRotated(GammaT, 0,0,1);
    //вращаемся вокруг мировых осей Y, X, Z
    if((AlphaG != 0)||(BetaG != 0)||(GammaG != 0)) RotateAroundWoldAxises(AlphaG, BetaG, GammaG);

    //рисуем оси
	DisplayAxis(AxisX,AxisY,AxisZ);

	bool AnaliseitView = AnalizViewSpeedButton->Down;//затенения обрезки
	bool LeftNormal = LeftRightSpeedButton->Down;
	bool ShowClipPlane = ShowClipPlaneSpeedButton->Down;
	bool AtomPriview = DelHoldSpeedButton->Down;//режим удаления атомов

    if(AnaliseitView)
    {
     if(ShowClipPlane)
     {
	  //ProjectionMatrix[0][1],ProjectionMatrix[1][1],ProjectionMatrix[2][1]);
 	  glPushMatrix();
	   glLoadIdentity();//переходим в глобальные координаты
       GLdouble Len = YPort*Scale;
       glBegin(GL_LINES);
       float color[4];// = {1, 1, 1, 0.1};
       color[0]=1; color[1]=1; color[2]=0; color[3]=1;
       glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
       glVertex3d(0,-Len,0);
       glVertex3d(0, Len,0);
       color[0]=0; color[1]=0; color[2]=0; color[3]=1;
       glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
       glEnd();
 	  glPopMatrix();
     }
    }
    // сохраняем старое положение сцены
 	glPushMatrix();
     glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);
     glGetFloatv(GL_MODELVIEW_MATRIX, pMVM);
     //InfoForm->AddModelViewMatrix(pMatix);
     //glScalef(Scale,Scale,Scale);
     glTranslated(SpeedXT + CenterXT,
                  SpeedYT + CenterYT,
                  SpeedZT + CenterZT);

     glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);
     //InfoForm->AddProjectionMatrix(pMatix);


     GLfloat PM00 = ProjectionMatrix[0][0];
     GLfloat PM10 = ProjectionMatrix[1][0];
     GLfloat PM20 = ProjectionMatrix[2][0];
     GLfloat PM30 = ProjectionMatrix[3][0];
     if(LeftNormal)
     {
      PM00 = -PM00;
      PM10 = -PM10;
      PM20 = -PM20;
      PM30 = -PM30;
     }
     if(SurfaceMode == true)
     {
      DisplaySurface();// функция рисования поверхности
     }
     else
     //{}
      if(IsListGen || IsSurfaceGen == true)
      {
       if(1/Scale < 1)
       {
        glLineWidth(2.0  * 1/Scale);
        glPointSize(20.0 * AtomFromScale(1/Scale));
       }
       else glPointSize(20.0 * AtomFromScale(0.5));
       //begin
       {
        int i,j,k;
        Zmax = Zmin = 0;
        for(k=0; k < 3; k++ )
        {
         TmpMax = ModelViewMatrix[k][2]*MaxTopLeftUP.Coord[k];
         TmpMin = ModelViewMatrix[k][2]*MinTopLeftUP.Coord[k];
         if(TmpMax > TmpMin)
         {
          Zmax += TmpMax;
          Zmin += TmpMin;
         }
         else
         {
          Zmax += TmpMin;
          Zmin += TmpMax;
         }
        }
        TAtom3d *A3d;
        glColor3d(0,0,0);

        if(Points == false)
        {
 	     // создаем новый объект
         // для создания сфер и цилиндров
         quadObj = gluNewQuadric();
        }
        else
        {
         glBegin(GL_POINTS);
        }

        GLfloat r,g,b,HideR,HideG,HideB;
        if(AtomPriview)
        {
         if(SelAtom.Type != 0)
         {
          //HideR = 0.5;
          //HideG = 1.0;
          //HideB = 1.0;
          ColorAtom[0] = 0.5;
          ColorAtom[1] = 1.0;
          ColorAtom[2] = 1.0;
          ColorAtom[3] = 1;
          DrowColorAtom(SelAtom.Coord[0],SelAtom.Coord[1],-SelAtom.Coord[2],ColorAtom[0],ColorAtom[1],ColorAtom[2], false);
          /*
          if(Points == false)
          {
      	   glColor3f(ColorAtom[0],ColorAtom[1],ColorAtom[2]);
           glPushMatrix();
      	    glTranslatef(SelAtom.Coord[0],SelAtom.Coord[1],-SelAtom.Coord[2]);
            gluSphere(quadObj, 1*AtomSize, Qality, Qality); // рисуем сферу
      	   glPopMatrix();
          }
          else
          {
           glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
           glVertex3i(SelAtom.Coord[0],SelAtom.Coord[1],-SelAtom.Coord[2]);
          }
          */
         }
        }
		bool bDrow;
		for(j = 0; j < NumberAtoms; j++)
		{
		 if(j%100 == 0 )
		  j = j;
		 A3d = (TAtom3d*)(Atoms+j);
		 GetColorFromAtomType(A3d->Type,r,g,b);
		 bDrow = true;

		 if(AtomPriview)
		 {
		  if(((A3d->Type & SELECT_MASK_GROUPE) == SELECT_MASK_GROUPE))
		  {
		   r = SelectTypeColorR;
		   g = SelectTypeColorG;
		   b = SelectTypeColorB;
		  }
		  if((A3d->Type & SELECT_MASK_SELECT) == SELECT_MASK_SELECT)
		  {
			if(r>0.5) HideR = r-0.5;
			else HideR = 1;
			if(g>0.5) HideG = g-0.5;
			else HideG = 1;
			if(b>0.5) HideB = b-0.5;
			else HideB = 1;

			r = HideR;
			g = HideG;
			b = HideB;
		  }
		 }

		 if(AnaliseitView)
		 {
		  if((A3d->Type & SELECT_MASK_INVISIBLE) == 0)//  1 - невидим, 0 - видм
		  {
		   if(ShowClipPlane)
		   {
			if((PM00*A3d->Coord[0] + PM10*A3d->Coord[1] - PM20*A3d->Coord[2] + PM30)>0)
			{//атом в затененной области
			  r *= AtomsClipPlaneBrigthness;//0.85
			  g *= AtomsClipPlaneBrigthness;
			  b *= AtomsClipPlaneBrigthness;
			}
		   }
		  }
		  else
		  {
		   bDrow = false;
		  }

		 }
		 if(bDrow == true)
		 {
		   DrowColorAtom(A3d->Coord[0],A3d->Coord[1],-A3d->Coord[2],r,g,b);
		 }


		 /*
		 if(AnaliseitView)
		 {
		  if((A3d->Type & SELECT_MASK_INVISIBLE) == 0)//  1 - невидим, 0 - видм
		  {
		   HideR = r;
		   HideG = g;
		   HideB = b;
		   if(ShowClipPlane)
		   {
			if((PM00*A3d->Coord[0] + PM10*A3d->Coord[1] - PM20*A3d->Coord[2] + PM30)>0)
			{//атом в затененной области
			  HideR = AtomsClipPlaneBrigthness*(HideR);//0.85
			  HideG = AtomsClipPlaneBrigthness*(HideG);
			  HideB = AtomsClipPlaneBrigthness*(HideB);
			}
		   }
		   //рисуем атом
		   DrowColorAtom(A3d->Coord[0],A3d->Coord[1],-A3d->Coord[2],HideR,HideG,HideB);
		  }
		 }
		 else
		 {
		  if(AtomPriview)
		  {
		   if((A3d->Type & SELECT_MASK_SELECT) == SELECT_MASK_SELECT)
		   {
			//HideR = 0.5;
			//HideG = 1.5;
			//HideB = 0.5;
			if(r>0.5) HideR = r-0.5;
			else HideR = 1;
			if(g>0.5) HideG = g-0.5;
			else HideG = 1;
			if(b>0.5) HideB = b-0.5;
			else HideB = 1;
			DrowColorAtom(A3d->Coord[0],A3d->Coord[1],-A3d->Coord[2],HideR,HideG,HideB);
		   }
		   else
		   {
			if(((A3d->Type & SELECT_MASK_GROUPE) == SELECT_MASK_GROUPE))
			 DrowColorAtom(A3d->Coord[0],A3d->Coord[1],-A3d->Coord[2],SelectTypeColorR,SelectTypeColorG,SelectTypeColorB);
			else
			 DrowColorAtom(A3d->Coord[0],A3d->Coord[1],-A3d->Coord[2],r,g,b);
		   }
		  }
		  else
		   DrowColorAtom(A3d->Coord[0],A3d->Coord[1],-A3d->Coord[2],r,g,b);
		 }
		 */


		}

        if(Points == false)
        {
         gluDeleteQuadric(quadObj);
        }
        else
        {
         glEnd();
        }
        if(IsLinksVisibled == true)
        {
         bool bCylinders = Points;
         if(bCylinders == false)
         {
   	      // создаем новый объект
          // для создания сфер и цилиндров
          quadObj = gluNewQuadric();
         }
         else
         {
          glBegin(GL_LINES);
         }

         //GLint xb,yb,zb,xe,ye,ze;
         GLint CoordBegin[3], CoordEnd[3];

         GLfloat rb,gb,bb;
         GLfloat re,ge,be;

         for(j = 0; j < NumberLinksFromAtoms; j++)
         {
          for(k = 0; k < 3; k++)
          {
           CoordBegin[k] = LinksFromAtoms[0][j].Coord[k];
           CoordEnd[k] = LinksFromAtoms[1][j].Coord[k];
          }

          if(
             CoordBegin[0]==12
          && CoordBegin[1]==10
          && CoordBegin[2]==2
            )
          {
           CoordBegin[0] = CoordBegin[0];

          }
		  GetColorLinkFromAtomType(LinksFromAtoms[0][j].Type, LinksFromAtoms[1][j].Type, r,g,b);

		  GetColorFromAtomType(LinksFromAtoms[0][j].Type,rb,gb,bb);
		  GetColorFromAtomType(LinksFromAtoms[1][j].Type,re,ge,be);

          if(AnaliseitView)
          {
		   //  1 - невидим, 0 - видм
		   if(
			 ((LinksFromAtoms[0][j].Type & SELECT_MASK_INVISIBLE) == 0 && (LinksFromAtoms[0][j].Type & SELECT_MASK_TYPE) > 0 )
		   ||((LinksFromAtoms[1][j].Type & SELECT_MASK_INVISIBLE) == 0 && (LinksFromAtoms[1][j].Type & SELECT_MASK_TYPE) > 0 )
             )
           {
            HideR = r;
            HideG = g;
            HideB = b;
            if(ShowClipPlane)
            {
             if((PM00*CoordBegin[0] + PM10*CoordBegin[1] - PM20*CoordBegin[2] + PM30)>0)
             {
              HideR = AtomsClipPlaneBrigthness*(HideR);//0.85
              HideG = AtomsClipPlaneBrigthness*(HideG);
              HideB = AtomsClipPlaneBrigthness*(HideB);
			  rb *= AtomsClipPlaneBrigthness;
			  gb *= AtomsClipPlaneBrigthness;
			  bb *= AtomsClipPlaneBrigthness;
			  re *= AtomsClipPlaneBrigthness;
              ge *= AtomsClipPlaneBrigthness;
              be *= AtomsClipPlaneBrigthness;
              DrowColorLink(CoordBegin[0],CoordBegin[1],-CoordBegin[2],
							CoordEnd[0],  CoordEnd[1],  -CoordEnd[2],HideR,HideG,HideB,rb,gb,bb,re,ge,be);
             }
             else
              DrowColorLink(CoordBegin[0],CoordBegin[1],-CoordBegin[2],
           	 	 		    CoordEnd[0],  CoordEnd[1],  -CoordEnd[2],HideR,HideG,HideB,rb,gb,bb,re,ge,be);
            }
            else
             DrowColorLink(CoordBegin[0],CoordBegin[1],-CoordBegin[2],
          	 	 		   CoordEnd[0],  CoordEnd[1],  -CoordEnd[2],HideR,HideG,HideB,rb,gb,bb,re,ge,be);
           }
          }
          else
		   DrowColorLink(CoordBegin[0],CoordBegin[1],-CoordBegin[2],
						 CoordEnd[0],  CoordEnd[1],  -CoordEnd[2],r,g,b,rb,gb,bb,re,ge,be);
         }

         if(bCylinders == false)
         {
          gluDeleteQuadric(quadObj);
         }
         else
         {
          glEnd();
         }
        }
        glLineWidth(2.0);
        glPointSize(10.0);
       }
      }
      else SnowMan();
	  //возвращаем координату на место
 	  glPopMatrix();

    if(PrintIndex == true)
    {
     //рисование индексов миилера
	 glPushMatrix();
      GLfloat color[4];
      color[0]=1; color[1]=1; color[2]=1; color[3]=1;
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
      glColor3d(1.0,1.0,1.0);
      glLoadIdentity();
      //glTranslated(0,1,0);
	  //glRasterPos2f(-XPort*Scale,-YPort*Scale*0.98);
      glRasterPos3f(
        -XPort*Scale*0.99,-YPort*Scale*0.98,        Far/2.0-Near        );
      //glColor4ub(255,255,255,255);
      //glColor3f(1.0f,1.0f,1.0f);
      //glBegin(GL_TRIANGLES);

      // now draw the characters in a string
      //glCallLists (24, GL_UNSIGNED_BYTE, "Hello Win32 OpenGL World");
	  glCallLists (MillersIndexesLabel->Caption.Length(), GL_UNSIGNED_BYTE, _c_str(MillersIndexesLabel->Caption));
	  //glEnd();
      //устанавливаем цвет по умолчанию
      color[0]=0; color[1]=0; color[2]=0; color[3]=1;
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
     glPopMatrix();
    }



    double dt = (double)(LstTm.CurrentDateTime() - LstTm);
    double fps;
    if(dt > 10e-6)
    {
     fps = floor((100*(1/((dt)*86400.0)))+0.5)/100;
     if(fps!=0)
      PaintCntLabel->Caption="PaintCnt = " + IntToStr(++PaintCnt)
    								+ "; fps: " + AnsiString((float)fps)
    								+ "; (" + AnsiString(floor((100*(1/fps))+0.5)/100)+" sec)";
    }
    else
    {
     PaintCntLabel->Caption="PaintCnt = error";
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormPaint(TObject *Sender)
{
	//if(Sender == NULL)
	//{
	//    Sender = Sender;
	//}
    if(Initialiseded)
    {
     if(fTimerEvent == false)
     {
	  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	  Display();
	  glFinish();
	  SwapBuffers(wglGetCurrentDC());
     }
     else fTimerEvent = false;
    }
    DrowProgress();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PhotoSpeedButtonClick(TObject *Sender)
{
	if(hGLRC == NULL)
    {
     if(InitGL(GetDC(ScreenPanel->Handle)) == 0)
     	return;
     //FormResize(Sender);

     //SetCamera();
     SetCenter();

     ScreenPanelResize(Sender);
 	 Repaint();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetCamera(void)
{
     glMatrixMode( GL_PROJECTION );
     glLoadIdentity();
     //XPort = YPort

     //glOrtho(-XPort,XPort, -YPort,YPort, Near, Far);
     glOrtho(-XPort*Scale,XPort*Scale, -YPort*Scale,YPort*Scale, Near, Far);
     //glFrustum(-XPort,XPort, -YPort,YPort, Near, Far);

     // EyeX = 0;
	 // EyeY = 0;
	 // EyeZ = 10;
	 // CenterX = 0;
	 // CenterY = 0;
	 // CenterZ = 0;
	 // UpX = 0;
	 // UpY = -1;
	 // UpZ = 0;

     //UpX = UpX*cos(Roll) + UpY*sin(Roll);
     //UpY = UpX*sin(Roll) + UpY*cos(Roll);

     //UpX = sin(Roll);
     //UpY = cos(Roll);
     UpX = EyeX - CenterX;
     UpY = EyeY - CenterY;
	 UpZ = EyeZ - CenterZ;

	 DirectAlongZ(UpX,UpY,UpZ);

   	 gluLookAt( EyeX,EyeY,EyeZ, CenterX,CenterY,CenterZ, UpX,UpY,UpZ );
     //glRotated(RollZ,0,0,1);
     //glRotated(RollY,0,1,0);
     //glRotated(RollX,1,0,0);

   	 glMatrixMode( GL_MODELVIEW );
     //N1Label->Caption = "UpX: " + AnsiString(UpX);
     //N2Label->Caption = "UpX: " + AnsiString(UpY);
     //N3Label->Caption = "UpZ: " + AnsiString(UpZ);
     N1Label->Caption = "EyeX: " + AnsiString(EyeX) + "; CenterX: " + AnsiString(CenterX);
     N2Label->Caption = "EyeY: " + AnsiString(EyeY) + "; CenterY: " + AnsiString(CenterY);
     N3Label->Caption = "EyeZ: " + AnsiString(EyeZ) + "; CenterZ: " + AnsiString(CenterZ);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
    if(Initialiseded)
    {
     ExitGL();
    }
	/*if(hGLRC != NULL)
    {
     ExitGL();
    }
	*/
    delete Keys;
    delete ExperimentProperty;

    if(pQuantityByGroupeForm != NULL)
    {
     delete pQuantityByGroupeForm;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ScreenPanelResize(TObject *Sender)
{
	static OldW = 0, OldH = 0;
    if(Initialiseded)
    {
     //ExitGL();
     //if(InitGL(GetDC(ScreenPanel->Handle)) == 0)
     //	return;

     int w, h;
     w = ScreenPanel->ClientWidth;
     h = ScreenPanel->ClientHeight;
     GLdouble MaxWH = min(w,h);
     GLdouble MaxOWH  = min(OldW,OldH);

     glViewport(0,0,w,h);

     //if((OldW != 0) && (OldH != 0)) glScalef(oldW/(float)(oldW<oldH?oldW:oldH),oldH/(float)(oldW<oldH?oldW:oldH),1);
     //glScalef((w<h?w:h)/(float)w,(w<h?w:h)/(float)h,1);

     if((OldW != 0) && (OldH != 0))
     {
      //XPort = OldW/(float)(OldW<OldH?OldW:OldH);
      //YPort = OldH/(float)(OldW<OldH?OldW:OldH);
      XPort *= MaxOWH/(float)OldW;
      YPort *= MaxOWH/(float)OldH;
     }
     //XPort = (w<h?w:h)/(float)w;
     //YPort = (w<h?w:h)/(float)h;
     XPort *= w/MaxWH;
     YPort *= h/MaxWH;

     OldW = w;
     OldH = h;

     SetCamera();
	 //Resize(w, h);

	 //ResizeGL(ScreenPanel->ClientWidth, ScreenPanel->ClientHeight);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
 	ShiftState = Shift;
	switch(Key)
    {
     //повороты (локальные оси)
     case 65://'a' 0x41
      AlphaT = -AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 68://'d' 0x44
      AlphaT = AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 87://'w' 0x57
      BetaT = -BetaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 83://'s' 0x53
      BetaT = BetaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 81://'q' 0x51
      GammaT = GammaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 69://'e' 0x45
      GammaT = -GammaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;

     //повороты (мировые оси)
     case 71://'g' 0x47
      AlphaG = -AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 86://'v' 0x56
      AlphaG = AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 67://'c' 0x43
      BetaG = -BetaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 66://'b' 0x42
      BetaG = BetaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 70://'f' 0x46
      GammaG = GammaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;
     case 72://'h' 0x48
      GammaG = -GammaW*ShiftSpeed(ShiftState)*MultiAngle;
     break;

     //перемещения
     case 76://'д' 0x4C
      SpeedXT += SpeedXW*ShiftSpeed(ShiftState)*MultiSpeed;
     break;
     case 188://'б' 0xBC
      SpeedXT += -SpeedXW*ShiftSpeed(ShiftState)*MultiSpeed;
     break;
     case 186://'ж' 0xBA
      SpeedYT += SpeedYW*ShiftSpeed(ShiftState)*MultiSpeed;
     break;
     case 190://'ю' 0xBE
      SpeedYT += -SpeedYW*ShiftSpeed(ShiftState)*MultiSpeed;
     break;
     case 222://'э' 0xDE
      SpeedZT += SpeedZW*ShiftSpeed(ShiftState)*MultiSpeed;
     break;
     case 191://',' 0xBF
      SpeedZT += -SpeedZW*ShiftSpeed(ShiftState)*MultiSpeed;
     break;
     case 88://'x' 0x58
      AxisX = !AxisX;
      AxisCheckBox->Checked = AxisX||AxisY||AxisZ;
     break;
     case 89://'x' 0x59
      AxisY = !AxisY;
      AxisCheckBox->Checked = AxisX||AxisY||AxisZ;
     break;
     case 90://'x' 0x5A
      AxisZ = !AxisZ;
      AxisCheckBox->Checked = AxisX||AxisY||AxisZ;
     break;
     case 8://'Backspace' 0x8
      SetCenter();
     break;
     case 79://'o' 0x4F
     case 189://'-' 0xBD
     case 109://'-' Numpad
      OUTSpeedButtonClick(NULL);
     break;
     case 73://'i' 0x49
     case 187://'+' 0xBB
     case 107://'+' Numpad
      INSpeedButtonClick(NULL);
     break;
     case VK_DELETE:
      if((SaveOrientationComboBox->ItemIndex > 0)
      		&&(SaveOrientationComboBox->DroppedDown))
      {
       GLfloat *pMatix;
       pMatix = (GLfloat *)SaveOrientationComboBox->Items->Objects[SaveOrientationComboBox->ItemIndex];
       delete pMatix;
       //if(Key == VK_DELETE)
       SaveOrientationComboBox->Items->Delete(SaveOrientationComboBox->ItemIndex);
      }
      else Keys->PressKey(Key,Shift);
     break;
     case VK_F11:
      //MultiAngle *= 2;
      //MulAngleLabel->Caption = "Угол x " + AnsiString(MultiAngle);//"Angle •" + AnsiString(MultiAngle);
      AngleUpSpeedButtonClick(Sender);
     break;
     case VK_F12:
      //MultiAngle /= 2;
      //MulAngleLabel->Caption = "Угол x " + AnsiString(MultiAngle);//"Angle •" + AnsiString(MultiAngle);
      AngleDownSpeedButtonClick(Sender);
     break;
     case VK_F9:
      //MultiSpeed *= 2;
      //MulSpeedLabel->Caption = "Шаг x " + AnsiString(MultiSpeed);//"Move •" + AnsiString(MultiSpeed);
      StepUpSpeedButtonClick(Sender);
     break;
     case VK_F10:
      //MultiSpeed /= 2;
      //MulSpeedLabel->Caption = "Шаг x " + AnsiString(MultiSpeed);//"Move •" + AnsiString(MultiSpeed);
      StepDownSpeedButtonClick(Sender);
     break;
     case 80:////'P' 0x50
	  IsLinksVisibled = !IsLinksVisibled;
      LinksCheckBox->Checked = IsLinksVisibled;
     break;
     case VK_F8://скриншот
      CopySpeedButtonClick(Sender);
     break;

     default:
	  Keys->PressKey(Key,Shift);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	switch(Key)
    {
     //повороты (локальные оси)
     case 65://'a' 0x41
     case 68://'d' 0x44
      AlphaT = 0;
     break;
     case 87://'w' 0x57
     case 83://'s' 0x53
      BetaT = 0;
     break;
     case 81://'q' 0x51
     case 69://'e' 0x45
      GammaT = 0;
     break;

     //повороты (мировые оси)
     case 71://'g' 0x47
     case 86://'v' 0x56
      AlphaG = 0;
     break;
     case 67://'c' 0x43
     case 66://'b' 0x42
      BetaG = 0;
     break;
     case 70://'f' 0x46
     case 72://'h' 0x48
      GammaG = 0;
     break;

     //перемещения
     /*case 76://'д' 0x4C
     case 188://'б' 0xBC
      SpeedXT = 0;
     break;
     case 186://'ж' 0xBA
     case 190://'ю' 0xBE
      SpeedYT = 0;
     break;
     case 222://'э' 0xDE
     case 191://',' 0xBF
      SpeedZT = 0;
     break;
     */
     default:
	  Keys->UnPressKey(Key,Shift);
    }
 	ShiftState = Shift;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AnalisateKey(void)
{
    TKeyState *Kl;
    TDateTime Curr;
	GLdouble XR, YPhi, ZTeta;
	GLdouble X, Y, Z;
    GLdouble dX,dY,dPhi,dTeta;
    //double Time;

    Curr = Curr.CurrentDateTime();
    //SpeedBeta;
    //SpeedAlpha;
	for(int i = 0; i < Keys->PressingKeyCount; i++)
    {
     Kl = Keys->Key[i];
     //Time = ((double)(Curr - Kl->TimePress))*86400.0;
     //Time = 0.1;
     switch(Kl->Key)
     {
      case 'A'://VK_LEFT:
       Alpha += ShiftSpeed(ShiftState)*SpeedAlpha*((double)(Curr - Kl->TimePress));
       //Label2->Caption="Curr - TimePress == " + AnsiString(SpeedAlpha*((double)(Curr - Kl->TimePress)));
       Kl->TimePress = Curr;
      break;
      case 'D'://VK_RIGHT:
       Alpha -= ShiftSpeed(ShiftState)*SpeedAlpha*((double)(Curr - Kl->TimePress));
       Kl->TimePress = Curr;
      break;
      case 'W'://VK_UP:
       Beta += ShiftSpeed(ShiftState)*SpeedBeta*((double)(Curr - Kl->TimePress));
       Kl->TimePress = Curr;
      break;
      case 'S'://VK_DOWN:
       Beta -= ShiftSpeed(ShiftState)*SpeedBeta*((double)(Curr - Kl->TimePress));
       Kl->TimePress = Curr;
      break;
/*      case VK_RIGHT:
       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       DirectAlongX(X, Y, Z);
       MoveDirection(X, Y, Z, +ShiftSpeed(ShiftState)*Time*StepDem);
       CenterX += X;
       CenterY += Y;
       CenterZ += Z;
       EyeX += X;
       EyeY += Y;
       EyeZ += Z;
       SetCamera();
       Kl->TimePress = Curr;
      break;
      case VK_LEFT:
       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       DirectAlongX(X, Y, Z);
       MoveDirection(X, Y, Z, -ShiftSpeed(ShiftState)*Time*StepDem);
       CenterX += X;
       CenterY += Y;
       CenterZ += Z;
       EyeX += X;
       EyeY += Y;
       EyeZ += Z;

       SetCamera();
       Kl->TimePress = Curr;
      break;
      case VK_DOWN:
       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       DirectAlongZ(X, Y, Z);
       MoveDirection(X, Y, Z, ShiftSpeed(ShiftState)*Time*StepDem);
       CenterX += X;
       CenterY += Y;
       CenterZ += Z;
       EyeX += X;
       EyeY += Y;
       EyeZ += Z;

       SetCamera();
       Kl->TimePress = Curr;
      break;
      case VK_UP:
       X = CenterX - EyeX;
       Y = CenterY - EyeY;
       Z = CenterZ - EyeZ;
       DirectAlongZ(X, Y, Z);
       MoveDirection(X, Y, Z, -ShiftSpeed(ShiftState)*Time*StepDem);
       CenterX += X;
       CenterY += Y;
       CenterZ += Z;
       EyeX += X;
       EyeY += Y;
       EyeZ += Z;

       SetCamera();
       Kl->TimePress = Curr;
      break;
      case VK_NUMPAD4:
       UpX +=0.2;
       SetCamera();
      break;
      case VK_NUMPAD5:
       UpY +=0.2;
       SetCamera();
      break;
      case VK_NUMPAD6:
       UpZ +=0.2;
       SetCamera();
      break;
      case VK_NUMPAD1:
       UpX -=0.2;
       SetCamera();
      break;
      case VK_NUMPAD2:
       UpY -=0.2;
       SetCamera();
      break;
      case 219://0xdb '['
      //case VK_PRIOR://VK_PGUP:
       Roll -=ShiftSpeed(ShiftState)*0.2;
       SetCamera();
      break;
      case 221://0xdd ']'
      //case VK_NEXT://VK_PAGEDOWN:
       Roll +=ShiftSpeed(ShiftState)*0.2;
       SetCamera();
       Kl->TimePress = Curr;
      break;
      case VK_HOME:
	   //GLdouble XR, YPhi, ZTeta;

       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       //RotationAroundX(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble Angle)
       RotationAroundX(X, Y, Z, ShiftSpeed(ShiftState)*Time*dRoll);
       CenterX = EyeX - X;
       CenterY = EyeY - Y;
       CenterZ = EyeZ - Z;

       SetCamera();
       Kl->TimePress = Curr;
      break;
      case VK_END:
	   //GLdouble XR, YPhi, ZTeta;
       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       //RotationAroundX(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble Angle)
       RotationAroundX(X, Y, Z, -ShiftSpeed(ShiftState)*Time*dRoll);
       CenterX = EyeX - X;
       CenterY = EyeY - Y;
       CenterZ = EyeZ - Z;

       SetCamera();
       Kl->TimePress = Curr;
      break;
      case VK_NEXT://VK_PAGEDOWN:
      //case VK_INSERT://VK_INSERT         0x2D
       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       //RotationAroundX(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble Angle)
       RotationAroundY(X, Y, Z, ShiftSpeed(ShiftState)*Time*dRoll);
       CenterX = EyeX - X;
       CenterY = EyeY - Y;
       CenterZ = EyeZ - Z;

       SetCamera();
       Kl->TimePress = Curr;
      break;
      case VK_DELETE://VK_DELETE         0x2E
       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       //RotationAroundX(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble Angle)
       RotationAroundY(X, Y, Z, -ShiftSpeed(ShiftState)*Time*dRoll);
       CenterX = EyeX - X;
       CenterY = EyeY - Y;
       CenterZ = EyeZ - Z;

       SetCamera();
       Kl->TimePress = Curr;
      break;
      //case 219://0xdb '['
      case VK_INSERT://VK_INSERT         0x2D
       //MoveDirection(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble DemitionValue)
       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       MoveDirection(X, Y, Z, ShiftSpeed(ShiftState)*Time*dDirection);
       CenterX += X;
       CenterY += Y;
       CenterZ += Z;
       EyeX += X;
       EyeY += Y;
       EyeZ += Z;
       SetCamera();
       Kl->TimePress = Curr;
      break;
      //case 221://0xdd ']'
      case VK_PRIOR://VK_PGUP:
       //MoveDirection(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble DemitionValue)
       X = EyeX - CenterX;
       Y = EyeY - CenterY;
       Z = EyeZ - CenterZ;
       MoveDirection(X, Y, Z, -ShiftSpeed(ShiftState)*Time*dDirection);
       CenterX += X;
       CenterY += Y;
       CenterZ += Z;
       EyeX += X;
       EyeY += Y;
       EyeZ += Z;
       SetCamera();
       Kl->TimePress = Curr;
      break;
      case 'P'://вверх
       RollX += dRoll;
       SetCamera();
      break;
      case 186://вниз ':' (0xba)
       RollX -= dRoll;
       SetCamera();
      break;
      case 'L'://влево
       RollY += dRoll;
       SetCamera();
      break;
      case 222://вправо '"' (0xde)
       RollY -= dRoll;
       SetCamera();
      break;
*/     }
    }
}
//---------------------------------------------------------------------------
float __fastcall TMainForm::ShiftSpeed(TShiftState Shift)
{
    float f = 1.0;
    //ssShift, ssAlt, ssCtrl, ssLeft, ssRight
    if(Shift.Contains(ssShift)) f *=5;
    if(Shift.Contains(ssAlt)) f *=5;
    if(Shift.Contains(ssCtrl)) f /=2;

    //if(Shift.Contains(ssShift) & Shift.Contains(ssLeft)) f /=2;
    //if(Shift.Contains(ssAlt)   & Shift.Contains(ssLeft)) f /=5;
    //if(Shift.Contains(ssCtrl)  & Shift.Contains(ssLeft)) f /=10;

    //if(Shift.Contains(ssShift) & Shift.Contains(ssRight)) f *=2;
    //if(Shift.Contains(ssAlt)   & Shift.Contains(ssRight)) f *=5;
    //if(Shift.Contains(ssCtrl)  & Shift.Contains(ssRight)) f *=10;

	return f;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyPress(TObject *Sender, char &Key)
{
    GLboolean bEnabled;
	switch(Key)
    {
     case '1':
       glGetBooleanv(GL_LIGHT0,&bEnabled);
       if(bEnabled) glDisable(GL_LIGHT0);
       else glEnable(GL_LIGHT0);
     break;
     case '2':
       glGetBooleanv(GL_LIGHT1,&bEnabled);
       if(bEnabled) glDisable(GL_LIGHT1);
       else glEnable(GL_LIGHT1);
     break;
     case '3':
       glGetBooleanv(GL_LIGHT2,&bEnabled);
       if(bEnabled) glDisable(GL_LIGHT2);
       else glEnable(GL_LIGHT2);
     break;
     case '4':
       glGetBooleanv(GL_LIGHT3,&bEnabled);
       if(bEnabled) glDisable(GL_LIGHT3);
       else glEnable(GL_LIGHT3);
     break;
     case '5':
       glGetBooleanv(GL_LIGHT4,&bEnabled);
       if(bEnabled) glDisable(GL_LIGHT4);
       else glEnable(GL_LIGHT4);
     break;
     case '6':
       glGetBooleanv(GL_LIGHT5,&bEnabled);
       if(bEnabled) glDisable(GL_LIGHT5);
       else glEnable(GL_LIGHT5);
     break;
     case '7':
       glGetBooleanv(GL_LIGHT6,&bEnabled);
       if(bEnabled) glDisable(GL_LIGHT6);
       else glEnable(GL_LIGHT6);
     break;
     //case '-':
       //if(!(IsListGen || IsSurfaceGen))
       //glScalef(1/ScaleStep,1/ScaleStep,1/ScaleStep);
     //break;
     //case '+':
       //if(!(IsListGen || IsSurfaceGen))
       //glScalef(ScaleStep,ScaleStep,ScaleStep);
     //break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SurfaceSpeedButtonClick(TObject *Sender)
{
    EnabledPaint = false;

      int i;//,j,k;

      if(Atoms != NULL)
      {
       delete Atoms;
       Atoms = NULL;
      }
      NumberAtoms = 0;
      for(i=0; i < 2; i++ )
      {
       if(LinksFromAtoms[i] != NULL)
       {
        delete LinksFromAtoms[i];
        LinksFromAtoms[i] = NULL;
       }
      }
      NumberLinksFromAtoms = 0;


    if(DissolutionThread == NULL)
	{
	 SurfaceForm->InitForm(ifCube, m_DssParams);
     if(SurfaceForm->ShowModal() == mrOk)
     {
	  SpeedXT = 0;
      SpeedYT = 0;
      SpeedZT = 0;
      //SpeedXT = -((double)m_DssParams.X)*2;
      //SpeedYT = -((double)m_DssParams.Y)*2;
      //SpeedZT = -((double)m_DssParams.Z-1)/2;


      DeletedLabel->Caption = "Куб (X)" + IntToStr((int)m_DssParams.X) + "x(Y)"
                                        + IntToStr((int)m_DssParams.Y) + "x(Z)"
                                        + IntToStr((int)m_DssParams.Z) ;
      //NumberNoDeleteAtoms = GetCubeAtoms(&NoDeleteAtoms);
      //NumberLinksFromNoDeleteAtoms = GetLinksFromCubeAtoms(&LinksFromNoDeleteAtoms[0],&LinksFromNoDeleteAtoms[1]);

      DissolutionThread = new TDissolutionThread(true);
	  DissolutionThread->InitIdealSmoothSurface(m_DssParams.X,
												m_DssParams.Y);

      NumberAtoms = DissolutionThread->GetCubeAtoms(&Atoms, (int)m_DssParams.Z);
	  NumberLinksFromAtoms =  DissolutionThread->GetLinksFromCubeAtoms(&LinksFromAtoms[0], &LinksFromAtoms[1], (int)m_DssParams.Z);
	  //DissolutionThread->InitCube((int)m_DssParams.X,(int)m_DssParams.Y,(int)m_DssParams.Z);
      //NumberNoDeleteAtoms = DissolutionThread->GetMaskedAtoms(&NoDeleteAtoms);
      //NumberLinksFromNoDeleteAtoms = DissolutionThread->GetLinksFromMaskedAtoms(&LinksFromNoDeleteAtoms[0],&LinksFromNoDeleteAtoms[1]);
      DissolutionThread->MaskAll = true;

	  ChangeSpeedButton->Caption = "Изменить";
      DissolutionParamsSet = true;
      StatStopPanel->Enabled = DissolutionParamsSet;
      StatStopPanel->Enabled = true;
      StatPauseLabel->Enabled = StatStopPanel->Enabled;
      StatPauseLabel->Caption = StatStopPanel->Caption;
      StatPauseLabel->Repaint();

      if(DsslExpPrprt == NULL)
      {
       DsslExpPrprt = new TExperimentProperty;
      }
      if(DsslExpPrprt != NULL)
      {
       DsslExpPrprt->W = DissolutionThread->Width;
       DsslExpPrprt->H = DissolutionThread->Height;
       DsslExpPrprt->DelAtoms = DissolutionThread->DeletedAtom;
       DsslExpPrprt->DeletedLayers = DissolutionThread->DeletedLayers;
       if((DsslExpPrprt->DeletingLayers != 0)
       	&&(DsslExpPrprt->Layers != NULL))
          	 delete DsslExpPrprt->Layers;
       DsslExpPrprt->DeletingLayers = DissolutionThread->DeletingLayers;
       DsslExpPrprt->N1 = DissolutionThread->N1;
       DsslExpPrprt->N2 = DissolutionThread->N2;
       DsslExpPrprt->N3 = DissolutionThread->N3;
       DsslExpPrprt->Layers = new int[DsslExpPrprt->DeletingLayers];
       for(i=0; i < DsslExpPrprt->DeletingLayers; i++)
       {
        DsslExpPrprt->Layers[i] =
        	 DissolutionThread->NumOfAtomsInLayer[i+DsslExpPrprt->DeletedLayers];
       }
       DsslExpPrprt->BeginTime = DissolutionThread->StartTime;
       DsslExpPrprt->DissolutionTime = DissolutionTime;
       DsslExpPrprt->EndTime = DissolutionTime.CurrentDateTime();
       DsslExpPrprt->FileName = DsslExpPrprt->EndTime.FormatString("yymmddhhnnss");
	   Caption = PROGNAME_AND_VER + DsslExpPrprt->FileName;
       if((double)DsslExpPrprt->DissolutionTime != 0)
       {
        DsslExpPrprt->AverageSpeed =
         ((double)(DsslExpPrprt->DelAtoms))/((double)(DsslExpPrprt->DissolutionTime)* 86400);
       }
       else DsslExpPrprt->AverageSpeed = -1;
      }

      SetViewParams();
      //SetCenter();

      IsListGen = true;
      IsSurfaceGen = false;
      SurfaceMode = false;
     }
    }
    else
    {
     int i;//,j,k;
     bool bSuspend = DissolutionThread->Suspended;
     DissolutionThread->EnterCS();
     DissolutionThread->Suspended = true;
     DissolutionThread->LeaveCS();

     NumberAtoms = DissolutionThread->GetCubeAtoms(&Atoms);
     NumberLinksFromAtoms =  DissolutionThread->GetLinksFromCubeAtoms(&LinksFromAtoms[0], &LinksFromAtoms[1]);

	 DeletedLabel->Caption = IntToStr((int)DissolutionThread->DeletedAtom);
     if(DsslExpPrprt == NULL)
     {
      DsslExpPrprt = new TExperimentProperty;
     }
     if(DsslExpPrprt != NULL)
     {
      DsslExpPrprt->W = DissolutionThread->Width;
      DsslExpPrprt->H = DissolutionThread->Height;
      DsslExpPrprt->DelAtoms = DissolutionThread->DeletedAtom;
      DsslExpPrprt->DeletedLayers = DissolutionThread->DeletedLayers;
      if((DsslExpPrprt->DeletingLayers != 0)
      	&&(DsslExpPrprt->Layers != NULL))
         	 delete DsslExpPrprt->Layers;
      DsslExpPrprt->DeletingLayers = DissolutionThread->DeletingLayers;
      DsslExpPrprt->N1 = DissolutionThread->N1;
      DsslExpPrprt->N2 = DissolutionThread->N2;
      DsslExpPrprt->N3 = DissolutionThread->N3;
      DsslExpPrprt->Layers = new int[DsslExpPrprt->DeletingLayers];
      for(i=0; i < DsslExpPrprt->DeletingLayers; i++)
      {
       DsslExpPrprt->Layers[i] =
       	 DissolutionThread->NumOfAtomsInLayer[i+DsslExpPrprt->DeletedLayers];
      }
      DissolutionThread->GenAtomCntInLayer(DsslExpPrprt->m_vAtomCntInLayer);
      DsslExpPrprt->BeginTime = DissolutionThread->StartTime;
      DsslExpPrprt->DissolutionTime = DissolutionTime;
      DsslExpPrprt->EndTime = DissolutionTime.CurrentDateTime();
      DsslExpPrprt->FileName = DsslExpPrprt->EndTime.FormatString("yymmddhhnnss");
      Caption = PROGNAME_AND_VER + DsslExpPrprt->FileName;
      if((double)DsslExpPrprt->DissolutionTime != 0)
      {
       DsslExpPrprt->AverageSpeed =
        ((double)(DsslExpPrprt->DelAtoms))/((double)(DsslExpPrprt->DissolutionTime)* 86400);
      }
      else DsslExpPrprt->AverageSpeed = -1;
      SetViewParams();
      ExternExpProp = false;
     }
     DissolutionThread->Suspended = bSuspend;
    }
    //delete m_DssParams;
    EnabledPaint = true;
    FormPaint(Sender);
	return;
    ////////////////////////////////////////////////
    /*if(DissolutionThread != NULL)
    {
     bool fSuspended = DissolutionThread->Suspended;
     DissolutionThread->Suspended = true;

 	 //GLboolean glIsList(GLuint list);
     //for(ListNum = 10; !(glIsList(ListNum)); ListNum++);
     ListNum = 10;
     while( (glIsList(ListNum)))
      ListNum++;
     IsListGen = DissolutionThread->Sample->CreateList(ListNum);
     Repaint();
     //IsListGen = true;
     DissolutionThread->Suspended = fSuspended;
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RectangleToSphere(GLdouble &XR, GLdouble &YPhi,GLdouble &ZTeta)
{
	GLdouble R, Phi, Teta;
    R = sqrt(XR*XR + YPhi*YPhi +ZTeta*ZTeta);
    if(R == 0)
    {
     Phi = Teta = 0;
    }
    else
    {
     /*if(XR = 0) Phi = atan(YPhi/XR);
     else Phi =
     if(ZTeta != 0) Teta = atan((YPhi*YPhi+XR*XR)/ZTeta);
     else Teta = M_PI_2;*/
     Phi = acos(ZTeta/R);
     if(XR == 0)
     {
      Teta = (YPhi>=0)? M_PI_2 :(M_PI + M_PI_2);
     }
     else
     {
      if(XR > 0)
      {
       Teta = atan(YPhi/XR);
      }
      else
      {
       Teta = M_PI + atan(YPhi/XR);
      }
     }
    }
    XR = R;
    YPhi = Phi;
    ZTeta = Teta;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SphereToRectangle(GLdouble &RX, GLdouble &PhiY,GLdouble &TetaZ)
{
	GLdouble X,Y,Z;

    X = RX * sin(PhiY) * cos(TetaZ);
    Y = RX * sin(PhiY) * sin(TetaZ);
    Z = RX * cos(PhiY);

    RX = X;
    PhiY = Y;
    TetaZ = Z;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RotationAroundX(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble Angle)
{
	TPoint3d A,L,VectorX;
    TMatrix RyAteta,RxAphi,RzRoll;
    TMatrix RyLteta,RxLphi,RzAngle,BackRxLphi,BackRyLteta;

    VectorX = Point3d(1,0,0);

    //float AnglePhi(void);//возращает угол Phi в полярных координатах (угол YOP - угол между осью Y и вектором P (0..180))
    //float AngleTeta(void);//возращает угол Teta в полярных координатах (угол между осью Z и проекцией вектора P на плоскость ZOX (0..360))
    A = Point3d(X,Y,Z);

    //RollZ_XOY(float Angle);//делат матрицу поворота вокруг оси Z на угол Angle от X к Y
    //RollX_YOZ(float Angle);//делает матрицу поворота вокруг оси X на угол Angle от Y к Z
    //RollY_ZOX(float Angle);//делает матрицу поворота вокруг оси Y на угол Angle от Z к X
    RyAteta.RollY_ZOX(A.AngleTeta());
    RxAphi.RollX_YOZ(A.AnglePhi());
    //RzRoll.RollZ_XOY(Roll);
    RzRoll.RollY_ZOX(-Roll);

    L = RyAteta*RxAphi*RzRoll * VectorX;//ось, вокруг которой вращаемся

    RyLteta.RollY_ZOX(L.AngleTeta());
    RxLphi.RollX_YOZ(L.AnglePhi());
    //RzAngle.RollZ_XOY(Angle);
    RzAngle.RollY_ZOX(Angle);
    BackRxLphi.RollX_YOZ(-L.AnglePhi());
    BackRyLteta.RollY_ZOX(-L.AngleTeta());

    A = RyLteta*RxLphi*RzAngle*BackRxLphi*BackRyLteta * A;

    X = A.x;
    Y = A.y;
    Z = A.z;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RotationAroundY(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble Angle)
{
	TPoint3d A,L,VectorX;
    TMatrix RyAteta,RxAphi,RzRoll;
    TMatrix RyLteta,RxLphi,RzAngle,BackRxLphi,BackRyLteta;

    VectorX = Point3d(0,0,1);

    //float AnglePhi(void);//возращает угол Phi в полярных координатах (угол YOP - угол между осью Y и вектором P (0..180))
    //float AngleTeta(void);//возращает угол Teta в полярных координатах (угол между осью Z и проекцией вектора P на плоскость ZOX (0..360))
    A = Point3d(X,Y,Z);

    //RollZ_XOY(float Angle);//делат матрицу поворота вокруг оси Z на угол Angle от X к Y
    //RollX_YOZ(float Angle);//делает матрицу поворота вокруг оси X на угол Angle от Y к Z
    //RollY_ZOX(float Angle);//делает матрицу поворота вокруг оси Y на угол Angle от Z к X
    RyAteta.RollY_ZOX(A.AngleTeta());
    RxAphi.RollX_YOZ(A.AnglePhi());
    //RzRoll.RollZ_XOY(Roll);
    RzRoll.RollY_ZOX(-Roll);

    L = RyAteta*RxAphi*RzRoll * VectorX;//ось, вокруг которой вращаемся

    RyLteta.RollY_ZOX(L.AngleTeta());
    RxLphi.RollX_YOZ(L.AnglePhi());
    //RzAngle.RollZ_XOY(Angle);
    RzAngle.RollY_ZOX(Angle);
    BackRxLphi.RollX_YOZ(-L.AnglePhi());
    BackRyLteta.RollY_ZOX(-L.AngleTeta());

    A = RyLteta*RxLphi*RzAngle*BackRxLphi*BackRyLteta * A;

    X = A.x;
    Y = A.y;
    Z = A.z;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MoveDirection(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble DirectionValue)
{
	TPoint3d D;
    D = Point3d(X,Y,Z);
    D = D.Normirate();
    D = D * DirectionValue;
    X = D.x;
    Y = D.y;
    Z = D.z;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DirectAlongX(GLdouble &X, GLdouble &Y,GLdouble &Z)
{
	TPoint3d A,L,VectorX;
    TMatrix RyAteta,RxAphi,RzRoll;

    VectorX = Point3d(1,0,0);

    //float AnglePhi(void);//возращает угол Phi в полярных координатах (угол YOP - угол между осью Y и вектором P (0..180))
    //float AngleTeta(void);//возращает угол Teta в полярных координатах (угол между осью Z и проекцией вектора P на плоскость ZOX (0..360))
    A = Point3d(X,Y,Z);

    //RollZ_XOY(float Angle);//делат матрицу поворота вокруг оси Z на угол Angle от X к Y
    //RollX_YOZ(float Angle);//делает матрицу поворота вокруг оси X на угол Angle от Y к Z
    //RollY_ZOX(float Angle);//делает матрицу поворота вокруг оси Y на угол Angle от Z к X
    RyAteta.RollY_ZOX(A.AngleTeta());
    RxAphi.RollX_YOZ(A.AnglePhi());
    //RzRoll.RollZ_XOY(Roll);
    RzRoll.RollY_ZOX(-Roll);

    L = RyAteta*RxAphi*RzRoll * VectorX;


    X = L.x;
    Y = L.y;
    Z = L.z;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DirectAlongZ(GLdouble &X, GLdouble &Y,GLdouble &Z)
{
	TPoint3d A,L,VectorX;
    TMatrix RyAteta,RxAphi,RzRoll;

    VectorX = Point3d(0,0,-1);

    //float AnglePhi(void);//возращает угол Phi в полярных координатах (угол YOP - угол между осью Y и вектором P (0..180))
    //float AngleTeta(void);//возращает угол Teta в полярных координатах (угол между осью Z и проекцией вектора P на плоскость ZOX (0..360))
    A = Point3d(X,Y,Z);

    //RollZ_XOY(float Angle);//делат матрицу поворота вокруг оси Z на угол Angle от X к Y
    //RollX_YOZ(float Angle);//делает матрицу поворота вокруг оси X на угол Angle от Y к Z
    //RollY_ZOX(float Angle);//делает матрицу поворота вокруг оси Y на угол Angle от Z к X
    RyAteta.RollY_ZOX(A.AngleTeta());
    RxAphi.RollX_YOZ(A.AnglePhi());
    //RzRoll.RollZ_XOY(Roll);
    RzRoll.RollY_ZOX(-Roll);

    L = RyAteta*RxAphi*RzRoll * VectorX;


    X = L.x;
    Y = L.y;
    Z = L.z;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DirectAlongY(GLdouble &X, GLdouble &Y,GLdouble &Z)
{
	TPoint3d A,L,VectorX;
    TMatrix RyAteta,RxAphi,RzRoll;

    VectorX = Point3d(0,1,0);

    //float AnglePhi(void);//возращает угол Phi в полярных координатах (угол YOP - угол между осью Y и вектором P (0..180))
    //float AngleTeta(void);//возращает угол Teta в полярных координатах (угол между осью Z и проекцией вектора P на плоскость ZOX (0..360))
    A = Point3d(X,Y,Z);

    //RollZ_XOY(float Angle);//делат матрицу поворота вокруг оси Z на угол Angle от X к Y
    //RollX_YOZ(float Angle);//делает матрицу поворота вокруг оси X на угол Angle от Y к Z
    //RollY_ZOX(float Angle);//делает матрицу поворота вокруг оси Y на угол Angle от Z к X
    RyAteta.RollY_ZOX(A.AngleTeta());
    RxAphi.RollX_YOZ(A.AnglePhi());
    //RzRoll.RollZ_XOY(Roll);
    RzRoll.RollY_ZOX(-Roll);

    L = RyAteta*RxAphi*RzRoll * VectorX;


    X = L.x;
    Y = L.y;
    Z = L.z;
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::Visibled(int Nx, int Nz)
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y)
{
	fTimerEvent = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DisplayAxis(bool X, bool Y, bool Z)
{
    GLfloat ProjectionMatrix[4][4], *pMatix;
    pMatix = (GLfloat*)ProjectionMatrix;

    glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);

    MillersIndexesLabel->Caption = "(" +
     							 IntToStr((int)floor((100*ProjectionMatrix[0][2])+0.5)/1) + ":" +
                                 IntToStr((int)floor((100*ProjectionMatrix[1][2])+0.5)/1) + ":" +
                                 IntToStr((int)floor((100*ProjectionMatrix[2][2])+0.5)/1) + ")";
    OrthoMillersIndexesLabel->Caption = "|- (" +
     							 IntToStr((int)floor((100*ProjectionMatrix[0][0])+0.5)/1) + ":" +
                                 IntToStr((int)floor((100*ProjectionMatrix[1][0])+0.5)/1) + ":" +
                                 IntToStr((int)floor((100*ProjectionMatrix[2][0])+0.5)/1) + ")";
	if(X || Y || Z)
    {
     float color[4] = {1, 1, 1, 0.1};
     //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
     //MillersComboBox->Items->Strings[0] = MillersIndexesLabel->Caption;
     //SaveOrientationComboBox->Items->Strings[0] = MillersIndexesLabel->Caption;
     GLdouble Len = 0.95*min(XPort*Scale,YPort*Scale);
     glColor3d(0,0,0);
     if(X == true)
     {
      glBegin(GL_LINES);
        //glColor3d(1,0,0);
        //glColor3d(0,0,0);
        //glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
        color[0]=1; color[1]=0; color[2]=0; color[3]=1;
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
        glVertex3d(-Len,0,0);
        //glColor3d(1,0,0);
        //glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
        //color[0]=1; color[1]=0; color[2]=0; color[3]=0;
        //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
        glVertex3d(Len,0,0);
      glEnd();
     color[0]=(ProjectionMatrix[0][2]>=0)? 1: 0.5; color[1]=0; color[2]=0; color[3]=1;
     //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);//GL_AMBIENT
      glBegin(GL_POINTS);
        //glColor3d(1,0,0);
        //glColor3d(0,0,0);
        glVertex3d(Len,0,0);
      glEnd();
     }
     if(Y == true)
     {
      //glColor3d(0,1,0);
      glBegin(GL_LINES);//GL_QUADS
        //glColor3d(0,1,0);
        //glColor3d(0,0,0);
        //glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
        color[0]=0; color[1]=1; color[2]=0; color[3]=0;
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
        glVertex3d(0,Len,0);
        //glVertex3d(0.2,Len,0); glVertex3d(-0.1,Len,0);
        //glColor3d(0,1,0);
        //glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
        //color[0]=0; color[1]=1; color[2]=0; color[3]=0;
        //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
        glVertex3d(0,-Len,0);
        //glVertex3d(-0.1,-Len,0); glVertex3d(0.1,-Len,0);
      glEnd();
     //color[0]=0; color[1]=0; color[2]=0; color[3]=1;
     //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
     color[0]=0; color[1]=(ProjectionMatrix[1][2]>=0)? 1: 0.5; color[2]=0; color[3]=1;
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);//GL_AMBIENT
      glBegin(GL_POINTS);
        //glColor3d(0,1,0);
        glVertex3d(0,Len,0);
      glEnd();
     }
     if(Z == true)
     {
      glBegin(GL_LINES);
        //glColor3d(0,0,1);
        //glColor3d(0,0,0);
        //glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
        color[0]=0; color[1]=0; color[2]=1; color[3]=0;
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
        glVertex3d(0,0,-Len);
        //glColor3d(0,0,1);
        //glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
        //color[0]=0; color[1]=0; color[2]=1; color[3]=0;
        //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
        glVertex3d(0,0,Len);
      glEnd();
      color[0]=0; color[1]=0; color[2]=(ProjectionMatrix[2][2]>=0)? 1: 0.5; color[3]=1;
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
      glBegin(GL_POINTS);
        //glColor3d(0,0,1);
        glVertex3d(0,0,Len);
      glEnd();
     }
     color[0]=0; color[1]=0; color[2]=0; color[3]=1;
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
    }


    //ставим третий светильник
 	glPushMatrix();
	 glLoadIdentity();//переходим в глобальные координаты
     float color[4] = {1,1,1,1};
     float pos[4];
     float dir[3];
	 pos[2] = 100+CenterZ;
	 pos[0] = pos[2]*0.4+CenterX;
	 pos[1] = pos[2]*0.4+CenterY;
	 pos[2] = 100;
	 pos[0] = pos[2]*2;
	 pos[1] = pos[2]*0.4;
	 //pos[3] = 0.5+((Scale));
	 pos[3] = 1;
     dir[0] = 0;
     dir[1] = 0;
     dir[2] = -1;
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
     glLightfv(GL_LIGHT2, GL_POSITION, pos);
     glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);
     glLightfv(GL_LIGHT2, GL_DIFFUSE, color);
     glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 100.0);
     glLightf(GL_LIGHT2,GL_CONSTANT_ATTENUATION,0.7);
     glLightf(GL_LIGHT2,GL_LINEAR_ATTENUATION, 0.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,0.0);
 	glPopMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RotateAroundWoldAxises(GLdouble Alpha, GLdouble Beta, GLdouble Gamma)
{
     GLfloat ProjectionMatrix[4][4], *pMatix;
     pMatix = (GLfloat*)ProjectionMatrix;
     glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);

     if(Alpha !=0) glRotated(Alpha, ProjectionMatrix[0][0],ProjectionMatrix[1][0],ProjectionMatrix[2][0]);
     if(Beta !=0)  glRotated(Beta,  ProjectionMatrix[0][1],ProjectionMatrix[1][1],ProjectionMatrix[2][1]);
     if(Gamma !=0) glRotated(Gamma, ProjectionMatrix[0][2],ProjectionMatrix[1][2],ProjectionMatrix[2][2]);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MillersComboBoxChange(TObject *Sender)
{
/*
(0:0:1)
(0:-1:0)
(1:0:0)
(0:1:1)
(1:0:1)
(1:1:0)
(1:1:1)
-2.1
-2.2
-2.3
-2.4
-2.5
-2.6
-2.7
-3.1
-3.2
-3.3
-3.4
-3.5
-3.6
-3.7
(-1:-1:1)
(1:-1:0)
      case 0://001
       //уже реализована
      break;
      case 1://(0;-1;0)
       glRotated(-90, 1,0,0);
       //glRotated(90, 0,1,0);
      break;
      case 2://100
       glRotated(-90, 0,1,0);
      break;
      case 3://011
       glRotated(45, 1,0,0);
      break;
      case 4://101
       glRotated(-45, 0,1,0);
      break;
      case 5://110
       glRotated(90, 0,1,0);
       glRotated(45, 0,0,1);
       glRotated(180, 0,1,0);
      break;
      case 6://111
       //glRotated(-45, 1,0,0);
       glRotated(-54.73561031725, 1,0,0); //54,73561031725
       glRotated(-135, 0,0,1);
      break;
      case 7://(-1;-1;1)
       //glRotated(-45, 1,0,0);
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);
      break;
      case 8://(1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);
      break;
     }


      case 0://001
       //уже реализована
      break;
      case 1://(0;-1;0)
       glRotated(-90, 1,0,0);
      break;
      case 2://100
       glRotated(-90, 0,1,0);
      break;
      case 3://011
       glRotated(45, 1,0,0);
      break;
      case 4://101
       glRotated(-45, 0,1,0);
      break;
      case 5://110
       glRotated(90, 0,1,0);
       glRotated(45, 0,0,1);
       glRotated(180, 0,1,0);
      break;
      case 6://111
       glRotated(-54.73561031725, 1,0,0); //54,73561031725
       glRotated(-135, 0,0,1);
      break;

      case 7://( 0; 0; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       //уже реализована
      break;
      case 8://( 0;-1; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(-90, 1,0,0);
      break;
      case 9://( 1; 0; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(-90, 0,1,0);
      break;
      case 10://( 0; 1; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(45, 1,0,0);
      break;
      case 11://( 1; 0; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(-45, 0,1,0);
      break;
      case 12://( 1; 1; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(90, 0,1,0);
       glRotated(45, 0,0,1);
       glRotated(180, 0,1,0);
      break;
      case 13://( 1; 1; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(-54.73561031725, 1,0,0); //54,73561031725
       glRotated(-135, 0,0,1);
      break;

      //case 14://( 0; 0; 1) для (1;-1;0)
      // glRotated(-90, 1,0,0);
      // glRotated(-45, 0,0,1);
      //break;
      case 14://( 0; 0; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //уже реализована
      break;
      case 15://( 0;-1; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);
       //RotateAroundWoldAxises(AlphaG, BetaG, GammaG)
       //glRotated(-90, 1,0,0);
       RotateAroundWoldAxises(-90, 0, 0);
      break;
      case 16://( 1; 0; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-90, 0,1,0);
       RotateAroundWoldAxises(-90, 0, 0);
       RotateAroundWoldAxises( 0, -90, 0);
      break;
      case 17://( 0; 1; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(45, 1,0,0);
       RotateAroundWoldAxises(-45, 0, 0);
      break;
      case 18://( 1; 0; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-45, 0,1,0);
       RotateAroundWoldAxises( 0,-45, 0);
      break;
      case 19://( 1; 1; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       RotateAroundWoldAxises( 0, 0, -45);
       RotateAroundWoldAxises( -90, 0, 0);
      break;
      case 20://( 1; 1; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-54.73561031725, 1,0,0); //54,73561031725
       //RotateAroundWoldAxises( -54.73561031725, 0, 0);
       //glRotated(-135, 0,0,1);
       //RotateAroundWoldAxises( 0, 0, -135);

       RotateAroundWoldAxises( 0, 0, -45);
       RotateAroundWoldAxises( -54.73561031725, 0, 0);
      break;
////////////////////////////////////////////////
(0:0:1) -1
(0:-1:0)-1
(1:0:0) -1
(0:1:1) -1
(1:0:1) -1
(1:1:0) -1
(1:1:1) -1
(0:0:1) -2
(0:-1:0)-2
(1:0:0) -2
(0:1:1) -2
(1:0:1) -2
(1:1:0) -2
(1:1:1) -2
(0:0:1) -3
(0:-1:0)-3
(1:0:0) -3
(0:1:1) -3
(1:0:1) -3
(1:1:0) -3
(1:1:1) -3

      case 0://001
       //уже реализована
      break;
      case 1://(0;-1;0)
       glRotated(-90, 1,0,0);
      break;
      case 2://100
       glRotated(-90, 0,1,0);
      break;
      case 3://011
       glRotated(45, 1,0,0);
      break;
      case 4://101
       glRotated(-45, 0,1,0);
      break;
      case 5://110
       glRotated(90, 0,1,0);
       glRotated(45, 0,0,1);
       glRotated(180, 0,1,0);
      break;
      case 6://111
       glRotated(-54.73561031725, 1,0,0); //54,73561031725
       glRotated(-135, 0,0,1);
      break;

      case 7://( 0; 0; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       //уже реализована
      break;
      case 8://( 0;-1; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(-90, 1,0,0);
      break;
      case 9://( 1; 0; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(-90, 0,1,0);
      break;
      case 10://( 0; 1; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(45, 1,0,0);
      break;
      case 11://( 1; 0; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(-45, 0,1,0);
      break;
      case 12://( 1; 1; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(90, 0,1,0);
       glRotated(45, 0,0,1);
       glRotated(180, 0,1,0);
      break;
      case 13://( 1; 1; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       glRotated(-54.73561031725, 1,0,0); //54,73561031725
       glRotated(-135, 0,0,1);
      break;

      //case 14://( 0; 0; 1) для (1;-1;0)
      // glRotated(-90, 1,0,0);
      // glRotated(-45, 0,0,1);
      //break;
      case 14://( 0; 0; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //уже реализована
      break;
      case 15://( 0;-1; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);
       //RotateAroundWoldAxises(AlphaG, BetaG, GammaG)
       //glRotated(-90, 1,0,0);
       RotateAroundWoldAxises(-90, 0, 0);
      break;
      case 16://( 1; 0; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-90, 0,1,0);
       RotateAroundWoldAxises(-90, 0, 0);
       RotateAroundWoldAxises( 0, -90, 0);
      break;
      case 17://( 0; 1; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(45, 1,0,0);
       RotateAroundWoldAxises(-45, 0, 0);
      break;
      case 18://( 1; 0; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-45, 0,1,0);
       RotateAroundWoldAxises( 0,-45, 0);
      break;
      case 19://( 1; 1; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       RotateAroundWoldAxises( 0, 0, -45);
       RotateAroundWoldAxises( -90, 0, 0);
      break;
      case 20://( 1; 1; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-54.73561031725, 1,0,0); //54,73561031725
       //RotateAroundWoldAxises( -54.73561031725, 0, 0);
       //glRotated(-135, 0,0,1);
       //RotateAroundWoldAxises( 0, 0, -135);

       RotateAroundWoldAxises( 0, 0, -45);
       RotateAroundWoldAxises( -54.73561031725, 0, 0);
      break;


*/
    if(Initialiseded)
    {
	 glLoadIdentity();
	 SpeedXT = SpeedYT = SpeedZT = 0;
     switch(MillersComboBox->ItemIndex)
     {
      case 0://001
       //уже реализована
      break;
      case 1://(0;-1;0)
       glRotated(-90, 1,0,0);
      break;
      case 2://100
       glRotated(-90, 0,1,0);
       glRotated(-90, 1,0,0);
      break;

      case 3://( 0; 0; 1) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //уже реализована
      break;
      case 4://( 0;-1; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);
       //RotateAroundWoldAxises(AlphaG, BetaG, GammaG)
       //glRotated(-90, 1,0,0);
       RotateAroundWoldAxises(-90, 0, 0);
      break;
      case 5://( 1; 0; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-90, 0,1,0);
       RotateAroundWoldAxises(-90, 0, 0);
       RotateAroundWoldAxises( 0, -90, 0);
      break;
      case 6://( 1; 0; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-90, 0,1,0);
       RotateAroundWoldAxises(0, 0, -90);
       RotateAroundWoldAxises( -45, 0, 0);
       RotateAroundWoldAxises( 0,-45,  0);
      break;
      case 7://( 1; 0; 0) для (1;-1;0)
       glRotated(-90, 1,0,0);
       glRotated(-45, 0,0,1);

       //glRotated(-90, 0,1,0);
       RotateAroundWoldAxises(0,45,0);
       RotateAroundWoldAxises(0,0,90);
       RotateAroundWoldAxises(0,-45,0);
      break;

      case 8://( 0; 0; 1) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       //уже реализована
      break;
      case 9://( 0;-1; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       RotateAroundWoldAxises(-90,0,0);
       RotateAroundWoldAxises(0,-180,0);
      break;
      case 10://( 0;-1; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       RotateAroundWoldAxises(-90,0,0);
       RotateAroundWoldAxises(0,-120,0);
      break;
      case 11://( 1; 0; 0) для (-1;-1;1)
       glRotated(-45, 1,0,0); //54,73561031725
       glRotated(35.264389682754654315377000330019, 0,1,1);

       RotateAroundWoldAxises(-90,0,0);
       RotateAroundWoldAxises(0,-150,0);
      break;
     }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MillersComboBoxDropDown(TObject *Sender)
{
	EnabledPaint = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveOrientationComboBoxChange(TObject *Sender)
{
    int ItemIndex = SaveOrientationComboBox->ItemIndex;
    if(ItemIndex > 0)
    {
     TOrientation *Orientation;
     Orientation = (TOrientation *)SaveOrientationComboBox->Items->Objects[ItemIndex];
     RestoreOrn(*Orientation);
     /*
     glLoadMatrixf(Orientation->vMatix);
     Scale = Orientation->Scale;
     MultiAngle = Orientation->MultiAngle;
     MultiSpeed = Orientation->MultiSpeed;
     SpeedXT = Orientation->Xt;
     SpeedYT = Orientation->Yt;
     SpeedZT = Orientation->Zt;
     MulAngleLabel->Caption = "Угол x " + AnsiString(MultiAngle);//"Angle •" + AnsiString(MultiAngle);
     MulSpeedLabel->Caption = "Шаг x " + AnsiString(MultiSpeed);//"Move •" + AnsiString(MultiSpeed);
     AcceptScale();
     */
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ScreenPanelMouseMove(TObject *Sender,
	TShiftState Shift, int X, int Y)
{
	EnabledPaint = true;
    ScreenPanelMousePoint.x = X;
    ScreenPanelMousePoint.y = Y;
    //XLabel->Caption = IntToStr(ScreenPanelMousePoint.x);
    //YLabel->Caption = IntToStr(ScreenPanelMousePoint.y);
    if(IsSurfaceGen)
	{
	 if(DelHoldSpeedButton->Down)
      DelHoldSufAtomPriview();
     //if(MarkSpeedButton->Down)
     // MarkSufAtomPriview();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveOrientationSpeedButtonClick(TObject *Sender)
{
    if(Initialiseded)
    {
     //GLfloat ProjectionMatrix[4][4], *pMatix;
     //pMatix = (GLfloat*)ProjectionMatrix;
     //glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);
	 //GLfloat *pMatix;
     //pMatix = new GLfloat[16];
     //glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);
     TOrientation *Orientation;
     Orientation = new TOrientation;
     /*
     glGetFloatv(GL_MODELVIEW_MATRIX, Orientation->vMatix);
     Orientation->Scale = Scale;
     Orientation->MultiAngle = MultiAngle;
     Orientation->MultiSpeed = MultiSpeed;
     Orientation->Xt = SpeedXT;
     Orientation->Yt = SpeedYT;
     Orientation->Zt = SpeedZT;
     */
     SaveOrn(*Orientation);
     //AddObject(const System::AnsiString S, System::TObject* AObject);
     SaveOrientationComboBox->ItemIndex =
	  SaveOrientationComboBox->Items->AddObject(IntToStr(SaveOrientationComboBox->Items->Count) + ": " +
       //MillersIndexesLabel->Caption, (System::TObject*)pMatix);
       MillersIndexesLabel->Caption, (System::TObject*)Orientation);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MillersComboBoxClick(TObject *Sender)
{
    EnabledPaint = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ScreenPanelClick(TObject *Sender)
{
    if(IsSurfaceGen & Initialiseded)
    {
     if(DelHoldSpeedButton->Down)
     {
      AtomMouseClick();
      // DelSufAtom();
     }
     //if(MarkSpeedButton->Down)
     // MarkSufAtom();

    }
    //InfoForm->Visible =!InfoForm->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrowAtom(GLint x, GLint y, GLint z)
{
    GLfloat IntensivColor,Zt, MinColor;
    MinColor = 0.5;//*Scale;
	//if(ModelViewMatrix[0][2]*(float))
    Zt = ModelViewMatrix[0][2]*(float)x + ModelViewMatrix[1][2]*(float)y + ModelViewMatrix[2][2]*(float)z;
    IntensivColor = (1-MinColor)*(Zt-Zmin)/(Zmax-Zmin) + MinColor;
    ColorAtom[0] = ColorAtom[1] = ColorAtom[2] = IntensivColor;
    //ColorAtom[1] = 0;
    ColorAtom[3] = 1;
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
    glVertex3i(x,y,z);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrowColorAtom(GLint x, GLint y, GLint z,GLfloat R, GLfloat G, GLfloat B, bool bUseDep)
{
	//if(ModelViewMatrix[0][2]*(float))
    if(Depth && bUseDep)
    {
     GLfloat IntensivColor,Zt, MinColor;
     MinColor = 0.5;//*Scale;
     Zt = ModelViewMatrix[0][2]*(float)x + ModelViewMatrix[1][2]*(float)y + ModelViewMatrix[2][2]*(float)z;
     if(Zmax!=Zmin) IntensivColor = (1-MinColor)*(Zt-Zmin)/(Zmax-Zmin) + MinColor;
     else IntensivColor = 1;
     ColorAtom[0] = R*IntensivColor;
     ColorAtom[1] = G*IntensivColor;
     ColorAtom[2] = B*IntensivColor;
     //ColorAtom[1] = 0;
     ColorAtom[3] = 1;
    }
    else
    {
     ColorAtom[0] = R;
     ColorAtom[1] = G;
     ColorAtom[2] = B;
     ColorAtom[3] = 1;
    }
    if(Points == false)
    {
	 glColor3f(ColorAtom[0],ColorAtom[1],ColorAtom[2]);
   	 glPushMatrix();
	  glTranslatef(x,y,z);
//      ColorAtom[0] = 0;
//      ColorAtom[1] = 0;
//      ColorAtom[2] = 0;
//      ColorAtom[3] = 0;
//      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
      gluSphere(quadObj, 1*AtomSize, Qality, Qality); // рисуем сферу
	 glPopMatrix();
    }
    else
    {
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
     glVertex3i(x,y,z);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrowLink(GLint x1, GLint y1, GLint z1,GLint x2, GLint y2, GLint z2)
{
    GLfloat IntensivColor,Zt, MinColor;
    MinColor = 0.5;//*Scale;
    Zt = ModelViewMatrix[0][2]*(float)x1 + ModelViewMatrix[1][2]*(float)y1 + ModelViewMatrix[2][2]*(float)z1;
    //IntensivColor = (1-MinColor)*(Zt-Zmin)/(Zmax-Zmin) + MinColor;
    if(Zmax!=Zmin) IntensivColor = (1-MinColor)*(Zt-Zmin)/(Zmax-Zmin) + MinColor;
    else IntensivColor = 1;
    ColorAtom[1] = IntensivColor;
    ColorAtom[0] = IntensivColor;
    ColorAtom[2] = IntensivColor;
    ColorAtom[3] = 1;
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
    glVertex3i(x1,y1,z1);
    Zt = ModelViewMatrix[0][2]*(float)x2 + ModelViewMatrix[1][2]*(float)y2 + ModelViewMatrix[2][2]*(float)z2;
    //IntensivColor = (1-MinColor)*(Zt-Zmin)/(Zmax-Zmin) + MinColor;
    if(Zmax!=Zmin) IntensivColor = (1-MinColor)*(Zt-Zmin)/(Zmax-Zmin) + MinColor;
    else IntensivColor = 1;
    ColorAtom[1] = IntensivColor;
    ColorAtom[0] = ColorAtom[2] = 0;
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
    glVertex3i(x2,y2,z2);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrowColorLink(GLint x1, GLint y1, GLint z1,GLint x2, GLint y2, GLint z2, GLfloat R, GLfloat G, GLfloat B, GLfloat rb, GLfloat gb, GLfloat bb, GLfloat re, GLfloat ge, GLfloat be)
{
    GLfloat IntensivColor = 1.0;
    if(Depth)
    {
     GLfloat Zt, MinColor;
     MinColor = 0.5;//*Scale;
     Zt = ModelViewMatrix[0][2]*(float)x1 + ModelViewMatrix[1][2]*(float)y1 + ModelViewMatrix[2][2]*(float)z1;
     if(Zmax!=Zmin) IntensivColor = (1-MinColor)*(Zt-Zmin)/(Zmax-Zmin) + MinColor;
    }
    ColorAtom[0] = R * IntensivColor;
    ColorAtom[1] = G * IntensivColor;
    ColorAtom[2] = B * IntensivColor;
    ColorAtom[3] = 1;
                    
    if(Points == false)
    {
     bool bSepLink = true;
     if(bSepLink == true)
     {
      double dx, dy, dz, dxylen;
      dx = x2-x1;
      dy = y2-y1;
      dz = z2-z1;
      dxylen = pow(dx*dx+dy*dy,0.5);
      ColorAtom[0] = rb * IntensivColor;
      ColorAtom[1] = gb * IntensivColor;
      ColorAtom[2] = bb * IntensivColor;
      ColorAtom[3] = 1;

      glColor3f(ColorAtom[0],ColorAtom[1],ColorAtom[2]);
      glPushMatrix();
       glTranslatef(x1,y1,z1);
       //glRotated(90.0+(z2-z1)*45.0, x2-x1, y2-y1, 0);
       //вокруг вектора = векторное произведение оси Z (0 0 1) и проекции на плоскость ху (dx,dy,0)
       //векторное произведение [AB]= (AyBz-AzBy, AzBx-AxBz, AxBy-AyBx)
       glRotated(-(90.0-180.0/M_PI*atan(dz/dxylen)) , dy, -dx, 0);
       gluCylinder(quadObj, 0.3*AtomSize, 0.3*AtomSize, 1/2.0*1.7320508075688772935274463415059, Qality, 1);
       //gluSphere(quadObj, 1*AtomSize, Qality, Qality); // рисуем сферу
	  glPopMatrix();

      ColorAtom[0] = re * IntensivColor;
      ColorAtom[1] = ge * IntensivColor;
      ColorAtom[2] = be * IntensivColor;
      ColorAtom[3] = 1;

 	  glColor3f(ColorAtom[0],ColorAtom[1],ColorAtom[2]);
      glPushMatrix();
 	   glTranslatef((x1+x2)/2.0,(y1+y2)/2.0,(z1+z2)/2.0);
       //glRotated(90.0+(z2-z1)*45.0, x2-x1, y2-y1, 0);
       //double dx, dy, dz, dxylen;
       //вокруг вектора = векторное произведение оси Z (0 0 1) и проекции на плоскость ху (dx,dy,0)
       //векторное произведение [AB]= (AyBz-AzBy, AzBx-AxBz, AxBy-AyBx)
       glRotated(-(90.0-180.0/M_PI*atan(dz/dxylen)) , dy, -dx, 0);
       gluCylinder(quadObj, 0.3*AtomSize, 0.3*AtomSize, 1/2.0*1.7320508075688772935274463415059, Qality, 1);
       //gluSphere(quadObj, 1*AtomSize, Qality, Qality); // рисуем сферу
	  glPopMatrix();

     }
     else
     {
	 glColor3f(ColorAtom[0],ColorAtom[1],ColorAtom[2]);
   	 glPushMatrix();
	  glTranslatef(x1,y1,z1);
      //glRotated(90.0+(z2-z1)*45.0, x2-x1, y2-y1, 0);
      double dx, dy, dz, dxylen;
      dx = x2-x1;
      dy = y2-y1;
      dz = z2-z1;
      dxylen = pow(dx*dx+dy*dy,0.5);
      //вокруг вектора = векторное произведение оси Z (0 0 1) и проекции на плоскость ху (dx,dy,0)
      //векторное произведение [AB]= (AyBz-AzBy, AzBx-AxBz, AxBy-AyBx)
      glRotated(-(90.0-180.0/M_PI*atan(dz/dxylen)) , dy, -dx, 0);
      gluCylinder(quadObj, 0.3*AtomSize, 0.3*AtomSize, 1.7320508075688772935274463415059, Qality, 1);
      //gluSphere(quadObj, 1*AtomSize, Qality, Qality); // рисуем сферу
	 glPopMatrix();

     }

    }
    else
    {
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
     glVertex3i(x1,y1,z1);
     glVertex3i(x2,y2,z2);
    }


}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetZinZmax(void)
{
       Zmax = Zmin = 0;
       if(ModelViewMatrix[0][2] > 0)
       Zmax += 4*ModelViewMatrix[0][2]*(float)m_DssParams.X;
       else Zmin += 4*ModelViewMatrix[0][2]*(float)m_DssParams.X;
       if(ModelViewMatrix[1][2] > 0)
       Zmax += 4*ModelViewMatrix[1][2]*(float)m_DssParams.Y;
       else Zmin += 4*ModelViewMatrix[1][2]*(float)m_DssParams.Y;
       if(ModelViewMatrix[2][2] < 0)
       Zmax += -ModelViewMatrix[2][2]*(float)m_DssParams.Z;
       else Zmin += -ModelViewMatrix[2][2]*(float)m_DssParams.Z;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrowAtomicResh(void)
{
	SetZinZmax();
       int i,j,k;
       int x1,y1;
       int x2,y2;

       //glColor3d(1,0,1);
       glColor3d(0,0,0);
       glBegin(GL_POINTS);
       for(k = 0; k < (signed)m_DssParams.Z; k++)
       {
        for(j = 0; j < (signed)m_DssParams.Y; j++)
        {
         for(i = 0; i < (signed)m_DssParams.X; i++)
         {
          switch(k % 4)
          {
           case 0:
            x1 = i*4;
            y1 = j*4;
            x2 = i*4 + 2;
            y2 = j*4 + 2;
           break;
           case 1:
            x1 = i*4 + 1;
            y1 = j*4 + 3;
            x2 = i*4 + 3;
            y2 = j*4 + 1;
           break;
           case 2:
            x1 = i*4 + 0;
            y1 = j*4 + 2;
            x2 = i*4 + 2;
            y2 = j*4 + 0;
           break;
           case 3:
            x1 = i*4 + 1;
            y1 = j*4 + 1;
            x2 = i*4 + 3;
            y2 = j*4 + 3;
           break;
          }
          DrowAtom(x1,y1,-k);
          DrowAtom(x2,y2,-k);
         }
         if(k%4==0)
         {
          DrowAtom(i*4,j*4,-k);
          if((unsigned)(j+1) >= m_DssParams.Y) DrowAtom(i*4,(j+1)*4,-k);
         }
         if(k%4==2) DrowAtom(i*4,j*4+2, -k);
        }
        if(k%4==0)
        {
         for(i = 0; i < (signed)m_DssParams.X; i++)
          DrowAtom(i*4,j*4,-k);
          //DrowAtom((i-1)*4,j*4,-k);
        }
        if(k%4==2)
        {
         for(i = 0; i < (signed)m_DssParams.X; i++)
 	      DrowAtom(i*4+2,j*4, -k);
 		  //DrowAtom((i-1)*4+2,j*4, -k);
        }
       }
       glEnd();
       //glPointSize(10.0);

       //if((Scale > 0.25)&&(IsLinksVisibled))
       if(IsLinksVisibled)
       {
        int imax,jmax;
        int x3,y3;
        int x4,y4;
        int x5,y5;
        int x6,y6;
        int x7,y7;
        int x8,y8;

        imax = m_DssParams.X;
        jmax = m_DssParams.Y;
        glColor3d(1,1,1);
        //glColor3d(0,0,0);
        glBegin(GL_LINES);
        for(k = 0; k < (signed)m_DssParams.Z-1; k++)
        {
         for(j = 0; j < (signed)m_DssParams.Y; j++)
         {
          for(i = 0; i < (signed)m_DssParams.X; i++)
          {
           switch(k % 4)
           {
            case 0:
             x1 = i*4;
             y1 = ((jmax+j-1)%jmax+1)*4;
             x3 = ((imax+i-1)%imax+1)*4;
             y3 = j*4;

             x2 = x4 = i*4 + 2;
             y2 = y4 = j*4 + 2;
            break;
            case 1:
             x1 = x3 = i*4 + 1;
             y1 = y3 = j*4 + 3;
             x2 = x4 = i*4 + 3;
             y2 = y4 = j*4 + 1;
            break;
            case 2:
             x1 = i*4 + 0;
             x3 = ((imax+i-1)%imax+1)*4 + 0;
             y1 = y3 = j*4 + 2;
             x2 = x4 = i*4 + 2;
             y2 = ((jmax+j-1)%jmax+1)*4 + 0;
             y4 = j*4 + 0;
            break;
            case 3:
             x1 = x3 = i*4 + 1;
             y1 = y3 = j*4 + 1;
             x2 = x4 = i*4 + 3;
             y2 = y4 = j*4 + 3;
            break;
           }
           switch(k % 2)
           {
            case 0:
             x5 = x1 + 1;
             y5 = y1 - 1;
             x6 = x2 + 1;
             y6 = y2 - 1;

             x7 = x3 - 1;
             y7 = y3 + 1;
             x8 = x4 - 1;
             y8 = y4 + 1;
            break;
            case 1:
             x5 = x1 - 1;
             y5 = y1 - 1;
             x6 = x2 - 1;
             y6 = y2 - 1;

             x7 = x3 + 1;
             y7 = y3 + 1;
             x8 = x4 + 1;
             y8 = y4 + 1;
            break;
           }
           DrowLink(x1,y1,-k, x5,y5,-(k+1));
           DrowLink(x3,y3,-k, x7,y7,-(k+1));

           DrowLink(x2,y2,-k, x6,y6,-(k+1));
           DrowLink(x4,y4,-k, x8,y8,-(k+1));
          }
         }
        }
        glEnd();
        //glLineWidth(2.0);
       }
}
//---------------------------------------------------------------------------
TOrientation::TOrientation()
{
}
//---------------------------------------------------------------------------
TOrientation::~TOrientation()
{
}
//---------------------------------------------------------------------------
TOrientation::TOrientation(const TOrientation &orn)
{
    *this = orn;
}
//---------------------------------------------------------------------------
void TOrientation::operator = (const TOrientation &orn)
{
	memcpy(vMatix, orn.vMatix, sizeof(vMatix));
	Xt = orn.Xt;
    Yt = orn.Yt;
    Zt = orn.Zt;
    MultiAngle = orn.MultiAngle;
    MultiSpeed = orn.MultiSpeed;
    Scale = orn.Scale;
    m_vClipPlane = orn.m_vClipPlane;
}
//---------------------------------------------------------------------------
#define FileWriteDataA(file, data) ((signed)sizeof(data) == FileWrite(file, (void*)(data), sizeof(data)))
#define FileWriteDataV(file, data) ((signed)sizeof(data) == FileWrite(file, (void*)&(data), sizeof(data)))
bool TOrientation::WriteToFile(int hFile)
{
    bool bRet = true;
    //int nSize;
    //nSize = sizeof(vMatix);
    //bRet &= (nSize == FileWrite(hFile, vMatix, nSize));
	bRet &= FileWriteDataA(hFile, vMatix);
	bRet &= FileWriteDataV(hFile, Xt);
    bRet &= FileWriteDataV(hFile, Yt);
    bRet &= FileWriteDataV(hFile, Zt);
	bRet &= FileWriteDataV(hFile, MultiAngle);
    bRet &= FileWriteDataV(hFile, MultiSpeed);
    bRet &= FileWriteDataV(hFile, Scale);

    UINT nCount = m_vClipPlane.size();
    bRet &= FileWriteDataV(hFile, nCount);
    UINT i;
    for(i = 0; i < nCount; i++)
    {
     TClipPlane &cp = m_vClipPlane[i];
     bRet &= cp.WriteToFile(hFile);
    }

    return bRet;
}
//---------------------------------------------------------------------------
//if(FileRead(hFile, pOrn, nSize) != nSize)
#define FileReadDataA(file, data) ((signed)sizeof(data) == FileRead(file, (void*)(data), sizeof(data)))
#define FileReadDataV(file, data) ((signed)sizeof(data) == FileRead(file, (void*)&(data), sizeof(data)))
//---------------------------------------------------------------------------
bool TOrientation::LoadFromFile(int hFile)
{
	bool bRet = true;
	bRet &= FileReadDataA(hFile, vMatix);
	bRet &= FileReadDataV(hFile, Xt);
    bRet &= FileReadDataV(hFile, Yt);
    bRet &= FileReadDataV(hFile, Zt);
    bRet &= FileReadDataV(hFile, MultiAngle);
    bRet &= FileReadDataV(hFile, MultiSpeed);
    bRet &= FileReadDataV(hFile, Scale);

    UINT nCount = 0;
    bRet &= FileReadDataV(hFile, nCount);
    UINT i;
    TClipPlane cp;
    for(i = 0; i < nCount; i++)
    {
     bRet &= cp.LoadFromFile(hFile);
     m_vClipPlane.push_back(cp);
    }
    return bRet;
}
//---------------------------------------------------------------------------
TClipPlane::TClipPlane()
{
    memset(FirstRowPM,0,sizeof(FirstRowPM));
}
//---------------------------------------------------------------------------
TClipPlane::TClipPlane(const TClipPlane &cp)
{
    *this = cp;
}
//---------------------------------------------------------------------------
void TClipPlane::operator = (const TClipPlane &cp)
{
	memcpy(FirstRowPM, cp.FirstRowPM, sizeof(FirstRowPM));
}
//---------------------------------------------------------------------------
bool TClipPlane::WriteToFile(int hFile)
{
    bool bRet = true;
	bRet &= FileWriteDataA(hFile, FirstRowPM);
    return bRet;
}
//---------------------------------------------------------------------------
bool TClipPlane::LoadFromFile(int hFile)
{
    bool bRet = true;
    bRet &= FileReadDataA(hFile, FirstRowPM);
    return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ProrertySpeedButtonClick(TObject *Sender)
{
	PropertyForm = new TPropertyForm(this);
    if((ExternExpProp == true)||(DsslExpPrprt == NULL)) PropertyForm->InitPropertyForm(ExperimentProperty);
    else  PropertyForm->InitPropertyForm(DsslExpPrprt);
    Hide();
    EnabledPaint = false;
    PropertyForm->ShowModal();
    EnabledPaint = true;
    Show();
    if(PropertyForm->ModalResult == mrYes)
    {
	 SaveSfsSpeedButtonClick(Sender);
    }
    FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LinksCheckBoxClick(TObject *Sender)
{
	IsLinksVisibled = LinksCheckBox->Checked;
	FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AxisCheckBoxMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	AxisX=AxisY=AxisZ=!AxisCheckBox->Checked;
    FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StepUpSpeedButtonClick(TObject *Sender)
{
      MultiSpeed *= 2;
      MulSpeedLabel->Caption = "Шаг x " + AnsiString(MultiSpeed);//"Move •" + AnsiString(MultiSpeed);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StepDownSpeedButtonClick(TObject *Sender)
{
      MultiSpeed /= 2;
      MulSpeedLabel->Caption = "Шаг x " + AnsiString(MultiSpeed);//"Move •" + AnsiString(MultiSpeed);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AngleUpSpeedButtonClick(TObject *Sender)
{
      MultiAngle *= 2;
      MulAngleLabel->Caption = "Угол x " + AnsiString(MultiAngle);//"Angle •" + AnsiString(MultiAngle);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AngleDownSpeedButtonClick(TObject *Sender)
{
      MultiAngle /= 2;
      MulAngleLabel->Caption = "Угол x " + AnsiString(MultiAngle);//"Angle •" + AnsiString(MultiAngle);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RightMoveSpeedButtonClick(TObject *Sender)
{
      SpeedXT += -SpeedXW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LeftMoveSpeedButtonSpeedButtonClick(TObject *Sender)
{
      SpeedXT += SpeedXW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::UpMoveSpeedButtonClick(TObject *Sender)
{
      SpeedYT += SpeedYW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DownMoveSpeedButtonClick(TObject *Sender)
{
      SpeedYT += -SpeedYW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FrontMoveSpeedButtonClick(TObject *Sender)
{
      SpeedZT += SpeedZW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BackMoveSpeedButtonClick(TObject *Sender)
{
      SpeedZT += -SpeedZW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XLocalBackSpeedButtonClick(TObject *Sender)
{
      BetaT = -BetaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      BetaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XLocalFrontSpeedButtonClick(TObject *Sender)
{
      BetaT = BetaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      BetaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::YLocalRightSpeedButtonClick(TObject *Sender)
{
      AlphaT = -AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      AlphaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::YLocalLeftSpeedButtonClick(TObject *Sender)
{
      AlphaT = AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      AlphaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ZLocalClockwiseSpeedButtonClick(TObject *Sender)
{
      GammaT = -GammaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      GammaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ZLocalAnticlockwiseSpeedButtonClick(TObject *Sender)
{
      GammaT = GammaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      GammaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XGlobalBackSpeedButtonClick(TObject *Sender)
{
      AlphaG = -AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      AlphaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XGlobalFrontSpeedButtonClick(TObject *Sender)
{
      AlphaG = AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      AlphaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::YGlobalRightSpeedButtonClick(TObject *Sender)
{
      BetaG = -BetaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      BetaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::YGlobalLeftSpeedButtonClick(TObject *Sender)
{
      BetaG = BetaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      BetaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ZGlobalClockwiseSpeedButtonClick(TObject *Sender)
{
      GammaG = -GammaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      GammaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ZGlobalAnticlockwiseSpeedButtonClick(TObject *Sender)
{
      GammaG = GammaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(NULL);
      GammaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::INSpeedButtonClick(TObject *Sender)
{
      Scale *= 1/(ScaleStep * ((ShiftSpeed(ShiftState) < 1)?(1/ShiftSpeed(ShiftState)):ShiftSpeed(ShiftState)));
      AcceptScale();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OUTSpeedButtonClick(TObject *Sender)
{
      Scale *= ScaleStep * ((ShiftSpeed(ShiftState) < 1)?(1/ShiftSpeed(ShiftState)):ShiftSpeed(ShiftState));
      AcceptScale();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveSfsSpeedButtonClick(TObject *Sender)
{
     TExperimentProperty *EpmntPrprt;
     if(ExternExpProp == true) EpmntPrprt = ExperimentProperty;
     else  EpmntPrprt = DsslExpPrprt;

     SfsSaveDialog->FileName = EpmntPrprt->FileName;
     if(SfsSaveDialog->Execute() == true)
     {
      HANDLE hFile;
      //HANDLE CreateFile(
      //LPCTSTR lpFileName,	// pointer to name of the file
      //DWORD dwDesiredAccess,	// access (read-write) mode
      //DWORD dwShareMode,	// share mode
      //LPSECURITY_ATTRIBUTES lpSecurityAttributes,	// pointer to security attributes
      //DWORD dwCreationDistribution,	// how to create
	  //DWORD dwFlagsAndAttributes,	// file attributes
      //HANDLE hTemplateFile 	// handle to file with attributes to copy
	  //);

	  hFile = CreateFile(_c_str(SfsSaveDialog->FileName),
      					 GENERIC_WRITE,//GENERIC_READ
						 FILE_SHARE_READ,
                         NULL,
                         CREATE_ALWAYS,
                         FILE_ATTRIBUTE_NORMAL,
						 NULL);
      if(hFile != INVALID_HANDLE_VALUE)
      {
       DWORD NumberOfBytesToWrite,NumberOfBytesWritten;
       int i,j;
       int TmpInt;
       double TmpDouble;
       bool bwf = true;
       //BOOL WriteFile(
       //	HANDLE hFile,	// handle to file to write to
       //	LPCVOID lpBuffer,	// pointer to data to write to file
       //	DWORD nNumberOfBytesToWrite,	// number of bytes to write
       //	LPDWORD lpNumberOfBytesWritten,	// pointer to number of bytes written
       //	LPOVERLAPPED lpOverlapped 	// pointer to structure needed for overlapped I/O
   	   //	);
       EpmntPrprt->FileName = SfsSaveDialog->FileName;
       do
       {
        TmpInt = EpmntPrprt->FileName.Pos("\\");
        if(TmpInt != 0) EpmntPrprt->FileName.Delete(1, TmpInt);
	   }
       while(TmpInt != 0);
	   Caption = PROGNAME_AND_VER + EpmntPrprt->FileName;

	   AnsiString id_sring = "This file is sfs format.";
	   //char *P_id = new char[id_sring.Length()];
	   NumberOfBytesToWrite = id_sring.Length()*sizeof(char);
	   bwf &= WriteFile(hFile,_c_str(id_sring),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       NumberOfBytesToWrite = sizeof(int);
	   bwf &= WriteFile(hFile,&(EpmntPrprt->W),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   bwf &= WriteFile(hFile,&(EpmntPrprt->H),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);

       bwf &= EpmntPrprt->SP.SaveToFile(hFile);

       bwf &= EpmntPrprt->m_vMask.SaveToFile(hFile, NULL);

       NumberOfBytesToWrite = sizeof(int);
       bwf &= WriteFile(hFile,&(EpmntPrprt->DelAtoms),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       bwf &= WriteFile(hFile,&(EpmntPrprt->DeletedLayers),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       bwf &= WriteFile(hFile,&(EpmntPrprt->DeletingLayers),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       bwf &= WriteFile(hFile,&(EpmntPrprt->N1),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       bwf &= WriteFile(hFile,&(EpmntPrprt->N2),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       bwf &= WriteFile(hFile,&(EpmntPrprt->N3),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       NumberOfBytesToWrite = sizeof(int)*EpmntPrprt->DeletingLayers;
       bwf &= WriteFile(hFile,EpmntPrprt->Layers,NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       NumberOfBytesToWrite = sizeof(double);
       TmpDouble = (double)EpmntPrprt->BeginTime;
       bwf &= WriteFile(hFile,&(TmpDouble),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       TmpDouble = (double)EpmntPrprt->DissolutionTime;
       bwf &= WriteFile(hFile,&(TmpDouble),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       TmpDouble = (double)EpmntPrprt->EndTime;
       bwf &= WriteFile(hFile,&(TmpDouble),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       bwf &= WriteFile(hFile,&(EpmntPrprt->AverageSpeed),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       TmpInt = EpmntPrprt->Description.Length();
       NumberOfBytesToWrite = sizeof(int);
       bwf &= WriteFile(hFile,&(TmpInt),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       if(TmpInt != 0)
       {
        NumberOfBytesToWrite = sizeof(char)*EpmntPrprt->Description.Length();
		bwf &= WriteFile(hFile,_c_str(EpmntPrprt->Description),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   }
	   if(bwf == false)
	   {
		char Text[] = "Свойства поверхности сохранить не удалось.";
        char Caption[] =  "Ошибка при сохранении файла";
		Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
       }
       bwf = true;
       //TAtom3d *KindAtoms[3],*LinksFromKindAtoms[3][2];
       //TAtom3d *NoDeleteAtoms,*LinksFromNoDeleteAtoms[2];
       //int NumberKindAtoms[3],NumberLinksFromKindAtoms[3];
       //int NumberNoDeleteAtoms,NumberLinksFromNoDeleteAtoms;
       NumberOfBytesToWrite = sizeof(int) * 1;
       bwf &= WriteFile(hFile,&NumberAtoms,NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       bwf &= WriteFile(hFile,&NumberLinksFromAtoms,NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);

       NumberOfBytesToWrite = sizeof(TAtom3d) * NumberAtoms;
       bwf &= WriteFile(hFile,Atoms,NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);

       NumberOfBytesToWrite = sizeof(TAtom3d) * NumberLinksFromAtoms;
       for(j = 0; j < 2; j++)
        bwf &= WriteFile(hFile,LinksFromAtoms[j],NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);

       if(bwf == false)
       {
        char Text[] = "Массивы атомов и массивы связей сохранить не удалось.";
		char Caption[] =  "Ошибка при сохранении файла";
		Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
	   }
	   SetEndOfFile(hFile);
	   CloseHandle(hFile);
	  }
	  else
	  {
	   char Text[] = "Функция CreateFile возратила INVALID_HANDLE_VALUE";
	   char Caption[] =  "Ошибка при сохранении файла";//открытии
	   Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
      }
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenSfsSpeedButtonClick(TObject *Sender)
{
     if(SfsOpenDialog->Execute() == true)
     {
      HANDLE hFile;
      //HANDLE CreateFile(
      //LPCTSTR lpFileName,	// pointer to name of the file
      //DWORD dwDesiredAccess,	// access (read-write) mode
      //DWORD dwShareMode,	// share mode
      //LPSECURITY_ATTRIBUTES lpSecurityAttributes,	// pointer to security attributes
      //DWORD dwCreationDistribution,	// how to create
	  //DWORD dwFlagsAndAttributes,	// file attributes
      //HANDLE hTemplateFile 	// handle to file with attributes to copy
      //);

	  hFile = CreateFile(_c_str(SfsOpenDialog->FileName),
						 GENERIC_READ,//GENERIC_WRITE
						 FILE_SHARE_WRITE,
						 NULL,
						 OPEN_ALWAYS,
						 FILE_ATTRIBUTE_NORMAL,
						 NULL);
      if(hFile != INVALID_HANDLE_VALUE)
      {
       DWORD NumberOfBytesRead,NumberOfBytesReaded;
       int i,j;
       int TmpInt;
       double TmpDouble;
       bool bwf = true;
	   //BOOL ReadFile(
       //	HANDLE hFile,	// handle of file to read
       //	LPVOID lpBuffer,	// address of buffer that receives data
       //	DWORD nNumberOfBytesToRead,	// number of bytes to read
       //	LPDWORD lpNumberOfBytesRead,	// address of number of bytes read
       //	LPOVERLAPPED lpOverlapped 	// address of structure for data
       //);
       AnsiString id_sring = "This file is sfs format.";
       char *P_id = new char[id_sring.Length()];
       NumberOfBytesRead = id_sring.Length()*sizeof(char);
       bwf &= ReadFile(hFile,P_id,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
       //P_id[id_sring.Length()] = '\0';
       if(AnsiString(P_id,(unsigned char)id_sring.Length()) == id_sring)
       {
        ExperimentProperty->FileName = SfsOpenDialog->FileName;
        do
        {
         TmpInt = ExperimentProperty->FileName.Pos("\\");
         if(TmpInt != 0) ExperimentProperty->FileName.Delete(1, TmpInt);
        }
        while(TmpInt != 0);
        Caption = PROGNAME_AND_VER + ExperimentProperty->FileName;
        NumberOfBytesRead = sizeof(int);
        bwf &= ReadFile(hFile,&(ExperimentProperty->W),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        bwf &= ReadFile(hFile,&(ExperimentProperty->H),NumberOfBytesRead,&NumberOfBytesReaded,NULL);

        bwf &= ExperimentProperty->SP.LoadFromFile(hFile);

        bwf &= ExperimentProperty->m_vMask.LoadFromFile(hFile, NULL);

        NumberOfBytesRead = sizeof(int);
        bwf &= ReadFile(hFile,&(ExperimentProperty->DelAtoms),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        bwf &= ReadFile(hFile,&(ExperimentProperty->DeletedLayers),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        if( ExperimentProperty->DeletingLayers != 0 ) delete ExperimentProperty->Layers;
        bwf &= ReadFile(hFile,&(ExperimentProperty->DeletingLayers),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        bwf &= ReadFile(hFile,&(ExperimentProperty->N1),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        bwf &= ReadFile(hFile,&(ExperimentProperty->N2),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        bwf &= ReadFile(hFile,&(ExperimentProperty->N3),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        NumberOfBytesRead = sizeof(int)*ExperimentProperty->DeletingLayers;
        ExperimentProperty->Layers = new int[ExperimentProperty->DeletingLayers];
        bwf &= ReadFile(hFile,ExperimentProperty->Layers,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        NumberOfBytesRead = sizeof(double);
        bwf &= ReadFile(hFile,&(TmpDouble),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        ExperimentProperty->BeginTime = TmpDouble;
        bwf &= ReadFile(hFile,&(TmpDouble),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        ExperimentProperty->DissolutionTime = TmpDouble;
        bwf &= ReadFile(hFile,&(TmpDouble),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        ExperimentProperty->EndTime = TmpDouble;
        bwf &= ReadFile(hFile,&(ExperimentProperty->AverageSpeed),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        TmpInt = ExperimentProperty->Description.Length();
        NumberOfBytesRead = sizeof(int);
        bwf &= ReadFile(hFile,&(TmpInt),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        if(TmpInt != 0)
        {
         char *TmpStr = new char[TmpInt];
		 //NumberOfBytesRead = sizeof(char)*ExperimentProperty->Description.Length();
		 //bwf &= ReadFile(hFile,_c_str(ExperimentProperty->Description),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		 NumberOfBytesRead = sizeof(char)*TmpInt;
         bwf &= ReadFile(hFile,TmpStr,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
         ExperimentProperty->Description = AnsiString(TmpStr, (unsigned char)TmpInt);
         delete TmpStr;
        }
        if(bwf == false)
        {
         char Text[] = "Свойства поверхности прочитать не удалось.";
         char Caption[] =  "Ошибка при открытии файла";
		 Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
		}
		DeletedLabel->Caption = IntToStr(ExperimentProperty->DelAtoms);

		bwf = true;
        //TAtom3d *KindAtoms[3],*LinksFromKindAtoms[3][2];
        //TAtom3d *NoDeleteAtoms,*LinksFromNoDeleteAtoms[2];
        //int NumberKindAtoms[3],NumberLinksFromKindAtoms[3];
        //int NumberNoDeleteAtoms,NumberLinksFromNoDeleteAtoms;
        if(NumberAtoms != 0) delete Atoms;
        if(NumberLinksFromAtoms != 0)
        {
         delete LinksFromAtoms[0];
         delete LinksFromAtoms[1];
        }

        NumberOfBytesRead = sizeof(int) * 1;

        bwf &= ReadFile(hFile,&NumberAtoms,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        bwf &= ReadFile(hFile,&NumberLinksFromAtoms,NumberOfBytesRead,&NumberOfBytesReaded,NULL);

        if(NumberAtoms != 0) Atoms = new TAtom3d[NumberAtoms];
        if(NumberLinksFromAtoms != 0)
        {
         LinksFromAtoms[0] = new TAtom3d[NumberLinksFromAtoms];
         LinksFromAtoms[1] = new TAtom3d[NumberLinksFromAtoms];
        }

        NumberOfBytesRead = sizeof(TAtom3d) * NumberAtoms;
        bwf &= ReadFile(hFile,Atoms,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        NumberOfBytesRead = sizeof(TAtom3d) * NumberLinksFromAtoms;
        for(j = 0; j < 2; j++)
         bwf &= ReadFile(hFile,LinksFromAtoms[j],NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        if(bwf == false)
        {
         char Text[] = "Массивы атомов и массивы связей прочитать не удалось.";
         char Caption[] =  "Ошибка при открытии файла";
		 Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
		}
        else
        {
     	 ExternExpProp = true;
         SetViewParams();
         //IsSurfaceGen = true;
        }
	   }
	   else
	   {
		AnsiString Text = "Файл " + SfsOpenDialog->FileName + " не sfs формата.";
		char Caption[] =  "Ошибка при открытии файла";
		Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
	   }
	   delete P_id;
	   //SetEndOfFile(hFile);
	   CloseHandle(hFile);
	  }
	  else
	  {
	   char Text[] = "Функция CreateFile возратила INVALID_HANDLE_VALUE";
	   char Caption[] =  "Ошибка при открытии файла";
	   Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
	  }
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetViewParams(void)
{
     int i,j,k;
     int Summ;
     for(k=0; k < 3; k++ )
     {
      MaxTopLeftUP.Coord[k] = Atoms[0].Coord[k];
      MinTopLeftUP.Coord[k] = Atoms[0].Coord[k];
     }

     for(j=0; j < NumberAtoms; j++ )
     {
      for(k=0; k < 3; k++ )
      {
       if(Atoms[j].Coord[k] > MaxTopLeftUP.Coord[k])
        MaxTopLeftUP.Coord[k] = Atoms[j].Coord[k];
       if(Atoms[j].Coord[k] < MinTopLeftUP.Coord[k])
        MinTopLeftUP.Coord[k] = Atoms[j].Coord[k];
      }
     }
     MaxTopLeftUP.Coord[2] = -MaxTopLeftUP.Coord[2];
     MinTopLeftUP.Coord[2] = -MinTopLeftUP.Coord[2];
     //SpeedXT = -((double)(MaxTopLeftUP.Coord[0]+MinTopLeftUP.Coord[0])/2);
     //SpeedYT = -((double)(MaxTopLeftUP.Coord[1]+MinTopLeftUP.Coord[1])/2);
     //DissolutionThread->Width;
     //DissolutionThread->Height;
     double H_2,W_2,Z_sr;
     if(ExternExpProp == true)
     {
      //EpmntPrprt = ExperimentProperty;

      //SpeedXT = -((double)(2*(ExperimentProperty->W)+2*(ExperimentProperty->H))/2);
      //SpeedYT = -((double)(2*(ExperimentProperty->W)-4*(ExperimentProperty->H))/2);
      H_2 = (double)ExperimentProperty->H/2.0;
      W_2 = (double)ExperimentProperty->W/2.0;
      Z_sr = ExperimentProperty->DeletedLayers + ExperimentProperty->DeletingLayers/2;
     }
     else
     {
      //EpmntPrprt = DsslExpPrprt;
      //SpeedXT = -((double)(2*(DsslExpPrprt->W)+2*(DsslExpPrprt->H))/2);
      //SpeedYT = -((double)(2*(DsslExpPrprt->W)-4*(DsslExpPrprt->H))/2);
      //SpeedZT = -((double)(-4*(DsslExpPrprt->W)+2*(DsslExpPrprt->H))/2);
      H_2 = (double)DsslExpPrprt->H/2.0;
      W_2 = (double)DsslExpPrprt->W/2.0;
      Z_sr = DsslExpPrprt->DeletedLayers + DsslExpPrprt->DeletingLayers/2;
     }
#ifdef Almas100
#endif
#ifdef Almas110
#endif
#ifdef Almas111
#endif
     if(SSD.m_nCaptureCode == 0)
     {
      CenterXT =  -(Mtr2[0][0]*W_2 + Mtr2[1][0]*H_2 + Mtr2[2][0]*Z_sr);
      CenterYT =  -(Mtr2[0][1]*W_2 + Mtr2[1][1]*H_2 + Mtr2[2][1]*Z_sr);
      CenterZT =  (Mtr2[0][2]*W_2 + Mtr2[1][2]*H_2 + Mtr2[2][2]*Z_sr);
     }
	 IsSurfaceGen = true;
     SurfaceMode = false;
     InitSecondTypeComboBox();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StatStopPanelClick(TObject *Sender)
{
    if(StatStopPanel->Caption != "Pause")
    {
     if(DissolutionThread == NULL)
     {
      //if(m_DssParams == 0) m_DssParams = new TDissolutionParametries;
	  //SurfaceForm->InitForm(ifNew);
      //EnabledPaint = false;
      //if(SurfaceForm->ShowModal() == mrOk)
      {
       //Repaint();
       StatusBar1->Panels->Items[1]->Text = "Инициализация...";
       DissolutionThread = new TDissolutionThread(true);
       if(DsslExpPrprt == NULL) DsslExpPrprt = new TExperimentProperty;

	   DissolutionThread->SP = m_DssParams.SP;
	   DissolutionThread->Algoritm = m_DssParams.m_Algoritm;

	   DissolutionThread->Plane = m_DssParams.Plane;
	   DsslExpPrprt->SP = DissolutionThread->SP;

       DsslExpPrprt->m_vMask.clear();

       if(m_DssParams.Masked == false)
       {
	   }
	   else
	   {
		DsslExpPrprt->m_vMask = m_DssParams.m_vMask;
	   }

	   //инициализация поверхности
	   DissolutionThread->InitSurface(m_DssParams);

       DsslExpPrprt->W = DissolutionThread->Width;
       DsslExpPrprt->H = DissolutionThread->Height;
       DsslExpPrprt->Description = "";

       StatStopPanel->Caption = "Pause";
       StatPauseLabel->Enabled = StatStopPanel->Enabled;
       StatPauseLabel->Caption = StatStopPanel->Caption;
       StatPauseLabel->Repaint();
       //Initialisation ProgressBar
       ChangeSpeedButton->Enabled = true;
       Min = 0;
       Max = DissolutionThread->Plane;
       Position= DissolutionThread->DeletedAtom;
       DissolutionThread->Finish = false;
       //поехали
       DissolutionThread->Suspended = false;
       Timer->Enabled = true;
       DissolutionTime = DissolutionTime.CurrentDateTime() -
     				   DissolutionThread->StartTime - LastPauseTime;
       PauseTime = 0;
       DrowProgress();
      }
      //EnabledPaint = true;
     }
     else
     {
      StatStopPanel->Caption = "Pause";
      StatPauseLabel->Enabled = StatStopPanel->Enabled;
      StatPauseLabel->Caption = StatStopPanel->Caption;
      StatPauseLabel->Repaint();
      //Initialisation ProgressBar
      Min = 0;
      Max = DissolutionThread->Plane;
      Position= DissolutionThread->DeletedAtom;
      DissolutionThread->Finish = false;
      DrowProgress();
      //поехали
      DissolutionThread->Suspended = false;
      Timer->Enabled = true;
      DissolutionTime = DissolutionTime.CurrentDateTime() -
     				   DissolutionThread->StartTime - LastPauseTime;
      PauseTime += LastPauseTime.CurrentDateTime() - LastPauseTime;
     }
    }
    else
    {
     StatStopPanel->Caption = "Start";
     StatPauseLabel->Enabled = StatStopPanel->Enabled;
     StatPauseLabel->Caption = StatStopPanel->Caption;
     StatPauseLabel->Repaint();
     DissolutionThread->EnterCS();
     DissolutionThread->Suspended = true;
     DissolutionThread->LeaveCS();
     TimerTimer(NULL);
     //DrowProgress();
     Timer->Enabled = false;
     LastPauseTime = LastPauseTime.CurrentDateTime();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ChangeSpeedButtonClick(TObject *Sender)
{
	EnabledPaint = false;
    bool Masked;
    if(DissolutionParamsSet)
    {
     SurfaceForm->InitForm(ifContinue, m_DssParams);
     Masked = m_DssParams.Masked;
    }
    else
    {
     SurfaceForm->InitForm(ifNew, m_DssParams);
     Masked = false;
    }
    if(SurfaceForm->ShowModal() != mrCancel)//mrOk
    {
	 //Изменить
	 //Параметры
     if((DissolutionParamsSet)&&(DissolutionThread != NULL))
     {
      StatusBar1->Panels->Items[1]->Text = "Изменение параметров...";


	  bool bNeedRendering = false;

	  //если изменился набор вероятностей, то перерендерить
	  if(DissolutionThread->SP.GetInterface() != NULL && m_DssParams.SP.GetInterface()!=NULL)
	  {
		if(DissolutionThread->SP.GetInterface()->GetGlobalData().GetProbSetIdString()
		!=        m_DssParams.SP.GetInterface()->GetGlobalData().GetProbSetIdString()
		  )
		{
		 bNeedRendering = true;
		}
	  }

	  //если изменилось поведение нудаляемых атомов, то перерендерить
	  if(DissolutionThread->Algoritm.m_nNoDelAtomsBehaviour != m_DssParams.m_Algoritm.m_nNoDelAtomsBehaviour)
	  {
	   bNeedRendering = true;
	  }

	  DissolutionThread->SP = m_DssParams.SP;
	  DissolutionThread->Algoritm = m_DssParams.m_Algoritm;

	  if(bNeedRendering == true)
	  {
	   DissolutionThread->RenderingKindAtomByNewAlgoritm();
	  }

	  if(DissolutionThread->DeletedAtom > m_DssParams.Plane)
        DissolutionThread->Plane = DissolutionThread->DeletedAtom + m_DssParams.Plane;
      else DissolutionThread->Plane += m_DssParams.Plane;
      //DsslExpPrprt->N1Probability = DissolutionThread->W1;
      //DsslExpPrprt->N2Probability = DissolutionThread->W2;
      //DsslExpPrprt->N3Probability = DissolutionThread->W3;
      ///
      //тут вылетает
      DsslExpPrprt->SP = DissolutionThread->SP;
      if(Masked &&(!m_DssParams.Masked))
      {
       DissolutionThread->DeleteMaskedAtoms();
      }
      if(m_DssParams.Masked == false)
      {
       DsslExpPrprt->m_vMask.clear();
      }
      else
      {
       DsslExpPrprt->m_vMask.clear();
       DsslExpPrprt->m_vMask = m_DssParams.m_vMask;

       if(SurfaceForm->MaskChanged)
       {
        DissolutionThread->RenderingNewMask(DsslExpPrprt->m_vMask);
       }
      }

      //DsslExpPrprt->W = DissolutionThread->Width;
      //DsslExpPrprt->H = DissolutionThread->Height;
      Min = 0;
      Max = DissolutionThread->Plane;
      Position= DissolutionThread->DeletedAtom;
      if(DissolutionThread->Plane > DissolutionThread->DeletedAtom) DissolutionThread->Finish = false;
      DrowProgress();
     }
     ChangeSpeedButton->Caption = "Изменить";
	 DissolutionParamsSet = true;
     StatStopPanel->Enabled = DissolutionParamsSet;
     StatStopPanel->Enabled = true;
     StatPauseLabel->Enabled = StatStopPanel->Enabled;
     StatPauseLabel->Caption = StatStopPanel->Caption;
     StatPauseLabel->Repaint();
    }
    if(SurfaceForm->ModalResult == mrYes)//Start button
    {
     Repaint();
     if(DissolutionThread == NULL) StatStopPanelClick(Sender);
     else if(DissolutionThread->Suspended == true) StatStopPanelClick(Sender);
    }
    EnabledPaint = true;
/*      bool Masked = m_DssParams.Masked;
      EnabledPaint = false;
      if(SurfaceForm->ShowModal() == mrOk)
      {
       Repaint();
       //StatusBar1->Panels->Items[1]->Text = "Инициализация...";
       //DissolutionThread = new TDissolutionThread(true);
       DissolutionThread->W1 = m_DssParams.W1;
       DissolutionThread->W2 = m_DssParams.W2;
       DissolutionThread->W3 = m_DssParams.W3;
       DissolutionThread->Plane += m_DssParams.Plane;
       ExperimentProperty->N1Probability = DissolutionThread->W1;
       ExperimentProperty->N2Probability = DissolutionThread->W2;
       ExperimentProperty->N3Probability = DissolutionThread->W3;
       if(Masked &&(!m_DssParams.Masked))
       {
        DissolutionThread->DeleteMaskedAtoms();
       }
       if(m_DssParams.Masked == false)
       {
        //DissolutionThread->InitIdealSmoothSurface(m_DssParams.X,
        //										   m_DssParams.Y);
        if(ExperimentProperty->CountMask !=0) delete ExperimentProperty->MasksArray;
        ExperimentProperty->CountMask = 0;
       }
       else
       {
        //DissolutionThread->InitIdealMaskedSurface(m_DssParams.X,
       	//										  m_DssParams.Y,
        //            							  m_DssParams.MasksList);
        if(ExperimentProperty->CountMask !=0) delete ExperimentProperty->MasksArray;
        ExperimentProperty->CountMask = m_DssParams.MasksList->Count;
        ExperimentProperty->MasksArray = new TMask[ExperimentProperty->CountMask];
        for(int i = 0; i < ExperimentProperty->CountMask; i++)
        {
         //((TMask*)(ExperimentProperty->MasksArray+i))->CopyMask(
         ExperimentProperty->MasksArray[i].CopyMask(
         	(TMask*)(m_DssParams.MasksList->Items[i]));
        }
       }
       ExperimentProperty->W = DissolutionThread->Width;
       ExperimentProperty->H = DissolutionThread->Height;
       //ExperimentProperty->Description = "";
       //StatStopPanel->Caption = "Pause";
       //Initialisation ProgressBar
       Min = 0;
       Max = DissolutionThread->Plane;
       Position= DissolutionThread->DeletedAtom;
       if(DissolutionThread->Plane > DissolutionThread->DeletedAtom) DissolutionThread->Finish = false;
       DrowProgress();
      }
       EnabledPaint = true;
*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AppOrientationSpeedButtonClick(TObject *Sender)
{
	//ApplyOrientaton = true;
    if((IsSurfaceGen == true)||(IsListGen == true))
    {
     GLfloat ProjectionMatrix[4][4], *pMatix;
     pMatix = (GLfloat*)ProjectionMatrix;
     bool AnaliseitView = AnalizViewSpeedButton->Down;
     bool LeftNormal = LeftRightSpeedButton->Down;
     bool ShowClipPlane = ShowClipPlaneSpeedButton->Down;

     if(AnaliseitView == true && ShowClipPlane == true)
     {
      glPushMatrix();
      //glScalef(Scale,Scale,Scale);
      glTranslated(SpeedXT + CenterXT,
                   SpeedYT + CenterYT,
                   SpeedZT + CenterZT);
      //glTranslated(SpeedXT, SpeedYT, SpeedZT);
      glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);
      glPopMatrix();

      GLfloat PM00 = ProjectionMatrix[0][0];
      GLfloat PM10 = ProjectionMatrix[1][0];
      GLfloat PM20 = ProjectionMatrix[2][0];
      GLfloat PM30 = ProjectionMatrix[3][0];
      if(LeftNormal)
      {
       PM00 = -PM00;
       PM10 = -PM10;
       PM20 = -PM20;
       PM30 = -PM30;
      }
      TClipPlane Cp;

      Cp.FirstRowPM[0] = PM00;
      Cp.FirstRowPM[1] = PM10;
      Cp.FirstRowPM[2] = PM20;
      Cp.FirstRowPM[3] = PM30;

      m_CurrOrn.m_vClipPlane.push_back(Cp);//добавить текущую обрезку в массив обрезок
      AppClipPlane(Cp);
     }

     /*
     int i,j,k;
     TAtom3d* A3d;
     //атомы
     for(j = 0; j < NumberAtoms; j++)
     {
      A3d = &Atoms[j];
      if(AnaliseitView)
      {
       if((A3d->Type & SELECT_MASK_INVISIBLE) == 0)//  1 - невидим, 0 - видм
       {
        if(ShowClipPlane)
        {
         if((PM00*A3d->Coord[0] + PM10*A3d->Coord[1] - PM20*A3d->Coord[2] + PM30)>0)
         {
          A3d->Type = A3d->Type | (char)SELECT_MASK_INVISIBLE;
         }
        }
       }
      }
     }

     GLint CoordBegin[3], CoordEnd[3];
     //связи
     for(j = 0; j < NumberLinksFromAtoms; j++)
     {
      for(k = 0; k < 3; k++)
      {
       CoordBegin[k] = LinksFromAtoms[0][j].Coord[k];
       CoordEnd[k] = LinksFromAtoms[1][j].Coord[k];
      }
      if(AnaliseitView)
      {
       if((LinksFromAtoms[1][j].Type & SELECT_MASK_INVISIBLE) == 0)//  1 - невидим, 0 - видм
       {
        if(ShowClipPlane)
        {
         if(((PM00*CoordBegin[0] + PM10*CoordBegin[1] - PM20*CoordBegin[2] + PM30)>0)&&
            ((PM00*CoordEnd[0] + PM10*CoordEnd[1] - PM20*CoordEnd[2] + PM30)>0))
         {
          LinksFromAtoms[1][j].Type = LinksFromAtoms[1][j].Type | (char)SELECT_MASK_INVISIBLE;
         }
        }
       }
      }
     }
     */
     FormPaint(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AppClipPlane(const TClipPlane &cp)
{
     GLfloat PM00 = cp.FirstRowPM[0];
     GLfloat PM10 = cp.FirstRowPM[1];
     GLfloat PM20 = cp.FirstRowPM[2];
     GLfloat PM30 = cp.FirstRowPM[3];

     int i,j,k;
     TAtom3d* A3d;
     //атомы
     for(j = 0; j < NumberAtoms; j++)
     {
      A3d = &Atoms[j];
      if((A3d->Type & SELECT_MASK_INVISIBLE) == 0)//  1 - невидим, 0 - видм
      {
       if((PM00*A3d->Coord[0] + PM10*A3d->Coord[1] - PM20*A3d->Coord[2] + PM30)>0)
       {
        A3d->Type = A3d->Type | (char)SELECT_MASK_INVISIBLE;
       }
      }
     }

     GLint CoordBegin[3], CoordEnd[3];
     //связи
     for(j = 0; j < NumberLinksFromAtoms; j++)
     {
      for(k = 0; k < 3; k++)
      {
       CoordBegin[k] = LinksFromAtoms[0][j].Coord[k];
       CoordEnd[k] = LinksFromAtoms[1][j].Coord[k];
      }
      /*
      if((LinksFromAtoms[1][j].Type & SELECT_MASK_INVISIBLE) == 0)//  1 - невидим, 0 - видм
      {
       if(((PM00*CoordBegin[0] + PM10*CoordBegin[1] - PM20*CoordBegin[2] + PM30)>0)&&
          ((PM00*CoordEnd[0] + PM10*CoordEnd[1] - PM20*CoordEnd[2] + PM30)>0))
       {
        LinksFromAtoms[1][j].Type = LinksFromAtoms[1][j].Type | (char)SELECT_MASK_INVISIBLE;
       }
      }
      */
      if(((PM00*CoordBegin[0] + PM10*CoordBegin[1] - PM20*CoordBegin[2] + PM30)>0))
      {
        LinksFromAtoms[0][j].Type = LinksFromAtoms[0][j].Type | (char)SELECT_MASK_INVISIBLE;
      }
      if(((PM00*CoordEnd[0] + PM10*CoordEnd[1] - PM20*CoordEnd[2] + PM30)>0))
      {
        LinksFromAtoms[1][j].Type = LinksFromAtoms[1][j].Type | (char)SELECT_MASK_INVISIBLE;
      }
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearInvisibleBitSpeedButtonClick(TObject *Sender)
{
	//ClearVisibledBit = true;
    if((IsSurfaceGen == true)||(IsListGen == true))
    {
     //GLfloat ProjectionMatrix[4][4], *pMatix;
     //pMatix = (GLfloat*)ProjectionMatrix;
     bool AnaliseitView = AnalizViewSpeedButton->Down;
     //bool LeftNormal = LeftRightSpeedButton->Down;
     //bool ShowClipPlane = ShowClipPlaneSpeedButton->Down;
     /*
     glPushMatrix();
     //glScalef(Scale,Scale,Scale);
     glTranslated(SpeedXT, SpeedYT, SpeedZT);
     glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);
     glPopMatrix();

     GLfloat PM00 = ProjectionMatrix[0][0];
     GLfloat PM10 = ProjectionMatrix[1][0];
     GLfloat PM20 = ProjectionMatrix[2][0];
     GLfloat PM30 = ProjectionMatrix[3][0];
     if(LeftNormal)
     {
      PM00 = -PM00;
      PM10 = -PM10;
      PM20 = -PM20;
      PM30 = -PM30;
     }
     */
     if(AnaliseitView)
     {
      m_CurrOrn.m_vClipPlane.clear();//удаление плоскостей обрезания
      ClearClip();
     }
     /*
     int i,j,k;
     TAtom3d* A3d;
     for(j = 0; j < NumberAtoms; j++)
     {
      A3d = &Atoms[j];
      if(AnaliseitView)
      {
       //if((A3d->Type & SELECT_MASK_INVISIBLE) == 1)//  1 - невидим, 0 - видм
        A3d->Type = A3d->Type & (char)~SELECT_MASK_INVISIBLE;
      }
     }

     GLint CoordBegin[3], CoordEnd[3];
     //маскируемые
     for(j = 0; j < NumberLinksFromAtoms; j++)
     {
      if(AnaliseitView)
      {
       //if((LinksFromNoDeleteAtoms[1][j].Type & SELECT_MASK_INVISIBLE) == 1)//  1 - невидим, 0 - видм
        LinksFromAtoms[1][j].Type = LinksFromAtoms[1][j].Type & (char)~SELECT_MASK_INVISIBLE;
      }
     }
     */
     FormPaint(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearClip(void)
{//очистка обрезки
     int i,j,k;
     TAtom3d* A3d;
     for(j = 0; j < NumberAtoms; j++)
     {
      A3d = &Atoms[j];
      A3d->Type = A3d->Type & (char)~SELECT_MASK_INVISIBLE;
     }

     GLint CoordBegin[3], CoordEnd[3];
     //маскируемые
     for(j = 0; j < NumberLinksFromAtoms; j++)
     {
      LinksFromAtoms[0][j].Type = LinksFromAtoms[0][j].Type & (char)~SELECT_MASK_INVISIBLE;
      LinksFromAtoms[1][j].Type = LinksFromAtoms[1][j].Type & (char)~SELECT_MASK_INVISIBLE;
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AtomsColorsComboBoxChange(TObject *Sender)
{
//      SelectTypeColorR = 0.7;
//      SelectTypeColorG = 0.5;
//      SelectTypeColorB = 1.0;
    SelectTypeColorR = 1.0;
    SelectTypeColorG = 0.4;
    SelectTypeColorB = 1.0;
    switch(AtomsColorsComboBox->ItemIndex)
    {
     default:
     case 0://Стандартный набор
      AtomsClipPlaneBrigthness = 0.7;
      OneLinksAtomColorR = 1;
      OneLinksAtomColorG = 1;
      OneLinksAtomColorB = 1;
      TwoLinksAtomColorR = 1;
      TwoLinksAtomColorG = 1;
      TwoLinksAtomColorB = 0;
      ThreeLinksAtomColorR = 0;
      ThreeLinksAtomColorG = 0;
      ThreeLinksAtomColorB = 1;
      FourLinksAtomColorR = 0;
      FourLinksAtomColorG = 1;
      FourLinksAtomColorB = 0;
      NoDeleteAtomColorR = 1;
      NoDeleteAtomColorG = 0;
      NoDeleteAtomColorB = 0;
      LinkNoAtomColorR = 1;//1
      LinkNoAtomColorG = 1;//1
      LinkNoAtomColorB = 1;//1
      LinkOneTwoLinksAtomColorR = 1;
      LinkOneTwoLinksAtomColorG = 1;
      LinkOneTwoLinksAtomColorB = 0;
      LinkThreeLinksAtomColorR = 0;
      LinkThreeLinksAtomColorG = 0;
      LinkThreeLinksAtomColorB = 1;
      LinkFourLinksAtomColorR = 0;
      LinkFourLinksAtomColorG = 1;
      LinkFourLinksAtomColorB = 0;
      LinkNoDeleteAtomColorR = 1;
      LinkNoDeleteAtomColorG = 0;
      LinkNoDeleteAtomColorB = 0;
     break;
     case 1://Полные цвета
      AtomsClipPlaneBrigthness = 0.7;
      OneLinksAtomColorR = 0;
      OneLinksAtomColorG = 1;
      OneLinksAtomColorB = 0;
      TwoLinksAtomColorR = 0;
      TwoLinksAtomColorG = 0;
      TwoLinksAtomColorB = 1;
      ThreeLinksAtomColorR = 1;
      ThreeLinksAtomColorG = 0;
      ThreeLinksAtomColorB = 0;
      FourLinksAtomColorR = 1;
      FourLinksAtomColorG = 1;
      FourLinksAtomColorB = 1;
      NoDeleteAtomColorR = 1;
      NoDeleteAtomColorG = 1;
      NoDeleteAtomColorB = 1;
      LinkNoAtomColorR = 1;//1
      LinkNoAtomColorG = 1;//1
      LinkNoAtomColorB = 1;//1
      LinkOneTwoLinksAtomColorR = 1;
      LinkOneTwoLinksAtomColorG = 1;
      LinkOneTwoLinksAtomColorB = 1;
      LinkThreeLinksAtomColorR = 1;
      LinkThreeLinksAtomColorG = 1;
      LinkThreeLinksAtomColorB = 1;
      LinkFourLinksAtomColorR = 1;
      LinkFourLinksAtomColorG = 1;
      LinkFourLinksAtomColorB = 1;
      LinkNoDeleteAtomColorR = 1;
      LinkNoDeleteAtomColorG = 1;
      LinkNoDeleteAtomColorB = 1;
     break;
     case 2://Черно-белая печать
      AtomsClipPlaneBrigthness = 0.7;
      OneLinksAtomColorR = 1;
      OneLinksAtomColorG = 1;
      OneLinksAtomColorB = 1;
      TwoLinksAtomColorR = 1;
      TwoLinksAtomColorG = 1;
      TwoLinksAtomColorB = 1;
      ThreeLinksAtomColorR = 1;
      ThreeLinksAtomColorG = 1;
      ThreeLinksAtomColorB = 1;
      FourLinksAtomColorR = 1;
      FourLinksAtomColorG = 1;
      FourLinksAtomColorB = 1;
      NoDeleteAtomColorR = 1;
      NoDeleteAtomColorG = 1;
      NoDeleteAtomColorB = 1;
      LinkNoAtomColorR = 1;//1
      LinkNoAtomColorG = 1;//1
      LinkNoAtomColorB = 1;//1
      LinkOneTwoLinksAtomColorR = 1;
      LinkOneTwoLinksAtomColorG = 1;
      LinkOneTwoLinksAtomColorB = 1;
      LinkThreeLinksAtomColorR = 1;
      LinkThreeLinksAtomColorG = 1;
      LinkThreeLinksAtomColorB = 1;
      LinkFourLinksAtomColorR = 1;
      LinkFourLinksAtomColorG = 1;
      LinkFourLinksAtomColorB = 1;
      LinkNoDeleteAtomColorR = 1;
      LinkNoDeleteAtomColorG = 1;
      LinkNoDeleteAtomColorB = 1;
     break;
     case 3://Цветная  печать 1
      AtomsClipPlaneBrigthness = 0.7;
      OneLinksAtomColorR = 1;
      OneLinksAtomColorG = 0;
      OneLinksAtomColorB = 1;
      TwoLinksAtomColorR = 0.5;
      TwoLinksAtomColorG = 0.5;
      TwoLinksAtomColorB = 0.5;
      ThreeLinksAtomColorR = 1;
      ThreeLinksAtomColorG = 1;
      ThreeLinksAtomColorB = 0;
      FourLinksAtomColorR = 1;
      FourLinksAtomColorG = 1;
      FourLinksAtomColorB = 0;
      NoDeleteAtomColorR = 1;
      NoDeleteAtomColorG = 1;
      NoDeleteAtomColorB = 1;
      LinkNoAtomColorR = 1;//1
      LinkNoAtomColorG = 0;//1
      LinkNoAtomColorB = 0;//1
      LinkOneTwoLinksAtomColorR = TwoLinksAtomColorR;
      LinkOneTwoLinksAtomColorG = TwoLinksAtomColorG;
      LinkOneTwoLinksAtomColorB = TwoLinksAtomColorB;
      LinkThreeLinksAtomColorR = ThreeLinksAtomColorR;
      LinkThreeLinksAtomColorG = ThreeLinksAtomColorG;
      LinkThreeLinksAtomColorB = ThreeLinksAtomColorB;
      LinkFourLinksAtomColorR = NoDeleteAtomColorR;
      LinkFourLinksAtomColorG = NoDeleteAtomColorG;
      LinkFourLinksAtomColorB = NoDeleteAtomColorB;
      LinkNoDeleteAtomColorR = NoDeleteAtomColorR;
      LinkNoDeleteAtomColorG = NoDeleteAtomColorG;
      LinkNoDeleteAtomColorB = NoDeleteAtomColorB;
     break;
     case 4://Цветная  печать 2
     break;
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DepthCheckBoxClick(TObject *Sender)
{
    Depth = DepthCheckBox->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AtomSizeUpSpeedButtonClick(TObject *Sender)
{
    AtomSize += 0.1;
    if(AtomSize < 1.0e-4) AtomSize = 0;
    AtomSizeLabel->Caption = "Размер атома x " + AnsiString(AtomSize);
    FormPaint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AtomSizeDownSpeedButtonClick(TObject *Sender)
{
    AtomSize -= 0.1;
    if(AtomSize < 1.0e-4) AtomSize = 0;
    AtomSizeLabel->Caption = "Размер атома x " + AnsiString(AtomSize);
    FormPaint(NULL);
}
//---------------------------------------------------------------------------
double inline __fastcall TMainForm::AtomFromScale(GLdouble Scl)
{
    return Scl*AtomSize;
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::GetCubeAtoms(TAtom3d** A3d)
{
    int Number;
	//SetZinZmax();
    int i,j,k;
    int x1,y1;
    int x2,y2;

    Number = 0;
    for(k = 0; k < (signed)m_DssParams.Z; k++)
    {
     for(j = 0; j < (signed)m_DssParams.Y; j++)
     {
      for(i = 0; i < (signed)m_DssParams.X; i++)
      {
       Number++;
       Number++;
      }
      if(k%4==0)
      {
       Number++;
       if((unsigned)(j+1) >= m_DssParams.Y)
       Number++;
      }
      if(k%4==2)
       Number++;
     }
     if(k%4==0)
     {
      for(i = 0; i < (signed)m_DssParams.X; i++)
       Number++;
     }
     if(k%4==2)
     {
      for(i = 0; i < (signed)m_DssParams.X; i++)
       Number++;
     }
    }


    *A3d = new TAtom3d[Number];
    Number = 0;

    for(k = 0; k < (signed)m_DssParams.Z; k++)
    {
     for(j = 0; j < (signed)m_DssParams.Y; j++)
     {
      for(i = 0; i < (signed)m_DssParams.X; i++)
      {
       switch(k % 4)
       {
        case 0:
         x1 = i*4;
         y1 = j*4;
         x2 = i*4 + 2;
         y2 = j*4 + 2;
        break;
        case 1:
         x1 = i*4 + 1;
         y1 = j*4 + 3;
         x2 = i*4 + 3;
         y2 = j*4 + 1;
        break;
        case 2:
         x1 = i*4 + 0;
         y1 = j*4 + 2;
         x2 = i*4 + 2;
         y2 = j*4 + 0;
        break;
        case 3:
         x1 = i*4 + 1;
         y1 = j*4 + 1;
         x2 = i*4 + 3;
         y2 = j*4 + 3;
        break;
       }
        //DrowAtom(x1,y1,-k);
         Number++;
          ((TAtom3d*)(*A3d+Number-1))->Coord[0] = x1;
          ((TAtom3d*)(*A3d+Number-1))->Coord[1] = y1;
          ((TAtom3d*)(*A3d+Number-1))->Coord[2] = -k;
          ((TAtom3d*)(*A3d+Number-1))->Type = 1;//GetTypeAtom(&BAC);// его тип
        //DrowAtom(x2,y2,-k);
         Number++;
          ((TAtom3d*)(*A3d+Number-1))->Coord[0] = x2;
          ((TAtom3d*)(*A3d+Number-1))->Coord[1] = y2;
          ((TAtom3d*)(*A3d+Number-1))->Coord[2] = -k;
          ((TAtom3d*)(*A3d+Number-1))->Type = 1;//GetTypeAtom(&BAC);// его тип
      }
      if(k%4==0)
      {
       //DrowAtom(i*4,j*4,-k);
        Number++;
         ((TAtom3d*)(*A3d+Number-1))->Coord[0] = i*4;
         ((TAtom3d*)(*A3d+Number-1))->Coord[1] = j*4;
         ((TAtom3d*)(*A3d+Number-1))->Coord[2] = -k;
         ((TAtom3d*)(*A3d+Number-1))->Type = 1;//GetTypeAtom(&BAC);// его тип
       if((unsigned)(j+1) >= m_DssParams.Y)
       {
        //DrowAtom(i*4,(j+1)*4,-k);
        Number++;
         ((TAtom3d*)(*A3d+Number-1))->Coord[0] = i*4;
         ((TAtom3d*)(*A3d+Number-1))->Coord[1] = (j+1)*4;
         ((TAtom3d*)(*A3d+Number-1))->Coord[2] = -k;
         ((TAtom3d*)(*A3d+Number-1))->Type = 1;//GetTypeAtom(&BAC);// его тип
       }
      }
      if(k%4==2)
      {
       //DrowAtom(i*4,j*4+2, -k);
        Number++;
         ((TAtom3d*)(*A3d+Number-1))->Coord[0] = i*4;
         ((TAtom3d*)(*A3d+Number-1))->Coord[1] = j*4+2;
         ((TAtom3d*)(*A3d+Number-1))->Coord[2] = -k;
         ((TAtom3d*)(*A3d+Number-1))->Type = 1;//GetTypeAtom(&BAC);// его тип
      }
     }
     if(k%4==0)
     {
      for(i = 0; i < (signed)m_DssParams.X; i++)
      {
       //DrowAtom(i*4,j*4,-k);
        Number++;
         ((TAtom3d*)(*A3d+Number-1))->Coord[0] = i*4;
         ((TAtom3d*)(*A3d+Number-1))->Coord[1] = j*4;
         ((TAtom3d*)(*A3d+Number-1))->Coord[2] = -k;
         ((TAtom3d*)(*A3d+Number-1))->Type = 1;//GetTypeAtom(&BAC);// его тип
      }
     }
     if(k%4==2)
     {
      for(i = 0; i < (signed)m_DssParams.X; i++)
 	  {
       //DrowAtom(i*4+2,j*4, -k);
        Number++;
         ((TAtom3d*)(*A3d+Number-1))->Coord[0] = i*4+2;
         ((TAtom3d*)(*A3d+Number-1))->Coord[1] = j*4;
         ((TAtom3d*)(*A3d+Number-1))->Coord[2] = -k;
         ((TAtom3d*)(*A3d+Number-1))->Type = 1;//GetTypeAtom(&BAC);// его тип
      }
     }
    }

    return Number;
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::GetLinksFromCubeAtoms(TAtom3d** A3dBegin, TAtom3d** A3dEnd)
{
    int Number;
    int i,j,k;
    int x1,y1;
    int x2,y2;
    int x3,y3;
    int x4,y4;
    int x5,y5;
    int x6,y6;
    int x7,y7;
    int x8,y8;
    int imax,jmax;

    Number = 0;
    imax = m_DssParams.X;
    jmax = m_DssParams.Y;
    for(k = 0; k < (signed)m_DssParams.Z-1; k++)
    {
     for(j = 0; j < (signed)m_DssParams.Y; j++)
     {
      for(i = 0; i < (signed)m_DssParams.X; i++)
      {
       Number++;
       Number++;

       Number++;
       Number++;
      }
     }
    }

    *A3dBegin = new TAtom3d[Number];
    *A3dEnd = new TAtom3d[Number];
    Number = 0;

    for(k = 0; k < (signed)m_DssParams.Z-1; k++)
    {
     for(j = 0; j < (signed)m_DssParams.Y; j++)
     {
      for(i = 0; i < (signed)m_DssParams.X; i++)
      {
       switch(k % 4)
       {
        case 0:
         x1 = i*4;
         y1 = ((jmax+j-1)%jmax+1)*4;
         x3 = ((imax+i-1)%imax+1)*4;
         y3 = j*4;

         x2 = x4 = i*4 + 2;
         y2 = y4 = j*4 + 2;
        break;
        case 1:
         x1 = x3 = i*4 + 1;
         y1 = y3 = j*4 + 3;
         x2 = x4 = i*4 + 3;
         y2 = y4 = j*4 + 1;
        break;
        case 2:
         x1 = i*4 + 0;
         x3 = ((imax+i-1)%imax+1)*4 + 0;
         y1 = y3 = j*4 + 2;
         x2 = x4 = i*4 + 2;
         y2 = ((jmax+j-1)%jmax+1)*4 + 0;
         y4 = j*4 + 0;
        break;
        case 3:
         x1 = x3 = i*4 + 1;
         y1 = y3 = j*4 + 1;
         x2 = x4 = i*4 + 3;
         y2 = y4 = j*4 + 3;
        break;
       }
       switch(k % 2)
       {
        case 0:
         x5 = x1 + 1;
         y5 = y1 - 1;
         x6 = x2 + 1;
         y6 = y2 - 1;

         x7 = x3 - 1;
         y7 = y3 + 1;
         x8 = x4 - 1;
         y8 = y4 + 1;
        break;
        case 1:
         x5 = x1 - 1;
         y5 = y1 - 1;
         x6 = x2 - 1;
         y6 = y2 - 1;

         x7 = x3 + 1;
         y7 = y3 + 1;
         x8 = x4 + 1;
         y8 = y4 + 1;
        break;
       }
       //DrowLink(x1,y1,-k, x5,y5,-(k+1));
       ((TAtom3d*)(*A3dBegin+Number))->Coord[0] = x1;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[0] = x5;
       ((TAtom3d*)(*A3dBegin+Number))->Coord[1] = y1;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[1] = y5;
       ((TAtom3d*)(*A3dBegin+Number))->Coord[2] = -k;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[2] = -(k+1);

       ((TAtom3d*)(*A3dBegin+Number))->Type = 5;
       ((TAtom3d*)(*A3dEnd+Number))->Type = 5;
       Number++;

       //DrowLink(x3,y3,-k, x7,y7,-(k+1));
       ((TAtom3d*)(*A3dBegin+Number))->Coord[0] = x3;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[0] = x7;
       ((TAtom3d*)(*A3dBegin+Number))->Coord[1] = y3;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[1] = y7;
       ((TAtom3d*)(*A3dBegin+Number))->Coord[2] = -k;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[2] = -(k+1);

       ((TAtom3d*)(*A3dBegin+Number))->Type = 5;
       ((TAtom3d*)(*A3dEnd+Number))->Type = 5;
       Number++;


       //DrowLink(x2,y2,-k, x6,y6,-(k+1));
       ((TAtom3d*)(*A3dBegin+Number))->Coord[0] = x2;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[0] = x6;
       ((TAtom3d*)(*A3dBegin+Number))->Coord[1] = y2;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[1] = y6;
       ((TAtom3d*)(*A3dBegin+Number))->Coord[2] = -k;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[2] = -(k+1);

       ((TAtom3d*)(*A3dBegin+Number))->Type = 5;
       ((TAtom3d*)(*A3dEnd+Number))->Type = 5;
       Number++;

       //DrowLink(x4,y4,-k, x8,y8,-(k+1));
       ((TAtom3d*)(*A3dBegin+Number))->Coord[0] = x4;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[0] = x8;
       ((TAtom3d*)(*A3dBegin+Number))->Coord[1] = y4;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[1] = y8;
       ((TAtom3d*)(*A3dBegin+Number))->Coord[2] = -k;
       ((TAtom3d*)(*A3dEnd+Number))->Coord[2] = -(k+1);

       ((TAtom3d*)(*A3dBegin+Number))->Type = 5;
       ((TAtom3d*)(*A3dEnd+Number))->Type = 5;
       Number++;
      }
     }
    }
    return Number;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ListsSpeedButtonClick(TObject *Sender)
{
    DefectPageScroller->Visible = ListsSpeedButton->Down;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DelHoldSpeedButtonClick(TObject *Sender)
{
    DelCoolBar->Visible = DelHoldSpeedButton->Down;
    CoordPageScroller->Visible =true;
    DefectPageScroller->Visible =false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DelHoldSufAtomPriview(void)
{
    //Tpoint3d MousePoint;
    if(Initialiseded)
    {
    double x,y,z,w,h,x1,y1,z1,l,m,n,a,b,c;
    double Model_MATRIX[4][4];
    double Project_MATRIX[4][4];
    int i,j,k;
    TAtom3d *a3dTmp, *a3dSelected = NULL;
    double Rayting,delta,deltaSel,Rmod;
    //double RaytingSel = 0;
	deltaSel = 1.79e308;
    //MousePoint
    //XPort,YPort,Near,Far
    w = ScreenPanel->ClientWidth;
    h = ScreenPanel->ClientHeight;
    //x = ((double)ScreenPanelMousePoint.x)*2*XPort/w - XPort;
    //y = ((double)ScreenPanelMousePoint.y)*2*YPort/h - YPort;
    x = ((double)ScreenPanelMousePoint.x)*2/w - 1;
    y = ((double)ScreenPanelMousePoint.y)*2/h - 1;
    y = -y;
    z = 0;//Near;
 	glPushMatrix();
    //glScalef(Scale,Scale,Scale);
    //glTranslated(SpeedXT, SpeedYT, SpeedZT);
      glTranslated(SpeedXT + CenterXT,
                   SpeedYT + CenterYT,
                   SpeedZT + CenterZT);
    glGetDoublev(GL_MODELVIEW_MATRIX,(GLdouble*)Model_MATRIX);
 	glPopMatrix();
    glGetDoublev(GL_PROJECTION_MATRIX,(GLdouble*)Project_MATRIX);
    TMatrix mModel((double*)Model_MATRIX);
    TMatrix mProject((double*)Project_MATRIX);
    TMatrix mAllForward = mModel * mProject;
    TMatrix mAllBack = mAllForward.BackMatrix332();
    TMatrix mTst = mAllForward * mAllBack;
    //pnt3d = mAllBack.Transpose() * pnt3d;
    TPoint3d pnt3d;
    pnt3d.x = x;
    pnt3d.y = y;
    pnt3d.z = z;
    //pnt3d = mAllBack * pnt3d;
    pnt3d = mAllBack.Transpose() * pnt3d;
    x1 = pnt3d.x;
    y1 = pnt3d.y;
    z1 = pnt3d.z;
    //pnt3d.x = 0;
    //pnt3d.y = 0;
    //pnt3d.z = 1;
    //pnt3d = mAllBack * pnt3d;
    //l = pnt3d.x;
    //m = pnt3d.y;
    //n = pnt3d.z;
    TMatrix NN;
    NN = NN*0;
    NN.Item[2][0] = 1;
    NN = mAllBack.Transpose() * NN;
    l = NN.Item[0][0];
    m = NN.Item[1][0];
    n = NN.Item[2][0];
    //Rmod = l*l + m*m + n*n;
    Rmod = sqrt(l*l + m*m + n*n);

    for(j = 0; j < NumberAtoms; j++)
    {
     a3dTmp = &Atoms[j];
     //a3dTmp = &(KindAtoms[i][j]);
     a3dTmp->Type &= ~(SELECT_MASK_SELECT);
     a = a3dTmp->Coord[0];
     b = a3dTmp->Coord[1];
     c = -a3dTmp->Coord[2];
     try
     {
      delta = sqrt(pow(a-x1,2.0)+pow(b-y1,2.0)+pow(c-z1,2.0));
      delta = delta*sqrt(1-pow(((a-x1)*l+(b-y1)*m+(c-z1)*n)/(delta*Rmod),2.0));
      if(delta < 1.0)
      {
       if(deltaSel > delta)
       {
        deltaSel = delta;
        a3dSelected = a3dTmp;
       }
      }
     }
     catch(...)
     {
	  //delta =0;
     }
	}

    if(a3dSelected != NULL)
    {
     a3dSelected->Type |= (SELECT_MASK_SELECT);
	 SetAdjType(a3dSelected->ProbIndex);
    }
    //glOrtho
    //;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DelSufAtom(void)
{
    //;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HoldSufAtom(void)
{
    //;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AtomMouseClick(void)
{
    SelectAtomType = false;

    SelectAtomType = true;

    int i,j;
    TAtom3d* A3d;
    for(j = 0; j < NumberAtoms; j++)
    {
     A3d = &Atoms[j];
     if((A3d->Type & SELECT_MASK_SELECT) == SELECT_MASK_SELECT)
     {
      RecordDelAtomXYZ(A3d);
      return;
     }
    }
    RecordDelAtomXYZ(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RecordDelAtomXYZ(TAtom3d* A3d)
{
    if(A3d!=NULL)
    {
     XEdit->Text = IntToStr(A3d->Coord[0]);
     YEdit->Text = IntToStr(A3d->Coord[1]);
     ZEdit->Text = IntToStr(A3d->Coord[2]);
     A3d->Type = A3d->Type & ~SELECT_MASK_SELECT;
     TShiftState Shift;
     unsigned short Key;
     XEditKeyUp(NULL, Key,Shift);
    }
    else
    {
     XEdit->Text = "";
     YEdit->Text = "";
     ZEdit->Text = "";
    }
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::CheckCoord(bool Msg)
{
    int x;
    int y;
    int z;
    x = StrToIntDef(XEdit->Text, 0x7fffffff);
    if(x == 0x7fffffff)
    {
     if(Msg)
     {
      ShowMessage("Координата X должна быть числом.");
      XEdit->SetFocus();
      //XEdit->SelText = XEdit->Text;
     }
     return false;
    }
    y = StrToIntDef(YEdit->Text, 0x7fffffff);
    if(y == 0x7fffffff)
    {
     if(Msg)
     {
      ShowMessage("Координата Y должна быть числом.");
      YEdit->SetFocus();
      //YEdit->SelText = YEdit->Text;
     }
     return false;
    }
    z = StrToIntDef(ZEdit->Text, 0x7fffffff);
    if(z == 0x7fffffff)
    {
     if(Msg)
     {
      ShowMessage("Координата Z должна быть числом.");
      ZEdit->SetFocus();
      //ZEdit->SelText = ZEdit->Text;
     }
     return false;
    }

    return true;
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::CheckCoordAtom(int x,int y,int z)
{
    bool Existence;
    int xx,yy,zz;
    xx = x;
    yy = y;
    zz = z;
    //if(x<0) x = -x;
    //if(y<0) y = -y;
    //if(z<0) z = -z;
    //x = x%4;
    //y = y%4;
    //z = z%4;
    Existence = false;
    while(x<0) x+=4;
    while(y<0) y+=4;
    while(z<0) z+=4;
    switch(100*(x%4)+10*(y%4)+(z%4))
    {
     case 000:
     case 131:
     case 220:
     case 311:
     case  22:
     case 113:
     case 202:
     case 333:
      Existence = true;
    }
    x = xx;
    y = yy;
    z = zz;
    if(Existence==true)
    {
     if(DissolutionThread!=NULL)
     {
      //if(DissolutionThread->GetTypeAtom(x,y,z)!=0)
      // return true;
      //else return false;
      return DissolutionThread->GetTypeAtom(x,y,z);
     }
     else return -1;
    }
    else return -1;
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::SetStateCoord(void)
{
     if(CheckCoord(false))
     {
      int x;
      int y;
      int z;
      x = StrToIntDef(XEdit->Text, 0x7fffffff);
      y = StrToIntDef(YEdit->Text, 0x7fffffff);
      z = StrToIntDef(ZEdit->Text, 0x7fffffff);
      SelAtom.Type = CheckCoordAtom(x,y,z);
      if(SelAtom.Type < 1)
      {
       //
       //clFuchsia
       //clAqua
       //clLime
       //clLtGray
       //clMaroon
       //clNavy
       //clTeal
       //clSilver
       //clPurple
       //clOlive
       YEdit->Font->Color = clPurple;//clNavy;//clDkGray;
       XEdit->Font->Color = clPurple;//clLtGray;
       ZEdit->Font->Color = clPurple;
      }
      else
      {
       XEdit->Font->Color = clBlack;
       YEdit->Font->Color = clBlack;
       ZEdit->Font->Color = clBlack;
       SelAtom.Coord[0]=x;
       SelAtom.Coord[1]=y;
       SelAtom.Coord[2]=z;
       SelAtom.Type |= SELECT_MASK_SELECT;
       return true;
      }
     }
     else
     {
      int Number;
      Number = StrToIntDef(XEdit->Text, 0x7fffffff);
      if(Number == 0x7fffffff)
      {
       XEdit->Font->Color = clRed;
      }
      else
      {
       XEdit->Font->Color = clBlack;
      }
      Number = StrToIntDef(YEdit->Text, 0x7fffffff);
      if(Number == 0x7fffffff)
      {
       YEdit->Font->Color = clRed;
      }
      else
      {
       YEdit->Font->Color = clBlack;
      }
      Number = StrToIntDef(ZEdit->Text, 0x7fffffff);
      if(Number == 0x7fffffff)
      {
       ZEdit->Font->Color = clRed;
      }
      else
      {
       ZEdit->Font->Color = clBlack;
      }
     }
     SelAtom.Type = 0;
     return false;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMainForm::A3dToStr(TAtom3d *A3d)
{
    AnsiString S;
    S =   "X:" + IntToStr((int)(A3d->Coord[0])) +
        "; Y:" + IntToStr((int)(A3d->Coord[1])) +
        "; Z:" + IntToStr((int)(A3d->Coord[2])) +
        "; T:" + IntToStr((int)((A3d->Type)&0x3f));
    return S;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XEditEnter(TObject *Sender)
{
    KeyPreview = false;
    SetStateCoord();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XEditExit(TObject *Sender)
{
    KeyPreview = true;
    SetStateCoord();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XEditKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 0x0d )
    {
     if(CheckCoord(true))
     {
      int x;
      int y;
      int z;
      x = StrToIntDef(XEdit->Text, 0x7fffffff);
      y = StrToIntDef(YEdit->Text, 0x7fffffff);
      z = StrToIntDef(ZEdit->Text, 0x7fffffff);
      SelAtom.Type = CheckCoordAtom(x,y,z);
      if(SelAtom.Type < 1)
      {
       ShowMessage("Атом с такими координатами не существует.");
       //XEdit->SelText = XEdit->Text;
       //YEdit->SelText = YEdit->Text;
       //ZEdit->SelText = ZEdit->Text;
       SelAtom.Type = 0;
      }
      else
      {
       SelAtom.Coord[0] = x;
       SelAtom.Coord[1] = y;
       SelAtom.Coord[2] = z;
       SelAtom.Type |= SELECT_MASK_SELECT;
      }
     }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XEditKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    SetStateCoord();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DelSpeedButtonClick(TObject *Sender)
{
    if(SetStateCoord() == false)
    {
     WORD Key = 0x0d;
     TShiftState Shift;
     XEditKeyDown(NULL,Key,Shift);
	 return;
    }
	TUndo *Und = new TUndo;
	//Und->UDT = new TUndoDissolutfionThread;
	DissolutionThread->SaveToMem(&Und->UDT);
	Und->i = DelComboBox->Items->Count + HoldComboBox->Items->Count;
	if(DissolutionThread->DeleteAtom((int)StrToInt(XEdit->Text),
									 (int)StrToInt(YEdit->Text),
									 (int)StrToInt(ZEdit->Text)) == true)
	{
	 //DelComboBox->Items->Insert(0,A3dToStr(&SelAtom));
	 DelComboBox->ItemIndex = DelComboBox->Items->AddObject(A3dToStr(&SelAtom),(TObject*)Und);
	 SelAtom.Type = 0;
	 SurfaceSpeedButtonClick(NULL);
     TimerTimer(NULL);
    }
    else
    {
	 //DissolutionThread->DeleteUDT(Und->UDT);
     delete Und;
     ShowMessage("Не получилось удалить атом.");
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HoldSpeedButtonClick(TObject *Sender)
{
    if(SetStateCoord() == false)
    {
     WORD Key = 0x0d;
     TShiftState Shift;
     XEditKeyDown(NULL,Key,Shift);
     return;
    }
    TUndo *Und = new TUndo;
	//Und->UDT = new TUndoDissolutionThread;
	DissolutionThread->SaveToMem(&Und->UDT);
	Und->i = DelComboBox->Items->Count + HoldComboBox->Items->Count;
	if(DissolutionThread->HoldAtom(StrToInt(XEdit->Text),
								   StrToInt(YEdit->Text),
								   StrToInt(ZEdit->Text)) == true)
	{
	 //HoldComboBox->Items->Insert(0,A3dToStr(&SelAtom));
	 HoldComboBox->ItemIndex = HoldComboBox->Items->AddObject(A3dToStr(&SelAtom),(TObject*)Und);
	 SelAtom.Type = 0;
	 SurfaceSpeedButtonClick(NULL);
	}
	else
	{
	 //DissolutionThread->DeleteUDT(Und->UDT);
     delete Und;
     ShowMessage("Не получилось сделать атом неудаляемым.");
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Adjacent1SpeedButtonClick(TObject *Sender)
{
    if(CheckCoord(true))
    {
      int x;
      int y;
      int z;
      int Tp;
      x = StrToIntDef(XEdit->Text, 0x7fffffff);
      y = StrToIntDef(YEdit->Text, 0x7fffffff);
      z = StrToIntDef(ZEdit->Text, 0x7fffffff);
      Tp = CheckCoordAtom(x,y,z);
      if(Tp >= 1)
      {
       if(z%2==0)
       {
        z--;
        y--;
        x--;
       }
       else
       {
        z--;
        y++;
        x--;
       }
       XEdit->Text = IntToStr(x);
       YEdit->Text = IntToStr(y);
       ZEdit->Text = IntToStr(z);
       SetStateCoord();
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Adjacent2SpeedButtonClick(TObject *Sender)
{
    if(CheckCoord(true))
    {
      int x;
      int y;
      int z;
      int Tp;
      x = StrToIntDef(XEdit->Text, 0x7fffffff);
      y = StrToIntDef(YEdit->Text, 0x7fffffff);
      z = StrToIntDef(ZEdit->Text, 0x7fffffff);
      Tp = CheckCoordAtom(x,y,z);
      if(Tp >= 1)
      {
       if(z%2==0)
       {
        z--;
        y++;
        x++;
       }
       else
       {
        z--;
        y--;
        x++;
       }
       XEdit->Text = IntToStr(x);
       YEdit->Text = IntToStr(y);
       ZEdit->Text = IntToStr(z);
       SetStateCoord();
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Adjacent3SpeedButtonClick(TObject *Sender)
{
    if(CheckCoord(true))
    {
      int x;
      int y;
      int z;
      int Tp;
      x = StrToIntDef(XEdit->Text, 0x7fffffff);
      y = StrToIntDef(YEdit->Text, 0x7fffffff);
      z = StrToIntDef(ZEdit->Text, 0x7fffffff);
      Tp = CheckCoordAtom(x,y,z);
      if(Tp >= 1)
      {
       if(z%2==0)
       {
        z++;
        y++;
        x--;
       }
       else
       {
        z++;
        y--;
        x--;
       }
       XEdit->Text = IntToStr(x);
       YEdit->Text = IntToStr(y);
       ZEdit->Text = IntToStr(z);
       SetStateCoord();
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Adjacent4SpeedButtonClick(TObject *Sender)
{
    if(CheckCoord(true))
    {
      int x;
      int y;
      int z;
      int Tp;
      x = StrToIntDef(XEdit->Text, 0x7fffffff);
      y = StrToIntDef(YEdit->Text, 0x7fffffff);
      z = StrToIntDef(ZEdit->Text, 0x7fffffff);
      Tp = CheckCoordAtom(x,y,z);
      if(Tp >= 1)
      {
       if(z%2==0)
       {
        z++;
        y--;
        x++;
       }
       else
       {
        z++;
        y++;
        x++;
       }
       XEdit->Text = IntToStr(x);
       YEdit->Text = IntToStr(y);
       ZEdit->Text = IntToStr(z);
       SetStateCoord();
      }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BackDelsSpeedButtonClick(TObject *Sender)
{
    TComboBox *FirstComboBox,*SecondComboBox,*TmpComboBox;
    if(Sender == BackDelsSpeedButton)
    {
     FirstComboBox = DelComboBox;
     SecondComboBox = HoldComboBox;
    }
    else
    {
     if(Sender == BackHoldsSpeedButton)
     {
      FirstComboBox = HoldComboBox;
      SecondComboBox = DelComboBox;
     }
     else return;
    }
    if((FirstComboBox->Items->Count > 0)&&(FirstComboBox->ItemIndex >= 0))
    {
     int i;
     TUndo *Und,*TmpUnd;
     TmpComboBox = FirstComboBox;
     i = TmpComboBox->ItemIndex;
     Und = (TUndo*)TmpComboBox->Items->Objects[i];
     TmpComboBox->Items->Delete(i);

     TmpComboBox = FirstComboBox;
     for(i = 0; i < TmpComboBox->Items->Count; i++)
     {
	  TmpUnd = (TUndo*)TmpComboBox->Items->Objects[i];
      if(TmpUnd->i > Und->i)
	  {
	   //DissolutionThread->DeleteUDT(TmpUnd->UDT);
       delete TmpUnd;
       TmpComboBox->Items->Delete(i);
       i--;
      }
     }
     TmpComboBox = SecondComboBox;
     for(i = 0; i < TmpComboBox->Items->Count; i++)
     {
      TmpUnd = (TUndo*)TmpComboBox->Items->Objects[i];
      if(TmpUnd->i > Und->i)
      {
	   //DissolutionThread->DeleteUDT(TmpUnd->UDT);
       delete TmpUnd;
       TmpComboBox->Items->Delete(i);
       i--;
      }
     }
	 DissolutionThread->LoadFromMem(&Und->UDT);
	 //DissolutionThread->DeleteUDT(Und->UDT);
     delete Und;
     SurfaceSpeedButtonClick(NULL);
     TimerTimer(NULL);
     FirstComboBox->ItemIndex = FirstComboBox->Items->Count - 1;
     SecondComboBox->ItemIndex = SecondComboBox->Items->Count - 1;
     FirstComboBox->Repaint();
     SecondComboBox->Repaint();
    }
    else
    {
     ShowMessage("Выберете пункт из списка, а потом нажмите отмена.");
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenABASpeedButtonClick(TObject *Sender)
{
	 TExperimentProperty *EpmntPrprt;
     DsslExpPrprt = new TExperimentProperty;
     EpmntPrprt = DsslExpPrprt;

     SfsOpenDialog->FilterIndex = 2;
     if(SfsOpenDialog->Execute() == true)
     {
      HANDLE hFile;
      //HANDLE CreateFile(
      //LPCTSTR lpFileName,	// pointer to name of the file
      //DWORD dwDesiredAccess,	// access (read-write) mode
      //DWORD dwShareMode,	// share mode
      //LPSECURITY_ATTRIBUTES lpSecurityAttributes,	// pointer to security attributes
      //DWORD dwCreationDistribution,	// how to create
	  //DWORD dwFlagsAndAttributes,	// file attributes
      //HANDLE hTemplateFile 	// handle to file with attributes to copy
      //);
      int nSeek = 0;

	  hFile = CreateFile(_c_str(SfsOpenDialog->FileName),
						 GENERIC_READ,//GENERIC_WRITE
						 FILE_SHARE_WRITE,
						 NULL,
						 OPEN_ALWAYS,
						 FILE_ATTRIBUTE_NORMAL,
						 NULL);
      if(hFile != INVALID_HANDLE_VALUE)
      {
	   DWORD NumberOfBytesRead,NumberOfBytesReaded;
	   int i,j;
       int TmpInt;
       double TmpDouble;
       bool bwf = true;
	   //BOOL ReadFile(
       //	HANDLE hFile,	// handle of file to read
       //	LPVOID lpBuffer,	// address of buffer that receives data
       //	DWORD nNumberOfBytesToRead,	// number of bytes to read
       //	LPDWORD lpNumberOfBytesRead,	// address of number of bytes read
       //	LPOVERLAPPED lpOverlapped 	// address of structure for data
       //);
       AnsiString id_sring = AbaFileIdString;
	   char *P_id = new char[id_sring.Length()];
       NumberOfBytesRead = id_sring.Length()*sizeof(char);
       bwf &= ReadFile(hFile,P_id,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
       nSeek += (bwf)?NumberOfBytesReaded:0;
       //P_id[id_sring.Length()] = '\0';
       if(AnsiString(P_id,(unsigned char)id_sring.Length()) == id_sring)
       {
        EpmntPrprt->FileName = SfsOpenDialog->FileName;
        do
        {
         TmpInt = EpmntPrprt->FileName.Pos("\\");
		 if(TmpInt != 0) EpmntPrprt->FileName.Delete(1, TmpInt);
        }
		while(TmpInt != 0);
        NumberOfBytesRead = sizeof(int);
		bwf &= ReadFile(hFile,&(EpmntPrprt->W),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        bwf &= ReadFile(hFile,&(EpmntPrprt->H),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		bwf &= EpmntPrprt->SP.LoadFromFile(hFile, &nSeek);

        bwf &= EpmntPrprt->m_vMask.LoadFromFile(hFile, &nSeek);

        NumberOfBytesRead = sizeof(int);
        bwf &= ReadFile(hFile,&(EpmntPrprt->DelAtoms),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        bwf &= ReadFile(hFile,&(EpmntPrprt->DeletedLayers),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        if( EpmntPrprt->DeletingLayers != 0 ) delete EpmntPrprt->Layers;
        bwf &= ReadFile(hFile,&(EpmntPrprt->DeletingLayers),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        bwf &= ReadFile(hFile,&(EpmntPrprt->N1),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        bwf &= ReadFile(hFile,&(EpmntPrprt->N2),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        bwf &= ReadFile(hFile,&(EpmntPrprt->N3),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
		NumberOfBytesRead = sizeof(int)*EpmntPrprt->DeletingLayers;
		EpmntPrprt->Layers = new int[EpmntPrprt->DeletingLayers];
        bwf &= ReadFile(hFile,EpmntPrprt->Layers,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        NumberOfBytesRead = sizeof(double);
        bwf &= ReadFile(hFile,&(TmpDouble),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        EpmntPrprt->BeginTime = TmpDouble;
        bwf &= ReadFile(hFile,&(TmpDouble),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        EpmntPrprt->DissolutionTime = TmpDouble;
        bwf &= ReadFile(hFile,&(TmpDouble),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        EpmntPrprt->EndTime = TmpDouble;
        bwf &= ReadFile(hFile,&(EpmntPrprt->AverageSpeed),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
		TmpInt = EpmntPrprt->Description.Length();
        NumberOfBytesRead = sizeof(int);
        bwf &= ReadFile(hFile,&(TmpInt),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;
        if(TmpInt != 0)
        {
         char *TmpStr = new char[TmpInt];
         //NumberOfBytesRead = sizeof(char)*EpmntPrprt->Description.Length();
		 //bwf &= ReadFile(hFile,_c_str(EpmntPrprt->Description),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
         NumberOfBytesRead = sizeof(char)*TmpInt;
         bwf &= ReadFile(hFile,TmpStr,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
         nSeek += (bwf)?NumberOfBytesReaded:0;
         EpmntPrprt->Description = AnsiString(TmpStr, (unsigned char)TmpInt);
         delete TmpStr;
        }
        if(bwf == false)
		{
         char Text[] = "Свойства поверхности прочитать не удалось.";
         char Caption[] =  "Ошибка при открытии файла";
		 Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
        }
        DeletedLabel->Caption = IntToStr(EpmntPrprt->DelAtoms);

		bwf = true;
        //TUndoDissolutionThread *UDT = new TUndoDissolutionThread;
		TUndoDissolutionThread UDT;
		bwf &= UDT.LoadFromFile(hFile, &nSeek);

        if(DissolutionThread == NULL)
        {
		 DissolutionThread = new TDissolutionThread(true);
		}
		DissolutionThread->LoadFromMem(&UDT);
		//DissolutionThread->DeleteUDT(&UDT);
		SurfaceSpeedButtonClick(Sender);
		//DissolutionThread->Suspended = false;
		ChangeSpeedButton->Caption = "Изменить";
	    DissolutionParamsSet = true;
        StatStopPanel->Enabled = DissolutionParamsSet;
        StatStopPanel->Enabled = true;
		StatPauseLabel->Enabled = StatStopPanel->Enabled;
        StatPauseLabel->Caption = StatStopPanel->Caption;
        StatPauseLabel->Repaint();

		//StatStopPanelClick(Sender);

        //}
        if(bwf == false)
        {
         char Text[] = "Массив атомов и сортовой массив прочитать не удалось.";
         char Caption[] =  "Ошибка при открытии файла";
		 Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
        }
        else
		{
		 m_DssParams.SP = UDT.SP;
		 m_DssParams.m_Algoritm = UDT.m_Algoritm;
		 m_DssParams.Plane = 0;
		 m_DssParams.X = UDT.SizeX;
		 m_DssParams.Y = UDT.SizeY;
		 m_DssParams.Z = 0;

		 m_DssParams.m_vMask.clear();

		 if(EpmntPrprt->m_vMask.size() != 0)
         {
          m_DssParams.Masked = true;
          m_DssParams.m_vMask = EpmntPrprt->m_vMask;
         }
         else
         {
          m_DssParams.Masked = false;
         }
     	 ExternExpProp = false;
         SetViewParams();
         TimerTimer(NULL);
         Caption = PROGNAME_AND_VER + EpmntPrprt->FileName;
         //IsSurfaceGen = true;
        }
       }
       else
       {
        AnsiString Text = "Файл " + SfsOpenDialog->FileName + " не ABA формата.";
        char Caption[] =  "Ошибка при открытии файла";
		Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
	   }
	   delete P_id;
	   //SetEndOfFile(hFile);
	   CloseHandle(hFile);

	  }
	  else
	  {

	   char Text[] = "Функция CreateFile возратила INVALID_HANDLE_VALUE";
	   char Caption[] =  "Ошибка при открытии файла";
	   Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
      }
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveABASpeedButtonClick(TObject *Sender)
{
	 TExperimentProperty *EpmntPrprt;
     EpmntPrprt = DsslExpPrprt;
    //
     if(EpmntPrprt == NULL)
     {
      MessageBox(Handle,"Нечего сохранять.","Сохранение",MB_OK|MB_ICONWARNING);
      return;
     }
     SfsSaveDialog->FileName = EpmntPrprt->FileName;
     SfsSaveDialog->FilterIndex = 2;
     if(SfsSaveDialog->Execute() == true)
     {
      HANDLE hFile;
      //HANDLE CreateFile(
      //LPCTSTR lpFileName,	// pointer to name of the file
      //DWORD dwDesiredAccess,	// access (read-write) mode
      //DWORD dwShareMode,	// share mode
      //LPSECURITY_ATTRIBUTES lpSecurityAttributes,	// pointer to security attributes
      //DWORD dwCreationDistribution,	// how to create
	  //DWORD dwFlagsAndAttributes,	// file attributes
      //HANDLE hTemplateFile 	// handle to file with attributes to copy
      //);

      //if(ExtractFileExt(SfsSaveDialog->FileName) == "")
      //{
      // ChangeFileExt( SfsSaveDialog->FileName, ".ABA" ) );
      //}
      int nSeek = 0;

	  hFile = CreateFile(_c_str(SfsSaveDialog->FileName),
      					 GENERIC_WRITE,//GENERIC_READ
                         FILE_SHARE_READ,
                         NULL,
                         CREATE_ALWAYS,
                         FILE_ATTRIBUTE_NORMAL,
						 NULL);
      if(hFile != INVALID_HANDLE_VALUE)
      {
       DWORD NumberOfBytesToWrite,NumberOfBytesWritten;
       int i,j;
       int TmpInt;
       double TmpDouble;
       bool bwf = true;
       //BOOL WriteFile(
       //	HANDLE hFile,	// handle to file to write to
       //	LPCVOID lpBuffer,	// pointer to data to write to file
       //	DWORD nNumberOfBytesToWrite,	// number of bytes to write
       //	LPDWORD lpNumberOfBytesWritten,	// pointer to number of bytes written
       //	LPOVERLAPPED lpOverlapped 	// pointer to structure needed for overlapped I/O
	   //	);
	   TUndoDissolutionThread UDT;
	   DissolutionThread->SaveToMem(&UDT);
       EpmntPrprt->FileName = SfsSaveDialog->FileName;
       do
       {
		TmpInt = EpmntPrprt->FileName.Pos("\\");
        if(TmpInt != 0) EpmntPrprt->FileName.Delete(1, TmpInt);
       }
       while(TmpInt != 0);
       Caption = PROGNAME_AND_VER + EpmntPrprt->FileName;

       AnsiString id_sring = AbaFileIdString;

       NumberOfBytesToWrite = id_sring.Length()*sizeof(char);
	   bwf &= WriteFile(hFile,_c_str(id_sring),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;
       NumberOfBytesToWrite = sizeof(int);
       bwf &= WriteFile(hFile,&(EpmntPrprt->W),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       bwf &= WriteFile(hFile,&(EpmntPrprt->H),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
	   //NumberOfBytesToWrite = sizeof(double);
	   //bwf &= WriteFile(hFile,&(EpmntPrprt->N1Probability),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   //bwf &= WriteFile(hFile,&(EpmntPrprt->N2Probability),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   //bwf &= WriteFile(hFile,&(EpmntPrprt->N3Probability),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);

	   bwf &= EpmntPrprt->SP.SaveToFile(hFile, &nSeek);

	   bwf &= EpmntPrprt->m_vMask.SaveToFile(hFile, &nSeek);

	   NumberOfBytesToWrite = sizeof(int);
       bwf &= WriteFile(hFile,&(EpmntPrprt->DelAtoms),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
	   bwf &= WriteFile(hFile,&(EpmntPrprt->DeletedLayers),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       bwf &= WriteFile(hFile,&(EpmntPrprt->DeletingLayers),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;
       bwf &= WriteFile(hFile,&(EpmntPrprt->N1),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       bwf &= WriteFile(hFile,&(EpmntPrprt->N2),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       bwf &= WriteFile(hFile,&(EpmntPrprt->N3),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       NumberOfBytesToWrite = sizeof(int)*EpmntPrprt->DeletingLayers;
       bwf &= WriteFile(hFile,EpmntPrprt->Layers,NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;
       NumberOfBytesToWrite = sizeof(double);
       TmpDouble = (double)EpmntPrprt->BeginTime;
       bwf &= WriteFile(hFile,&(TmpDouble),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       TmpDouble = (double)EpmntPrprt->DissolutionTime;
       bwf &= WriteFile(hFile,&(TmpDouble),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       TmpDouble = (double)EpmntPrprt->EndTime;
       bwf &= WriteFile(hFile,&(TmpDouble),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       bwf &= WriteFile(hFile,&(EpmntPrprt->AverageSpeed),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       TmpInt = EpmntPrprt->Description.Length();
       NumberOfBytesToWrite = sizeof(int);
       bwf &= WriteFile(hFile,&(TmpInt),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;
       if(TmpInt != 0)
       {
        NumberOfBytesToWrite = sizeof(char)*EpmntPrprt->Description.Length();
		bwf &= WriteFile(hFile,_c_str(EpmntPrprt->Description),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
        nSeek+= (bwf)?NumberOfBytesWritten:0;
       }
       if(bwf == false)
       {
        char Text[] = "Свойства поверхности сохранить не удалось.";
        char Caption[] =  "Ошибка при сохранении файла";
		Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
       }
       bwf = true;

	   bwf &= UDT.SaveToFile(hFile, &nSeek);

	   if(bwf == false)
       {
        char Text[] = "Массивы атомов и сортовой массив сохранить не удалось.";
        char Caption[] =  "Ошибка при сохранении файла";
		Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
       }
       SetEndOfFile(hFile);
       CloseHandle(hFile);
	   //DissolutionThread->DeleteUDT(UDT);
      }
      else
      {
       char Text[] = "Функция CreateFile возратила INVALID_HANDLE_VALUE";
       char Caption[] =  "Ошибка при сохранении файла";//открытии
	   Application->MessageBox(_WST(Text),_WST(Caption),MB_OK);// | MB_EXEPTIION
      }
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PointsCheckBoxClick(TObject *Sender)
{
    Points = PointsCheckBox->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CopySpeedButtonClick(TObject *Sender)
{
	if(hGLRC == NULL)
    {
        MessageBox(Handle, "OpenGL не проинициализирован. Нажмите кнопку OpenGL.", "Внимание", MB_ICONERROR);
        return;
    }

	EnabledPaint = false;
    TScreenCopyForm *SC = new TScreenCopyForm(this);
    SC->OriginalHeight = ScreenPanel->Height;
    SC->OriginalWidth = ScreenPanel->Width;

    if(SSD.m_strDir != "")
    {
     SC->m_bCapture    = SSD.m_bCapture;
     SC->m_nFrom       = SSD.m_nFrom;
     SC->m_nStep       = SSD.m_nStep;
     SC->m_nTo         = SSD.m_nTo;
     SC->m_bSeveralOrn = SSD.m_bSeveralOrn;
     SC->m_strBaseName = SSD.m_strBaseName;
     SC->m_strDir      = SSD.m_strDir;
    }

    if(SC->ShowModal() == mrOk)
    {
     SSD.AllH = SC->SamHeight;
     SSD.AllW = SC->SamWidth;
     SSD.Qual = SC->SamQuality;
     SSD.PrintIndex = PrintIndex;
     PrintIndex = SC->PrintIndex;

     SSD.m_nCaptureCode = 1;//начало
     if(SC->m_bCapture == false )
        SSD.m_nCaptureCode = 0;//выход
     SSD.m_bCapture    = SC->m_bCapture;
     SSD.m_nFrom       = SC->m_nFrom;
     SSD.m_nStep       = SC->m_nStep;
     SSD.m_nTo         = SC->m_nTo;
     SSD.m_bSeveralOrn = SC->m_bSeveralOrn;
     SSD.m_strBaseName = SC->m_strBaseName;
     SSD.m_strDir      = SC->m_strDir;

     if(SSD.m_bCapture == true)
     {
        PostMessage(Handle,WM_CAPTUREVIDEO,2,0);
     }
     else
     {
        InitScshtData();
        PostMessage(Handle,WM_COPYSCREENSHOT,0,0);
     }
    }
    delete SC;
	EnabledPaint = true;
    return;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::InitScshtData(void)
{
     SSD.Code = 0;
     SSD.MaxW = ScreenPanel->Width;
     SSD.MaxH = ScreenPanel->Height;
     SSD.NW = (SSD.AllW-1)/SSD.MaxW +1;
     SSD.NH = (SSD.AllH-1)/SSD.MaxH +1;
     SSD.Bitmap = new Graphics::TBitmap;
     SSD.Bitmap->Width=SSD.AllW;
     SSD.Bitmap->Height=SSD.AllH;
     SSD.XPort = XPort;
     SSD.YPort = YPort;
     //учёт непропорциональности отношения сторон - при необходимости область будет расширена
     float dRatioAll = (float)SSD.AllH/SSD.AllW;
     float dRatioMax = (float)SSD.MaxH/SSD.MaxW;
     float dRatio = dRatioAll/dRatioMax;
     if(dRatio > 1)
     {//область выше исходной - увеличить Y
        YPort*= dRatio;
     }
     else
     {//область шире исходной - увеличить X
        XPort*= 1/dRatio;
     }
     //создать шрифт для скриншота
     HWND hWnd= ScreenPanel->Handle;
     HDC hDC = GetDC(hWnd);

     LOGFONT f;

     memset(&f, sizeof(f), 0);
     //определяем размер шрифта
     f.lfHeight = -MulDiv( MulDiv(12,SSD.AllH,SSD.MaxH), GetDeviceCaps(hDC, LOGPIXELSY), 72);
     //параметры начертания
     f.lfWeight = FW_BOLD;
     f.lfItalic = FALSE;
     f.lfUnderline = FALSE;
     f.lfStrikeOut = FALSE;
     //остальные параметры
     f.lfOutPrecision = OUT_TT_PRECIS;
     f.lfQuality = ANTIALIASED_QUALITY;
     f.lfPitchAndFamily = VARIABLE_PITCH;
     //поворот
     f.lfEscapement = 0;
     //название шрифта
     strcpy(f.lfFaceName, "Arial");
     HFONT hf = CreateFontIndirect(&f);
     HGDIOBJ hOldObj;
     hOldObj = SelectObject (hDC, hf);
     BOOL bRet = wglUseFontBitmaps (hDC, 0, 255, 2000);
     if(bRet == FALSE)
     {
      LPVOID lpMsgBuf;

      FormatMessage(
         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
         NULL,
         GetLastError(),
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         (LPTSTR) &lpMsgBuf,
         0,
         NULL
       );

      // Display the string.
      MessageBox( NULL, (char*)lpMsgBuf, "GetLastError-wglUseFontOutlines", MB_OK|MB_ICONINFORMATION );

      // Free the buffer.
      LocalFree( lpMsgBuf );
     }
     SelectObject (hDC, hOldObj);
     DeleteObject(hf);
     glListBase (2000);
     ReleaseDC(hWnd,hDC);
}
//---------------------------------------------------------------------------
void DispError(void)
{
    LPVOID lpMsgBuf;

    FormatMessage(
     FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
     NULL,
     GetLastError(),
     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
     (LPTSTR) &lpMsgBuf,
     0,
     NULL
    );

    // Display the string.
    MessageBox( NULL, (char*)lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );

    // Free the buffer.
    LocalFree( lpMsgBuf );
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CopyDisplayAxis(bool X,bool Y,bool Z)
{
//рисуем оси
    GLfloat ProjectionMatrix[4][4], *pMatix;
    pMatix = (GLfloat*)ProjectionMatrix;
    glGetFloatv(GL_MODELVIEW_MATRIX, pMatix);
    GLdouble Len = 0.95*min(XPort,YPort);
    float color[4] = {1, 1, 1, 0.1};
    if(X == true)
    {
     glColor3d(0,0,0);
     glBegin(GL_LINES);
       color[0]=1; color[1]=0; color[2]=0; color[3]=1;
       glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
       glVertex3d(-Len,0,0);
       glVertex3d(Len,0,0);
     glEnd();
     color[0]=(ProjectionMatrix[0][2]>=0)? 1: 0.5; color[1]=0; color[2]=0; color[3]=1;
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);//GL_AMBIENT
     glBegin(GL_POINTS);
      glVertex3d(Len,0,0);
     glEnd();
    }
    if(Y == true)
    {
     glBegin(GL_LINES);//GL_QUADS
      color[0]=0; color[1]=1; color[2]=0; color[3]=0;
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
      glVertex3d(0,Len,0);
      glVertex3d(0,-Len,0);
     glEnd();
     color[0]=0; color[1]=(ProjectionMatrix[1][2]>=0)? 1: 0.5; color[2]=0; color[3]=1;
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);//GL_AMBIENT
     glBegin(GL_POINTS);
      glVertex3d(0,Len,0);
     glEnd();
    }
    if(Z == true)
    {
     glBegin(GL_LINES);
      color[0]=0; color[1]=0; color[2]=1; color[3]=0;
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
      glVertex3d(0,0,-Len);
      glVertex3d(0,0,Len);
     glEnd();
     color[0]=0; color[1]=0; color[2]=(ProjectionMatrix[2][2]>=0)? 1: 0.5; color[3]=1;
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
     glBegin(GL_POINTS);
      glVertex3d(0,0,Len);
     glEnd();
    }

    //DisplayAxis(AxisX,AxisY,AxisZ);
    //Display();
    //ставим третий светильник
 	glPushMatrix();
    {
	 glLoadIdentity();//переходим в глобальные координаты
     float color[4] = {1,1,1,1};
     float pos[4];
     float dir[3];
	 pos[2] = 100+CenterZ;
	 pos[0] = pos[2]*0.4+CenterX;
	 pos[1] = pos[2]*0.4+CenterY;
	 pos[2] = 100;
	 pos[0] = pos[2]*2;
	 pos[1] = pos[2]*0.4;
	 //pos[3] = 0.5+((Scale));
	 pos[3] = 1;
     dir[0] = 0;
     dir[1] = 0;
     dir[2] = -1;
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
     glLightfv(GL_LIGHT2, GL_POSITION, pos);
     glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);
     glLightfv(GL_LIGHT2, GL_DIFFUSE, color);
     glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 100.0);
     glLightf(GL_LIGHT2,GL_CONSTANT_ATTENUATION,0.7);
     glLightf(GL_LIGHT2,GL_LINEAR_ATTENUATION, 0.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,0.0);
    }
 	glPopMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CopySreenShot(TMessage& Msg)
{
    int TmpQality = Qality;
    Qality = SSD.Qual;
    int AllW, AllH;
    int MaxW,MaxH,CW,CH,NW,NH,i,j;
    float lp,rp,tp,bp;
    TRect CurrentRect;
    int Code = SSD.Code;
    AllW = SSD.AllW;
    AllH = SSD.AllH;
    MaxW = SSD.MaxW;
	MaxH = SSD.MaxH;
	CW = SSD.CW;
	CH = SSD.CH;
    NW = SSD.NW;
    NH = SSD.NH;
    CurrentRect = SSD.CurrentRect;
    i = (Code)%NW;
    j = ((Code)/NW)%NH;

    if(Code!=0)
    {
     HDC glhdc = GetDC(ScreenPanel->Handle);//hwnd);
     HDC BitmapDC  = (HDC)SSD.Bitmap->Canvas->Handle;
     int err;
     err = BitBlt(BitmapDC,CurrentRect.Left,CurrentRect.Top,CurrentRect.Width(),CurrentRect.Height(),glhdc,0,0,SRCCOPY);
     if(err == 0)
      DispError();
     if(Code == NW*NH)
     {//выход
      TClipboard *Clipboard;
      Clipboard = new TClipboard;
      Word AFormat;
      unsigned int AData;
      HPALETTE APalette;
      Clipboard->Open();
      SSD.Bitmap->SaveToClipboardFormat(AFormat,AData,APalette);
      Clipboard->SetAsHandle(AFormat,AData);
      Clipboard->Close();
      delete Clipboard;
      if(SSD.m_nCaptureCode!=0)
      {
       AnsiString strFullFileName = ExpandFileName(SSD.m_strDir);
       if(DirectoryExists(strFullFileName) == false)
        ForceDirectories(strFullFileName);
       //сохранить изображение
       strFullFileName = ExpandFileName(SSD.m_strCurrFileName);
       SSD.Bitmap->SaveToFile(strFullFileName);
       //послать сообщение
       PostMessage(Handle,WM_CAPTUREVIDEO,3,0);
      }
      delete SSD.Bitmap;
      SSD.Bitmap = NULL;
      Qality = TmpQality;
      glDeleteLists(2000,255);
      glListBase (1000);
      XPort = SSD.XPort;
      YPort = SSD.YPort;
      ScreenPanelResize(NULL);
      PrintIndex = SSD.PrintIndex;
      FormPaint(NULL);
      return;
     }
    }
    Code++;
    float YkX = (float)AllH/(float)AllW;
    //float YkX = (float)AllW/(float)AllH;
    CW = MaxW;
    if((i+1)*MaxW > AllW)
     CW = MaxW - ((i+1)*MaxW - AllW);
    CH = MaxH;
    if((j+1)*MaxH > AllH)
     CH = MaxH - ((j+1)*MaxH - AllH);
    CurrentRect.Left   = i*MaxW;
    CurrentRect.Top    = j*MaxH;
    CurrentRect.Right  = CW + CurrentRect.Left;
    CurrentRect.Bottom = CH + CurrentRect.Top;
    //lp = (2*(float)((float)CurrentRect.Left*((float)MaxW)/((float)AllW)/((float)AllW))   -1)*XPort;
    //rp = (2*(float)((float)CurrentRect.Right*((float)MaxW)/((float)AllW)/((float)AllW))  -1)*XPort;
    //tp = -(2*(float)((float)CurrentRect.Top*((float)MaxH)/((float)AllH)/((float)AllH))   -1)*YPort;
    //bp = -(2*(float)((float)CurrentRect.Bottom*((float)MaxH)/((float)AllH)/((float)AllH))-1)*YPort;

    lp = (2*(float)((float)CurrentRect.Left/((float)AllW)) -1)*XPort*((YPort/XPort)/YkX)*Scale;
    rp = (2*(float)((float)(CurrentRect.Left+MaxW)/((float)AllW)) -1)*XPort*((YPort/XPort)/YkX)*Scale;
    tp = -(2*(float)((float)CurrentRect.Top/((float)AllH)) -1)*YPort*Scale;
    bp = -(2*(float)((float)(CurrentRect.Top+MaxH)/((float)AllH)) -1)*YPort*Scale;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(lp, rp, bp, tp, Near, Far);
    UpX = EyeX - CenterX;
    UpY = EyeY - CenterY;
	UpZ = EyeZ - CenterZ;
	DirectAlongZ(UpX,UpY,UpZ);
   	gluLookAt( EyeX,EyeY,EyeZ, CenterX,CenterY,CenterZ, UpX,UpY,UpZ );
   	glMatrixMode( GL_MODELVIEW );

    FormPaint(NULL);

    SSD.Code = Code;
    SSD.AllW = AllW;
    SSD.AllH = AllH;
    SSD.MaxW = MaxW;
    SSD.MaxH = MaxH;
	SSD.CW = CW;
    SSD.CH = CH;
    SSD.NW = NW;
    SSD.NH = NH;
    SSD.CurrentRect = CurrentRect;

    PostMessage(Handle,WM_COPYSCREENSHOT,0,0);

    Qality = TmpQality;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowSurfPanelSpeedButtonClick(TObject *Sender)
{
    SurfacePanel->Visible = ShowSurfPanelSpeedButton->Down;
    SurfCoolBar->Visible = ShowSurfPanelSpeedButton->Down;
    SurfacePanel->Visible =true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SurfSpeedButtonClick(TObject *Sender)
{

    if(DissolutionThread != NULL)
    {
     if(SurfaceMode == true)
     {
      IsListGen = true;
      IsSurfaceGen = false;
      SurfaceMode = false;
      glPushMatrix();
      SetViewParams();
 	  glPopMatrix();
      FormPaint(NULL);
     }
     else
     {
     EnabledPaint = false;
     SurfaceMode = true;
     IsListGen = false;
     IsSurfaceGen = false;
     CenterXT =  0;
     CenterYT =  0;
     CenterZT =  0;
     DissolutionThread->GenerateSurface(Surf);
     EnabledPaint = true;
     FormPaint(NULL);
     }
    }
    else
    {
	 Application->MessageBoxA(_WST("Нужно задать параметры образца."), _WST("Внимание"), MB_ICONERROR);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DisplaySurface(void)
{// функция рисования этой поверхности
	int i,j,k, ii,jj;
    TSurfVal Val;
    TSurfVal CenterZ;
    TSurfVal Sign = -1;
#ifdef Almas110
    Sign *= -1;//у этого алмаза вектора ячейки не образуют правую тройку векторов, поэтому знак наоборот
#endif

    TPoint3d PntG, PntL, Color, PntM1, PntM2,ColorM1,ColorM2, Normalvect, Avect, Bvect;
    int CenterX, CenterY;
    CenterX = Surf.SizeX/2;
    CenterY = Surf.SizeY/2;
    MinColor.x = 0;
    MinColor.y = 0;//минимальный зелёный
    MinColor.z = 1;

    MaxColor.x = 0;
    MaxColor.y = 1;
    MaxColor.z = 0;//максимальный синий

    //раасчёт минимальной и максимальной координаты по Z
    bool bSet = false;
    Zmax = Zmin = 0;
    for(i=0; i < 2; i++)
    {
     for(j=0; j < 4; j++)
     {
      PntL.x = (j%2)*(Surf.SizeX-1) - CenterX;
      PntL.y = (j/2)*(Surf.SizeY-1) - CenterY ;
      PntL.z = Sign*((i==0)?Surf.MinVal:Surf.MaxVal);
      PntG = Surf.FromBaseToOrtho * PntL;
      Val = ModelViewMatrix[0][2]*(float)PntG.x + ModelViewMatrix[1][2]*(float)PntG.y + ModelViewMatrix[2][2]*(float)PntG.z;
      if((Val > Zmax)||(bSet == false))
      {
       Zmax = Val;
      }
      if((Val < Zmin)||(bSet == false))
      {
       Zmin = Val;
      }
      bSet = true;
     }
    }
    //CenterZ = ceil(Surf.MinVal+Surf.MaxVal/2.0);
    CenterZ = ceil((Surf.MinVal+Surf.MaxVal)/2.0);
    float color[4];// = {1, 1, 1, 0.1};
    color[3]=1;
    //рисование самой поверхности из треугольников
    //glColor3f(  1, 0.59, 0.41);
    for(j=0; j < Surf.SizeY-1; j++)
    {
     color[0] = 0.7;
     color[0] = 0.8;
     color[0] = 0.9;
     //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, color);
     color[0] = 0.1;
     color[0] = 0.1;
     color[0] = 0.1;
     //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
     glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, color);
     //glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, color);
     //glMaterialfv(GL_BACK,GL_DIFFUSE, color);
     //glMateriali(GL_FRONT,GL_SHININESS, 128);
     glBegin(GL_TRIANGLE_STRIP);
     for(i=0; i < Surf.SizeX; i++)
     {
      for(k=0; k < 2; k++)
      {
       ii = i + 0;
       jj = j + k;
       Val = Surf.GetVal(ii,jj) - CenterZ;
       if(abs(Val) > 1e100)
           Val = Val;
       if(abs(Val) < 1e-100)
           Val = Val;

       PntL.x = ii - CenterX;
       PntL.y = jj - CenterY;
       PntL.z = Sign*Val ;
       PntG = Surf.FromBaseToOrtho * PntL;
       CalcColor(Val+CenterZ, Surf.MaxVal, Surf.MinVal, Color);
       //CalcIntensiv(PntG,Color);
       //color[0]=Color.Coord[0];
       //color[1]=Color.Coord[1];
       //color[2]=Color.Coord[2];
       //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);

       if(i > 0)
       {
        if(k!=0)
        {
         Avect = PntG - PntM1;
         Bvect = PntM2 - PntM1;
        }
        else
        {
         Avect = PntG - PntM1;
         Bvect = PntM1 - PntM2;
        }
        Normalvect = Avect & Bvect;//векторное произведение
        Normalvect.Normirate();
        //Normalvect=Normalvect*(-1.0);

        glNormal3f(Normalvect.x, Normalvect.y, Normalvect.z);
        glColor3f(ColorM2.x, ColorM2.y, ColorM2.z);
        glVertex3f(PntM2.x, PntM2.y, PntM2.z);

        glNormal3f(Normalvect.x, Normalvect.y, Normalvect.z);
        glColor3f(ColorM1.x, ColorM1.y, ColorM1.z);
        glVertex3f(PntM1.x, PntM1.y, PntM1.z);

        glNormal3f(Normalvect.x, Normalvect.y, Normalvect.z);
        glColor3f(Color.x, Color.y, Color.z);
        glVertex3f(PntG.x, PntG.y, PntG.z);
       }
       PntM2 = PntM1;
       PntM1 = PntG;
       ColorM2 = ColorM1;
       ColorM1 = Color;
      }
     }
     glEnd();
    }

    //рёбра
    if(GraniCheckBox->Checked == true)
    {
     float dz =-Sign*0.05;
     color[0]=1;
     color[1]=0;
     color[2]=0;
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, color);
     glColor3f(  0.0, 0.0, 0.0);
     bool bTriangle = false;
     if(bTriangle == true)
     {
      for(j=0; j < Surf.SizeY-1; j++)
      {
       glBegin(GL_LINE_STRIP);
       for(i=0; i < Surf.SizeX; i++)
       {
        for(k=0; k < 2; k++)
        {
         ii = i + 0;
         jj = j + k;
         Val = Surf.GetVal(ii,jj) - CenterZ;
         //PntL.x = ii - CenterX;
         //PntL.y = jj - CenterY ;
         PntL.x = ii - CenterX;
         PntL.y = jj - CenterY;
         PntL.z = Sign*Val + dz;
         PntG = Surf.FromBaseToOrtho * PntL;
         glVertex3f(PntG.x, PntG.y, PntG.z);
        }
       }
       glEnd();
      }
     }
     else
     {
      for(i=0; i < Surf.SizeX; i++)
      {
       glBegin(GL_LINE_STRIP);
       for(j=0; j < Surf.SizeY; j++)
       {
         ii = i;
         jj = j;
         Val = Surf.GetVal(ii,jj) - CenterZ;
         //PntL.x = ii - CenterX;
         //PntL.y = jj - CenterY ;
         PntL.x = ii - CenterX;
         PntL.y = jj - CenterY;
         PntL.z = Sign*Val + dz;
         PntG = Surf.FromBaseToOrtho * PntL;
         glVertex3f(PntG.x, PntG.y, PntG.z);
       }
       glEnd();
      }
     }


     for(j=0; j < Surf.SizeY; j++)
     {
      glBegin(GL_LINE_STRIP);
      for(i=0; i < Surf.SizeX; i++)
      {
        ii = i;
        jj = j;
        Val = Surf.GetVal(ii,jj) - CenterZ;
        //PntL.x = ii - CenterX;
        //PntL.y = jj - CenterY ;
        PntL.x = ii - CenterX;
        PntL.y = jj - CenterY;
        PntL.z = Sign*Val + dz;
        PntG = Surf.FromBaseToOrtho * PntL;
        glVertex3f(PntG.x, PntG.y, PntG.z);
      }
      glEnd();
     }
    }
}

void __fastcall TMainForm::CalcColor(float x, float max, float min, TPoint3d &RetColor)
{
    float k = (x-min)/(max - min);
    RetColor.x = k*(MaxColor.x - MinColor.x) + MinColor.x;
    RetColor.y = k*(MaxColor.y - MinColor.y) + MinColor.y;
    RetColor.z = k*(MaxColor.z - MinColor.z) + MinColor.z;
/*
    float k1, k2;
    k1 = sin(k*M_PI_2);
    k2 = cos(k*M_PI_2);
    RetColor.x = k1*MaxColor.x + k2*MinColor.x;
    RetColor.y = k1*MaxColor.y + k2*MinColor.y;
    RetColor.z = k1*MaxColor.z + k2*MinColor.z;
*/
}

void __fastcall TMainForm::CalcIntensiv(const TPoint3d &PntG, TPoint3d &RetColor)
{
     GLfloat IntensivColor,Zt, MinColor;
     MinColor = 0.5;//*Scale;
     Zt = ModelViewMatrix[0][2]*(float)PntG.x + ModelViewMatrix[1][2]*(float)PntG.y + ModelViewMatrix[2][2]*(float)PntG.z;
     if(Zmax!=Zmin) IntensivColor = (1-MinColor)*(Zt-Zmin)/(Zmax-Zmin) + MinColor;
     else IntensivColor = 1;
     RetColor.x *= IntensivColor;
     RetColor.y *= IntensivColor;
     RetColor.z *= IntensivColor;

     if(Zt<Zmin)
         IntensivColor = 1;
     if(Zt>Zmax)
         IntensivColor = 1;
}
void __fastcall TMainForm::ExportIntoMatlabSpeedButtonClick(
      TObject *Sender)
{
    if(SurfaceMode == true)
    {
     AnsiString DefaultExtantion =  SfsSaveDialog->DefaultExt;
     int FilterIndex = SfsSaveDialog->FilterIndex;
     SfsSaveDialog->DefaultExt = "z";
     SfsSaveDialog->FilterIndex = 3;
     if(SfsSaveDialog->InitialDir == "")
      SfsSaveDialog->InitialDir = GetCurrentDir();
     if(SfsSaveDialog->Execute() == true)
     {
      SfsSaveDialog->InitialDir = ExtractFileDir(SfsSaveDialog->FileName);
      AnsiString FileName = SfsSaveDialog->FileName;
      int hFile = -1;
      int i,j;
      double Value;
      AnsiString Str;
      //*.z-file
      FileName = ChangeFileExt(FileName, ".z");
      hFile = FileCreate(FileName);
      if(hFile == -1)
        hFile = FileOpen(FileName, fmOpenWrite | fmShareExclusive);
      if(hFile != -1)
      {
       for(j = 0; j < Surf.SizeY; j++)
       {
        Str = "";
        for(i = 0; i < Surf.SizeX; i++)
        {
         Value = Surf.GetVal(i,j);
         Str += AnsiString().FormatFloat("0.0000000e+000", Value);
         int nPos = Str.Pos(",");
         if(nPos > 0)
            Str[nPos] = '.';
         if((i+1) < Surf.SizeX)
          Str += " ";
        }
        if((j+1) < Surf.SizeY)
          Str += "\r\n";
		FileWrite(hFile, _c_str(Str), Str.Length());
       }
       FileClose(hFile);
      }
     }
     SfsSaveDialog->DefaultExt = DefaultExtantion;
     SfsSaveDialog->FilterIndex = FilterIndex;
	}
    else
    {
     MessageBox(Handle, "Режим отображения поверхности не активирован.", "Ошибка", MB_OK | MB_ICONERROR);
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SecondTypeComboBoxChange(TObject *Sender)
{
	if(SelectAtomType == true)
    {
     int ProbIndex;
     int ProbIndexEetalon = PI_ERROR;
     TAtom3d *a3dTmp;
	 if(SecondTypeComboBox->ItemIndex != -1)
     {
	  ProbIndexEetalon = (int)SecondTypeComboBox->Items->Objects[SecondTypeComboBox->ItemIndex];
     }
	 int i,j;

     for(j = 0; j < NumberAtoms; j++)
	 {
      a3dTmp = &(Atoms[j]);
	  a3dTmp->Type &= ~(SELECT_MASK_GROUPE);
	  ProbIndex = a3dTmp->ProbIndex;
	  if(ProbIndexEetalon == ProbIndex && ProbIndexEetalon != PI_ERROR)
       a3dTmp->Type |= (SELECT_MASK_GROUPE);
     }
    }
}
//---------------------------------------------------------------------------
void TMainForm::SetAdjType(int ProbIndex)
{
    bool SelectAtomTypeTmp = SelectAtomType;
    //SelectAtomType = false;
    int Index = SecondTypeComboBox->Items->IndexOfObject((TObject*)ProbIndex);
	SecondTypeComboBox->ItemIndex = Index;
    if(SelectAtomType == true)
	 SecondTypeComboBoxChange(NULL);
    SelectAtomType = SelectAtomTypeTmp;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetScaleLable(void)
{
    ScaleLabel->Caption = "Масштаб: " + AnsiString().FormatFloat("0.##",1/Scale);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::GetColorFromAtomType(unsigned char AtomType, float &r, float &g, float &b)
{
    switch(AtomType & SELECT_MASK_TYPE)
    {
     case 1:
      r = OneLinksAtomColorR;
      g = OneLinksAtomColorG;
      b = OneLinksAtomColorB;
     break;
     case 2:
      r = TwoLinksAtomColorR;
      g = TwoLinksAtomColorG;
      b = TwoLinksAtomColorB;
     break;
	 case 3:
      r = ThreeLinksAtomColorR;
      g = ThreeLinksAtomColorG;
      b = ThreeLinksAtomColorB;
     break;
     case 4:
      r = FourLinksAtomColorR;
      g = FourLinksAtomColorG;
      b = FourLinksAtomColorB;
     break;
     case 5:
     case 6:
      r = NoDeleteAtomColorR;
      g = NoDeleteAtomColorG;
      b = NoDeleteAtomColorB;
     break;
     default:
      r = 1;
      g = 1;
      b = 1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::GetColorLinkFromAtomType(unsigned char BeginAtomType, char EndAtomType, float &r, float &g, float &b)
{
    switch(min(BeginAtomType&SELECT_MASK_TYPE,EndAtomType&SELECT_MASK_TYPE))
    {
     case 0://в небеса
      r = LinkNoAtomColorR;
      g = LinkNoAtomColorG;
      b = LinkNoAtomColorB;
     break;
     default:
      switch(max(BeginAtomType&SELECT_MASK_TYPE,EndAtomType&SELECT_MASK_TYPE))
      {
       case 1://к односвязному атому
       case 2://к двусвязному атому
        r = LinkOneTwoLinksAtomColorR;
		g = LinkOneTwoLinksAtomColorG;
        b = LinkOneTwoLinksAtomColorB;
       break;
       case 3://к трёхсвязному атому
        r = LinkThreeLinksAtomColorR;
        g = LinkThreeLinksAtomColorG;
        b = LinkThreeLinksAtomColorB;
       break;
       case 4://к четырёхсвязному атому
        r = LinkFourLinksAtomColorR;
        g = LinkFourLinksAtomColorG;
        b = LinkFourLinksAtomColorB;
       break;
	   case 5://к неудаляемому атому
	   case 6://к неудаляемому атому замороженному вручную
		r = LinkNoDeleteAtomColorR;
        g = LinkNoDeleteAtomColorG;
        b = LinkNoDeleteAtomColorB;
       break;
      }
     break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetCenter(void)
{
    glLoadIdentity();
    if((IsSurfaceGen == true)||(SurfaceMode == true))
    {
     if(IsSurfaceGen == true)
      SetViewParams();
     //glRotated(-45, 1,0,0); //54,73561031725
     //glRotated(35.264389682754654315377000330019, 0,1,1);
#ifdef Almas100
     //
#endif
#ifdef Almas110
     glRotated(-90, 1,0,0); //54,73561031725
     glRotated(-45, 0,0,1);
#endif
#ifdef Almas111
     glRotated(-45, 1,0,0); //54,73561031725
     glRotated(35.264389682754654315377000330019, 0,1,1);
#endif
    }
    else
    {
     if(IsListGen)
     {
      //SetViewParams();
      double delta = 0;

#ifdef Almas100
      delta = 1/4.0;//
#endif
#ifdef Almas110
      glRotated(-90, 1,0,0); //54,73561031725
      glRotated(-45, 0,0,1);
      delta = 1/4.0;//
#endif
#ifdef Almas111
      glRotated(-45, 1,0,0); //54,73561031725
      glRotated(35.264389682754654315377000330019, 0,1,1);
      delta = 1/3.0;//
#endif
      //CenterXT = CenterYT = CenterZT = 0;
      double W_2 = (((double)m_DssParams.X)-delta)/2;
      double H_2 = (((double)m_DssParams.Y)-delta)/2;
      double Z_sr= ((double)m_DssParams.Z)/2;

      CenterXT = -(Mtr2[0][0]*W_2 + Mtr2[1][0]*H_2 + Mtr2[2][0]*Z_sr);
      CenterYT = -(Mtr2[0][1]*W_2 + Mtr2[1][1]*H_2 + Mtr2[2][1]*Z_sr);
      CenterZT =  (Mtr2[0][2]*W_2 + Mtr2[1][2]*H_2 + Mtr2[2][2]*Z_sr);
      int j,k;

      for(j=0; j < NumberAtoms; j++ )
      {
       if(Atoms[j].Type&SELECT_MASK_TYPE == 5 || Atoms[j].Type&SELECT_MASK_TYPE == 6)
       {
        for(k=0; k < 3; k++ )
        {
         if(Atoms[j].Coord[k] > MaxTopLeftUP.Coord[k])
          MaxTopLeftUP.Coord[k] = Atoms[j].Coord[k];
         if(Atoms[j].Coord[k] < MinTopLeftUP.Coord[k])
          MinTopLeftUP.Coord[k] = Atoms[j].Coord[k];
        }
       }
      }
      MaxTopLeftUP.Coord[2] = -MaxTopLeftUP.Coord[2];
      MinTopLeftUP.Coord[2] = -MinTopLeftUP.Coord[2];

      //CenterXT = -((double)m_DssParams.X)*2;
      //CenterYT = -((double)m_DssParams.Y)*2;
      //CenterZT = -((double)m_DssParams.Z-1)/2;
     }
     else
      CenterXT = CenterYT = CenterZT = 0;
    }
    SpeedXT = SpeedYT = SpeedZT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DelInvisibleSpeedButtonClick(TObject *Sender)
{
    if(DissolutionThread != NULL)
    {
        TAtom3d *A3d;
        int j;
        for(j = 0; j < NumberAtoms; j++)
        {
         A3d = &Atoms[j];
         if((A3d->Type & SELECT_MASK_INVISIBLE) != 0)//  1 - невидим, 0 - видм
         {
          DissolutionThread->DeleteAtom(A3d->Coord[0],A3d->Coord[1],A3d->Coord[2]);
         }
        }
        SurfaceSpeedButtonClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MillersSpeedButtonClick(TObject *Sender)
{
    TMillersForm *pMillers = new TMillersForm(this);
    pMillers->MI = MI;
    if(pMillers->ShowModal()== mrOk)
    {
        if(Initialiseded)
        {
	     glLoadIdentity();
	     SpeedXT = SpeedYT = SpeedZT = 0;

         TPoint3d Mill;//вектор миллера

         Mill.x = pMillers->MI.h;
         Mill.y = pMillers->MI.k;
         Mill.z = pMillers->MI.l;
         Mill.Normirate();//приведём к зноменателю

         //вокруг глобальной Y
         RotateAroundWoldAxises(0,-Mill.AngleTeta()*180/M_PI,0);
         //вокруг глобальной X
         RotateAroundWoldAxises(-(Mill.AnglePhi()-M_PI/2)*180/M_PI,0,0);
        }
        MI = pMillers->MI;
    }
    delete pMillers;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveOrientationListSpeedButtonClick(
      TObject *Sender)
{
    if(SaveOrientationComboBox->Items->Count == 1)
    {
     AnsiString strErr = "В списке нет ориентаций для сохранения.";
	 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
     return;
    }

    if(OrientationSaveDialog->Execute() == true)
    {
        int hFile = FileCreate(OrientationSaveDialog->FileName);
        if(hFile != -1)
        {
            try
            {
             char szFileIdString[] = ORN_FILE_ID_STRING;
             int nSize = sizeof(szFileIdString);
             if(FileWrite(hFile, szFileIdString, nSize) != nSize)
              throw AnsiString("Идентификационная строка формата.");

             int nCnt = SaveOrientationComboBox->Items->Count-1;
             nSize = sizeof(nCnt);
             if(FileWrite(hFile, &nCnt, nSize) != nSize)
              throw AnsiString("Количество структур.");
             char szName[MAX_ORN_NAME];
             TOrientation *pOrn;

             for(int i = 0; i < nCnt; i++)
             {
              setmem(szName, sizeof(szName), 0);
			  strncpy(szName, _c_str(SaveOrientationComboBox->Items->Strings[i+1]), sizeof(szName));
              nSize = sizeof(szName);
              if(FileWrite(hFile, szName, nSize) != nSize)
               throw AnsiString(AnsiString("Название структуры.")+
                                AnsiString("Элемент ")+ IntToStr(i) + AnsiString(" из ") + IntToStr(nCnt) + AnsiString("."));
              pOrn = (TOrientation *)SaveOrientationComboBox->Items->Objects[i+1];

              /*
              nSize = sizeof(TOrientation);
              if(FileWrite(hFile, pOrn, nSize) != nSize)
              */
              if(pOrn->WriteToFile(hFile) != true)
               throw AnsiString(AnsiString("Данные структуры.") +
                                AnsiString("Элемент ")+ IntToStr(i) + AnsiString(" из ") + IntToStr(nCnt) + AnsiString("."));
             }
            }
            catch(AnsiString strErrDscr)
            {
             AnsiString strErr = "Не удалось записать данные в файл \"" + OrientationSaveDialog->FileName + "\".\n"+strErrDscr;
			 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
            }
            FileClose(hFile);
        }
        else
        {
         AnsiString strErr = "Не удалось открыть файл \"" + OrientationSaveDialog->FileName + "\" для записи.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenOrientationListSpeedButtonClick(
      TObject *Sender)
{
    if(OrientationOpenDialog->Execute() == true)
    {
        int hFile = FileOpen(OrientationOpenDialog->FileName, fmOpenRead);
        if(hFile != -1)
        {
            try
            {
             char szFileIdString[] = ORN_FILE_ID_STRING;
             int nSize = sizeof(szFileIdString);
             setmem(szFileIdString, nSize, 0);
             if(FileRead(hFile, szFileIdString, nSize) != nSize)
              throw AnsiString("Идентификационная строка формата.");
             if(strcmp(szFileIdString, ORN_FILE_ID_STRING) != 0)
              throw AnsiString("Идентификационная строка формата не соответствует ожидаемоей.");
             int nCnt = 0;
             nSize = sizeof(nCnt);
             if(FileRead(hFile, &nCnt, nSize) != nSize)
              throw AnsiString("Количество структур.");
             char szName[MAX_ORN_NAME];
             TOrientation *pOrn;

             //удаление других ориентаций
             while(SaveOrientationComboBox->Items->Count >1)
             {
              pOrn = (TOrientation *)SaveOrientationComboBox->Items->Objects[1];
              delete pOrn;
              SaveOrientationComboBox->Items->Delete(1);
             }
             //зачитка из файла новых ориентаций
             for(int i = 0; i < nCnt; i++)
             {
              setmem(szName, sizeof(szName), 0);
			  //strncpy(szName, _c_str(SaveOrientationComboBox->Items->Strings[i+1]), sizeof(szName));
              nSize = sizeof(szName);
              if(FileRead(hFile, szName, nSize) != nSize)
               throw AnsiString(AnsiString("Название структуры.")+
                                AnsiString("Элемент ")+ IntToStr(i) + AnsiString(" из ") + IntToStr(nCnt) + AnsiString("."));
              pOrn = new TOrientation;
              /*
              nSize = sizeof(TOrientation);
              if(FileRead(hFile, pOrn, nSize) != nSize)
			  */
              if(pOrn->LoadFromFile(hFile) != true)
               throw AnsiString(AnsiString("Данные структуры.") +
                                AnsiString("Элемент ")+ IntToStr(i) + AnsiString(" из ") + IntToStr(nCnt) + AnsiString("."));
              SaveOrientationComboBox->Items->AddObject(szName, (TObject*)pOrn);
             }
            }
            catch(AnsiString strErrDscr)
            {
             AnsiString strErr = "Не удалось прочитать из файла \"" + OrientationOpenDialog->FileName + "\".\n"+strErrDscr;
			 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
			}
			FileClose(hFile);

		}
		else
		{
		 AnsiString strErr = "Не удалось открыть файл \"" + OrientationOpenDialog->FileName + "\" для чтения.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveOrientationComboBoxCloseUp(TObject *Sender)
{
    EnabledPaint = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MillersComboBoxCloseUp(TObject *Sender)
{
    EnabledPaint = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AcceptScale(void)
{
    AnsiString strScale;
    strScale = AnsiString::FloatToStrF(1.0/Scale, AnsiString::sffGeneral, 4, 4);
    ScaleLabel->Caption = "Масштаб: " + strScale;
    SetCamera();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LayerSpeedButtonClick(TObject *Sender)
{
    if(DsslExpPrprt!=NULL)
    {
     EnabledPaint = false;
     if(pQuantityByGroupeForm == NULL)
     {
	  pQuantityByGroupeForm = new TQuantityByGroupeForm(DsslExpPrprt->m_vAtomCntInLayer, this);
	 }
     pQuantityByGroupeForm->ShowModal();
     EnabledPaint = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CaptureVideo(TMessage& Msg)
{
    bool bSet = false;
    if(SSD.m_bCapture == true)
    {
     //третий шаг - выход либо продолжение
     if(SSD.m_nCaptureCode == 3 && bSet==false)
     {
      if(DissolutionThread != NULL)
      {
       if(DissolutionThread->Plane == DissolutionThread->DeletedAtom
       && (int)DissolutionThread->DeletedAtom <= (SSD.m_nTo - SSD.m_nStep)
         )
       {//продолжаем
        DissolutionThread->Plane+=SSD.m_nStep;
        StatStopPanelClick(NULL);
        SSD.m_nCaptureCode=2;//на скриншот
        bSet = true;
       }
       else
       {//выход
        RestoreOrn(SSD.m_BaseOrn);
        SSD.m_nCaptureCode=0;//выход
        bSet = true;
       }
      }
      else
      {
       SSD.m_nCaptureCode=0;//выход
       bSet = true;
      }
     }

     //второй шаг - сделать скриншот
     if(SSD.m_nCaptureCode == 2 && bSet==false)
     {
      if(DissolutionThread != NULL)
      {
       /*
       if(DissolutionThread->Plane == DissolutionThread->DeletedAtom
       && DissolutionThread->Finish == true
         )
       {
        ;
       }
       */
       //подготовить имя файла
       SSD.m_strCurrFileName = SSD.m_strDir;
       if(SSD.m_strCurrFileName[SSD.m_strCurrFileName.Length()] != '\\')
        SSD.m_strCurrFileName+= "\\";
       SSD.m_strCurrFileName+=SSD.m_strBaseName;
       TOrientation *Orientation = NULL;
       if(SSD.m_bSeveralOrn == true)
       {
        int ItemIndex = SSD.m_nOrnIndex+1;
        //TOrientation *Orientation;
        Orientation = (TOrientation *)SaveOrientationComboBox->Items->Objects[ItemIndex];
        //RestoreOrn(*Orientation);
        SSD.m_strCurrFileName+=" " + ReplaceOrnString(SaveOrientationComboBox->Items->Strings[ItemIndex]) + " ";
        SSD.m_nOrnIndex++;
       }
       else
       {
        Orientation = &(SSD.m_BaseOrn);
        //RestoreOrn(SSD.m_BaseOrn);
       }
	   SSD.m_strCurrFileName+=IntToStr((int)DissolutionThread->DeletedAtom);
       SSD.m_strCurrFileName+=".bmp";
       //снимок
       SurfaceSpeedButtonClick(NULL);
       //восстановить ориентацию
       RestoreOrn(*Orientation);
       //сделать скриншот
       InitScshtData();
       PostMessage(Handle,WM_COPYSCREENSHOT,0,0);
       //PostMessage(Handle,WM_COPYSCREENSHOT,0,0);
       if(SSD.m_bSeveralOrn == false || (SSD.m_bSeveralOrn == true && (SSD.m_nOrnIndex+1) >= SaveOrientationComboBox->Items->Count))
       {
        SSD.m_nOrnIndex = 0;
        SSD.m_nCaptureCode=3;//второй шаг сделан
        bSet = true;
       }
      }
      else
      {//выход
       SSD.m_nCaptureCode=0;//выход
       bSet = true;
      }
     }
     //первый шаг - снять нужное количество атомов
     if(SSD.m_nCaptureCode == 1 && bSet==false)
     {
      SSD.m_nOrnIndex=0;//индекс ориетации
      //SSD.m_BaseOrn;//базовая ориентация
      SaveOrn(SSD.m_BaseOrn);//базовая ориентация
      if(DissolutionThread == NULL)
      {
       m_DssParams.Plane = SSD.m_nFrom;
       StatStopPanelClick(NULL);
      }
      else
      {
       SSD.m_nFrom += DissolutionThread->DeletedAtom;
       SSD.m_nTo += DissolutionThread->DeletedAtom;
       DissolutionThread->Plane = SSD.m_nFrom;
       StatStopPanelClick(NULL);
      }
      SSD.m_nCaptureCode=2;//первый шаг сделан
      bSet = true;
     }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveOrn(TOrientation &Orn)
{//сохранить оринтацию
     glGetFloatv(GL_MODELVIEW_MATRIX, Orn.vMatix);
     Orn.Scale = Scale;
     Orn.MultiAngle = MultiAngle;
     Orn.MultiSpeed = MultiSpeed;
     Orn.Xt = SpeedXT;
     Orn.Yt = SpeedYT;
     Orn.Zt = SpeedZT;
     Orn.m_vClipPlane = m_CurrOrn.m_vClipPlane;//массив обрезки
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RestoreOrn(TOrientation &Orn, bool bClip)
{//восстановить оринтацию
     glLoadMatrixf(Orn.vMatix);
     Scale = Orn.Scale;
     MultiAngle = Orn.MultiAngle;
     MultiSpeed = Orn.MultiSpeed;
     SpeedXT = Orn.Xt;
     SpeedYT = Orn.Yt;
     SpeedZT = Orn.Zt;
     if(bClip)
     {//воссановление обрезки
      UINT i;
      ClearClip();
      for(i = 0; i < Orn.m_vClipPlane.size(); i++)
      {
       AppClipPlane(Orn.m_vClipPlane[i]);
      }
      m_CurrOrn.m_vClipPlane = Orn.m_vClipPlane;//массив обрезки
     }
     MulAngleLabel->Caption = "Угол x " + AnsiString(MultiAngle);//"Angle •" + AnsiString(MultiAngle);
     MulSpeedLabel->Caption = "Шаг x " + AnsiString(MultiSpeed);//"Move •" + AnsiString(MultiSpeed);
     AcceptScale();
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMainForm::ReplaceOrnString(AnsiString strOrn)//
{
    AnsiString strRet = strOrn;
    AnsiString strFind = ":";
    AnsiString strReplace;
    int nPos;
    strReplace=".";
    nPos = strRet.Pos(strFind);
    if(nPos > 0)
    {
     strRet.Delete(nPos, strFind.Length());
     strRet.Insert(strReplace, nPos);
    }
    strReplace=",";
    while(nPos = strRet.Pos(strFind),  nPos > 0)
    {
     strRet.Delete(nPos, strFind.Length());
     strRet.Insert(strReplace, nPos);
    }
    return strRet;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CentrSpeedButtonClick(TObject *Sender)
{
    bool AnaliseitView = AnalizViewSpeedButton->Down;
    bool bAnalis;
    TAtom3d* A3d;
    double dCenterX = 0;
    double dCenterY = 0;
    double dCenterZ = 0;
    int nAnalised = 0;
    int j;
    if(IsListGen || IsSurfaceGen == true)
    {
     for(j = 0; j < NumberAtoms; j++)
     {
      A3d = (TAtom3d*)(Atoms+j);
      bAnalis = false;
      if(AnaliseitView)
      {
       if((A3d->Type & SELECT_MASK_INVISIBLE) == 0)//  1 - невидим, 0 - видм
       {
        bAnalis = true;
       }
      }
      else
      {
       bAnalis = true;
      }
      if(bAnalis == true)
      {
       dCenterX += A3d->Coord[0];
       dCenterY += A3d->Coord[1];
       dCenterZ += A3d->Coord[2];
       nAnalised++;
      }
     }
     if(nAnalised != 0)
     {
      dCenterX = dCenterX/nAnalised;
      dCenterY = dCenterY/nAnalised;
      dCenterZ = dCenterZ/nAnalised;
     }
     SpeedXT = -floor(dCenterX + 0.5) - CenterXT;
     SpeedYT = -floor(dCenterY + 0.5) - CenterYT;
     SpeedZT = -floor(-dCenterZ + 0.5) - CenterZT;
    }
    FormPaint(NULL);
}
//---------------------------------------------------------------------------


