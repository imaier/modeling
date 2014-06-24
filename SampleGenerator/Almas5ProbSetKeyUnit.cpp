//---------------------------------------------------------------------------
#pragma hdrstop

#include "Almas5ProbSetKeyUnit.h"

#include <math.h>
//#include <stdio.h>
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas5ProbSet"
#define INTERFACE_NAME        "Объемно-поверхностные (без объемных вторых сосседей)"
#define INTERFACE_DISCRIPTION "Учитываются прямые и не прямые поверхностнве атомы первых и вторых соседей и объемные атомы перых соседей"
//---------------------------------------------------------------------------

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

#define SetKey2(Key, n1s, n1v, n2s, nns)   Key = (nns%10 + 10*(n2s%10) + 100*(n1v%10) + 1000*(n1s%10))
#define GetKey2(Key, n1s, n1v, n2s, nns)  nns = ((Key/1)%10); n2s = ((Key/10)%10); n1v = ((Key/100)%10); n1s = ((Key/1000)%10);
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

TAlmas5ProbSetKey::TAlmas5ProbSetKey()
:TBaseProbSetKey()
{
	n1s = 0;
	n1v = 0;
	n2v = 0;
	n2s = 0;
	nns = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas5ProbSetKey::fill2(TProbKey nKey)
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

	SetKey2(Key2, n1s, n1v, n2s, nns);
}

//---------------------------------------------------------------------------
void __fastcall TAlmas5ProbSetKey::GetProbNameFromKey2(AnsiString &_strName)
{
	_strName.sprintf("%04d (s%d, v%d; s%d, ns%d)x%d - %d", Key2, n1s, n1v, n2v, nns, Adg1+1, Key);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TAlmas5ProbSetKey::GetProbSetId()
{
	return AnsiString(INTERFACE_ID);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
