//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "DFT.h"
#pragma package(smart_init)

//Вспомогательная процедура для обращения порядка следования m битов индекса i
int Reverse(int i, int m)
{
  int j,k;
  for (k=j=0; j<m; j++, i>>=1)
  {
    k<<=1;
    if (i&1) k|=1;
  }
  return k;
}

//Функция прямого БПФ
void FFT(Vec c /*вектор коэффициентов Фурье*/, Vec v /*исходный вектор*/)
{
  int j,i,l,a,b,na,bm;
  Vec t,p;

  for (i=0; i<N; i++)
  {
    if  (i&1) t[i]=(v[Reverse(i&~1, M)] - v[Reverse(i|1, M)])/2.0;
    else      t[i]=(v[Reverse(i&~1, M)] + v[Reverse(i|1, M)])/2.0;
  }

  for(l=1; l<M; l++)
  {
    a=1<<l; b=a<<1;
    for (i=0; i<b; i++) p[i]=exp(TComplex(0.0, 2.0*M_PI*i/b));
    na=~a; bm=b-1;
    if  (l&1) for(i=0; i<N; i++) c[i]=(t[i&na] + p[i&bm] * t[i|a])/2.0;
    else      for(i=0; i<N; i++) t[i]=(c[i&na] + p[i&bm] * c[i|a])/2.0;
  }

  #if M&1
    memcpy(c, t, sizeof (complex) * N);
  #endif
}

//Функция обратного БПФ
void IFFT(Vec v /*восстанавливаемый вектор*/, Vec c /*вектор коэффициентов*/)
{
  int j,i,l,a,b,na,bm;
  Vec t,p;

  for (i=0; i<N; i++)
  {
    if  (i&1) t[i]=c[Reverse(i&~1, M)] - c[Reverse(i|1, M)];
    else      t[i]=c[Reverse(i&~1, M)] + c[Reverse(i|1, M)];
  }

  for(l=1; l<M; l++)
  {
    a=1<<l; b=a<<1;
    for (i=0; i<b; i++) p[i]=exp(TComplex(0.0, -2.0*M_PI*i/b));
    na=~a;  bm=b-1;
    if (l&1)  for(i=0; i<N; i++) v[i]=t[i&na] + p[i&bm] * t[i|a];
    else      for(i=0; i<N; i++) t[i]=v[i&na] + p[i&bm] * v[i|a];
  }

  #if M&1
      memcpy(v, t, sizeof(complex) * N);
  #endif
}
//---------------------------------------------------------------------------
void TComplexVector::AddReal(double Val)
{
    push_back(TComplex(Val,0));
}

//мои алгоритмы по преобразованию Фурье
//прямое ПФ
void FT(TComplexVector &c /*вектор коэффициентов Фурье*/, TComplexVector &v/*исходный вектор*/)
{
    c.clear();
    int N = v.size();
    TComplex eps = exp(TComplex(0, -2*M_PI/N));
    TComplex cplxVal, cplxZero(0,0);
    int k,n;
    for(k = 0; k < N; k++)
    {
     cplxVal = cplxZero;
     for(n = 0; n < N; n++)
     {
      cplxVal += v[n] * pow(eps,k*n);
     }
     c.push_back(cplxVal);
    }
}
//обратное ПФ
void IFT(TComplexVector &v /*восстанавливаемый вектор*/, TComplexVector &c /*вектор коэффициентов*/)
{
    v.clear();
    int N = c.size();
    TComplex eps = exp(TComplex(0, 2*M_PI/N));
    TComplex cplxVal, cplxZero(0,0);
    int k,n;
    for(n = 0; n < N; n++)
    {
     cplxVal = cplxZero;
     for(k = 0; k < N; k++)
     {
      cplxVal += c[n] * pow(eps,k*n);
     }
     cplxVal /= TComplex((TComplex::value_type)N, 0);
     v.push_back(cplxVal);
    }
}




