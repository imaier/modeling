//---------------------------------------------------------------------------

#ifndef Almas1ProbSetUnitH
#define Almas1ProbSetUnitH
//---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
#include "ProbPoviderUnit.h"
//---------------------------------------------------------------------------
/*
 * Класс глобальных данных для данного набора вероятностей
 */
class TAlmas1ProbSetGlobal : public IBaseProbSetGlobalData
{
private:
	void Init(void);//инициализация набора вероятностей
public:
	TAlmas1ProbSetGlobal();
	~TAlmas1ProbSetGlobal();

	static TAlmas1ProbSetGlobal& Get(void);//получение ссылки на глобальный класс

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
class TAlmas1ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas1ProbSetCreator();
    virtual IBaseProbSet* Create();//создание набора вероятностей
};
//---------------------------------------------------------------------------
/*
 * интерфейс набора вероятностей
 */
class TAlmas1ProbSet : public IBaseProbSet
{
private:
protected:
    TAlmas1ProbSet(IBaseProbSetCreator& Creator);
    //~TAlmas1ProbSet();

	//virtual bool SaveToFile(HANDLE hFile);
	//virtual bool LoadFromFile(HANDLE hFile);

	friend TAlmas1ProbSetCreator;
	friend TProbPovider;
public:
	//virtual int GetAllNumProbality(void);//количество уникальных вероятностей вероятностей в наборе
	//virtual AnsiString GetProbName(int Index);//получение названия (имени) внроятности
	//virtual AnsiString GetProbValue(int Index);//получение значения вероятности
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//получение индекса из набора для данного расположения атомов
	//virtual int GetNumLayerAtomShema();//получение количества слоёв до которого должна быть описана атомсхема
    //virtual const AnsiString& GetProbSetIdString();//получение идентификационной строки набора вероятности

	virtual ~TAlmas1ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
