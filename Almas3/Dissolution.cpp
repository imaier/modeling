//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#pragma warn -pck

//против такого варнинга пишем #pragma warn -com
//[BCC32 Warning] Dissolution.cpp(201): W8010 Continuation character \ found in // comment
#pragma warn -com

#include "Dissolution.h"
#include "MaskUnit.h"
#include "Matrix.h"
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
const CnstDtType = 4;
const CnstDtIndex = -1;
//---------------------------------------------------------------------------
#ifdef Almas100
const int NumAtomsInCell = 8; //число атомов в ячейке
const int NumCollumInCell = 8;//число столбцов в одной ячейке по сои Z
const int Num1AtomLayerInCell = 4; //количествоб одноатомных подслоев в ячейке  (слой толщиной в один атом)
#endif
#ifdef Almas110
const int NumAtomsInCell = 8;//число атомов в ячейке
const int NumCollumInCell = 8;
const int Num1AtomLayerInCell = 2; //количествоб одноатомных подслоев в ячейке
#endif
#ifdef Almas111
const int NumAtomsInCell = 18;//число атомов в ячейке
const int NumCollumInCell = 9;//число столбцов из атомов в ячейке по сои Z
const int Num1AtomLayerInCell = 6; //количествоб одноатомных подслоев в ячейке
#endif

#define STOP_BAC BigArrayCoord(0,4,10,2)

int _random(int Max);
void _randomize();

