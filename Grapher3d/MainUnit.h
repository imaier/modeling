//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <GL/gl.h>
#include <GL/glu.h>
#include <map.h>
//---------------------------------------------------------------------------
#include "ScreenCopyUnit.h"
#include "MillersUnit.h"
//---------------------------------------------------------------------------
#define WM_COPYSCREENSHOT WM_USER+1
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
struct TScreenShootData
{
    int Code;
    Graphics::TBitmap *Bitmap;
    int AllW, AllH, Qual;
    int MaxW,MaxH,CW,CH,NW,NH,i,j;
    float lp,rp,tp,bp;
    float XPort, YPort;
    TRect CurrentRect;
    bool PrintIndex;
};
//---------------------------------------------------------------------------
class TOrientation
{
public:
	GLfloat vMatix[16];
	GLdouble Xt, Yt, Zt;
    GLdouble MultiAngle;
    GLdouble MultiSpeed;
    GLdouble Scale;
};
//---------------------------------------------------------------------------
struct TObjColor
{
    float r,g,b;
};
//---------------------------------------------------------------------------
struct TSphera
{
    double x,y,z,r;
    int c,n;
	int LineNumber;
	AnsiString NumberName;//номер с нулями спереди как в файле
	TObjColor Color;
};
typedef map<int,TSphera*> TSpheraMap;
typedef TSpheraMap::iterator TSpheraMap_iter;
//---------------------------------------------------------------------------
struct TLine
{
	double x1,y1,z1,x2,y2,z2,w;
	int c,n,ns1,ns2;
	int LineNumber;
	AnsiString NumberName;//номер с нулями спереди как в файле
	TObjColor Color;
};
typedef map<int,TLine*> TLineMap;
typedef TLineMap::iterator TLineMap_iter;
//---------------------------------------------------------------------------
struct TCilinder
{
	double x1,y1,z1,x2,y2,z2,w;
	int c,n,ns1,ns2;
	int LineNumber;
	AnsiString NumberName;//номер с нулями спереди как в файле
	TObjColor Color;//цвет цилиндра
	TObjColor Color1;//цвет первой сферы
    TObjColor Color2;//цвет второй сферы
};
typedef map<int,TCilinder*> TCilinderMap;
typedef TCilinderMap::iterator TCilinderMap_iter;
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TMenuItem *FileMenuItem;
    TMenuItem *OpenMenuItem;
    TMenuItem *ExitMenuItem;
    TStatusBar *StatusBar;
    TToolBar *ToolBar;
    TPanel *OpenGLPanel;
    TApplicationEvents *ApplicationEvents;
    TPanel *Panel2;
    TLabel *MillersIndexesLabel;
    TLabel *MillersLabel;
    TPanel *Panel3;
    TPanel *Panel4;
    TSpeedButton *StepUpSpeedButton;
    TSpeedButton *StepDownSpeedButton;
    TLabel *MulSpeedLabel;
    TSpeedButton *RightMoveSpeedButton;
    TSpeedButton *LeftMoveSpeedButtonSpeedButton;
    TSpeedButton *UpMoveSpeedButton;
    TSpeedButton *DownMoveSpeedButton;
    TSpeedButton *FrontMoveSpeedButton;
    TSpeedButton *BackMoveSpeedButton;
    TSpeedButton *XLocalBackSpeedButton;
    TSpeedButton *XLocalFrontSpeedButton;
    TSpeedButton *YLocalRightSpeedButton;
    TSpeedButton *YLocalLeftSpeedButton;
    TSpeedButton *ZLocalClockwiseSpeedButton;
    TSpeedButton *ZLocalAnticlockwiseSpeedButton;
    TSpeedButton *XGlobalBackSpeedButton;
    TSpeedButton *XGlobalFrontSpeedButton;
    TSpeedButton *YGlobalRightSpeedButton;
    TSpeedButton *YGlobalLeftSpeedButton;
    TSpeedButton *ZGlobalClockwiseSpeedButton;
    TSpeedButton *ZGlobalAnticlockwiseSpeedButton;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TLabel *MulAngleLabel;
    TLabel *OrthoLabel;
    TLabel *OrthoMillersIndexesLabel;
    TOpenDialog *OpenDialog;
    TPanel *Panel1;
    TSpeedButton *INSpeedButton;
    TLabel *ScaleLabel;
    TSpeedButton *OUTSpeedButton;
    TPanel *Panel5;
    TCheckBox *AxisCheckBox;
    TSpeedButton *CopySpeedButton;
    TSpeedButton *OpenSpeedButton;
    TSpeedButton *ExitSpeedButton;
    TComboBox *MillersComboBox;
    TSpeedButton *InfoSpeedButton;
    TPanel *Panel6;
    TEdit *CxEdit;
    TLabel *CxLabel;
    TEdit *CyEdit;
    TLabel *CyLabel;
    TLabel *CzLabel;
    TEdit *CzEdit;
    TComboBox *ObjectCenterComboBox;
    TSpeedButton *CenterSpeedButton;
    TSpeedButton *AutocenterSpeedButton;
    TMenuItem *N1;
    TMenuItem *WhiteBackgroundMenuItem;
    TPanel *Panel7;
    TSpeedButton *DiamUpSpeedButton;
    TSpeedButton *DiamDownSpeedButton;
    TLabel *DiamLabel;
    TCheckBox *DrawLineCheckBox;
    TCheckBox *DrawSpherasCheckBox;
    TSpeedButton *SaveOrientationSpeedButton;
    TSpeedButton *MillersSpeedButton;
    TComboBox *SaveOrientationComboBox;
    TSpeedButton *SaveOrientationListSpeedButton;
    TSpeedButton *OpenOrientationListSpeedButton;
    TSaveDialog *OrientationSaveDialog;
    TOpenDialog *OrientationOpenDialog;
	TCheckBox *DrawCilindersCheckBox;
    void __fastcall OpenMenuItemClick(TObject *Sender);
    void __fastcall ExitMenuItemClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall OpenGLPanelResize(TObject *Sender);
    void __fastcall ApplicationEventsIdle(TObject *Sender, bool &Done);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall AxisCheckBoxClick(TObject *Sender);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall StepUpSpeedButtonClick(TObject *Sender);
    void __fastcall StepDownSpeedButtonClick(TObject *Sender);
    void __fastcall AngleUpSpeedButtonClick(TObject *Sender);
    void __fastcall AngleDownSpeedButtonClick(TObject *Sender);
    void __fastcall RightMoveSpeedButtonClick(TObject *Sender);
    void __fastcall LeftMoveSpeedButtonSpeedButtonClick(TObject *Sender);
    void __fastcall UpMoveSpeedButtonClick(TObject *Sender);
    void __fastcall DownMoveSpeedButtonClick(TObject *Sender);
    void __fastcall FrontMoveSpeedButtonClick(TObject *Sender);
    void __fastcall BackMoveSpeedButtonClick(TObject *Sender);
    void __fastcall XLocalBackSpeedButtonClick(TObject *Sender);
    void __fastcall XLocalFrontSpeedButtonClick(TObject *Sender);
    void __fastcall YLocalRightSpeedButtonClick(TObject *Sender);
    void __fastcall YLocalLeftSpeedButtonClick(TObject *Sender);
    void __fastcall ZLocalClockwiseSpeedButtonClick(TObject *Sender);
    void __fastcall ZLocalAnticlockwiseSpeedButtonClick(TObject *Sender);
    void __fastcall XGlobalBackSpeedButtonClick(TObject *Sender);
    void __fastcall XGlobalFrontSpeedButtonClick(TObject *Sender);
    void __fastcall YGlobalRightSpeedButtonClick(TObject *Sender);
    void __fastcall YGlobalLeftSpeedButtonClick(TObject *Sender);
    void __fastcall ZGlobalClockwiseSpeedButtonClick(TObject *Sender);
    void __fastcall ZGlobalAnticlockwiseSpeedButtonClick(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall INSpeedButtonClick(TObject *Sender);
    void __fastcall OUTSpeedButtonClick(TObject *Sender);
    void __fastcall CopySpeedButtonClick(TObject *Sender);
    void __fastcall MillersComboBoxDropDown(TObject *Sender);
    void __fastcall MillersComboBoxChange(TObject *Sender);
    void __fastcall OpenGLPanelMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
    void __fastcall InfoSpeedButtonClick(TObject *Sender);
    void __fastcall CxEditEnter(TObject *Sender);
    void __fastcall CxEditExit(TObject *Sender);
    void __fastcall CxEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall CenterSpeedButtonClick(TObject *Sender);
    void __fastcall ObjectCenterComboBoxChange(TObject *Sender);
    void __fastcall AutocenterSpeedButtonClick(TObject *Sender);
    void __fastcall WhiteBackgroundMenuItemClick(TObject *Sender);
    void __fastcall DiamUpSpeedButtonClick(TObject *Sender);
    void __fastcall DiamDownSpeedButtonClick(TObject *Sender);
    void __fastcall MillersSpeedButtonClick(TObject *Sender);
    void __fastcall SaveOrientationSpeedButtonClick(TObject *Sender);
    void __fastcall SaveOrientationComboBoxChange(TObject *Sender);
    void __fastcall SaveOrientationComboBoxCloseUp(TObject *Sender);
    void __fastcall SaveOrientationListSpeedButtonClick(TObject *Sender);
    void __fastcall OpenOrientationListSpeedButtonClick(TObject *Sender);
private:	// User declarations
    GLdouble XPort,YPort,Near,Far;
    GLdouble EyeX;
	GLdouble EyeY;
	GLdouble EyeZ;
	GLdouble CenterX;
	GLdouble CenterY;
	GLdouble CenterZ;
	GLdouble UpX;
	GLdouble UpY;
	GLdouble UpZ;
    GLdouble Roll;
	GLdouble AlphaT, BetaT, GammaT;
	GLdouble AlphaG, BetaG, GammaG;
	GLdouble AlphaW, BetaW, GammaW;
    GLdouble MultiAngle;
	GLdouble SpeedXT, SpeedYT, SpeedZT;
	GLdouble SpeedXW, SpeedYW, SpeedZW;
	GLdouble CenterXT, CenterYT, CenterZT;
    GLdouble MultiSpeed;

    GLdouble MultiDiam;
    bool Loaded;
    bool AxisX,AxisY,AxisZ;
    bool EnabledPaint;
    Classes::TShiftState ShiftState;

	TSpheraMap Spheras;
    TLineMap Lines;
	TCilinderMap Cilinders;
    GLint Qality;

    GLdouble Scale;
    TScreenShootData SSD;
    TPoint ScreenPanelMousePoint;
    AnsiString m_strDefaultCaption;
    AnsiString m_strFileNameCaption;
    TMillersIndexes MI;//индексы миилера для формы индексов миллера
    bool PrintIndex;//флаг отображения индексов миллера на 3d-изображении


    void __fastcall SetCamera(void);
    void __fastcall DirectAlongZ(GLdouble &X, GLdouble &Y,GLdouble &Z);
    void __fastcall Display(void);
    void __fastcall RotateAroundWoldAxises(GLdouble Alpha, GLdouble Beta, GLdouble Gamma);
    void __fastcall DisplayAxis(bool X, bool Y, bool Z);
	float __fastcall ShiftSpeed(TShiftState Shift);
    void __fastcall DrawList(void);
    bool __fastcall LoadFile(AnsiString FileName);
    AnsiString __fastcall GetParam(AnsiString &Params, AnsiString ExeptStr = "неизвестная ошибка");
    void __fastcall ClearLists(void);
    void __fastcall AcceptScale(void);
    bool __fastcall DecodeColor(AnsiString Str, TObjColor &color);
    void __fastcall SpheraPriview(void);
    void __fastcall SetCaption(AnsiString FileName);
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);

    void __fastcall CopySreenShot(TMessage* Msg);

    BEGIN_MESSAGE_MAP;
     MESSAGE_HANDLER(WM_COPYSCREENSHOT, TMessage*, CopySreenShot);
    END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
