//---------------------------------------------------------------------------

#ifndef ProbPoviderUnitH
#define ProbPoviderUnitH
//---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
#include <vector>
//---------------------------------------------------------------------------
typedef std::vector<IBaseProbSetCreator*> TProbSetCreatorVector;
//---------------------------------------------------------------------------
/*
 * ������ ����������� ����������
 */
class TProbPoviderGlobal
{
public:
	TProbPoviderGlobal();
	~TProbPoviderGlobal();

	TProbSetCreatorVector m_vProbSetCreator;
};


/*
 * ��������� � ���������� ������ ������������
 */
class TProbPovider
{
private:
	IBaseProbSet *pCurrInterface;
public:
	TProbPovider();
	TProbPovider(const TProbPovider &r);
	TProbPovider& operator=(const TProbPovider &r);

	IBaseProbSet *GetInterface(void) const;//��������� ��������� �� ��������� ������ ������������

	void CreateInterfaceByIdString(AnsiString strIdString);//������� ��������� ������ ������������ �� ��� ����
	void ClearInterface();//������� ��������� ������ ������������


	//������������ ��������� ������������
	int EnumirateGetCount();//������������ ���������� �����������
	AnsiString EnumirateGetIdString(unsigned int nIndex);//��������� ���� ���������� �� �������
	AnsiString EnumirateGetName(unsigned int nIndex);//��������� ����� ���������� �� �������
	AnsiString EnumirateGetDiscrption(unsigned int nIndex);//��������� �������� ���������� �� �������

	bool SaveToFile(AnsiString strFileName);//��������� ������� ����� ������������ � ����
    bool LoadFromFile(AnsiString strFileName);//��������� ����� ������������ �� �����

    bool SaveToFile(HANDLE hFile, int *pSeek = NULL);//��������� ������� ����� ������������ � �����
    bool LoadFromFile(HANDLE hFile, int *pSeek = NULL);//��������� ����� ������������ �� �����

    ~TProbPovider();
};
//---------------------------------------------------------------------------
#endif
