//---------------------------------------------------------------------------

#ifndef BaseProbSetUnitH
#define BaseProbSetUnitH
//---------------------------------------------------------------------------
#include <vcl.h>

//---------------------------------------------------------------------------
#define AS_MAX_ATOM_NUM 53
#define AS_MAX_SHEMA (AS_MAX_ATOM_NUM/(sizeof(DWORD)*8)+1)
//---------------------------------------------------------------------------
//��������� ������ �����������
#define PI_ERROR -1
//---------------------------------------------------------------------------
//��� ��� ������� �����������
typedef int TProbIndex;
//---------------------------------------------------------------------------
//��������� ������� � ���������
//�������� �����
#define GetIndex0LevAdj() 0
//������ ������� �������� �����
int GetIndex1LevAdj(int nNum1LevAdv);
//������ ������� �������� �����
int GetIndex2LevAdj(int nNum1LevAdv, int nNum2LevAdv);
//������� ������� �������� �����
int GetIndex3LevAdj(int nNum1LevAdv, int nNum2LevAdv, int nNum3LevAdv);
//---------------------------------------------------------------------------
//����� ������������ ������ ������ �������� ����� (���������)
class TAtomShema
{
private:
	DWORD m_Shema[AS_MAX_SHEMA];

public:
	TAtomShema();
	TAtomShema(const TAtomShema &r);

	TAtomShema& operator = (const TAtomShema &r);

	int GetBit(int nIndex);//1-���� ����, 0 - ���� �����
	void SetBit(int nIndex, int nState);//1-���� ����, 0 - ���� �����

	void Clear(void);//���������� �����

	AnsiString ToStr(void);//���������� � ���� ������
	AnsiString ToStr2(void);//���������� � ���� ������

	int m_nMaxLayer;//�� ������ �������� ������ ������� �����
	//-1  - ����� �� ������������
	// 0  - ������� ����
	// 1  - ������ ������
	// 2  - ������ ������
	// 3  - ������ ������
};
//---------------------------------------------------------------------------


class IBaseProbSet;
/*
 * ���������� ������ ������ ������������
 */
class IBaseProbSetGlobalData
{
protected:
	AnsiString m_IdString;
	AnsiString m_NameString;
	AnsiString m_DiscrptionString;

	bool m_bInit;//����� ������������������
	int  m_nAllNumProbality;//���������� ������������
	int  m_nNumLayerAtomShema;//���������� ���� �� �������� ������ ���� ������� ���������
	CRITICAL_SECTION m_InitCS;//����������� ������ �������������
	AnsiString* m_pstrProbName;//�������� ������������
	double* m_pdDefaultProbArr;//����������� �� ���������

	friend class IBaseProbSet;
	virtual void Init(void) = 0;//������������� ���������� ������
	//�������� ����� ������������� (�������� ������ ������ ������������)
	virtual bool FillDefaultProb(double* pdProbArr);//���������� ������������� �� ���������
public:
	IBaseProbSetGlobalData();
	~IBaseProbSetGlobalData();

	virtual const AnsiString& GetProbSetIdString();//��������� ����������������� ������ ������ �����������
	virtual const AnsiString& GetProbSetNameString();//��������� �������� ������ �����������
	virtual const AnsiString& GetProbSetDiscrptionString();//��������� ������ �������� ������ �����������

	//�������� ����� ������������� (�������� ������ ������ ������������)
	virtual int GetAllNumProbality(void);//���������� ���������� ������������ ������������ � ������
	virtual AnsiString GetProbName(int Index);//��������� �������� (�����) �����������
	virtual int GetMainAtomTypeForProb(int Index) = 0;//��������� ���� �������� ����� ��� ������ �����������
	virtual TProbIndex GetProbIndexFromAtomShema(TAtomShema &as) = 0;//��������� ������� �� ������ ��� ������� ������������ ������
	virtual int GetNumLayerAtomShema();//��������� ���������� ���� �� �������� ������ ���� ������� ���������
	virtual int Get_nS_CountForProb(int Index);//��������� ���������� �������� ������ ������� ��� ������ �����������
};
//---------------------------------------------------------------------------
/*
 * ����������� ����� ��������� ������ ������������
 */
class IBaseProbSetCreator
{
protected:
    IBaseProbSetGlobalData &m_GlobalData;
    IBaseProbSetCreator(IBaseProbSetGlobalData &GlobalData);
public:
    virtual IBaseProbSet* Create() = 0;//�������� ������ ������������
    virtual IBaseProbSetGlobalData& GetInfo();
};
//---------------------------------------------------------------------------
//��������� ������ ������������
class IBaseProbSet
{
private:
protected:
	IBaseProbSetCreator& m_Creator;
	IBaseProbSetGlobalData &m_GD;
    double *m_pdProbArr;
    IBaseProbSet(IBaseProbSetCreator& Creator);

    friend class TProbPovider;

    virtual bool SaveToFile(HANDLE hFile);
    virtual bool LoadFromFile(HANDLE hFile);
public:
//    virtual int GetAllNumProbality(void) = 0;//���������� ���������� ������������ ������������ � ������
//    virtual AnsiString GetProbName(int Index) = 0;//��������� �������� (�����) �����������
    virtual double GetProbValue(int Index);//��������� �������� �����������
    virtual void SetProbValue(int Index, double dProbVal);//��������� �������� �����������
//    virtual int GetProbIndexFromAtomShema(TAtomShema &as) = 0;//��������� ������� �� ������ ��� ������� ������������ ������
//    virtual int GetNumLayerAtomShema() = 0;//��������� ���������� ���� �� �������� ������ ���� ������� ���������
//    virtual AnsiString GetProbSetIdString() = 0;//��������� ����������������� ������ ������ �����������
    virtual bool FillDefault(void);//��������� �������� ����������� �� ���������
    virtual bool Copy(IBaseProbSet& ProbSet);//��������� �������� ����������� �� ������� ����� �������� ������


    virtual IBaseProbSetCreator& GetCreator(void);//��������� ��������� �� ����� ���������
    virtual IBaseProbSetGlobalData& GetGlobalData(void);//��������� ������ �� ���� ���������� ������ ��� ����� ������

    virtual ~IBaseProbSet();//
};
//---------------------------------------------------------------------------
#endif
