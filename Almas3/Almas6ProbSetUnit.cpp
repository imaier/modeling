//---------------------------------------------------------------------------
#pragma hdrstop

#include "Almas6ProbSetUnit.h"

#include <math.h>
#include <stdio.h>
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas6ProbSet"
#define INTERFACE_NAME        "Объемно-поверхностные (без прямых поверхностных вторых сосседей)"
//#define INTERFACE_DISCRIPTION "Учитываются прямые и не прямые объемные атомы первых и вторых соседей и поверхностнве атомы первых соседей"
#define INTERFACE_DISCRIPTION "Учитываются поверхностные и объемные атомы первых соседей, прямые объемные и не прямые поверхностные атомы вторых соседей"

//---------------------------------------------------------------------------
TAlmas6ProbSetGlobal g_Almas6ProbSetGlobal;
//---------------------------------------------------------------------------
TAlmas6ProbSetGlobal::TAlmas6ProbSetGlobal()
{
	m_IdString         = INTERFACE_ID;
	m_NameString       = INTERFACE_NAME;
	m_DiscrptionString = INTERFACE_DISCRIPTION;

	m_nNumLayerAtomShema = 3;
}
//---------------------------------------------------------------------------
TAlmas6ProbSetGlobal::~TAlmas6ProbSetGlobal()
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

