//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "GLDrow.h"
#include "Matrix.h"
#include <math.h>
#include <vcl\Clipbrd.hpp>
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
//мксимальная длна имени ориентации
#define MAX_ORN_NAME 40
#define ORN_FILE_ID_STRING "This File is ORN Format"
//---------------------------------------------------------------------------
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
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
    Roll = 0;
   //Паралельная
    XPort = YPort = 10;
    PrintIndex = true;
    Loaded = false;
    EnabledPaint = true;
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
    MultiDiam = 1;
    DiamLabel->Caption = "Радиус x " + AnsiString(MultiDiam);
    AxisCheckBoxClick(this);
    Qality = 10;
    Scale = 1.0;
    AcceptScale();
    MillersComboBox->ItemIndex = 0;
    Application->HintHidePause = 10000;
    //CxEdit->Ctl3D = false;
    //CyEdit->Ctl3D = false;
    //CzEdit->Ctl3D = false;
    ObjectCenterComboBox->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenMenuItemClick(TObject *Sender)
{
    //
    if(OpenDialog->Execute())
    {
     Loaded = LoadFile(OpenDialog->FileName);
     //int i;
     TSpheraMap_iter s_iter;
     TLineMap_iter l_iter;
     TCilinderMap_iter c_iter;

     ObjectCenterComboBox->Clear();
     for(s_iter = Spheras.begin(); s_iter != Spheras.end(); s_iter++)
     {
	  ObjectCenterComboBox->Items->AddObject("s#"+s_iter->second->NumberName,(TObject*)s_iter->second);
     }
     for(l_iter = Lines.begin(); l_iter != Lines.end(); l_iter++)
     {
	  ObjectCenterComboBox->Items->AddObject("l#"+l_iter->second->NumberName,(TObject*)l_iter->second);
     }
     for(c_iter = Cilinders.begin(); c_iter != Cilinders.end(); c_iter++)
     {
      ObjectCenterComboBox->Items->AddObject("с#"+c_iter->second->NumberName,(TObject*)c_iter->second);
     }
     ObjectCenterComboBox->ItemIndex = -1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExitMenuItemClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    //init GL
    m_strDefaultCaption = Caption;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormHide(TObject *Sender)
{
    //деinit GL
    if(Initialiseded)
    {
     ExitGL();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActivate(TObject *Sender)
{
	if(hGLRC == NULL)
    {
     if(InitGL(GetDC(OpenGLPanel->Handle)) == 0)
     	return;
     OpenGLPanelResize(Sender);
 	 Repaint();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetCamera(void)
{
     glMatrixMode( GL_PROJECTION );
     glLoadIdentity();
     //XPort = YPort

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
     ////N1Label->Caption = "UpX: " + AnsiString(UpX);
     ////N2Label->Caption = "UpX: " + AnsiString(UpY);
     ////N3Label->Caption = "UpZ: " + AnsiString(UpZ);
     //N1Label->Caption = "EyeX: " + AnsiString(EyeX) + "; CenterX: " + AnsiString(CenterX);
     //N2Label->Caption = "EyeY: " + AnsiString(EyeY) + "; CenterY: " + AnsiString(CenterY);
     //N3Label->Caption = "EyeZ: " + AnsiString(EyeZ) + "; CenterZ: " + AnsiString(CenterZ);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenGLPanelResize(TObject *Sender)
{
	static OldW = 0, OldH = 0;
    if(Initialiseded)
    {
     //ExitGL();
     //if(InitGL(GetDC(OpenGLPanel->Handle)) == 0)
     //	return;

     int w, h;
     w = OpenGLPanel->ClientWidth;
     h = OpenGLPanel->ClientHeight;
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

	 //ResizeGL(OpenGLPanel->ClientWidth, OpenGLPanel->ClientHeight);
    }
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

void __fastcall TMainForm::ApplicationEventsIdle(TObject *Sender,
      bool &Done)
{
    if(Initialiseded)
    {
 	 if(EnabledPaint) FormPaint(Sender);//Repaint();
     //if( Keys->PressingKeyCount !=0) R = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormPaint(TObject *Sender)
{
    if(Initialiseded)
    {
     //if(fTimerEvent == false)
     {
	  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	  Display();
	  glFinish();
	  SwapBuffers(wglGetCurrentDC());
     }
     //else fTimerEvent = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Display(void)
{
    //вращаемся вокруг локальных осей Y, X, Z
    glRotated(AlphaT, 0,1,0);
    glRotated(BetaT, 1,0,0);
    glRotated(GammaT, 0,0,1);
    //вращаемся вокруг мировых осей Y, X, Z
    if((AlphaG != 0)||(BetaG != 0)||(GammaG != 0)) RotateAroundWoldAxises(AlphaG, BetaG, GammaG);
    //рисуем оси
	DisplayAxis(AxisX,AxisY,AxisZ);
    // сохраняем старое положение сцены
 	glPushMatrix();
    {
     glTranslated(SpeedXT - CenterXT,
                  SpeedYT - CenterYT,
                  SpeedZT - CenterZT);

     if(Loaded == true)
     {

      DrawList();
     }
     else
     {
      SnowMan();
     }
    }
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
     GLdouble Len = 0.95*min(Scale*XPort,Scale*YPort);
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

void __fastcall TMainForm::AxisCheckBoxClick(TObject *Sender)
{
	AxisX=AxisY=AxisZ=AxisCheckBox->Checked;//true;
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
    }
 	ShiftState = Shift;
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
      glLoadIdentity();
      SpeedXT = SpeedYT = SpeedZT = 0;
      CenterXT = CenterYT = CenterZT = 0;
//      if(IsSurfaceGen == true)
//      {
//       SetViewParams();
//#ifdef Almas100
//       //
//#endif
//#ifdef Almas110
//       glRotated(-90, 1,0,0); //54,73561031725
//       glRotated(-45, 0,0,1);
//#endif
//#ifdef Almas111
//       glRotated(-45, 1,0,0); //54,73561031725
//       glRotated(35.264389682754654315377000330019, 0,1,1);
//#endif
//      }
//      else
//      {
//       if(IsListGen)
//       {
//        double delta = 0;
//#ifdef Almas100
//        delta = 1/4.0;//
//#endif
//#ifdef Almas110
//        glRotated(-90, 1,0,0); //54,73561031725
//        glRotated(-45, 0,0,1);
//        delta = 1/4.0;//
//#endif
//#ifdef Almas111
//        glRotated(-45, 1,0,0); //54,73561031725
//        glRotated(35.264389682754654315377000330019, 0,1,1);
//        delta = 1/3.0;//
//#endif
//        double W_2 = (((double)SurfaceForm->Params->X)-delta)/2;
//        double H_2 = (((double)SurfaceForm->Params->Y)-delta)/2;
//        double Z_sr= ((double)SurfaceForm->Params->Z)/2;
//
//        CenterXT = -(Mtr2[0][0]*W_2 + Mtr2[1][0]*H_2 + Mtr2[2][0]*Z_sr);
//        CenterYT = -(Mtr2[0][1]*W_2 + Mtr2[1][1]*H_2 + Mtr2[2][1]*Z_sr);
//        CenterZT =  (Mtr2[0][2]*W_2 + Mtr2[1][2]*H_2 + Mtr2[2][2]*Z_sr);
//        int j,k;
//
//        for(j=0; j < NumberNoDeleteAtoms; j++ )
//        {
//         for(k=0; k < 3; k++ )
//         {
//          if(((TAtom3d*)(NoDeleteAtoms+j))->Coord[k] > MaxTopLeftUP.Coord[k])
//           MaxTopLeftUP.Coord[k] = ((TAtom3d*)(NoDeleteAtoms+j))->Coord[k];
//          if(((TAtom3d*)(NoDeleteAtoms+j))->Coord[k] < MinTopLeftUP.Coord[k])
//           MinTopLeftUP.Coord[k] = ((TAtom3d*)(NoDeleteAtoms+j))->Coord[k];
//         }
//        }
//        MaxTopLeftUP.Coord[2] = -MaxTopLeftUP.Coord[2];
//        MinTopLeftUP.Coord[2] = -MinTopLeftUP.Coord[2];
//       }
//       else
//        CenterXT = CenterYT = CenterZT = 0;
//      }
     break;
     case 79://'o' 0x4F
     case 189://'-' 0xBD
     case 109://'-' Numpad
      OUTSpeedButtonClick(Sender);
     break;
     case 73://'i' 0x49
     case 187://'+' 0xBB
     case 107://'+' Numpad
      INSpeedButtonClick(Sender);
     break;
     case VK_DELETE:
        if((SaveOrientationComboBox->ItemIndex > 0)
      		&&(SaveOrientationComboBox->DroppedDown))
        {
         TOrientation *pObj;
         pObj = (TOrientation *)SaveOrientationComboBox->Items->Objects[SaveOrientationComboBox->ItemIndex];
         delete pObj;
         SaveOrientationComboBox->Items->Delete(SaveOrientationComboBox->ItemIndex);
        }
     break;
     case VK_F11:
      AngleUpSpeedButtonClick(Sender);
     break;
     case VK_F12:
      AngleDownSpeedButtonClick(Sender);
     break;
     case VK_F9:
      StepUpSpeedButtonClick(Sender);
     break;
     case VK_F10:
      StepDownSpeedButtonClick(Sender);
     break;
//     case 80:////'P' 0x50
//	  IsLinksVisibled = !IsLinksVisibled;
//      LinksCheckBox->Checked = IsLinksVisibled;
//     break;
     case VK_F8://скриншот
      CopySpeedButtonClick(Sender);
     break;
     case VK_F7://Автоцентрирование
      AutocenterSpeedButtonClick(Sender);
     break;

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
void __fastcall TMainForm::XLocalBackSpeedButtonClick(TObject *Sender)
{
      BetaT = -BetaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      BetaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XLocalFrontSpeedButtonClick(TObject *Sender)
{
      BetaT = BetaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      BetaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::YLocalRightSpeedButtonClick(TObject *Sender)
{
      AlphaT = -AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      AlphaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::YLocalLeftSpeedButtonClick(TObject *Sender)
{
      AlphaT = AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      AlphaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ZLocalClockwiseSpeedButtonClick(TObject *Sender)
{
      GammaT = -GammaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      GammaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ZLocalAnticlockwiseSpeedButtonClick(TObject *Sender)
{
      GammaT = GammaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      GammaT = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XGlobalBackSpeedButtonClick(TObject *Sender)
{
      AlphaG = -AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      AlphaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::XGlobalFrontSpeedButtonClick(TObject *Sender)
{
      AlphaG = AlphaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      AlphaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::YGlobalRightSpeedButtonClick(TObject *Sender)
{
      BetaG = -BetaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      BetaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::YGlobalLeftSpeedButtonClick(TObject *Sender)
{
      BetaG = BetaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      BetaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ZGlobalClockwiseSpeedButtonClick(TObject *Sender)
{
      GammaG = -GammaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      GammaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ZGlobalAnticlockwiseSpeedButtonClick(TObject *Sender)
{
      GammaG = GammaW*ShiftSpeed(ShiftState)*MultiAngle;
      FormPaint(Sender);
      GammaG = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RightMoveSpeedButtonClick(TObject *Sender)
{
      SpeedXT += -SpeedXW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LeftMoveSpeedButtonSpeedButtonClick(TObject *Sender)
{
      SpeedXT += SpeedXW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::UpMoveSpeedButtonClick(TObject *Sender)
{
      SpeedYT += SpeedYW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DownMoveSpeedButtonClick(TObject *Sender)
{
      SpeedYT += -SpeedYW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FrontMoveSpeedButtonClick(TObject *Sender)
{
      SpeedZT += SpeedZW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BackMoveSpeedButtonClick(TObject *Sender)
{
      SpeedZT += -SpeedZW*ShiftSpeed(ShiftState)*MultiSpeed;
      FormPaint(Sender);
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


    }
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::LoadFile(AnsiString FileName)
{
    TStringList *TempList = new TStringList;
    TempList->LoadFromFile(FileName);
    int i = 0;
    bool Ret = true;
    //if(i < TempList->Count)
    //{
     //проверить контрольную строку
    // i++;
    //}
    try
    {
    if(Ret == true)
    {//читать обекты
     AnsiString ObjStr;
     AnsiString ObjName;
	 AnsiString ObjParam;
	 AnsiString NumberName;
     int iPos;
     int n,c,ns1,ns2;
     double x,y,z,r,w,x1,x2,y1,y2,z1,z2;
     TObjColor Color1;
     TObjColor Color2;
     TSphera *Sp;
     ClearLists();
     TSpheraMap_iter s_iter;
     TLineMap_iter l_iter;
     TCilinderMap_iter c_iter;
     while(i < TempList->Count)
     {
      ObjStr = TempList->Strings[i];
      i++;
      ObjStr = ObjStr.Trim();
      if(ObjStr == "")
      {//пустые строки
       continue;//пропускаем
      }

      if(ObjStr.Length()>2)
      {
       if(ObjStr[1]=='/' && ObjStr[2]=='/')
       {//однострочные коментарии
        continue;//пропускаем
       }
      }

	  if((iPos = ObjStr.Pos(":")) > 0)
	  {
       ObjName = ObjStr.SubString(1,iPos-1);
       ObjStr.Delete(1,iPos);
       ObjName = ObjName.Trim();
       if(ObjName.LowerCase() == "s")
       {//шарик : n,x,y,z,r,c
		ObjParam = GetParam(ObjStr);
		n = ObjParam.ToInt();
		NumberName = ObjParam;
		ObjParam = GetParam(ObjStr);
		x = ObjParam.ToDouble();
		ObjParam = GetParam(ObjStr);
		y = ObjParam.ToDouble();
		ObjParam = GetParam(ObjStr);
		z = ObjParam.ToDouble();
		ObjParam = GetParam(ObjStr);
		r = ObjParam.ToDouble();
		ObjParam = GetParam(ObjStr);
		//c = ObjParam.ToInt();
		Sp = new TSphera;
		DecodeColor(ObjParam, Sp->Color);
		Sp->n = n;
		Sp->x = x;
		Sp->y = y;
		Sp->z = z;
		Sp->r = r;
		Sp->c = c;
		Sp->LineNumber = i;
		Sp->NumberName = NumberName;
		s_iter = Spheras.find(n);
        if(s_iter == Spheras.end())
        {
         Spheras[n] = Sp;
         continue;
        }
        else
        {
         //такой объект уже есть
         delete Sp;
         Ret = false;
         //break;
         //char szErr[1000];
		 //sprintf(szErr, "Объект \"Сфера\" с номером %d в строке %d встречался ранее в строке %d", n, i, Spheras[n]->LineNumber);
		 AnsiString strError;
		 strError.sprintf("Объект \"Сфера\" с номером %d в строке %d встречался ранее в строке %d", n, i, Spheras[n]->LineNumber);
		 throw strError;//AnsiString(szErr);
        }
       }
       if(ObjName.LowerCase() == "l")
       {//линия : n,ns1,ns2,w,c
        //n - номер обекта линия
        //ns1 - номер шарика = начальная точка
        //ns1 - номер шарика = конечная точка
        //w - толщина
        //c - цвет
        ObjParam = GetParam(ObjStr);
        n = ObjParam.ToInt();
		NumberName = ObjParam;
		ObjParam = GetParam(ObjStr);
        ns1 = ObjParam.ToInt();
        ObjParam = GetParam(ObjStr);
        ns2 = ObjParam.ToInt();
        ObjParam = GetParam(ObjStr);
        w = ObjParam.ToDouble();
        ObjParam = GetParam(ObjStr);
        //c = ObjParam.ToInt();
        s_iter = Spheras.find(ns1);
        if(s_iter != Spheras.end())
        {
         Sp = s_iter->second;
         x1 = Sp->x;
         y1 = Sp->y;
         z1 = Sp->z;
         s_iter = Spheras.find(ns2);
         if(s_iter != Spheras.end())
         {
          Sp = s_iter->second;
          x2 = Sp->x;
          y2 = Sp->y;
          z2 = Sp->z;
          TLine *Ln = new TLine;
          DecodeColor(ObjParam, Ln->Color);
          Ln->n = n;
          Ln->x1 = x1;
          Ln->y1 = y1;
          Ln->z1 = z1;
          Ln->x2 = x2;
          Ln->y2 = y2;
          Ln->z2 = z2;
          Ln->ns1 = ns1;
          Ln->ns2 = ns2;
          Ln->w = w;
          Ln->c = c;
		  Ln->LineNumber = i;
		  Ln->NumberName = NumberName;
		  l_iter = Lines.find(n);
          if(l_iter == Lines.end())
          {
           Lines[n] = Ln;
           continue;
          }
          else
          {//такой объект уже есть
           delete Ln;
           Ret = false;
           //break;
           AnsiString strError;
           strError.sprintf("Объект \"Линия\" с номером %d в строке %d встречался ранее в строке %d", n, i, Lines[n]->LineNumber);
           throw strError;//AnsiString(szErr);
          }
         }
         else
         {//неправильный второй номер
          Ret = false;
          //break;
          AnsiString strError;
          strError.sprintf("Объект \"Линия\" с номером %d в строке %d. Неправильный номер второй сферы (%d)", n, i, ns2);
          throw strError;//AnsiString(szErr);
         }
        }
        else
        {//неправильный первый номер
         Ret = false;
         //break;
         AnsiString strError;
         strError.sprintf("Объект \"Линия\" с номером %d в строке %d. Неправильный номер первой сферы (%d)", n, i, ns1);
         throw strError;//AnsiString(szErr);
        }
       }

////////////////////////////////////////////////////////
       if(ObjName.LowerCase() == "c")
       {//цилиндр : n,ns1,ns2,w,c
        //n - номер обекта цилидр
        //ns1 - номер шарика = начальная точка
        //ns1 - номер шарика = конечная точка
        //w - толщина
        //c - цвет
        ObjParam = GetParam(ObjStr);
		n = ObjParam.ToInt();
		NumberName = ObjParam;
		ObjParam = GetParam(ObjStr);
        ns1 = ObjParam.ToInt();
        ObjParam = GetParam(ObjStr);
        ns2 = ObjParam.ToInt();
        ObjParam = GetParam(ObjStr);
        w = ObjParam.ToDouble();
        ObjParam = GetParam(ObjStr);
        //c = ObjParam.ToInt();
        s_iter = Spheras.find(ns1);
        if(s_iter != Spheras.end())
        {
         Sp = s_iter->second;
         x1 = Sp->x;
         y1 = Sp->y;
         z1 = Sp->z;
         Color1 = Sp->Color;
         s_iter = Spheras.find(ns2);
         if(s_iter != Spheras.end())
         {
          Sp = s_iter->second;
          x2 = Sp->x;
          y2 = Sp->y;
          z2 = Sp->z;
          Color2 = Sp->Color;
          TCilinder *Cp = new TCilinder;
          DecodeColor(ObjParam, Cp->Color);
          Cp->n = n;
          Cp->x1 = x1;
          Cp->y1 = y1;
          Cp->z1 = z1;
          Cp->x2 = x2;
          Cp->y2 = y2;
          Cp->z2 = z2;
          Cp->ns1 = ns1;
          Cp->ns2 = ns2;
          Cp->w = w;
		  Cp->c = c;
		  Cp->LineNumber = i;
		  Cp->NumberName = NumberName;
		  Cp->Color1 = Color1;
          Cp->Color2 = Color2;
          c_iter = Cilinders.find(n);
          if(c_iter == Cilinders.end())
          {
           Cilinders[n] = Cp;
           continue;
          }
          else
          {//такой объект уже есть
           delete Cp;
           Ret = false;
           //break;
           AnsiString strError;
           strError.sprintf("Объект \"Цилиндр\" с номером %d в строке %d встречался ранее в строке %d", n, i, Cilinders[n]->LineNumber);
           throw strError;//AnsiString(szErr);
          }
         }
         else
         {//неправильный второй номер
          Ret = false;
          //break;
          AnsiString strError;
          strError.sprintf("Объект \"Цилиндр\" с номером %d в строке %d. Неправильный номер второй сферы (%d)", n, i, ns2);
          throw strError;//AnsiString(szErr);
         }
        }
        else
        {//неправильный первый номер
         Ret = false;
         //break;
         AnsiString strError;
         strError.sprintf("Объект \"Линия\" с номером %d в строке %d. Неправильный номер первой сферы (%d)", n, i, ns1);
         throw strError;//AnsiString(szErr);
        }
       }
////////////////////////////////////////////////////////
       //неопозднаная фигура
       Ret = false;
       //break;
       AnsiString strError;
       strError.sprintf("Неопозднаная фигура в строке %d",i);
       throw strError;//AnsiString(szErr);
	  }
	  else
	  {// нет двоеточия в строке - пропускаем, считаем что коментарий
       //строка сама увеличится
	   //i++;
	  }
	 }
	}
    }
    catch(AnsiString strErr)
    {
		Application->MessageBoxA(_WST(strErr), _WST("Ошибка"), MB_ICONERROR);
    }

    delete TempList;
    if(Ret == true)
    {
     SetCaption(FileName);
    }
    return Ret;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMainForm::GetParam(AnsiString &Params, AnsiString ExeptStr)
{
     AnsiString ObjParam;
     int iPos;
     try
     {
      int iPos = Params.Pos(",");
      if(iPos == 0)
      {
       ObjParam = Params;
      }
      else
      {
       ObjParam = Params.SubString(1,iPos-1);
       Params.Delete(1,iPos);
      }
      ObjParam = ObjParam.Trim();
      while((iPos = ObjParam.Pos(".")) > 0)
      {
       ObjParam[iPos] = ',';
      }
     }
     catch(...)
     {
      throw Exception(ExeptStr);
     }
     return ObjParam;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawList(void)
{
    float r,g,b;

	bool bDrawLine = DrawLineCheckBox->Checked;
	bool bDrawCilinders = DrawCilindersCheckBox->Checked;
	bool bDrawSpheras = DrawSpherasCheckBox->Checked;

    if(Spheras.size() > 0 && bDrawSpheras)
    {
     TSpheraMap_iter s_iter;
     TSphera *Sp;
     float x,y,z;
     GLUquadricObj *quadObj;
     quadObj = gluNewQuadric();
     for(s_iter = Spheras.begin(); s_iter != Spheras.end(); s_iter++)
     {
      Sp = s_iter->second;
      if(Sp->r > 0)
      {
       r = Sp->Color.r;
       g = Sp->Color.g;
       b = Sp->Color.b;

       glColor3f(r,g,b);
       glPushMatrix();
        glTranslatef(Sp->x,Sp->y,Sp->z);
        gluSphere(quadObj, Sp->r*MultiDiam, Qality, Qality); // рисуем сферу
	   glPopMatrix();
      }
     }
     gluDeleteQuadric(quadObj);
    }
    if(Lines.size() > 0 && bDrawLine)
    {
     GLfloat fLineWidth = 1.0;
     glGetFloatv(GL_LINE_WIDTH, &fLineWidth);
     TLineMap_iter l_iter;
     GLfloat ColorAtom[4];
     TLine *Ln;
     for(l_iter = Lines.begin(); l_iter != Lines.end(); l_iter++)
     {
      Ln = l_iter->second;
      ColorAtom[0] = Ln->Color.r;
      ColorAtom[1] = Ln->Color.g;
      ColorAtom[2] = Ln->Color.b;
      ColorAtom[3] = 1;
      r = Ln->Color.r;
      g = Ln->Color.g;
      b = Ln->Color.b;

      glLineWidth((GLfloat)Ln->w);
      glBegin(GL_LINES);
      glColor3f(r,g,b);
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
      glVertex3i(Ln->x1,Ln->y1,Ln->z1);
      glVertex3i(Ln->x2,Ln->y2,Ln->z2);
      glEnd();
     }
     glLineWidth(fLineWidth);
     ColorAtom[0] = 0;
     ColorAtom[1] = 0;
     ColorAtom[2] = 0;
     ColorAtom[3] = 1;
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, ColorAtom);
    }

    if(Cilinders.size() > 0 && bDrawCilinders)
    {
     TCilinderMap_iter c_iter;
     GLfloat ColorAtom[4];
     TCilinder *Cp;
     GLUquadricObj *quadObj;
     quadObj = gluNewQuadric();
     double dx, dy, dz, dxylen;
     double diametr;
     for(c_iter = Cilinders.begin(); c_iter != Cilinders.end(); c_iter++)
     {
      Cp = c_iter->second;
      diametr = Cp->w/2.0;

      dx = Cp->x2 - Cp->x1;
      dy = Cp->y2 - Cp->y1;
      dz = Cp->z2 - Cp->z1;
      dxylen = pow(dx*dx+dy*dy,0.5);
      r = Cp->Color1.r;
      g = Cp->Color1.g;
      b = Cp->Color1.b;

      glColor3f(r,g,b);
      glPushMatrix();
       glTranslatef(Cp->x1,Cp->y1,Cp->z1);
       //glRotated(90.0+(z2-z1)*45.0, x2-x1, y2-y1, 0);
       //вокруг вектора = векторное произведение оси Z (0 0 1) и проекции на плоскость ху (dx,dy,0)
       //векторное произведение [AB]= (AyBz-AzBy, AzBx-AxBz, AxBy-AyBx)
       glRotated(-(90.0-180.0/M_PI*atan(dz/dxylen)) , dy, -dx, 0);
       gluCylinder(quadObj, diametr*MultiDiam, diametr*MultiDiam, 1/2.0*1.7320508075688772935274463415059, Qality, 1);
	  glPopMatrix();

      r = Cp->Color2.r;
      g = Cp->Color2.g;
      b = Cp->Color2.b;

      glColor3f(r,g,b);
      glPushMatrix();
 	   glTranslatef((Cp->x1+Cp->x2)/2.0,(Cp->y1+Cp->y2)/2.0,(Cp->z1+Cp->z2)/2.0);
       //glRotated(90.0+(z2-z1)*45.0, x2-x1, y2-y1, 0);
       //double dx, dy, dz, dxylen;
       //вокруг вектора = векторное произведение оси Z (0 0 1) и проекции на плоскость ху (dx,dy,0)
       //векторное произведение [AB]= (AyBz-AzBy, AzBx-AxBz, AxBy-AyBx)
       glRotated(-(90.0-180.0/M_PI*atan(dz/dxylen)) , dy, -dx, 0);
       gluCylinder(quadObj, diametr*MultiDiam, diametr*MultiDiam, 1/2.0*1.7320508075688772935274463415059, Qality, 1);
	  glPopMatrix();
     }
     gluDeleteQuadric(quadObj);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClearLists(void)
{
    TSpheraMap_iter s_iter;
    for(s_iter = Spheras.begin(); s_iter != Spheras.end(); s_iter++)
    {
     delete s_iter->second;
    }
    Spheras.clear();

    TLineMap_iter l_iter;
    for(l_iter = Lines.begin(); l_iter != Lines.end(); l_iter++)
    {
     delete l_iter->second;
    }
    Lines.clear();

    TCilinderMap_iter c_iter;
    for(c_iter = Cilinders.begin(); c_iter != Cilinders.end(); c_iter++)
    {
     delete c_iter->second;
    }
    Cilinders.clear();



}
//---------------------------------------------------------------------------
void __fastcall TMainForm::INSpeedButtonClick(TObject *Sender)
{
    Scale = Scale*0.9;
    AcceptScale();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OUTSpeedButtonClick(TObject *Sender)
{
    Scale = Scale/0.9;
    AcceptScale();
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
void __fastcall TMainForm::CopySpeedButtonClick(TObject *Sender)
{
	EnabledPaint = false;
    TScreenCopyForm *SC = new TScreenCopyForm(this);
    SC->OriginalHeight = OpenGLPanel->Height;
    SC->OriginalWidth = OpenGLPanel->Width;
    if(SC->ShowModal() == mrOk)
    {
     SSD.Code = 0;//
     SSD.AllH = SC->SamHeight;
     SSD.AllW = SC->SamWidth;
     SSD.Qual = SC->SamQuality;
     SSD.PrintIndex = PrintIndex;
     PrintIndex = SC->PrintIndex;
     //SSD.AllH = 2*ScreenPanel->Height;
     //SSD.AllW = ScreenPanel->Width*SSD.AllH/ScreenPanel->Height;
     SSD.MaxW = OpenGLPanel->Width;
     SSD.MaxH = OpenGLPanel->Height;
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
     HWND hWnd= OpenGLPanel->Handle;
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

     PostMessage(Handle,WM_COPYSCREENSHOT,0,0);
    }
    delete SC;
	EnabledPaint = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CopySreenShot(TMessage* Msg)
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
     HDC glhdc = GetDC(OpenGLPanel->Handle);//hwnd);
     HDC BitmapDC  = (HDC)SSD.Bitmap->Canvas->Handle;
     //int err;
     //err = BitBlt(BitmapDC,CurrentRect.Left,CurrentRect.Top,CurrentRect.Width(),CurrentRect.Height(),glhdc,0,0,SRCCOPY);
     BitBlt(BitmapDC,CurrentRect.Left,CurrentRect.Top,CurrentRect.Width(),CurrentRect.Height(),glhdc,0,0,SRCCOPY);
     //if(err == 0)
     // DispError();
     if(Code == NW*NH)
     {
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
      delete SSD.Bitmap;
      Qality = TmpQality;
      glDeleteLists(2000,255);
      glListBase (1000);
      XPort = SSD.XPort;
      YPort = SSD.YPort;
      OpenGLPanelResize(NULL);
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
    //
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
bool __fastcall TMainForm::DecodeColor(AnsiString Str, TObjColor &color)
{
    bool Ret = true;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    try
    {
     AnsiString HexStr = Str.Trim();
     if(HexStr.SubString(1,2).LowerCase() == "0x")
     {
      //HexStr.Delete(1,2);
      DWORD HexColor = StrToInt(HexStr);//преобразовывает из шестнадцатиричной системы исчисления 
      color.r = (float)((HexColor>>(0*8))&0xFF)/255.0;
      color.g = (float)((HexColor>>(1*8))&0xFF)/255.0;
      color.b = (float)((HexColor>>(2*8))&0xFF)/255.0;
     }
     else
     {
      int c = Str.ToInt();
      switch(c)
      {
       case 1:
        color.r = 1;
       break;
       case 2:
        color.g = 1;
       break;
       case 3:
        color.b = 1;
       break;
       case 4:
        color.r = 0.5;
        color.g = 0.5;
        color.b = 0.5;
       break;
       default:
        Ret = false;
      }
     }
    }
    catch(...)
    {
     Ret = false;
    }
    return Ret;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MillersComboBoxDropDown(TObject *Sender)
{
	EnabledPaint = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MillersComboBoxChange(TObject *Sender)
{
    if(Initialiseded)
    {
	 glLoadIdentity();
	 //SpeedXT = SpeedYT = SpeedZT = 0;
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
    EnabledPaint = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenGLPanelMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
	if(InfoSpeedButton->Down == true)
    {
     ScreenPanelMousePoint.x = X;
     ScreenPanelMousePoint.y = Y;
     if(Loaded)
	 {
	  SpheraPriview();
	 }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SpheraPriview(void)
{
    double x,y,z,w,h,x1,y1,z1,l,m,n,a,b,c;
    double Model_MATRIX[4][4];
    double Project_MATRIX[4][4];
    int i,j,k;
    double Rayting,delta,deltaSel,Rmod;
    deltaSel = 1.79e308;
    w = OpenGLPanel->ClientWidth;
	h = OpenGLPanel->ClientHeight;
    x = ((double)ScreenPanelMousePoint.x)*2/w - 1;
    y = ((double)ScreenPanelMousePoint.y)*2/h - 1;
    y = -y;
    z = 0;//Near;
 	glPushMatrix();
    //???glScalef(Scale,Scale,Scale);
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
    TPoint3d pnt3d;
    pnt3d.x = x;
    pnt3d.y = y;
    pnt3d.z = z;
    pnt3d = mAllBack.Transpose() * pnt3d;
    x1 = pnt3d.x;
    y1 = pnt3d.y;
    z1 = pnt3d.z;
    TMatrix NN;
    NN = NN*0;
    NN.Item[2][0] = 1;
    NN = mAllBack.Transpose() * NN;
    l = NN.Item[0][0];
    m = NN.Item[1][0];
    n = NN.Item[2][0];
    Rmod = sqrt(l*l + m*m + n*n);

	TSpheraMap_iter s_iter;
    TSphera *Sp;
	int Selected = -1;
	TSpheraMap mapSelected;
	for(s_iter = Spheras.begin(); s_iter != Spheras.end(); s_iter++)
	{
	   Sp = s_iter->second;
	   a = Sp->x;
	   b = Sp->y;
	   c = Sp->z;
	   //вычисление расстояния между экранной точкой и координатой атома
	   delta = sqrt(pow(a-x1,2.0)+pow(b-y1,2.0)+pow(c-z1,2.0));
	   //вычисление скалярного произведения вектора X(l,m,n) и  вектором расстояния от экранной точки до атома (a-x1,b-y1,c-z1)
	   double Cos2Alpha = 0;
	   if( l > 1.0e100 || m > 1.0e100 || n > 1.0e100 )
	   {
		Cos2Alpha = 0;
	   }
	   else
	   {
		Cos2Alpha = pow(((a-x1)*l+(b-y1)*m+(c-z1)*n)/(delta*Rmod),2.0);
	   }
	   if(Cos2Alpha > 0)
	   {
		delta = delta*sqrt(1 - Cos2Alpha);
		if(delta < 1.0) // целевой объект должен находится в радиусе 1 четвертинки
		{
		 if(deltaSel > delta && (deltaSel > 1 || pow(deltaSel - delta, 2.0)>0.0001)) //тукущий объект должен находится ближе к точке на экране чес найденный ранее
		 {
		   deltaSel = delta;
		   Selected = s_iter->first;
		   mapSelected.clear();
		   mapSelected[s_iter->second->LineNumber] = s_iter->second;
		 }
		 else if(pow(deltaSel - delta, 2.0)<0.0001)// но если объеты находятся одинаково близко
		 {
		   mapSelected[s_iter->second->LineNumber] = s_iter->second;
		 }
		 /*
		 if(deltaSel > delta //тукущий объект должен находится ближе к точке на экране чес найденный ранее
		  ||(pow(deltaSel - delta, 2.0)<0.0001 && s_iter->first < Selected)// но если объеты находятся одинаково близко то взять объект с наименьшим номером
		  )
		 {
		  deltaSel = delta;
		  Selected = s_iter->first;
		 }
		 */
		}
       }
    }
    AnsiString HintStr;
	//s_iter = Spheras.find(Selected);
	//if(s_iter != Spheras.end())
	for(s_iter = mapSelected.begin(); s_iter != mapSelected.end(); s_iter++)
	{//формируем хинт
	 Sp = s_iter->second;
	 if(HintStr.Length()>0)
	 {
	  HintStr += "\r\n\r\n";
	 }
	 HintStr += "Шар №" + Sp->NumberName + " (строка " + IntToStr(Sp->LineNumber) + ")";
	 //ищем соседние линии
	 int AdjLines = 0;
	 TLine* Ln;
	 TLineMap_iter l_iter;
	 for(l_iter = Lines.begin(); l_iter != Lines.end(); l_iter++)
	 {
	  Ln = l_iter->second;
	  if((Sp->n == Ln->ns1) || (Sp->n == Ln->ns2))
	  {
	   if(AdjLines == 0)
	   {
		HintStr += "\r\nСоседние линии:";
	   }
	   AdjLines++;
	   HintStr += "\r\n  " + IntToStr(AdjLines) + ". Лииния №" + Ln->NumberName + " (строка " + IntToStr(Ln->LineNumber) + ")";
	  }
	 }
	 //ищем соседние цилиндры
	 int AdjCilinders = 0;
     TCilinder* Cp;
     TCilinderMap_iter c_iter;
     for(c_iter = Cilinders.begin(); c_iter != Cilinders.end(); c_iter++)
	 {
      Cp = c_iter->second;
      if((Sp->n == Cp->ns1) || (Sp->n == Cp->ns2))
      {
       if(AdjCilinders == 0)
       {
		HintStr += "\r\nСоседние цилиндры:";
       }
       AdjCilinders++;
       HintStr += "\r\n  " + IntToStr(AdjCilinders) + ". Цилиндр №" + Cp->NumberName + " (строка " + IntToStr(Cp->LineNumber) + ")";
      }
     }
    }
    OpenGLPanel->Hint = HintStr;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::InfoSpeedButtonClick(TObject *Sender)
{
    //InfoSpeedButton->Down = !InfoSpeedButton->Down;

    OpenGLPanel->ShowHint= InfoSpeedButton->Down;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CxEditEnter(TObject *Sender)
{
    ((TEdit*)Sender)->Font->Color = clBlack;
    KeyPreview = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CxEditExit(TObject *Sender)
{
    KeyPreview = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CxEditKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 0x0d)
    {
     CenterSpeedButtonClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CenterSpeedButtonClick(TObject *Sender)
{
     TEdit * Temp = NULL;
     float cx,cy,cz;
     try
     {
      if((CxEdit->Text!="")||(CyEdit->Text!="")||(CzEdit->Text!=""))
      {
       Temp = CxEdit;
       cx = Temp->Text.ToDouble();
       Temp = CyEdit;
       cy = Temp->Text.ToDouble();
       Temp = CzEdit;
       cz = Temp->Text.ToDouble();

       SpeedXT = -cx;
       SpeedYT = -cy;
       SpeedZT = -cz;
      }
      if(OpenGLPanel->CanFocus() == true)
       OpenGLPanel->SetFocus();
     }
     catch(EConvertError &ce)
     {
      if(Temp !=NULL)
      {
       Temp->Font->Color = clRed;
       if(Temp->CanFocus() == true)
        Temp->SetFocus();
      }
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ObjectCenterComboBoxChange(TObject *Sender)
{
    if(ObjectCenterComboBox->ItemIndex >= 0)
    {
     void *p;
     AnsiString S;
     float cx,cy,cz;
     p = (void*)ObjectCenterComboBox->Items->Objects[ObjectCenterComboBox->ItemIndex];
     S =        ObjectCenterComboBox->Items->Strings[ObjectCenterComboBox->ItemIndex];
     cx = 0;
     cy = 0;
     cz = 0;
     if(S[1] == 's')
     {
      TSphera* Sph = (TSphera*)p;
      cx = Sph->x;
      cy = Sph->y;
      cz = Sph->z;
     }
     if(S[1] == 'l')
     {
      TLine *Ln = (TLine*)p;
      cx = (Ln->x1 + Ln->x2)/2;
      cy = (Ln->y1 + Ln->y2)/2;
      cz = (Ln->z1 + Ln->z2)/2;
	 }
	 if(S[1] == 'c')
	 {
	  TCilinder *Cl = (TCilinder*)p;
	  cx = (Cl->x1 + Cl->x2)/2;
	  cy = (Cl->y1 + Cl->y2)/2;
	  cz = (Cl->z1 + Cl->z2)/2;
	 }

     CxEdit->Text = cx;
     CyEdit->Text = cy;
     CzEdit->Text = cz;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AutocenterSpeedButtonClick(TObject *Sender)
{
    float MaxX,MaxY,MaxZ;
    float MinX,MinY,MinZ;
    float cx,cy,cz;
    TSpheraMap_iter s_iter;
    TSphera* Sphera;

    MaxX=0; MaxY=0; MaxZ=0;
    MinX=0; MinY=0; MinZ=0;

    for(s_iter = Spheras.begin(); s_iter != Spheras.end(); s_iter++)
    {
     Sphera = s_iter->second;
     MaxX = max(MaxX,(float)Sphera->x);
     MaxY = max(MaxY,(float)Sphera->y);
     MaxZ = max(MaxZ,(float)Sphera->z);
     MinX = min(MinX,(float)Sphera->x);
     MinY = min(MinY,(float)Sphera->y);
     MinZ = min(MinZ,(float)Sphera->z);
    }

    cx = (MaxX + MinX)/2;
    cy = (MaxY + MinY)/2;
    cz = (MaxZ + MinZ)/2;

    CxEdit->Text = cx;
    CyEdit->Text = cy;
    CzEdit->Text = cz;

    CenterSpeedButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::WhiteBackgroundMenuItemClick(TObject *Sender)
{
    WhiteBackgroundMenuItem->Checked = !WhiteBackgroundMenuItem->Checked;
    if(WhiteBackgroundMenuItem->Checked)
     glClearColor(1, 1, 1, 0.5);
    else
     glClearColor(0, 0, 0, 0.5);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetCaption(AnsiString FileName)
{
    m_strFileNameCaption = ExtractFileName(FileName);
    Caption = m_strDefaultCaption + " " + m_strFileNameCaption;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DiamUpSpeedButtonClick(TObject *Sender)
{
    MultiDiam *= 1.1;
    DiamLabel->Caption = "Радиус x " + AnsiString(MultiDiam);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DiamDownSpeedButtonClick(TObject *Sender)
{
    MultiDiam *= 1/1.1;
    DiamLabel->Caption = "Радиус x " + AnsiString(MultiDiam);
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

void __fastcall TMainForm::SaveOrientationSpeedButtonClick(TObject *Sender)
{
    if(Initialiseded)
    {
     TOrientation *Orientation;
     Orientation = new TOrientation;
     glGetFloatv(GL_MODELVIEW_MATRIX, Orientation->vMatix);
     Orientation->Scale = Scale;
     Orientation->MultiAngle = MultiAngle;
     Orientation->MultiSpeed = MultiSpeed;
     Orientation->Xt = SpeedXT;
     Orientation->Yt = SpeedYT;
     Orientation->Zt = SpeedZT;

     SaveOrientationComboBox->ItemIndex =
	  SaveOrientationComboBox->Items->AddObject(IntToStr(SaveOrientationComboBox->Items->Count) + ": " +
       MillersIndexesLabel->Caption, (System::TObject*)Orientation);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveOrientationComboBoxChange(TObject *Sender)
{
    int ItemIndex = SaveOrientationComboBox->ItemIndex;
    if(ItemIndex > 0)
    {
     TOrientation *Orientation;
     Orientation = (TOrientation *)SaveOrientationComboBox->Items->Objects[ItemIndex];
     glLoadMatrixf(Orientation->vMatix);
     Scale = Orientation->Scale;
     MultiAngle = Orientation->MultiAngle;
     MulAngleLabel->Caption = "Угол x " + AnsiString(MultiAngle);//"Angle •" + AnsiString(MultiAngle);
     MultiSpeed = Orientation->MultiSpeed;
     MulSpeedLabel->Caption = "Шаг x " + AnsiString(MultiSpeed);//"Move •" + AnsiString(MultiSpeed);
     SpeedXT = Orientation->Xt;
     SpeedYT = Orientation->Yt;
     SpeedZT = Orientation->Zt;
     AcceptScale();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveOrientationComboBoxCloseUp(TObject *Sender)
{
    EnabledPaint = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveOrientationListSpeedButtonClick(
      TObject *Sender)
{
    if(SaveOrientationComboBox->Items->Count == 1)
    {
     AnsiString strErr = "В списке нет ориентаций для сохранения.";
     MessageBox(NULL, strErr.c_str(), "Ошибка", MB_ICONERROR);
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
              nSize = sizeof(TOrientation);
              if(FileWrite(hFile, pOrn, nSize) != nSize)
               throw AnsiString(AnsiString("Данные структуры.") +
                                AnsiString("Элемент ")+ IntToStr(i) + AnsiString(" из ") + IntToStr(nCnt) + AnsiString("."));
             }
            }
            catch(AnsiString strErrDscr)
            {
             AnsiString strErr = "Не удалось записать данные в файл \"" + OrientationSaveDialog->FileName + "\".\n"+strErrDscr;
             MessageBox(NULL, strErr.c_str(), "Ошибка", MB_ICONERROR);
            }
            FileClose(hFile);
        }
        else
        {
         AnsiString strErr = "Не удалось открыть файл \"" + OrientationSaveDialog->FileName + "\" для записи.";
         MessageBox(NULL, strErr.c_str(), "Ошибка", MB_ICONERROR);
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
              //strncpy(szName, SaveOrientationComboBox->Items->Strings[i+1].c_str(), sizeof(szName));
              nSize = sizeof(szName);
              if(FileRead(hFile, szName, nSize) != nSize)
               throw AnsiString(AnsiString("Название структуры.")+
                                AnsiString("Элемент ")+ IntToStr(i) + AnsiString(" из ") + IntToStr(nCnt) + AnsiString("."));
              pOrn = new TOrientation;
              nSize = sizeof(TOrientation);
              if(FileRead(hFile, pOrn, nSize) != nSize)
               throw AnsiString(AnsiString("Данные структуры.") +
                                AnsiString("Элемент ")+ IntToStr(i) + AnsiString(" из ") + IntToStr(nCnt) + AnsiString("."));
              SaveOrientationComboBox->Items->AddObject(szName, (TObject*)pOrn);
             }
            }
            catch(AnsiString strErrDscr)
            {
             AnsiString strErr = "Не удалось прочитать из файла \"" + OrientationOpenDialog->FileName + "\".\n"+strErrDscr;
             MessageBox(NULL, strErr.c_str(), "Ошибка", MB_ICONERROR);
            }
            FileClose(hFile);

        }
        else
        {
         AnsiString strErr = "Не удалось открыть файл \"" + OrientationOpenDialog->FileName + "\" для чтения.";
         MessageBox(NULL, strErr.c_str(), "Ошибка", MB_ICONERROR);
        }
    }
}
//---------------------------------------------------------------------------


