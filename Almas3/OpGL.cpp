//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>

#include "KeysControl.h"
#include "OpGL.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	pos[0] = 3;
	pos[1] = 3;
	pos[2] = 3;
	pos[3] = 1;

    dir[0] = -1;
    dir[1] = -1;
    dir[2] = -1;
    PaintCnt = ReszCnt = 0;
    Alpha = Beta = 0;
    SpeedAlpha = SpeedBeta = 100.0e5;
    Keys = new TKeysState;

    //hDC = ScrPaintBox->Canvas->Handle;
    //hDC = Canvas->Handle;
    hDC = GetDC(ScreenPanel->Handle);
    if(hDC == NULL)
    {
     AnsiString MS;
     MS = "hDC == " + IntToStr((int)hDC);
     Application->MessageBox(MS.c_str(),"",MB_OK);
    }
    Application->OnIdle = AppOnIdle;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    //long lStyle;
    ////wcl.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW
    //AnsiString Nm = ScrPaintBox->Name;
    //HWND hWnd = FindWindow("TPaintBox",NULL);
    //if(hWnd!=0) lStyle = GetWindowLong(ScreenPanel->Handle, GWL_STYLE);
    //else return;
    //WndStyle(lStyle);
    //ScreenPanel->Handle

    float color[4] = {1,1,1,1};
    //hDC
	//Canvas->Handle
	// устанавливаем параметры контекста воспроизведени€ OpenGL
   	SetWindowPixelFormat();

   	// создаем контекст воспроизведени€ OpenGL
   	hGLRC = wglCreateContext(hDC);

   	// делаем его текущим
   	wglMakeCurrent(hDC, hGLRC);

  	// далее см. предыдущий раздел
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
    pos[0] = -5;
    glLightfv(GL_LIGHT1, GL_POSITION, pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
    //glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    glClearColor(0, 0.6, 0, 0.5);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
        // удал€ем созданный выше
        // контекст воспроизведени€ OpenGL
        if (hGLRC)
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hGLRC);
        }

}
//---------------------------------------------------------------------------
int TMainForm::SetWindowPixelFormat()
{
    int m_GLPixelIndex;
    PIXELFORMATDESCRIPTOR pfd;


    pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion    = 1;

    pfd.dwFlags   = PFD_DRAW_TO_WINDOW |
                    PFD_SUPPORT_OPENGL |
                    PFD_DOUBLEBUFFER;

    pfd.iPixelType     = PFD_TYPE_RGBA;
    pfd.cColorBits     = 16;
    pfd.cRedBits       = 0;//pfd.cRedBits       = 8;
    pfd.cRedShift      = 0;//pfd.cRedShift      = 16;
    pfd.cGreenBits     = 0;//pfd.cGreenBits     = 8;
    pfd.cGreenShift    = 0;//pfd.cGreenShift    = 8;
    pfd.cBlueBits      = 0;//pfd.cBlueBits      = 8;
    pfd.cBlueShift     = 0;
    pfd.cAlphaBits     = 0;
    pfd.cAlphaShift    = 0;
    pfd.cAccumBits     = 64;
    pfd.cAccumRedBits  = 16;
    pfd.cAccumGreenBits   = 16;
    pfd.cAccumBlueBits    = 16;
    pfd.cAccumAlphaBits   = 0;
    pfd.cDepthBits        = 32;
    pfd.cStencilBits      = 8;
    pfd.cAuxBuffers       = 0;
    pfd.iLayerType        = PFD_MAIN_PLANE;
    pfd.bReserved         = 0;
    pfd.dwLayerMask       = 0;
    pfd.dwVisibleMask     = 0;
    pfd.dwDamageMask      = 0;



    m_GLPixelIndex = ChoosePixelFormat( hDC, &pfd);
    if(m_GLPixelIndex==0) // Let's choose a default index.
    {
     m_GLPixelIndex = 1;
     if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pfd)==0)
       return 0;
    }


    if (SetPixelFormat( hDC, m_GLPixelIndex, &pfd)==FALSE)
        return 0;


    return 1;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SnowMan(void)
{
    GLUquadricObj *quadObj;

 	quadObj = gluNewQuadric(); // создаем новый объект
                               // дл€ создани€ сфер и цилиндров
    if(quadObj == NULL)
    {
     return;
    }
    gluQuadricDrawStyle(quadObj, GLU_FILL); // устанавливаем
                               // стиль: сплошной


   	glPushMatrix();

	 glColor3d(0.75,0.75,0.75);

	 glTranslated(0,-3,0);
     gluSphere(quadObj, 2.0, 100, 100); // рисуем сферу
                                      // радиусом 0.5
	 //auxSolidSphere(2.0);

     glTranslated(0,3,0);
     gluSphere(quadObj, 1.5, 100, 100); // рисуем сферу
                                      // радиусом 0.5
	 //auxSolidSphere(1.5);

	 glTranslated(0,2,0);
     gluSphere(quadObj, 1.0, 100, 100); // рисуем сферу
                                      // радиусом 0.5
	 //auxSolidSphere(1);


	 glColor3d(0,0,0);

	 glTranslated(-0.3,0.3,1);
     gluSphere(quadObj, 0.1, 10, 10); // рисуем сферу
                                      // радиусом 0.5
	 //auxSolidSphere(0.1);

     glTranslated(0.6,0,0);
     gluSphere(quadObj, 0.1, 10, 10); // рисуем сферу
                                      // радиусом 0.5
	 //auxSolidSphere(0.1);

	 glTranslated(-0.3,-0.3,0);
	 glColor3d(1,0,0);
     gluCylinder(quadObj, 0.3, 0, 0.5, 100, 100);
	 //auxSolidCone(0.3,0.5);

	 glTranslated(0,0.75,-1);
     glColor3d(0,0,1);
   	 glRotated(-90,1,0,0);
     gluCylinder(quadObj, 0.75, 0, 0.75, 100, 100);
	 //auxSolidCone(0.75,0.75);

	glPopMatrix();

    gluDeleteQuadric(quadObj);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormResize(TObject *Sender)
{
 	// «десь вы указываете ту чать окна,
    // куда осуществл€етс€ вывод OpenGL.
    /*if(Width<Height)
    {
     glViewport(0,Height-Width/2,Width,Width);
    }
    else
    {
     glViewport(Width-Height/2,0,Height,Height);
    } */
    //glViewport(10,0,Width-10,Height-20);

    //ScreenPanel
    int x,y,w,h;
    w = ScreenPanel->ClientWidth;
    h = ScreenPanel->ClientHeight;
    if(w<h)
    {
     x = 0;
     y = (h-w)/2;
     h=w;
    }
    else
    {
     y = 0;
     x = (w-h)/2;
     w=h;
    }
    glViewport(x,y,w,h);
    //glViewport(0,0,w,h);
    //glViewport(0,0,Width,Height);


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

   	// ”станавливаем тип проекции.
   	// glOrtho - параллельна€
   	// glFrustum - перспективна€
   	// ѕараметры у этих функций одинаковые.
   	// ќни определ€ют объем, который вы видите.
   	// лева€ стенка - п€ть единиц влево
   	// права€ - п€ть единиц вправо
   	// далее, нижн€€ стенка и верхн€€
   	// и наконец, передн€€ и задн€€
   	// см. ниже картинку

   	glOrtho(-5,5, -5,5, 2,12);

    //if (w <= h)
    //glOrtho (-2.25, 2.25, -2.25*h/w, 2.25*h/w, -10.0, 10.0);
    //else
    //glOrtho (-2.25*w/h, 2.25*w/h, -2.25, 2.25, -10.0, 10.0);


   	// ”станавливаем точку, в которой
   	// находитс€ наш глаз ---(0,0,5)
   	// направление, куда смотрим --- (0,0,0)
   	// вектор, принимаемый за направление вверх --- (0,1,0)
   	// этим вектором €вл€етс€ ось Y

   	gluLookAt( 0,0,5, 0,0,0, 0,1,0 );

   	glMatrixMode( GL_MODELVIEW );
    //Repaint();

    Label2->Caption="ReszCnt = " + IntToStr(++ReszCnt);
}
//---------------------------------------------------------------------------
void TMainForm::WndStyle(long Style)
{
    //WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS
    AnsiString MS;
    MS = "Test WS_OVERLAPPEDWINDOW:" + IntToStr((Style & WS_OVERLAPPEDWINDOW)!=0 ? 1:0) + "\n" ;
    MS = MS + "Test WS_CLIPCHILDREN:" + IntToStr((Style & WS_CLIPCHILDREN)!=0 ? 1:0) + "\n" ;
    MS = MS + "Test WS_CLIPSIBLINGS:" + IntToStr((Style & WS_CLIPSIBLINGS)!=0 ? 1:0);
    Application->MessageBox(MS.c_str(),"",MB_OK);
}
//---------------------------------------------------------------------------




/*
 * (c) Copyright 1995-1999, Igor Tarasov
 * FidoNet: 2:5020/370.2 620.20 1103.5
 * Inet: itarasov@rtuis.miem.edu.ru
 * Phone: (095)942-50-97
 */

/*
#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>



void CALLBACK resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5, 2,12);
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}



void CALLBACK display(void)
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glPushMatrix();

	glColor3d(0.75,0.75,0.75);

	glTranslated(0,-3,0);
	auxSolidSphere(2.0);

    glTranslated(0,3,0);
	auxSolidSphere(1.5);

	glTranslated(0,2,0);
	auxSolidSphere(1);


	glColor3d(0,0,0);

	glTranslated(-0.3,0.3,1);
    auxSolidSphere(0.1);

    glTranslated(0.6,0,0);
    auxSolidSphere(0.1);

	glTranslated(-0.3,-0.3,0);
	glColor3d(1,0,0);
    auxSolidCone(0.3,0.5);

	glTranslated(0,0.75,-1);
    glColor3d(0,0,1);
	glRotated(-90,1,0,0);
    auxSolidCone(0.75,0.75);

  glPopMatrix();


    auxSwapBuffers();
}



void main()
{
	float pos[4] = {3,3,3,1};
	float dir[3] = {-1,-1,-1};

    auxInitPosition( 50, 10, 400, 400);
    auxInitDisplayMode( AUX_RGB | AUX_DEPTH | AUX_DOUBLE );
    auxInitWindow( "Snowman" );
    auxIdleFunc(display);
    auxReshapeFunc(resize);


    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	auxMainLoop(display);
}
*/
void __fastcall TMainForm::Display(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    AnalisateKey();
    // сохран€ем старое положение сцены
 	glPushMatrix();
  	 //вращаемс€ вокруг осей ’ и Y
     glRotated(Alpha, 0,1,0);
     glRotated(Beta, -1,0,0);
     SnowMan();
	//возвращаем координату на место
 	glPopMatrix();

	glFinish();
	SwapBuffers(wglGetCurrentDC());

    Label1->Caption="PaintCnt = " + IntToStr(++PaintCnt);
}
void __fastcall TMainForm::AppOnIdle(TObject *Sender,bool &R)
{
	Repaint();
    if( Keys->PressingKeyCount !=0) R = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PaintTimerTimer(TObject *Sender)
{
	//Display();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormHide(TObject *Sender)
{
	PaintTimer->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	PaintTimer->Enabled = false;
	//PaintTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	Keys->PressKey(Key,Shift);
 	ShiftState = Shift;
    Label3->Caption="TimePress == " + AnsiString((double)(Keys->Key[Keys->ExistKey(Key)]->TimePress));
    Label4->Caption= "PressingKeyCount == " + IntToStr(Keys->PressingKeyCount);
    if( Keys->PressingKeyCount !=0)
    Label4->Caption += "; Key[0] == " + IntToStr(Keys->Key[0]->Key);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	Keys->UnPressKey(Key,Shift);
 	ShiftState = Shift;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormPaint(TObject *Sender)
{
	Display();
}
/*
VK_SPACE          0x20
VK_PRIOR          0x21
VK_NEXT           0x22
VK_END            0x23
VK_HOME           0x24
VK_LEFT           0x25
VK_UP             0x26
VK_RIGHT          0x27
VK_DOWN           0x28
VK_SELECT         0x29
VK_PRINT          0x2A
VK_EXECUTE        0x2B
VK_SNAPSHOT       0x2C
VK_INSERT         0x2D
VK_DELETE         0x2E

VK_F1             0x70
VK_F2             0x71
VK_F3             0x72
VK_F4             0x73
VK_F5             0x74
VK_F6             0x75
VK_F7             0x76
VK_F8             0x77
VK_F9             0x78
VK_F10            0x79
VK_F11            0x7A
VK_F12            0x7B
VK_F13            0x7C
VK_F14            0x7D
VK_F15            0x7E
VK_F16            0x7F
VK_F17            0x80
VK_F18            0x81
VK_F19            0x82
VK_F20            0x83
VK_F21            0x84
VK_F22            0x85
VK_F23            0x86
VK_F24            0x87

VK_NUMPAD0        0x60
VK_NUMPAD1        0x61
VK_NUMPAD2        0x62
VK_NUMPAD3        0x63
VK_NUMPAD4        0x64
VK_NUMPAD5        0x65
VK_NUMPAD6        0x66
VK_NUMPAD7        0x67
VK_NUMPAD8        0x68
VK_NUMPAD9        0x69

*/
//---------------------------------------------------------------------------
void __fastcall TMainForm::AnalisateKey(void)
{
    TKeyState *Kl;
    TDateTime Curr;

    Curr = Curr.CurrentDateTime();
    //SpeedBeta;
    //SpeedAlpha;
	for(int i = 0; i < Keys->PressingKeyCount; i++)
    {
     Kl = Keys->Key[i];
     switch(Kl->Key)
     {
      case 'A'://VK_LEFT:
       Alpha += ShiftSpeed(ShiftState)*SpeedAlpha*((double)(Curr - Kl->TimePress));
       Label2->Caption="Curr - TimePress == " + AnsiString(SpeedAlpha*((double)(Curr - Kl->TimePress)));
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
     }
    }
}
//---------------------------------------------------------------------------
float __fastcall TMainForm::ShiftSpeed(TShiftState Shift)
{
    float f = 1.0;
    //ssShift, ssAlt, ssCtrl, ssLeft, ssRight
    if(Shift.Contains(ssShift)) f *=2;
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
    }

}
//---------------------------------------------------------------------------
