//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "SurfaceUnit.h"
#include <stdlib.h>
#include "MaskUnit.h"
//#include "ProbalityUnit.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TSurfaceForm *SurfaceForm;
//---------------------------------------------------------------------------
__fastcall TSurfaceForm::TSurfaceForm(TComponent* Owner)
	: TForm(Owner)
{
	m_pPictForm = NULL;
	m_pMaskEditForm = NULL;
	MaskChanged = false;
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::OkButtonClick(TObject *Sender)
{
	int i;
	EditParams.X = StrToInt(XEdit->Text);
	EditParams.Y = StrToInt(YEdit->Text);
	EditParams.Z = StrToInt(ZEdit->Text);

    //EditParams.SP = SP;

	EditParams.m_Algoritm.m_nAlgoritmKind = GetAlgDiss();
	EditParams.m_Algoritm.m_nNoDelAtomsBehaviour = GetNoDelAtomsBehaviour();
	EditParams.m_Algoritm.m_bInitRNG = InitRNGCheckBox->Checked;

	bool SetFocusOnError = true;

	if(ReadEditDouble(PorogEdit,SetFocusOnError, EditParams.m_Algoritm.m_dPorog) == false)
	{
	 ModalResult = mrNone;
	 return;
	}

	if(ReadEditDouble(DolaEdit,SetFocusOnError, EditParams.m_Algoritm.m_dDola) == false)
	{
	 ModalResult = mrNone;
	 return;
	}
	//автовыбор самого крутого набора вероятностей
	if(EditParams.SP.GetInterface() == NULL && ProbalityBitBtn->Enabled)
	{
		if(EditParams.SP.EnumirateGetCount()> 0)
		{
		 EditParams.SP.CreateInterfaceByIdString(EditParams.SP.EnumirateGetIdString(EditParams.SP.EnumirateGetCount()-1));
		}
	}

	//проверка набора вероятностей
	if(EditParams.SP.GetInterface() == NULL && ProbalityBitBtn->Enabled)
	{
	 MessageBox(NULL, "Не выбран набор вероятностей.", "Ошибка", MB_ICONERROR);
	 ModalResult = mrNone;
	 ProbalityBitBtnClick(Sender);
	 return;
	}


    EditParams.Plane = (unsigned int)StrToInt(PlanEdit->Text);
	/*
	EditParams.m_vMask.clear();
	for(i=0; i < MaskListBox->Items->Count; i++)
	{
	 TMask *pMask = (TMask*)MaskListBox->Items->Objects[i];
	 EditParams.m_vMask.push_back(TMask(*pMask));
	}
	*/

	//if(MaskedRadioButton->Checked == true)
	//{
	// EditParams.Masked = true;
	//}
	//else
	//{
	// EditParams.Masked = false;
	//}

	MaskChanged = (EditParams.m_vMask != RetParams->m_vMask);

	EditParams.Masked = MaskedRadioButton->Checked;

	*RetParams = EditParams;
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::MaskedRadioButtonClick(TObject *Sender)
{
	MaskEditBitBtn->Enabled = true;
	LoadSpeedButton->Enabled = true;
	SaveSpeedButton->Enabled = true;
	SetControlButton();
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::NoMaskRadioButtonClick(TObject *Sender)
{
	MaskEditBitBtn->Enabled = false;
	LoadSpeedButton->Enabled = false;
	SaveSpeedButton->Enabled = false;
	SetControlButton();
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::FormShow(TObject *Sender)
{
	;;;
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::FormHide(TObject *Sender)
{
	if (m_pPictForm != NULL)
	{
		m_pPictForm->Close();
		delete m_pPictForm;
		m_pPictForm = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::SetControlButton(void)
{
	int nCount;

	nCount = EditParams.m_vMask.size();

	bool bCountGrZero = (nCount > 0);

	PictSpeedButton->Enabled = bCountGrZero && MaskedRadioButton->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::PictSpeedButtonClick(TObject *Sender)
{
	int nSizeX = StrToInt(XEdit->Text);
	int nSizeY = StrToInt(YEdit->Text);

	if(m_pPictForm == NULL)
	{
	 m_pPictForm = new TPictuteForm(this);
	}

	m_pPictForm->PaintMask(EditParams.m_vMask, nSizeX, nSizeY);
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::InitForm(TInitForm InitForm, TDissolutionParametries &DP)
{
	RetParams = &DP;
	EditParams = *RetParams;

	bool bNew = (InitForm == ifNew);
	bool bContinue = (InitForm == ifContinue);
	bool bCube = (InitForm == ifCube);
	bool bNewOrContinue = bNew || bContinue;
	bool bNewOrCube = bNew || bCube;


	TDissolutionParametries *tmpDP;
	if(bNew)
	{
	 EditParams.Init();
	}

	XEdit->Text = IntToStr((int)EditParams.X);
	YEdit->Text = IntToStr((int)EditParams.Y);
	ZEdit->Text = IntToStr((int)EditParams.Z);
	XEdit->Enabled = bNewOrCube;
	XLabel->Enabled = XEdit->Enabled;
	YEdit->Enabled = bNewOrCube;
	YLabel->Enabled = YEdit->Enabled;
	ZEdit->Enabled = bCube;
	ZLabel->Enabled = ZEdit->Enabled;

	SetAlgDiss(EditParams.m_Algoritm.m_nAlgoritmKind);
	PorogEdit->Text = AnsiString(EditParams.m_Algoritm.m_dPorog);
	DolaEdit->Text = AnsiString(EditParams.m_Algoritm.m_dDola);
	SetNoDelAtomsBehaviour(EditParams.m_Algoritm.m_nNoDelAtomsBehaviour);
	InitRNGCheckBox->Checked = EditParams.m_Algoritm.m_bInitRNG;

	//SP = EditParams.SP;

	ProbalityBitBtn->Enabled = bNewOrContinue;

	PlanEdit->Text = IntToStr((int)EditParams.Plane);

	PlanEdit->Enabled = bNewOrContinue;
	PlanLabel->Enabled = PlanEdit->Enabled;

	//UINT i;

	if(EditParams.Masked == true)
	{
	 MaskedRadioButton->Checked = true;
	 MaskedRadioButtonClick(NULL);
	}
	else
	{
	 NoMaskRadioButton->Checked = true;
	 NoMaskRadioButtonClick(NULL);
	}

	MaskGroupBox->Enabled      = bNewOrContinue;
	NoMaskRadioButton->Enabled = bNewOrContinue;
	MaskedRadioButton->Enabled = bNewOrContinue;
	MaskEditBitBtn->Enabled   &= bNewOrContinue;
	DefectLabel->Enabled       = bNewOrContinue;
	DefectEditBitBtn->Enabled  = bNewOrContinue;
	PictSpeedButton->Enabled  &= bNewOrContinue;
	StartButton->Enabled       = bNewOrContinue;

	ProbabilityGroupBox->Enabled             = bNewOrContinue;
	AlgMontecarloRadioButton->Enabled        = bNewOrContinue;
	InitRNGCheckBox->Enabled                 = bNewOrContinue;
	AlgPorogRadioButton->Enabled             = bNewOrContinue;
	PorogDolaRadioButton->Enabled            = bNewOrContinue;
	DolaProbRadioButton->Enabled             = bNewOrContinue;
	AlgParamGroupBox->Enabled                = bNewOrContinue;
	//PorogLabel->Enabled                      = bNewOrContinue;
	PorogEdit->Enabled                       = bNewOrContinue;
	PorogNeedLabel->Enabled                  = bNewOrContinue;
	//DolaLabel->Enabled                       = bNewOrContinue;
	DolaEdit->Enabled                        = bNewOrContinue;
	DolaNeedLabel->Enabled                   = bNewOrContinue;
	NoDelAtomsBehaviourGroupBox->Enabled     = bNewOrContinue;
	BehaviourUsuallyRadioButton->Enabled     = bNewOrContinue;
	BehaviourAsFourLinksRadioButton->Enabled = bNewOrContinue;

	MaskChanged = false;
	SetControlButton();
}
//---------------------------------------------------------------------------
TDissolutionParametries::TDissolutionParametries()
{
	Init();
}
//---------------------------------------------------------------------------
void TDissolutionParametries::Init()
{
	X = 5;
	Y = 5;
	Z = 20;
	//удаляемые атомы
	Plane = 1000000;
	Masked = false;
	m_vMask.clear();

	//алгоритм расстворения
	m_Algoritm.Init();

	//дефекты поверхности
	m_vDefect.clear();//вектор дефектов

}
//---------------------------------------------------------------------------
TDissolutionParametries::TDissolutionParametries(const TDissolutionParametries &r)
{
	X = r.X;
	Y = r.Z;
	Z = r.Z;

	SP = r.SP;

	m_Algoritm = r.m_Algoritm;

	//удаляемые атомы
	Plane = r.Plane;
	Masked = r.Masked;
	m_vMask = r.m_vMask;

	//дефекты поверхности
	m_vDefect = r.m_vDefect;
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::PlanEditKeyPress(TObject *Sender, char &Key)
{
	if(Key == 's')
	{
	 StartButton->Click();
	 //OkButtonClick(Sender);
	 Key = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::ProbalityBitBtnClick(TObject *Sender)
{
	ProbalityForm->EditProb(EditParams.SP);
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::SaveSpeedButtonClick(TObject *Sender)
{
	int nMaskCount = EditParams.m_vMask.size();
	if( nMaskCount == 0)
	{
		 AnsiString strErr = "Нельзя сохранить файл не содержащий ниодной маски.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		 return;
	}

	if(MaskSaveDialog->Execute() == true)
	{
		AnsiString strFileName = MaskSaveDialog->FileName;
		HANDLE hFile = CreateFile(
			_c_str(strFileName),	// pointer to name of the file
			GENERIC_WRITE,	// access (read-write) mode
			0,	// share mode
			NULL,	// pointer to security attributes
			CREATE_ALWAYS,	// how to create
			FILE_ATTRIBUTE_NORMAL,	// file attributes
			NULL 	// handle to file with attributes to copy
		   );
		if(hFile != INVALID_HANDLE_VALUE)
		{
			int nSeek = 0;
			if(EditParams.m_vMask.SaveToFile(hFile, &nSeek) == true)
			{
			 //всё хорошо
			}
			else
			{
			 AnsiString strErr = "Не удалось записать в файл \"" + strFileName + "\". Ошибка в позиции " + nSeek;
			 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
			}
			CloseHandle(hFile);
		}
		else
		{
		 AnsiString strErr = "Не удалось открыть файл \"" + strFileName + "\" для записи.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::LoadSpeedButtonClick(TObject *Sender)
{
	if(MaskOpenDialog->Execute() == true)
	{
		AnsiString strFileName = MaskOpenDialog->FileName;
		HANDLE hFile = CreateFile(
			_c_str(strFileName),	// pointer to name of the file
			GENERIC_READ,	// access (read-write) mode
			0,	// share mode
			NULL,	// pointer to security attributes
			OPEN_EXISTING,	// how to create
			FILE_ATTRIBUTE_NORMAL,	// file attributes
			NULL 	// handle to file with attributes to copy
		   );
		if(hFile != INVALID_HANDLE_VALUE)
		{
			TMaskVec Rec;
			int nSeek = 0;
			if(Rec.LoadFromFile(hFile, &nSeek) == true )
			{
			 EditParams.m_vMask = Rec;
			 SetControlButton();
			}
			else
			{
			 AnsiString strErr = "Не удалось прочитать из файла \"" + strFileName + "\". Ошибка в позиции " + nSeek;
			 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
			}

			CloseHandle(hFile);
		}
		else
		{
		 AnsiString strErr = "Не удалось открыть файл \"" + strFileName + "\" для чтения.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		}
	}
}
//---------------------------------------------------------------------------
void TSurfaceForm::SetAlgDiss(int nAlgoritmKind)
{
	AlgMontecarloRadioButton->Checked = (nAlgoritmKind == ALG_MONTECARLO);
	AlgPorogRadioButton->Checked = (nAlgoritmKind == ALG_POROGOVIY);
	PorogDolaRadioButton->Checked = (nAlgoritmKind == ALG_POROG_DOLA);
	DolaProbRadioButton->Checked = (nAlgoritmKind == ALG_DOLA_PROB);

	SetOptParam(nAlgoritmKind);
}
//---------------------------------------------------------------------------
void TSurfaceForm::SetOptParam(int nAlgoritmKind)
{
	PorogNeedLabel->Visible = (nAlgoritmKind == ALG_POROGOVIY)
							||(nAlgoritmKind == ALG_POROG_DOLA);
    DolaNeedLabel->Visible = (nAlgoritmKind == ALG_POROG_DOLA)
                           ||(nAlgoritmKind == ALG_DOLA_PROB);
}
//---------------------------------------------------------------------------
int TSurfaceForm::GetAlgDiss(void)
{
    int nAlgoritmKind = CB_ERR;
    if(AlgMontecarloRadioButton->Checked == true)
    {
        nAlgoritmKind = ALG_MONTECARLO;
    }
    if(AlgPorogRadioButton->Checked == true)
    {
        nAlgoritmKind = ALG_POROGOVIY;
    }
    if(PorogDolaRadioButton->Checked == true)
    {
        nAlgoritmKind = ALG_POROG_DOLA;
    }
    if(DolaProbRadioButton->Checked == true)
    {
        nAlgoritmKind = ALG_DOLA_PROB;
    }
    return nAlgoritmKind;
}
//---------------------------------------------------------------------------

void __fastcall TSurfaceForm::AlgMontecarloRadioButtonClick(
      TObject *Sender)
{
	int nAlgoritmKind = GetAlgDiss();
	SetOptParam(nAlgoritmKind);
}
//---------------------------------------------------------------------------
TAlgoritm::TAlgoritm()
{
	Init();
}
//---------------------------------------------------------------------------
void TAlgoritm::Init()
{
	m_nAlgoritmKind = ALG_MONTECARLO;
	m_dPorog        = 1.0;//порог вероятности
	m_dDola         = 0.5;//доля количества
	m_nNoDelAtomsBehaviour = 2;
	m_bInitRNG = false;
}
//---------------------------------------------------------------------------
TAlgoritm::TAlgoritm(const TAlgoritm &r)
{
	*this = r;
}
//---------------------------------------------------------------------------
TAlgoritm& TAlgoritm::operator = (const TAlgoritm &r)
{
	m_nAlgoritmKind = r.m_nAlgoritmKind;
	m_dPorog        = r.m_dPorog;
	m_dDola         = r.m_dDola;
	m_nNoDelAtomsBehaviour = r.m_nNoDelAtomsBehaviour;
	m_bInitRNG    	= r.m_bInitRNG;
	return *this;
}
//---------------------------------------------------------------------------
void TSurfaceForm::SetNoDelAtomsBehaviour(int nKind)
{
	BehaviourUsuallyRadioButton->Checked     = (nKind == BHV_USUALLY);
	BehaviourAsFourLinksRadioButton->Checked = (nKind == BHV_AS_FOUR_LINKS);
}
//---------------------------------------------------------------------------
int  TSurfaceForm::GetNoDelAtomsBehaviour(void)
{
	int nKind = CB_ERR;
	if(BehaviourUsuallyRadioButton->Checked == true)
	{
		nKind = BHV_USUALLY;
	}
	if(BehaviourAsFourLinksRadioButton->Checked == true)
	{
		nKind = BHV_AS_FOUR_LINKS;
	}
	return nKind;
}
//---------------------------------------------------------------------------
bool TAlgoritm::SaveToFile(HANDLE hFile, int *pSeek/* = NULL*/)
{//сохранить структуру в поток
	bool bRet = false;
	int nSeek = 0;
	DWORD NumberOfBytesToWrite, NumberOfBytesWritten;
	bool bwf = true;
	//int i;

	   NumberOfBytesToWrite = sizeof(m_nAlgoritmKind);
	   bwf &= WriteFile(hFile,&(m_nAlgoritmKind),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(m_dPorog);
	   bwf &= WriteFile(hFile,&(m_dPorog),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(m_dDola);
	   bwf &= WriteFile(hFile,&(m_dDola),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(m_nNoDelAtomsBehaviour);
	   bwf &= WriteFile(hFile,&(m_nNoDelAtomsBehaviour),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(m_bInitRNG);
	   bwf &= WriteFile(hFile,&(m_bInitRNG),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	if(pSeek != NULL)
	{
	 *pSeek += nSeek;
	}
	bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
bool TAlgoritm::LoadFromFile(HANDLE hFile, int *pSeek/* = NULL*/)
{//загрузить структуру из потока
	bool bRet = false;
	int nSeek = 0;
	DWORD NumberOfBytesRead,NumberOfBytesReaded;
	//int i;
	bool bwf = true;


		NumberOfBytesRead = sizeof(m_nAlgoritmKind);
		bwf &= ReadFile(hFile,&m_nAlgoritmKind,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(m_dPorog);
		bwf &= ReadFile(hFile,&m_dPorog,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(m_dDola);
		bwf &= ReadFile(hFile,&m_dDola,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(m_nNoDelAtomsBehaviour);
		bwf &= ReadFile(hFile,&m_nNoDelAtomsBehaviour,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(m_bInitRNG);
		bwf &= ReadFile(hFile,&m_bInitRNG,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;



	if(pSeek != NULL)
	{
	 *pSeek += nSeek;
	}
	bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::DefectEditBitBtnClick(TObject *Sender)
{
	TDefectForm *DefectForm;
	DefectForm = new TDefectForm(this);

	int nSizeX = StrToInt(XEdit->Text);
	int nSizeY = StrToInt(YEdit->Text);

	DefectForm->EditDefect(EditParams.m_vDefect, nSizeX, nSizeY);
	delete DefectForm;
}
//---------------------------------------------------------------------------
void __fastcall TSurfaceForm::MaskEditBitBtnClick(TObject *Sender)
{
	bool bRet;
	if (m_pMaskEditForm == NULL)
	{
	 m_pMaskEditForm = new TMaskEditForm(this);
	}
	int nSizeX = StrToInt(XEdit->Text);
	int nSizeY = StrToInt(YEdit->Text);

	bRet = m_pMaskEditForm->EditMask(EditParams.m_vMask, nSizeX, nSizeY);
	if(bRet == true)
	{
	 SetControlButton();
	}
}
//---------------------------------------------------------------------------

