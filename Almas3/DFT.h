//---------------------------------------------------------------------------
#ifndef DFTH
#define DFTH
//---------------------------------------------------------------------------
//����������� ���������� ���. Copyright � ���� �. �������, 2003. ��� ����� ��������.
#include <complex.h>
#include <vector.h>

#define M 10 /*�������� �������� N (��. ����)*/
const int N=(1<<M); /*����� ��������� ������������ �������*/

typedef complex<double> TComplex;

typedef TComplex Vec[N];

//������� ������� ���
void FFT(Vec c /*������ ������������� �����*/, Vec v /*�������� ������*/);
//������� ��������� ���
void IFFT(Vec v /*����������������� ������*/, Vec c /*������ �������������*/);

/////////////////////////////////////////////////////

//������ ����������� �����
class TComplexVector : public std::vector<TComplex>
{
    void AddReal(double Val);
};
//��� ��������� �� �������������� �����
//������ ��
void FT(TComplexVector &c /*������ ������������� �����*/, TComplexVector &v/*�������� ������*/);
//�������� ��
void IFT(TComplexVector &v /*����������������� ������*/, TComplexVector &c /*������ �������������*/);


typedef std::vector<TComplexVector> TComplexArray;



#endif