//---------------------------------------------------------------------------
//TATOM::TATOM()
//{
//	Type = 4;
//    Index = -1;
//}
//---------------------------------------------------------------------------
TCC::TCC(int Na, int i, int j, int k)
{
	N    = Na;
    di   = i;
	dj   = j;
    dk   = k;
}
//---------------------------------------------------------------------------
TCr::TCr(int x, int y, int z, int _SubLayer)
{
	dx   = x;
	dy   = y;
	dz   = z;
	SubLayer = _SubLayer;
}
//---------------------------------------------------------------------------
//Таблица связей
const TCC LinksTable[NumAtomsInCell/*8*/][4]=
{
#ifdef Almas100
// номер |   сосед №1     |   сосед №2    |   сосед №3    |   сосед №4    |
// атома |                |               |               |               |
  /* 1*/  {TCC(8,-1,-1,-1),TCC(6, 0, 0,-1),TCC(4,-1, 0, 0),TCC(2, 0,-1, 0)},
  /* 2*/  {TCC(1, 0,+1, 0),TCC(3, 0, 0, 0),TCC(5, 0, 0, 0),TCC(7, 0,+1, 0)},
  /* 3*/  {TCC(6, 0, 0,-1),TCC(8, 0, 0,-1),TCC(2, 0, 0, 0),TCC(4, 0, 0, 0)},
  /* 4*/  {TCC(3, 0, 0, 0),TCC(1,+1, 0, 0),TCC(7, 0, 0, 0),TCC(5,+1, 0, 0)},
  /* 5*/  {TCC(4,-1, 0, 0),TCC(2, 0, 0, 0),TCC(8,-1, 0, 0),TCC(6, 0, 0, 0)},
  /* 6*/  {TCC(5, 0, 0, 0),TCC(7, 0, 0, 0),TCC(1, 0, 0,+1),TCC(3, 0, 0,+1)},
  /* 7*/  {TCC(2, 0,-1, 0),TCC(4, 0, 0, 0),TCC(6, 0, 0, 0),TCC(8, 0,-1, 0)},
  /* 8*/  {TCC(7, 0,+1, 0),TCC(5,+1, 0, 0),TCC(3, 0, 0,+1),TCC(1,+1,+1,+1)},
#endif
#ifdef Almas110
// номер |   сосед №1     |   сосед №2    |   сосед №3    |   сосед №4    |
// атома |                |               |               |               |
//1/1
//  /* 1*/  {TCC(8,-1,-1, 0),TCC(7, 0,-1, 0),TCC(3, 0, 0, 0),TCC(3, 0, 0,-1)},
//  /* 2*/  {TCC(7, 0,-1, 0),TCC(8, 0,-1, 0),TCC(4, 0, 0, 0),TCC(4, 0, 0,-1)},
//  /* 3*/  {TCC(1, 0, 0,+1),TCC(1, 0, 0, 0),TCC(6,-1, 0, 0),TCC(5, 0, 0, 0)},
//  /* 4*/  {TCC(2, 0, 0,+1),TCC(2, 0, 0, 0),TCC(5, 0, 0, 0),TCC(6, 0, 0, 0)},
//  /* 5*/  {TCC(3, 0, 0, 0),TCC(4, 0, 0, 0),TCC(7, 0, 0,+1),TCC(7, 0, 0, 0)},
//  /* 6*/  {TCC(4, 0, 0, 0),TCC(3,+1, 0, 0),TCC(8, 0, 0,+1),TCC(8, 0, 0, 0)},
//  /* 7*/  {TCC(5, 0, 0, 0),TCC(5, 0, 0,-1),TCC(1, 0,+1, 0),TCC(2, 0,+1, 0)},
//  /* 8*/  {TCC(6, 0, 0, 0),TCC(6, 0, 0,-1),TCC(2, 0,+1, 0),TCC(1,+1,+1, 0)},
//1/2
///* 1*/  {TCC(8,-1,-1, 0),TCC(7, 0,-1, 0),TCC(3, 0, 0, 0),TCC(3, 0, 0,+1)},
///* 2*/  {TCC(7, 0,-1, 0),TCC(8, 0,-1, 0),TCC(4, 0, 0, 0),TCC(4, 0, 0,+1)},
///* 3*/  {TCC(1, 0, 0,-1),TCC(1, 0, 0, 0),TCC(6,-1, 0, 0),TCC(5, 0, 0, 0)},
///* 4*/  {TCC(2, 0, 0,-1),TCC(2, 0, 0, 0),TCC(5, 0, 0, 0),TCC(6, 0, 0, 0)},
///* 5*/  {TCC(3, 0, 0, 0),TCC(4, 0, 0, 0),TCC(7, 0, 0,-1),TCC(7, 0, 0, 0)},
///* 6*/  {TCC(4, 0, 0, 0),TCC(3,+1, 0, 0),TCC(8, 0, 0,-1),TCC(8, 0, 0, 0)},
///* 7*/  {TCC(5, 0, 0, 0),TCC(5, 0, 0,+1),TCC(1, 0,+1, 0),TCC(2, 0,+1, 0)},
///* 8*/  {TCC(6, 0, 0, 0),TCC(6, 0, 0,+1),TCC(2, 0,+1, 0),TCC(1,+1,+1, 0)},

//2/1
//  /* 1*/  {TCC(4,-1, 0, 0),TCC(3, 0, 0, 0),TCC(7, 0,-1, 0),TCC(7, 0,-1,-1)},
//  /* 2*/  {TCC(3, 0, 0, 0),TCC(4, 0, 0, 0),TCC(8, 0,-1, 0),TCC(8, 0,-1,-1)},
//  /* 3*/  {TCC(5, 0, 0, 0),TCC(5, 0, 0,-1),TCC(1, 0, 0, 0),TCC(2, 0, 0, 0)},
//  /* 4*/  {TCC(6, 0, 0, 0),TCC(6, 0, 0,-1),TCC(2, 0, 0, 0),TCC(1,+1, 0, 0)},
//  /* 5*/  {TCC(7, 0, 0, 0),TCC(8, 0, 0, 0),TCC(3, 0, 0,+1),TCC(3, 0, 0, 0)},
//  /* 6*/  {TCC(8, 0, 0, 0),TCC(7,+1, 0, 0),TCC(4, 0, 0,+1),TCC(4, 0, 0, 0)},
//  /* 7*/  {TCC(1, 0,+1,+1),TCC(1, 0,+1, 0),TCC(6,-1, 0, 0),TCC(5, 0, 0, 0)},
//  /* 8*/  {TCC(2, 0,+1,+1),TCC(2, 0,+1, 0),TCC(5, 0, 0, 0),TCC(6, 0, 0, 0)},
//2/
  /* 1*/  {TCC(4,-1, 0, 0),TCC(3, 0, 0, 0),TCC(7, 0,-1, 0),TCC(7, 0,-1,-1)},
  /* 2*/  {TCC(3, 0, 0, 0),TCC(4, 0, 0, 0),TCC(8, 0,-1, 0),TCC(8, 0,-1,-1)},
  /* 3*/  {TCC(5, 0, 0, 0),TCC(5, 0, 0,-1),TCC(1, 0, 0, 0),TCC(2, 0, 0, 0)},
  /* 4*/  {TCC(6, 0, 0, 0),TCC(6, 0, 0,-1),TCC(2, 0, 0, 0),TCC(1,+1, 0, 0)},
  /* 5*/  {TCC(7, 0, 0, 0),TCC(8, 0, 0, 0),TCC(3, 0, 0,+1),TCC(3, 0, 0, 0)},
  /* 6*/  {TCC(8, 0, 0, 0),TCC(7,+1, 0, 0),TCC(4, 0, 0,+1),TCC(4, 0, 0, 0)},
  /* 7*/  {TCC(1, 0,+1,+1),TCC(1, 0,+1, 0),TCC(6,-1, 0, 0),TCC(5, 0, 0, 0)},
  /* 8*/  {TCC(2, 0,+1,+1),TCC(2, 0,+1, 0),TCC(5, 0, 0, 0),TCC(6, 0, 0, 0)},
#endif
#ifdef Almas111
//// номер |   сосед №1    |   сосед №2   |   сосед №3   |   сосед №4    |
//// атома |               |              |              |               |
//  /* 1*/  {TCC(6,-1,-1,0),TCC(2, 0, 0,0),TCC(3, 0, 0,0),TCC(13,0,0,-1)},
//  /* 2*/  {TCC(1, 0, 0,0),TCC(5,-1, 0,0),TCC(4, 0, 0,0),TCC(7, 0, 0,0)},
//  /* 3*/  {TCC(4, 0,-1,0),TCC(1, 0, 0,0),TCC(5, 0, 0,0),TCC(8, 0, 0,0)},
//  /* 4*/  {TCC(2, 0, 0,0),TCC(3, 0,+1,0),TCC(6, 0, 0,0),TCC(17,0,0,-1)},
//  /* 5*/  {TCC(3, 0, 0,0),TCC(6, 0, 0,0),TCC(2,+1, 0,0),TCC(18,0,0,-1)},
//  /* 6*/  {TCC(5, 0, 0,0),TCC(4, 0, 0,0),TCC(1,+1,+1,0),TCC(12,0, 0,0)},
//  /* 7*/  {TCC(11,-1,0,0),TCC(9, 0, 0,0),TCC(10,0, 0,0),TCC(2, 0, 0,0)},
//  /* 8*/  {TCC(9, 0,-1,0),TCC(10,0, 0,0),TCC(11,0, 0,0),TCC(3, 0, 0,0)},
//  /* 9*/  {TCC(7, 0, 0,0),TCC(12,-1,0,0),TCC(8, 0,+1,0),TCC(14,0, 0,0)},
//  /*10*/  {TCC(8, 0, 0,0),TCC(7, 0, 0,0),TCC(12,0, 0,0),TCC(15,0, 0,0)},
//  /*11*/  {TCC(12,0,-1,0),TCC(8, 0, 0,0),TCC(7,+1, 0,0),TCC(16,0, 0,0)},
//  /*12*/  {TCC(10,0, 0,0),TCC(11,0,+1,0),TCC(9,+1, 0,0),TCC(6, 0, 0,0)},
//  /*13*/  {TCC(14,0,-1,0),TCC(16,-1,0,0),TCC(15,0, 0,0),TCC(1, 0,0,+1)},
//  /*14*/  {TCC(18,-1,0,0),TCC(13,0,+1,0),TCC(17,0, 0,0),TCC(9, 0, 0,0)},
//  /*15*/  {TCC(13,0, 0,0),TCC(17,0, 0,0),TCC(18,0, 0,0),TCC(10,0, 0,0)},
//  /*16*/  {TCC(17,0,-1,0),TCC(18,0, 0,0),TCC(13,+1,0,0),TCC(11,0, 0,0)},
//  /*17*/  {TCC(15,0, 0,0),TCC(14,0, 0,0),TCC(16,0,+1,0),TCC(4, 0,0,+1)},
//  /*18*/  {TCC(16,0, 0,0),TCC(15,0, 0,0),TCC(14,+1,0,0),TCC(5, 0,0,+1)}
//2
// номер |   сосед №1    |   сосед №2   |   сосед №3   |   сосед №4    |
// атома |               |              |              |               |
  /* 1*/  {TCC(13,0,0,-1),TCC(6,-1,-1,0),TCC(3, 0, 0,0),TCC(2, 0, 0,0)},
  /* 2*/  {TCC(1, 0, 0,0),TCC(5,-1, 0,0),TCC(4, 0, 0,0),TCC(7, 0, 0,0)},
  /* 3*/  {TCC(4, 0,-1,0),TCC(1, 0, 0,0),TCC(5, 0, 0,0),TCC(8, 0, 0,0)},
  /* 4*/  {TCC(17,0,0,-1),TCC(2, 0, 0,0),TCC(6, 0, 0,0),TCC(3, 0,+1,0)},
  /* 5*/  {TCC(18,0,0,-1),TCC(3, 0, 0,0),TCC(2,+1, 0,0),TCC(6, 0, 0,0)},
  /* 6*/  {TCC(5, 0, 0,0),TCC(4, 0, 0,0),TCC(1,+1,+1,0),TCC(12,0, 0,0)},
  /* 7*/  {TCC(2, 0, 0,0),TCC(11,-1,0,0),TCC(10,0, 0,0),TCC(9, 0, 0,0)},
  /* 8*/  {TCC(3, 0, 0,0),TCC(9, 0,-1,0),TCC(11,0, 0,0),TCC(10,0, 0,0)},
  /* 9*/  {TCC(7, 0, 0,0),TCC(12,-1,0,0),TCC(8, 0,+1,0),TCC(14,0, 0,0)},
  /*10*/  {TCC(8, 0, 0,0),TCC(7, 0, 0,0),TCC(12,0, 0,0),TCC(15,0, 0,0)},
  /*11*/  {TCC(12,0,-1,0),TCC(8, 0, 0,0),TCC(7,+1, 0,0),TCC(16,0, 0,0)},
  /*12*/  {TCC(6, 0, 0,0),TCC(10,0, 0,0),TCC(9,+1, 0,0),TCC(11,0,+1,0)},
  /*13*/  {TCC(14,0,-1,0),TCC(16,-1,0,0),TCC(15,0, 0,0),TCC(1, 0,0,+1)},
  /*14*/  {TCC(9, 0, 0,0),TCC(18,-1,0,0),TCC(17,0, 0,0),TCC(13,0,+1,0)},
  /*15*/  {TCC(10,0, 0,0),TCC(13,0, 0,0),TCC(18,0, 0,0),TCC(17,0, 0,0)},
  /*16*/  {TCC(11,0, 0,0),TCC(17,0,-1,0),TCC(13,+1,0,0),TCC(18,0, 0,0)},
  /*17*/  {TCC(15,0, 0,0),TCC(14,0, 0,0),TCC(16,0,+1,0),TCC(4, 0,0,+1)},
  /*18*/  {TCC(16,0, 0,0),TCC(15,0, 0,0),TCC(14,+1,0,0),TCC(5, 0,0,+1)}
#endif
};
//---------------------------------------------------------------------------
//Таблица координат
const TCr CoordTable[NumAtomsInCell/*8*/]=
{
#ifdef Almas100
// номер | координаты |номер атомного подслоя
// атома |            |0-бэйзед
  /* 1*/  TCr( 0, 0, 0, 0),
  /* 2*/  TCr( 1, 3, 1, 1),
  /* 3*/  TCr( 2, 2, 0, 0),
  /* 4*/  TCr( 3, 1, 1, 1),
  /* 5*/  TCr( 0, 2, 2, 2),
  /* 6*/  TCr( 1, 1, 3, 3),
  /* 7*/  TCr( 2, 0, 2, 2),
  /* 8*/  TCr( 3, 3, 3, 3),
#endif
#ifdef Almas110
// номер | координаты |номер атомного подслоя
// атома |            |0-бэйзед
//  /* 1*/  TCr( 0, 0, 0),
//  /* 2*/  TCr( 2, 2, 0),
//  /* 3*/  TCr(-1, 1,-1),
//  /* 4*/  TCr( 1, 3,-1),
//  /* 5*/  TCr( 0, 2,-2),
//  /* 6*/  TCr( 2, 4,-2),
//  /* 7*/  TCr( 1, 1,-3),
//  /* 8*/  TCr( 3, 3,-3),
//1/1
//  /* 1*/  TCr( 0, 0, 0),
//  /* 2*/  TCr( 2, 2, 0),
//  /* 3*/  TCr(-1, 1, 1),
//  /* 4*/  TCr( 1, 3, 1),
//  /* 5*/  TCr( 0, 2, 2),
//  /* 6*/  TCr( 2, 4, 2),
//  /* 7*/  TCr( 1, 1, 3),
//  /* 8*/  TCr( 3, 3, 3),
//2

//ячейка 110  *- атомы верхнего атомного подслоя, o- атомы нижнего атомного подслоя
//
//  1*  2*   *
//    \ / \ /
//    3*  4*
//     |   |
//    5o  6o
//    / \ / \
//  7o  8o   o
//
  /* 1*/  TCr( 0, 0, 0, 0),
  /* 2*/  TCr( 2, 2, 0, 0),
  /* 3*/  TCr( 1, 1,-1, 0),
  /* 4*/  TCr( 3, 3,-1, 0),
  /* 5*/  TCr( 0, 2,-2, 1),
  /* 6*/  TCr( 2, 4,-2, 1),
  /* 7*/  TCr(-1, 1,-3, 1),
  /* 8*/  TCr( 1, 3,-3, 1),
//2
//  /* 1*/  TCr( 0, 0, 0),
//  /* 2*/  TCr( 2, 2, 0),
//  /* 3*/  TCr( 1, 1,-1),
//  /* 4*/  TCr( 3, 3,-1),
//  /* 5*/  TCr( 0, 2,-2),
//  /* 6*/  TCr( 2, 4,-2),
//  /* 7*/  TCr(-1, 1,-3),
//  /* 8*/  TCr( 1, 3,-3),
#endif
#ifdef Almas111

//ячейка 111  *- атомы верхнего атомного подслоя, o- атомы нижнего атомного подслоя
//   первый уровень  | второй уровень | третий уровень
//                   |                |
//                   |                |
//        *          |                |         o
//         \         |                |        /
//          o        |      9o-*      |       *14
//         /         |      /   \     |        \
//    2o- *4         |    7*     o    |       17o-*
//    /    \         |      \   /     |        /   \
//  1*    6o-*       |     10o-*12    |   13o-*15   o
//    \   /          |      /   \     |        \   /
//    3o-*5          |    8*     o    |       18o-*
//        \          |      \   /     |        /
//         o         |     11o-*      |       *16
//        /          |                |        \
//       *           |                |         o
//



// номер | координаты |номер атомного подслоя
// атома |            |0-бэйзед
  /* 1*/  TCr( 0, 0, 0, 0),
  /* 2*/  TCr( 1, 1,-1, 1),
  /* 3*/  TCr( 1,-1, 1, 1),
  /* 4*/  TCr( 2, 0,-2, 0),
  /* 5*/  TCr( 2,-2, 0, 0),
  /* 6*/  TCr( 3,-1,-1, 1),
  /* 7*/  TCr( 2, 2, 0, 2),
  /* 8*/  TCr( 2, 0, 2, 2),
  /* 9*/  TCr( 3, 3,-1, 3),
  /*10*/  TCr( 3, 1, 1, 3),
  /*11*/  TCr( 3,-1, 3, 3),
  /*12*/  TCr( 4, 0, 0, 2),
  /*13*/  TCr( 3, 3, 3, 5),
  /*14*/  TCr( 4, 4, 0, 4),
  /*15*/  TCr( 4, 2, 2, 4),
  /*16*/  TCr( 4, 0, 4, 4),
  /*17*/  TCr( 5, 3, 1, 5),
  /*18*/  TCr( 5, 1, 3, 5),
#endif
};
//---------------------------------------------------------------------------
bool TUndoDissolutionThread::SaveToFile(HANDLE hFile, int *pSeek /*= NULL*/)
{//сохранить структуру в поток
	bool bRet = false;
	int nSeek = 0;
	DWORD NumberOfBytesToWrite, NumberOfBytesWritten;
	bool bwf = true;
	int i;

	   NumberOfBytesToWrite = sizeof(Count);
	   bwf &= WriteFile(hFile,&(Count),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(SizeX);
	   bwf &= WriteFile(hFile,&(SizeX),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(SizeY);
	   bwf &= WriteFile(hFile,&(SizeY),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(NumAtomsInCell);
	   bwf &= WriteFile(hFile,&(NumAtomsInCell),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(NumAtomsInLayer);
	   bwf &= WriteFile(hFile,&(NumAtomsInLayer),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(CopacityMemoryForLayer);
	   bwf &= WriteFile(hFile,&(CopacityMemoryForLayer),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(OneX);
	   bwf &= WriteFile(hFile,&(OneX),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(OneY);
	   bwf &= WriteFile(hFile,&(OneY),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(OneN);
	   bwf &= WriteFile(hFile,&(OneN),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(SizeDtType);
	   bwf &= WriteFile(hFile,&(SizeDtType),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(SizeDtIndex);
	   bwf &= WriteFile(hFile,&(SizeDtIndex),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(SizeBothDtTypeDtIndex);
	   bwf &= WriteFile(hFile,&(SizeBothDtTypeDtIndex),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(iDeletedAtom);
	   bwf &= WriteFile(hFile,&(iDeletedAtom),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   bwf &= SP.SaveToFile(hFile, &nSeek);
	   bwf &= m_Algoritm.SaveToFile(hFile, &nSeek);

	   NumberOfBytesToWrite = sizeof(Finish);
	   bwf &= WriteFile(hFile,&(Finish),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(Plane);
	   bwf &= WriteFile(hFile,&(Plane),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(StartTime);
	   bwf &= WriteFile(hFile,&(StartTime),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = sizeof(FinishTime);
	   bwf &= WriteFile(hFile,&(FinishTime),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = Count*sizeof(int);
	   bwf &= WriteFile(hFile, (Watch),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   NumberOfBytesToWrite = CopacityMemoryForLayer;
	   for(i = 0; i < Count; i++)
	   {
		if(Watch[i] > 0)
		{
		 bwf &= WriteFile(hFile, (Items[i]),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
		 nSeek+= (bwf)?NumberOfBytesWritten:0;
		}
	   }

	   KindAtoms.SaveToFile(hFile, &nSeek);
	   /*
	   NumberOfBytesToWrite = sizeof(nProbCnt);
	   bwf &= WriteFile(hFile,&(nProbCnt),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek += (bwf)?NumberOfBytesWritten:0;

	   if(nProbCnt > 0)
	   {
		NumberOfBytesToWrite = nProbCnt*sizeof(KindAtomsCount[0]);
		bwf &= WriteFile(hFile,&(KindAtomsCount[0]),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
		nSeek+= (bwf)?NumberOfBytesWritten:0;

		for(i = 0; i < nProbCnt; i++)
		{
		 NumberOfBytesToWrite = KindAtomsCount[i]*sizeof(BigArrayCoord);
		 if(NumberOfBytesToWrite > 0)
		 {
		  bwf &= WriteFile(hFile, (KindAtoms[i]),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
		  nSeek+= (bwf)?NumberOfBytesWritten:0;
		 }
		}
	   }
	   */

	if(pSeek != NULL)
	{
	 *pSeek += nSeek;
	}
	bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
bool TUndoDissolutionThread::LoadFromFile(HANDLE hFile, int *pSeek /*= NULL*/)
{//загрузить структуру из потока
	bool bRet = false;
	int nSeek = 0;
	DWORD NumberOfBytesRead,NumberOfBytesReaded;
	int i;
	bool bwf = true;

		NumberOfBytesRead = sizeof(Count);
		bwf &= ReadFile(hFile,&Count,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(SizeX);
		bwf &= ReadFile(hFile,&(SizeX),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(SizeY);
		bwf &= ReadFile(hFile,&(SizeY),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(NumAtomsInCell);
        bwf &= ReadFile(hFile,&(NumAtomsInCell),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(NumAtomsInLayer);
		bwf &= ReadFile(hFile,&(NumAtomsInLayer),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(CopacityMemoryForLayer);
        bwf &= ReadFile(hFile,&(CopacityMemoryForLayer),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

        NumberOfBytesRead = sizeof(OneX);
        bwf &= ReadFile(hFile,&(OneX),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(OneY);
        bwf &= ReadFile(hFile,&(OneY),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

        NumberOfBytesRead = sizeof(OneN);
        bwf &= ReadFile(hFile,&(OneN),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

        NumberOfBytesRead = sizeof(SizeDtType);
        bwf &= ReadFile(hFile,&(SizeDtType),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

        NumberOfBytesRead = sizeof(SizeDtIndex);
        bwf &= ReadFile(hFile,&(SizeDtIndex),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

        NumberOfBytesRead = sizeof(SizeBothDtTypeDtIndex);
        bwf &= ReadFile(hFile,&(SizeBothDtTypeDtIndex),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

        NumberOfBytesRead = sizeof(iDeletedAtom);
        bwf &= ReadFile(hFile,&(iDeletedAtom),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		bwf &= SP.LoadFromFile(hFile, &nSeek);

		bwf &= m_Algoritm.LoadFromFile(hFile, &nSeek);

        NumberOfBytesRead = sizeof(Finish);
        bwf &= ReadFile(hFile,&(Finish),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(Plane);
        bwf &= ReadFile(hFile,&(Plane),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

        NumberOfBytesRead = sizeof(StartTime);
        bwf &= ReadFile(hFile,&(StartTime),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

		NumberOfBytesRead = sizeof(FinishTime);
        bwf &= ReadFile(hFile,&(FinishTime),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

        if(Count != 0)
        {
         Watch = new int[Count];
         Items = new char*[Count];
		 NumberOfBytesRead = Count*sizeof(int);
         bwf &= ReadFile(hFile,(Watch),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
         nSeek += (bwf)?NumberOfBytesReaded:0;
         NumberOfBytesRead = CopacityMemoryForLayer;

         for(i = 0; i < Count; i++)
         {
          if(Watch[i] > 0)
          {
           Items[i] = new char[CopacityMemoryForLayer];
           bwf &= ReadFile(hFile,(Items[i]),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
           nSeek += (bwf)?NumberOfBytesReaded:0;
		  }
          else Items[i] = NULL;
		 }
		}

		KindAtoms.LoadFromFile(hFile, &nSeek);
		/*
		NumberOfBytesRead = sizeof(nProbCnt);
		bwf &= ReadFile(hFile,&(nProbCnt),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

		if(nProbCnt > 0)
		{
		 KindAtomsCount = new int[nProbCnt];
		 KindAtoms = new BigArrayCoord*[nProbCnt];
		 NumberOfBytesRead = nProbCnt*sizeof(KindAtomsCount[0]);
		 bwf &= ReadFile(hFile,&(KindAtomsCount[0]),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		 nSeek += (bwf)?NumberOfBytesReaded:0;
		 for(i = 0; i < nProbCnt; i++)
		 {
		  NumberOfBytesRead = KindAtomsCount[i]*sizeof(BigArrayCoord);
		  if(NumberOfBytesRead > 0)
		  {
		   KindAtoms[i] = new BigArrayCoord[KindAtomsCount[i]];
		   bwf &= ReadFile(hFile,(KindAtoms[i]),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		   nSeek += (bwf)?NumberOfBytesReaded:0;
		  }
		  else
		  {
		   KindAtoms[i] = NULL;
		  }
		 }
		}
		else
		{
		 KindAtomsCount = NULL;
		 KindAtoms = NULL;
		}
		*/

	if(pSeek != NULL)
	{
	 *pSeek += nSeek;
	}
	bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
TUndoDissolutionThread::TUndoDissolutionThread()
{
	Watch = NULL;
	Count = 0;
	Items = NULL;

	Clear();
}
//---------------------------------------------------------------------------
TUndoDissolutionThread::~TUndoDissolutionThread()
{
	Clear();
}
//---------------------------------------------------------------------------
void TUndoDissolutionThread::Clear(void)
{
	int i;
	if(Count > 0)
	{
	 for(i = 0; i < Count; i++)
	 {
	  if(Watch[i] != 0 && Items[i] != NULL)
		delete [] Items[i];
	 }
	 delete [] Items;
	 delete [] Watch;
	}

	Watch = NULL;
	Count = 0;
	Items = NULL;

	KindAtoms.clear();

	SizeX = 0;
	SizeY = 0;; //размер поверхности
	NumAtomsInCell = 0;
	NumAtomsInLayer = 0;
	CopacityMemoryForLayer = 0;
	OneX = 0;
	OneY = 0;
	OneN = 0;
	SizeDtType = 0;
	SizeDtIndex = 0;
	SizeBothDtTypeDtIndex = 0;
	iDeletedAtom = 0;

	SP.ClearInterface();
	Finish = false;
	Plane = 0;
}
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TDissolutionThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TDissolutionThread::TDissolutionThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
    //NumAtomsInCell = 8;
    NumAtomsInLayer = 0;
    CopacityMemoryForLayer = 0;
    SizeDtType = sizeof(DtType);
	SizeDtIndex = sizeof(DtIndex);
	SizeBothDtTypeDtIndex = SizeDtType + SizeDtIndex;
	OneN = SizeBothDtTypeDtIndex;
	Items = new TList;
	Watch = new TList;
	Items->Clear();
	Watch->Clear();
	int i;
	MaskAll=false;//по умолчанию маскировать только первый слой
	KindAtoms.clear();
	setmem(&m_CS, 0 ,sizeof(m_CS));
	InitializeCriticalSection(&m_CS);
	m_InitRng = false;
}
//---------------------------------------------------------------------------
__fastcall TDissolutionThread::~TDissolutionThread()
{
	while(Items->Count != 0)
	{
	 if(*((int*)(Watch->Items[Watch->Count-1])) > 0) delete Items->Items[Items->Count-1];
	 delete Watch->Items[Watch->Count-1];
	 Items->Delete(Items->Count-1);
	 Watch->Delete(Watch->Count-1);
	}
	delete Items;
	delete Watch;
	KindAtoms.clear();
	DeleteCriticalSection(&m_CS);
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::AddLayers(unsigned int Indx)
{
    char *pAtoms;
    int i;
	while((signed)Indx >= Items->Count)
    {
     pAtoms = new char[CopacityMemoryForLayer];
     for(i=0; i < NumAtomsInLayer; i++)
     {
      *(DtType*)(pAtoms +(i*SizeBothDtTypeDtIndex)) = CnstDtType;// 4
      *(DtIndex*)(pAtoms +(i*SizeBothDtTypeDtIndex + SizeDtType)) = CnstDtIndex;// -1
     }
     Items->Add(pAtoms);
     int *pInt;
     pInt = new int;
     *pInt = NumAtomsInLayer;
     Watch->Add(pInt);
    }
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::DecTypeAtom(BigArrayCoord* BAC)
{
	if(BAC->Z >= (unsigned)Items->Count) AddLayers(BAC->Z);
    if(*((int*)(Watch->Items[BAC->Z])) <= 0)
    {
     throw Exception("DecTypeAtom error. Layer deleted. Access dinieded.");
     //return;
    }
    DtType* Type =(DtType*)(((char*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN);
    //pAtom =((TATOM*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN + SizeDtType;
    if(*Type == 0)
    {
     throw Exception("DecTypeAtom error. Atom->Type is zero, don't decremented.");
     //return;
    }
    //pAtom->Type--;
    (*Type)--;
    if(*Type == 0)
    {
     (*(int*)(Watch->Items[BAC->Z]))--;
     iDeletedAtom++;
    }
    if((*(int*)(Watch->Items[BAC->Z])) <= 0) delete Items->Items[BAC->Z];
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::SetToZeroTypeAtom(BigArrayCoord* BAC)
{
	if(BAC->Z >= (unsigned)Items->Count) AddLayers(BAC->Z);
	if(*((int*)(Watch->Items[BAC->Z])) <= 0)
	{
	 throw Exception("SetToZeroTypeAtom error. Layer deleted. Access dinieded.");
	 //return;
	}
	DtType* Type =(DtType*)(((char*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN);
	//pAtom =((TATOM*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N;
	if(*Type == 0)
	{
	 throw Exception("SetToZeroTypeAtom error. Atom->Type is zero, don't delete deleted atom.");
	 //return;
	}
	if(*BAC == STOP_BAC)
	{
	 Type = Type;
	}

    *Type = 0;
    (*(int*)(Watch->Items[BAC->Z]))--;
	iDeletedAtom++;
    if((*(int*)(Watch->Items[BAC->Z])) <= 0) delete Items->Items[BAC->Z];
}
//---------------------------------------------------------------------------
unsigned char __fastcall TDissolutionThread::GetTypeAtom(BigArrayCoord* BAC)
{
    //TATOM *pAtom;
    if(BAC->Z == 0xffffffff) return 0;
	if(BAC->Z >= (unsigned)Items->Count)
	{
	 //throw Exception("GetTypeAtom. Layer no init. Access dinieded.");
	 return CnstDtType;
	}
	if(*((int*)(Watch->Items[BAC->Z])) <= 0)
	{
	 //throw Exception("GetTypeAtom error. Layer deleted. Access dinieded.");
	 return 0;
	}
	return *(DtType*)(((char*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN);
}
//---------------------------------------------------------------------------
int __fastcall TDissolutionThread::GetIndexAtom(BigArrayCoord* BAC)
{
	if(BAC->Z >= (unsigned)Items->Count)
    {
	 throw Exception("GetIndexAtom error. Layer no init. Access dinieded.");
     //return 0;
    }
    if((*(int*)(Watch->Items[BAC->Z])) <= 0)
    {
     throw Exception("GetIndexAtom error. Layer deleted. Access dinieded.");
     //return 0;
    }
    return *(DtIndex*)(((char*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN + SizeDtType);
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::SetNoDeletedTypeAtom(BigArrayCoord* BAC)
{
	if(BAC->Z >= (unsigned)Items->Count) AddLayers(BAC->Z);
    if(*((int*)(Watch->Items[BAC->Z])) <= 0)
    {
     throw Exception("SetNoDeletedTypeAtom error. Layer deleted. Access dinieded.");
     //return;
    }
    DtType* Type =(DtType*)(((char*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN);
    //pAtom =((TATOM*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN + SizeDtType;
    if(*Type == 0)
    {
     throw Exception("SetNoDeletedTypeAtom error. Atom->Type is zero, don't decremented.");
     //return;
    }
    //pAtom->Type--;
    (*Type) = 5;
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::SetIndexAtom(BigArrayCoord* BAC, int Indx)
{
	if(BAC->Z >= (unsigned)Items->Count)
	{
     throw Exception("SetIndexAtom. Layer no init. Access dinieded.");
	 //return;
	}
	if(*((int*)(Watch->Items[BAC->Z])) <= 0)
	{
	 throw Exception("SetIndexAtom error. Layer deleted. Access dinieded.");
	 //return;
	}

	if(*BAC ==  STOP_BAC)
	{
	 BAC->N = BAC->N;
	}

	//if(DeletedAtom>2239)
    //{
	// if((BAC->X == 4)&&
    //    (BAC->Y == 3)&&
    //    (BAC->Z == 0)&&
	//    ((BAC->N == 0)||(BAC->N == 2)))
    // Indx == Indx;
    //}
	*(DtIndex*)(((char*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN + SizeDtType) = Indx;
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::SetTypeAtom(BigArrayCoord* BAC)
{
    if((signed)BAC->Z < 0) return;

    //if(DeletedAtom>2239)
    //{
    // if((BAC->X == 4)&&
    //    (BAC->Y == 3)&&
    //    (BAC->Z == 0)&&
    //    ((BAC->N == 0)||(BAC->N == 2)))
    // BAC == BAC;
    //}

	unsigned char TypeAtom,TmpType, i;
	BigArrayCoord TempAtomBAC;
    TypeAtom = 0;
    for(i=1; i<=4; i++)
    {
	 CopyBAC1toBAC2(BAC, &TempAtomBAC);
     AdjacentAtom(i, &TempAtomBAC);//получаем координаты соседа
	 TmpType = GetTypeAtom(&TempAtomBAC);// его тип
	 if(TmpType != 0) TypeAtom++;
	}
	TmpType = GetTypeAtom(BAC);
	if((signed)BAC->Z >= Items->Count) AddLayers(BAC->Z);
    if((*((int*)(Watch->Items[BAC->Z])) <= 0)&&(TypeAtom > 0)&&(TmpType > 0))
    {
     throw Exception("SetTypeAtom error. Layer deleted. Access dinieded.");
	 //return;
    }
    if(*((int*)(Watch->Items[BAC->Z])) > 0)
    {
     DtType* Type =(DtType*)(((char*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN);
     if((*Type != 0)&&(*Type != 5)&&(*Type != 6))
     {
      *Type = TypeAtom;
	  if(*Type == 0)
	  {
	   (*(int*)(Watch->Items[BAC->Z]))--;
	   iDeletedAtom++;
	  }
	 }
     //else
     //{
     //  *Type = TypeAtom;
     // if(*Type != 0)
     // {
     //  (*(int*)(Watch->Items[BAC->Z]))++;
     //  iDeletedAtom--;
     // }
     //}

	 if((*(int*)(Watch->Items[BAC->Z])) <= 0) delete Items->Items[BAC->Z];
     //else
     //{
      //switch(TypeAtom)
      //{
	  // case 1:
      // case 2:
      // case 3:
      //  AddLBACtoKindsArrays(TypeAtom-1,BAC);
      // break;
      //}
     //}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::DelLBACFromKindsArrays(int Sort, int Indx)
{
	int nSize = 0;
	int nSize2 = 0;
	nSize = KindAtoms.size();
	if(Sort < nSize)
	{
		nSize2 = KindAtoms[Sort].size();
		if(Indx < nSize2)
		{
			if(KindAtoms[Sort][Indx] == STOP_BAC)
			{
			 Sort = Sort;
			}
		}
	}

	if(Indx < (int)KindAtoms[Sort].size()-1)
	{
	 KindAtoms[Sort][Indx]=KindAtoms[Sort][KindAtoms[Sort].size()-1];
	 SetIndexAtom((BigArrayCoord*)&KindAtoms[Sort][Indx], Indx);
	}
	KindAtoms[Sort].pop_back();

/*
	void *p;
	//if(Indx>KindAtoms[Sort]->Count)
	// p = KindAtoms[Sort]->Items[Indx];

	p = KindAtoms[Sort]->Items[Indx];
	if(Indx < KindAtoms[Sort]->Count-1)
	{
	 KindAtoms[Sort]->Items[Indx] = KindAtoms[Sort]->Last();
	 SetIndexAtom((BigArrayCoord*)KindAtoms[Sort]->Items[Indx], Indx);
	}
	KindAtoms[Sort]->Delete(KindAtoms[Sort]->Count-1);
	delete p;

*/
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::AddLBACtoKindsArrays(int Sort, BigArrayCoord* BAC)
{
	//if(DeletedAtom >= 2240 )
	//{
	// if((BAC->X == 17)&&
	//    (BAC->Y == 11)&&
	//    (BAC->Z == 0)&&
	//    (BAC->N == 0))
	// Sort == Sort;
	//}
	if(*BAC == STOP_BAC)
	{
	 BAC->N = BAC->N;
	}

	KindAtoms[Sort].push_back(BigArrayCoord(*BAC));
	SetIndexAtom(&(KindAtoms[Sort][KindAtoms[Sort].size()-1]), KindAtoms[Sort].size()-1);

	//BigArrayCoord* BAC2 = new BigArrayCoord;
	//CopyBAC1toBAC2(BAC, BAC2);
	//SetIndexAtom(BAC2, KindAtoms[Sort]->Add(BAC2));
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::AdjacentAtom(int N, BigArrayCoord* BAC)
{
	BAC->X += LinksTable[BAC->N][N-1].di;
	BAC->Y += LinksTable[BAC->N][N-1].dj;
	BAC->Z += LinksTable[BAC->N][N-1].dk;
	BAC->N  = LinksTable[BAC->N][N-1].N - 1;

    BAC->X = (unsigned short int)((SizeX+((signed short int)BAC->X))%SizeX);
    BAC->Y = (unsigned short int)((SizeY+((signed short int)BAC->Y))%SizeY);
}
//---------------------------------------------------------------------------
/*
void __fastcall TDissolutionThread::AdjacentAtom1(BigArrayCoord* BAC)
{
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::AdjacentAtom2(BigArrayCoord* BAC)
{
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::AdjacentAtom3(BigArrayCoord* BAC)
{
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::AdjacentAtom4(BigArrayCoord* BAC)
{
}
*/
//---------------------------------------------------------------------------
BigArrayCoord::BigArrayCoord(const BigArrayCoord& BAC)
{
	*this = BAC;
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::CopyBAC1toBAC2(BigArrayCoord* BAC1,BigArrayCoord* BAC2)
{
	*BAC2 = *BAC1;
}
//---------------------------------------------------------------------------
void TDissolutionThread::InitIdealSmoothSurface(int NewX,int NewY)
{
	int i;
	SurfaceMode SrfcMd = smFirst;//smSecond;//smFirst;//тип поверхности
	SizeX = NewX;
	SizeY = NewY;
	NumAtomsInLayer = SizeY * SizeX * NumAtomsInCell;
	CopacityMemoryForLayer = NumAtomsInLayer * SizeBothDtTypeDtIndex;
	OneX = NumAtomsInCell * OneN;
	OneY = OneX * SizeX;
	while(Items->Count != 0)
	{
	 if((*(int*)(Watch->Items[Watch->Count-1])) > 0) delete Items->Items[Items->Count-1];
	 delete Watch->Items[Watch->Count-1];
	 Items->Delete(Items->Count-1);
	 Watch->Delete(Watch->Count-1);
	}

	bool bRet = KindAtoms.InitFomProb(SP);
	if( bRet == false )
		return;

	iDeletedAtom = 0;

	BigArrayCoord BAC;
	unsigned char TypeAtom;
	int Kind;
	BAC.Z = 0;
	for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	{
	 for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	 {
	  for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
	  {
	   SetTypeAtom(&BAC);
	  }
	 }
	}

	switch(SrfcMd)
	{
	 case smFirst:
	  for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	  {
	   for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	   {
		for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
		{
		 if((Kind = GetKindAtom(&BAC)) != PI_ERROR)
		   AddLBACtoKindsArrays(Kind, &BAC);
		}
	   }
	  }
	  break;

	 case smSecond:
	  for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	  {
	   for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	   {
		for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
		{
		 TypeAtom = GetTypeAtom(&BAC);
		 if(TypeAtom < 4)
		  SetNoDeletedTypeAtom(&BAC);
		}
	   }
	  }
	  {
	   TMaskVec vMask;
	   DeleteLeftMaskAtoms(vMask);
	  }
	 break;
	}
	iDeletedAtom = 0;
	Finish = false;

	//Определение наиболее популярного типа атома на гладкой поверхности (для статистики)
	int nMaxCountIndex = -1;
	int nMaxCount = -1;

	for(int i=0; i < (int)KindAtoms.size(); i++)
	{
	 if (nMaxCount < (int)KindAtoms[i].size())
	 {
	  nMaxCountIndex = (int)i;
	  nMaxCount = KindAtoms[i].size();
	 }
	}
	if (nMaxCountIndex != -1)
	{
	 m_StaticticParam.m_MostPopularTypeIndex = nMaxCountIndex;
	}
}
//---------------------------------------------------------------------------
bool TKindAtoms::InitFomProb(TProbPovider &SP)
{
	bool bRet = false;
	clear();
	IBaseProbSet *pPS = SP.GetInterface();
	if(pPS != NULL)
	{
		int nCnt = pPS->GetGlobalData().GetAllNumProbality();
		resize(nCnt);
		bRet = true;
	}
	return bRet;
}
//---------------------------------------------------------------------------
/*
void TDissolutionThread::InitIdealMaskedSurface(int NewX,int NewY,
													 TMaskVec &vMask)
{
	int i;
	SurfaceMode SrfcMd = smFirst;//smSecond;//smFirst;//тип поверхности
	SizeX = NewX;
	SizeY = NewY;
	NumAtomsInLayer = SizeY * SizeX * NumAtomsInCell;
	CopacityMemoryForLayer = NumAtomsInLayer * SizeBothDtTypeDtIndex;
	OneX = NumAtomsInCell * OneN;
	OneY = OneX * SizeX;
	while(Items->Count != 0)
	{
	 if((*(int*)(Watch->Items[Watch->Count-1])) > 0) delete Items->Items[Items->Count-1];
	 delete Watch->Items[Watch->Count-1];
	 Items->Delete(Items->Count-1);
	 Watch->Delete(Watch->Count-1);
	}


	bool bRet = KindAtoms.InitFomProb(SP);
	if( bRet == false )
		return;

	iDeletedAtom = 0;

	BigArrayCoord BAC;
	unsigned char TypeAtom;
	int Kind;
	BAC.Z = 0;
	for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	{
	 for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	 {
	  for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
	  {
	   SetTypeAtom(&BAC);
	  }
	 }
	}

	switch(SrfcMd)
	{
	 case smFirst:
	  for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	  {
	   for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	   {
		for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
		{
		 if((Kind = GetKindAtom(&BAC)) != PI_ERROR)
		   AddLBACtoKindsArrays(Kind, &BAC);
		}
	   }
	  }
	  break;

	 case smSecond:
	  for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	  {
	   for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	   {
		for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
		{
		 TypeAtom = GetTypeAtom(&BAC);
		 if(TypeAtom < 4)
		  SetNoDeletedTypeAtom(&BAC);
		}
	   }
	  }
	  {
	   TMaskVec vMask;
	   DeleteLeftMaskAtoms(vMask);
	  }
	 break;
	}
	if(vMask.size() > 0)
	{
	 RenderingNewMask(vMask);
	}
	iDeletedAtom = 0;
	Finish = false;
}
*/
//---------------------------------------------------------------------------
void TDissolutionThread::RenderingNewMask(TMaskVec &vMask)
{
	DeleteLeftMaskAtoms(vMask);

	int k, dx,dy,dz;
	BigArrayCoord BAC,BAC2,*TempAtomBAC = &BAC2;
	unsigned char TypeAtom;
	bool Visib;
	double x,y;
	int i,j;
	int Kind;
	unsigned int AllLayers = DeletingLayers + DeletedLayers;
    for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
    {
     for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
     {
      for(j = 0; j < NumCollumInCell; j++)//8 столбцов в одной ячейке по сои Z
      {
       //GetCoordAtomInCell((int)BAC.N,dx,dy,dz);
       BAC.Z = 0;
       BAC.N = 90;
       switch(j*100)// самый верхний в i-том столбце
       {
#ifdef Almas100
        case 0:
         BAC.N = 1;
        break;
        case 100:
         BAC.N = 2;
        break;
        case 200:
         BAC.N = 3;
        break;
        case 300:
         BAC.N = 4;
        break;
        case 400:
         BAC.N = 5;
		break;
        case 500:
         BAC.N = 6;
        break;
        case 600:
         BAC.N = 7;
        break;
        case 700:
         BAC.N = 8;
        break;
#endif
#ifdef Almas110
        case 0:
         BAC.N = 1;
        break;
        case 100:
         BAC.N = 2;
        break;
        case 200:
         BAC.N = 3;
        break;
        case 300:
         BAC.N = 4;
        break;
        case 400:
         BAC.N = 5;
        break;
        case 500:
         BAC.N = 6;
        break;
        case 600:
         BAC.N = 7;
        break;
        case 700:
         BAC.N = 8;
        break;
#endif
#ifdef Almas111
        case 0:
         BAC.N = 1;
        break;
		case 100:
         BAC.N = 2;
        break;
        case 200:
         BAC.N = 9;
        break;
        case 300:
         BAC.N = 3;
        break;
        case 400:
         BAC.N = 10;
        break;
        case 500:
         BAC.N = 4;
        break;
        case 600:
         BAC.N = 11;
        break;
        case 700:
         BAC.N = 5;
        break;
        case 800:
         BAC.N = 6;
        break;
#endif
       }
       BAC.N--;
       //(MaskAll == true)||
       //while((!((TypeAtom == 1)||(TypeAtom == 2)||(TypeAtom == 3)))&&(BAC.Z < AllLayers))
       bool AtomMasked = false;
       while((!((AtomMasked == true)&&(MaskAll == false)))&&(BAC.Z < AllLayers))
	   {
		TypeAtom = GetTypeAtom(&BAC);
        AtomMasked = false;
        switch(TypeAtom)
        {
         case 1:
         case 2:
		 case 3:
		  Visib = IsAtomVisible(&BAC,vMask);
		  if(Visib == false)
		  {
		   //????DelLBACFromKindsArrays(TypeAtom-1, GetIndexAtom(&BAC));
		   //if((GetKindAtom(&BAC) == 46)&&(GetIndexAtom(&BAC) == 1828))
		   //{
		   // Kind = Kind;
		   //}

		   //заморозить атом
		   HoldAtom(&BAC, true);//заморозить атом 5 типом

		   /*
		   //удалить сам атом и его ближайших соседей
		   if((Kind = GetKindAtom(&BAC))!= PI_ERROR)
			DelLBACFromKindsArrays(Kind,GetIndexAtom(&BAC));
		   for(i=1; i<=4; i++)
		   {
			CopyBAC1toBAC2(&BAC, TempAtomBAC);
			AdjacentAtom(i, TempAtomBAC);//получаем координаты первичнго соседа
			if((Kind = GetKindAtom(TempAtomBAC))!= PI_ERROR)
			 DelLBACFromKindsArrays(Kind,GetIndexAtom(TempAtomBAC));
		   }
		   //собственно установить тип атома
		   SetNoDeletedTypeAtom(&BAC);
		   //исправлени связности для ближайших соседей
		   for(i=1; i<=4; i++)
		   {
			CopyBAC1toBAC2(&BAC, TempAtomBAC);
			AdjacentAtom(i, TempAtomBAC);//получаем координаты первичнго соседа
			SetTypeAtom(TempAtomBAC);
		   }
		   //добавление в сортовые массивы ближайших соседей
		   for(i=1; i<=4; i++)
		   {
			CopyBAC1toBAC2(&BAC, TempAtomBAC);
			AdjacentAtom(i, TempAtomBAC);//получаем координаты первичнго соседа
			if((Kind = GetKindAtom(TempAtomBAC))!= PI_ERROR)
			{
			 AddLBACtoKindsArrays(Kind,TempAtomBAC);
			}
		   }
		   */
		   AtomMasked = true;
		  }
          else
           Visib = true;
         break;
        }
        //переходим к следующему атому в этом столбце
        do
        {
         switch(j*100 + BAC.N + 1)//  в i-том столбце
         {
#ifdef Almas100
          case 1:
           BAC.Z++;
           BAC.N = 1;
          break;
          case 102:
           BAC.Z++;
           BAC.N = 2;
          break;
          case 203:
           BAC.Z++;
           BAC.N = 3;
          break;
          case 304:
           BAC.Z++;
           BAC.N = 4;
          break;
          case 405:
           BAC.Z++;
           BAC.N = 5;
          break;
          case 506:
           BAC.Z++;
           BAC.N = 6;
          break;
          case 607:
           BAC.Z++;
           BAC.N = 7;
          break;
          case 708:
		   BAC.Z++;
           BAC.N = 8;
          break;
#endif
#ifdef Almas110
          case 1:
           BAC.Z++;
           BAC.N = 1;
          break;
          case 102:
           BAC.Z++;
           BAC.N = 2;
          break;
          case 203:
           BAC.Z++;
           BAC.N = 3;
          break;
          case 304:
           BAC.Z++;
           BAC.N = 4;
          break;
          case 405:
           BAC.Z++;
           BAC.N = 5;
          break;
          case 506:
           BAC.Z++;
           BAC.N = 6;
          break;
          case 607:
           BAC.Z++;
           BAC.N = 7;
          break;
          case 708:
           BAC.Z++;
           BAC.N = 8;
          break;
#endif
#ifdef Almas111
          case 1:
           BAC.N = 13;
		  break;
          case 13:
           BAC.Z++;
           BAC.N = 1;
          break;
          case 102:
           BAC.N = 7;
          break;
          case 107:
           BAC.Z++;
           BAC.N = 2;
          break;
          case 209:
           BAC.N = 14;
          break;
          case 214:
           BAC.Z++;
           BAC.N = 9;
          break;
          case 303:
           BAC.N = 8;
          break;
          case 308:
           BAC.Z++;
           BAC.N = 3;
          break;
          case 410:
           BAC.N = 15;
          break;
          case 415:
           BAC.Z++;
           BAC.N = 10;
          break;
          case 504:
           BAC.N = 17;
          break;
          case 517:
           BAC.Z++;
           BAC.N = 4;
          break;
          case 611:
		   BAC.N = 16;
          break;
          case 616:
           BAC.Z++;
           BAC.N = 11;
          break;
          case 705:
           BAC.N = 18;
          break;
          case 718:
           BAC.Z++;
           BAC.N = 5;
          break;
          case 806:
           BAC.N = 12;
          break;
          case 812:
           BAC.Z++;
           BAC.N = 6;
          break;
#endif
         }
         BAC.N--;
        }
        while(NumOfAtomsInLayer[BAC.Z] == 0);
       }
      }
     }
    }
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::CalcN1N2N3(void)
{
	UINT i;
	AnsiString ProbSetIdString = SP.GetInterface()->GetGlobalData().GetProbSetIdString();

	if(ProbSetIdString != MainAtomTypeVecProbIdString)
	{
	 MainAtomTypeVec.clear();
	 _N1 = -1;
	 _N2 = -1;
	 _N3 = -1;
	 CurrDeleted = -1;
	 IBaseProbSetGlobalData &pPSGD = SP.GetInterface()->GetGlobalData();

	 UINT n = pPSGD.GetAllNumProbality();

	 MainAtomTypeVec.resize(n, 0);


	 for (i = 0; i < n; i++)
	 {
	  MainAtomTypeVec[i] = pPSGD.GetMainAtomTypeForProb(i);
	 }

	 MainAtomTypeVecProbIdString = ProbSetIdString;
	}

	if(CurrDeleted != DeletedAtom)
	{
	 _N1 = 0;
	 _N2 = 0;
	 _N3 = 0;
	 UINT n = MainAtomTypeVec.size();

	 if (n != KindAtoms.size())
	 {
	  return false;
	 }
	 int cnt;
	 for (i = 0; i < n; i++)
	 {
	  switch(MainAtomTypeVec[i])
	  {
		case 1:
		 _N1 += KindAtoms[i].size();
		break;
		case 2:
		 _N2 += KindAtoms[i].size();
		break;
		case 3:
		 _N3 += KindAtoms[i].size();
		break;
	  }
	 }
	}

	return true;
}
//---------------------------------------------------------------------------
unsigned int TDissolutionThread::GetN1(void)
{
	if(CalcN1N2N3() == false)
	{
	 return 0;
	}

	return _N1;
}
//---------------------------------------------------------------------------
unsigned int TDissolutionThread::GetN2(void)
{
	if(CalcN1N2N3() == false)
	{
	 return 0;
	}

	return _N2;
}
//---------------------------------------------------------------------------
unsigned int TDissolutionThread::GetN3(void)
{
	if(CalcN1N2N3() == false)
	{
	 return 0;
	}

	return _N3;
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::SetAlgoritm(TAlgoritm &newAlgoritm)
{
	if(newAlgoritm.m_bInitRNG == true && m_Algoritm.m_bInitRNG == false)
	{
	  m_InitRng = true;
	}
	m_Algoritm = newAlgoritm;
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::DeleteAtom(void)
{
	EnterCS();
	bool bRet = false;
	InitRNG();

	switch(m_Algoritm.m_nAlgoritmKind)
	{
	 case ALG_MONTECARLO:
	  bRet = AlgMonteCarloDeleteAtom();
	 break;
	 case ALG_POROGOVIY:
	  bRet = AlgPorogDeleteAtom();
	 break;
	 case ALG_POROG_DOLA:
	  bRet = AlgPorogDolaDeleteAtom();
	 break;
	 case ALG_DOLA_PROB:
	  bRet = AlgDolaProbDeleteAtom();
	 break;
	}
	if (m_StaticticParam.m_PeriodOfAverage > 0)
	{
	 TStaticticData sd;
	 sd.N1 = GetN1();
	 sd.N2 = GetN2();
	 sd.N3 = GetN3();
	 sd.Deleted = iDeletedAtom;
	 sd.MostPopularTypeCount = GetPopularTypeCount();
	 m_StaticticParam.AddStaticticData(sd);
	}

    LeaveCS();
	return bRet;
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::AlgPorogDolaDeleteAtom(void)
{//растворение по алгоритму пороговый дольный
    if((iDeletedAtom >= Plane) || Finish)
    {
     Finish = true;
     return false;
    }

    int i,j,k;
    int nCnt;
    int nCntDel;
    int nDel = 0;
    BigArrayCoord *pvDelAtoms = NULL;
	BigArrayCoord TempAtom;
	nCntDel=0;

	int nProbCnt = 0;
	IBaseProbSet *pPS = SP.GetInterface();
	if(pPS == NULL)
		return false;
	else
	{
	 nProbCnt = pPS->GetGlobalData().GetAllNumProbality();
	}

	for(k = 0; k < 2; k++)
	{
	 if(nCntDel > 0 && k==1)
	 {
	  pvDelAtoms = new BigArrayCoord[nCntDel];
	 }
	 nCntDel=0;
	 for(i = 0; i < nProbCnt;i++)
	 {
	  if(pPS->GetProbValue(i) >= m_Algoritm.m_dPorog)
	  {
	   nCnt = KindAtoms[i].size();
	   for(j = 0; j < nCnt; j++)
	   {
		if(pvDelAtoms!=NULL)
		{
		 CopyBAC1toBAC2(&KindAtoms[i][j], &(pvDelAtoms[nCntDel]));
		}
		nCntDel++;
	   }
	  }
	 }
	 if(nCntDel > 0 && k==1)
	 {
	  int nDola = nCntDel*m_Algoritm.m_dDola;
      int nRandIndex;

      for(j=0; j < min(nDola,nCntDel); j++)
      {
		nRandIndex = _random(nCntDel-j);
        CopyBAC1toBAC2(&(pvDelAtoms[j]), &TempAtom);
        CopyBAC1toBAC2(&(pvDelAtoms[nRandIndex+j]), &(pvDelAtoms[j]));
        CopyBAC1toBAC2(&TempAtom, &(pvDelAtoms[nRandIndex+j]));
      }
      for(j=0; j < min(nDola,nCntDel); j++)
      {
	   DeleteAtom(&(pvDelAtoms[j]));
       nDel++;
      }
	  delete [] pvDelAtoms;
	  pvDelAtoms = NULL;
     }
    }
    bool bRet = (nDel>0);;
    return bRet;
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::AlgDolaProbDeleteAtom(void)
{//растворение по алгоритму дольный наиболее веротных атомов
    if((iDeletedAtom >= Plane) || Finish)
    {
     Finish = true;
     return false;
    }

    int i,j,k;
    int nCnt;
    int nCntAllKind;
    int nCntDel;
    int nDel = 0;
    int nDola;
    int nMaxCnt=0;
    BigArrayCoord *pvDelAtoms = NULL;
    BigArrayCoord TempAtom;
    nCntDel=0;
	nCntAllKind=0;

	int nProbCnt = 0;
	IBaseProbSet *pPS = SP.GetInterface();
	if(pPS == NULL)
		return false;
	else
	{
	 nProbCnt = pPS->GetGlobalData().GetAllNumProbality();
	}


	int *SortedProb = new int[nProbCnt];

	int nTmp;
	int nRandIndex;
	int nKAS;
	//подсчет общего количесваатомов
	for(i = 0; i < nProbCnt;i++)
	{
	 nKAS = KindAtoms[i].size();
	 nCntAllKind += nKAS;
	 SortedProb[i]=i;
	 if(i==0)
	 {
	  nMaxCnt = nKAS;
	 }
	 else
	 {
	  if(nKAS > nMaxCnt)
	  {
	   nMaxCnt = nKAS;
	  }
	 }
	}
	int *pnItemIndex = new int[nMaxCnt];
	//количество атомов подлежащих удалению
	nDola = (int)floor(((double)nCntAllKind)*m_Algoritm.m_dDola + 0.5);
	if(nDola < 1)
	{
	   nDola = 1;
	}

	if(nDola > nCntAllKind)
	{
	 nDola = nCntAllKind;
	}

	//сортировка вероятностей по убыванию, начиная с самой большой
	for(i = 0; i < (nProbCnt-1);i++)
	{
	 for(j = i+1; j < nProbCnt;j++)
	 {
	  if(pPS->GetProbValue(SortedProb[i]) < pPS->GetProbValue(SortedProb[j]))
	  {
	   nTmp = SortedProb[i];
	   SortedProb[i] = SortedProb[j];
	   SortedProb[j] = nTmp;
	  }
	 }
	}

///подумать над 4 алгоритмом... вроде подумал
	for(k = 0; k < 2; k++)
	{
	 if(nCntDel > 0 && k==1)
	 {
	  pvDelAtoms = new BigArrayCoord[nCntDel];
	 }
	 nCntDel=0;
	 for(i = 0; i < nProbCnt;i++)
	 {
	  //if(SP.Probality[i] >= SP.m_dPorog)
	  {
	   nCnt = KindAtoms[SortedProb[i]].size();
	   for(j = 0; j < nCnt; j++)
	   {
		pnItemIndex[j]=j;
	   }
	   //перемешивание
	   for(j = 0; j < nCnt; j++)
	   {
		nRandIndex = _random(nCnt-j);
		nTmp = pnItemIndex[j];
		pnItemIndex[j] = pnItemIndex[nRandIndex+j];
		pnItemIndex[nRandIndex+j] = nTmp;
	   }

	   for(j = 0; (j < nCnt) && (nCntDel < nDola); j++)
	   {
		if(pvDelAtoms!=NULL)
		{
		 CopyBAC1toBAC2(&KindAtoms[SortedProb[i]][pnItemIndex[j]], &(pvDelAtoms[nCntDel]));
		}
		nCntDel++;
	   }
	  }
	 }
	 if(nCntDel > 0 && k==1)
	 {
	  for(j=0; j < nCntDel; j++)
	  {
	   DeleteAtom(&(pvDelAtoms[j]));
	   nDel++;
	  }
	  delete [] pvDelAtoms;
	  pvDelAtoms = NULL;
	 }
	}
	delete [] SortedProb;
	delete [] pnItemIndex;
	bool bRet = (nDel>0);;
	return bRet;
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::AlgPorogDeleteAtom(void)
{
	if((iDeletedAtom >= Plane) || Finish)
	{
	 Finish = true;
	 return false;
	}

	int nProbCnt = 0;
	IBaseProbSet *pPS = SP.GetInterface();
	if(pPS == NULL)
		return false;
	else
	{
	 nProbCnt = pPS->GetGlobalData().GetAllNumProbality();
	}

	int i,j,k;
	int nCnt;
	int nCntDel;
	BigArrayCoord *pvDelAtoms = NULL;
	nCntDel=0;
	for(k = 0; k < 2; k++)
	{
	 if(nCntDel > 0 && k==1)
	 {
	  pvDelAtoms = new BigArrayCoord[nCntDel];
	 }
	 nCntDel=0;
	 for(i = 0; i < nProbCnt;i++)
	 {
	  if(pPS->GetProbValue(i) >= m_Algoritm.m_dPorog)
	  {
	   nCnt = KindAtoms[i].size();
       for(j = 0; j < nCnt; j++)
       {
        if(pvDelAtoms!=NULL)
        {
		 CopyBAC1toBAC2(&KindAtoms[i][j], &(pvDelAtoms[nCntDel]));
        }
        nCntDel++;
       }
      }
     }
     if(nCntDel > 0 && k==1)
     {
      for(j = 0; j < nCntDel; j++)
      {
	   DeleteAtom(&(pvDelAtoms[j]));
	  }
	  delete [] pvDelAtoms;
	  pvDelAtoms = NULL;
	 }
	}
	bool bRet = (nCntDel > 0);
	return bRet;
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::AlgMonteCarloDeleteAtom(void)
{
	if((iDeletedAtom >= Plane) || Finish)
	{
	 Finish = true;
	 return false;
	}

	BigArrayCoord DeletingAtomBAC;
	int Kind;
	int RandNum,RandNumMax;
	double RandNumNorm, P;
	double Pn;
	int i,j;

	static clock_t clkVibor = 0;
	static clock_t clkUdalen = 0;
	clock_t clkStart;
	clkStart = clock();


	int nProbCnt = 0;
	IBaseProbSet *pPS = SP.GetInterface();
	if(pPS == NULL)
		return false;
	else
	{
	 nProbCnt = pPS->GetGlobalData().GetAllNumProbality();
	}
	SPn = SP;

	IBaseProbSet *pPSn = SPn.GetInterface();
	if(pPSn == NULL)
		return false;

	P = 0;
	int nKindSize;
	for(i=0;i<nProbCnt;i++)
	{
	 nKindSize = KindAtoms[i].size();
	 //Pn =((double)nKindSize)*pPS->GetProbValue(i);
	 Pn = pPS->GetProbValue(i);
	 Pn *= ((double)nKindSize);
	 pPSn->SetProbValue(i, Pn);
	 P += Pn;
	}

	if(P==0)
	{
	 Finish = true;
	 return false;
	}

	for(i=0;i<nProbCnt;i++)
	{
	 pPSn->SetProbValue(i, pPSn->GetProbValue(i)/P);
	}

	//выбор группы
	RandNumMax = RAND_MAX;
	RandNum = _random(RandNumMax);
	RandNumNorm = ((double)RandNum)/((double)RandNumMax);

	P = 0;
	for(i=0;i<nProbCnt;i++)
	{
	 Pn = pPSn->GetProbValue(i);
	 P += Pn;
	 if(P > RandNumNorm)
	 {
	  Kind = i;

	  break;
	 }
	}

	//выбор атома
	nKindSize = KindAtoms[Kind].size();
	RandNum = _random(nKindSize);
	//RandNum = rand()%nKindSize;

	//удаление атома
	DeletingAtomBAC = KindAtoms[Kind][RandNum];

	clkVibor += clock() - clkStart;

	clkStart = clock();

	if(GetTypeAtom(&DeletingAtomBAC) == 0)
	{
	 nKindSize = nKindSize;
	}


	bool bSucsess =
	DeleteAtom(&DeletingAtomBAC);

	clkUdalen+= clock() - clkStart;

	if (iDeletedAtom > 300) {
	 iDeletedAtom = iDeletedAtom;
	 RandNum = RandNum;
	 Pn = Pn;
	 P = P;
	 nKindSize = nKindSize;
	}

	//return true;
	return bSucsess;
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::DeleteAtom(BigArrayCoord* BAC)
{
	return DelOrHoldAtom(BAC);
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::DelOrHoldAtom(BigArrayCoord* BAC, bool bHold, bool b5Type)
{
	BigArrayCoord  TempAtomBAC3;
	BigArrayCoord* TempAtomBAC;
	BigArrayCoord* TempAtomBAC2;
	BigArrayCoord* DeletingAtomBAC = BAC;

	if(GetTypeAtom(DeletingAtomBAC) == 0)
	{
	 return false;
	}

	if(iDeletedAtom == 303)
	{
	 iDeletedAtom = iDeletedAtom;
	}

	//IBaseProbSet *pPS = SP.GetInterface();
	//if(pPS == NULL)
	//	return false;

	//int nDep = pPS->GetGlobalData().GetNumLayerAtomShema();

	int i,j,k;
	//int jj,kk;
	int TreeNeibCnt;
	int k3;
	int Kind;


	TempAtomBAC = new BigArrayCoord;
	TempAtomBAC2 = new BigArrayCoord;

	//удаление атома из сортового массива
	if((Kind = GetKindAtom(DeletingAtomBAC))!= PI_ERROR)
	 DelLBACFromKindsArrays(Kind,GetIndexAtom(DeletingAtomBAC));
	else
	{
	  //Kind = Kind; ///это странно
	}

	k3 = 0;
	TreeNeibCnt=0;
	//удаление из сортовых массивов всех первичных и вторичных соседей
	for(i=1; i<=4; i++)
	{
	 CopyBAC1toBAC2(DeletingAtomBAC, TempAtomBAC);
	 AdjacentAtom(i, TempAtomBAC);//получаем координаты первичнго соседа

	 if((Kind = GetKindAtom(TempAtomBAC))!= PI_ERROR)
	  DelLBACFromKindsArrays(Kind,GetIndexAtom(TempAtomBAC));

	 //удаление из сортовых массивов вторичных соседей
	 for(j=1; j<=4; j++)
	 {
	  CopyBAC1toBAC2(TempAtomBAC, TempAtomBAC2);
	  AdjacentAtom(j, TempAtomBAC2);//получаем координаты ближайшего соседа
	  if(*DeletingAtomBAC != *TempAtomBAC2)
	  {
	   if((Kind = GetKindAtom(TempAtomBAC2))!= PI_ERROR)
		DelLBACFromKindsArrays(Kind,GetIndexAtom(TempAtomBAC2));
	   for(k=1; k<=4; k++)
	   {
		CopyBAC1toBAC2(TempAtomBAC2, &TempAtomBAC3);
		AdjacentAtom(k, &TempAtomBAC3);//получаем координаты ближайшего соседа
		if(*TempAtomBAC != TempAtomBAC3)
		{
		 k3++;
		 if(FindTreeNeib(TempAtomBAC3, TreeNeibCnt) == -1)
		 {
		  m_vTreeNeib[TreeNeibCnt] = TempAtomBAC3;
		  TreeNeibCnt++;
		  if((Kind = GetKindAtom(&TempAtomBAC3))!= PI_ERROR)
		   DelLBACFromKindsArrays(Kind,GetIndexAtom(&TempAtomBAC3));//удаление из сортовых массивов третичных сосседей
		 }
		}
	   }
	  }
	 }
	}


	if(bHold == true)
	{
	  int TypeAtom = GetTypeAtom(DeletingAtomBAC);
	  if((TypeAtom != 0)&&(TypeAtom != 6))
	  {
	   if(b5Type == true)
	   {
		SetNoDeletedTypeAtom(DeletingAtomBAC);//заморозить 5 типом
	   }
	   else
	   {
		SetNoDeleted2TypeAtom(DeletingAtomBAC);//заморозить 6 типом
	   }
	  }
	}
	else
	{
	 //собственно удаление атома
	 SetToZeroTypeAtom(DeletingAtomBAC);
	}


	//исправлени связности для ближайших соседей
	for(i=1; i<=4; i++)
    {
	 CopyBAC1toBAC2(DeletingAtomBAC, TempAtomBAC);
     AdjacentAtom(i, TempAtomBAC);//получаем координаты первичнго соседа
	 SetTypeAtom(TempAtomBAC);
	}
	//добавление в сортовые массивы всех первичных вторичных и третичных соседей
	for(i=1; i<=4; i++)
	{
	 CopyBAC1toBAC2(DeletingAtomBAC, TempAtomBAC);
	 AdjacentAtom(i, TempAtomBAC);//получаем координаты первичнго соседа
	 if((Kind = GetKindAtom(TempAtomBAC))!= PI_ERROR)
	 {
	  AddLBACtoKindsArrays(Kind,TempAtomBAC);
	 }
	 else
	 {
	  //атом у которого только односвязные соседи тоже
	  //надо удалить т.к. он висит в воздухе
	  switch(iSecondTypeAtom)
	  {
	   case 0x00000001:
	   case 0x00000101:
	   case 0x00010101:
	   case 0x01010101:
		{
		 DeleteOneLinkAtom(TempAtomBAC);
		}
	   break;
	  }
	 }

	 for(j=1; j<=4; j++)
	 {
	  CopyBAC1toBAC2(TempAtomBAC, TempAtomBAC2);
	  AdjacentAtom(j, TempAtomBAC2);//получаем координаты вторичного соседа
	  if(*DeletingAtomBAC != *TempAtomBAC2)
	  {
	   if((Kind = GetKindAtom(TempAtomBAC2))!= PI_ERROR)
		AddLBACtoKindsArrays(Kind,TempAtomBAC2);
	   else
	   {
		//атом у которого только односвязные соседи тоже
		//надо удалить т.к. он висит в воздухе
		switch(iSecondTypeAtom)
		{
		 case 0x00000001:
		 case 0x00000101:
		 case 0x00010101:
		 case 0x01010101:
		  {
		   DeleteOneLinkAtom(TempAtomBAC2);
		  }
		 break;
		}
	   }
	   /*
	   for(k=1; k<=4; k++)
	   {
		CopyBAC1toBAC2(TempAtomBAC2, &TempAtomBAC3);
		AdjacentAtom(k, &TempAtomBAC3);//получаем координаты третичного соседа
		if(*TempAtomBAC != TempAtomBAC3)
		{
		 if((Kind = GetKindAtom(&TempAtomBAC3))!= PI_ERROR)
		  AddLBACtoKindsArrays(Kind,&TempAtomBAC3);
		 else
		 {
		  //атом у которого только односвязные соседи тоже
		  //надо удалить т.к. он висит в воздухе
		  switch(iSecondTypeAtom)
		  {
		   case 0x00000001:
		   case 0x00000101:
		   case 0x00010101:
		   case 0x01010101:
			{
			 DeleteOneLinkAtom(&TempAtomBAC3);
			}
		   break;
		  }
		 }
		}
	   }
	   */
	  }
	 }
	}

	for(k3 = 0; k3 < TreeNeibCnt; k3++)
	{
	 TempAtomBAC3 = m_vTreeNeib[k3];
	 if((Kind = GetKindAtom(&TempAtomBAC3))!= PI_ERROR)
	  AddLBACtoKindsArrays(Kind,&TempAtomBAC3);
	}

    delete TempAtomBAC;
    delete TempAtomBAC2;
    return true;
}
//---------------------------------------------------------------------------
int __fastcall TDissolutionThread::FindTreeNeib(BigArrayCoord& BAC, int MaxSize )
{// найти третьего соседа
	int i;
	for(i=0; i < MaxSize; i++)
	{
	 if(m_vTreeNeib[i]== BAC)
		return i;
	}
	return -1;
}
//---------------------------------------------------------------------------
void __fastcall	TDissolutionThread::DeleteOneLinkAtom(BigArrayCoord* BAC)
{
	/*
	BigArrayCoord NeibBAC;
	int i;
	TProbIndex Kind;
	for(i=1; i<=4; i++)
	{
	 NeibBAC = *BAC;
	 AdjacentAtom(i, &NeibBAC);//получаем координаты первичнго соседа
	 if((Kind = GetKindAtom(&NeibBAC))!= PI_ERROR)
	  DelLBACFromKindsArrays(Kind,GetIndexAtom(&NeibBAC));
	}

	SetToZeroTypeAtom(BAC);

	//исправлени связности для ближайших соседей
	for(i=1; i<=4; i++)
	{
	 NeibBAC = *BAC;
	 AdjacentAtom(i, &NeibBAC);//получаем координаты первичнго соседа
	 SetTypeAtom(&NeibBAC);
	}
	*/
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::Execute()
{
	//---- Place thread code here ----
    StartTime = StartTime.CurrentDateTime();
	//while(DeleteAtom()&& !Terminated) ;// Sleep(0);//Sleep(1);//;//
	bool bSucsess;
	do
	{
	 do
	 {
	  bSucsess = DeleteAtom();
	 }
	 while(bSucsess && !Terminated) ;// Sleep(0);//Sleep(1);//;//
     FinishTime = FinishTime.CurrentDateTime();
     if(!Terminated) Suspended = true;
    }
    while(!Terminated);
}
//---------------------------------------------------------------------------
unsigned int TDissolutionThread::GetDeletingLayers(void)
{
	int iDeletingLayers = 0;
    for(int i=0; i < Watch->Count; i++)
	 if((*(int*)(Watch->Items[i])) != 0) iDeletingLayers++;
    return iDeletingLayers;
}
//---------------------------------------------------------------------------
unsigned int TDissolutionThread::GetDeletedLayers(void)
{
	int iDeletedLayers = 0;
    for(int i=0; i < Watch->Count; i++)
	 if((*(int*)(Watch->Items[i])) == 0) iDeletedLayers++;
	return iDeletedLayers;
}
//---------------------------------------------------------------------------
unsigned int TDissolutionThread::GetNumAtomsInLayer(int Index)
{
	if(Index < Watch->Count) return (*(int*)(Watch->Items[Index]));
    else return NumAtomsInLayer;
}
//---------------------------------------------------------------------------
int __fastcall TDissolutionThread::GetMemoryCopacityForBAK(void)
{
	int Copacity,i;
    Copacity = 0;
    for(i =0; i < Watch->Count; i++)
    {
	 if((*(int*)(Watch->Items[i])) != 0)
      Copacity += CopacityMemoryForLayer;
    }
    return Copacity;
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::GetCoordAtomInCell(int N, int &dx, int &dy, int &dz)
{
     dx = CoordTable[N].dx;
     dy = CoordTable[N].dy;
     dz = CoordTable[N].dz;
}
//---------------------------------------------------------------------------
/*
int TDissolutionThread::GenerateKindAtoms(int Sort, TAtom3d** A3d)
{
    int i,j;
    int dx,dy,dz;
    *A3d = NULL;
    BigArrayCoord *BAC;
    int SortCount;
    SortCount = 0;
    for(i =0; i < AllNumProbality; i++)
    {
	 if(Sort == GetSortByKind((TProbIndex)i))
     {
      SortCount += KindAtoms[i]->Count;
     }
    }

    if(SortCount != 0)
    {
     *A3d = new TAtom3d[SortCount];
     SortCount = 0;
     for(j =0; j < AllNumProbality; j++)
     {
      if(Sort == GetSortByKind((TProbIndex)j))
      {
       for(i = 0; i < KindAtoms[j]->Count; i++)
       {
        GetTAtom3dFromBAC( &((*A3d)[SortCount]),(BigArrayCoord*)(KindAtoms[j]->Items[i]));
        SortCount++;
       }
      }
     }
    }
    return SortCount;
}
*/
//---------------------------------------------------------------------------
/*
int __fastcall TDissolutionThread::GetSortByKind(TProbIndex nKind)
{
    int Sort= -1;
    switch(nKind)
    {
     case pe2:
     case pe3:
     case pe4:
     case pe5:
      Sort = 0;
     break;
	 case pe12:
     case pe13:
     case pe14:
     case pe15:
     case pe22:
     case pe23:
     case pe24:
     case pe25:
     case pe33:
     case pe34:
     case pe35:
     case pe44:
     case pe45:
     case pe55:
      Sort = 1;
     break;
     case pe112:
     case pe113:
     case pe114:
     case pe115:
     case pe122:
     case pe123:
     case pe124:
     case pe125:
     case pe133:
     case pe134:
     case pe135:
     case pe144:
     case pe145:
     case pe155:
     case pe222:
     case pe223:
     case pe224:
     case pe225:
     case pe233:
     case pe234:
     case pe235:
     case pe244:
     case pe245:
     case pe255:
     case pe333:
     case pe334:
     case pe335:
     case pe344:
     case pe345:
     case pe355:
     case pe444:
     case pe445:
     case pe455:
     case pe555:
      Sort = 2;
     break;
    }
    return Sort;
}
*/
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::GetTAtom3dFromBAC(TAtom3d* A3d,BigArrayCoord* BAC)
{
    int dx,dy,dz;
	GetCoordAtomInCell(BAC->N, dx, dy, dz);
    A3d->Coord[0] = BAC->X*Mtr2[0][0] + BAC->Y*Mtr2[1][0] + BAC->Z*Mtr2[2][0] + dx;
    A3d->Coord[1] = BAC->X*Mtr2[0][1] + BAC->Y*Mtr2[1][1] + BAC->Z*Mtr2[2][1] + dy;
    A3d->Coord[2] = BAC->X*Mtr2[0][2] + BAC->Y*Mtr2[1][2] + BAC->Z*Mtr2[2][2] + dz;
    A3d->Type = GetTypeAtom(BAC);
	//A3d->ProbIndex = GetAdjTypeAtom(BAC);
	A3d->ProbIndex = GetKindAtom(BAC);
}
//---------------------------------------------------------------------------
void TDissolutionThread::DeleteMaskedAtoms(void)
{
    //int dx,dy,dz, AdjacentAtomType, da;
    unsigned char TmpType;
    BigArrayCoord *DeletingAtomBAC, *TempAtomBAC;
    //int Number,i,j,k;
    int i;
    DeletingAtomBAC = new BigArrayCoord;
    TempAtomBAC = new BigArrayCoord;
 	for(DeletingAtomBAC->Z = 0;
     		DeletingAtomBAC->Z < DeletingLayers+DeletedLayers;
            	DeletingAtomBAC->Z++)
    {
     if(NumOfAtomsInLayer[DeletingAtomBAC->Z] != 0)
     {
      for(DeletingAtomBAC->Y = 0;DeletingAtomBAC->Y < SizeY ;DeletingAtomBAC->Y++)
      {
       for(DeletingAtomBAC->X = 0;DeletingAtomBAC->X < SizeX ;DeletingAtomBAC->X++)
       {
        for(DeletingAtomBAC->N = 0;DeletingAtomBAC->N < NumAtomsInCell; DeletingAtomBAC->N++)
        {
         if(GetTypeAtom(DeletingAtomBAC) == 5)
         {
    	  //удаление атома
          DeleteAtom(DeletingAtomBAC);
          //SetToZeroTypeAtom(DeletingAtomBAC);
          //for(i=1; i<=4; i++)
          //{
          // CopyBAC1toBAC2(DeletingAtomBAC, TempAtomBAC);
          // AdjacentAtom(i, TempAtomBAC);//получаем координаты соседа
          // TmpType = GetTypeAtom(TempAtomBAC);// его тип
          // //если требуется удаляем его из соответствующего сортового массива
          // switch(TmpType)
          // {
          //  case 1:
          //  case 2:
          //  case 3:
          //  case 4:
		  //   if(TmpType < 4)DelLBACFromKindsArrays(TmpType-1,GetIndexAtom(TempAtomBAC));
          //   //уменьшаем его тип на 1
          //   DecTypeAtom(TempAtomBAC);
          //   TmpType--;
          //   //если требуется добавляем его в соответствующий сортовой массив
          //   if(TmpType > 0) AddLBACtoKindsArrays(TmpType-1,TempAtomBAC);
      	  //	break;
		  // }
    	  //}
         }
        }
       }
      }
     }
    }
    delete DeletingAtomBAC;
    delete TempAtomBAC;
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::DeleteLeftMaskAtoms(TMaskVec &vMask)
{
	int k, dx,dy,dz;
	BigArrayCoord BAC,TempAtomBAC;
	unsigned char TypeAtom;
	int i,TmpType;
	bool VisibNew, VisibOld;
	//TMask* Mask;
	double x,y;
	for(BAC.Z = 0;	BAC.Z < DeletingLayers+DeletedLayers; BAC.Z++)
	{
	 if(NumOfAtomsInLayer[BAC.Z] != 0)
	 {
	  for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	  {
	   for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	   {
		for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++)//BAC.N=(unsigned)(BAC.N+2)  )
		{
		 if(GetTypeAtom(&BAC) == 5)//неудаляемый
		 {
		  VisibNew = IsAtomVisible(&BAC,vMask);
		  if(VisibNew)
          {
           DeleteAtom(&BAC);
          }
         }
        }
       }
      }
     }
    }
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::IsAtomVisible(BigArrayCoord* BAC,TMaskVec &vMask)
{
    int k;
    double bx,by,bz;
    int dx,dy,dz;
    double x,y,z;
    bool Visib = true;
    GetCoordAtomInCell((int)BAC->N,dx,dy,dz);
    bx = BAC->X;
    by = BAC->Y;
    bz = BAC->Z;
    //x = (double)(bx*Mtr2[0][0] + by*Mtr2[1][0] + bz*Mtr2[2][0] + dx) - (double)(SizeX*2 + SizeY*2)/2.0;
    //y = (double)(bx*Mtr2[0][1] + by*Mtr2[1][1] + bz*Mtr2[2][1] + dy) - (double)(SizeX*2+SizeY*(-4))/2.0;
    //z = (double)(bx*Mtr2[0][2] + by*Mtr2[1][2] + bz*Mtr2[2][2] + dz) - (double)(SizeX*(-4)+SizeY*2)/2.0;
    x = (double)((bx - (double)SizeX/2.0)*Mtr2[0][0] + (by - (double)SizeY/2.0)*Mtr2[1][0] + bz*Mtr2[2][0] + dx);
    y = (double)((bx - (double)SizeX/2.0)*Mtr2[0][1] + (by - (double)SizeY/2.0)*Mtr2[1][1] + bz*Mtr2[2][1] + dy);
	z = (double)((bx - (double)SizeX/2.0)*Mtr2[0][2] + (by - (double)SizeY/2.0)*Mtr2[1][2] + bz*Mtr2[2][2] + dz);
	for(k=0; (UINT)k < vMask.size(); k++)
	{
	 TMask &Mask = vMask[k];
	 if(Mask.TypeSuperimproseMask == tsmmBoolean)
	 {
      if(Mask.LogicFunction == lfAND) Visib = Visib && (!Mask.IsIncludePoint(x, y,z));
      else if(Mask.LogicFunction == lfOR) Visib = Visib || (!Mask.IsIncludePoint(x, y,z));
           else Visib = Visib || (!Mask.IsIncludePoint(x, y, z));
     }
     else
     {
      if( Mask.IsIncludePoint(x, y, z))
      {
	   if(Mask.InsideFig == ifDeletedAtoms) Visib = true;
	   else Visib = false;
      }
     }
    }
    return Visib;
}
//---------------------------------------------------------------------------
unsigned char TDissolutionThread::GetTypeAtom(int x,int y,int z)
{
    BigArrayCoord BAC;
/*    BAC.Z = z/4;
    BAC.X = x/4;
    BAC.Y = y/4;
    x = x%4;
    y = y%4;
    z = z%4;
    switch(x*100+10*y+1*z)
    {
     case 000:
      BAC.N = 0;
     break;
     case 131:
      BAC.N = 1;
     break;
     case 220:
      BAC.N = 2;
     break;
     case 311:
      BAC.N = 3;
     break;
     case 022:
      BAC.N = 4;
     break;
     case 113:
      BAC.N = 5;
     break;
     case 202:
      BAC.N = 6;
     break;
     case 333:
      BAC.N = 7;
     break;
     default:
      BAC.N = 255;
    }
*/
    ConFromXyzToBak(x,y,z,BAC);

    return GetTypeAtom(&BAC);
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::DeleteAtom(int x,int y,int z)
{
    BigArrayCoord BAC, TempAtomBAC;
    unsigned char TypeAtom, TmpType;
    unsigned int Index, i;
    ConFromXyzToBak(x,y,z,BAC);
    return DeleteAtom(&BAC);
    /*
    TypeAtom = GetTypeAtom(&BAC);
    switch(TypeAtom)
    {
     case 0:
      return false;
     //break;
     case 1:
     case 2:
     case 3:
      Index = GetIndexAtom(&BAC);
      SetToZeroTypeAtom(&BAC);
      //SetToZeroTypeAtom(DeletingAtomBAC);
      DelLBACFromKindsArrays(TypeAtom-1, Index);
      for(i=1; i<=4; i++)
      {
       CopyBAC1toBAC2(&BAC, &TempAtomBAC);
       AdjacentAtom(i, &TempAtomBAC);//получаем координаты соседа
//       SetTypeAtom(&TempAtomBAC);
       TmpType = GetTypeAtom(&TempAtomBAC);// его тип
       //если требуется удаляем его из соответствующего сортового массива
       switch(TmpType)
       {
        case 1:
        case 2:
        case 3:
        case 4:
         if(TmpType < 4)DelLBACFromKindsArrays(TmpType-1,GetIndexAtom(&TempAtomBAC));
         //уменьшаем его тип на 1
         DecTypeAtom(&TempAtomBAC);
         TmpType--;
         //если требуется добавляем его в соответствующий сортовой массив
         if(TmpType > 0) AddLBACtoKindsArrays(TmpType-1,&TempAtomBAC);
        break;
       }
      }
     break;
     case 4:
     case 5:
     case 6:
      SetToZeroTypeAtom(&BAC);
      for(i=1; i<=4; i++)
      {
       CopyBAC1toBAC2(&BAC, &TempAtomBAC);
       AdjacentAtom(i, &TempAtomBAC);//получаем координаты соседа
       //SetTypeAtom(&TempAtomBAC);
       TmpType = GetTypeAtom(&TempAtomBAC);// его тип
       //если требуется удаляем его из соответствующего сортового массива
       switch(TmpType)
       {
        case 1:
        case 2:
        case 3:
        case 4:
         if(TmpType < 4)DelLBACFromKindsArrays(TmpType-1,GetIndexAtom(&TempAtomBAC));
         //уменьшаем его тип на 1
         DecTypeAtom(&TempAtomBAC);
         TmpType--;
         //если требуется добавляем его в соответствующий сортовой массив
         if(TmpType > 0) AddLBACtoKindsArrays(TmpType-1,&TempAtomBAC);
        break;
       }
      }
     break;
    }
    return true;
    */
}
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::ConFromXyzToBak(int x,int y,int z,BigArrayCoord &BAC)
{
    TMatrix FromSampleToOrtho;
    TMatrix FromOrthoToSample;
    int ii,jj;
    FromSampleToOrtho.EMatrix();
    FromOrthoToSample.EMatrix();
    for(ii=0;ii<3;ii++)
    {
     for(jj=0;jj<3;jj++)
     {
      FromSampleToOrtho.Item[ii][jj] = Mtr2[jj][ii];
     }
    }
    FromOrthoToSample = FromSampleToOrtho.BackMatrix332();
    TPoint3d OrthoCoord, SampleCoord;
    TPoint3d DeltaCoord;
    int i,dx,dy,dz;
    OrthoCoord.x = x;
    OrthoCoord.y = y;
    OrthoCoord.z = z;
    BAC.N = 255;
    for(i = 0; i < NumAtomsInCell; i++)
    {
     GetCoordAtomInCell(i,dx,dy,dz);
     DeltaCoord = TPoint3d(dx,dy,dz);
     SampleCoord = FromOrthoToSample * (OrthoCoord - DeltaCoord);
     BAC.X = floor(SampleCoord.x+0.5);
     BAC.Y = floor(SampleCoord.y+0.5);
     BAC.Z = floor(SampleCoord.z+0.5);
     if(
        (fabs(SampleCoord.x - BAC.X)<1e-4)&&
        (fabs(SampleCoord.y - BAC.Y)<1e-4)&&
        (fabs(SampleCoord.z - BAC.Z)<1e-4)
       )
     {
      BAC.N = i;
      break;
     }
    }
    //return;
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::HoldAtom(int x,int y,int z)
{
	BigArrayCoord BAC;
	ConFromXyzToBak(x,y,z,BAC);
	return HoldAtom(&BAC);
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::HoldAtom(BigArrayCoord* BAC, bool b5Type)
{
	return DelOrHoldAtom(BAC, true, b5Type);
/*

	unsigned char TypeAtom;
	int i;
	BigArrayCoord TempAtomBAC;
	int Kind;

	TypeAtom = GetTypeAtom(BAC);
	switch(TypeAtom)
	{
	 case 0:
	 case 6:
	  return false;
	 case 1:
	 case 2:
	 case 3:
	 case 4:
	 case 5:
	  for(i=1; i<=4; i++)
	  {
	   CopyBAC1toBAC2(BAC, &TempAtomBAC);
	   AdjacentAtom(i, &TempAtomBAC);//получаем координаты первичнго соседа
	   if((Kind = GetKindAtom(&TempAtomBAC))!= PI_ERROR)
		DelLBACFromKindsArrays(Kind,GetIndexAtom(&TempAtomBAC));
	  }
	  //изменение типа замораживаемому атому и удаление его из сортового массива
	  if((Kind = GetKindAtom(BAC))!= PI_ERROR)
	   DelLBACFromKindsArrays(Kind,GetIndexAtom(BAC));
	  if((TypeAtom != 0)&&(TypeAtom != 6))
	   SetNoDeleted2TypeAtom(BAC);
	  //добавление ближайших соседей в сортовые массивы
	  for(i=1; i<=4; i++)
	  {
	   CopyBAC1toBAC2(BAC, &TempAtomBAC);
	   AdjacentAtom(i, &TempAtomBAC);//получаем координаты первичнго соседа
	   if((Kind = GetKindAtom(&TempAtomBAC))!= PI_ERROR)
		AddLBACtoKindsArrays(Kind,&TempAtomBAC);
	  }
	 break;
    }
	return true;
*/
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::SaveToMem(TUndoDissolutionThread *UDT)
{
    if(UDT == NULL)
    {
     return false;
    }
    else
    {
     int i;
     UDT->Count = Watch->Count;
     UDT->Watch = new int[UDT->Count];
     UDT->Items = new char*[UDT->Count];
     for(i = 0; i < UDT->Count; i++)
     {
	  UDT->Watch[i] = (*(int*)(Watch->Items[i]));
      if(UDT->Watch[i] != 0)
      {
       UDT->Items[i] = new char[CopacityMemoryForLayer];
       CopyMemory(UDT->Items[i],Items->Items[i],CopacityMemoryForLayer);
      }
      else UDT->Items[i] = NULL;
	 }


	 UDT->KindAtoms = KindAtoms;
	 /*
	 for(i = 0; i < AllNumProbality; i++)
	 {
	  UDT->KindAtomsCount[i] = KindAtoms[i]->Count;
	  UDT->KindAtoms[i] = new BigArrayCoord[UDT->KindAtomsCount[i]];
	  for(int j = 0; j < UDT->KindAtomsCount[i]; j++)
	  {
	   CopyBAC1toBAC2((BigArrayCoord*)(KindAtoms[i]->Items[j]),&(UDT->KindAtoms[i][j]));
	  }
	 }
	 */
	 UDT->SizeX = SizeX;
     UDT->SizeY = SizeY;
     UDT->NumAtomsInCell = NumAtomsInCell;
     UDT->NumAtomsInLayer = NumAtomsInLayer;
     UDT->CopacityMemoryForLayer = CopacityMemoryForLayer;
	 UDT->OneX = OneX;
     UDT->OneY = OneY;
     UDT->OneN = OneN;
	 UDT->SizeDtType = SizeDtType;
	 UDT->SizeDtIndex = SizeDtIndex;
     UDT->SizeBothDtTypeDtIndex = SizeBothDtTypeDtIndex;
     UDT->iDeletedAtom = iDeletedAtom;

	 UDT->SP = SP;
	 UDT->m_Algoritm = m_Algoritm;
	 UDT->Finish = Finish;
	 UDT->Plane = Plane;
     UDT->StartTime = StartTime;
     UDT->FinishTime = FinishTime;

	 return true;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TDissolutionThread::LoadFromMem(TUndoDissolutionThread *UDT)
{
	if(UDT == NULL)
	{
	 return false;
	}
	else
	{
	 int i;

	 while(Items->Count != 0)
	 {
	  if(*((int*)(Watch->Items[Watch->Count-1])) > 0) delete Items->Items[Items->Count-1];
	  delete Watch->Items[Watch->Count-1];
	  Items->Delete(Items->Count-1);
	  Watch->Delete(Watch->Count-1);
	 }

	 Items->Clear();
	 Watch->Clear();
	 KindAtoms.clear();

	 char *pAtoms;
	 int *pInt;
	 for(i = 0; i < UDT->Count; i++)
	 {
	  if(UDT->Watch[i]>0)
	  {
	   pAtoms = new char[UDT->CopacityMemoryForLayer];
	   CopyMemory(pAtoms,UDT->Items[i],UDT->CopacityMemoryForLayer);
	  }
	  else pAtoms = NULL;
	  Items->Add(pAtoms);
	  pInt = new int;
	  *pInt = UDT->Watch[i];
	  Watch->Add(pInt);
	 }

	 KindAtoms = UDT->KindAtoms;

	 SizeX = UDT->SizeX;
	 SizeY = UDT->SizeY;
	 //NumAtomsInCell = UDT->NumAtomsInCell;
	 NumAtomsInLayer = UDT->NumAtomsInLayer;
	 CopacityMemoryForLayer = UDT->CopacityMemoryForLayer;
	 OneX = UDT->OneX;
	 OneY = UDT->OneY;
	 OneN = UDT->OneN;
	 SizeDtType = UDT->SizeDtType;
	 SizeDtIndex = UDT->SizeDtIndex;
	 SizeBothDtTypeDtIndex = UDT->SizeBothDtTypeDtIndex;
	 iDeletedAtom = UDT->iDeletedAtom;

	 SP = UDT->SP;
	 m_Algoritm = UDT->m_Algoritm;

	 Finish = UDT->Finish;
     Plane = UDT->Plane;
     StartTime = UDT->StartTime;
     FinishTime = UDT->FinishTime;
     return true;
    }
}
//---------------------------------------------------------------------------
/*
bool __fastcall TDissolutionThread::DeleteUDT(TUndoDissolutionThread *UDT)
{
	if(UDT == NULL)
	{
	 return false;
	}
	else
	{
	 int i;
	 if(UDT->Count > 0)
	 {
	  for(i = 0; i < UDT->Count; i++)
	  {
	   if(UDT->Watch[i] != 0 && UDT->Items[i] != NULL)
		delete [] UDT->Items[i];
	  }
	  delete [] UDT->Items;
	  delete [] UDT->Watch;
	  UDT->Count = 0;
	 }
	 UDT->Watch = NULL;
	 UDT->Items = NULL;

	 KindAtoms.clear();

	 delete UDT;
	 UDT = NULL;
	 return true;
	}
}
*/
//---------------------------------------------------------------------------
void __fastcall TDissolutionThread::SetNoDeleted2TypeAtom(BigArrayCoord* BAC)
{
	if(BAC->Z >= (unsigned)Items->Count) AddLayers(BAC->Z);
	if(*((int*)(Watch->Items[BAC->Z])) <= 0)
	{
     throw Exception("SetNoDeleted2TypeAtom error. Layer deleted. Access dinieded.");
    }
	DtType* Type =(DtType*)(((char*)(Items->Items[BAC->Z])) + BAC->Y*OneY + BAC->X*OneX + BAC->N*OneN);
    if(*Type == 0)
    {
     throw Exception("SetNoDeleted2TypeAtom error. Atom->Type is zero.");
    }
    (*Type) = 6;
}
//---------------------------------------------------------------------------
void TDissolutionThread::InitCube(int NewX,int NewY,int NewZ)
{
	//TMaskVec vMask;
	//InitIdealMaskedSurface(NewX,NewY,vMask);
	InitIdealSmoothSurface(NewX,NewY);
	BigArrayCoord BAC;

	for(BAC.Z = 0; BAC.Z < (unsigned int)NewZ; BAC.Z++ )
	{
	 for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	 {
	  for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	  {
	   for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
	   {
		HoldAtom(&BAC);
	   }
	  }
	 }
	}
}
//---------------------------------------------------------------------------
TProbIndex __fastcall TDissolutionThread::GetKindAtom(BigArrayCoord* BAC)
{
	int i,j;
	//SecondTypeAtom[4]
	DtType TempTp;
	BigArrayCoord AtomBAC;
	BigArrayCoord* TempAtomBAC;
	TempAtomBAC = &AtomBAC;

	TProbIndex Ret;
	Ret = PI_ERROR;
	for(i=0; i < 4; i++)
	{
	 CopyBAC1toBAC2(BAC, TempAtomBAC);
	 AdjacentAtom(i+1, TempAtomBAC);//получаем координаты первичнго соседа
	 SecondTypeAtom[i] = GetTypeAtom(TempAtomBAC);
	 if(SecondTypeAtom[i] == 6) SecondTypeAtom[i] = 5;
	}
	iSecondTypeAtom = 0;
	 for(i=0; i < 4; i++)
	  {
	   for(j=i+1; j < 4; j++)
	   {
		if(SecondTypeAtom[i] > SecondTypeAtom[j])
		{
		 TempTp = SecondTypeAtom[i];
		 SecondTypeAtom[i] = SecondTypeAtom[j];
		 SecondTypeAtom[j] = TempTp;
		}
	   }
	  }
	  j=0;
	  for(i=0; i < 4; i++)
	  {
	   j |= (0xff & SecondTypeAtom[i])<<(i*8);
	  }
	  while(((j&0xff) == 0)&&(j!=0))
	  {
	   j = j>>8;
	  }
	  iSecondTypeAtom = j;
	  //iSecondTypeAtom = j;


	IBaseProbSet *pPS = SP.GetInterface();
	if(pPS == NULL)
		return Ret;
	int nProbCnt = pPS->GetGlobalData().GetAllNumProbality();

	TAtomShema as;
	if(GetAtomShema(BAC, as, pPS) == false)
		return Ret;

	switch(GetTypeAtom(BAC))
	{
	 case 0:
	  iSecondTypeAtom = 0;
	 break;
	 case 1:
	 case 2:
	 case 3:
	  Ret = pPS->GetGlobalData().GetProbIndexFromAtomShema(as);
	  if (Ret >= nProbCnt)
	  {
	   Ret = PI_ERROR;
	  }
	  //Ret = SP.IndexOf(j);
	  //if((Ret != PI_ERROR)&&(GetTypeAtom(BAC) != GetSortByKind(Ret)+1))
	  // Ret = PI_ERROR;
	 break;
	}
	return Ret;
}
//---------------------------------------------------------------------------
bool TDissolutionThread::GetAtomShema(BigArrayCoord *pBAC, TAtomShema &as, IBaseProbSet *pPS)
{
	bool bRet = false;
	int i,j, jj, k, kk;
	BigArrayCoord BAC1LevAdj;
	BigArrayCoord BAC2LevAdj;
	BigArrayCoord BAC3LevAdj;

	bool bNoDelAtomsFourLinks = (m_Algoritm.m_nNoDelAtomsBehaviour == BHV_AS_FOUR_LINKS);

	bool Atom1NoDel;
	bool Atom2NoDel;

	as.m_nMaxLayer = pPS->GetGlobalData().GetNumLayerAtomShema();
	unsigned char nAtomType;
	nAtomType = GetTypeAtom(pBAC);
	as.SetBit(GetIndex0LevAdj(), nAtomType?1:0);
	if(as.m_nMaxLayer>0)
	{
	 for(i=0; i < 4; i++)
	 {
	  CopyBAC1toBAC2(pBAC, &BAC1LevAdj);
	  AdjacentAtom(i+1, &BAC1LevAdj);//получаем координаты первичнго соседа
	  nAtomType = GetTypeAtom(&BAC1LevAdj);
	  Atom1NoDel = false;
	  if(nAtomType == 5 || nAtomType == 6)
	   Atom1NoDel = true;
	  as.SetBit(GetIndex1LevAdj(i), nAtomType?1:0);
	  if(as.m_nMaxLayer>1)
	  {
	   jj = 0;
	   for(j=0; j < 4; j++)
	   {
		CopyBAC1toBAC2(&BAC1LevAdj, &BAC2LevAdj);
		AdjacentAtom(j+1, &BAC2LevAdj);//получаем координаты первичнго соседа
		if(BAC2LevAdj != *pBAC)
		{
		 nAtomType = GetTypeAtom(&BAC2LevAdj);
		 Atom2NoDel = false;
		 if(nAtomType == 5 || nAtomType == 6)
		  Atom2NoDel = true;
		 as.SetBit(GetIndex2LevAdj(i,jj), (nAtomType||(Atom1NoDel&&bNoDelAtomsFourLinks))?1:0);
		 if(as.m_nMaxLayer>2)
		 {
		  kk=0;
		  for(k=0; k < 4; k++)
		  {
		   CopyBAC1toBAC2(&BAC2LevAdj, &BAC3LevAdj);
		   AdjacentAtom(k+1, &BAC3LevAdj);//получаем координаты первичнго соседа
		   if(BAC3LevAdj != BAC1LevAdj)
		   {
			nAtomType = GetTypeAtom(&BAC3LevAdj);
			as.SetBit(GetIndex3LevAdj(i, jj, kk), (nAtomType||(Atom2NoDel&&bNoDelAtomsFourLinks))?1:0);
			if(as.m_nMaxLayer>3)
			{
			 //дальше не реализовано
			}
			kk++;
		   }
		  }
		 }
		 jj++;
		}
	   }
	  }
	 }
	}
	AnsiString strTmp = as.ToStr2();

	bRet = true;
	return bRet;
}
//---------------------------------------------------------------------------
/*
int TDissolutionThread::Get4LnksAtoms(TAtom3d** A3d)
{
	BigArrayCoord BAC;
	int Number,i;
	int dx,dy,dz;
	int Type;
	TProbIndex nKind;

	for(i=0; i<2; i++)
	{
     Number = 0;
     for(BAC.Z = 0; BAC.Z < (DeletingLayers+DeletedLayers); BAC.Z++)
     {
      if(NumOfAtomsInLayer[BAC.Z] != 0)
      {
       for(BAC.Y=0; BAC.Y < SizeY; BAC.Y++)
       {
        for(BAC.X=0; BAC.X < SizeX; BAC.X++)
        {
         for(BAC.N=0; BAC.N < NumAtomsInCell; BAC.N++)
         {
          Type = GetTypeAtom(&BAC);
          if(Type == 4)
          {
		   nKind = GetKindAtom(&BAC);
           if((nKind == PI_ERROR)&&(iSecondTypeAtom !=0x04040404))
           {
            Number++;
            if(i!=0)
            {
  	         GetCoordAtomInCell(BAC.N, dx, dy, dz);
             ((TAtom3d*)(*A3d+Number-1))->Coord[0] = BAC.X*Mtr2[0][0] + BAC.Y*Mtr2[1][0] + BAC.Z*Mtr2[2][0] + dx;
             ((TAtom3d*)(*A3d+Number-1))->Coord[1] = BAC.X*Mtr2[0][1] + BAC.Y*Mtr2[1][1] + BAC.Z*Mtr2[2][1] + dy;
             ((TAtom3d*)(*A3d+Number-1))->Coord[2] = BAC.X*Mtr2[0][2] + BAC.Y*Mtr2[1][2] + BAC.Z*Mtr2[2][2] + dz;
             ((TAtom3d*)(*A3d+Number-1))->Type = GetTypeAtom(&BAC);// его тип
            }
           }
          }
         }
        }
       }
      }
     }
     if(i==0)
     {
      if(Number != 0)
       *A3d = new TAtom3d[Number];
      else
       *A3d = NULL;
     }
    }

    return Number;
}
*/
//---------------------------------------------------------------------------
void TDissolutionThread::GenerateSurface(TSurface &Surf)
{
    int i,j,k,l;
    BigArrayCoord BAC;
    //своя система координат
    //i - целое число (X в своей системе)
    //j - целое число (Y в своей системе)
    //M[i,j] - вещественное число (Z в своей системе)
    //(вектор)i = (вектор) семпловый X / NumSemplsX
    //(вектор)j = (вектор) семпловый Y / NumSemplsY
    //вектор Z в своей системе = направлен как семпловый Z,
    //но единица длины как длина в глобальных координатах
    Surf.iOrt.x = Mtr2[0][0]/NumSemplsX;
    Surf.iOrt.y = Mtr2[0][1]/NumSemplsX;
    Surf.iOrt.z = Mtr2[0][2]/NumSemplsX;
    Surf.jOrt.x = Mtr2[1][0]/NumSemplsY;
    Surf.jOrt.y = Mtr2[1][1]/NumSemplsY;
    Surf.jOrt.z = Mtr2[1][2]/NumSemplsY;
    Surf.kOrt.x = Mtr2[2][0];
    Surf.kOrt.y = Mtr2[2][1];
    Surf.kOrt.z = Mtr2[2][2];
	Surf.kOrt = Surf.kOrt.Normirate();
    //преобразование из своей системы в глобальную  (г - глобальная система координат , с - своя)
    // [ Xг ]   [iOrt.x jOrt.x kOrt.x] [ Xс ]
    // [ Yг ] = [iOrt.y jOrt.y kOrt.y]*[ Yс ]
    // [ Zг ]   [iOrt.z jOrt.z kOrt.z] [ Zс ]
    //обратное - кажись неправильно
    // [ Xс ]   [iOrt.x iOrt.y iOrt.z] [ Xг ]
    // [ Yс ] = [jOrt.x jOrt.y jOrt.z]*[ Yг ]
    // [ Zс ]   [kOrt.x kOrt.y kOrt.z] [ Zг ]
    Surf.FromBaseToOrtho.EMatrix();
    for(i=0; i < 3; i++)
    {
        Surf.FromBaseToOrtho.Item[i][0] = Surf.iOrt.Coord[i];
        Surf.FromBaseToOrtho.Item[i][1] = Surf.jOrt.Coord[i];
        Surf.FromBaseToOrtho.Item[i][2] = Surf.kOrt.Coord[i];
    }
    Surf.FromOrthoToBase = Surf.FromBaseToOrtho.BackMatrix332();
    TMatrix CheckMtr = Surf.FromOrthoToBase * Surf.FromBaseToOrtho;
    TMatrix CheckMtr2 = Surf.FromBaseToOrtho * Surf.FromOrthoToBase;

    Surf.SetSize(SizeX*NumSemplsX, SizeY*NumSemplsY);
    TAtom3d A3d;
    TPoint3d OrthoPoint, BasePoint;

    OrthoPoint = Point3d(1,1,-1);
    BasePoint = Surf.FromOrthoToBase * OrthoPoint;

    TSurfVal Dist;
    for(BAC.Z = DeletedLayers; BAC.Z < (DeletedLayers+DeletingLayers); BAC.Z++)
    {
     for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++)
     {
      for(BAC.X = 0; BAC.X < SizeX; BAC.X++)
      {
       for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++)
       {
        GetTAtom3dFromBAC(&A3d,&BAC);
        if((A3d.Type != 0) && (A3d.Type != 4))//если атом не удалён и не четырёхсвязный
		{
         OrthoPoint = TPoint3d(A3d.Coord[0],A3d.Coord[1],A3d.Coord[2]);
         BasePoint = Surf.FromOrthoToBase * OrthoPoint;
         Surf.FromCoordToIndex(BasePoint, i,j,Dist);
         if(i==33 && j==79)
             i=i;

         if(Surf.Array2D[i][j] == INIT_VAL)//если значение ещё не присвоено
         {
          if(abs(Dist) > 1e100)
           Dist = Dist;
          if(abs(Dist) < 1e-100)
           Dist = Dist;
          Surf.Array2D[i][j] = Dist;
         }
        }
       }
      }
     }
    }
    int nRadius;
    int nFixCnt;
    int nInitValCnt = 1;
    int nDxP,nDxM,nDyP,nDyM;
    TSurfVal svDxP,svDxM,svDyP,svDyM;
    TSurfVal svX, svY;
    TSurfVal svAverage;

    for(nRadius = 1; nRadius < max(Surf.SizeY, Surf.SizeX); nRadius++)
    {
     do
     {
      nInitValCnt=0;
      nFixCnt = 0;
      for(i = 0; i < Surf.SizeX; i++)
      {
       for(j = 0; j < Surf.SizeY; j++)
       {
		if(Surf.Array2D[i][j] == INIT_VAL)
        {
         nInitValCnt++;
         svDxP = INIT_VAL;
         svDxM = INIT_VAL;
         svDyP = INIT_VAL;
         svDyM = INIT_VAL;
         for(nDxP=1; nDxP < nRadius && nDxP < Surf.SizeX; nDxP++)
         {
          svDxP = Surf.Array2D[(i+nDxP+Surf.SizeX)%Surf.SizeX][j];
          if(svDxP != INIT_VAL)
            break;
         }

         for(nDxM=1; nDxM < nRadius && nDxM < Surf.SizeX; nDxM++)
         {
          svDxM = Surf.Array2D[(i-nDxM+Surf.SizeX)%Surf.SizeX][j];
          if(svDxM != INIT_VAL)
            break;
         }


         for(nDyP=1; nDyP < nRadius && nDyP < Surf.SizeY; nDyP++)
         {
          svDyP = Surf.Array2D[i][(j+nDyP+Surf.SizeY)%Surf.SizeY];
          if(svDyP != INIT_VAL)
            break;
         }

         for(nDyM=1; nDyM < nRadius && nDyM < Surf.SizeY; nDyM++)
         {
          svDyM = Surf.Array2D[i][(j-nDyM+Surf.SizeY)%Surf.SizeY];
          if(svDyM != INIT_VAL)
            break;
         }

         //среднее значение по X
         svX = INIT_VAL;
		 if(svDxP != INIT_VAL && svDxM != INIT_VAL)
         {
          svX = (svDxM-svDxP)*nDxP/((TSurfVal)(nDxP+nDxM))+svDxP;
         }

         //среднее значение по Y
         svY = INIT_VAL;
         if(svDyP != INIT_VAL && svDyM != INIT_VAL)
         {
          svY = (svDyM-svDyP)*nDyP/((TSurfVal)(nDyP+nDyM))+svDyP;
         }
         svAverage = svX;
         if(svY != INIT_VAL)
         {
            if(svAverage != INIT_VAL)
            {
             svAverage = (svAverage+svY)/2.0;
            }
            else
            {
             svAverage = svY;
            }
         }

         if(svAverage != INIT_VAL)
         {
          Surf.Array2D[i][j] = svAverage;
          nFixCnt++;
          svY = Surf.Array2D[i][j];
          svX = Surf.Array2D[i][j];
         }
        }
       }
      }
     }
     while(nFixCnt > 0);

     if(nInitValCnt == 0)
		break;
    }
    svAverage *=svAverage;

    bool ValPresent;
    TSurfVal Val1,Val2;
/*
    //усреднение по иксам
    for(j = 0; j < Surf.SizeY; j++)
    {
     ValPresent = false;
     for(i = 0; i < Surf.SizeX; i++)
     {
      if(Surf.Array2D[i][j] != INIT_VAL)
      {
       ValPresent = true;
       break;
      }
     }
     if(ValPresent == true)
     {
      for(i = 0; i < Surf.SizeX; i++)
      {
       if(Surf.Array2D[i][j] == INIT_VAL)
       {
        k=1;
        while(Surf.Array2D[(i+k)%Surf.SizeX][j] == INIT_VAL)
         k++;
        l=1;
        while(Surf.Array2D[(Surf.SizeX+i-l)%Surf.SizeX][j] == INIT_VAL)
         l++;
        Val1 = Surf.Array2D[(Surf.SizeX+i-l)%Surf.SizeX][j];
        Val2 = Surf.Array2D[(i+k)%Surf.SizeX][j];
        Surf.Array2D[i][j] = (Val2-Val1)/(k+l)*l + Val1;
       }
      }
     }
    }

    //усреднение по игрикам
    for(i = 0; i < Surf.SizeX; i++)
    {
     ValPresent = false;
     {
      for(j = 0; j < Surf.SizeY; j++)
      {
       ValPresent = true;
       break;
      }
     }
     if(ValPresent == true)
     {
      for(j = 0; j < Surf.SizeY; j++)
      {
       if(Surf.Array2D[i][j] == INIT_VAL)
       {
        k=1;
        while(Surf.Array2D[i][(j+k)%Surf.SizeY] == INIT_VAL)
         k++;
        l=1;
        while(Surf.Array2D[i][(Surf.SizeY+j-l)%Surf.SizeY] == INIT_VAL)
         l++;
        Val1 = Surf.Array2D[i][(Surf.SizeY+j-l)%Surf.SizeY];
        Val2 = Surf.Array2D[i][(j+k)%Surf.SizeY];
        Surf.Array2D[i][j] = (Val2-Val1)/(k+l)*l + Val1;
       }
      }
     }
    }

    //пока не будем.

*/
    //Минимум и максимум
    Surf.MinVal = 0;
    Surf.MaxVal = 0;
	if(Surf.SizeY*Surf.SizeX > 0)
    {
     Surf.MinVal = Surf.Array2D[0][0];
     Surf.MaxVal = Surf.Array2D[0][0];
    }

    for(j = 0; j < Surf.SizeY; j++)
    {
     for(i = 0; i < Surf.SizeX; i++)
     {
      Val1 = Surf.Array2D[i][j];
      if(Val1 > Surf.MaxVal)
      {
       Surf.MaxVal = Val1;
      }
      if(Val1 < Surf.MinVal)
      {
       Surf.MinVal = Val1;
      }
     }
    }
    if(Surf.MinVal == Surf.MaxVal)
    {
     Surf.MaxVal = Surf.MinVal + 1;
    }
}
//---------------------------------------------------------------------------
bool TSurface::FromCoordToIndex(TPoint3d Coord, int &i, int &j, TSurfVal &z)
{
    TSurfVal Pressigion = 1.0e-4;//точность
    TSurfVal Val;
    bool Ret = true;

    Val = Coord.x;
    if(abs(Val -  floor(Val +0.5)) > Pressigion)
     Ret = false;
    Val = Coord.y;
    if(abs(Val -  floor(Val +0.5)) > Pressigion)
	 Ret = false;

    if(Ret == false)
     throw Exception("Плохая точность");

    i = floor(Coord.x +0.5);
    j = floor(Coord.y +0.5);
    z = Coord.z;
    return Ret;
}

void TSurface::SetSize(int X, int Y)
{
    SizeX = X;
    SizeY = Y;
    Array2D.clear();
    int i,j;
    TSurfVal InitialVal = INIT_VAL;
    TValVector Values;
    for(j = 0; j < SizeY; j++)
        Values.push_back(InitialVal);
    //int sss = Values.size();
    for(i = 0; i < SizeX; i++)
        Array2D.push_back(Values);
    //sss = Array2D.size();
    //sss = Array2D[5].size();
}
//---------------------------------------------------------------------------
TSurfVal& TSurface::GetVal(int i, int j)
{
    if(
        ((!(i<SizeX))&&(i < 0))
      &&((!(j<SizeY))&&(j < 0))
      )
     throw Exception("Выход за пределы массива");
    return Array2D[i][j];
}
//---------------------------------------------------------------------------
TSurfVal TSurface::Distance(TPoint3d APoint, TPoint3d NormVector, TSurfVal D)
{
    TSurfVal Module, Dist;
    Module = sqrt(  pow((float)NormVector.x, (float)2.0)
                  + pow((float)NormVector.y, (float)2.0)
                  + pow((float)NormVector.z, (float)2.0)
                 );
    NormVector.x /= Module;
    NormVector.y /= Module;
    NormVector.z /= Module;
    Dist =   NormVector.x*APoint.x
           + NormVector.x*APoint.x
           + NormVector.x*APoint.x;
    return Dist;
}
//---------------------------------------------------------------------------
void TSurface::SortValVector(TValVector &SV)
{
    std::sort(SV.begin(), SV.end());
}
//---------------------------------------------------------------------------
int __fastcall TDissolutionThread::GetAdjTypeAtom(BigArrayCoord* BAC)
{//получить типы соседних атомов
    int ProbIndex = 0;

    BigArrayCoord AdjBAC;


    int i;
    DtType TempTp;
    BigArrayCoord AtomBAC;
    //BigArrayCoord* TempAtomBAC;
    //TempAtomBAC = &AtomBAC;
    unsigned char Type;

    for(i=0; i < 4; i++)
    {
     CopyBAC1toBAC2(BAC, &AdjBAC);
	 AdjacentAtom(i+1, &AdjBAC);//получаем координаты первичнго соседа
     Type = GetTypeAtom(&AdjBAC);
     if(Type == 6) Type = 5;
     ProbIndex |= (0xff & Type)<<(i*8);
    }
    return ProbIndex;
}
//---------------------------------------------------------------------------
int TDissolutionThread::GetCubeAtoms(TAtom3d** A3d, int CubeZ)
{
    BigArrayCoord BAC;
    int Number,i;
    int dx,dy,dz;
    int Type;
	TProbIndex nKind;
    bool bAllAtoms = false;
    int MaxZ = DeletingLayers + DeletedLayers+1;
    if(CubeZ > 0)
    {
        //MaxZ = min(MaxZ, CubeZ);
        MaxZ = CubeZ;
        bAllAtoms = true;
    }

 	for(i=0; i<2; i++)
    {
     Number = 0;
     for(BAC.Z = 0; (signed)BAC.Z < MaxZ ; BAC.Z++)
     {
      if(NumOfAtomsInLayer[BAC.Z] != 0)
      {
       for(BAC.Y=0; BAC.Y < SizeY; BAC.Y++)
       {
        for(BAC.X=0; BAC.X < SizeX; BAC.X++)
        {
         for(BAC.N=0; BAC.N < NumAtomsInCell; BAC.N++)
		 {
          Type = GetTypeAtom(&BAC);
		  nKind = GetKindAtom(&BAC);
          if(
             //все атомы кроме четерёхсвязных
             ((Type != 0)&&(Type != 4))
             //четырёхсвязные (предповерхностные и внутренние)
		  || ((Type == 4)&&(nKind == PI_ERROR)&&((iSecondTypeAtom !=0x04040404)||(bAllAtoms==true)))
            )
          {
           if(i!=0)
           {
            GetTAtom3dFromBAC( &((*A3d)[Number]),&BAC);
           }
           Number++;
          }
         }
        }
       }
      }
     }
     if(i==0)
     {
      if(Number != 0)
       *A3d = new TAtom3d[Number];
      else
       *A3d = NULL;
     }
    }

    return Number;
}
//---------------------------------------------------------------------------
int TDissolutionThread::GetLinksFromCubeAtoms(TAtom3d** A3dBegin, TAtom3d** A3dEnd, int CubeZ)
{
	TProbIndex nKind;
    int dx,dy,dz, AdjacentAtomType, da;
    BigArrayCoord BAC,BACAdjacentAtom;
    TAtom3d *BeginLink, *EndLink;
    int Number,i,j,I,J,K;
	bool Kraevoi;
    //bool UpLink4;
    int Type;
    *A3dBegin = NULL;
    *A3dEnd = NULL;
    bool bAllAtoms = false;

    int MaxZ = DeletingLayers + DeletedLayers+1;
    if(CubeZ > 0)
    {
        //MaxZ = min(MaxZ, CubeZ);
        MaxZ = CubeZ;
        bAllAtoms = true;
    }

 	for(i=0; i<2; i++)
    {
     Number = 0;
     for(BAC.Z=0; BAC.Z < (unsigned)MaxZ; BAC.Z++)
     {
      if(NumOfAtomsInLayer[BAC.Z] != 0)
      {
       for(BAC.Y=0; BAC.Y < SizeY; BAC.Y++)
       {
        for(BAC.X=0; BAC.X < SizeX; BAC.X++)
        {
         for(BAC.N=0; BAC.N < NumAtomsInCell; BAC.N++)
         {
          Type = GetTypeAtom(&BAC);
          nKind = GetKindAtom(&BAC);
          if(
             //все атомы кроме четерёхсвязных
             ((Type != 0)&&(Type != 4))
             //четырёхсвязные (предповерхностные и внутренние)
          || ((Type == 4)&&(nKind == PI_ERROR)&&((iSecondTypeAtom !=0x04040404)||(bAllAtoms==true)))
            )
          {
 	       for(j=1; j<=4; j++)
		   {
            CopyBAC1toBAC2(&BAC, &BACAdjacentAtom);
            AdjacentAtom(j, &BACAdjacentAtom);//получаем координаты j-ого соседа
            AdjacentAtomType = GetTypeAtom(&BACAdjacentAtom);
            Kraevoi = false;
            I = (signed)(BAC.X + LinksTable[BAC.N][j-1].di);
            J = (signed)(BAC.Y + LinksTable[BAC.N][j-1].dj);
            K = (signed)(BAC.Z + LinksTable[BAC.N][j-1].dk);
            if((I<0)||(I>=SizeX)) Kraevoi = true;
            if((J<0)||(J>=SizeY)) Kraevoi = true;
            if(K<0) Kraevoi = true;
            if(
               ((AdjacentAtomType == 0)||(AdjacentAtomType == 4))||
               ((j == 1))||
               ((j == 2))||
               (Kraevoi)
              )
            {
             if(i!=0)
             {
    	      GetCoordAtomInCell(BAC.N, dx, dy, dz);
              BeginLink = *A3dBegin;
              EndLink = *A3dEnd;
              I = (signed)(BAC.X);
              J = (signed)(BAC.Y);
              K = (signed)(BAC.Z);
              ((TAtom3d*)(BeginLink+Number))->Coord[0] = I*Mtr2[0][0] + J*Mtr2[1][0] + K*Mtr2[2][0] + dx;
              ((TAtom3d*)(BeginLink+Number))->Coord[1] = I*Mtr2[0][1] + J*Mtr2[1][1] + K*Mtr2[2][1] + dy;
              ((TAtom3d*)(BeginLink+Number))->Coord[2] = I*Mtr2[0][2] + J*Mtr2[1][2] + K*Mtr2[2][2] + dz;
              ((TAtom3d*)(BeginLink+Number))->Type = GetTypeAtom(&BAC);// его тип
    	      BACAdjacentAtom.X = BAC.X + LinksTable[BAC.N][j-1].di;
	          BACAdjacentAtom.Y = BAC.Y + LinksTable[BAC.N][j-1].dj;
	          BACAdjacentAtom.Z = BAC.Z + LinksTable[BAC.N][j-1].dk;
	          BACAdjacentAtom.N  = LinksTable[BAC.N][j-1].N-1;
	          GetCoordAtomInCell(BACAdjacentAtom.N, dx, dy, dz);
              I = (signed)(BAC.X + LinksTable[BAC.N][j-1].di);
              J = (signed)(BAC.Y + LinksTable[BAC.N][j-1].dj);
              K = (signed)(BAC.Z + LinksTable[BAC.N][j-1].dk);
			  ((TAtom3d*)(EndLink+Number))->Coord[0] = I*Mtr2[0][0] + J*Mtr2[1][0] + K*Mtr2[2][0] + dx;
              ((TAtom3d*)(EndLink+Number))->Coord[1] = I*Mtr2[0][1] + J*Mtr2[1][1] + K*Mtr2[2][1] + dy;
              ((TAtom3d*)(EndLink+Number))->Coord[2] = I*Mtr2[0][2] + J*Mtr2[1][2] + K*Mtr2[2][2] + dz;
        	  ((TAtom3d*)(*A3dEnd+Number))->Type = (unsigned char)AdjacentAtomType;// его тип
             }
             Number++;
            }
           }
          }
         }
        }
       }
      }
     }
     if(i==0)
     {
      *A3dBegin = new TAtom3d[Number];
      *A3dEnd = new TAtom3d[Number];
     }
    }
    return Number;
}
//---------------------------------------------------------------------------
int TDissolutionThread::GetSubLayer(int N)
{//получения индекса атомного подслоя для атома ячейки под номером N
	return CoordTable[N].SubLayer;
}
//---------------------------------------------------------------------------
void TDissolutionThread::GenAtomCntInLayer(TAtomCntInLayerVector& vec)
{
	TProbIndex nKind;
    int Type;
    int dx,dy,dz, AdjacentAtomType, da;
    BigArrayCoord BAC,BACAdjacentAtom;
	int Number,i,j,I,J,K;

	vec.clear();

	int nProbCnt = 0;
	IBaseProbSet *pPS = SP.GetInterface();
	if(pPS == NULL)
		return;
	else
	{
	 nProbCnt = pPS->GetGlobalData().GetAllNumProbality();
	}


	int MaxZ = DeletingLayers + DeletedLayers;

	AnsiString strIdString;
	strIdString = pPS->GetGlobalData().GetProbSetIdString();
	TAtomCntInLayer Rec(strIdString);
	Rec.m_vnSortAttom = SP;
	Rec.m_SubLayers.resize(Num1AtomLayerInCell, TAtomCntInSubLayer(strIdString));
	IBaseProbSet *pRecPS = Rec.m_vnSortAttom.GetInterface();
	int nAllAtom = SizeY*SizeX*NumAtomsInCell;
	int nSubLayerIndex;
	int nSubAllAtom[Num1AtomLayerInCell];

	for(i=0; i<Num1AtomLayerInCell; i++)
	{
	 nSubAllAtom[i] = 0;
	}
	for(i=0; i<NumAtomsInCell; i++)
	{
	 nSubLayerIndex = GetSubLayer(i);
	 if(nSubLayerIndex<Num1AtomLayerInCell)
		 nSubAllAtom[nSubLayerIndex]+= SizeY*SizeX;
	 else
	 {//ошибка
		nSubLayerIndex = nSubLayerIndex;
	 }
	}

	for(BAC.Z=0; BAC.Z < (unsigned)MaxZ; BAC.Z++)
	{
	 Rec.Zero();
	 Rec.m_nAllAtom = nAllAtom;
	 Rec.m_nLayer = BAC.Z;
	 //обновить значения AllAtom
	 for(i=0; i<Num1AtomLayerInCell; i++)
	 {
	  Rec.m_SubLayers[i].m_nAllAtom = nSubAllAtom[i];
	  Rec.m_SubLayers[i].m_nLayer = i;
	 }

	 if(NumOfAtomsInLayer[BAC.Z] != 0)
	 {
	  for(BAC.Y=0; BAC.Y < SizeY; BAC.Y++)
	  {
	   for(BAC.X=0; BAC.X < SizeX; BAC.X++)
	   {

		for(BAC.N=0; BAC.N < NumAtomsInCell; BAC.N++)
		{
		 Type = GetTypeAtom(&BAC);
		 nKind = GetKindAtom(&BAC);

		 nSubLayerIndex = GetSubLayer(BAC.N);

		 TAtomCntInSubLayer &CurrSubLayer = Rec.m_SubLayers[nSubLayerIndex];

		 if(nKind == PI_ERROR)
		 {
		  switch(Type)
		  {
		   case 0:
			Rec.m_nDelAtom++;
			CurrSubLayer.m_nDelAtom++;
		   break;
		   case 4:
			Rec.m_nFourLinkAtom++;
			CurrSubLayer.m_nFourLinkAtom++;
		   break;
		   case 5:
		   case 6:
			Rec.m_nNoDelAtom++;
			CurrSubLayer.m_nNoDelAtom++;
		   break;
		   default://что-то невообразимое
			Rec.m_nNoDelAtom = Rec.m_nNoDelAtom;
		  }
		 }
		 else
		 {
		  if(nKind > nProbCnt)
		  {
			Rec.m_nNoDelAtom = Rec.m_nNoDelAtom;
		  }
		  pRecPS->SetProbValue(nKind, pRecPS->GetProbValue(nKind)+1);

		  IBaseProbSet *pRecSLPS = CurrSubLayer.m_vnSortAttom.GetInterface();
		  pRecSLPS->SetProbValue(nKind, pRecSLPS->GetProbValue(nKind)+1);
		  //Rec.m_vnSortAttom [nKind]++;
		 }
		}
	   }
	  }
	 }
	 else
	 {
	  Rec.m_nDelAtom = NumAtomsInLayer;
	  for(i=0; i<Num1AtomLayerInCell; i++)
	  {
	   Rec.m_SubLayers[i].m_nDelAtom = nSubAllAtom[i];
	  }
	 }
	 vec.push_back(Rec);
	}
}
//---------------------------------------------------------------------------
void TDissolutionThread::EnterCS(void)
{
	EnterCriticalSection(&m_CS);
}
//---------------------------------------------------------------------------
void TDissolutionThread::LeaveCS(void)
{
	LeaveCriticalSection(&m_CS);
}
//---------------------------------------------------------------------------
bool TKindAtoms::SaveToFile(HANDLE hFile, int *pSeek)
{//сохранить структуру в поток
	bool bRet;
	int nSeek = 0;
	DWORD NumberOfBytesToWrite, NumberOfBytesWritten;
	bool bwf = true;
	int i,j;

	   int nProbCnt = size();

	   NumberOfBytesToWrite = sizeof(nProbCnt);
	   bwf &= WriteFile(hFile,&(nProbCnt),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek += (bwf)?NumberOfBytesWritten:0;

	   if(nProbCnt > 0)
	   {
		for(i = 0; i < nProbCnt; i++)
		{
		 int nKindAtomsCount = (*this)[i].size();

		 NumberOfBytesToWrite = sizeof(nKindAtomsCount);
		 bwf &= WriteFile(hFile,&(nKindAtomsCount),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
		 nSeek += (bwf)?NumberOfBytesWritten:0;

		 NumberOfBytesToWrite = sizeof(BigArrayCoord);
		 for(j = 0; j < nKindAtomsCount; j++)
		 {
		  bwf &= WriteFile(hFile, &((*this)[i][j]),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
		  nSeek+= (bwf)?NumberOfBytesWritten:0;
		 }
		}
	   }


	if(pSeek != NULL)
	{
	 *pSeek += nSeek;
	}
	bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
bool TKindAtoms::LoadFromFile(HANDLE hFile, int *pSeek)
{//загрузить структуру из потока
	bool bRet;
	int nSeek = 0;
	DWORD NumberOfBytesRead,NumberOfBytesReaded;
	int i,j;
	bool bwf = true;

	clear();

	   int nProbCnt = 0;

	   NumberOfBytesRead = sizeof(nProbCnt);
	   bwf &= ReadFile(hFile,&(nProbCnt),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
	   nSeek += (bwf)?NumberOfBytesReaded:0;

	   if(nProbCnt > 0)
	   {
		resize(nProbCnt);
		for(i = 0; i < nProbCnt; i++)
		{
		 int nKindAtomsCount = 0;

		 NumberOfBytesRead = sizeof(nKindAtomsCount);
		 bwf &= ReadFile(hFile,&(nKindAtomsCount),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		 nSeek += (bwf)?NumberOfBytesReaded:0;

		 if (nKindAtomsCount > 0)
		 {
		  (*this)[i].resize(nKindAtomsCount);
		  NumberOfBytesRead = sizeof(BigArrayCoord);
		  for(j = 0; j < nKindAtomsCount; j++)
		  {
		   bwf &= ReadFile(hFile,(&(*this)[i][j]),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		   nSeek += (bwf)?NumberOfBytesReaded:0;
		  }
		 }
		}
	   }

	if(pSeek != NULL)
	{
	 *pSeek += nSeek;
	}
	bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
BigArrayCoord& BigArrayCoord::operator =(const BigArrayCoord& r)
{
	Z = r.Z;
	X = r.X;
	Y = r.Y;
	N = r.N;
	return *this;
}
//---------------------------------------------------------------------------
bool BigArrayCoord::operator ==(const BigArrayCoord& r)
{
	return  	(
		(Z == r.Z)
	&&	(X == r.X)
	&&	(Y == r.Y)
	&&	(N == r.N)
	);

}
//---------------------------------------------------------------------------
bool BigArrayCoord::operator !=(const BigArrayCoord& r)
{
	return (!(*this == r));
}
//---------------------------------------------------------------------------
void TDissolutionThread::RenderingKindAtomByNewAlgoritm(void)//вызывать когда поменялся алгоритм растворения
{
	EnterCS();

	bool bRet = KindAtoms.InitFomProb(SP);
	if( bRet == false )
		return;

	BigArrayCoord BAC;
	unsigned char TypeAtom;
	int Kind;
	for(BAC.Z = 0; BAC.Z < (unsigned)Items->Count; BAC.Z++ )
	{
	 if(*((int*)(Watch->Items[BAC.Z])) > 0) //в слое есть атомы
	 {
	  for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	  {
	   for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	   {
		for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
		{
		 TypeAtom = GetTypeAtom(&BAC);
		 if(TypeAtom > 0)
		 {
		  if((Kind = GetKindAtom(&BAC)) != PI_ERROR)
			AddLBACtoKindsArrays(Kind, &BAC);
		 }
		}
	   }
	  }
	 }
	}

	LeaveCS();
}
//---------------------------------------------------------------------------
#ifndef _DEBUG
#define DEBUG_MESSAGE //
#endif
#ifdef _DEBUG
#define DEBUG_MESSAGE(msg) OutputDebugString(msg)
#endif

int _random(int Max)
{
	int ret = rand()%Max;
	//AnsiString msg;
	//msg.printf("_random(%d)=%d",Max, ret);
	//DEBUG_MESSAGE(_c_str(msg));
	return ret;
}

void _randomize()
{
	time_t t;
	srand((unsigned) time(&t));
}
//---------------------------------------------------------------------------
void TDissolutionThread::InitRNG(void)
{
	if(m_InitRng == true)
	{
	 _randomize();
	 m_InitRng = false;
	}
}
//---------------------------------------------------------------------------
void TDissolutionThread::InitSurface(TDissolutionParametries &DP)
{
	SP = DP.SP;

	//начальная поверхность
	InitIdealSmoothSurface(DP.X, DP.Y);
/*
	int i;
	SurfaceMode SrfcMd = smFirst;//smSecond;//smFirst;//тип поверхности
	SizeX = DP.X;
	SizeY = DP.Y;
	NumAtomsInLayer = SizeY * SizeX * NumAtomsInCell;
	CopacityMemoryForLayer = NumAtomsInLayer * SizeBothDtTypeDtIndex;
	OneX = NumAtomsInCell * OneN;
	OneY = OneX * SizeX;
	while(Items->Count != 0)
	{
	 if((*(int*)(Watch->Items[Watch->Count-1])) > 0) delete Items->Items[Items->Count-1];
	 delete Watch->Items[Watch->Count-1];
	 Items->Delete(Items->Count-1);
	 Watch->Delete(Watch->Count-1);
	}

	bool bRet = KindAtoms.InitFomProb(SP);
	if( bRet == false )
		return;

	iDeletedAtom = 0;

	BigArrayCoord BAC;
	unsigned char TypeAtom;
	int Kind;
	BAC.Z = 0;
	for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	{
	 for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	 {
	  for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
	  {
	   SetTypeAtom(&BAC);
	  }
	 }
	}

	switch(SrfcMd)
	{
	 case smFirst:
	  for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	  {
	   for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	   {
		for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
		{
		 if((Kind = GetKindAtom(&BAC)) != PI_ERROR)
		   AddLBACtoKindsArrays(Kind, &BAC);
		}
	   }
	  }
	  break;

	 case smSecond:
	  for(BAC.Y = 0; BAC.Y < SizeY; BAC.Y++ )
	  {
	   for(BAC.X = 0; BAC.X < SizeX; BAC.X++ )
	   {
		for(BAC.N = 0; BAC.N < NumAtomsInCell; BAC.N++ )
		{
		 TypeAtom = GetTypeAtom(&BAC);
		 if(TypeAtom < 4)
		  SetNoDeletedTypeAtom(&BAC);
		}
	   }
	  }
	  {
	   TMaskVec vMask;
	   DeleteLeftMaskAtoms(vMask);
	  }
	 break;
	}
*/
	//дефекты
	if(DP.m_vDefect.size() > 0)
	{
	 int i,j;
	 int nDefectCount;
	 nDefectCount = DP.m_vDefect.size();
	 for(i = 0; i < nDefectCount; i++)
	 {
	  TDefect &Rec = DP.m_vDefect[i];
	  for(j = 0; j < Rec.m_nLoopCount; j++)
	  {
	   RenderingNewMask(Rec.m_vMask);
	   DeleteMaskedAtoms();
	  }
	 }
	}

	//маска
	if((DP.Masked == true) && (DP.m_vMask.size() > 0))
	{
	 RenderingNewMask(DP.m_vMask);
	}
	iDeletedAtom = 0;
	Finish = false;
}
//---------------------------------------------------------------------------
TStaticticData::TStaticticData()
{
	Init();
}
//---------------------------------------------------------------------------
TStaticticData::TStaticticData(const TStaticticData& r)
{
	*this = r;
}
//---------------------------------------------------------------------------
void TStaticticData::operator=(const TStaticticData& r)
{
	N1 = r.N1;
	N2 = r.N2;
	N3 = r.N3;
	Deleted = r.Deleted;
	MostPopularTypeCount = r.MostPopularTypeCount;
}
//---------------------------------------------------------------------------
void TStaticticData::Init(void)
{
	N1 = 0;
	N2 = 0;
	N3 = 0;
	Deleted = 0;
	MostPopularTypeCount = 0;
}
//---------------------------------------------------------------------------
TStaticticParam::TStaticticParam()
{
	Init();
}
//---------------------------------------------------------------------------
void TStaticticParam::Init()
{
	m_PeriodOfAverage = 0;
	m_vStatictic.clear();//не усредненная
	m_vAveragedStatictic.clear();//усредненная статисктика
}
//---------------------------------------------------------------------------
void TStaticticParam::AddStaticticData(TStaticticData &data)
{
	if (m_PeriodOfAverage > 0)
	{
	 if(m_vAveragedStatictic.size() ==0)
	 {
	  m_vAveragedStatictic.push_back(data);
	  return;
	 }
	 m_vStatictic.push_back(data);
	 AverageData();
	}
}
//---------------------------------------------------------------------------
void TStaticticParam::AverageData(void)
{
	if(m_vStatictic.size() == 0)
	{
	 return;
	}
	int LastAverageDeleted = 0;
	int cnt = m_vStatictic.size();
	int LastDeleted = m_vStatictic[cnt-1].Deleted;

	if(m_vAveragedStatictic.size() > 0)
	{
	 LastAverageDeleted = m_vAveragedStatictic[m_vAveragedStatictic.size()-1].Deleted;
	}

	if((LastDeleted - LastAverageDeleted) >= m_PeriodOfAverage)
	{
	 TStaticticData AvData;
	 int i = 0;

	 for(i=0; i < cnt; i++)
	 {
	  TStaticticData& Data = m_vStatictic[i];
	  AvData.N1 += Data.N1;
	  AvData.N2 += Data.N2;
	  AvData.N3 += Data.N3;
	  AvData.MostPopularTypeCount += Data.MostPopularTypeCount;
	 }
	 AvData.N1 /= cnt;
	 AvData.N2 /= cnt;
	 AvData.N3 /= cnt;
	 AvData.MostPopularTypeCount /= cnt;
	 AvData.Deleted = LastDeleted;
	 m_vAveragedStatictic.push_back(AvData);
	 m_vStatictic.clear();
	}
}
//---------------------------------------------------------------------------
const TStaticticDataVec& TStaticticParam::GetStatictic(void)
{
	m_vAveragedStatictic.m_MostPopularTypeIndex = m_MostPopularTypeIndex;
	return m_vAveragedStatictic;
}
//---------------------------------------------------------------------------
void TDissolutionThread::SetStaticticPeriod(int PeriodOfAverage)
{//включить сбор статистики с периодом усреднения
	if(m_StaticticParam.m_PeriodOfAverage != PeriodOfAverage)
	{
	 m_StaticticParam.Init();
	 m_StaticticParam.m_PeriodOfAverage = PeriodOfAverage;

	 TStaticticData sd;
	 sd.N1 = GetN1();
	 sd.N2 = GetN2();
	 sd.N3 = GetN3();
	 sd.N3 = GetN3();
	 sd.MostPopularTypeCount = GetPopularTypeCount();
	 sd.Deleted = iDeletedAtom;
	 m_StaticticParam.AddStaticticData(sd);
	}
}
//---------------------------------------------------------------------------
const TStaticticDataVec& TDissolutionThread::GetStatictic(void)
{//получить вектор накопленной статистки
	return m_StaticticParam.GetStatictic();
}
//---------------------------------------------------------------------------
int TDissolutionThread::GetPopularTypeCount()
{
	int ret=-1;
	if(m_StaticticParam.m_MostPopularTypeIndex != -1)
	{
	 ret = KindAtoms[m_StaticticParam.m_MostPopularTypeIndex].size();
	}
	return ret;
}
//---------------------------------------------------------------------------
TStaticticDataVec::TStaticticDataVec()
:std::vector<TStaticticData>()
{
	m_MostPopularTypeIndex = -1;
}
//---------------------------------------------------------------------------
TStaticticDataVec::TStaticticDataVec(const TStaticticDataVec &r)
:std::vector<TStaticticData>(r)
{
	m_MostPopularTypeIndex = r.m_MostPopularTypeIndex;
}
//---------------------------------------------------------------------------

