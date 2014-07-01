//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <math.h>
#include "Almas2ProbSetUnit.h"
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas2ProbSet"
#define INTERFACE_NAME        "Вторые соседи"
#define INTERFACE_DISCRIPTION "Учитываются первые и вторые соседи"
//---------------------------------------------------------------------------
TAlmas2ProbSetGlobal g_Almas2ProbSetGlobal;
//---------------------------------------------------------------------------
TAlmas2ProbSetGlobal::TAlmas2ProbSetGlobal()
{
	m_IdString         = INTERFACE_ID;
	m_NameString       = INTERFACE_NAME;
	m_DiscrptionString = INTERFACE_DISCRIPTION;

	m_nNumLayerAtomShema = 2;
}
//---------------------------------------------------------------------------
TAlmas2ProbSetGlobal::~TAlmas2ProbSetGlobal()
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
void TAlmas2ProbSetGlobal::Init(void)
{//инициализация набора вероятностей
	if(m_bInit == false)
	{
		EnterCriticalSection(&m_InitCS);
		if(m_bInit == false)
		{
		 m_nAllNumProbality = 31;
		 m_pstrProbName = new AnsiString[m_nAllNumProbality];
		 m_pdDefaultProbArr = new double[m_nAllNumProbality];
		 //for(int i=0; i<m_nAllNumProbality; i++)
		 //{
		 // m_pstrProbName[i] = IntToStr(i+1);//имя вероятности
		 // m_pdDefaultProbArr[i] = pow(10, -i*3);//значение вероятности по умолчанию
		 //}
		 int i=0;
		 //имя вероятности                  значение вероятности по умолчанию
		 m_pstrProbName[i] = "1x2"; 		m_pdDefaultProbArr[i] = pow(10, -0*3); i++; // 1
		 m_pstrProbName[i] = "1x3"; 		m_pdDefaultProbArr[i] = pow(10, -0*3); i++; // 2
		 m_pstrProbName[i] = "1x4"; 		m_pdDefaultProbArr[i] = pow(10, -0*3); i++; // 3

		 m_pstrProbName[i] = "2x12"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 4
		 m_pstrProbName[i] = "2x13"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 5
		 m_pstrProbName[i] = "2x14"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 6
		 m_pstrProbName[i] = "2x22"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 7
		 m_pstrProbName[i] = "2x23"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 8
		 m_pstrProbName[i] = "2x24"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 9
		 m_pstrProbName[i] = "2x33"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 10
		 m_pstrProbName[i] = "2x34"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 11
		 m_pstrProbName[i] = "2x44"; 		m_pdDefaultProbArr[i] = pow(10, -1*3); i++; // 12

		 m_pstrProbName[i] = "3x112"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 13
		 m_pstrProbName[i] = "3x113"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 14
		 m_pstrProbName[i] = "3x114"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 15
		 m_pstrProbName[i] = "3x122"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 16
		 m_pstrProbName[i] = "3x123"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 17
		 m_pstrProbName[i] = "3x124"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 18
		 m_pstrProbName[i] = "3x133"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 19
		 m_pstrProbName[i] = "3x134"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 20
		 m_pstrProbName[i] = "3x144"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 21
		 m_pstrProbName[i] = "3x222"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 22
		 m_pstrProbName[i] = "3x223"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 23
		 m_pstrProbName[i] = "3x224"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 24
		 m_pstrProbName[i] = "3x233"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 25
		 m_pstrProbName[i] = "3x234"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 26
		 m_pstrProbName[i] = "3x244"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 27
		 m_pstrProbName[i] = "3x333"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 28
		 m_pstrProbName[i] = "3x334"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 29
		 m_pstrProbName[i] = "3x344"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 30
		 m_pstrProbName[i] = "3x444"; 		m_pdDefaultProbArr[i] = pow(10, -2*3); i++; // 31

		 m_bInit = true;
		}
		LeaveCriticalSection(&m_InitCS);
	}
}
//---------------------------------------------------------------------------
TAlmas2ProbSetGlobal& TAlmas2ProbSetGlobal::Get(void)
{//получение ссылки на глобальный класс
	return g_Almas2ProbSetGlobal;
}
//---------------------------------------------------------------------------
TProbIndex TAlmas2ProbSetGlobal::GetProbIndexFromAtomShema(TAtomShema &as)
{//получение индекса из набора для данного расположения атомов
	TProbIndex nPI = PI_ERROR;
	if(as.m_nMaxLayer < m_nNumLayerAtomShema)
	{
		throw Exception("TAlmas2ProbSetGlobal::GetProbIndexFromAtomShema - атомсхема описана недостаточно полно.");
	}
	if(as.GetBit(GetIndex0LevAdj()) == 1)
	{
		int i, j;
		int vnSecType[4];
		nPI = 0;
		for(i = 0; i < 4; i++)
		{
		 vnSecType[i] = 0;
		 if(as.GetBit(GetIndex1LevAdj(i)) == 1)
		 {
		  vnSecType[i] = 1;
		  nPI++;
		  for(j = 0; j < 3; j++)
		  {
		   if(as.GetBit(GetIndex2LevAdj(i,j)) == 1)
		   {
			vnSecType[i]++;
		   }
		  }
		 }
		}
		if(nPI == 0 || nPI >= 4)
		{
		 nPI = PI_ERROR;
		}
		else
		{
		 //сортировка по возрастанию
		 int nTmp;
		 int nSecondType=0;
		 for(i = 0; i < 4; i++)
		 {
		  for(j = i; j < 4; j++)
		  {
		   if(vnSecType[i] < vnSecType[j])
		   {
			nTmp = vnSecType[i];
			vnSecType[i] = vnSecType[j];
			vnSecType[j] = nTmp;
		   }
		  }
		  nSecondType |= (vnSecType[i]&0xFF) << (i*8);
		 }
		 switch(nSecondType)
		 {
		 case 0x00000002:  nPI = 0;	 break;
		 case 0x00000003:  nPI = 1;	 break;
		 case 0x00000004:  nPI = 2;	 break;

		 case 0x00000102:  nPI = 3;	 break;
		 case 0x00000103:  nPI = 4;	 break;
		 case 0x00000104:  nPI = 5;	 break;
		 case 0x00000202:  nPI = 6;	 break;
		 case 0x00000203:  nPI = 7;	 break;
		 case 0x00000204:  nPI = 8;	 break;
		 case 0x00000303:  nPI = 9;	 break;
		 case 0x00000304:  nPI = 10; break;
		 case 0x00000404:  nPI = 11; break;

		 case 0x00010102:  nPI = 12; break;
		 case 0x00010103:  nPI = 13; break;
		 case 0x00010104:  nPI = 14; break;
		 case 0x00010202:  nPI = 15; break;
		 case 0x00010203:  nPI = 16; break;
		 case 0x00010204:  nPI = 17; break;
		 case 0x00010303:  nPI = 18; break;
		 case 0x00010304:  nPI = 19; break;
		 case 0x00010404:  nPI = 20; break;
		 case 0x00020202:  nPI = 21; break;
		 case 0x00020203:  nPI = 22; break;
		 case 0x00020204:  nPI = 23; break;
		 case 0x00020303:  nPI = 24; break;
		 case 0x00020304:  nPI = 25; break;
		 case 0x00020404:  nPI = 26; break;
		 case 0x00030303:  nPI = 27; break;
		 case 0x00030304:  nPI = 28; break;
		 case 0x00030404:  nPI = 29; break;
		 case 0x00040404:  nPI = 30; break;
		 default: 		   nPI = PI_ERROR;
		 }
		}
	}

	return nPI;
}
//---------------------------------------------------------------------------
int TAlmas2ProbSetGlobal::GetMainAtomTypeForProb(int Index)
{//получение типа главного атома для данной вероятности
	int nType = -1;

	if (Index >=0 && Index<m_nAllNumProbality && m_bInit)
	{
		switch(Index)
		{
			case 0:
			case 1:
			case 2:
				nType = 1;
			break;

			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
				nType = 2;
			break;

			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
				nType = 3;
			break;
		}
	}

	return nType;
}
//---------------------------------------------------------------------------
TAlmas2ProbSetCreator::TAlmas2ProbSetCreator()
:IBaseProbSetCreator(TAlmas2ProbSetGlobal::Get())
{
}
//---------------------------------------------------------------------------
IBaseProbSet* TAlmas2ProbSetCreator::Create()
{//создание набора вероятностей
	TAlmas2ProbSet *pNewProbSet = new TAlmas2ProbSet(*this);
	return pNewProbSet;
}
//---------------------------------------------------------------------------
TAlmas2ProbSet::TAlmas2ProbSet(IBaseProbSetCreator& Creator)
: IBaseProbSet(Creator)
{
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

