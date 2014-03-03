//---------------------------------------------------------------------------
#ifndef GLDrowH
#define GLDrowH
//---------------------------------------------------------------------------
extern HGLRC hGLRC;
extern HDC hDC;
extern bool Initialiseded;
extern float pos[4];
extern float dir[3];
//int PaintCnt,ReszCnt;
//---------------------------------------------------------------------------
//int InitGL(HWND Handle);
int InitGL(HDC HandleDC);
void ExitGL(void);
void __fastcall SnowMan(void);
void __fastcall ResizeGL(int w, int h);
//void __fastcall Display(void);
int SetWindowPixelFormat(HDC hDC,bool fbitmap = false);
//---------------------------------------------------------------------------
#endif
