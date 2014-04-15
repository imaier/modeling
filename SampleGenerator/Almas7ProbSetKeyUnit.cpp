//---------------------------------------------------------------------------


#pragma hdrstop

#include "Almas7ProbSetKeyUnit.h"
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

	GetProbNameFromKey2(strName);
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
int __fastcall TAlmas7ProbSetKey::GetAdjType(int i)
{
	int j;
	int Type = 0;
	int Adg2;

	if(Adg1 >= i)
	{
	 Type++;
	 for(j = 0; j < Adg2Num; j++)
	 {
	  Adg2 = divGetAdg2(Key, i, j);
	  if(Adg2 != (Adg2State-1))
	  {
	   Type++;
	  }
	 }
	}

	return Type;
}
//---------------------------------------------------------------------------
int __fastcall TAlmas7ProbSetKey::GetAdj2Type(int i,int j)
{
	int Type = 0;
	int Adg2;
	Adg2 = divGetAdg2(Key, i, j);
	if(Adg2 != (Adg2State-1))
	{
	 Type = Adg2+1;
	}
	return Type;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas7ProbSetKey::GetProbNameFromKey2(AnsiString &_strName)
{
	int nType = Adg1+1;
	strName.sprintf("%03d (F%d, dS%d, nS%d)x%d - %d", Key2, F, dS, nS, nType, Key);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
