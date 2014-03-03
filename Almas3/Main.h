//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Menus.hpp>
//---------------------------------------------------------------------------
#include "Dissolution.h"
#include "KeysControl.h"
#include "PropertyUnit.h"
#include <vcl\Dialogs.hpp>
#include <ToolWin.hpp>
#include "MillersUnit.h"
//---------------------------------------------------------------------------
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>
//---------------------------------------------------------------------------
#define SELECT_MASK_INVISIBLE   0x80 //маска для невидимых атомов при обрезке
#define SELECT_MASK_SELECT      0x40 //маска для выделения выделенных пользователем атомов
#define SELECT_MASK_GROUPE      0x20 //маска для подсветки атомов определённого типа
#define SELECT_MASK_TYPE        0x1F //маска для выделения типов атомов
//---------------------------------------------------------------------------
#define WM_COPYSCREENSHOT WM_USER+1
#define WM_CAPTUREVIDEO   WM_USER+2
//---------------------------------------------------------------------------
class TClipPlane //класс для воссановления обрезки
{
public:
    GLfloat FirstRowPM[4];//первая строка матрицы GL_MODELVIEW_MATRIX с учетом смещений и нормали
    TClipPlane();
    TClipPlane(const TClipPlane &cp);
    void operator = (const TClipPlane &cp);
    bool WriteToFile(int hFile);
    bool LoadFromFile(int hFile);
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
    std::vector<TClipPlane> m_vClipPlane;

