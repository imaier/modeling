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
	//������

	//��������
	AnsiString m_sName;
	//���������� ������
	int m_nLoopCount;
	//M����
	TMaskVec m_vMask;//������ �����

public:
	//������
	void Init();//���������������� ��������� �� ���������

	TDefect();//����������� �� ���������
	TDefect(const TDefect& r);//����������� �����������

	TDefect& operator = (const TDefect &r);//�������� �����������

	bool SaveToFile(HANDLE hFile, int *pSeek = NULL);//��������� ��������� � �����
	bool LoadFromFile(HANDLE hFile, int *pSeek = NULL);//��������� ��������� �� ������

	AnsiString ToStr();//�������� ������� �������
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
	bool EditDefect(TDefect &rec, int nWidth, int nHeight);//��� ���� ����������
	__fastcall TDefectEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE TDefectEditForm *DefectEditForm;
//---------------------------------------------------------------------------
#endif
