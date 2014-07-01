//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <math.h>
#include "Almas1ProbSetUnit.h"
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas1ProbSet"
#define INTERFACE_NAME        "Ближайшие соседи"
#define INTERFACE_DISCRIPTION "Учитываются только 4 ближних соседа"
//---------------------------------------------------------------------------
TAlmas1ProbSetGlobal g_Almas1ProbSetGlobal;
//---------------------------------------------------------------------------
TAlmas1ProbSetGlobal::TAlmas1ProbSetGlobal()
{
	m_IdString         = INTERFACE_ID;
	m_NameString       = INTERFACE_NAME;
	m_DiscrptionString = INTERFACE_DISCRIPTION;

	m_nNumLayerAtomShema = 1;
}
//---------------------------------------------------------------------------
TAlmas1ProbSetGlobal::~TAlmas1ProbSetGlobal()
{
	if(m_bInit == true)
	{
	 if(m_pstrProbName != NULL)
	  delete [] m_pstrProbName;
	 if(m_pdDefaultProbArr != NULL)
	  delete [] m_pdDefaultProbArr;
	}
}
//---------------------------------------------------------------------------
void TAlmas1ProbSetGlobal::Init(void)
{//инициализация набора вероятностей
	EnterCriticalSection(&m_InitCS);
	if(m_bInit == false)
	{
	 m_nAllNumProbality = 3;
	 m_pstrProbName = new AnsiString[m_nAllNumProbality];
	 m_pdDefaultProbArr = new double[m_nAllNumProbality];
	 for(int i=0; i<m_nAllNumProbality; i++)
	 {
	  m_pstrProbName[i] = IntToStr(i+1);//имя вероятности
	  m_pdDefaultProbArr[i] = pow(10, -i*3);//значение вероятности по умолчанию
	 }
	 m_bInit = true;
	}
	LeaveCriticalSection(&m_InitCS);
}
//---------------------------------------------------------------------------
TAlmas1ProbSetGlobal& TAlmas1ProbSetGlobal::Get(void)
{//получение ссылки на глобальный класс
	return g_Almas1ProbSetGlobal;
}
//---------------------------------------------------------------------------
TProbIndex TAlmas1ProbSetGlobal::GetProbIndexFromAtomShema(TAtomShema &as)
{//получение индекса из набора для данного расположения атомов
	TProbIndex nPI = PI_ERROR;

	if(as.GetBit(GetIndex0LevAdj()) == 1)
	{
		int i;
		nPI = -1;
		for(i=0; i< 4; i ++)
		{
		 if(as.GetBit(GetIndex1LevAdj(i)) == 1)
		  nPI++;
		}
		if(nPI == -1 || nPI >= GetAllNumProbality())
		{
		 nPI = PI_ERROR;
		}
	}

	return nPI;
}
//---------------------------------------------------------------------------
int TAlmas1ProbSetGlobal::GetMainAtomTypeForProb(int Index)
{//получение типа главного атома для данной вероятности
	int nType = -1;

	if (Index >=0 && Index<m_nAllNumProbality && m_bInit)
	{
		nType = Index+1;
	}

	return nType;
}
//---------------------------------------------------------------------------
TAlmas1ProbSetCreator::TAlmas1ProbSetCreator()
:IBaseProbSetCreator(TAlmas1ProbSetGlobal::Get())
{
}
//---------------------------------------------------------------------------
IBaseProbSet* TAlmas1ProbSetCreator::Create()
{//создание набора вероятностей
	TAlmas1ProbSet *pNewProbSet = new TAlmas1ProbSet(*this);
	return pNewProbSet;
}
//---------------------------------------------------------------------------
TAlmas1ProbSet::TAlmas1ProbSet(IBaseProbSetCreator& Creator)
: IBaseProbSet(Creator)
{
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