    TOrientation();
    ~TOrientation();
    TOrientation(const TOrientation &orn);
    void operator = (const TOrientation &orn);
    bool WriteToFile(int hFile);
    bool LoadFromFile(int hFile);
};
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
    //для захвата видеоряда
    int m_nCaptureCode;
    bool m_bCapture;
    int m_nFrom;
    int m_nStep;
    int m_nTo;
    bool m_bSeveralOrn;
    AnsiString m_strBaseName;
    AnsiString m_strDir;
    AnsiString m_strCurrFileName;
    int m_nOrnIndex;//индекс ориетации
    TOrientation m_BaseOrn;//базовая ориентация
};
//---------------------------------------------------------------------------
void DispError(void);
//---------------------------------------------------------------------------
struct TUndo
{
    int i;
    TUndoDissolutionThread UDT;
};
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *ProgressPanel;
	TStatusBar *StatusBar1;
	TSpeedButton *OpenSfsSpeedButton;
	TSpeedButton *ProrertySpeedButton;
	TTimer *Timer;
	TLabel *N1Label;
	TLabel *N3Label;
	TLabel *N2Label;
	TSpeedButton *MonitoringSpeedButton;
	TSpeedButton *PhotoSpeedButton;
	TPanel *ScreenPanel;
	TLabel *PaintCntLabel;
	TSpeedButton *SurfaceSpeedButton;
	TLabel *MillersIndexesLabel;
	TComboBox *MillersComboBox;
	TComboBox *SaveOrientationComboBox;
	TSpeedButton *SaveOrientationSpeedButton;
	TLabel *MulAngleLabel;
	TLabel *MulSpeedLabel;
	TSpeedButton *RightMoveSpeedButton;
	TSpeedButton *LeftMoveSpeedButtonSpeedButton;
	TSpeedButton *UpMoveSpeedButton;
	TSpeedButton *DownMoveSpeedButton;
	TSpeedButton *FrontMoveSpeedButton;
	TSpeedButton *BackMoveSpeedButton;
	TSpeedButton *SpeedButton8;
	TSpeedButton *SpeedButton9;
	TSpeedButton *SpeedButton10;
	TSpeedButton *SpeedButton11;
	TSpeedButton *SpeedButton12;
	TSpeedButton *SpeedButton13;
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
	TCheckBox *AxisCheckBox;
	TCheckBox *LinksCheckBox;
	TSpeedButton *StepUpSpeedButton;
	TSpeedButton *StepDownSpeedButton;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *AngleUpSpeedButton;
	TSpeedButton *AngleDownSpeedButton;
	TSpeedButton *INSpeedButton;
	TSpeedButton *OUTSpeedButton;
	TLabel *ScaleLabel;
	TSpeedButton *SaveSfsSpeedButton;
	TSaveDialog *SfsSaveDialog;
	TOpenDialog *SfsOpenDialog;
	TPanel *SetUpPanel;
	TPanel *StatStopPanel;
	TLabel *StatPauseLabel;
	TLabel *DeletedLabel;
	TPanel *StopPanel;
	TPanel *ChangePanel;
	TSpeedButton *ChangeSpeedButton;
	TSpeedButton *AnalizViewSpeedButton;
    TSpeedButton *ClearInvisibleBitSpeedButton;
	TSpeedButton *LeftRightSpeedButton;
	TSpeedButton *AppOrientationSpeedButton;
	TSpeedButton *ShowClipPlaneSpeedButton;
    TComboBox *AtomsColorsComboBox;
    TLabel *AtomsColorsLabel;
    TCheckBox *DepthCheckBox;
    TLabel *AtomSizeLabel;
    TSpeedButton *AtomSizeUpSpeedButton;
    TSpeedButton *AtomSizeDownSpeedButton;
    TLabel *XLabel;
    TSpeedButton *OpenABASpeedButton;
    TSpeedButton *SaveABASpeedButton;
    TSpeedButton *DelHoldSpeedButton;
    TCoolBar *DelCoolBar;
    TPageScroller *DefectPageScroller;
    TPanel *DelPanel;
    TBevel *DelBevel3;
    TBevel *ListsHoldBevel;
    TLabel *Label1;
    TBevel *ListsDelBevel;
    TLabel *Label4;
    TLabel *Label7;
    TSpeedButton *BackDelsSpeedButton;
    TSpeedButton *BackHoldsSpeedButton;
    TBevel *Bevel2;
    TComboBox *DelComboBox;
    TComboBox *HoldComboBox;
    TPageScroller *CoordPageScroller;
    TPanel *CoordPanel;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label3;
    TBevel *CoordBevel1;
    TLabel *Label2;
    TSpeedButton *HoldSpeedButton;
    TSpeedButton *DelSpeedButton;
    TBevel *CoordBevel2;
    TBevel *Bevel1;
    TSpeedButton *ListsSpeedButton;
    TSpeedButton *Adjacent1SpeedButton;
    TSpeedButton *Adjacent2SpeedButton;
    TSpeedButton *Adjacent3SpeedButton;
    TSpeedButton *Adjacent4SpeedButton;
    TBevel *Bevel3;
    TLabel *Label8;
    TEdit *YEdit;
    TEdit *ZEdit;
    TEdit *XEdit;
    TLabel *OrthoMillersIndexesLabel;
    TCheckBox *PointsCheckBox;
    TSpeedButton *CopySpeedButton;
    TSpeedButton *ShowSurfPanelSpeedButton;
    TCoolBar *SurfCoolBar;
    TPanel *SurfacePanel;
    TSpeedButton *SurfSpeedButton;
    TBevel *Bevel5;
    TBevel *Bevel6;
    TBevel *Bevel7;
    TBevel *Bevel4;
    TCheckBox *GraniCheckBox;
    TSpeedButton *ExportIntoMatlabSpeedButton;
    TComboBox *SecondTypeComboBox;
    TSpeedButton *DelInvisibleSpeedButton;
        TSpeedButton *MillersSpeedButton;
    TSpeedButton *SaveOrientationListSpeedButton;
    TSpeedButton *OpenOrientationListSpeedButton;
    TSaveDialog *OrientationSaveDialog;
    TOpenDialog *OrientationOpenDialog;
    TSpeedButton *LayerSpeedButton;
    TSpeedButton *CentrSpeedButton;
	void __fastcall StatusBar1DrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel,
	const TRect &Rect);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall StatStopPanelMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall StatStopPanelMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall MonitoringSpeedButtonClick(TObject *Sender);
	void __fastcall StopPanelMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall StopPanelMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall StopPanelClick(TObject *Sender);
	void __fastcall AppOnIdle(TObject *Sender,bool &R);
	//void __fastcall AppOnHint(TObject *Sender,bool &R);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall PhotoSpeedButtonClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ScreenPanelResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall SurfaceSpeedButtonClick(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MillersComboBoxChange(TObject *Sender);
	void __fastcall MillersComboBoxDropDown(TObject *Sender);
	void __fastcall SaveOrientationComboBoxChange(TObject *Sender);
	void __fastcall ScreenPanelMouseMove(TObject *Sender, TShiftState Shift, int X,
	int Y);
	void __fastcall SaveOrientationSpeedButtonClick(TObject *Sender);
	void __fastcall MillersComboBoxClick(TObject *Sender);
	void __fastcall ScreenPanelClick(TObject *Sender);


	void __fastcall ProrertySpeedButtonClick(TObject *Sender);
	
	void __fastcall LinksCheckBoxClick(TObject *Sender);
	void __fastcall AxisCheckBoxMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);


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

	void __fastcall INSpeedButtonClick(TObject *Sender);
	void __fastcall OUTSpeedButtonClick(TObject *Sender);
	void __fastcall SaveSfsSpeedButtonClick(TObject *Sender);
	
	void __fastcall OpenSfsSpeedButtonClick(TObject *Sender);
	void __fastcall StatStopPanelClick(TObject *Sender);

	void __fastcall ChangeSpeedButtonClick(TObject *Sender);
	
	void __fastcall AppOrientationSpeedButtonClick(TObject *Sender);
	void __fastcall ClearInvisibleBitSpeedButtonClick(TObject *Sender);
    void __fastcall AtomsColorsComboBoxChange(TObject *Sender);
    void __fastcall DepthCheckBoxClick(TObject *Sender);
    void __fastcall AtomSizeUpSpeedButtonClick(TObject *Sender);
    void __fastcall AtomSizeDownSpeedButtonClick(TObject *Sender);
    void __fastcall ListsSpeedButtonClick(TObject *Sender);
    void __fastcall DelHoldSpeedButtonClick(TObject *Sender);
    void __fastcall XEditEnter(TObject *Sender);
    void __fastcall XEditExit(TObject *Sender);
    void __fastcall XEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall XEditKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall DelSpeedButtonClick(TObject *Sender);
    void __fastcall HoldSpeedButtonClick(TObject *Sender);
    void __fastcall Adjacent1SpeedButtonClick(TObject *Sender);
    void __fastcall Adjacent2SpeedButtonClick(TObject *Sender);
    void __fastcall Adjacent3SpeedButtonClick(TObject *Sender);
    void __fastcall Adjacent4SpeedButtonClick(TObject *Sender);
    void __fastcall BackDelsSpeedButtonClick(TObject *Sender);
    void __fastcall OpenABASpeedButtonClick(TObject *Sender);
    void __fastcall SaveABASpeedButtonClick(TObject *Sender);
    void __fastcall PointsCheckBoxClick(TObject *Sender);
    void __fastcall CopySpeedButtonClick(TObject *Sender);
    void __fastcall ShowSurfPanelSpeedButtonClick(TObject *Sender);
    void __fastcall SurfSpeedButtonClick(TObject *Sender);
    void __fastcall ExportIntoMatlabSpeedButtonClick(TObject *Sender);
    void __fastcall SecondTypeComboBoxChange(TObject *Sender);

    void __fastcall GetColorFromAtomType(unsigned char AtomType, float &r, float &g, float &b);
    void __fastcall GetColorLinkFromAtomType(unsigned char BeginAtomType, char EndAtomType, float &r, float &g, float &b);
    void __fastcall DelInvisibleSpeedButtonClick(TObject *Sender);
        void __fastcall MillersSpeedButtonClick(TObject *Sender);
    void __fastcall SaveOrientationListSpeedButtonClick(TObject *Sender);
    void __fastcall OpenOrientationListSpeedButtonClick(TObject *Sender);
    void __fastcall SaveOrientationComboBoxCloseUp(TObject *Sender);
    void __fastcall MillersComboBoxCloseUp(TObject *Sender);
    void __fastcall AcceptScale(void);
    void __fastcall LayerSpeedButtonClick(TObject *Sender);
    void __fastcall CentrSpeedButtonClick(TObject *Sender);

