//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Almas3ProbSetUnit.h"
#include <math.h>
#include <stdio.h>
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas3ProbSet"
#define INTERFACE_NAME        "Объемно-поверхностные (прямые)"
#define INTERFACE_DISCRIPTION "Учитываются только прямые объемные и поверхностнве атомы первых и вторых соседей"
//---------------------------------------------------------------------------
TAlmas3ProbSetGlobal g_Almas3ProbSetGlobal;
//---------------------------------------------------------------------------
TAlmas3ProbSetGlobal::TAlmas3ProbSetGlobal()
{
	m_IdString         = INTERFACE_ID;
	m_NameString       = INTERFACE_NAME;
	m_DiscrptionString = INTERFACE_DISCRIPTION;

	m_nNumLayerAtomShema = 3;
}
//---------------------------------------------------------------------------
TAlmas3ProbSetGlobal::~TAlmas3ProbSetGlobal()
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

//маски вторых соседей
#define Adg2MaskOffset(i,j) (4+6*i+2*j)
#define Adg2Mask(i,j) (0x03<<Adg2MaskOffset(i,j))
#define GetAdg2(Key,i,j) (Key&Adg2Mask(i,j))>>Adg2MaskOffset(i,j)
#define SetAdg2(Key,Data,i,j) Key = (Key&(~Adg2Mask(i,j))|((Data<<Adg2MaskOffset(i,j))&Adg2Mask(i,j)))
#define GetAdg(Key,i) (Key&(0x01<<(i)))
#define SetAdg(Key,Data,i) (Key = ((Key&(~(0x01<<(i))))|((Data&0x01)<<(i))))

#define AllAdg2Mask(i) (Adg2Mask(i,0)|Adg2Mask(i,1)|Adg2Mask(i,2))
#define GetAllAdg2(Key, i) ((Key&AllAdg2Mask(i))>>Adg2MaskOffset(i,0))
#define SetAllAdg2(Key,Data, i) (Key = ((Key&(~AllAdg2Mask(i)))|((Data<<Adg2MaskOffset(i,0))&AllAdg2Mask(i))))
const int nInvMask1 = ~(0x3F<<Adg2MaskOffset(0, 0));
const int nInvMask2 = ~(0x3F<<Adg2MaskOffset(0, 1));
const int nInvMask3 = ~(0x3F<<Adg2MaskOffset(0, 2));
const int nInvMask4 = ~(0x3F<<Adg2MaskOffset(0, 3));


//новый способ с делениями
#define Adg1Base 1
//количество первых соседей
#define Adg1State 3
//количество вторых соседей
#define Adg2Num 3
//количество состояний вторых соседей
#define Adg2State 5
//состояние вторых соседей означающее отсутсвие второго соседа
#define NoAdg2Val (Adg2State-1)
//емкость состояний для первых j соседей
#define Adg3State(j) IntPow(IntPow(Adg2State,Adg2Num), j)
//база
#define Adg2Base_(i, j) (Adg1State*Adg3State(j)*IntPow(Adg2State,i))

#define divGetAdg1(Key) (Key%Adg1State)
#define divSetAdg1(Key, Data) (Key + ((Data%Adg1State) - divGetAdg1(Key))*Adg1Base)
#define divGetAdg2(Key, i, j) ((Key/Adg2Base(i,j))%Adg2State)
#define divSetAdg2(Key, Data, i, j) (Key + ((Data%Adg2State) - divGetAdg2(Key,i,j))*Adg2Base(i,j))

