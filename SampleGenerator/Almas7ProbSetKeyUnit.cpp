//---------------------------------------------------------------------------


#pragma hdrstop

#include "Almas7ProbSetKeyUnit.h"
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas7ProbSet"
#define INTERFACE_NAME        "Первые и вторые прямые, вторые непрямые соседи"
#define INTERFACE_DISCRIPTION "Учитывается общее число первых соседей, число вторых прямых и число вторых непрямых соседей"
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
/*
 * Типы атомов в этой модели можно характеризовать тройкой знаков с числами,
 * например, (F, dS, nS) , где F – общее число первых соседей, dS – число вторых
 * прямых соседей, nS – число вторых непрямых соседей, соответственно.
 */
#define SetKey2(Key, F, dS, nS) Key = (nS%10 + 10*(dS%10) + 100*(F%10))
#define GetKey2(Key, F, dS, nS) nS = ((Key/1)%10); dS = ((Key/10)%10); F = ((Key/100)%10);
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
TProbKey Adg2Base_5(int i, int j)
{
static TProbKey cvAdg2Base[4][3] = { {Adg2Base_(0,0),Adg2Base_(0,1),Adg2Base_(0,2)},
									 {Adg2Base_(1,0),Adg2Base_(1,1),Adg2Base_(1,2)},
									 {Adg2Base_(2,0),Adg2Base_(2,1),Adg2Base_(2,2)},
									 {Adg2Base_(3,0),Adg2Base_(3,1),Adg2Base_(3,2)}
								   };
	return cvAdg2Base[i][j];
}
//---------------------------------------------------------------------------
TAlmas7ProbSetKey::TAlmas7ProbSetKey()
:TBaseProbSetKey()
{
	F = 0;
	dS = 0;
	nS = 0;
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
void __fastcall TAlmas7ProbSetKey::GetProbNameFromKey2(AnsiString &_strName)
{
	int nType = Adg1+1;
	strName.sprintf("%03d (F%d, dS%d, nS%d)x%d - %d", Key2, F, dS, nS, nType, Key);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TAlmas7ProbSetKey::GetProbSetId()
{
	return AnsiString(INTERFACE_ID);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
