//---------------------------------------------------------------------------

#ifndef MaskEditUnitH
#define MaskEditUnitH
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
//---------------------------------------------------------------------------
class TMaskEditForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *TopPanel;
	TLabel *HelpLabel;
	TPanel *RightPanel;
	TSpeedButton *MoveUpSpeedButton;
	TSpeedButton *MoveDownSpeedButton;
	TSpeedButton *PictSpeedButton;
	TPanel *ButtonsPanel;
	TSpeedButton *LoadSpeedButton;
	TSpeedButton *SaveSpeedButton;
	TPanel *OkPanel;
	TButton *OkButton;
	TPanel *CancelPanel;
	TButton *CancelButton;
	TPanel *ClientPanel;
	TListBox *MaskListBox;
	TBitBtn *DelMaskBitBtn;
	TBitBtn *AddMaskBitBtn;
	TBitBtn *EditMaskBitBtn;
	TOpenDialog *MaskOpenDialog;
	TSaveDialog *MaskSaveDialog;
	TSpeedButton *AddMaskFromFileSpeedButton;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MoveUpSpeedButtonClick(TObject *Sender);
	void __fastcall MoveDownSpeedButtonClick(TObject *Sender);
	void __fastcall MaskListBoxClick(TObject *Sender);
	void __fastcall AddMaskBitBtnClick(TObject *Sender);
	void __fastcall EditMaskBitBtnClick(TObject *Sender);
	void __fastcall DelMaskBitBtnClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PictSpeedButtonClick(TObject *Sender);
	void __fastcall LoadSpeedButtonClick(TObject *Sender);
	void __fastcall SaveSpeedButtonClick(TObject *Sender);
	void __fastcall AddMaskFromFileSpeedButtonClick(TObject *Sender);
private:	// User declarations
	TMaskVec m_EditRec;
	int m_nWidth;
	int m_nHeight;
	bool __fastcall Swap(int nIndex1, int nIndex2);
	void __fastcall SetControlButton();
	bool __fastcall EditRec(TMask &rec);

	TMaskForm *m_pMaskForm;
	TPictuteForm *m_pPictForm;
public:		// User declarations
	bool EditMask(TMaskVec &rec, int nWidth, int nHeight);//тру если изменилось

 	__fastcall TMaskEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMaskEditForm *MaskEditForm;
//---------------------------------------------------------------------------
#endif