private:	// User declarations
    void __fastcall DrowProgress(void);
	void __fastcall Display(void);
	void __fastcall AnalisateKey(void);
	float __fastcall ShiftSpeed(TShiftState Shift);
    void __fastcall SetCamera(void);
    void __fastcall RectangleToSphere(GLdouble &XR, GLdouble &YPhi,GLdouble &ZTeta);
    void __fastcall SphereToRectangle(GLdouble &RX, GLdouble &PhiY,GLdouble &TetaZ);
    void __fastcall RotationAroundX(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble A);
	void __fastcall RotationAroundY(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble Angle);
    void __fastcall DirectAlongX(GLdouble &X, GLdouble &Y,GLdouble &Z);
    void __fastcall DirectAlongY(GLdouble &X, GLdouble &Y,GLdouble &Z);
    void __fastcall DirectAlongZ(GLdouble &X, GLdouble &Y,GLdouble &Z);
    void __fastcall MoveDirection(GLdouble &X, GLdouble &Y,GLdouble &Z, GLdouble DirectionValue);
    bool __fastcall Visibled(int Nx, int Nz);
    void __fastcall DisplayAxis(bool X, bool Y, bool Z);
    void __fastcall RotateAroundWoldAxises(GLdouble Alpha, GLdouble Beta, GLdouble Gamma);
    void __fastcall DrowAtom(GLint x, GLint y, GLint z);
	void __fastcall DrowColorAtom(GLint x, GLint y, GLint z,GLfloat R, GLfloat G, GLfloat B, bool bUseDep = true);
    void __fastcall DrowLink(GLint x1, GLint y1, GLint z1,GLint x2, GLint y2, GLint z2);
    void __fastcall DrowColorLink(GLint x1, GLint y1, GLint z1,GLint x2, GLint y2, GLint z2, GLfloat R, GLfloat G, GLfloat B, GLfloat rb, GLfloat gb, GLfloat bb, GLfloat re, GLfloat ge, GLfloat be);
	void __fastcall SetZinZmax(void);
    void __fastcall DrowAtomicResh(void);
	void __fastcall SetViewParams(void);
    double inline __fastcall AtomFromScale(GLdouble Scl);
    int __fastcall GetCubeAtoms(TAtom3d** A3d);
    int __fastcall GetLinksFromCubeAtoms(TAtom3d** A3dBegin, TAtom3d** A3dEnd);
    //void __fastcall Orientation1n11(void);
    void __fastcall SetScaleLable(void);
    void __fastcall InitScshtData(void);

    void __fastcall SaveOrn(TOrientation &Orn);//сохранить оринтацию
    void __fastcall RestoreOrn(TOrientation &Orn, bool bClip = true);//восстановить оринтацию
    AnsiString __fastcall ReplaceOrnString(AnsiString strOrn);//


    TRect StatusRect;
    int Position,Min,Max;
    bool fTimerEvent;

    double Alpha,Beta;
    double SpeedAlpha, SpeedBeta;
    int PaintCnt;
    TKeysState *Keys;
    Classes::TShiftState ShiftState;

    unsigned int ListNum,ListLinksNum;
    bool IsListGen,IsSurfaceGen;
    float ScaleStep;
    GLdouble EyeX;
	GLdouble EyeY;
	GLdouble EyeZ;
	GLdouble CenterX;
	GLdouble CenterY;
	GLdouble CenterZ;
	GLdouble UpX;
	GLdouble UpY;
	GLdouble UpZ;
    GLdouble StepDem;
    GLdouble Roll;
    GLdouble RollPhi,RollTeta;
    GLdouble RollX,RollY,RollZ,dRoll;
    GLdouble dDirection;

	GLdouble AlphaT, BetaT, GammaT;
	GLdouble AlphaG, BetaG, GammaG;
	GLdouble AlphaW, BetaW, GammaW;
    GLdouble MultiAngle;
	GLdouble SpeedXT, SpeedYT, SpeedZT;
	GLdouble CenterXT, CenterYT, CenterZT;
	GLdouble SpeedXW, SpeedYW, SpeedZW;
    GLdouble MultiSpeed;

    GLdouble XPort,YPort,Near,Far;
    GLdouble Scale;

    bool AxisX,AxisY,AxisZ;
    bool EnabledPaint;
    TDateTime LstTm;

    GLfloat ModelViewMatrix[4][4], *pMVM;
    GLfloat Zmax,Zmin;
    GLfloat ColorAtom[4];
    //TAtom3d *KindAtoms[4],*LinksFromKindAtoms[3][2];
    //TAtom3d *NoDeleteAtoms,*LinksFromNoDeleteAtoms[2];
    TAtom3d *Atoms;
    TAtom3d *LinksFromAtoms[2];
    bool IsLinksVisibled;
    //int NumberKindAtoms[4],NumberLinksFromKindAtoms[3];
    //int NumberNoDeleteAtoms,NumberLinksFromNoDeleteAtoms;
    int NumberAtoms;
    int NumberLinksFromAtoms;


    TAtom3d MinTopLeftUP,MaxTopLeftUP;
    GLdouble TmpMax,TmpMin;
    TExperimentProperty *ExperimentProperty;
    TExperimentProperty *DsslExpPrprt;
    bool ExternExpProp;

    bool DissolutionParamsSet;
    double AtomSize;
    //bool ApplyOrientaton;
    //bool ClearVisibledBit;
    //20.06.03
    TPoint ScreenPanelMousePoint;
    TAtom3d SelAtom;
    void __fastcall DelHoldSufAtomPriview(void);
    //void __fastcall MarkSufAtomPriview(void);
    void __fastcall DelSufAtom(void);
    void __fastcall HoldSufAtom(void);
    void __fastcall AtomMouseClick(void);
    void __fastcall RecordDelAtomXYZ(TAtom3d* A3d);
    bool __fastcall SetStateCoord(void);
    bool __fastcall CheckCoord(bool Msg);
    int __fastcall CheckCoordAtom(int x,int y,int z);
    AnsiString __fastcall A3dToStr(TAtom3d *A3d);

    AnsiString AbaFileIdString;
    void __fastcall CopyDisplayAxis(bool X,bool Y,bool Z);
    void __fastcall CopyDisplay(void);

    bool Points;
    GLUquadricObj *quadObj;
    GLint Qality;
    TMillersIndexes MI;//индексы миилера для формы индексов миллера
    bool PrintIndex;//флаг отображения индексов миллера на 3d-изображении

    TScreenShootData SSD;

    bool SelectAtomType;
    void SetAdjType(int ProbIndex);

    TDissolutionParametries m_DssParams;//параметры расстворения



    bool SurfaceMode;//режим отображения поверхности
    TSurface Surf;//поверхность для этого режима
    void __fastcall DisplaySurface(void);// функция рисования этой поверхности
    TPoint3d MinColor;
    TPoint3d MaxColor;
    void __fastcall CalcColor(float x, float max, float min, TPoint3d &RetColor);
    void __fastcall CalcIntensiv(const TPoint3d &PntG, TPoint3d &RetColor);

    void __fastcall SetCenter(void);


    TOrientation m_CurrOrn;//текущая ориентация (ради массива обрезки)

    void __fastcall AppClipPlane(const TClipPlane &cp);//примененеие плоскости обрезания (обрезки)
    void __fastcall ClearClip(void);//очистка обрезки

    void __fastcall InitSecondTypeComboBox();//инициализация комбика типов атомов