#define SetKey2(Key, n1s, n1v, n2v, nns)   Key = (nns%10 + 10*(n2v%10) + 100*(n1v%10) + 1000*(n1s%10))
#define GetKey2(Key, n1s, n1v, n2v, nns)  nns = ((Key/1)%10); n2v = ((Key/10)%10); n1v = ((Key/100)%10); n1s = ((Key/1000)%10);
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
TAlmas6ProbSetKey::TAlmas6ProbSetKey()
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

	n1s = 0;
	n1v = 0;
	n2v = 0;
	n2s = 0;
	nns = 0;

	Key2 = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas6ProbSetKey::fill(TProbKey nKey)
{
//#define Adg1Base 1
//количество первых соседей
//#define Adg1State 3
//количество вторых соседей
//#define Adg2Num 3
//количество состояний вторых соседей
//#define Adg2State 5
//состояние вторых соседей означающее отсутсвие второго соседа
//#define NoAdg2Val (Adg2State-1)
//емкость состояний для первых j соседей
//#define Adg3State(j) (IntPow(IntPow(Adg2State,Adg2Num), j))
//база
//#define Adg2Base(i, j) (Adg1State*Adg3State(j)*IntPow(Adg2State,i))

//#define divGetAdg1(Key) (Key%Adg1State)
//#define divSetAdg1(Key, Data) (Key + ((Data%Adg1State) - divGetAdg1(Key))*Adg1Base)
//#define divGetAdg2(Key, i, j) ((Key/Adg2Base(i,j))%Adg2State)
//#define divSetAdg2(Key, Data, i, j) (Key + ((Data%Adg2State) - divGetAdg2(Key,i,j))*Adg2Base(i,j))

	Key = nKey;

	Adg1 = divGetAdg1(nKey);
	Adg2_i0_j0 = divGetAdg2(nKey, 0, 0);
	//Adg2_i1_j0 = Adg2Base(1,0);
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

	int nType;
	int nNumber=-2;
	TAlmas6ProbSetGlobal::GetProbNameFromKey2(nKey, nType, nNumber, strName);
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas6ProbSetKey::unfill()
{
	TProbKey nKey = 0;

	//int ii = Adg3State(0);

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

	TAlmas6ProbSetKey k1;
	k1.fill(Key);


	TProbKey nKey30;
	TProbKey nKey31;
	TProbKey nKey32;

	divSetAdg2(nKey30, Adg2_i3_j0, 3, 0);
	divSetAdg2(nKey31, Adg2_i3_j1, 3, 1);
	divSetAdg2(nKey32, Adg2_i3_j2, 3, 2);


 /*
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
 */
	return nKey;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas6ProbSetKey::fill2(TProbKey nKey)
{
	int i,j;
	int nAdjTtpeI;
	bool bNoVol;

	n1s = 0;
	n1v = divGetAdg1(nKey)+1;//по умолчанию считаем первых сосоедей объемными (4-х связными)
	n2v = 0;
	n2s = 0;
	nns = 0;

	for(i = 0; i < (signed)divGetAdg1(nKey)+1; i++)
	{
	 bNoVol = false;
	 for(j = 0; j < Adg2Num; j++)
	 {
	  nAdjTtpeI = divGetAdg2(nKey, i, j);
	  if(nAdjTtpeI == NoAdg2Val)
	  {//второго соседа нету
	   bNoVol = true;
	  }
	  else
	  {
	   if(nAdjTtpeI == 3)
	   {//второй сосед объемный
		n2v++;
	   }
	   else
	   {//второй сосед поверхностный
		n2s++;
	   }
	  }
	 }
	 if(bNoVol == true)
	 {//сосед не четырёхсвязный - значит он поверхностный
	  n1s++;//чило поверхностных увеличить
	  n1v--;//число объемных уменьшить
	 }
	}

	for(i = divGetAdg1(nKey)+1; i < Adg1State; i++)
	{
	 for(j = 0; j < Adg2Num; j++)
	 {
	  nAdjTtpeI = divGetAdg2(nKey, i, j);
	  if(nAdjTtpeI == NoAdg2Val)
	  {//второго соседа нету
	   //bNoVol = true;
	  }
	  else
	  {//есть второй сосед без присутсвия первого - не прямой второй сосед
	   nns++;
	  }
	 }
	}

	SetKey2(Key2, n1s, n1v, n2v, nns);
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
TProbKey __fastcall TAlmas6ProbSetGlobal::RemoveLeftFromKey2(TProbKey BaseKey)
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
TProbKey __fastcall TAlmas6ProbSetGlobal::CanonateKey2(TProbKey BaseKey)
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
bool __fastcall TAlmas6ProbSetGlobal::ChekKey2(TProbKey nKey)
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
TProbKey __fastcall TAlmas6ProbSetGlobal::KeyToKey2(TProbKey BaseKey)
{
	TAlmas6ProbSetKey psk;
	psk.fill2(BaseKey);
	return psk.Key2;
}
//---------------------------------------------------------------------------
void TAlmas6ProbSetGlobal::Init(void)
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


		 TAlmas6ProbSetKey k1,k2;
		 k1.fill(14);//22. (s1, v0; s0, v0)x1 - 189012

		 k2.Adg1 = 1;
		 k2.Adg2_i0_j0 = 3;
		 k2.Adg2_i0_j1 = 3;
		 k2.Adg2_i0_j2 = 3;
		 k2.Adg2_i1_j0 = 3;
		 k2.Adg2_i1_j1 = 3;
		 k2.Adg2_i1_j2 = 3;
		 k2.Adg2_i2_j0 = NoAdg2Val;
		 k2.Adg2_i2_j1 = NoAdg2Val;
		 k2.Adg2_i2_j2 = 2;
		 k2.Adg2_i3_j0 = NoAdg2Val;
		 k2.Adg2_i3_j1 = NoAdg2Val;
		 k2.Adg2_i3_j2 = 2;

		 k2.unfill();

		 k1.fill(k2.Key);

		 //bool bck = ChekKey2(k2.Key);

		 AnsiString strAll, str1;
		 AnsiString szFilename;
		 szFilename = GetProgramPath()+INTERFACE_ID;
		 szFilename += ".cfg";




		 TProbKey nKey, nKey2;

		 int i=0;
		 if(FileExists(szFilename) == true)
		 {
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
		   //int nKey2ToKeyMapSize = m_Key2ToKeyMap.size();
		   for(i = 0; (i < nPkSize) && bChk; i++)
		   {
			nKey = vPK[i];
			bChk2 = false;
			if(ChekKey2(nKey))
			{
			 nKey2 = RemoveLeftFromKey2( nKey );
			 if(nKey2 == nKey)
			 {//нет избыточности
			  nKey2 = CanonateKey2(nKey);
			  if(nKey2 == nKey)
			  {//правильно отсортирован
			   bChk2 = true;
			  }
			 }
			}
			if(bChk2 != true)
			{
			 bChk = false;
			}
			//nKey2ToKeyMapSize = m_Key2ToKeyMap.size();
		   }
		   if(bChk == false)
		   {
			vPK.clear();
		   }
		  }
		 }

		 if(vPK.size()==0)
		 {
		  m_Key2ToKeyMap.clear();
		  TProbKey nMaxKey = Adg2Base(Adg1State-1,Adg2Num-1)*Adg2State;
		  for(nKey = 0; nKey < nMaxKey; nKey++)
		  {
		   if(k2.Key == nKey)
		   {
			k2.Key = nKey;
		   }
		   if(ChekKey2(nKey))
		   {
			nKey2 = RemoveLeftFromKey2( nKey );
			if(nKey2 == nKey)
			{//нет избыточности
			 nKey2 = CanonateKey2(nKey);
			 if(nKey2 == nKey)
			 {//правильно отсортирован
			  vPK.push_back(nKey);//добавляем в мап
			 }
			}
		   }
		  }
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
		   k1.fill2(itr->second);
		   GetProbNameFromKey2(itr->second, nType, i, str1);//имя вероятности
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
		  //nType = GetTypeFromKey2(nKey);
		  GetProbNameFromKey2(nKey, nType, i, m_pstrProbName[i]);//имя вероятности
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
AnsiString TAlmas6ProbSetGlobal::GetProbNameFromKey(TProbKey nKey)
{
	AnsiString strName = "Не реализовано";
	return strName;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas6ProbSetGlobal::GetProbNameFromKey2(TProbKey nKey, int &nType, int &nNumber, AnsiString& strName)
{
	TAlmas6ProbSetKey psk;
	psk.fill2(nKey);
	nType = GetTypeFromKey2(nKey);

	strName.sprintf("%02d. (s%d, v%d; v%d, ns%d)x%d - %d", nNumber+1, psk.n1s, psk.n1v, psk.n2v, psk.nns, nType, nKey);
}
//---------------------------------------------------------------------------
int __fastcall TAlmas6ProbSetGlobal::GetTypeFromKey2(TProbKey BaseKey)
{
	int nType = 0;
	nType = divGetAdg1(BaseKey)+1;
	return nType;
}
//---------------------------------------------------------------------------
TAlmas6ProbSetGlobal& TAlmas6ProbSetGlobal::Get(void)
{//получение ссылки на глобальный класс
	return g_Almas6ProbSetGlobal;
}
//---------------------------------------------------------------------------
TProbIndex TAlmas6ProbSetGlobal::GetProbIndexFromAtomShema(TAtomShema &as)
{//получение индекса из набора для данного расположения атомов
	TProbIndex nPI = PI_ERROR;
	if(as.m_nMaxLayer < m_nNumLayerAtomShema)
	{
		throw Exception("TAlmas6ProbSetGlobal::GetProbIndexFromAtomShema - атомсхема описана недостаточно полно.");
	}
	if(as.GetBit(GetIndex0LevAdj()) == 1)
	{
		int n1s = 0;
		int n1v = 0;
		int n2s = 0;
		int n2v = 0;
		int nns = 0;

		int i, j, k;
		int vnSecType[4];
		int nTreeType;

		AnsiString strTmp = as.ToStr2();

		nPI = PI_ERROR;
		for(i = 0; i < 4; i++)
		{
		 vnSecType[i] = 0;
		 if(as.GetBit(GetIndex1LevAdj(i)) == 1)
		 {
		  vnSecType[i] = 1;
		  for(j = 0; j < 3; j++)
		  {
		   if(as.GetBit(GetIndex2LevAdj(i,j)) == 1)
		   {
			vnSecType[i]++;
			nTreeType = 1;
			for(k = 0; k < 3; k++)
			{
			 if(as.GetBit(GetIndex3LevAdj(i,j,k)) == 1)
			 {
			  nTreeType++;
			 }
			}
			if(nTreeType==4)
			{
			 n2v++;
			}
			else
			{
			 n2s++;
			}
		   }
		  }
		 }
		 else
		 {
		  for(j = 0; j < 3; j++)
		  {
		   nTreeType = 0;
		   if(as.GetBit(GetIndex2LevAdj(i,j)) == 1)
		   {
			nTreeType = 1;
			for(k = 0; k < 3; k++)
			{
			 if(as.GetBit(GetIndex3LevAdj(i,j,k)) == 1)
			 {
			  nTreeType++;
			 }
			}
			if(nTreeType>1)
			{
			 nns++;
			}
		   }
		  }
		 }

		 if(vnSecType[i]>0)
		 {
		  if(vnSecType[i]<4)
		  {
		   n1s++;
		  }
		  else
		  {
		   n1v++;
		  }
		 }
		}

		if(n2s > 9 || n2v > 9)
		{
		 nPI = PI_ERROR;
		}
		else
		{
		 TProbKey2 nKey2;
		 SetKey2(nKey2, n1s, n1v, n2v, nns);// формируем ключ2 (n1s+n1v+n2v+nns)
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
int TAlmas6ProbSetGlobal::GetMainAtomTypeForProb(int Index)
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
int TAlmas6ProbSetGlobal::Get_nS_CountForProb(int Index)
{//получение количества непрямых вторых соседей для данной вероятности
	int nCnt = -1;

	if (Index >=0 && Index<m_nAllNumProbality && m_bInit)
	{
		TKey2ToKeyMap::iterator itr = m_Key2ToKeyMap.begin();
		for(int i = 0; i < Index; i++)
		{
		 itr++;
		}
		if(itr != m_Key2ToKeyMap.end())
		{
		 TProbKey nKey = itr->second;
		 TAlmas6ProbSetKey ProbSetKey;
		 ProbSetKey.fill(nKey);
		 nCnt =  ProbSetKey.nns;
		}
	}

	return nCnt;
}
//---------------------------------------------------------------------------
TAlmas6ProbSetCreator::TAlmas6ProbSetCreator()
:IBaseProbSetCreator(TAlmas6ProbSetGlobal::Get())
{
}
//---------------------------------------------------------------------------
IBaseProbSet* TAlmas6ProbSetCreator::Create()
{//создание набора вероятностей
	TAlmas6ProbSet *pNewProbSet = new TAlmas6ProbSet(*this);
	return pNewProbSet;
}
//---------------------------------------------------------------------------
TAlmas6ProbSet::TAlmas6ProbSet(IBaseProbSetCreator& Creator)
: IBaseProbSet(Creator)
{
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
