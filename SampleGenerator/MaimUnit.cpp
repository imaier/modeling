//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MaimUnit.h"
//#include <windef.h>
//#include <algorithm>
#include <stdio.h>

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMaimForm *MaimForm;
//---------------------------------------------------------------------------
TAtomCrd::TAtomCrd()
{
    x = 0;
    y = 0;
    z = 0;
    nV= 0;
}

TAtomCrd TAtomCrd::GetAdj(int i)
{//получить координаты итого соседа
    int dx, dy, dz;
    dx = 0;
    dy = 0;
    dz = 0;
    switch(i+1)
    {
        case 1:
         dx = -1;
         dy = +1;
         dz = +1;
        break;
        case 2:
         dx = +1;
         dy = -1;
         dz = +1;
        break;
        case 3:
         dx = -1;
         dy = -1;
         dz = -1;
        break;
        case 4:
         dx = +1;
         dy = +1;
         dz = -1;
        break;
    }
    if(z%2 != 0)
    {
     dx *= -1;
     dy *= -1;
     dz *= -1;
    }

    TAtomCrd AdjAtom;
    AdjAtom.x = x+dx;
    AdjAtom.y = y+dy;
    AdjAtom.z = z+dz;
    return AdjAtom;
}
//---------------------------------------------------------------------------
int TAtomCrd::GetColor()
{
    int nColor = 0;
    switch(nV)
    {
        case 0:
         //nColor = 0x0;
         nColor = 0xFFFFFF;//белый
        break;
        case 1:
         nColor = 0xFFFFFF;//белый
        break;
        case 2:
         nColor = 0x00FFFF;//желтый
        break;
        case 3:
         nColor = 0xFF0000;//синий
        break;
        case 4:
         nColor = 0x00FF00;//зелёный
        break;
        case 5:
         nColor = 0x0000FF;//красный
        break;
    }
    return nColor;
}
//---------------------------------------------------------------------------
int TAtomCrd::GetLinkColor(TAtomCrd b)
{
    int nColor = 0;
    switch(min(nV,b.nV))
    {
     case 0://в небеса
      nColor = 0xFFFFFF;//белый
     break;
     default:
      switch(max(nV,b.nV))
      {
       case 1://к односвязному атому
        nColor = 0xFFFFFF;//белый
       break;
       case 2://к двусвязному атому
        nColor = 0x00FFFF;//желтый
       break;
       case 3://к трёхсвязному атому
         nColor = 0xFF0000;//синий
       break;
       case 4://к четырёхсвязному атому
         nColor = 0x00FF00;//зелёный
       break;
       case 5://к неудаляемому атому
		 nColor = 0x0000FF;//красный
	   break;
	  }
	 break;
	}
	return nColor;
}
//---------------------------------------------------------------------------
 __fastcall TMaimForm::TMaimForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