public:		// User declarations
    float AtomsClipPlaneBrigthness;
    float OneLinksAtomColorR;
    float OneLinksAtomColorG;
    float OneLinksAtomColorB;
    float TwoLinksAtomColorR;
    float TwoLinksAtomColorG;
    float TwoLinksAtomColorB;
    float ThreeLinksAtomColorR;
    float ThreeLinksAtomColorG;
    float ThreeLinksAtomColorB;
    float FourLinksAtomColorR;
    float FourLinksAtomColorG;
    float FourLinksAtomColorB;
    float NoDeleteAtomColorR;
    float NoDeleteAtomColorG;
    float NoDeleteAtomColorB;
    float LinkNoAtomColorR;//1
    float LinkNoAtomColorG;//1
    float LinkNoAtomColorB;//1
    float LinkOneTwoLinksAtomColorR;
    float LinkOneTwoLinksAtomColorG;
    float LinkOneTwoLinksAtomColorB;
    float LinkThreeLinksAtomColorR;
    float LinkThreeLinksAtomColorG;
    float LinkThreeLinksAtomColorB;
    float LinkFourLinksAtomColorR;
    float LinkFourLinksAtomColorG;
    float LinkFourLinksAtomColorB;
    float LinkNoDeleteAtomColorR;
    float LinkNoDeleteAtomColorG;
    float LinkNoDeleteAtomColorB;

    float SelectTypeColorR;
    float SelectTypeColorG;
    float SelectTypeColorB;

    bool Depth;
	TDateTime LastPauseTime,PauseTime;
	TDateTime DissolutionTime;

	__fastcall TMainForm(TComponent* Owner);
    void __fastcall CopySreenShot(TMessage& Msg);
    void __fastcall CaptureVideo(TMessage& Msg);


    TQuantityByGroupeForm* pQuantityByGroupeForm;

    BEGIN_MESSAGE_MAP;
     MESSAGE_HANDLER(WM_COPYSCREENSHOT, TMessage, CopySreenShot);
     MESSAGE_HANDLER(WM_CAPTUREVIDEO, TMessage, CaptureVideo);
    END_MESSAGE_MAP(TForm);

};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
extern TDissolutionThread *DissolutionThread;

//---------------------------------------------------------------------------
#endif
