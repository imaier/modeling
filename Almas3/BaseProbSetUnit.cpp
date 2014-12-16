//---------------------------------------------------------------------------
#pragma hdrstop

#include "BaseProbSetUnit.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
//��������� ������� � �����
//������ ������� �������� �����
int GetIndex1LevAdj(int nNum1LevAdv)
{
	return (1+ nNum1LevAdv);
}
//---------------------------------------------------------------------------
//��������� ������� � �����
//������ ������� �������� �����
int GetIndex2LevAdj(int nNum1LevAdv, int nNum2LevAdv)
{
	return (1+4+ nNum1LevAdv*3+nNum2LevAdv*1);
}
//---------------------------------------------------------------------------
//��������� ������� � �����
//������� ������� �������� �����
int GetIndex3LevAdj(int nNum1LevAdv, int nNum2LevAdv, int nNum3LevAdv)
{
	return (1+4+12+ nNum1LevAdv*9+nNum2LevAdv*3+nNum3LevAdv*1);
}
//---------------------------------------------------------------------------
TAtomShema::TAtomShema()
{
    Clear();
}
//---------------------------------------------------------------------------
void TAtomShema::Clear(void)
{//���������� �����
	UINT i;
	for(i = 0; i < AS_MAX_SHEMA; i++)
	{
		m_Shema[i] = 0;
	}

	m_nMaxLayer = -1;
}
//---------------------------------------------------------------------------
TAtomShema::TAtomShema(const TAtomShema &r)
{
	*this = r;
}
//---------------------------------------------------------------------------
TAtomShema& TAtomShema::operator = (const TAtomShema &r)
{
	UINT i;
	for(i =0; i<AS_MAX_SHEMA; i++)
    {
        m_Shema[i] = r.m_Shema[i];
    }

    m_nMaxLayer = r.m_nMaxLayer;
    return *this;
}
//---------------------------------------------------------------------------
int TAtomShema::GetBit(int nIndex)
{//1-���� ����, 0 - ���� �����
    int nState = -1;
	int nElemSize = (sizeof(m_Shema[0])*8);
	int nShemIndex = nIndex / nElemSize;
	int nIndexInElem = nIndex % nElemSize;
	int nMask = 1 << nIndexInElem;
	if((UINT)nShemIndex < AS_MAX_SHEMA)
    {
		nState = 0;
		if((m_Shema[nShemIndex] & nMask) > 0)
		{
			nState = 1;
        }
	}
    else
	{
		throw Exception("TAtomShema::GetBit = ����� �� ������� ���������.");
	}
	return nState;
}
//---------------------------------------------------------------------------
void TAtomShema::SetBit(int nIndex, int nState)
{//1-���� ����, 0 - ���� �����
	int nElemSize = (sizeof(m_Shema[0])*8);
	int nShemIndex = nIndex / nElemSize;
	int nIndexInElem = nIndex % nElemSize;
	int nMask = 1 << nIndexInElem;
	if((UINT)nShemIndex < AS_MAX_SHEMA)
	{
		m_Shema[nShemIndex] &= ~nMask;//�������� ���
		if(nState == 1)
		{
			m_Shema[nShemIndex] |= nMask;//���������� ���
		}
	}
	else
	{
		throw Exception("TAtomShema::SetBit = ����� �� ������� ���������.");
	}
}
//---------------------------------------------------------------------------
AnsiString TAtomShema::ToStr(void)
{//���������� � ���� ������
	AnsiString strRet;

	//long nLayer3Spacing = 1;
	//long nLayer2Spacing = (nLayer3Spacing)*3;
	//long nLayer1Spacing = (nLayer2Spacing)*3;
	//long nLayer0Spacing = (nLayer1Spacing)*4;


	const int nCount = 4;
	long nLayerSpacing[nCount];
	AnsiString strLayerFmt[nCount];
	AnsiString strLayer[nCount];
	AnsiString strTmp;

	int i, j, k;
	nLayerSpacing[nCount-1] = 1;
	for(i = nCount-2; i >= 0; i--)
	{
	 nLayerSpacing[i] = (nLayerSpacing[i+1])*(3 + (i==0?1:0));
	}
	for(i = 0; i < nCount; i++)
	{
	 if(nLayerSpacing[i] == 0)
		strLayerFmt[i].sprintf("%%d");
	 else
		strLayerFmt[i].sprintf("%%%dd", nLayerSpacing[i]+1);
	}
	int l=0;
	strLayer[l].sprintf(_c_str(strLayerFmt[l]), GetBit(GetIndex0LevAdj()));
	if(m_nMaxLayer > l)
	for(i = 0; i < 4; i++)
	{
	 l=1;
	 strLayer[l] +=  strTmp.sprintf(_c_str(strLayerFmt[l]), GetBit(GetIndex1LevAdj(i)));
	 if(m_nMaxLayer > l)
	 for(j = 0; j < 3; j++)
	 {
	  l=2;
	  strLayer[l] +=  strTmp.sprintf(_c_str(strLayerFmt[l]), GetBit(GetIndex2LevAdj(i,j)));
	  if(m_nMaxLayer > l)
	  for(k = 0; k < 3; k++)
	  {
	   l=3;
	   strLayer[l] +=  strTmp.sprintf(_c_str(strLayerFmt[l]), GetBit(GetIndex3LevAdj(i,j,k)));
	  }
	 }
	}

	strTmp = "";
	for(i = 0; i < nCount; i++)
	{
	 if (strTmp.Length() > 0)
	 {
	  strTmp += "\r\n";
	 }
	 strTmp += strLayer[i];

	 if(i == m_nMaxLayer)
	 {
	  if (strTmp.Length() > 0)
	  {
	   strTmp += "\r\n";
	  }
	  strTmp += "----------------------------------";
	 }
	}
	return strTmp;
}
//---------------------------------------------------------------------------
AnsiString TAtomShema::ToStr2(void)
{//���������� � ���� ������
	AnsiString strRet;

	//long nLayer3Spacing = 1;
	//long nLayer2Spacing = (nLayer3Spacing)*3;
	//long nLayer1Spacing = (nLayer2Spacing)*3;
	//long nLayer0Spacing = (nLayer1Spacing)*4;


	const int nCount = 4;
	long nLayerSpacing[nCount];
	AnsiString strLayerFmt[nCount];
	AnsiString strLayer[nCount];
	AnsiString strTmp;

	int i, j, k;
	nLayerSpacing[nCount-1] = 1;
	for(i = nCount-2; i >= 0; i--)
	{
	 nLayerSpacing[i] = (nLayerSpacing[i+1])*(3 + (i==0?1:0));
	}
	for(i = 0; i < nCount; i++)
	{
	 if(nLayerSpacing[i] == 0)
		strLayerFmt[i].sprintf("%%d");
	 else
		strLayerFmt[i].sprintf("%%%dd", nLayerSpacing[i]+1);
	}
	int l=0;
	strLayer[l].sprintf(_c_str(strLayerFmt[l]), GetBit(GetIndex0LevAdj()));
	if(m_nMaxLayer > l)
	for(i = 0; i < 4; i++)
	{
	 l=1;
	 strRet += strTmp.sprintf("(%d:%d",i+1, GetBit(GetIndex1LevAdj(i)));
	 strLayer[l] +=  strTmp.sprintf(_c_str(strLayerFmt[l]), GetBit(GetIndex1LevAdj(i)));
	 if(m_nMaxLayer > l)
	 {
	  strRet += strTmp.sprintf("[");
	  for(j = 0; j < 3; j++)
	  {
	   l=2;
	   strRet += strTmp.sprintf("%d",GetBit(GetIndex2LevAdj(i,j)));
	   strLayer[l] +=  strTmp.sprintf(_c_str(strLayerFmt[l]), GetBit(GetIndex2LevAdj(i,j)));
	   if(m_nMaxLayer > l)
	   {
		strRet += strTmp.sprintf("{");
		for(k = 0; k < 3; k++)
		{
		 l=3;
		 strRet += strTmp.sprintf("%d",GetBit(GetIndex3LevAdj(i,j,k)));
		 strLayer[l] +=  strTmp.sprintf(_c_str(strLayerFmt[l]), GetBit(GetIndex3LevAdj(i,j,k)));
		}
		strRet += strTmp.sprintf("}");
		}
	   }
	   strRet += strTmp.sprintf("]");
	  }
	 strRet += strTmp.sprintf(")");
	}

	strTmp = "";
	for(i = 0; i < nCount; i++)
	{
	 if (strTmp.Length() > 0)
	 {
	  strTmp += "\r\n";
	 }
	 strTmp += strLayer[i];

	 if(i == m_nMaxLayer)
	 {
	  if (strTmp.Length() > 0)
	  {
	   strTmp += "\r\n";
	  }
	  strTmp += "----------------------------------";
	 }
	}
	return strRet;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
IBaseProbSetGlobalData::IBaseProbSetGlobalData()
{
	m_bInit = false;
	m_nAllNumProbality =0;
	m_pstrProbName = NULL;
	m_pdDefaultProbArr = NULL;
	InitializeCriticalSection(&m_InitCS);
}
//---------------------------------------------------------------------------
IBaseProbSetGlobalData::~IBaseProbSetGlobalData()
{
    if(m_bInit == true)
    {
     if(m_pstrProbName!=NULL)
     {
      delete [] m_pstrProbName;
      //m_pstrProbName = NULL;
     }
     if(m_pdDefaultProbArr!=NULL)
     {
      delete [] m_pdDefaultProbArr;
      //m_pdDefaultProbArr = NULL;
     }
    }
    DeleteCriticalSection(&m_InitCS);
}
//---------------------------------------------------------------------------
const AnsiString& IBaseProbSetGlobalData::GetProbSetIdString()
{//��������� ����������������� ������ ������ �����������
    return m_IdString;
}
//---------------------------------------------------------------------------
const AnsiString& IBaseProbSetGlobalData::GetProbSetNameString()
{//��������� �������� ������ �����������
    return  m_NameString;
}
//---------------------------------------------------------------------------
const AnsiString& IBaseProbSetGlobalData::GetProbSetDiscrptionString()
{//��������� ������ �������� ������ �����������
	return  m_DiscrptionString;
}
bool IBaseProbSetGlobalData::FillDefaultProb(double* pdProbArr)
{//���������� ������������� �� ���������
	bool bRet = false;
	if(m_bInit == true)
	{
	 memcpy(pdProbArr, m_pdDefaultProbArr, m_nAllNumProbality*sizeof(double));
	 bRet = true;
	}
	return bRet;
}
//---------------------------------------------------------------------------
int IBaseProbSetGlobalData::GetAllNumProbality(void)
{//���������� ���������� ������������ ������������ � ������
	return m_nAllNumProbality;
}
//---------------------------------------------------------------------------
AnsiString IBaseProbSetGlobalData::GetProbName(int Index)
{//��������� �������� (�����) �����������
	AnsiString strRet = "�����";
	if(Index>=0 && Index < m_nAllNumProbality)
	{
	 if(m_pstrProbName != NULL)
	 {
	  strRet = m_pstrProbName[Index];
	 }
	 else
	 {
	  strRet = "�������� �� ������";
	 }
	}
	else
	{
	 strRet = "��� ���������";
	}
	return strRet;
}
//---------------------------------------------------------------------------
int IBaseProbSetGlobalData::GetNumLayerAtomShema()
{//��������� ���������� ���� �� �������� ������ ���� ������� ���������
	return m_nNumLayerAtomShema;
}
//---------------------------------------------------------------------------
int IBaseProbSetGlobalData::Get_nS_CountForProb(int Index)
{//��������� ���������� �������� ������ ������� ��� ������ �����������
	return -1;
}
//---------------------------------------------------------------------------
IBaseProbSetCreator::IBaseProbSetCreator(IBaseProbSetGlobalData &GlobalData):
m_GlobalData(GlobalData)
{
}
//---------------------------------------------------------------------------
IBaseProbSetGlobalData& IBaseProbSetCreator::GetInfo()
{
    return m_GlobalData;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
IBaseProbSet::IBaseProbSet(IBaseProbSetCreator& Creator)
:m_Creator(Creator), m_GD(Creator.GetInfo()), m_pdProbArr(NULL)
{
	m_GD.Init();
    int nCnt = m_GD.GetAllNumProbality();
    m_pdProbArr = new double[nCnt];
	memset(m_pdProbArr, 0, nCnt*sizeof(double));
	//m_GD.FillDefaultProb(m_pdProbArr);//��������� ���������� �������������
}
//---------------------------------------------------------------------------
IBaseProbSet::~IBaseProbSet()
{
	delete [] m_pdProbArr;
}
//---------------------------------------------------------------------------
IBaseProbSetCreator& IBaseProbSet::GetCreator(void)
{//��������� ��������� �� ����� ���������
	return m_Creator;
}
//---------------------------------------------------------------------------
bool IBaseProbSet::FillDefault(void)
{//��������� �������� ����������� �� ���������
	return m_GD.FillDefaultProb(m_pdProbArr);//��������� ���������� �������������
}
//---------------------------------------------------------------------------
bool IBaseProbSet::Copy(IBaseProbSet& ProbSet)
{//��������� �������� ����������� �� ������� ����� �������� ������
    bool bRet = false;
    if(m_GD.GetProbSetIdString() == ProbSet.m_GD.GetProbSetIdString())
    {
     int nCnt = m_GD.GetAllNumProbality();
     memcpy(m_pdProbArr, ProbSet.m_pdProbArr, nCnt*sizeof(double));
     bRet = true;
    }
    return bRet;
}
//---------------------------------------------------------------------------
double IBaseProbSet::GetProbValue(int Index)
{//��������� �������� �����������
    int nCnt = m_GD.GetAllNumProbality();
	if(Index < 0 || Index >= nCnt)
	{
		throw Exception("����� �� ������� �������");
	}
	return m_pdProbArr[Index];
}
//---------------------------------------------------------------------------
void IBaseProbSet::SetProbValue(int Index, double dProbVal)
{//��������� �������� �����������
	int nCnt = m_GD.GetAllNumProbality();
	if(Index < 0 || Index >= nCnt)
	{
		throw Exception("����� �� ������� �������");
	}
	if(dProbVal < 0)
	{
		throw Exception("������������� �������� ����������� �����������.");
    }
    m_pdProbArr[Index] = dProbVal;
}
//---------------------------------------------------------------------------
bool IBaseProbSet::SaveToFile(HANDLE hFile)
{
	bool bRet = false;
	int nCnt = m_GD.GetAllNumProbality();
	DWORD nNumberOfBytesToWrite = nCnt*sizeof(m_pdProbArr[0]);
    DWORD nNumberOfBytesWritten=0;
    BOOL nRet = WriteFile(
     hFile,	                // handle to file to write to
     m_pdProbArr,	        // pointer to data to write to file
     nNumberOfBytesToWrite,	// number of bytes to write
     &nNumberOfBytesWritten,// pointer to number of bytes written
	 NULL 	                // pointer to structure needed for overlapped I/O
	 );
    bRet = (nRet != FALSE);
    return bRet;
}
//---------------------------------------------------------------------------
bool IBaseProbSet::LoadFromFile(HANDLE hFile)
{
	bool bRet = false;
	int nCnt = m_GD.GetAllNumProbality();
	DWORD nNumberOfBytesToRead = nCnt*sizeof(m_pdProbArr[0]);
	DWORD nNumberOfBytesRead = 0;
	BOOL nRet = ReadFile(
	 hFile,	                // handle of file to read
	 m_pdProbArr,	        // address of buffer that receives data
	 nNumberOfBytesToRead,	// number of bytes to read
	 &nNumberOfBytesRead,	// address of number of bytes read
	 NULL 	                // address of structure for data
	);
	bRet = (nRet != FALSE);
	return bRet;
}
//---------------------------------------------------------------------------
IBaseProbSetGlobalData& IBaseProbSet::GetGlobalData(void)
{//��������� ������ �� ���� ���������� ������ ��� ����� ������
	return m_GD;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
