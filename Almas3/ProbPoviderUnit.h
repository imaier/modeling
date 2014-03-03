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
 * Список интерфейсов провайдера
 */
class TProbPoviderGlobal
{
public:
	TProbPoviderGlobal();
	~TProbPoviderGlobal();

	TProbSetCreatorVector m_vProbSetCreator;
};


/*
 * Провайдер к интерфейсу набора вероятностей
 */
class TProbPovider
{
private:
	IBaseProbSet *pCurrInterface;
public:
	TProbPovider();
	TProbPovider(const TProbPovider &r);
	TProbPovider& operator=(const TProbPovider &r);

	IBaseProbSet *GetInterface(void) const;//получение указателя на интерфейс набора вероятностей

	void CreateInterfaceByIdString(AnsiString strIdString);//создать интерфейс набора вероятностей по его уину
	void ClearInterface();//удалить интерфейс набора вероятностей


	//Перечисление возможных интерефейсов
	int EnumirateGetCount();//максимальное количество интерфейсов
	AnsiString EnumirateGetIdString(unsigned int nIndex);//получение уина интерфейса по индексу
	AnsiString EnumirateGetName(unsigned int nIndex);//получение имени интерфейса по индексу
	AnsiString EnumirateGetDiscrption(unsigned int nIndex);//получение описания интерфейса по индексу

	bool SaveToFile(AnsiString strFileName);//сохранить текущий набор вероятностей в файл
    bool LoadFromFile(AnsiString strFileName);//загрузить набор вероятностей из файла

    bool SaveToFile(HANDLE hFile, int *pSeek = NULL);//сохранить текущий набор вероятностей в поток
    bool LoadFromFile(HANDLE hFile, int *pSeek = NULL);//загрузить набор вероятностей из поток

    ~TProbPovider();
};
//---------------------------------------------------------------------------
#endif
