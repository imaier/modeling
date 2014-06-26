//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Almas3ProbSetKeyUnit.h"
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas3ProbSet"
#define INTERFACE_NAME        "Объемно-поверхностные (прямые)"
#define INTERFACE_DISCRIPTION "Учитываются только прямые объемные и поверхностнве атомы первых и вторых соседей"
//---------------------------------------------------------------------------

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
TProbKey Adg2Base(int i, int j)
{
static TProbKey cvAdg2Base[3][3] = { {Adg2Base_(0,0),Adg2Base_(1,0),Adg2Base_(2,0)},
									 {Adg2Base_(0,1),Adg2Base_(1,1),Adg2Base_(2,1)},
									 {Adg2Base_(0,2),Adg2Base_(1,2),Adg2Base_(2,2)}
								   };

	return cvAdg2Base[i][j];
}
//---------------------------------------------------------------------------
TAlmas3ProbSetKey::TAlmas3ProbSetKey()
:TBaseProbSetKey()
{
	n1s = 0;
	n1v = 0;
	n2v = 0;
	n2s = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas3ProbSetKey::fill(TProbKey nKey)
{
	Key = nKey;

	Adg1 = divGetAdg1(nKey);
	Adg2_i0_j0 = divGetAdg2(nKey, 0, 0);
	Adg2_i1_j0 = divGetAdg2(nKey, 1, 0);
	Adg2_i2_j0 = divGetAdg2(nKey, 2, 0);
	Adg2_i0_j1 = divGetAdg2(nKey, 0, 1);
	Adg2_i1_j1 = divGetAdg2(nKey, 1, 1);
	Adg2_i2_j1 = divGetAdg2(nKey, 2, 1);
	Adg2_i0_j2 = divGetAdg2(nKey, 0, 2);
	Adg2_i1_j2 = divGetAdg2(nKey, 1, 2);
	Adg2_i2_j2 = divGetAdg2(nKey, 2, 2);

	fill2(nKey);

	GetProbNameFromKey2(strName);
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
void __fastcall TAlmas3ProbSetKey::GetProbNameFromKey2(AnsiString &_strName)
{
	_strName.sprintf("%04d (s%d, v%d; s%d, v%d)x%d - %d", Key2, n1s, n1v, n2s, n2v, Adg1+1, Key);
}
//---------------------------------------------------------------------------
/*
void __fastcall TAlmas3ProbSetGlobal::GetProbNameFromKey2(TProbKey nKey, int &nType, int &nNumber, AnsiString& strName)
{

	TAlmas3ProbSetKey psk;
	psk.fill2(nKey);
	nType = GetTypeFromKey2(nKey);


	strName.sprintf("%02d. (s%d, v%d; s%d, v%d)x%d - %d", nNumber+1, psk.n1s, psk.n1v, psk.n2s, psk.n2v, nType, nKey);
} */
//---------------------------------------------------------------------------
AnsiString __fastcall TAlmas3ProbSetKey::GetProbSetId()
{
	return AnsiString(INTERFACE_ID);
}
//---------------------------------------------------------------------------
int __fastcall TAlmas3ProbSetKey::GetAdjType(int i)
{
	int j;
	int Type = 0;
	int Adg2;

	if(Adg1 >= i)
	{
	 Type++;
	 for(j = 0; j < Adg2Num; j++)
	 {
	  if (i < Adg1State)
	  {
	   Adg2 = divGetAdg2(Key, i, j);
	  }
	  else
	  {
	   Adg2 = Adg2State-1;
	  }
	  if(Adg2 != (Adg2State-1))
	  {
	   Type++;
	  }
	 }
	}

	return Type;
}
//---------------------------------------------------------------------------
int __fastcall TAlmas3ProbSetKey::GetAdj2Type(int i,int j)
{
	int Type = 0;
	int Adg2;
	if (i < Adg1State)
	{
	 Adg2 = divGetAdg2(Key, i, j);
	}
	else
	{
	 Adg2 = Adg2State-1;
	}
	if(Adg2 != (Adg2State-1))
	{
	 Type = Adg2+1;
	}
	return Type;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

