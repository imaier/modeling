//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "GLDrow.h"
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>
HGLRC hGLRC;
HDC hDC;
bool Initialiseded;
float pos[4];
float dir[3];
//---------------------------------------------------------------------------
//int InitGL(HWND Handle)
int InitGL(HDC HandleDC)
{
    float color[4] = {1,1,1,1};
    //hDC = GetDC(Handle);
    hDC = HandleDC;
	// устанавливаем параметры контекста воспроизведени€ OpenGL
   	if(!SetWindowPixelFormat(hDC)) return 0;

   	// создаем контекст воспроизведени€ OpenGL
   	hGLRC = wglCreateContext(hDC);

   	// делаем его текущим
   	wglMakeCurrent(hDC, hGLRC);

    //создаЄм шрифт
    LOGFONT f;

    memset(&f, sizeof(f), 0);
    //определ€ем размер шрифта
    f.lfHeight = -MulDiv(12, GetDeviceCaps(hDC, LOGPIXELSY), 72);
    //параметры начертани€
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
    BOOL bRet = wglUseFontBitmaps (hDC, 0, 255, 1000);
    //GLYPHMETRICSFLOAT agmf[256];
    //GLYPHMETRICSFLOAT *pagmf = agmf;
    //BOOL bRet = wglUseFontOutlines(hDC, '0','0'+9 , 1000, 0.0f, 0.1f, WGL_FONT_POLYGONS, pagmf);
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
    glListBase (1000);


  	// далее см. предыдущий раздел
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //float pos[4];
	//float dir[3];
	pos[0] = 3;
	pos[1] = 3;
	pos[2] = 3;
	pos[3] = 1;

    dir[0] = -1;
    dir[1] = -1;
    dir[2] = -1;

    //float ambient[4] = {0.7, 0.7, 0.7, 1};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 10.0);
    //pos[0] = 0;
    //pos[1] = 15;
    //pos[2] = 0;
    //dir[0] = 0;
    //dir[1] = 0;
    //dir[2] = 0;
    glLightfv(GL_LIGHT1, GL_POSITION, pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color);

    //glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION, 0.5);
    glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION, 0.01);
    //glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION, 0.0);
    //glLightf(GL_LIGHT0,GL_SPOT_CUTOFF, 180.0);
    //color[0] = 0.7;
    //color[1] = 0.7;
    //color[2] = 0.7;
    pos[0] = -3;
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);

    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 10;
    dir[0] = 0;
    dir[0] = 0;
    dir[0] = 0;
    glLightfv(GL_LIGHT3, GL_POSITION, pos);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, color);


    pos[0] = 100;
    pos[1] = 0;
    pos[2] = -1000;
    dir[0] = 0;
    dir[0] = 0;
    dir[0] = 0;
    glLightfv(GL_LIGHT4, GL_POSITION, pos);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, color);


    pos[0] = 1000;
    pos[1] = 0;
    pos[2] = 1000;
    dir[0] = 0;
    dir[0] = 0;
    dir[0] = 0;
    glLightfv(GL_LIGHT5, GL_POSITION, pos);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, color);

    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 1000;
    dir[0] = 0;
    dir[0] = 0;
    dir[0] = 0;
    glLightfv(GL_LIGHT6, GL_POSITION, pos);
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, dir);
    glLightfv(GL_LIGHT6, GL_DIFFUSE, color);

    //pos[0] = -5;
    //glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    //glClearColor(0, 0.6, 0, 0.5);
    //glClearColor(1.0, 1.0, 1.0, 0.5);
    glClearColor(0, 0, 0, 0.5);
    glLineWidth(2.0);
    glPointSize(10.0);
	glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_FOG);
    //glFogf(GL_FOG_DENSITY,0.1);
    //glFogf(GL_FOG_START,0.5);

    Initialiseded = true;
    return 1;
}
//---------------------------------------------------------------------------
void ExitGL(void)
{
	// удал€ем созданный выше
    // контекст воспроизведени€ OpenGL
    if (hGLRC)
    {
     wglMakeCurrent(NULL, NULL);
     wglDeleteContext(hGLRC);
     hGLRC = NULL;
    }
    Initialiseded = false;
}
//---------------------------------------------------------------------------
int SetWindowPixelFormat(HDC hDC,bool fbitmap )
{
    int m_GLPixelIndex;
    PIXELFORMATDESCRIPTOR pfd, *ppdf;


    pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion    = 1;

//    pfd.dwFlags   = ((fbitmap)?PFD_DRAW_TO_BITMAP:PFD_DRAW_TO_WINDOW) |
    pfd.dwFlags   = PFD_DRAW_TO_WINDOW |
                    PFD_SUPPORT_OPENGL |
                    PFD_DOUBLEBUFFER;

    pfd.iPixelType     = PFD_TYPE_RGBA;//PFD_TYPE_COLORINDEX
    pfd.cColorBits     = 16;//1
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

PIXELFORMATDESCRIPTOR pfd2 = {
	sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
	1,                     // version number
    //PFD_DRAW_TO_BITMAP |
	PFD_DRAW_TO_WINDOW |   // support window
	PFD_SUPPORT_OPENGL |   // support OpenGL
	PFD_DOUBLEBUFFER,      // double buffered
	PFD_TYPE_RGBA,         // RGBA type
	24,                    // 24-bit color depth
	0, 0, 0, 0, 0, 0,      // color bits ignored
	0,                     // no alpha buffer
	0,                     // shift bit ignored
    0,                     // no accumulation buffer
	0, 0, 0, 0,            // accum bits ignored
	32,                    // 32-bit z-buffer
	0,                     // no stencil buffer
	0,                     // no auxiliary buffer
	PFD_MAIN_PLANE,        // main layer
	0,                     // reserved
	0, 0, 0                // layer masks ignored
	};

    ppdf = &pfd2;
    m_GLPixelIndex = ChoosePixelFormat( hDC, ppdf);
    //m_GLPixelIndex = 3;
    if(m_GLPixelIndex==0) // Let's choose a default index.
    {
     m_GLPixelIndex = 1;
     if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),ppdf)==0)
       return 0;
    }

    Sleep(200);
    if (SetPixelFormat( hDC, m_GLPixelIndex, ppdf)==FALSE)
        return 0;

    return 1;
}
//---------------------------------------------------------------------------
void __fastcall SnowMan(void)
{
    GLUquadricObj *quadObj;
    int Qality = 15;
 	quadObj = gluNewQuadric(); // создаем новый объект
                               // дл€ создани€ сфер и цилиндров
    if(quadObj == NULL)
    {
     return;
    }
    gluQuadricDrawStyle(quadObj, GLU_FILL); // устанавливаем GLU_LINE GLU_FILL
                               // стиль: сплошной


   	glPushMatrix();

	 //glColor3d(0.75,0.75,0.75);
	 //glColor3f(0.75,0.75,0.75);
	 //glColor3i(175,175,175);
	 glColor3ub(255*0.75,255*0.75,255*0.75);
	 //glColor3ub(127,127,127);

	 //glTranslated(0,-3,0);
	 glTranslatef(0,-3.0,0);
     gluSphere(quadObj, 2.0, Qality, Qality); // рисуем сферу
                                      // радиусом 0.5
	 //auxSolidSphere(2.0);

     glTranslated(0,3,0);
     gluSphere(quadObj, 1.5, Qality, Qality); // рисуем сферу
                                      // радиусом 0.5
	 //auxSolidSphere(1.5);

	 glTranslated(0,2,0);
     gluSphere(quadObj, 1.0, Qality, Qality); // рисуем сферу
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
     gluCylinder(quadObj, 0.3, 0, 0.5, Qality, Qality);
	 //auxSolidCone(0.3,0.5);

	 glTranslated(0,0.75,-1);
     glColor3d(0,0,1);
   	 glRotated(-90,1,0,0);
     gluCylinder(quadObj, 0.75, 0, 0.75, Qality, Qality);
	 //auxSolidCone(0.75,0.75);

	glPopMatrix();

    gluDeleteQuadric(quadObj);
}
//---------------------------------------------------------------------------
void __fastcall ResizeGL(int w, int h)
{
    static int oldW = 0,oldH = 0;
 	// «десь вы указываете ту чать окна,
    // куда осуществл€етс€ вывод OpenGL.
    /*if(Width<Height)
    {
     glViewport(0,Height-Width/2,Width,Width);
    }
    else
    {
     glViewport(Width-Height/2,0,Height,Height);
    }
    //glViewport(10,0,Width-10,Height-20);
    */
    //ScreenPanel
    /*int x,y;
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
    */
    //glViewport(0,0,w>h?w:h,w>h?w:h);
    if((oldW != 0) && (oldH != 0)) glScalef(oldW/(float)(oldW<oldH?oldW:oldH),oldH/(float)(oldW<oldH?oldW:oldH),1);
    glScalef((w<h?w:h)/(float)w,(w<h?w:h)/(float)h,1);
    oldW = w;
    oldH = h;

    glViewport(0,0,w,h);
    //glViewport(0,0,Width,Height);


    //glMatrixMode( GL_PROJECTION );
    //glLoadIdentity();

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
	//glTranslated(0,0,-1);

    //glFrustum(-1,1, -1,1, 1,100);

   	//glOrtho(-5,5, -5,5, 0,12);
	//glTranslated(0,0,2);

    //if (w <= h)
    //glOrtho (-2.25, 2.25, -2.25*h/w, 2.25*h/w, -10.0, 10.0);
    //else
    //glOrtho (-2.25*w/h, 2.25*w/h, -2.25, 2.25, -10.0, 10.0);


   	// ”станавливаем точку, в которой
   	// находитс€ наш глаз ---(0,0,5)
   	// направление, куда смотрим --- (0,0,0)
   	// вектор, принимаемый за направление вверх --- (0,1,0)
   	// этим вектором €вл€етс€ ось Y

   	//gluLookAt( 0,0,10, 0,0,0, 0,1,0 );

   	//glMatrixMode( GL_MODELVIEW );

    //Repaint();

    //Label2->Caption="ReszCnt = " + IntToStr(++ReszCnt);
}
//---------------------------------------------------------------------------
/*void __fastcall Display(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //AnalisateKey();
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

    //Label1->Caption="PaintCnt = " + IntToStr(++PaintCnt);
}
*/
//---------------------------------------------------------------------------

