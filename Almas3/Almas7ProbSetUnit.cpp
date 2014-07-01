//---------------------------------------------------------------------------


#pragma hdrstop

#include "Almas7ProbSetUnit.h"

#include <math.h>
#include <stdio.h>
#include "GlobalUnit.h"
#include "ProgressUnit.h"
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas7ProbSet"
#define INTERFACE_NAME        "Первые и вторые прямые, вторые непрямые соседи"
#define INTERFACE_DISCRIPTION "Учитывается общее число первых соседей, число вторых прямых и число вторых непрямых соседей"

//---------------------------------------------------------------------------
TAlmas7ProbSetGlobal g_Almas7ProbSetGlobal;
//---------------------------------------------------------------------------
TAlmas7ProbSetGlobal::TAlmas7ProbSetGlobal()
{
	m_IdString         = INTERFACE_ID;
	m_NameString       = INTERFACE_NAME;
	m_DiscrptionString = INTERFACE_DISCRIPTION;

	m_nNumLayerAtomShema = 3;
}
//---------------------------------------------------------------------------
TAlmas7ProbSetGlobal::~TAlmas7ProbSetGlobal()
{
	if(m_bInit == true)
	{
	 if(m_pstrProbName != NULL)
	 {
	  delete [] m_pstrProbName;
	  m_pstrProbName = NULL;
	 }
	 if(m_pdDefaultProbArr != NULL)
	 {
	  delete [] m_pdDefaultProbArr;
	  m_pdDefaultProbArr = NULL;
	 }
	}
}

//новый способ с делениями
#define Adg1Base 1
//количество первых соседей
#define Adg1State 4
//количество вторых соседей
#define Adg2Num 3
//количество состояний вторых соседей
#define Adg2State 5
//состояние вторых соседей означающее отсутсвие второго соседа
#define NoAdg2Val (Adg2State-1)
//емкость состояний для первых j соседей
#define Adg3State(i) IntPow(IntPow(Adg2State,Adg2Num), i)
//база
#define Adg2Base_(i, j) (Adg1State*Adg3State(i)*IntPow(Adg2State,j))
#define Adg2Base(i, j) Adg2Base_5(i, j)

#define divGetAdg1(Key) (Key%Adg1State)
#define divSetAdg1(Key, Data) Key = (Key + ((Data%Adg1State) - divGetAdg1(Key))*Adg1Base)
#define divGetAdg2(Key, i, j) ((Key/Adg2Base(i,j))%Adg2State)
#define divSetAdg2(Key, Data, i, j) Key = (Key + ((Data%Adg2State) - divGetAdg2(Key,i,j))*Adg2Base(i,j))
/*
 * Типы атомов в этой модели можно характеризовать тройкой знаков с числами,
 * например, (F, dS, nS) , где F – общее число первых соседей, dS – число вторых
 * прямых соседей, nS – число вторых непрямых соседей, соответственно.
 */
