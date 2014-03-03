//---------------------------------------------------------------------------
#ifndef Classes3dH
#define Classes3dH
//2d
//Точка на плоскости (2d-точка)
/*class TPoint2d
{
public:
	float Coord[2];
    __property float x = {read = Coord[0], write = Coord[0]};
    __property float y = {read = Coord[1], write = Coord[1]};
};
//Проекция грани - треугольник
class TSide2d
{
public:
    int Count;//сколько точек получилось при проекции грани
    TPoint2d Points[7];
    //три точки, треугольник
    __property TPoint2d A = {read = Points[0], write = Points[0]};
    __property TPoint2d B = {read = Points[1], write = Points[1]};
    __property TPoint2d C = {read = Points[2], write = Points[2]};
    //но возможно ещё 4 точки при проекции треугольника
    __property TPoint2d D = {read = Points[3], write = Points[3]};
    __property TPoint2d E = {read = Points[4], write = Points[4]};
    __property TPoint2d F = {read = Points[5], write = Points[5]};
    __property TPoint2d G = {read = Points[6], write = Points[6]};
};
*/
//3d
//Точка в пространастве (3d-точка)
class TPoint3d
{
public:
	float Coord[3];
    __property float x = {read = Coord[0], write = Coord[0]};
    __property float y = {read = Coord[1], write = Coord[1]};
    __property float z = {read = Coord[2], write = Coord[2]};
    TPoint3d operator =(const TPoint3d &Pnt)//Операция присваивания векторов (*this = Pnt)
    {
     x = Pnt.x;
     y = Pnt.y;
     z = Pnt.z;
     return *this;
    }
    TPoint3d operator -(TPoint3d A)//Операция вычитания векторов (B = *this - A)
    {
     int i;
     TPoint3d B;
     for(i=0;i<3;i++)
      B.Coord[i] = Coord[i] - A.Coord[i];
     return B;
    }
    TPoint3d operator +(TPoint3d A)//Операция сложения векторов (B = *this + A)
    {
     int i;
     TPoint3d B;
     for(i=0;i<3;i++)
      B.Coord[i] = Coord[i] + A.Coord[i];
     return B;
    }
    TPoint3d operator *(float a)//Операция умножения вектора на число (B = (*this) * a)
    {
     int i;
     TPoint3d B;
     for(i=0;i<3;i++)
      B.Coord[i] = Coord[i] * a;
     return B;
    }
    float operator *(TPoint3d A)//Операция скалярного произведения векторов (S = (*this , A))
    {
     int i;
     float S = 0;
     for(i=0;i<3;i++)
      S += Coord[i] * A.Coord[i];
     return S;
    }
    TPoint3d operator &(TPoint3d A)//Операция векторного произведения векторов (B=[*this,A])
    {
     int i;
     TPoint3d B;
     for(i=0;i<3;i++)
      B.Coord[i] = Coord[(i+1)%3] * A.Coord[(i+2)%3]-Coord[(i+2)%3] * A.Coord[(i+1)%3];
     return B;
    }
    //Операции векторного сравнения
    bool operator ==(TPoint3d Pnt)//Операции равенства 2-х векторв (*this == Pnt)
    {
     return ((x == Pnt.x)&(y == Pnt.y)&(z == Pnt.z));
    }
    bool operator !=(TPoint3d Pnt)//Операции неравенства 2-х векторв (*this != Pnt)
    {
     return !((x == Pnt.x)&(y == Pnt.y)&(z == Pnt.z));
    }

