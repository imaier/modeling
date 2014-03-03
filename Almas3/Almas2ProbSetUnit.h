//---------------------------------------------------------------------------

#ifndef Almas2ProbSetUnitH
#define Almas2ProbSetUnitH
///---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
#include "ProbPoviderUnit.h"
//---------------------------------------------------------------------------
/*
 * Класс глобальных данных для данного набора вероятностей
 */
class TAlmas2ProbSetGlobal : public IBaseProbSetGlobalData
{
private:
	void Init(void);//инициализация набора вероятностей
public:
	TAlmas2ProbSetGlobal();
	~TAlmas2ProbSetGlobal();

	static TAlmas2ProbSetGlobal& Get(void);//получение ссылки на глобальный класс

	//доступны после инициализации (создание обекта набора вероятностей)
	//virtual int GetAllNumProbality(void);//количество уникальных вероятностей вероятностей в наборе
	//virtual AnsiString GetProbName(int Index);//получение названия (имени) внроятности
	virtual TProbIndex GetProbIndexFromAtomShema(TAtomShema &as);//получение индекса из набора для данного расположения атомов
	//virtual int GetNumLayerAtomShema();//получение количества слоёв до которого должна быть описана атомсхема
	//virtual const AnsiString& GetProbSetIdString();//получение идентификационной строки набора вероятности
};
//---------------------------------------------------------------------------
/*
 * создатель набора вероятностей
 */
class TAlmas2ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas2ProbSetCreator();
    virtual IBaseProbSet* Create();//создание набора вероятностей
};
//---------------------------------------------------------------------------
/*
 * интерфейс набора вероятностей
 */
class TAlmas2ProbSet : public IBaseProbSet
{
private:
protected:
    TAlmas2ProbSet(IBaseProbSetCreator& Creator);
    //~TAlmas2ProbSet();

	//virtual bool SaveToFile(HANDLE hFile);
	//virtual bool LoadFromFile(HANDLE hFile);

	friend TAlmas2ProbSetCreator;
	friend TProbPovider;
public:
	//virtual int GetAllNumProbality(void);//количество уникальных вероятностей вероятностей в наборе
	//virtual AnsiString GetProbName(int Index);//получение названия (имени) внроятности
	//virtual AnsiString GetProbValue(int Index);//получение значения вероятности
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//получение индекса из набора для данного расположения атомов
	//virtual int GetNumLayerAtomShema();//получение количества слоёв до которого должна быть описана атомсхема
    //virtual const AnsiString& GetProbSetIdString();//получение идентификационной строки набора вероятности

	virtual ~TAlmas2ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
