//---------------------------------------------------------------------------

#ifndef DefectUnitH
#define DefectUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "DefectEditUnit.h"
#include <Dialogs.hpp>
#include <vector>
#include "PictUnit.h"
//---------------------------------------------------------------------------
class TDefectVec: public std::vector<TDefect>
{
public:
	bool SaveToFile(HANDLE hFile, int *pSeek);
	bool LoadFromFile(HANDLE hFile, int *pSeek);
};
//---------------------------------------------------------------------------
class TDefectForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *ButtonsPanel;
	TSpeedButton *LoadSpeedButton;
	TSpeedButton *SaveSpeedButton;
	TPanel *OkPanel;
	TButton *OkButton;
	TPanel *CancelPanel;
	TButton *CancelButton;
	TListBox *DefectListBox;
	TOpenDialog *DefectOpenDialog;
	TSaveDialog *DefectSaveDialog;
	TPanel *TopPanel;
	TLabel *HelpLabel;
	TPanel *RightPanel;
	TSpeedButton *MoveUpSpeedButton;
	TSpeedButton *MoveDownSpeedButton;
	TBitBtn *DelDefectBitBtn;
	TBitBtn *AddDefectBitBtn;
	TBitBtn *EditDefectBitBtn;
	TPanel *ClientPanel;
	TSpeedButton *PictSpeedButton;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LoadSpeedButtonClick(TObject *Sender);
	void __fastcall SaveSpeedButtonClick(TObject *Sender);
	void __fastcall MoveUpSpeedButtonClick(TObject *Sender);
	void __fastcall MoveDownSpeedButtonClick(TObject *Sender);
	void __fastcall AddDefectBitBtnClick(TObject *Sender);
	void __fastcall EditDefectBitBtnClick(TObject *Sender);
	void __fastcall DelDefectBitBtnClick(TObject *Sender);
	void __fastcall PictSpeedButtonClick(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall DefectListBoxClick(TObject *Sender);
private:	// User declarations
	TDefectVec m_EditRec;
	int m_nWidth;
	int m_nHeight;
	void __fastcall SetControlButton();
	bool __fastcall Swap(int nIndex1, int nIndex2);
	bool __fastcall EditRec(TDefect &rec);

	TPictuteForm *m_pPictForm;
	TDefectEditForm *m_pDefectEditForm;

public:		// User declarations
	bool EditDefect(TDefectVec &rec, int nWidth, int nHeight);//тру если изменилось
	__fastcall TDefectForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TDefectForm *DefectForm;
//---------------------------------------------------------------------------
#endif