    float __fastcall Length(void);//Длина (модуль) вектора
    //void __fastcall Normirate(void);//Нормировать вектор
    TPoint3d __fastcall Normirate(void);//Возращает нормированный вектор
    float __fastcall AngleXOY(void);//возращает угол между осью X и проекцией вектора на плоскость XOY (изменеие этого угла такое же как и угол при повороте вокру оси Z)
    float __fastcall AngleYOZ(void);//возращает угол между осью Y и проекцией вектора на плоскость YOZ (изменеие этого угла такое же как и угол при повороте вокру оси X)
    float __fastcall AngleZOX(void);//возращает угол между осью Z и проекцией вектора на плоскость ZOX (изменеие этого угла такое же как и угол при повороте вокру оси Y)
    //полярные координаты
    float __fastcall AnglePhi(void);//возращает угол Phi в полярных координатах (угол YOP - угол между осью Y и вектором P (0..180))
    float __fastcall AngleTeta(void);//возращает угол Teta в полярных координатах (угол между осью Z и проекцией вектора P на плоскость ZOX (0..360))

    float __fastcall AngleBetwinVectors(const TPoint3d &_b);//возращает угол между векторами *this и b (0..360)

    void __fastcall Point3d(float _x,float _y, float _z);//просто и быстро задаём координаты
    //конструкторы
    __fastcall TPoint3d(void){};
    __fastcall TPoint3d(float _x,float _y, float _z);
};
TPoint3d Point3d(float _x,float _y, float _z);

//Грань
class TSide
{
private:
	TPoint3d __fastcall GetNorm(void);
public:
	TPoint3d A, B, C;//три точки, задающие грань (плоскость)
    __property TPoint3d N = {read =GetNorm};//вектор нормали к плоскости
};
//Матрица
class TMatrix
{
private:
	float ADp(TMatrix Mtr,int ii, int jj);//определитель алгебраического дополнения
public:
	//float Item[4][4];//элементы матрицы
	double Item[4][4];//элементы матрицы
    void __fastcall EMatrix(void);//делает единичную матрицу
    TMatrix BackMatrix(void);//обратная матрица методом Гаусса ( [A|E] ->[E|A] )- неработает
    TMatrix BackMatrix33(void);//обратная матрица "в лоб" - вообще неработает
    TMatrix BackMatrixMTH(void);//обратная матрица "в лоб" по Mathcad'овски - должна работать
    TMatrix BackMatrix332(void);
    float __fastcall Opred(void);//определитель матрици 3х3
    void __fastcall RollZ_XOY(float Angle);//делат матрицу поворота вокруг оси Z на угол Angle от X к Y
    void __fastcall RollX_YOZ(float Angle);//делает матрицу поворота вокруг оси X на угол Angle от Y к Z
    void __fastcall RollY_ZOX(float Angle);//делает матрицу поворота вокруг оси Y на угол Angle от Z к X
    void __fastcall Roll(float Angle, TPoint3d vec);//делает матрицу поворота вокруг оси vec на угол Angle