#define SetKey2(Key, F, dS, nS) Key = (nS%10 + 10*(dS%10) + 100*(F%10))
#define GetKey2(Key, F, dS, nS) nS = ((Key/1)%10); dS = ((Key/10)%10); F = ((Key/100)%10);
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TProbKey Adg2Base_5(int i, int j)
{
static TProbKey cvAdg2Base[4][3] = { {Adg2Base_(0,0),Adg2Base_(0,1),Adg2Base_(0,2)},
									 {Adg2Base_(1,0),Adg2Base_(1,1),Adg2Base_(1,2)},
									 {Adg2Base_(2,0),Adg2Base_(2,1),Adg2Base_(2,2)},
									 {Adg2Base_(3,0),Adg2Base_(3,1),Adg2Base_(3,2)}
								   };
	return cvAdg2Base[i][j];
}
TAlmas7ProbSetKey::TAlmas7ProbSetKey()
{
	Adg1 = 0;
	Adg2_i0_j0 = 0;
	Adg2_i1_j0 = 0;
	Adg2_i2_j0 = 0;
	Adg2_i3_j0 = 0;
	Adg2_i0_j1 = 0;
	Adg2_i1_j1 = 0;
	Adg2_i2_j1 = 0;
	Adg2_i3_j1 = 0;
	Adg2_i0_j2 = 0;
	Adg2_i1_j2 = 0;
	Adg2_i2_j2 = 0;
	Adg2_i3_j2 = 0;

	F = 0;
	dS = 0;
	nS = 0;

	Key2 = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas7ProbSetKey::fill(TProbKey nKey)
{
	Key = nKey;

	Adg1 = divGetAdg1(nKey);
	Adg2_i0_j0 = divGetAdg2(nKey, 0, 0);
	Adg2_i1_j0 = divGetAdg2(nKey, 1, 0);
	Adg2_i2_j0 = divGetAdg2(nKey, 2, 0);
	Adg2_i3_j0 = divGetAdg2(nKey, 3, 0);
	Adg2_i0_j1 = divGetAdg2(nKey, 0, 1);
	Adg2_i1_j1 = divGetAdg2(nKey, 1, 1);
	Adg2_i2_j1 = divGetAdg2(nKey, 2, 1);
	Adg2_i3_j1 = divGetAdg2(nKey, 3, 1);
	Adg2_i0_j2 = divGetAdg2(nKey, 0, 2);
	Adg2_i1_j2 = divGetAdg2(nKey, 1, 2);
	Adg2_i2_j2 = divGetAdg2(nKey, 2, 2);
	Adg2_i3_j2 = divGetAdg2(nKey, 3, 2);

	fill2(nKey);

	int nNumber=-1;
	TAlmas7ProbSetGlobal::GetProbNameFromKey(nKey, nNumber, strName);
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas7ProbSetKey::unfill()
{
	TProbKey nKey = 0;

	divSetAdg1(nKey,Adg1);
	divSetAdg2(nKey, Adg2_i0_j0, 0, 0);
	divSetAdg2(nKey, Adg2_i0_j1, 0, 1);
	divSetAdg2(nKey, Adg2_i0_j2, 0, 2);
	divSetAdg2(nKey, Adg2_i1_j0, 1, 0);
	divSetAdg2(nKey, Adg2_i1_j1, 1, 1);
	divSetAdg2(nKey, Adg2_i1_j2, 1, 2);
	divSetAdg2(nKey, Adg2_i2_j0, 2, 0);
	divSetAdg2(nKey, Adg2_i2_j1, 2, 1);
	divSetAdg2(nKey, Adg2_i2_j2, 2, 2);
	divSetAdg2(nKey, Adg2_i3_j0, 3, 0);
	divSetAdg2(nKey, Adg2_i3_j1, 3, 1);
	divSetAdg2(nKey, Adg2_i3_j2, 3, 2);

	Key = nKey;

	TAlmas7ProbSetKey k1;
	k1.fill(Key);

	return nKey;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas7ProbSetKey::fill2(TProbKey nKey)
{//разложить ключ 1 в парамтеры
/*

//новый способ с делениями
#define Adg1Base 1
//количество первых соседей
#define Adg1State 4
//количество вторых соседей
#define Adg2Num 3
//количество состояний вторых соседей
#define Adg2State 5
//состояние вторых соседей означающее отсутсвие второго соседа
#define NoAdg2Val (Adg2State-1)
//емкость состояний для первых j соседей
#define Adg3State(i) IntPow(IntPow(Adg2State,Adg2Num), i)
//база
#define Adg2Base_(i, j) (Adg1State*Adg3State(i)*IntPow(Adg2State,j))
#define Adg2Base(i, j) Adg2Base_5(i, j)

#define divGetAdg1(Key) (Key%Adg1State)
#define divSetAdg1(Key, Data) Key = (Key + ((Data%Adg1State) - divGetAdg1(Key))*Adg1Base)
#define divGetAdg2(Key, i, j) ((Key/Adg2Base(i,j))%Adg2State)
#define divSetAdg2(Key, Data, i, j) Key = (Key + ((Data%Adg2State) - divGetAdg2(Key,i,j))*Adg2Base(i,j))

#define SetKey2(Key, F, dS, nS) Key = (nS%10 + 10*(dS%10) + 100*(F%10)
#define GetKey2(Key, F, dS, nS) nS = ((Key/1)%10); dS = ((Key/10)%10); F = ((Key/100)%10);

*/

	int i,j;
	int nAdjTtpeI;
	bool bNoVol;

	F = divGetAdg1(nKey)+1; //количетво первых соседей
	dS = 0;
	nS = 0;

	for(i = 0; i < Adg1State; i++)
	{
	 for(j = 0; j < Adg2Num; j++)
	 {
	  nAdjTtpeI = divGetAdg2(nKey, i, j);
	  if(nAdjTtpeI == NoAdg2Val)
	  {//второго соседа нету
	  }
	  else
	  {//второй сосед есть
	   if(i < F)
	   {//и при этом есть первый сосед, то второй сосед является прямым
		dS++;
		/*
		if (dS > 99) {
			throw Exception(("Количество прямых вторых соседей 10 и более."));
		}
		*/
	   }
	   else
	   {//первого соседа нет значит второй сосед не прямой
		nS++;
		/*if (nS > 9) {
			throw Exception(("Количество не прямых вторых соседей 10 и более."));
		}
		*/
	   }
	  }
	 }
	}

	SetKey2(Key2, F, dS, nS);
}
//---------------------------------------------------------------------------
int __fastcall IntPow(int x, int p)
{
	int y=1;
	for(int i = 0; i < p; i++)
	{
	 y*=x;
	}
	return y;
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas7ProbSetGlobal::RemoveLeftFromKey2(TProbKey BaseKey)
{//убрать лишние биты из ключа
	TProbKey nKey = BaseKey;
	/*//нету лишних битов
	int i,j;
	for(i = divGetAdg1(nKey); i < (Adg1State-1); i++)
	{
	 for(j = 0; j < Adg2Num; j++)
	 {
	  divSetAdg2(nKey, NoAdg2Val, i,j); //поставить что атома нет
	 }
	}
	*/
	return nKey;
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas7ProbSetGlobal::CanonateKey2(TProbKey BaseKey)
{
	TProbKey nKey = BaseKey;

	int i,j,k;
	int nAdjTtpeJ;
	int nAdjTtpeK;
	//сортировка вторых соседей
	for(i = 0; i < Adg1State; i++)
	{
	 for(j = 0; j < Adg2Num-1; j++)
	 {
	  for(k = j+1; k < Adg2Num; k++)
	  {
	   nAdjTtpeJ = divGetAdg2(nKey, i, j);
	   nAdjTtpeK = divGetAdg2(nKey, i, k);
	   if(nAdjTtpeJ < nAdjTtpeK)
	   {
		divSetAdg2(nKey, nAdjTtpeK, i, j);
		divSetAdg2(nKey, nAdjTtpeJ, i, k);
	   }
	  }
	 }
	}
	if(BaseKey == nKey)
	{
	 /*
	 if(nKey == 2468447
	 || nKey == 2468495)
	 {
	  BaseKey++;
	 }
	 if(nKey == 1847186
	 || nKey == 1055546)
	 {
	  BaseKey++;
	 }
	 */

	 TProbKey2 Key2 = KeyToKey2(nKey);
	 TKey2ToKeyMap::iterator itr;
	 itr = m_Key2ToKeyMap.find(Key2);
	 if(itr!=m_Key2ToKeyMap.end())
	 {
	  nKey = itr->second;
	 }
	 else
	 {
	  m_Key2ToKeyMap[Key2] = nKey;
	 }
	}
	return nKey;
}
//---------------------------------------------------------------------------
bool __fastcall TAlmas7ProbSetGlobal::ChekKey2(TProbKey nKey)
{//проверка ключа на соответсвие канонической форме
	bool bRet = true;
	int i,j,k;
	int nAdjTtpeJ, nAdjTtpeOld;
	int nAdjTtpeK;
	//TProbKey nKey = BaseKey;

	if((divGetAdg1(nKey)+1)==4)
	{//четырехсвязных атомов быть не должно
	 bRet = false;
	 return bRet;
	}

	//проверка что вторые соседи отсортированы
	for(i = 0; i < Adg1State; i++)
	{
	 j = 0;
	 nAdjTtpeOld = divGetAdg2(nKey, i,j );
	 for(j = 1; j < Adg2Num; j++)
	 {
	  nAdjTtpeJ = divGetAdg2(nKey, i, j);
	  if(nAdjTtpeOld<nAdjTtpeJ)
	  {
	   bRet = false;
	   return bRet;
	  }
	 }
	}
	return bRet;
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas7ProbSetGlobal::KeyToKey2(TProbKey BaseKey)
{
	TAlmas7ProbSetKey psk;
	psk.fill2(BaseKey);
	return psk.Key2;
}
//---------------------------------------------------------------------------
void TAlmas7ProbSetGlobal::Init(void)
{//инициализация набора вероятностей
	if(m_bInit == false)
	{
		EnterCriticalSection(&m_InitCS);
		if(m_bInit == false)
		{
		 TProbKeyVec vPK;
		 int nType;
		 //Application->HideHint()
		 //
		 Screen->Cursor = crHourGlass;

		 AnsiString strAll, str1;
		 AnsiString szFilename;
		 szFilename = GetProgramPath()+INTERFACE_ID;
		 szFilename += ".cfg";

		 TProbKey nKey, nTmpKey;

		 int i=0;
		 if(FileExists(szFilename) == true)
		 {//если существует файл с конфигурацией то загружаемся из него
		  FILE *pFile = fopen(_c_str(szFilename),"r");
		  if(pFile != NULL)
		  {
		   char szVal[256];
		   int Key;
		   while(fgets(szVal, sizeof(szVal), pFile))
		   {
			str1 = szVal;
			str1 = str1.Trim();
			Key = StrToInt(str1);
			nKey = Key;
			vPK.push_back(nKey);
		   }
		   fclose(pFile);
		   bool bChk = true;
		   bool bChk2 = true;
		   m_Key2ToKeyMap.clear();
		   int nPkSize = vPK.size();
		   for(i = 0; (i < nPkSize) && bChk; i++)
		   {
			nKey = vPK[i];
			bChk2 = false;
			if(ChekKey2(nKey))
			{
			 nTmpKey = RemoveLeftFromKey2( nKey );
			 if(nTmpKey == nKey)
			 {//нет избыточности
			  nTmpKey = CanonateKey2(nKey);
			  if(nTmpKey == nKey)
			  {//правильно отсортирован
			   bChk2 = true;
			  }
			 }
			}
			if(bChk2 != true)
			{
			 bChk = false;
			}
		   }
		   if(bChk == false)
		   {
			vPK.clear();
		   }
		  }
		 }

		 if(vPK.size()==0)
		 {//если конфигурации нет то считаем заново
		  m_Key2ToKeyMap.clear();
		  TProbKey nMaxKey = Adg2Base(Adg1State-1,Adg2Num-1)*Adg2State;

		  TProgressRec pr;
		  pr.m_strOperation = "Генерирование набора вероятностей";
		  pr.m_strState = "Отсеивание дублирующих конфигураций";
		  pr.m_nMax = nMaxKey;
		  for(nKey = 0; nKey < nMaxKey; nKey++)
		  {
		   if(ChekKey2(nKey))
		   {
			nTmpKey = RemoveLeftFromKey2( nKey );
			if(nTmpKey == nKey)
			{//нет избыточности
			 nTmpKey = CanonateKey2(nKey);
			 if(nTmpKey == nKey)
			 {//правильно отсортирован
			  vPK.push_back(nKey);//добавляем ключ в вектор для последующего сохранения
			 }
			}
		   }
		   if((nKey % 1000) == 0)
		   {
			if(TProgressProvider::GetInstanse().IsStopped())
			{
			 TProgressProvider::GetInstanse().FinishProgress();
			 throw Exception("Процесс остановлен.");
			}
			pr.m_nCurr = nKey;
			pr.m_strState = "Отсеивание дублирующих конфигураций";
			TProgressProvider::GetInstanse().PostProgress(pr);
		   }
		  }
		  pr.m_strState = "Сохранение конфигурации";
		  pr.m_nCurr = pr.m_nMax;
		  TProgressProvider::GetInstanse().PostProgress(pr);

		  //сохранить конфигурацию в файл
		  FILE *pFile = fopen(_c_str(szFilename),"w+");
		  if(pFile != NULL)
		  {
		   for(UINT i = 0; i < vPK.size(); i++)
		   {
			str1=IntToStr((int)(vPK[i]))+"\n";
			fputs(_c_str(str1), pFile);
		   }
		   fclose(pFile);
		  }
		  TProgressProvider::GetInstanse().FinishProgress();
		 }

		 TKey2ToKeyMap::iterator itr;
		 vPK.clear();
		 bool bTest = false;
		 bTest = true;
		 i=0;
		 for(itr = m_Key2ToKeyMap.begin(); itr != m_Key2ToKeyMap.end(); itr++)
		 {
		  vPK.push_back(itr->second);
		  if(bTest)
		  {
		   nType = GetTypeFromKey(itr->second);
		   GetProbNameFromKey(itr->second, i+1, str1);//имя вероятности
		   if(bTest)
		   {
			strAll += str1 + " k2:" +IntToStr((int)itr->first)+"\r\n";
		   }
		  }
		  i++;
		 }

		 if(bTest)
		 {
		  str1 = INTERFACE_ID;
		  str1 += ".txt";

		  FILE *pFile = fopen(_c_str(str1),"w+b");
		  if(pFile != NULL)
		  {
		   fwrite(_c_str(strAll), strAll.Length(),1,pFile);
		   fclose(pFile);
		  }
		 }


		 m_nAllNumProbality = vPK.size();
		 m_pstrProbName = new AnsiString[m_nAllNumProbality];
		 m_pdDefaultProbArr = new double[m_nAllNumProbality];

		 double TypeProb[3];
		 TypeProb[0] = pow(10, -(0)*3);
		 TypeProb[1] = pow(10, -(1)*3);
		 TypeProb[2] = pow(10, -(2)*3);
		 m_PiKeyMap.clear();
		 for(i=0; i < m_nAllNumProbality; i++)
		 {
		  nKey = vPK[i];
		  m_PiKeyMap[nKey] = (TProbIndex)i;
		  nType = GetTypeFromKey(nKey);
		  GetProbNameFromKey(nKey, i+1, m_pstrProbName[i]);//имя вероятности
		  if(nType> 0 && nType < 4)
		   m_pdDefaultProbArr[i] = TypeProb[nType-1];//значение вероятности по умолчанию
		  else
		   nType /= 0;
		 }
		 Screen->Cursor = crDefault;

		 m_bInit = true;
		}
		LeaveCriticalSection(&m_InitCS);
	}
}
//---------------------------------------------------------------------------
AnsiString TAlmas7ProbSetGlobal::GetProbNameFromKey(TProbKey nKey)
{
	AnsiString strName = "Не реализовано";
	return strName;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas7ProbSetGlobal::GetProbNameFromKey(TProbKey nKey, int nNumber, AnsiString& strName)
{
	TAlmas7ProbSetKey psk;
	psk.fill2(nKey);
	int nType = GetTypeFromKey(nKey);

	strName.sprintf("%02d. (F%d, dS%d, nS%d)x%d - %d", nNumber, psk.F, psk.dS, psk.nS, nType, nKey);
}
//---------------------------------------------------------------------------
int __fastcall TAlmas7ProbSetGlobal::GetTypeFromKey(TProbKey BaseKey)
{
	int nType = 0;
	nType = divGetAdg1(BaseKey)+1;
	return nType;
}
//---------------------------------------------------------------------------
TAlmas7ProbSetGlobal& TAlmas7ProbSetGlobal::Get(void)
{//получение ссылки на глобальный класс
	return g_Almas7ProbSetGlobal;
}
//---------------------------------------------------------------------------
TProbIndex TAlmas7ProbSetGlobal::GetProbIndexFromAtomShema(TAtomShema &as)
{//получение индекса из набора для данного расположения атомов
	TProbIndex nPI = PI_ERROR;
	if(as.m_nMaxLayer < m_nNumLayerAtomShema)
	{
		throw Exception("TAlmas7ProbSetGlobal::GetProbIndexFromAtomShema - атомсхема описана недостаточно полно.");
	}
	if(as.GetBit(GetIndex0LevAdj()) == 1)
	{
		int F, dS, nS;
		F = 0;
		dS = 0;
		nS = 0;

		int i, j, k;
		int vnSecType[4];
		int nTreeType;


		AnsiString strTmp = as.ToStr2();

		nPI = PI_ERROR;
		for(i = 0; i < 4; i++)
		{
		 vnSecType[i] = 0;
		 if(as.GetBit(GetIndex1LevAdj(i)) == 1)
		 {//i-й первый сосед существует
		  F++; // есть первый сосед
		  vnSecType[i] = 1;
		  for(j = 0; j < 3; j++)
		  {
		   if(as.GetBit(GetIndex2LevAdj(i,j)) == 1)
		   {//j-й второй сосед у i-того первого соседа существует
			vnSecType[i]++;
			nTreeType = 1;
			for(k = 0; k < 3; k++)
			{
			 if(as.GetBit(GetIndex3LevAdj(i,j,k)) == 1)
			 {
			  nTreeType++;
			 }
			}
			if(nTreeType > 0)
			{
			 dS++; //есть второрой прямой сосед
			}
		   }
		  }
		 }
		 else
		 {//i-й первый сосед не существует
		  for(j = 0; j < 3; j++)
		  {
		   if(as.GetBit(GetIndex2LevAdj(i,j)) == 1)
		   {//второй сосед сущесвует
			nTreeType = 0;
			for(k = 0; k < 3; k++)
			{
			 if(as.GetBit(GetIndex3LevAdj(i,j,k)) == 1)
			 {//второй сосед имеет своего третьего соседа
			  nTreeType++;
			 }
			}
			if(nTreeType > 0)
			{
			 nS++; //есть второрой не прямой сосед
			}
		   }
		  }
		 }
		}

		if(nS > 9 || dS > 9)
		{
		 nPI = PI_ERROR;
		}
		else
		{
		 TProbKey2 nKey2;
		 SetKey2(nKey2, F, dS, nS);// формируем ключ2
		 TKey2ToKeyMap::iterator itr;
		 itr = m_Key2ToKeyMap.find(nKey2);//находим соответсвие ключа2 ключу1 (такого соответсвия может и не быть если атом четырёхсвязный)
		 if(itr != m_Key2ToKeyMap.end())
		 {
		  TProbKey nKey = itr->second;
		  //nPI = itr - m_Key2ToKeyMap.begin();  //предварительно нашли
		  TProbKeyMap::iterator itr2;
		  itr2 = m_PiKeyMap.find(nKey);//находим порядковый номер вероятности по его ключу 1
		  if(itr2 != m_PiKeyMap.end())
		   nPI = itr2->second;  //нашли
		  else
			nPI = PI_ERROR;
		 }
		 else
		 {
		  nPI = PI_ERROR;
		 }
		}
	}

	return nPI;
}
//---------------------------------------------------------------------------
int TAlmas7ProbSetGlobal::GetMainAtomTypeForProb(int Index)
{//получение типа главного атома для данной вероятности
	int nType = -1;

	if (Index >=0 && Index<m_nAllNumProbality && m_bInit)
	{
		TKey2ToKeyMap::iterator itr = m_Key2ToKeyMap.begin();
		for(int i = 0; i < Index; i++)
		{
		 itr++;
		}
		if(itr != m_Key2ToKeyMap.end())
		{
		 int nKey = itr->second;
		 nType =  divGetAdg1(nKey)+1;
		}
	}

	return nType;
}
//---------------------------------------------------------------------------
TAlmas7ProbSetCreator::TAlmas7ProbSetCreator()
:IBaseProbSetCreator(TAlmas7ProbSetGlobal::Get())
{
}
//---------------------------------------------------------------------------
IBaseProbSet* TAlmas7ProbSetCreator::Create()
{//создание набора вероятностей
	TAlmas7ProbSet *pNewProbSet = new TAlmas7ProbSet(*this);
	return pNewProbSet;
}
//---------------------------------------------------------------------------
TAlmas7ProbSet::TAlmas7ProbSet(IBaseProbSetCreator& Creator)
: IBaseProbSet(Creator)
{
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