//psk.n1s, psk.n1v, psk.n2s, psk.n2v
#define SetKey2(Key, n1s, n1v, n2s, n2v)   Key = (n2v%10 + 10*(n2s%10) + 100*(n1v%10) + 1000*(n1s%10))
#define GetKey2(Key, n1s, n1v, n2s, n2v)  n2v = ((Key/1)%10); n2s = ((Key/10)%10); n1v = ((Key/100)%10); n1s = ((Key/1000)%10);
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TProbKey Adg2Base(int i, int j)
{
static TProbKey cvAdg2Base[3][3] = { {Adg2Base_(0,0),Adg2Base_(1,0),Adg2Base_(2,0)},
									 {Adg2Base_(0,1),Adg2Base_(1,1),Adg2Base_(2,1)},
									 {Adg2Base_(0,2),Adg2Base_(1,2),Adg2Base_(2,2)}
								   };

	return cvAdg2Base[i][j];
}
TAlmas3ProbSetKey::TAlmas3ProbSetKey()
{
	Adg1 = 0;
	Adg2_i0_j0 = 0;
	Adg2_i1_j0 = 0;
	Adg2_i2_j0 = 0;
	Adg2_i0_j1 = 0;
	Adg2_i1_j1 = 0;
	Adg2_i2_j1 = 0;
	Adg2_i0_j2 = 0;
	Adg2_i1_j2 = 0;
	Adg2_i2_j2 = 0;

	n1s = 0;
	n1v = 0;
	n2v = 0;
	n2s = 0;

	Key2 = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas3ProbSetKey::fill(TProbKey nKey)
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


	Adg1 = divGetAdg1(nKey);
	Adg2_i0_j0 = divGetAdg2(nKey, 0, 0);
	//Adg2_i1_j0 = Adg2Base(1,0);
	Adg2_i1_j0 = divGetAdg2(nKey, 1, 0);
	//Adg2_i2_j0 = Adg2Base(2,0);
	Adg2_i2_j0 = divGetAdg2(nKey, 2, 0);
	Adg2_i0_j1 = divGetAdg2(nKey, 0, 1);
	Adg2_i1_j1 = divGetAdg2(nKey, 1, 1);
	Adg2_i2_j1 = divGetAdg2(nKey, 2, 1);
	Adg2_i0_j2 = divGetAdg2(nKey, 0, 2);
	Adg2_i1_j2 = divGetAdg2(nKey, 1, 2);
	Adg2_i2_j2 = divGetAdg2(nKey, 2, 2);

	fill2(nKey);

	int nType;
	int nNumber=-2;
	TAlmas3ProbSetGlobal::GetProbNameFromKey2(nKey, nType, nNumber, strName);
}
//---------------------------------------------------------------------------
void __fastcall TAlmas3ProbSetKey::fill2(TProbKey nKey)
{
	int i,j;
	int nAdjTtpeI;
	bool bNoVol;

	n1s = 0;
	n1v = divGetAdg1(nKey)+1;//по умолчанию считаем первых сосоедей объемными (4-х связными)
	n2v = 0;
	n2s = 0;

	for(j = 0; j < (signed)divGetAdg1(nKey)+1; j++)
	{
	 bNoVol = false;
	 for(i = 0; i < Adg2Num; i++)
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

	SetKey2(Key2, n1s, n1v, n2s, n2v);
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
TProbKey __fastcall TAlmas3ProbSetGlobal::RemoveLeftFromKey2(TProbKey BaseKey)
{//убрать лишние биты из ключа
	TProbKey nKey = BaseKey;
	int i,j;
	for(i = divGetAdg1(nKey); i < (Adg1State-1); i++)
	{
	 for(j = 0; j < Adg2Num; j++)
	 {
	  divSetAdg2(nKey, NoAdg2Val, i,j); //поставить что атома нет
	 }
	}
	return nKey;
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas3ProbSetGlobal::CanonateKey2(TProbKey BaseKey)
{
	TProbKey nKey = BaseKey;

	int i,j,k;
	int nAdjTtpeJ;
	int nAdjTtpeK;
	//сортировка вторых соседей
	for(i = 0; i < (signed)divGetAdg1(nKey)+1; i++)
	{
	 for(j = 0; j < Adg2Num-1; j++)
	 {
	  for(k = j+1; k < Adg2Num; k++)
	  {
	   nAdjTtpeJ = divGetAdg2(nKey, j, i);
	   nAdjTtpeK = divGetAdg2(nKey, k, i);
	   if(nAdjTtpeJ < nAdjTtpeK)
	   {
		divSetAdg2(nKey, nAdjTtpeK, j, i);
		divSetAdg2(nKey, nAdjTtpeJ, k, i);
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
TProbKey __fastcall TAlmas3ProbSetGlobal::KeyToKey2(TProbKey BaseKey)
{
	TAlmas3ProbSetKey psk;
	psk.fill2(BaseKey);
	return psk.Key2;
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas3ProbSetGlobal::RemoveLeftFromKey(TProbKey BaseKey)
{
	if((BaseKey & 0x01) == 0)
	 BaseKey &= nInvMask1;
	if((BaseKey & 0x02) == 0)
	 BaseKey &= nInvMask2;
	if((BaseKey & 0x04) == 0)
	 BaseKey &= nInvMask3;
	if((BaseKey & 0x08) == 0)
	 BaseKey &= nInvMask4;

	return BaseKey;
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas3ProbSetGlobal::CanonateKey(TProbKey BaseKey)
{//привести к канонической форме (вызывать после RemoveLeftFromKey)
	int vSecondTypes[4];
	int vSecondIndex[4];
	int vTreeTypes[3];
	int vTreeIndex[3];

	int Tmp, nTreeTypesJ, nTreeTypesK, nSecondTypesI, nSecondTypesJ;
	int i,j, k;
	for(i = 0; i < 4; i++)
	{
	 vSecondTypes[i] = 0;
	 vSecondIndex[i] = i;
	 if(GetAdg(BaseKey, i) > 0)
	 {
	  for(j = 0; j < 3; j++)
	  {
	   vTreeIndex[j] = j;
	   vTreeTypes[j] = GetAdg2(BaseKey, i, j);
	   if(vTreeTypes[j] != 0)
		vSecondTypes[i]++;
	  }
	  //SortAdg2(BaseKey, i);
	  {//сортировка третьих соседей
	   for(j = 0; j < (3-1); j++)
	   {
		for(k = j+1; k < 3; k++)
		{
		 nTreeTypesJ = vTreeIndex[j];
		 nTreeTypesK = vTreeIndex[k];
		 if(vTreeTypes[nTreeTypesJ] > vTreeTypes[nTreeTypesK] )
		 {
		  //Tmp = vTreeTypes[nTreeTypesJ];
		  //vTreeTypes[nTreeTypesJ] = vTreeTypes[nTreeTypesK];
		  //vTreeTypes[nTreeTypesK] = Tmp;
		  vTreeIndex[j] = nTreeTypesK;
		  vTreeIndex[k] = nTreeTypesJ;
		 }
		}
	   }
	  }//сортировка третьих соседей

	  //заносим обратно
	  for(j = 0; j < 3; j++)
	  {
	   SetAdg2(BaseKey,vTreeTypes[vTreeIndex[j]], i, j);
	  }
	 }
	}

	{//сортировка вторых соседей
	 for(i = 0; i < (4-1); i++)
	 {
	  for(j = i+1; j < 4; j++)
	  {
	   nSecondTypesI = vSecondIndex[i];
	   nSecondTypesJ = vSecondIndex[j];
	   if(vTreeTypes[nSecondTypesI] > vTreeTypes[nSecondTypesJ] )
	   {
		vSecondIndex[j] = nSecondTypesI;
		vSecondIndex[i] = nSecondTypesJ;
	   }
	  }
	 }
	}//сортировка вторых соседей

	//заносим обратно
	{
	 int nSecondAdj1;
	 int nTreeAdj1;
	 int nSecondAdj2;
	 int nTreeAdj2;
	 for(i = 0; i < 4; i++)
	 {
	  nSecondTypesI = vSecondIndex[i];
	  if(nSecondTypesI != i)
	  {
	   nSecondAdj1 = GetAdg(BaseKey, i);
	   nTreeAdj1 = GetAllAdg2(BaseKey, i);
	   nSecondAdj2 = GetAdg(BaseKey, nSecondTypesI);
	   nTreeAdj2 = GetAllAdg2(BaseKey, nSecondTypesI);
	   SetAdg(BaseKey,     nSecondAdj2,   i);
	   SetAllAdg2(BaseKey, nTreeAdj2,     i);
	   SetAdg(BaseKey,     nSecondAdj1,   nSecondTypesI);
	   SetAllAdg2(BaseKey, nTreeAdj1,     nSecondTypesI);
	  }
	 }
	}
	return BaseKey;
}
//---------------------------------------------------------------------------
void TAlmas3ProbSetGlobal::Init(void)
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
			nKey2 = RemoveLeftFromKey2( nKey );
			if(nKey2 == nKey)
			{//нет избыточности
			 nKey2 = CanonateKey2(nKey);
			 if(nKey2 == nKey)
			 {//правильно отсортирован
			  bChk2 = true;
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
		  TProbKey nMaxKey = Adg2Base(2,2)*Adg2State;
		  TProbKey nKey, nKey2;

		  for(nKey = 0; nKey < nMaxKey; nKey++)
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

		 TAlmas3ProbSetKey k1,k2;
		 //k1.fill(2468447);
		 //k2.fill(2468495);
		 //k1.fill(189012);//22. (s1, v0; s0, v0)x1 - 189012
		 k1.fill(14);//22. (s1, v0; s0, v0)x1 - 189012

		 TKey2ToKeyMap::iterator itr;
		 vPK.clear();
		 bool bTest = false;
		 //bTest = true;
		 //AnsiString strAll, str1;
		 //int i=0;
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
AnsiString TAlmas3ProbSetGlobal::GetProbNameFromKey(TProbKey nKey)
{
	AnsiString strName = "Не реализовано";
	return strName;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas3ProbSetGlobal::GetProbNameFromKey2(TProbKey nKey, int &nType, int &nNumber, AnsiString& strName)
{
/*
	//strName = "Не реализовано";
	static int n1s;
	static int n1v;
	static int n2s;
	static int n2v;
	int i,j;
	static int nAdjTtpeJ;
	static bool bNoVol;


	n1s = 0;
	n1v = divGetAdg1(nKey)+1;//по умолчанию считаем первых сосоедей объемными (4-х связными)
	n2v = 0;
	n2s = 0;

	for(i = 0; i < (signed)divGetAdg1(nKey)+1; i++)
	{
	 for(j = 0; j < Adg2Num; j++)
	 {
	  nAdjTtpeJ = divGetAdg2(nKey, i, j);
	  if(nAdjTtpeJ == NoAdg2Val)
	  {//второго соседа нету
	   bNoVol = true;
	  }
	  else
	  {
	   if(nAdjTtpeJ == 3)
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
 */

	TAlmas3ProbSetKey psk;
	psk.fill2(nKey);
	nType = GetTypeFromKey2(nKey);


	strName.sprintf("%02d. (s%d, v%d; s%d, v%d)x%d - %d", nNumber+1, psk.n1s, psk.n1v, psk.n2s, psk.n2v, nType, nKey);
}
//---------------------------------------------------------------------------
int __fastcall TAlmas3ProbSetGlobal::GetTypeFromKey2(TProbKey BaseKey)
{
	int nType = 0;
	nType = divGetAdg1(BaseKey)+1;
	return nType;
}
//---------------------------------------------------------------------------
int __fastcall TAlmas3ProbSetGlobal::GetTypeFromKey(TProbKey BaseKey)
{
	int nType = 0;
	for(int i=0; i < 4; i++)
	{
	 if( GetAdg(BaseKey,i) > 0)
	  nType++;
	}
	return nType;
}
//---------------------------------------------------------------------------
TAlmas3ProbSetGlobal& TAlmas3ProbSetGlobal::Get(void)
{//получение ссылки на глобальный класс
	return g_Almas3ProbSetGlobal;
}
//---------------------------------------------------------------------------
TProbIndex TAlmas3ProbSetGlobal::GetProbIndexFromAtomShema(TAtomShema &as)
{//получение индекса из набора для данного расположения атомов
	TProbIndex nPI = PI_ERROR;
	if(as.m_nMaxLayer < m_nNumLayerAtomShema)
	{
		throw Exception("TAlmas3ProbSetGlobal::GetProbIndexFromAtomShema - атомсхема описана недостаточно полно.");
	}
	if(as.GetBit(GetIndex0LevAdj()) == 1)
	{
		int n1s = 0;
		int n1v = 0;
		int n2s = 0;
		int n2v = 0;

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
		 SetKey2(nKey2, n1s, n1v, n2s, n2v);// формируем ключ2 (n1s+n1v+n2s+n2v)
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
int TAlmas3ProbSetGlobal::GetMainAtomTypeForProb(int Index)
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
TAlmas3ProbSetCreator::TAlmas3ProbSetCreator()
:IBaseProbSetCreator(TAlmas3ProbSetGlobal::Get())
{
}
//---------------------------------------------------------------------------
IBaseProbSet* TAlmas3ProbSetCreator::Create()
{//создание набора вероятностей
	TAlmas3ProbSet *pNewProbSet = new TAlmas3ProbSet(*this);
	return pNewProbSet;
}
//---------------------------------------------------------------------------
TAlmas3ProbSet::TAlmas3ProbSet(IBaseProbSetCreator& Creator)
: IBaseProbSet(Creator)
{
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