int GetOneCount(int n)
{//количество бит==1
	int nRet = 0;
	for(int i = 0; i < 32; i++)
	{
		nRet += (n>>i)&0x01;
	}
	return nRet;
}
//---------------------------------------------------------------------------
void __fastcall TMaimForm::GenerateAlmas4(void)
{
	m_bStop = false;
	StatusProgressBar->Min = 0;
	StatusProgressBar->Max = 100;
	StatusProgressBar->Position = 0;
	bool bSplit = SplitCheckBox->Checked;
	bool bCube = CubeCheckBox->Checked;

		 AnsiString strAll, str1;
		 AnsiString szFilename;
		 szFilename = "Almas4ProbSet";
		 szFilename += ".cfg";

		 TProbKeyVec vPK;

		 TProbKey nKey, nKey2;

		 //int i=0;
		 if(FileExists(szFilename) == true)
		 {
		  FILE *pFile = fopen(szFilename.c_str(),"r");
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
		  }
		 }
		 else
		 {
		  AnsiString strErr;
		  strErr = "Не удалось открыть файл \"" + szFilename + "\"";
		  MessageBoxA(this->Handle,strErr.c_str(),("Внимание"),MB_OK | MB_ICONERROR);
		  return;
		 }

		 AnsiString strFileName;
		 int nPkSize = vPK.size();
		 int i;
		 for(i=0; i < nPkSize; i++)
		 {
		  nKey = vPK[i];
		  GenFile2(nKey, bSplit, bCube, strFileName);

		  if(i%5==0)
		  {
		   StatusLabel->Caption = strFileName;
		   StatusProgressBar->Position = (i+1)*100/nPkSize;
		  }

		//обработать очередь собщений
		Application->ProcessMessages();

		if(m_bStop == true)
		{
			StatusProgressBar->Position = 0;
			StatusLabel->Caption = "";
			break;
		}


		 }






	StatusProgressBar->Position = 100;
}
//---------------------------------------------------------------------------
void __fastcall TMaimForm::GenerateAlmas2(void)
{
	m_bStop = false;
	StatusProgressBar->Min = 0;
	StatusProgressBar->Max = 100;
	StatusProgressBar->Position = 0;
	bool bSplit = SplitCheckBox->Checked;
	bool bCube = CubeCheckBox->Checked;

	int nMaxNum = 0x100000;
	GenFile(0x0FFFF, bSplit, bCube);
	for(int i= 0; i < nMaxNum; i++)
	{
		if(i == 0x0008A008)
		{
		   i =i;
		}
		//если первого соседа нет, то не должно быть вторых соседей
		//true = первого соседа нет, а вторые есть
		bool b1 = (((i&0x00000001) == 0) && ((i&0x00000070) != 0));
		bool b2 = (((i&0x00000002) == 0) && ((i&0x00000380) != 0));
		bool b3 = (((i&0x00000004) == 0) && ((i&0x00001C00) != 0));
		bool b4 = (((i&0x00000008) == 0) && ((i&0x0000E000) != 0));

		//если первого соседа нет, то он не должен быть неудаляемым
		//true = первого соседа нет, а он неудаляем
		bool n1 = (((i&0x00000001) == 0) && ((i&0x00010000) != 0));
        bool n2 = (((i&0x00000002) == 0) && ((i&0x00020000) != 0));
        bool n3 = (((i&0x00000004) == 0) && ((i&0x00040000) != 0));
        bool n4 = (((i&0x00000008) == 0) && ((i&0x00080000) != 0));

        //возможна ли такая ситуация
        if(//должен быть хоть один первый сосед и как минимум один сосед отсутсвовать
           (GetOneCount(i&0x0000000f) > 0 && GetOneCount(i&0x0000000f) < 4)
           //если первого соседа нет, то не должно быть вторых соседей
        &&!(b1
		  ||b2
		  ||b3
		  ||b4
		   )
		//если первого соседа нет, то он не должен быть неудаляемым
		&&!(n1
		  ||n2
		  ||n3
		  ||n4
		   )
		  )
		{//так возможно
			StatusLabel->Caption = GenFileName(i);
			StatusProgressBar->Position = i*100/nMaxNum;
			GenFile(i, bSplit, bCube);

		}
		//обработать очередь собщений
		Application->ProcessMessages();

		if(m_bStop == true)
		{
			StatusProgressBar->Position = 0;
			StatusLabel->Caption = "";
			break;
		}
	}
	StatusProgressBar->Position = 100;
}
//---------------------------------------------------------------------------
AnsiString AddSphera(int nObjectNum, TAtomCrd& AtmCrd, bool bCrai = false)
{
	AnsiString strRet;
	strRet = "\r\ns:\t" + IntToStr(nObjectNum) + ",\t "
	 + IntToStr(AtmCrd.x) + ",\t "
	 + IntToStr(AtmCrd.y) + ",\t "
	 + IntToStr(AtmCrd.z) + ",\t "
	 + AnsiString((AtmCrd.nV>0? "0.5": "0")) + ",\t "
	 + AnsiString("0x") + IntToHex(bCrai?0x00FF00:AtmCrd.GetColor(), 6);//если атом краевой, то цвет зелёный
	 return strRet;
}
//---------------------------------------------------------------------------
AnsiString AddLine(int nObjectNum, int nS1, int nS2, int nColor)
{
    AnsiString strRet;
    bool bCilinders = true;//цилиндры вместо линий
    if(bCilinders == true)
    {
	 strRet = "\r\nc:\t" + IntToStr(nObjectNum) + ",\t "
      + IntToStr(nS1) + ",\t "
      + IntToStr(nS2) + ",\t "
      + AnsiString("0.3") + ",\t "
      + AnsiString("0x") + IntToHex(nColor, 6);
    }
    else
    {
     strRet = "\r\nl:\t" + IntToStr(nObjectNum) + ",\t "
      + IntToStr(nS1) + ",\t "
      + IntToStr(nS2) + ",\t "
      + IntToStr(1) + ",\t "
      + AnsiString("0x") + IntToHex(nColor, 6);
    }
    return strRet;
}
//---------------------------------------------------------------------------
void __fastcall TMaimForm::GenFile(int nPosition, bool bSplit, bool bCube)
{
    AnsiString strFileName = GenFileName(nPosition);
    AnsiString strContent;
    AnsiString strSpheras;
    AnsiString strLines;
    bool bDrowFourLinks = true;

    TAtomCrd MainAtom, AdjAtom, AdjAtom2, AdjAtom3;
    int ObjectNum = 100;//номер объекта сферы
    int ObjectLNum = 1000;//номер объекта линии
    int TmpObjectNum,TmpObjectNum2, TmpObjectNum3, MainObjectNum ;
    MainAtom.nV = GetOneCount((nPosition>>0) &0x0f);
    strSpheras += AddSphera(ObjectNum, MainAtom);
    MainObjectNum = ObjectNum++;
    int nV;
    for(int i = 0; i < 4; i++)
    {
        AdjAtom = MainAtom.GetAdj(i);
        AdjAtom.nV = GetOneCount((nPosition>>(4+i*3)) &0x07) + 1;
        AdjAtom.nV *= (nPosition>>i)&0x01;
		nV = AdjAtom.nV;
        if(AdjAtom.nV != 0)
        {//атом есть, он может быть неудаляемым
         if(((nPosition>>(i+16))&0x01) != 0)
         {//это неудаляемый атом
            AdjAtom.nV = 5;
         }
        }
        strSpheras += AddSphera(ObjectNum, AdjAtom);
        TmpObjectNum = ObjectNum++;
        strLines += AddLine(ObjectLNum++, MainObjectNum, TmpObjectNum, MainAtom.GetLinkColor(AdjAtom));
        if(nV != 0)
        {//сосед есть
         //int n4xCnt=0;//счетчик четерёхсвязных соседей i-того соседа
         for(int j = 0; j < 4; j++)
         {
          if(i != j)
          {
           //n4xCnt++;
           AdjAtom2 = AdjAtom.GetAdj(j);
           //if(n4xCnt > AdjAtom.nV-1)
           if((nPosition&(1<<(4+i*3+((j>i)?j-1:j)))) == 0)
           {
            AdjAtom2.nV = 0;//нет атома
           }
           else
           {
            AdjAtom2.nV = 4;//четырёхсвязный сосед
           }
           strSpheras += AddSphera(ObjectNum, AdjAtom2);
           TmpObjectNum2 = ObjectNum++;
           strLines += AddLine(ObjectLNum++, TmpObjectNum, TmpObjectNum2, AdjAtom.GetLinkColor(AdjAtom2));
           if(bDrowFourLinks == true && AdjAtom2.nV != 0)
           {
            for(int k = 0; k < 4; k++)
            {
             if(k != j)
             {
			  AdjAtom3 = AdjAtom2.GetAdj(k);
              AdjAtom3.nV = 0;//чтобы атом не рисовался
              strSpheras += AddSphera(ObjectNum, AdjAtom3, true);
              TmpObjectNum3 = ObjectNum++;
              AdjAtom3.nV = 4;//а цвет связей как у четырёхсвязного
              strLines += AddLine(ObjectLNum++, TmpObjectNum2, TmpObjectNum3, AdjAtom2.GetLinkColor(AdjAtom3));
             }
            }
           }
          }
         }
        }
        else
        {//ничего
        }
    }
    strContent = strSpheras + strLines;

    if(bCube)
    {
        strContent+= "\r\n\
s: 0000011,	1,	1,	3,	0,	0x00FF00\r\n\
s: 0000012,	1,	-1,	3,	0,	0x00FF00\r\n\
s: 0000013,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0000014,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0000015,	-1,	1,	3,	0,	0x00FF00\r\n\
s: 0000016,	-1,	-1,	3,	0,	0x00FF00\r\n\
s: 0000017,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 0000018,	-1,	1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0100011,	3,	1,	3,	0,	0x00FF00\r\n\
s: 0100012,	3,	-1,	3,	0,	0x00FF00\r\n\
s: 0100013,	3,	-1,	1,	0,	0x00FF00\r\n\
s: 0100014,	3,	1,	1,	0,	0x00FF00\r\n\
s: 0100015,	1,	1,	3,	0,	0x00FF00\r\n\
s: 0100016,	1,	-1,	3,	0,	0x00FF00\r\n\
s: 0100017,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0100018,	1,	1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 9100011,	-1,	1,	3,	0,	0x00FF00\r\n\
s: 9100012,	-1,	-1,	3,	0,	0x00FF00\r\n\
s: 9100013,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 9100014,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 9100015,	-3,	1,	3,	0,	0x00FF00\r\n\
s: 9100016,	-3,	-1,	3,	0,	0x00FF00\r\n\
s: 9100017,	-3,	-1,	1,	0,	0x00FF00\r\n\
s: 9100018,	-3,	1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0001011,	1,	3,	3,	0,	0x00FF00\r\n\
s: 0001012,	1,	1,	3,	0,	0x00FF00\r\n\
s: 0001013,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0001014,	1,	3,	1,	0,	0x00FF00\r\n\
s: 0001015,	-1,	3,	3,	0,	0x00FF00\r\n\
s: 0001016,	-1,	1,	3,	0,	0x00FF00\r\n\
s: 0001017,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 0001018,	-1,	3,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0091011,	1,	-1,	3,	0,	0x00FF00\r\n\
s: 0091012,	1,	-3,	3,	0,	0x00FF00\r\n\
s: 0091013,	1,	-3,	1,	0,	0x00FF00\r\n\
s: 0091014,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0091015,	-1,	-1,	3,	0,	0x00FF00\r\n\
s: 0091016,	-1,	-3,	3,	0,	0x00FF00\r\n\
s: 0091017,	-1,	-3,	1,	0,	0x00FF00\r\n\
s: 0091018,	-1,	-1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0101011,	3,	3,	3,	0,	0x00FF00\r\n\
s: 0101012,	3,	1,	3,	0,	0x00FF00\r\n\
s: 0101013,	3,	1,	1,	0,	0x00FF00\r\n\
s: 0101014,	3,	3,	1,	0,	0x00FF00\r\n\
s: 0101015,	1,	3,	3,	0,	0x00FF00\r\n\
s: 0101016,	1,	1,	3,	0,	0x00FF00\r\n\
s: 0101017,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0101018,	1,	3,	1,	0,	0x00FF00\r\n\
\r\n\
s: 9191011,	-1,	-1,	3,	0,	0x00FF00\r\n\
s: 9191012,	-1,	-3,	3,	0,	0x00FF00\r\n\
s: 9191013,	-1,	-3,	1,	0,	0x00FF00\r\n\
s: 9191014,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 9191015,	-3,	-1,	3,	0,	0x00FF00\r\n\
s: 9191016,	-3,	-3,	3,	0,	0x00FF00\r\n\
s: 9191017,	-3,	-3,	1,	0,	0x00FF00\r\n\
s: 9191018,	-3,	-1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 9101011,	-1,	3,	3,	0,	0x00FF00\r\n\
s: 9101012,	-1,	1,	3,	0,	0x00FF00\r\n\
s: 9101013,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 9101014,	-1,	3,	1,	0,	0x00FF00\r\n\
s: 9101015,	-3,	3,	3,	0,	0x00FF00\r\n\
s: 9101016,	-3,	1,	3,	0,	0x00FF00\r\n\
s: 9101017,	-3,	1,	1,	0,	0x00FF00\r\n\
s: 9101018,	-3,	3,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0191011,	3,	-1,	3,	0,	0x00FF00\r\n\
s: 0191012,	3,	-3,	3,	0,	0x00FF00\r\n\
s: 0191013,	3,	-3,	1,	0,	0x00FF00\r\n\
s: 0191014,	3,	-1,	1,	0,	0x00FF00\r\n\
s: 0191015,	1,	-1,	3,	0,	0x00FF00\r\n\
s: 0191016,	1,	-3,	3,	0,	0x00FF00\r\n\
s: 0191017,	1,	-3,	1,	0,	0x00FF00\r\n\
s: 0191018,	1,	-1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0000001,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0000002,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0000003,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0000004,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0000005,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 0000006,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 0000007,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0000008,	-1,	1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0100001,	3,	1,	1,	0,	0x00FF00\r\n\
s: 0100002,	3,	-1,	1,	0,	0x00FF00\r\n\
s: 0100003,	3,	-1,	-1,	0,	0x00FF00\r\n\
s: 0100004,	3,	1,	-1,	0,	0x00FF00\r\n\
s: 0100005,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0100006,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0100007,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0100008,	1,	1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 9100001,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 9100002,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 9100003,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 9100004,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 9100005,	-3,	1,	1,	0,	0x00FF00\r\n\
s: 9100006,	-3,	-1,	1,	0,	0x00FF00\r\n\
s: 9100007,	-3,	-1,	-1,	0,	0x00FF00\r\n\
s: 9100008,	-3,	1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0001001,	1,	3,	1,	0,	0x00FF00\r\n\
s: 0001002,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0001003,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0001004,	1,	3,	-1,	0,	0x00FF00\r\n\
s: 0001005,	-1,	3,	1,	0,	0x00FF00\r\n\
s: 0001006,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 0001007,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 0001008,	-1,	3,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0091001,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0091002,	1,	-3,	1,	0,	0x00FF00\r\n\
s: 0091003,	1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0091004,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0091005,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 0091006,	-1,	-3,	1,	0,	0x00FF00\r\n\
s: 0091007,	-1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0091008,	-1,	-1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0101001,	3,	3,	1,	0,	0x00FF00\r\n\
s: 0101002,	3,	1,	1,	0,	0x00FF00\r\n\
s: 0101003,	3,	1,	-1,	0,	0x00FF00\r\n\
s: 0101004,	3,	3,	-1,	0,	0x00FF00\r\n\
s: 0101005,	1,	3,	1,	0,	0x00FF00\r\n\
s: 0101006,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0101007,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0101008,	1,	3,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 9191001,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 9191002,	-1,	-3,	1,	0,	0x00FF00\r\n\
s: 9191003,	-1,	-3,	-1,	0,	0x00FF00\r\n\
s: 9191004,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 9191005,	-3,	-1,	1,	0,	0x00FF00\r\n\
s: 9191006,	-3,	-3,	1,	0,	0x00FF00\r\n\
s: 9191007,	-3,	-3,	-1,	0,	0x00FF00\r\n\
s: 9191008,	-3,	-1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 9101001,	-1,	3,	1,	0,	0x00FF00\r\n\
s: 9101002,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 9101003,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 9101004,	-1,	3,	-1,	0,	0x00FF00\r\n\
s: 9101005,	-3,	3,	1,	0,	0x00FF00\r\n\
s: 9101006,	-3,	1,	1,	0,	0x00FF00\r\n\
s: 9101007,	-3,	1,	-1,	0,	0x00FF00\r\n\
s: 9101008,	-3,	3,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0191001,	3,	-1,	1,	0,	0x00FF00\r\n\
s: 0191002,	3,	-3,	1,	0,	0x00FF00\r\n\
s: 0191003,	3,	-3,	-1,	0,	0x00FF00\r\n\
s: 0191004,	3,	-1,	-1,	0,	0x00FF00\r\n\
s: 0191005,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0191006,	1,	-3,	1,	0,	0x00FF00\r\n\
s: 0191007,	1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0191008,	1,	-1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0000911,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0000912,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0000913,	1,	-1,	-3,	0,	0x00FF00\r\n\
s: 0000914,	1,	1,	-3,	0,	0x00FF00\r\n\
s: 0000915,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 0000916,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0000917,	-1,	-1,	-3,	0,	0x00FF00\r\n\
s: 0000918,	-1,	1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0100911,	3,	1,	-1,	0,	0x00FF00\r\n\
s: 0100912,	3,	-1,	-1,	0,	0x00FF00\r\n\
s: 0100913,	3,	-1,	-3,	0,	0x00FF00\r\n\
s: 0100914,	3,	1,	-3,	0,	0x00FF00\r\n\
s: 0100915,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0100916,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0100917,	1,	-1,	-3,	0,	0x00FF00\r\n\
s: 0100918,	1,	1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 9100911,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 9100912,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 9100913,	-1,	-1,	-3,	0,	0x00FF00\r\n\
s: 9100914,	-1,	1,	-3,	0,	0x00FF00\r\n\
s: 9100915,	-3,	1,	-1,	0,	0x00FF00\r\n\
s: 9100916,	-3,	-1,	-1,	0,	0x00FF00\r\n\
s: 9100917,	-3,	-1,	-3,	0,	0x00FF00\r\n\
s: 9100918,	-3,	1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0001911,	1,	3,	-1,	0,	0x00FF00\r\n\
s: 0001912,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0001913,	1,	1,	-3,	0,	0x00FF00\r\n\
s: 0001914,	1,	3,	-3,	0,	0x00FF00\r\n\
s: 0001915,	-1,	3,	-1,	0,	0x00FF00\r\n\
s: 0001916,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 0001917,	-1,	1,	-3,	0,	0x00FF00\r\n\
s: 0001918,	-1,	3,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0091911,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0091912,	1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0091913,	1,	-3,	-3,	0,	0x00FF00\r\n\
s: 0091914,	1,	-1,	-3,	0,	0x00FF00\r\n\
s: 0091915,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0091916,	-1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0091917,	-1,	-3,	-3,	0,	0x00FF00\r\n\
s: 0091918,	-1,	-1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0101911,	3,	3,	-1,	0,	0x00FF00\r\n\
s: 0101912,	3,	1,	-1,	0,	0x00FF00\r\n\
s: 0101913,	3,	1,	-3,	0,	0x00FF00\r\n\
s: 0101914,	3,	3,	-3,	0,	0x00FF00\r\n\
s: 0101915,	1,	3,	-1,	0,	0x00FF00\r\n\
s: 0101916,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0101917,	1,	1,	-3,	0,	0x00FF00\r\n\
s: 0101918,	1,	3,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 9191911,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 9191912,	-1,	-3,	-1,	0,	0x00FF00\r\n\
s: 9191913,	-1,	-3,	-3,	0,	0x00FF00\r\n\
s: 9191914,	-1,	-1,	-3,	0,	0x00FF00\r\n\
s: 9191915,	-3,	-1,	-1,	0,	0x00FF00\r\n\
s: 9191916,	-3,	-3,	-1,	0,	0x00FF00\r\n\
s: 9191917,	-3,	-3,	-3,	0,	0x00FF00\r\n\
s: 9191918,	-3,	-1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 9101911,	-1,	3,	-1,	0,	0x00FF00\r\n\
s: 9101912,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 9101913,	-1,	1,	-3,	0,	0x00FF00\r\n\
s: 9101914,	-1,	3,	-3,	0,	0x00FF00\r\n\
s: 9101915,	-3,	3,	-1,	0,	0x00FF00\r\n\
s: 9101916,	-3,	1,	-1,	0,	0x00FF00\r\n\
s: 9101917,	-3,	1,	-3,	0,	0x00FF00\r\n\
s: 9101918,	-3,	3,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0191911,	3,	-1,	-1,	0,	0x00FF00\r\n\
s: 0191912,	3,	-3,	-1,	0,	0x00FF00\r\n\
s: 0191913,	3,	-3,	-3,	0,	0x00FF00\r\n\
s: 0191914,	3,	-1,	-3,	0,	0x00FF00\r\n\
s: 0191915,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0191916,	1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0191917,	1,	-3,	-3,	0,	0x00FF00\r\n\
s: 0191918,	1,	-1,	-3,	0,	0x00FF00\r\n\
\r\n\
l: 00000112,	0000011,	0000012,	1,	0x00FFFF\r\n\
l: 00000114,	0000011,	0000014,	1,	0x00FFFF\r\n\
l: 00000115,	0000011,	0000015,	1,	0x00FFFF\r\n\
l: 00000123,	0000012,	0000013,	1,	0x00FFFF\r\n\
l: 00000126,	0000012,	0000016,	1,	0x00FFFF\r\n\
l: 00000134,	0000013,	0000014,	1,	0xFFFF00\r\n\
l: 00000137,	0000013,	0000017,	1,	0xFFFF00\r\n\
l: 00000148,	0000014,	0000018,	1,	0xFFFF00\r\n\
l: 00000156,	0000015,	0000016,	1,	0x00FFFF\r\n\
l: 00000158,	0000015,	0000018,	1,	0x00FFFF\r\n\
l: 00000167,	0000016,	0000017,	1,	0x00FFFF\r\n\
l: 00000178,	0000017,	0000018,	1,	0xFFFF00\r\n\
l: 01000112,	0100011,	0100012,	1,	0x00FFFF\r\n\
l: 01000114,	0100011,	0100014,	1,	0x00FFFF\r\n\
l: 01000115,	0100011,	0100015,	1,	0x00FFFF\r\n\
l: 01000123,	0100012,	0100013,	1,	0x00FFFF\r\n\
l: 01000126,	0100012,	0100016,	1,	0x00FFFF\r\n\
l: 01000134,	0100013,	0100014,	1,	0x00FFFF\r\n\
l: 01000137,	0100013,	0100017,	1,	0x00FFFF\r\n\
l: 01000148,	0100014,	0100018,	1,	0x00FFFF\r\n\
l: 01000156,	0100015,	0100016,	1,	0x00FFFF\r\n\
l: 01000158,	0100015,	0100018,	1,	0x00FFFF\r\n\
l: 01000167,	0100016,	0100017,	1,	0x00FFFF\r\n\
l: 01000178,	0100017,	0100018,	1,	0x00FFFF\r\n\
l: 91000112,	9100011,	9100012,	1,	0x00FFFF\r\n\
l: 91000114,	9100011,	9100014,	1,	0x00FFFF\r\n\
l: 91000115,	9100011,	9100015,	1,	0x00FFFF\r\n\
l: 91000123,	9100012,	9100013,	1,	0x00FFFF\r\n\
l: 91000126,	9100012,	9100016,	1,	0x00FFFF\r\n\
l: 91000134,	9100013,	9100014,	1,	0x00FFFF\r\n\
l: 91000137,	9100013,	9100017,	1,	0x00FFFF\r\n\
l: 91000148,	9100014,	9100018,	1,	0x00FFFF\r\n\
l: 91000156,	9100015,	9100016,	1,	0x00FFFF\r\n\
l: 91000158,	9100015,	9100018,	1,	0x00FFFF\r\n\
l: 91000167,	9100016,	9100017,	1,	0x00FFFF\r\n\
l: 91000178,	9100017,	9100018,	1,	0x00FFFF\r\n\
l: 00010112,	0001011,	0001012,	1,	0x00FFFF\r\n\
l: 00010114,	0001011,	0001014,	1,	0x00FFFF\r\n\
l: 00010115,	0001011,	0001015,	1,	0x00FFFF\r\n\
l: 00010123,	0001012,	0001013,	1,	0x00FFFF\r\n\
l: 00010126,	0001012,	0001016,	1,	0x00FFFF\r\n\
l: 00010134,	0001013,	0001014,	1,	0x00FFFF\r\n\
l: 00010137,	0001013,	0001017,	1,	0x00FFFF\r\n\
l: 00010148,	0001014,	0001018,	1,	0x00FFFF\r\n\
l: 00010156,	0001015,	0001016,	1,	0x00FFFF\r\n\
l: 00010158,	0001015,	0001018,	1,	0x00FFFF\r\n\
l: 00010167,	0001016,	0001017,	1,	0x00FFFF\r\n\
l: 00010178,	0001017,	0001018,	1,	0x00FFFF\r\n\
l: 00910112,	0091011,	0091012,	1,	0x00FFFF\r\n\
l: 00910114,	0091011,	0091014,	1,	0x00FFFF\r\n\
l: 00910115,	0091011,	0091015,	1,	0x00FFFF\r\n\
l: 00910123,	0091012,	0091013,	1,	0x00FFFF\r\n\
l: 00910126,	0091012,	0091016,	1,	0x00FFFF\r\n\
l: 00910134,	0091013,	0091014,	1,	0x00FFFF\r\n\
l: 00910137,	0091013,	0091017,	1,	0x00FFFF\r\n\
l: 00910148,	0091014,	0091018,	1,	0x00FFFF\r\n\
l: 00910156,	0091015,	0091016,	1,	0x00FFFF\r\n\
l: 00910158,	0091015,	0091018,	1,	0x00FFFF\r\n\
l: 00910167,	0091016,	0091017,	1,	0x00FFFF\r\n\
l: 00910178,	0091017,	0091018,	1,	0x00FFFF\r\n\
l: 01010112,	0101011,	0101012,	1,	0x00FFFF\r\n\
l: 01010114,	0101011,	0101014,	1,	0x00FFFF\r\n\
l: 01010115,	0101011,	0101015,	1,	0x00FFFF\r\n\
l: 01010123,	0101012,	0101013,	1,	0x00FFFF\r\n\
l: 01010126,	0101012,	0101016,	1,	0x00FFFF\r\n\
l: 01010134,	0101013,	0101014,	1,	0x00FFFF\r\n\
l: 01010137,	0101013,	0101017,	1,	0x00FFFF\r\n\
l: 01010148,	0101014,	0101018,	1,	0x00FFFF\r\n\
l: 01010156,	0101015,	0101016,	1,	0x00FFFF\r\n\
l: 01010158,	0101015,	0101018,	1,	0x00FFFF\r\n\
l: 01010167,	0101016,	0101017,	1,	0x00FFFF\r\n\
l: 01010178,	0101017,	0101018,	1,	0x00FFFF\r\n\
l: 91910112,	9191011,	9191012,	1,	0x00FFFF\r\n\
l: 91910114,	9191011,	9191014,	1,	0x00FFFF\r\n\
l: 91910115,	9191011,	9191015,	1,	0x00FFFF\r\n\
l: 91910123,	9191012,	9191013,	1,	0x00FFFF\r\n\
l: 91910126,	9191012,	9191016,	1,	0x00FFFF\r\n\
l: 91910134,	9191013,	9191014,	1,	0x00FFFF\r\n\
l: 91910137,	9191013,	9191017,	1,	0x00FFFF\r\n\
l: 91910148,	9191014,	9191018,	1,	0x00FFFF\r\n\
l: 91910156,	9191015,	9191016,	1,	0x00FFFF\r\n\
l: 91910158,	9191015,	9191018,	1,	0x00FFFF\r\n\
l: 91910167,	9191016,	9191017,	1,	0x00FFFF\r\n\
l: 91910178,	9191017,	9191018,	1,	0x00FFFF\r\n\
l: 91010112,	9101011,	9101012,	1,	0x00FFFF\r\n\
l: 91010114,	9101011,	9101014,	1,	0x00FFFF\r\n\
l: 91010115,	9101011,	9101015,	1,	0x00FFFF\r\n\
l: 91010123,	9101012,	9101013,	1,	0x00FFFF\r\n\
l: 91010126,	9101012,	9101016,	1,	0x00FFFF\r\n\
l: 91010134,	9101013,	9101014,	1,	0x00FFFF\r\n\
l: 91010137,	9101013,	9101017,	1,	0x00FFFF\r\n\
l: 91010148,	9101014,	9101018,	1,	0x00FFFF\r\n\
l: 91010156,	9101015,	9101016,	1,	0x00FFFF\r\n\
l: 91010158,	9101015,	9101018,	1,	0x00FFFF\r\n\
l: 91010167,	9101016,	9101017,	1,	0x00FFFF\r\n\
l: 91010178,	9101017,	9101018,	1,	0x00FFFF\r\n\
l: 01910112,	0191011,	0191012,	1,	0x00FFFF\r\n\
l: 01910114,	0191011,	0191014,	1,	0x00FFFF\r\n\
l: 01910115,	0191011,	0191015,	1,	0x00FFFF\r\n\
l: 01910123,	0191012,	0191013,	1,	0x00FFFF\r\n\
l: 01910126,	0191012,	0191016,	1,	0x00FFFF\r\n\
l: 01910134,	0191013,	0191014,	1,	0x00FFFF\r\n\
l: 01910137,	0191013,	0191017,	1,	0x00FFFF\r\n\
l: 01910148,	0191014,	0191018,	1,	0x00FFFF\r\n\
l: 01910156,	0191015,	0191016,	1,	0x00FFFF\r\n\
l: 01910158,	0191015,	0191018,	1,	0x00FFFF\r\n\
l: 01910167,	0191016,	0191017,	1,	0x00FFFF\r\n\
l: 01910178,	0191017,	0191018,	1,	0x00FFFF\r\n\
l: 00000012,	0000001,	0000002,	1,	0xFFFF00\r\n\
l: 00000014,	0000001,	0000004,	1,	0xFFFF00\r\n\
l: 00000015,	0000001,	0000005,	1,	0xFFFF00\r\n\
l: 00000023,	0000002,	0000003,	1,	0xFFFF00\r\n\
l: 00000026,	0000002,	0000006,	1,	0xFFFF00\r\n\
l: 00000034,	0000003,	0000004,	1,	0xFFFF00\r\n\
l: 00000037,	0000003,	0000007,	1,	0xFFFF00\r\n\
l: 00000048,	0000004,	0000008,	1,	0xFFFF00\r\n\
l: 00000056,	0000005,	0000006,	1,	0xFFFF00\r\n\
l: 00000058,	0000005,	0000008,	1,	0xFFFF00\r\n\
l: 00000067,	0000006,	0000007,	1,	0xFFFF00\r\n\
l: 00000078,	0000007,	0000008,	1,	0xFFFF00\r\n\
l: 01000012,	0100001,	0100002,	1,	0x00FFFF\r\n\
l: 01000014,	0100001,	0100004,	1,	0x00FFFF\r\n\
l: 01000015,	0100001,	0100005,	1,	0x00FFFF\r\n\
l: 01000023,	0100002,	0100003,	1,	0x00FFFF\r\n\
l: 01000026,	0100002,	0100006,	1,	0x00FFFF\r\n\
l: 01000034,	0100003,	0100004,	1,	0x00FFFF\r\n\
l: 01000037,	0100003,	0100007,	1,	0x00FFFF\r\n\
l: 01000048,	0100004,	0100008,	1,	0x00FFFF\r\n\
l: 01000056,	0100005,	0100006,	1,	0x00FFFF\r\n\
l: 01000058,	0100005,	0100008,	1,	0x00FFFF\r\n\
l: 01000067,	0100006,	0100007,	1,	0x00FFFF\r\n\
l: 01000078,	0100007,	0100008,	1,	0x00FFFF\r\n\
l: 91000012,	9100001,	9100002,	1,	0x00FFFF\r\n\
l: 91000014,	9100001,	9100004,	1,	0x00FFFF\r\n\
l: 91000015,	9100001,	9100005,	1,	0x00FFFF\r\n\
l: 91000023,	9100002,	9100003,	1,	0x00FFFF\r\n\
l: 91000026,	9100002,	9100006,	1,	0x00FFFF\r\n\
l: 91000034,	9100003,	9100004,	1,	0x00FFFF\r\n\
l: 91000037,	9100003,	9100007,	1,	0x00FFFF\r\n\
l: 91000048,	9100004,	9100008,	1,	0x00FFFF\r\n\
l: 91000056,	9100005,	9100006,	1,	0x00FFFF\r\n\
l: 91000058,	9100005,	9100008,	1,	0x00FFFF\r\n\
l: 91000067,	9100006,	9100007,	1,	0x00FFFF\r\n\
l: 91000078,	9100007,	9100008,	1,	0x00FFFF\r\n\
l: 00010012,	0001001,	0001002,	1,	0x00FFFF\r\n\
l: 00010014,	0001001,	0001004,	1,	0x00FFFF\r\n\
l: 00010015,	0001001,	0001005,	1,	0x00FFFF\r\n\
l: 00010023,	0001002,	0001003,	1,	0x00FFFF\r\n\
l: 00010026,	0001002,	0001006,	1,	0x00FFFF\r\n\
l: 00010034,	0001003,	0001004,	1,	0x00FFFF\r\n\
l: 00010037,	0001003,	0001007,	1,	0x00FFFF\r\n\
l: 00010048,	0001004,	0001008,	1,	0x00FFFF\r\n\
l: 00010056,	0001005,	0001006,	1,	0x00FFFF\r\n\
l: 00010058,	0001005,	0001008,	1,	0x00FFFF\r\n\
l: 00010067,	0001006,	0001007,	1,	0x00FFFF\r\n\
l: 00010078,	0001007,	0001008,	1,	0x00FFFF\r\n\
l: 00910012,	0091001,	0091002,	1,	0x00FFFF\r\n\
l: 00910014,	0091001,	0091004,	1,	0x00FFFF\r\n\
l: 00910015,	0091001,	0091005,	1,	0x00FFFF\r\n\
l: 00910023,	0091002,	0091003,	1,	0x00FFFF\r\n\
l: 00910026,	0091002,	0091006,	1,	0x00FFFF\r\n\
l: 00910034,	0091003,	0091004,	1,	0x00FFFF\r\n\
l: 00910037,	0091003,	0091007,	1,	0x00FFFF\r\n\
l: 00910048,	0091004,	0091008,	1,	0x00FFFF\r\n\
l: 00910056,	0091005,	0091006,	1,	0x00FFFF\r\n\
l: 00910058,	0091005,	0091008,	1,	0x00FFFF\r\n\
l: 00910067,	0091006,	0091007,	1,	0x00FFFF\r\n\
l: 00910078,	0091007,	0091008,	1,	0x00FFFF\r\n\
l: 01010012,	0101001,	0101002,	1,	0x00FFFF\r\n\
l: 01010014,	0101001,	0101004,	1,	0x00FFFF\r\n\
l: 01010015,	0101001,	0101005,	1,	0x00FFFF\r\n\
l: 01010023,	0101002,	0101003,	1,	0x00FFFF\r\n\
l: 01010026,	0101002,	0101006,	1,	0x00FFFF\r\n\
l: 01010034,	0101003,	0101004,	1,	0x00FFFF\r\n\
l: 01010037,	0101003,	0101007,	1,	0x00FFFF\r\n\
l: 01010048,	0101004,	0101008,	1,	0x00FFFF\r\n\
l: 01010056,	0101005,	0101006,	1,	0x00FFFF\r\n\
l: 01010058,	0101005,	0101008,	1,	0x00FFFF\r\n\
l: 01010067,	0101006,	0101007,	1,	0x00FFFF\r\n\
l: 01010078,	0101007,	0101008,	1,	0x00FFFF\r\n\
l: 91910012,	9191001,	9191002,	1,	0x00FFFF\r\n\
l: 91910014,	9191001,	9191004,	1,	0x00FFFF\r\n\
l: 91910015,	9191001,	9191005,	1,	0x00FFFF\r\n\
l: 91910023,	9191002,	9191003,	1,	0x00FFFF\r\n\
l: 91910026,	9191002,	9191006,	1,	0x00FFFF\r\n\
l: 91910034,	9191003,	9191004,	1,	0x00FFFF\r\n\
l: 91910037,	9191003,	9191007,	1,	0x00FFFF\r\n\
l: 91910048,	9191004,	9191008,	1,	0x00FFFF\r\n\
l: 91910056,	9191005,	9191006,	1,	0x00FFFF\r\n\
l: 91910058,	9191005,	9191008,	1,	0x00FFFF\r\n\
l: 91910067,	9191006,	9191007,	1,	0x00FFFF\r\n\
l: 91910078,	9191007,	9191008,	1,	0x00FFFF\r\n\
l: 91010012,	9101001,	9101002,	1,	0x00FFFF\r\n\
l: 91010014,	9101001,	9101004,	1,	0x00FFFF\r\n\
l: 91010015,	9101001,	9101005,	1,	0x00FFFF\r\n\
l: 91010023,	9101002,	9101003,	1,	0x00FFFF\r\n\
l: 91010026,	9101002,	9101006,	1,	0x00FFFF\r\n\
l: 91010034,	9101003,	9101004,	1,	0x00FFFF\r\n\
l: 91010037,	9101003,	9101007,	1,	0x00FFFF\r\n\
l: 91010048,	9101004,	9101008,	1,	0x00FFFF\r\n\
l: 91010056,	9101005,	9101006,	1,	0x00FFFF\r\n\
l: 91010058,	9101005,	9101008,	1,	0x00FFFF\r\n\
l: 91010067,	9101006,	9101007,	1,	0x00FFFF\r\n\
l: 91010078,	9101007,	9101008,	1,	0x00FFFF\r\n\
l: 01910012,	0191001,	0191002,	1,	0x00FFFF\r\n\
l: 01910014,	0191001,	0191004,	1,	0x00FFFF\r\n\
l: 01910015,	0191001,	0191005,	1,	0x00FFFF\r\n\
l: 01910023,	0191002,	0191003,	1,	0x00FFFF\r\n\
l: 01910026,	0191002,	0191006,	1,	0x00FFFF\r\n\
l: 01910034,	0191003,	0191004,	1,	0x00FFFF\r\n\
l: 01910037,	0191003,	0191007,	1,	0x00FFFF\r\n\
l: 01910048,	0191004,	0191008,	1,	0x00FFFF\r\n\
l: 01910056,	0191005,	0191006,	1,	0x00FFFF\r\n\
l: 01910058,	0191005,	0191008,	1,	0x00FFFF\r\n\
l: 01910067,	0191006,	0191007,	1,	0x00FFFF\r\n\
l: 01910078,	0191007,	0191008,	1,	0x00FFFF\r\n\
l: 00009112,	0000911,	0000912,	1,	0xFFFF00\r\n\
l: 00009114,	0000911,	0000914,	1,	0x00FFFF\r\n\
l: 00009115,	0000911,	0000915,	1,	0x00FFFF\r\n\
l: 00009123,	0000912,	0000913,	1,	0x00FFFF\r\n\
l: 00009126,	0000912,	0000916,	1,	0x00FFFF\r\n\
l: 00009134,	0000913,	0000914,	1,	0x00FFFF\r\n\
l: 00009137,	0000913,	0000917,	1,	0x00FFFF\r\n\
l: 00009148,	0000914,	0000918,	1,	0x00FFFF\r\n\
l: 00009156,	0000915,	0000916,	1,	0x00FFFF\r\n\
l: 00009158,	0000915,	0000918,	1,	0x00FFFF\r\n\
l: 00009167,	0000916,	0000917,	1,	0x00FFFF\r\n\
l: 00009178,	0000917,	0000918,	1,	0x00FFFF\r\n\
l: 01009112,	0100911,	0100912,	1,	0x00FFFF\r\n\
l: 01009114,	0100911,	0100914,	1,	0x00FFFF\r\n\
l: 01009115,	0100911,	0100915,	1,	0x00FFFF\r\n\
l: 01009123,	0100912,	0100913,	1,	0x00FFFF\r\n\
l: 01009126,	0100912,	0100916,	1,	0x00FFFF\r\n\
l: 01009134,	0100913,	0100914,	1,	0x00FFFF\r\n\
l: 01009137,	0100913,	0100917,	1,	0x00FFFF\r\n\
l: 01009148,	0100914,	0100918,	1,	0x00FFFF\r\n\
l: 01009156,	0100915,	0100916,	1,	0xFFFF00\r\n\
l: 01009158,	0100915,	0100918,	1,	0x00FFFF\r\n\
l: 01009167,	0100916,	0100917,	1,	0x00FFFF\r\n\
l: 01009178,	0100917,	0100918,	1,	0x00FFFF\r\n\
l: 91009112,	9100911,	9100912,	1,	0x00FFFF\r\n\
l: 91009114,	9100911,	9100914,	1,	0x00FFFF\r\n\
l: 91009115,	9100911,	9100915,	1,	0x00FFFF\r\n\
l: 91009123,	9100912,	9100913,	1,	0x00FFFF\r\n\
l: 91009126,	9100912,	9100916,	1,	0x00FFFF\r\n\
l: 91009134,	9100913,	9100914,	1,	0x00FFFF\r\n\
l: 91009137,	9100913,	9100917,	1,	0x00FFFF\r\n\
l: 91009148,	9100914,	9100918,	1,	0x00FFFF\r\n\
l: 91009156,	9100915,	9100916,	1,	0x00FFFF\r\n\
l: 91009158,	9100915,	9100918,	1,	0x00FFFF\r\n\
l: 91009167,	9100916,	9100917,	1,	0x00FFFF\r\n\
l: 91009178,	9100917,	9100918,	1,	0x00FFFF\r\n\
l: 00019112,	0001911,	0001912,	1,	0x00FFFF\r\n\
l: 00019114,	0001911,	0001914,	1,	0x00FFFF\r\n\
l: 00019115,	0001911,	0001915,	1,	0x00FFFF\r\n\
l: 00019123,	0001912,	0001913,	1,	0x00FFFF\r\n\
l: 00019126,	0001912,	0001916,	1,	0x00FFFF\r\n\
l: 00019134,	0001913,	0001914,	1,	0x00FFFF\r\n\
l: 00019137,	0001913,	0001917,	1,	0x00FFFF\r\n\
l: 00019148,	0001914,	0001918,	1,	0x00FFFF\r\n\
l: 00019156,	0001915,	0001916,	1,	0x00FFFF\r\n\
l: 00019158,	0001915,	0001918,	1,	0x00FFFF\r\n\
l: 00019167,	0001916,	0001917,	1,	0x00FFFF\r\n\
l: 00019178,	0001917,	0001918,	1,	0x00FFFF\r\n\
l: 00919112,	0091911,	0091912,	1,	0x00FFFF\r\n\
l: 00919114,	0091911,	0091914,	1,	0x00FFFF\r\n\
l: 00919115,	0091911,	0091915,	1,	0x00FFFF\r\n\
l: 00919123,	0091912,	0091913,	1,	0x00FFFF\r\n\
l: 00919126,	0091912,	0091916,	1,	0x00FFFF\r\n\
l: 00919134,	0091913,	0091914,	1,	0x00FFFF\r\n\
l: 00919137,	0091913,	0091917,	1,	0x00FFFF\r\n\
l: 00919148,	0091914,	0091918,	1,	0x00FFFF\r\n\
l: 00919156,	0091915,	0091916,	1,	0x00FFFF\r\n\
l: 00919158,	0091915,	0091918,	1,	0x00FFFF\r\n\
l: 00919167,	0091916,	0091917,	1,	0x00FFFF\r\n\
l: 00919178,	0091917,	0091918,	1,	0x00FFFF\r\n\
l: 01019112,	0101911,	0101912,	1,	0x00FFFF\r\n\
l: 01019114,	0101911,	0101914,	1,	0x00FFFF\r\n\
l: 01019115,	0101911,	0101915,	1,	0x00FFFF\r\n\
l: 01019123,	0101912,	0101913,	1,	0x00FFFF\r\n\
l: 01019126,	0101912,	0101916,	1,	0x00FFFF\r\n\
l: 01019134,	0101913,	0101914,	1,	0x00FFFF\r\n\
l: 01019137,	0101913,	0101917,	1,	0x00FFFF\r\n\
l: 01019148,	0101914,	0101918,	1,	0x00FFFF\r\n\
l: 01019156,	0101915,	0101916,	1,	0x00FFFF\r\n\
l: 01019158,	0101915,	0101918,	1,	0x00FFFF\r\n\
l: 01019167,	0101916,	0101917,	1,	0x00FFFF\r\n\
l: 01019178,	0101917,	0101918,	1,	0x00FFFF\r\n\
l: 91919112,	9191911,	9191912,	1,	0x00FFFF\r\n\
l: 91919114,	9191911,	9191914,	1,	0x00FFFF\r\n\
l: 91919115,	9191911,	9191915,	1,	0x00FFFF\r\n\
l: 91919123,	9191912,	9191913,	1,	0x00FFFF\r\n\
l: 91919126,	9191912,	9191916,	1,	0x00FFFF\r\n\
l: 91919134,	9191913,	9191914,	1,	0x00FFFF\r\n\
l: 91919137,	9191913,	9191917,	1,	0x00FFFF\r\n\
l: 91919148,	9191914,	9191918,	1,	0x00FFFF\r\n\
l: 91919156,	9191915,	9191916,	1,	0x00FFFF\r\n\
l: 91919158,	9191915,	9191918,	1,	0x00FFFF\r\n\
l: 91919167,	9191916,	9191917,	1,	0x00FFFF\r\n\
l: 91919178,	9191917,	9191918,	1,	0x00FFFF\r\n\
l: 91019112,	9101911,	9101912,	1,	0x00FFFF\r\n\
l: 91019114,	9101911,	9101914,	1,	0x00FFFF\r\n\
l: 91019115,	9101911,	9101915,	1,	0x00FFFF\r\n\
l: 91019123,	9101912,	9101913,	1,	0x00FFFF\r\n\
l: 91019126,	9101912,	9101916,	1,	0x00FFFF\r\n\
l: 91019134,	9101913,	9101914,	1,	0x00FFFF\r\n\
l: 91019137,	9101913,	9101917,	1,	0x00FFFF\r\n\
l: 91019148,	9101914,	9101918,	1,	0x00FFFF\r\n\
l: 91019156,	9101915,	9101916,	1,	0x00FFFF\r\n\
l: 91019158,	9101915,	9101918,	1,	0x00FFFF\r\n\
l: 91019167,	9101916,	9101917,	1,	0x00FFFF\r\n\
l: 91019178,	9101917,	9101918,	1,	0x00FFFF\r\n\
l: 01919112,	0191911,	0191912,	1,	0x00FFFF\r\n\
l: 01919114,	0191911,	0191914,	1,	0x00FFFF\r\n\
l: 01919115,	0191911,	0191915,	1,	0x00FFFF\r\n\
l: 01919123,	0191912,	0191913,	1,	0x00FFFF\r\n\
l: 01919126,	0191912,	0191916,	1,	0x00FFFF\r\n\
l: 01919134,	0191913,	0191914,	1,	0x00FFFF\r\n\
l: 01919137,	0191913,	0191917,	1,	0x00FFFF\r\n\
l: 01919148,	0191914,	0191918,	1,	0x00FFFF\r\n\
l: 01919156,	0191915,	0191916,	1,	0x00FFFF\r\n\
l: 01919158,	0191915,	0191918,	1,	0x00FFFF\r\n\
l: 01919167,	0191916,	0191917,	1,	0x00FFFF\r\n\
l: 01919178,	0191917,	0191918,	1,	0x00FFFF\r\n\
        ";
    }



    //запись в файл
    if(strContent!= "")
    {
        AnsiString strDir = GetCurrentDir();
        strDir += "\\Samples";
        if(bSplit == true)
        {
            int nLnk = GetOneCount((nPosition>>0)&0x0f);
            int nAdLnk[4];
            int nTmp, i, j;
            AnsiString strAddDir;
            for(int i = 0; i < 4 ; i++)
            {
                //связность соседа
                nAdLnk[i] = (GetOneCount((nPosition>>(4+i*3))&0x07)+1) * (nPosition>>i&1);
				if(nAdLnk[i] != 0 && ((nPosition>>(i+16)&1)!=0))
                {
                    nAdLnk[i] = 5;//сосед неудаляемый
                }
            }

            for(j = 0; j < 4 ; j++)
            {
                for(i = j+1; i < 4 ; i++)
                {
                    if(nAdLnk[j] > nAdLnk[i])
                    {
                        nTmp = nAdLnk[j];
                        nAdLnk[j] = nAdLnk[i];
                        nAdLnk[i] = nTmp;
                    }
                }
                if(nAdLnk[j] > 0)
                {
                    strAddDir+= IntToStr(nAdLnk[j]);
                }
            }
            strDir+="\\" + IntToStr(nLnk);
            if(strAddDir != "")
            {
                strDir+="\\" + strAddDir;
            }
        }
        if(DirectoryExists(strDir) == false)
        {
         ForceDirectories(strDir);
        }
        //int hFile = FileOpen(strFileName, fmCreate|fmOpenWrite);
        int hFile = FileCreate(strDir + "\\" + strFileName);
        if(hFile != -1)
        {
            FileWrite(hFile, strContent.c_str(), strContent.Length());
            FileClose(hFile);
		}
    }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMaimForm::GenFileName(int nPosition)
{
    AnsiString strRet, strTemp;
    strTemp.printf("%5.5x",nPosition);
    strRet+= GetOneCount((nPosition>>0)&0x0f);
    int i, nV;

    for(i = 0; i < 4; i++)
    {
        nV = (GetOneCount((nPosition>>(4+i*3))&0x07)+1) * (nPosition>>i&1);
        if(nV != 0 && (nPosition>>(i+16)&1) != 0)
        {
            nV = 5;
        }
        strRet+= nV;
    }
    //strRet+= (GetOneCount((nPosition>>4)&0x07)+1) * (nPosition>>0&1);
    //strRet+= (GetOneCount((nPosition>>7)&0x07)+1) * (nPosition>>1&1);
    //strRet+= (GetOneCount((nPosition>>10)&0x07)+1)* (nPosition>>2&1);
    //strRet+= (GetOneCount((nPosition>>13)&0x07)+1)* (nPosition>>3&1);
    strRet = strRet + "-" +strTemp.UpperCase();
    strRet+= ".txt";
    return strRet;
}
//---------------------------------------------------------------------------
void __fastcall TMaimForm::StopButtonClick(TObject *Sender)
{
    m_bStop = true;
}
//---------------------------------------------------------------------------
void __fastcall TMaimForm::GenerateButtonClick(TObject *Sender)
{
	//GenerateAlmas2();
	GenerateAlmas4();
}
//---------------------------------------------------------------------------
void __fastcall TMaimForm::GenFile2(TProbKey nKey, bool bSplit, bool bCube, AnsiString &strFileName)
{
	TAlmas4ProbSetKey k;
	k.fill(nKey);

	if(k.Key2 == 20302)
	{
	 k.Key2 = k.Key2;
	}

	strFileName = k.strName + ".txt";
	AnsiString strContent;
	AnsiString strSpheras;
	AnsiString strLines;
	bool bDrowFourLinks = true;

	TAtomCrd MainAtom, AdjAtom, AdjAtom2, AdjAtom3, AdjAtom4;
	int ObjectNum = 100;//номер объекта сферы
	int ObjectLNum = 1000;//номер объекта линии
	int TmpObjectNum,TmpObjectNum2, TmpObjectNum3, MainObjectNum ;
	MainAtom.nV = k.Adg1+1;
	strSpheras += AddSphera(ObjectNum, MainAtom);
	MainObjectNum = ObjectNum++;
	//int nV;
	for(int i = 0; i < 4; i++)
	{
		AdjAtom = MainAtom.GetAdj(i);
		AdjAtom.nV = k.GetAdjType(i);
		//nV = AdjAtom.nV;
		strSpheras += AddSphera(ObjectNum, AdjAtom);
		TmpObjectNum = ObjectNum++;
		strLines += AddLine(ObjectLNum++, MainObjectNum, TmpObjectNum, MainAtom.GetLinkColor(AdjAtom));

		for(int j = 0; j < 4; j++)
		{
		 if(i != j)
		 {
		  AdjAtom2 = AdjAtom.GetAdj(j);
		  AdjAtom2.nV = k.GetAdj2Type(i, (j>i)? (j-1):(j));
		  strSpheras += AddSphera(ObjectNum, AdjAtom2);
		  TmpObjectNum2 = ObjectNum++;
		  if(AdjAtom.nV > 0 || AdjAtom2.nV > 0)
			strLines += AddLine(ObjectLNum++, TmpObjectNum, TmpObjectNum2, AdjAtom.GetLinkColor(AdjAtom2));


		  if(bDrowFourLinks == true && AdjAtom2.nV > 0)
		  {
		   for(int k = 0; k < 4; k++)
		   {
			if(k != j)
			{
			 AdjAtom3 = AdjAtom2.GetAdj(k);
			 AdjAtom3.nV = 0;//чтобы атом не рисовался
			 if((AdjAtom2.nV-((AdjAtom.nV==0)?0:1)) > ((k>j)? (k-1):(k)))
			 {
			  AdjAtom3.nV = 4;//
			 }
			 strSpheras += AddSphera(ObjectNum, AdjAtom3/*, true*/);
			 TmpObjectNum3 = ObjectNum++;
			 //AdjAtom3.nV = 4;//а цвет связей как у четырёхсвязного
			 if(AdjAtom2.nV > 0)
			  strLines += AddLine(ObjectLNum++, TmpObjectNum2, TmpObjectNum3, AdjAtom2.GetLinkColor(AdjAtom3));
			}
		   }
		  }

		 }
		}

	}
	strContent = strSpheras + strLines;

	if(bCube)
	{
		strContent+= "\r\n\
s: 0000011,	1,	1,	3,	0,	0x00FF00\r\n\
s: 0000012,	1,	-1,	3,	0,	0x00FF00\r\n\
s: 0000013,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0000014,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0000015,	-1,	1,	3,	0,	0x00FF00\r\n\
s: 0000016,	-1,	-1,	3,	0,	0x00FF00\r\n\
s: 0000017,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 0000018,	-1,	1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0100011,	3,	1,	3,	0,	0x00FF00\r\n\
s: 0100012,	3,	-1,	3,	0,	0x00FF00\r\n\
s: 0100013,	3,	-1,	1,	0,	0x00FF00\r\n\
s: 0100014,	3,	1,	1,	0,	0x00FF00\r\n\
s: 0100015,	1,	1,	3,	0,	0x00FF00\r\n\
s: 0100016,	1,	-1,	3,	0,	0x00FF00\r\n\
s: 0100017,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0100018,	1,	1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 9100011,	-1,	1,	3,	0,	0x00FF00\r\n\
s: 9100012,	-1,	-1,	3,	0,	0x00FF00\r\n\
s: 9100013,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 9100014,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 9100015,	-3,	1,	3,	0,	0x00FF00\r\n\
s: 9100016,	-3,	-1,	3,	0,	0x00FF00\r\n\
s: 9100017,	-3,	-1,	1,	0,	0x00FF00\r\n\
s: 9100018,	-3,	1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0001011,	1,	3,	3,	0,	0x00FF00\r\n\
s: 0001012,	1,	1,	3,	0,	0x00FF00\r\n\
s: 0001013,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0001014,	1,	3,	1,	0,	0x00FF00\r\n\
s: 0001015,	-1,	3,	3,	0,	0x00FF00\r\n\
s: 0001016,	-1,	1,	3,	0,	0x00FF00\r\n\
s: 0001017,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 0001018,	-1,	3,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0091011,	1,	-1,	3,	0,	0x00FF00\r\n\
s: 0091012,	1,	-3,	3,	0,	0x00FF00\r\n\
s: 0091013,	1,	-3,	1,	0,	0x00FF00\r\n\
s: 0091014,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0091015,	-1,	-1,	3,	0,	0x00FF00\r\n\
s: 0091016,	-1,	-3,	3,	0,	0x00FF00\r\n\
s: 0091017,	-1,	-3,	1,	0,	0x00FF00\r\n\
s: 0091018,	-1,	-1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0101011,	3,	3,	3,	0,	0x00FF00\r\n\
s: 0101012,	3,	1,	3,	0,	0x00FF00\r\n\
s: 0101013,	3,	1,	1,	0,	0x00FF00\r\n\
s: 0101014,	3,	3,	1,	0,	0x00FF00\r\n\
s: 0101015,	1,	3,	3,	0,	0x00FF00\r\n\
s: 0101016,	1,	1,	3,	0,	0x00FF00\r\n\
s: 0101017,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0101018,	1,	3,	1,	0,	0x00FF00\r\n\
\r\n\
s: 9191011,	-1,	-1,	3,	0,	0x00FF00\r\n\
s: 9191012,	-1,	-3,	3,	0,	0x00FF00\r\n\
s: 9191013,	-1,	-3,	1,	0,	0x00FF00\r\n\
s: 9191014,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 9191015,	-3,	-1,	3,	0,	0x00FF00\r\n\
s: 9191016,	-3,	-3,	3,	0,	0x00FF00\r\n\
s: 9191017,	-3,	-3,	1,	0,	0x00FF00\r\n\
s: 9191018,	-3,	-1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 9101011,	-1,	3,	3,	0,	0x00FF00\r\n\
s: 9101012,	-1,	1,	3,	0,	0x00FF00\r\n\
s: 9101013,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 9101014,	-1,	3,	1,	0,	0x00FF00\r\n\
s: 9101015,	-3,	3,	3,	0,	0x00FF00\r\n\
s: 9101016,	-3,	1,	3,	0,	0x00FF00\r\n\
s: 9101017,	-3,	1,	1,	0,	0x00FF00\r\n\
s: 9101018,	-3,	3,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0191011,	3,	-1,	3,	0,	0x00FF00\r\n\
s: 0191012,	3,	-3,	3,	0,	0x00FF00\r\n\
s: 0191013,	3,	-3,	1,	0,	0x00FF00\r\n\
s: 0191014,	3,	-1,	1,	0,	0x00FF00\r\n\
s: 0191015,	1,	-1,	3,	0,	0x00FF00\r\n\
s: 0191016,	1,	-3,	3,	0,	0x00FF00\r\n\
s: 0191017,	1,	-3,	1,	0,	0x00FF00\r\n\
s: 0191018,	1,	-1,	1,	0,	0x00FF00\r\n\
\r\n\
s: 0000001,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0000002,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0000003,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0000004,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0000005,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 0000006,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 0000007,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0000008,	-1,	1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0100001,	3,	1,	1,	0,	0x00FF00\r\n\
s: 0100002,	3,	-1,	1,	0,	0x00FF00\r\n\
s: 0100003,	3,	-1,	-1,	0,	0x00FF00\r\n\
s: 0100004,	3,	1,	-1,	0,	0x00FF00\r\n\
s: 0100005,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0100006,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0100007,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0100008,	1,	1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 9100001,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 9100002,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 9100003,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 9100004,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 9100005,	-3,	1,	1,	0,	0x00FF00\r\n\
s: 9100006,	-3,	-1,	1,	0,	0x00FF00\r\n\
s: 9100007,	-3,	-1,	-1,	0,	0x00FF00\r\n\
s: 9100008,	-3,	1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0001001,	1,	3,	1,	0,	0x00FF00\r\n\
s: 0001002,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0001003,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0001004,	1,	3,	-1,	0,	0x00FF00\r\n\
s: 0001005,	-1,	3,	1,	0,	0x00FF00\r\n\
s: 0001006,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 0001007,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 0001008,	-1,	3,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0091001,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0091002,	1,	-3,	1,	0,	0x00FF00\r\n\
s: 0091003,	1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0091004,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0091005,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 0091006,	-1,	-3,	1,	0,	0x00FF00\r\n\
s: 0091007,	-1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0091008,	-1,	-1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0101001,	3,	3,	1,	0,	0x00FF00\r\n\
s: 0101002,	3,	1,	1,	0,	0x00FF00\r\n\
s: 0101003,	3,	1,	-1,	0,	0x00FF00\r\n\
s: 0101004,	3,	3,	-1,	0,	0x00FF00\r\n\
s: 0101005,	1,	3,	1,	0,	0x00FF00\r\n\
s: 0101006,	1,	1,	1,	0,	0x00FF00\r\n\
s: 0101007,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0101008,	1,	3,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 9191001,	-1,	-1,	1,	0,	0x00FF00\r\n\
s: 9191002,	-1,	-3,	1,	0,	0x00FF00\r\n\
s: 9191003,	-1,	-3,	-1,	0,	0x00FF00\r\n\
s: 9191004,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 9191005,	-3,	-1,	1,	0,	0x00FF00\r\n\
s: 9191006,	-3,	-3,	1,	0,	0x00FF00\r\n\
s: 9191007,	-3,	-3,	-1,	0,	0x00FF00\r\n\
s: 9191008,	-3,	-1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 9101001,	-1,	3,	1,	0,	0x00FF00\r\n\
s: 9101002,	-1,	1,	1,	0,	0x00FF00\r\n\
s: 9101003,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 9101004,	-1,	3,	-1,	0,	0x00FF00\r\n\
s: 9101005,	-3,	3,	1,	0,	0x00FF00\r\n\
s: 9101006,	-3,	1,	1,	0,	0x00FF00\r\n\
s: 9101007,	-3,	1,	-1,	0,	0x00FF00\r\n\
s: 9101008,	-3,	3,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0191001,	3,	-1,	1,	0,	0x00FF00\r\n\
s: 0191002,	3,	-3,	1,	0,	0x00FF00\r\n\
s: 0191003,	3,	-3,	-1,	0,	0x00FF00\r\n\
s: 0191004,	3,	-1,	-1,	0,	0x00FF00\r\n\
s: 0191005,	1,	-1,	1,	0,	0x00FF00\r\n\
s: 0191006,	1,	-3,	1,	0,	0x00FF00\r\n\
s: 0191007,	1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0191008,	1,	-1,	-1,	0,	0x00FF00\r\n\
\r\n\
s: 0000911,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0000912,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0000913,	1,	-1,	-3,	0,	0x00FF00\r\n\
s: 0000914,	1,	1,	-3,	0,	0x00FF00\r\n\
s: 0000915,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 0000916,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0000917,	-1,	-1,	-3,	0,	0x00FF00\r\n\
s: 0000918,	-1,	1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0100911,	3,	1,	-1,	0,	0x00FF00\r\n\
s: 0100912,	3,	-1,	-1,	0,	0x00FF00\r\n\
s: 0100913,	3,	-1,	-3,	0,	0x00FF00\r\n\
s: 0100914,	3,	1,	-3,	0,	0x00FF00\r\n\
s: 0100915,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0100916,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0100917,	1,	-1,	-3,	0,	0x00FF00\r\n\
s: 0100918,	1,	1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 9100911,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 9100912,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 9100913,	-1,	-1,	-3,	0,	0x00FF00\r\n\
s: 9100914,	-1,	1,	-3,	0,	0x00FF00\r\n\
s: 9100915,	-3,	1,	-1,	0,	0x00FF00\r\n\
s: 9100916,	-3,	-1,	-1,	0,	0x00FF00\r\n\
s: 9100917,	-3,	-1,	-3,	0,	0x00FF00\r\n\
s: 9100918,	-3,	1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0001911,	1,	3,	-1,	0,	0x00FF00\r\n\
s: 0001912,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0001913,	1,	1,	-3,	0,	0x00FF00\r\n\
s: 0001914,	1,	3,	-3,	0,	0x00FF00\r\n\
s: 0001915,	-1,	3,	-1,	0,	0x00FF00\r\n\
s: 0001916,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 0001917,	-1,	1,	-3,	0,	0x00FF00\r\n\
s: 0001918,	-1,	3,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0091911,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0091912,	1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0091913,	1,	-3,	-3,	0,	0x00FF00\r\n\
s: 0091914,	1,	-1,	-3,	0,	0x00FF00\r\n\
s: 0091915,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0091916,	-1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0091917,	-1,	-3,	-3,	0,	0x00FF00\r\n\
s: 0091918,	-1,	-1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0101911,	3,	3,	-1,	0,	0x00FF00\r\n\
s: 0101912,	3,	1,	-1,	0,	0x00FF00\r\n\
s: 0101913,	3,	1,	-3,	0,	0x00FF00\r\n\
s: 0101914,	3,	3,	-3,	0,	0x00FF00\r\n\
s: 0101915,	1,	3,	-1,	0,	0x00FF00\r\n\
s: 0101916,	1,	1,	-1,	0,	0x00FF00\r\n\
s: 0101917,	1,	1,	-3,	0,	0x00FF00\r\n\
s: 0101918,	1,	3,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 9191911,	-1,	-1,	-1,	0,	0x00FF00\r\n\
s: 9191912,	-1,	-3,	-1,	0,	0x00FF00\r\n\
s: 9191913,	-1,	-3,	-3,	0,	0x00FF00\r\n\
s: 9191914,	-1,	-1,	-3,	0,	0x00FF00\r\n\
s: 9191915,	-3,	-1,	-1,	0,	0x00FF00\r\n\
s: 9191916,	-3,	-3,	-1,	0,	0x00FF00\r\n\
s: 9191917,	-3,	-3,	-3,	0,	0x00FF00\r\n\
s: 9191918,	-3,	-1,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 9101911,	-1,	3,	-1,	0,	0x00FF00\r\n\
s: 9101912,	-1,	1,	-1,	0,	0x00FF00\r\n\
s: 9101913,	-1,	1,	-3,	0,	0x00FF00\r\n\
s: 9101914,	-1,	3,	-3,	0,	0x00FF00\r\n\
s: 9101915,	-3,	3,	-1,	0,	0x00FF00\r\n\
s: 9101916,	-3,	1,	-1,	0,	0x00FF00\r\n\
s: 9101917,	-3,	1,	-3,	0,	0x00FF00\r\n\
s: 9101918,	-3,	3,	-3,	0,	0x00FF00\r\n\
\r\n\
s: 0191911,	3,	-1,	-1,	0,	0x00FF00\r\n\
s: 0191912,	3,	-3,	-1,	0,	0x00FF00\r\n\
s: 0191913,	3,	-3,	-3,	0,	0x00FF00\r\n\
s: 0191914,	3,	-1,	-3,	0,	0x00FF00\r\n\
s: 0191915,	1,	-1,	-1,	0,	0x00FF00\r\n\
s: 0191916,	1,	-3,	-1,	0,	0x00FF00\r\n\
s: 0191917,	1,	-3,	-3,	0,	0x00FF00\r\n\
s: 0191918,	1,	-1,	-3,	0,	0x00FF00\r\n\
\r\n\
l: 00000112,	0000011,	0000012,	1,	0x00FFFF\r\n\
l: 00000114,	0000011,	0000014,	1,	0x00FFFF\r\n\
l: 00000115,	0000011,	0000015,	1,	0x00FFFF\r\n\
l: 00000123,	0000012,	0000013,	1,	0x00FFFF\r\n\
l: 00000126,	0000012,	0000016,	1,	0x00FFFF\r\n\
l: 00000134,	0000013,	0000014,	1,	0xFFFF00\r\n\
l: 00000137,	0000013,	0000017,	1,	0xFFFF00\r\n\
l: 00000148,	0000014,	0000018,	1,	0xFFFF00\r\n\
l: 00000156,	0000015,	0000016,	1,	0x00FFFF\r\n\
l: 00000158,	0000015,	0000018,	1,	0x00FFFF\r\n\
l: 00000167,	0000016,	0000017,	1,	0x00FFFF\r\n\
l: 00000178,	0000017,	0000018,	1,	0xFFFF00\r\n\
l: 01000112,	0100011,	0100012,	1,	0x00FFFF\r\n\
l: 01000114,	0100011,	0100014,	1,	0x00FFFF\r\n\
l: 01000115,	0100011,	0100015,	1,	0x00FFFF\r\n\
l: 01000123,	0100012,	0100013,	1,	0x00FFFF\r\n\
l: 01000126,	0100012,	0100016,	1,	0x00FFFF\r\n\
l: 01000134,	0100013,	0100014,	1,	0x00FFFF\r\n\
l: 01000137,	0100013,	0100017,	1,	0x00FFFF\r\n\
l: 01000148,	0100014,	0100018,	1,	0x00FFFF\r\n\
l: 01000156,	0100015,	0100016,	1,	0x00FFFF\r\n\
l: 01000158,	0100015,	0100018,	1,	0x00FFFF\r\n\
l: 01000167,	0100016,	0100017,	1,	0x00FFFF\r\n\
l: 01000178,	0100017,	0100018,	1,	0x00FFFF\r\n\
l: 91000112,	9100011,	9100012,	1,	0x00FFFF\r\n\
l: 91000114,	9100011,	9100014,	1,	0x00FFFF\r\n\
l: 91000115,	9100011,	9100015,	1,	0x00FFFF\r\n\
l: 91000123,	9100012,	9100013,	1,	0x00FFFF\r\n\
l: 91000126,	9100012,	9100016,	1,	0x00FFFF\r\n\
l: 91000134,	9100013,	9100014,	1,	0x00FFFF\r\n\
l: 91000137,	9100013,	9100017,	1,	0x00FFFF\r\n\
l: 91000148,	9100014,	9100018,	1,	0x00FFFF\r\n\
l: 91000156,	9100015,	9100016,	1,	0x00FFFF\r\n\
l: 91000158,	9100015,	9100018,	1,	0x00FFFF\r\n\
l: 91000167,	9100016,	9100017,	1,	0x00FFFF\r\n\
l: 91000178,	9100017,	9100018,	1,	0x00FFFF\r\n\
l: 00010112,	0001011,	0001012,	1,	0x00FFFF\r\n\
l: 00010114,	0001011,	0001014,	1,	0x00FFFF\r\n\
l: 00010115,	0001011,	0001015,	1,	0x00FFFF\r\n\
l: 00010123,	0001012,	0001013,	1,	0x00FFFF\r\n\
l: 00010126,	0001012,	0001016,	1,	0x00FFFF\r\n\
l: 00010134,	0001013,	0001014,	1,	0x00FFFF\r\n\
l: 00010137,	0001013,	0001017,	1,	0x00FFFF\r\n\
l: 00010148,	0001014,	0001018,	1,	0x00FFFF\r\n\
l: 00010156,	0001015,	0001016,	1,	0x00FFFF\r\n\
l: 00010158,	0001015,	0001018,	1,	0x00FFFF\r\n\
l: 00010167,	0001016,	0001017,	1,	0x00FFFF\r\n\
l: 00010178,	0001017,	0001018,	1,	0x00FFFF\r\n\
l: 00910112,	0091011,	0091012,	1,	0x00FFFF\r\n\
l: 00910114,	0091011,	0091014,	1,	0x00FFFF\r\n\
l: 00910115,	0091011,	0091015,	1,	0x00FFFF\r\n\
l: 00910123,	0091012,	0091013,	1,	0x00FFFF\r\n\
l: 00910126,	0091012,	0091016,	1,	0x00FFFF\r\n\
l: 00910134,	0091013,	0091014,	1,	0x00FFFF\r\n\
l: 00910137,	0091013,	0091017,	1,	0x00FFFF\r\n\
l: 00910148,	0091014,	0091018,	1,	0x00FFFF\r\n\
l: 00910156,	0091015,	0091016,	1,	0x00FFFF\r\n\
l: 00910158,	0091015,	0091018,	1,	0x00FFFF\r\n\
l: 00910167,	0091016,	0091017,	1,	0x00FFFF\r\n\
l: 00910178,	0091017,	0091018,	1,	0x00FFFF\r\n\
l: 01010112,	0101011,	0101012,	1,	0x00FFFF\r\n\
l: 01010114,	0101011,	0101014,	1,	0x00FFFF\r\n\
l: 01010115,	0101011,	0101015,	1,	0x00FFFF\r\n\
l: 01010123,	0101012,	0101013,	1,	0x00FFFF\r\n\
l: 01010126,	0101012,	0101016,	1,	0x00FFFF\r\n\
l: 01010134,	0101013,	0101014,	1,	0x00FFFF\r\n\
l: 01010137,	0101013,	0101017,	1,	0x00FFFF\r\n\
l: 01010148,	0101014,	0101018,	1,	0x00FFFF\r\n\
l: 01010156,	0101015,	0101016,	1,	0x00FFFF\r\n\
l: 01010158,	0101015,	0101018,	1,	0x00FFFF\r\n\
l: 01010167,	0101016,	0101017,	1,	0x00FFFF\r\n\
l: 01010178,	0101017,	0101018,	1,	0x00FFFF\r\n\
l: 91910112,	9191011,	9191012,	1,	0x00FFFF\r\n\
l: 91910114,	9191011,	9191014,	1,	0x00FFFF\r\n\
l: 91910115,	9191011,	9191015,	1,	0x00FFFF\r\n\
l: 91910123,	9191012,	9191013,	1,	0x00FFFF\r\n\
l: 91910126,	9191012,	9191016,	1,	0x00FFFF\r\n\
l: 91910134,	9191013,	9191014,	1,	0x00FFFF\r\n\
l: 91910137,	9191013,	9191017,	1,	0x00FFFF\r\n\
l: 91910148,	9191014,	9191018,	1,	0x00FFFF\r\n\
l: 91910156,	9191015,	9191016,	1,	0x00FFFF\r\n\
l: 91910158,	9191015,	9191018,	1,	0x00FFFF\r\n\
l: 91910167,	9191016,	9191017,	1,	0x00FFFF\r\n\
l: 91910178,	9191017,	9191018,	1,	0x00FFFF\r\n\
l: 91010112,	9101011,	9101012,	1,	0x00FFFF\r\n\
l: 91010114,	9101011,	9101014,	1,	0x00FFFF\r\n\
l: 91010115,	9101011,	9101015,	1,	0x00FFFF\r\n\
l: 91010123,	9101012,	9101013,	1,	0x00FFFF\r\n\
l: 91010126,	9101012,	9101016,	1,	0x00FFFF\r\n\
l: 91010134,	9101013,	9101014,	1,	0x00FFFF\r\n\
l: 91010137,	9101013,	9101017,	1,	0x00FFFF\r\n\
l: 91010148,	9101014,	9101018,	1,	0x00FFFF\r\n\
l: 91010156,	9101015,	9101016,	1,	0x00FFFF\r\n\
l: 91010158,	9101015,	9101018,	1,	0x00FFFF\r\n\
l: 91010167,	9101016,	9101017,	1,	0x00FFFF\r\n\
l: 91010178,	9101017,	9101018,	1,	0x00FFFF\r\n\
l: 01910112,	0191011,	0191012,	1,	0x00FFFF\r\n\
l: 01910114,	0191011,	0191014,	1,	0x00FFFF\r\n\
l: 01910115,	0191011,	0191015,	1,	0x00FFFF\r\n\
l: 01910123,	0191012,	0191013,	1,	0x00FFFF\r\n\
l: 01910126,	0191012,	0191016,	1,	0x00FFFF\r\n\
l: 01910134,	0191013,	0191014,	1,	0x00FFFF\r\n\
l: 01910137,	0191013,	0191017,	1,	0x00FFFF\r\n\
l: 01910148,	0191014,	0191018,	1,	0x00FFFF\r\n\
l: 01910156,	0191015,	0191016,	1,	0x00FFFF\r\n\
l: 01910158,	0191015,	0191018,	1,	0x00FFFF\r\n\
l: 01910167,	0191016,	0191017,	1,	0x00FFFF\r\n\
l: 01910178,	0191017,	0191018,	1,	0x00FFFF\r\n\
l: 00000012,	0000001,	0000002,	1,	0xFFFF00\r\n\
l: 00000014,	0000001,	0000004,	1,	0xFFFF00\r\n\
l: 00000015,	0000001,	0000005,	1,	0xFFFF00\r\n\
l: 00000023,	0000002,	0000003,	1,	0xFFFF00\r\n\
l: 00000026,	0000002,	0000006,	1,	0xFFFF00\r\n\
l: 00000034,	0000003,	0000004,	1,	0xFFFF00\r\n\
l: 00000037,	0000003,	0000007,	1,	0xFFFF00\r\n\
l: 00000048,	0000004,	0000008,	1,	0xFFFF00\r\n\
l: 00000056,	0000005,	0000006,	1,	0xFFFF00\r\n\
l: 00000058,	0000005,	0000008,	1,	0xFFFF00\r\n\
l: 00000067,	0000006,	0000007,	1,	0xFFFF00\r\n\
l: 00000078,	0000007,	0000008,	1,	0xFFFF00\r\n\
l: 01000012,	0100001,	0100002,	1,	0x00FFFF\r\n\
l: 01000014,	0100001,	0100004,	1,	0x00FFFF\r\n\
l: 01000015,	0100001,	0100005,	1,	0x00FFFF\r\n\
l: 01000023,	0100002,	0100003,	1,	0x00FFFF\r\n\
l: 01000026,	0100002,	0100006,	1,	0x00FFFF\r\n\
l: 01000034,	0100003,	0100004,	1,	0x00FFFF\r\n\
l: 01000037,	0100003,	0100007,	1,	0x00FFFF\r\n\
l: 01000048,	0100004,	0100008,	1,	0x00FFFF\r\n\
l: 01000056,	0100005,	0100006,	1,	0x00FFFF\r\n\
l: 01000058,	0100005,	0100008,	1,	0x00FFFF\r\n\
l: 01000067,	0100006,	0100007,	1,	0x00FFFF\r\n\
l: 01000078,	0100007,	0100008,	1,	0x00FFFF\r\n\
l: 91000012,	9100001,	9100002,	1,	0x00FFFF\r\n\
l: 91000014,	9100001,	9100004,	1,	0x00FFFF\r\n\
l: 91000015,	9100001,	9100005,	1,	0x00FFFF\r\n\
l: 91000023,	9100002,	9100003,	1,	0x00FFFF\r\n\
l: 91000026,	9100002,	9100006,	1,	0x00FFFF\r\n\
l: 91000034,	9100003,	9100004,	1,	0x00FFFF\r\n\
l: 91000037,	9100003,	9100007,	1,	0x00FFFF\r\n\
l: 91000048,	9100004,	9100008,	1,	0x00FFFF\r\n\
l: 91000056,	9100005,	9100006,	1,	0x00FFFF\r\n\
l: 91000058,	9100005,	9100008,	1,	0x00FFFF\r\n\
l: 91000067,	9100006,	9100007,	1,	0x00FFFF\r\n\
l: 91000078,	9100007,	9100008,	1,	0x00FFFF\r\n\
l: 00010012,	0001001,	0001002,	1,	0x00FFFF\r\n\
l: 00010014,	0001001,	0001004,	1,	0x00FFFF\r\n\
l: 00010015,	0001001,	0001005,	1,	0x00FFFF\r\n\
l: 00010023,	0001002,	0001003,	1,	0x00FFFF\r\n\
l: 00010026,	0001002,	0001006,	1,	0x00FFFF\r\n\
l: 00010034,	0001003,	0001004,	1,	0x00FFFF\r\n\
l: 00010037,	0001003,	0001007,	1,	0x00FFFF\r\n\
l: 00010048,	0001004,	0001008,	1,	0x00FFFF\r\n\
l: 00010056,	0001005,	0001006,	1,	0x00FFFF\r\n\
l: 00010058,	0001005,	0001008,	1,	0x00FFFF\r\n\
l: 00010067,	0001006,	0001007,	1,	0x00FFFF\r\n\
l: 00010078,	0001007,	0001008,	1,	0x00FFFF\r\n\
l: 00910012,	0091001,	0091002,	1,	0x00FFFF\r\n\
l: 00910014,	0091001,	0091004,	1,	0x00FFFF\r\n\
l: 00910015,	0091001,	0091005,	1,	0x00FFFF\r\n\
l: 00910023,	0091002,	0091003,	1,	0x00FFFF\r\n\
l: 00910026,	0091002,	0091006,	1,	0x00FFFF\r\n\
l: 00910034,	0091003,	0091004,	1,	0x00FFFF\r\n\
l: 00910037,	0091003,	0091007,	1,	0x00FFFF\r\n\
l: 00910048,	0091004,	0091008,	1,	0x00FFFF\r\n\
l: 00910056,	0091005,	0091006,	1,	0x00FFFF\r\n\
l: 00910058,	0091005,	0091008,	1,	0x00FFFF\r\n\
l: 00910067,	0091006,	0091007,	1,	0x00FFFF\r\n\
l: 00910078,	0091007,	0091008,	1,	0x00FFFF\r\n\
l: 01010012,	0101001,	0101002,	1,	0x00FFFF\r\n\
l: 01010014,	0101001,	0101004,	1,	0x00FFFF\r\n\
l: 01010015,	0101001,	0101005,	1,	0x00FFFF\r\n\
l: 01010023,	0101002,	0101003,	1,	0x00FFFF\r\n\
l: 01010026,	0101002,	0101006,	1,	0x00FFFF\r\n\
l: 01010034,	0101003,	0101004,	1,	0x00FFFF\r\n\
l: 01010037,	0101003,	0101007,	1,	0x00FFFF\r\n\
l: 01010048,	0101004,	0101008,	1,	0x00FFFF\r\n\
l: 01010056,	0101005,	0101006,	1,	0x00FFFF\r\n\
l: 01010058,	0101005,	0101008,	1,	0x00FFFF\r\n\
l: 01010067,	0101006,	0101007,	1,	0x00FFFF\r\n\
l: 01010078,	0101007,	0101008,	1,	0x00FFFF\r\n\
l: 91910012,	9191001,	9191002,	1,	0x00FFFF\r\n\
l: 91910014,	9191001,	9191004,	1,	0x00FFFF\r\n\
l: 91910015,	9191001,	9191005,	1,	0x00FFFF\r\n\
l: 91910023,	9191002,	9191003,	1,	0x00FFFF\r\n\
l: 91910026,	9191002,	9191006,	1,	0x00FFFF\r\n\
l: 91910034,	9191003,	9191004,	1,	0x00FFFF\r\n\
l: 91910037,	9191003,	9191007,	1,	0x00FFFF\r\n\
l: 91910048,	9191004,	9191008,	1,	0x00FFFF\r\n\
l: 91910056,	9191005,	9191006,	1,	0x00FFFF\r\n\
l: 91910058,	9191005,	9191008,	1,	0x00FFFF\r\n\
l: 91910067,	9191006,	9191007,	1,	0x00FFFF\r\n\
l: 91910078,	9191007,	9191008,	1,	0x00FFFF\r\n\
l: 91010012,	9101001,	9101002,	1,	0x00FFFF\r\n\
l: 91010014,	9101001,	9101004,	1,	0x00FFFF\r\n\
l: 91010015,	9101001,	9101005,	1,	0x00FFFF\r\n\
l: 91010023,	9101002,	9101003,	1,	0x00FFFF\r\n\
l: 91010026,	9101002,	9101006,	1,	0x00FFFF\r\n\
l: 91010034,	9101003,	9101004,	1,	0x00FFFF\r\n\
l: 91010037,	9101003,	9101007,	1,	0x00FFFF\r\n\
l: 91010048,	9101004,	9101008,	1,	0x00FFFF\r\n\
l: 91010056,	9101005,	9101006,	1,	0x00FFFF\r\n\
l: 91010058,	9101005,	9101008,	1,	0x00FFFF\r\n\
l: 91010067,	9101006,	9101007,	1,	0x00FFFF\r\n\
l: 91010078,	9101007,	9101008,	1,	0x00FFFF\r\n\
l: 01910012,	0191001,	0191002,	1,	0x00FFFF\r\n\
l: 01910014,	0191001,	0191004,	1,	0x00FFFF\r\n\
l: 01910015,	0191001,	0191005,	1,	0x00FFFF\r\n\
l: 01910023,	0191002,	0191003,	1,	0x00FFFF\r\n\
l: 01910026,	0191002,	0191006,	1,	0x00FFFF\r\n\
l: 01910034,	0191003,	0191004,	1,	0x00FFFF\r\n\
l: 01910037,	0191003,	0191007,	1,	0x00FFFF\r\n\
l: 01910048,	0191004,	0191008,	1,	0x00FFFF\r\n\
l: 01910056,	0191005,	0191006,	1,	0x00FFFF\r\n\
l: 01910058,	0191005,	0191008,	1,	0x00FFFF\r\n\
l: 01910067,	0191006,	0191007,	1,	0x00FFFF\r\n\
l: 01910078,	0191007,	0191008,	1,	0x00FFFF\r\n\
l: 00009112,	0000911,	0000912,	1,	0xFFFF00\r\n\
l: 00009114,	0000911,	0000914,	1,	0x00FFFF\r\n\
l: 00009115,	0000911,	0000915,	1,	0x00FFFF\r\n\
l: 00009123,	0000912,	0000913,	1,	0x00FFFF\r\n\
l: 00009126,	0000912,	0000916,	1,	0x00FFFF\r\n\
l: 00009134,	0000913,	0000914,	1,	0x00FFFF\r\n\
l: 00009137,	0000913,	0000917,	1,	0x00FFFF\r\n\
l: 00009148,	0000914,	0000918,	1,	0x00FFFF\r\n\
l: 00009156,	0000915,	0000916,	1,	0x00FFFF\r\n\
l: 00009158,	0000915,	0000918,	1,	0x00FFFF\r\n\
l: 00009167,	0000916,	0000917,	1,	0x00FFFF\r\n\
l: 00009178,	0000917,	0000918,	1,	0x00FFFF\r\n\
l: 01009112,	0100911,	0100912,	1,	0x00FFFF\r\n\
l: 01009114,	0100911,	0100914,	1,	0x00FFFF\r\n\
l: 01009115,	0100911,	0100915,	1,	0x00FFFF\r\n\
l: 01009123,	0100912,	0100913,	1,	0x00FFFF\r\n\
l: 01009126,	0100912,	0100916,	1,	0x00FFFF\r\n\
l: 01009134,	0100913,	0100914,	1,	0x00FFFF\r\n\
l: 01009137,	0100913,	0100917,	1,	0x00FFFF\r\n\
l: 01009148,	0100914,	0100918,	1,	0x00FFFF\r\n\
l: 01009156,	0100915,	0100916,	1,	0xFFFF00\r\n\
l: 01009158,	0100915,	0100918,	1,	0x00FFFF\r\n\
l: 01009167,	0100916,	0100917,	1,	0x00FFFF\r\n\
l: 01009178,	0100917,	0100918,	1,	0x00FFFF\r\n\
l: 91009112,	9100911,	9100912,	1,	0x00FFFF\r\n\
l: 91009114,	9100911,	9100914,	1,	0x00FFFF\r\n\
l: 91009115,	9100911,	9100915,	1,	0x00FFFF\r\n\
l: 91009123,	9100912,	9100913,	1,	0x00FFFF\r\n\
l: 91009126,	9100912,	9100916,	1,	0x00FFFF\r\n\
l: 91009134,	9100913,	9100914,	1,	0x00FFFF\r\n\
l: 91009137,	9100913,	9100917,	1,	0x00FFFF\r\n\
l: 91009148,	9100914,	9100918,	1,	0x00FFFF\r\n\
l: 91009156,	9100915,	9100916,	1,	0x00FFFF\r\n\
l: 91009158,	9100915,	9100918,	1,	0x00FFFF\r\n\
l: 91009167,	9100916,	9100917,	1,	0x00FFFF\r\n\
l: 91009178,	9100917,	9100918,	1,	0x00FFFF\r\n\
l: 00019112,	0001911,	0001912,	1,	0x00FFFF\r\n\
l: 00019114,	0001911,	0001914,	1,	0x00FFFF\r\n\
l: 00019115,	0001911,	0001915,	1,	0x00FFFF\r\n\
l: 00019123,	0001912,	0001913,	1,	0x00FFFF\r\n\
l: 00019126,	0001912,	0001916,	1,	0x00FFFF\r\n\
l: 00019134,	0001913,	0001914,	1,	0x00FFFF\r\n\
l: 00019137,	0001913,	0001917,	1,	0x00FFFF\r\n\
l: 00019148,	0001914,	0001918,	1,	0x00FFFF\r\n\
l: 00019156,	0001915,	0001916,	1,	0x00FFFF\r\n\
l: 00019158,	0001915,	0001918,	1,	0x00FFFF\r\n\
l: 00019167,	0001916,	0001917,	1,	0x00FFFF\r\n\
l: 00019178,	0001917,	0001918,	1,	0x00FFFF\r\n\
l: 00919112,	0091911,	0091912,	1,	0x00FFFF\r\n\
l: 00919114,	0091911,	0091914,	1,	0x00FFFF\r\n\
l: 00919115,	0091911,	0091915,	1,	0x00FFFF\r\n\
l: 00919123,	0091912,	0091913,	1,	0x00FFFF\r\n\
l: 00919126,	0091912,	0091916,	1,	0x00FFFF\r\n\
l: 00919134,	0091913,	0091914,	1,	0x00FFFF\r\n\
l: 00919137,	0091913,	0091917,	1,	0x00FFFF\r\n\
l: 00919148,	0091914,	0091918,	1,	0x00FFFF\r\n\
l: 00919156,	0091915,	0091916,	1,	0x00FFFF\r\n\
l: 00919158,	0091915,	0091918,	1,	0x00FFFF\r\n\
l: 00919167,	0091916,	0091917,	1,	0x00FFFF\r\n\
l: 00919178,	0091917,	0091918,	1,	0x00FFFF\r\n\
l: 01019112,	0101911,	0101912,	1,	0x00FFFF\r\n\
l: 01019114,	0101911,	0101914,	1,	0x00FFFF\r\n\
l: 01019115,	0101911,	0101915,	1,	0x00FFFF\r\n\
l: 01019123,	0101912,	0101913,	1,	0x00FFFF\r\n\
l: 01019126,	0101912,	0101916,	1,	0x00FFFF\r\n\
l: 01019134,	0101913,	0101914,	1,	0x00FFFF\r\n\
l: 01019137,	0101913,	0101917,	1,	0x00FFFF\r\n\
l: 01019148,	0101914,	0101918,	1,	0x00FFFF\r\n\
l: 01019156,	0101915,	0101916,	1,	0x00FFFF\r\n\
l: 01019158,	0101915,	0101918,	1,	0x00FFFF\r\n\
l: 01019167,	0101916,	0101917,	1,	0x00FFFF\r\n\
l: 01019178,	0101917,	0101918,	1,	0x00FFFF\r\n\
l: 91919112,	9191911,	9191912,	1,	0x00FFFF\r\n\
l: 91919114,	9191911,	9191914,	1,	0x00FFFF\r\n\
l: 91919115,	9191911,	9191915,	1,	0x00FFFF\r\n\
l: 91919123,	9191912,	9191913,	1,	0x00FFFF\r\n\
l: 91919126,	9191912,	9191916,	1,	0x00FFFF\r\n\
l: 91919134,	9191913,	9191914,	1,	0x00FFFF\r\n\
l: 91919137,	9191913,	9191917,	1,	0x00FFFF\r\n\
l: 91919148,	9191914,	9191918,	1,	0x00FFFF\r\n\
l: 91919156,	9191915,	9191916,	1,	0x00FFFF\r\n\
l: 91919158,	9191915,	9191918,	1,	0x00FFFF\r\n\
l: 91919167,	9191916,	9191917,	1,	0x00FFFF\r\n\
l: 91919178,	9191917,	9191918,	1,	0x00FFFF\r\n\
l: 91019112,	9101911,	9101912,	1,	0x00FFFF\r\n\
l: 91019114,	9101911,	9101914,	1,	0x00FFFF\r\n\
l: 91019115,	9101911,	9101915,	1,	0x00FFFF\r\n\
l: 91019123,	9101912,	9101913,	1,	0x00FFFF\r\n\
l: 91019126,	9101912,	9101916,	1,	0x00FFFF\r\n\
l: 91019134,	9101913,	9101914,	1,	0x00FFFF\r\n\
l: 91019137,	9101913,	9101917,	1,	0x00FFFF\r\n\
l: 91019148,	9101914,	9101918,	1,	0x00FFFF\r\n\
l: 91019156,	9101915,	9101916,	1,	0x00FFFF\r\n\
l: 91019158,	9101915,	9101918,	1,	0x00FFFF\r\n\
l: 91019167,	9101916,	9101917,	1,	0x00FFFF\r\n\
l: 91019178,	9101917,	9101918,	1,	0x00FFFF\r\n\
l: 01919112,	0191911,	0191912,	1,	0x00FFFF\r\n\
l: 01919114,	0191911,	0191914,	1,	0x00FFFF\r\n\
l: 01919115,	0191911,	0191915,	1,	0x00FFFF\r\n\
l: 01919123,	0191912,	0191913,	1,	0x00FFFF\r\n\
l: 01919126,	0191912,	0191916,	1,	0x00FFFF\r\n\
l: 01919134,	0191913,	0191914,	1,	0x00FFFF\r\n\
l: 01919137,	0191913,	0191917,	1,	0x00FFFF\r\n\
l: 01919148,	0191914,	0191918,	1,	0x00FFFF\r\n\
l: 01919156,	0191915,	0191916,	1,	0x00FFFF\r\n\
l: 01919158,	0191915,	0191918,	1,	0x00FFFF\r\n\
l: 01919167,	0191916,	0191917,	1,	0x00FFFF\r\n\
l: 01919178,	0191917,	0191918,	1,	0x00FFFF\r\n\
        ";
    }



    //запись в файл
    if(strContent!= "")
    {
        AnsiString strDir = GetCurrentDir();
        strDir += "\\Samples";
        if(bSplit == true)
		{
			int nLnk = k.Adg1+1;
			AnsiString strAddDir;
			strDir+="\\" + IntToStr(nLnk);
			if(strAddDir != "")
			{
                strDir+="\\" + strAddDir;
            }
        }
        if(DirectoryExists(strDir) == false)
        {
         ForceDirectories(strDir);
		}

		int hFile = FileCreate(strDir + "\\" + strFileName);
        if(hFile != -1)
        {
            FileWrite(hFile, strContent.c_str(), strContent.Length());
            FileClose(hFile);
		}
    }
}
//---------------------------------------------------------------------------

