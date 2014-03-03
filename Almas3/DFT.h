//---------------------------------------------------------------------------
#ifndef DFTH
#define DFTH
//---------------------------------------------------------------------------
//Программная реализация БПФ. Copyright © Юрий А. Гаджиев, 2003. Все права защищены.
#include <complex.h>
#include <vector.h>

#define M 10 /*двоичный логарифм N (см. ниже)*/
const int N=(1<<M); /*число элементов комплексного вектора*/

typedef complex<double> TComplex;

typedef TComplex Vec[N];

//Функция прямого БПФ
void FFT(Vec c /*вектор коэффициентов Фурье*/, Vec v /*исходный вектор*/);
//Функция обратного БПФ
void IFFT(Vec v /*восстанавливаемый вектор*/, Vec c /*вектор коэффициентов*/);

/////////////////////////////////////////////////////

//вектор комплексных чисел
class TComplexVector : public std::vector<TComplex>
{
    void AddReal(double Val);
};
//мои алгоритмы по преобразованию Фурье
//прямое ПФ
void FT(TComplexVector &c /*вектор коэффициентов Фурье*/, TComplexVector &v/*исходный вектор*/);
//обратное ПФ
void IFT(TComplexVector &v /*восстанавливаемый вектор*/, TComplexVector &c /*вектор коэффициентов*/);


typedef std::vector<TComplexVector> TComplexArray;



#endif