    TMatrix operator =(TMatrix A)//Операция присваивания матриц
    {
     int i,j;
     for (i=0;i<4;i++)
      for (j=0;j<4;j++)
       Item[i][j] = A.Item[i][j];
     return *this;
    }
    TMatrix operator +(TMatrix A)//Операция сложения матриц
    {
     int i,j;
     TMatrix B;
     for (i=0;i<4;i++)
      for (j=0;j<4;j++)
       B.Item[i][j] = Item[i][j] + A.Item[i][j];
     return B;
    }
    TMatrix operator *(float A)//Операция умножения матрицы на число
    {
     int i,j;
     TMatrix B;
     for (i=0;i<4;i++)
      for (j=0;j<4;j++)
       B.Item[i][j] = Item[i][j] * A;
     return B;
    }
    TPoint3d operator *(TPoint3d Pnt)//Операция умножения матрицы на вектор
    {
     int i,k;
     TPoint3d Result;
     for (i=0;i<3;i++)
     {
      Result.Coord[i] = 0;
      for (k=0;k<4;k++)
       Result.Coord[i] += Item[i][k] * ((k!=3)? Pnt.Coord[k] : 1);
     }
     return Result;
    }
    TMatrix operator *(TMatrix A)//Операция умножения матриц
    {
     int i,j,k;
     TMatrix B;
     for (i=0;i<4;i++)
      for (j=0;j<4;j++)
      {
       B.Item[i][j] = 0;
       for (k=0;k<4;k++)
        B.Item[i][j] += Item[i][k] * A.Item[k][j];
      }
     return B;
    }
    __fastcall TMatrix(){};
    __fastcall TMatrix(double * Mtr);
    TMatrix __fastcall Transpose(void);
};
/*
class TCamera
{
private:
    bool __fastcall N1Plosc(TPoint3d Pnt);//видна ли точка по отношению к 1-ой плоскости камеры
    bool __fastcall N2Plosc(TPoint3d Pnt);//видна ли точка по отношению к 2-ой плоскости камеры
    bool __fastcall N3Plosc(TPoint3d Pnt);//видна ли точка по отношению к 3-ой плоскости камеры
    bool __fastcall N4Plosc(TPoint3d Pnt);//видна ли точка по отношению к 4-ой плоскости камеры
    int __fastcall Visibled(TPoint3d Pnt);//видна ли точка из камеры
public:
    float XSize, //ширина экрана
    	  YSize, //ширина экрана
          Dist;  //фокусное расстояние (от точки центра экрана до точки фокуса)
	TPoint3d Location, //положение (или S)
    		 Target;   //направление (точнее, точкой, в которую направлена эта камера)
    float FOV,         //угол зрения
    	  Roll;        //угол поворота относительно своей оси

// 1.	Считаем p = target - location
// 2.	Если p.x == 0 и p.z == 0, то q = (0, 0, 1); иначе q = (p.z, 0, -p.x)
// 3.	Считаем r = crossProduct(p, q) - векторное произведение p на q
// 4.	Считаем lp = length(p) - длина p
// 5.	Приводим r и q к длине 2*lp*tan(FOV/2)

//Вектора произвольной камеры
//p - вектор "вперед" соединяет центр проецирования и центр экрана,
//q - вектор "вправо" соединяет центр экрана и правую его границу,
//r - вектор "вверх", соответственно, центр экрана и верхнюю его границу,
//s - центр проецирования (точка)

//Вектора стандартной камеры
//Sp = (0,0,dist)
//Sq = (xSize/2,0,0)
//Sr = (0,ySize/2,0)
//Ss = (0,0,-dist)
	TPoint3d P,Q,R,S;
//FinalCameraMatrix = RollMatrix * T1 * MoveMatrix
//RollMatrix - матрица поворота камеры на угол Roll относительно своей оси
//MoveMatrix - матрица паралеьного переноса (точки s )
//T1-матрица превода (векторов p,q,r) произвольной камеры к стандартной камере (векторам Sp,Sq,Sr)
    TMatrix CameraMatrix;

    void __fastcall CalculateMatrix(void);
    TSide2d __fastcall DisplaySide(TSide Side);
	TPoint2d __fastcall DisplayPoint(TPoint3d Pnt);


    __fastcall TCamera(float XSz, float YSz, float Dst);//Коструктор
};
*/
//вращение вокруг оси Z
// [ x' ] = [ cos(alpha)  -sin(alpha)  0 ] [ x ]
// [ y' ] = [ sin(alpha)   cos(alpha)  0 ] [ y ]
// [ z' ] = [ 0            0           1 ] [ z ]
//вращение вокруг оси X
// [ x' ] = [ 1            0           0 ] [ x ]
// [ y' ] = [ 0   cos(alpha)  -sin(alpha)] [ y ]
// [ z' ] = [ 0   sin(alpha)   cos(alpha)] [ z ]
//вращение вокруг оси Y
// [ x' ] = [ cos(alpha)   0   sin(alpha)] [ x ]
// [ y' ] = [ 0            1   0         ] [ y ]
// [ z' ] = [ -sin(alpha)  0   cos(alpha)] [ z ]

//class TPlosc //плоскость
//{
//
//};
//---------------------------------------------------------------------------
#endif
