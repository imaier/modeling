//---------------------------------------------------------------------------

#ifndef DefectEditUnitH
#define DefectEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "MaskUnit.h"
#include "PictUnit.h"
#include "MaskEditUnit.h"
//---------------------------------------------------------------------------
class TDefect
{
public:
	//Данные

	//Название
	AnsiString m_sName;
	//Количество циклов
	int m_nLoopCount;
	//Mаска
	TMaskVec m_vMask;//вектор масок

public:
	//методы
	void Init();//инициализировать структуру по умолчанию

	TDefect();//конструктор по умолчанию
	TDefect(const TDefect& r);//конструктор копирования

	TDefect& operator = (const TDefect &r);//оператор копирования

	bool SaveToFile(HANDLE hFile, int *pSeek = NULL);//сохранить структуру в поток
	bool LoadFromFile(HANDLE hFile, int *pSeek = NULL);//загрузить структуру из потока

	AnsiString ToStr();//описание дефекта строкой
};
//---------------------------------------------------------------------------
class TDefectEditForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *ButtonsPanel;
	TPanel *OkPanel;
	TButton *OkButton;
	TPanel *CancelPanel;
	TButton *CancelButton;
	TLabel *Label1;
	TLabel *CountLabel;
	TEdit *CountEdit;
	TLabel *NameLabel;
	TEdit *NameEdit;
	TSpeedButton *PictSpeedButton;
	TSaveDialog *MaskSaveDialog;
	TOpenDialog *MaskOpenDialog;
	TBitBtn *EditBitBtn;
	TLabel *MaskLabel;
	TLabel *HelpLabel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PictSpeedButtonClick(TObject *Sender);
	void __fastcall OkButtonClick(TObject *Sender);
	void __fastcall EditBitBtnClick(TObject *Sender);
private:	// User declarations
	TDefect m_EditRec;
	int m_nWidth;
	int m_nHeight;

	void __fastcall SetControlButton();

	TPictuteForm *m_pPictForm;
	TMaskEditForm *m_pMaskEditForm;
public:		// User declarations
	bool EditDefect(TDefect &rec, int nWidth, int nHeight);//тру если изменилось
	__fastcall TDefectEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TDefectEditForm *DefectEditForm;
//---------------------------------------------------------------------------
#endif
