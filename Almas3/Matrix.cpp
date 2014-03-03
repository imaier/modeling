//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "Matrix.h"
#include "math.h"
int Round(float x)
{
	return (int)floor(x+0.5);
}
//Длина вектора Pnt
float length3d(TPoint3d &Pnt)
{
	return sqrt(Pnt.x*Pnt.x + Pnt.y*Pnt.y + Pnt.z*Pnt.z);
}
//Векторное Произведение векторов Pnt1 и Pnt2
TPoint3d crossProduct(TPoint3d &Pnt1,TPoint3d &Pnt2)
{
//             [ Ax ]   [ Bx ]   | i  j  k  |   [ Ay*Bz-Az*By ]
// [A,B]=AxB = [ Ay ] x [ By ] = | Ax Ay Az | = [ Az*Bx-Ax*Bz ]
//             [ Az ]   [ Bz ]   | Bx By Bz |   [ Ax*By-Ay*Bx ]
	TPoint3d Pnt;
    Pnt.x = Pnt1.y*Pnt2.z - Pnt1.z*Pnt2.y;
    Pnt.y = Pnt1.z*Pnt2.x - Pnt1.x*Pnt2.z;//(?)=-(Pnt1.z*Pnt2.x - Pnt1.x*Pnt2.z)
    Pnt.z = Pnt1.x*Pnt2.y - Pnt1.y*Pnt2.x;
    return Pnt;
}
//---------------------------------------------------------------------------
__fastcall TPoint3d::TPoint3d(float _x,float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
TPoint3d Point3d(float _x,float _y, float _z)
{
	//x = _x;
	//y = _y;
	//z = _z;
    //return *this;
    TPoint3d Pnt;
	Pnt.x = _x;
	Pnt.y = _y;
	Pnt.z = _z;
    return Pnt;
}
//Длина (модуль) вектора
float __fastcall TPoint3d::Length(void)
{
	return sqrt(x*x + y*y + z*z);
}
//Нормировать вектор
/*void __fastcall TPoint3d::Normirate(void)
{
    int i;
	float nrm = sqrt(x*x + y*y + z*z);
    for(i=0;i<3;i++) Coord[i]/= nrm;
} */
//Возращает нормированный вектор
TPoint3d __fastcall TPoint3d::Normirate(void)
{
    int i;
    TPoint3d N=*this;
	float nrm = sqrt(x*x + y*y + z*z);
    if(nrm !=0) for(i=0;i<3;i++) N.Coord[i]/= nrm;
    return N;
}
//возращает угол между осью X и проекцией вектора на плоскость XOY (изменеие этого угла такое же как и угол при повороте вокру оси Z)
float __fastcall TPoint3d::AngleXOY(void)
{
	TPoint3d V;
    V = *this;
    V.z = 0;
    V = V.Normirate();
    if(V.y < 0) return -acos(V.x);
    return acos(V.x);
}
//возращает угол между осью Y и проекцией вектора на плоскость YOZ (изменеие этого угла такое же как и угол при повороте вокру оси X)
float __fastcall TPoint3d::AngleYOZ(void)
{
	TPoint3d V;
    V = *this;
    V.x = 0;
    V = V.Normirate();
    if(V.z < 0) return -acos(V.y);
    return acos(V.y);
}
//возращает угол между осью Z и проекцией вектора на плоскость ZOX (измкенеие этого угла такое же как и угол при повороте вокру оси Y)
float __fastcall TPoint3d::AngleZOX(void)
{
	TPoint3d V;
    V = *this;
    V.y = 0;
    V = V.Normirate();
    if(V.x < 0) return -acos(V.z);
	return acos(V.z);
}
//возращает угол Phi в полярных координатах (угол YOP - угол между осью Y и вектором P (0..180))
float __fastcall TPoint3d::AnglePhi(void)
{
    float Ro = Length();
	if (Ro == 0) return 0;
    else return acos(y/Ro);
}
//возращает угол Teta в полярных координатах (угол между осью Z и проекцией вектора P на плоскость ZOX (0..360))
float __fastcall TPoint3d::AngleTeta(void)
{
	if (Length() == 0) return 0;
    else
    {
     if(z == 0)
     {
      if(x >= 0) return M_PI/2;
      else return 3*M_PI/2;
     }
     if(z > 0) return atan(x/z);
     else return M_PI + atan(x/z);
    }
}
//просто и быстро задаём координаты
void __fastcall TPoint3d::Point3d(float _x,float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
//возращает угол между векторами *this и b (0..360)
float __fastcall TPoint3d::AngleBetwinVectors(const TPoint3d &_b)
{
    float Angle = 0;
    TPoint3d a, b, c,e;
    a = *this;
    b = _b;
	if (a.Length() == 0) return 0;
	if (b.Length() == 0) return 0;

    a = a.Normirate();
    b = b.Normirate();
    float cos_phi = a*b;
    Angle = acos(cos_phi);

    //слева или справо от вектора
    c = a&b;//вектрное произведение
    e = a&c;

    float cos_phi2 = e*b;

    if(cos_phi2 < 0)
    {//вектор b лежит правее вектора a, значит угол больше 180 градусов
        Angle = 2*M_PI - Angle;
    }
    return Angle;
}

//---------------------------------------------------------------------------
TPoint3d __fastcall TSide::GetNorm(void)
{
    //TPoint3d Nvector = ((A-B)&(A-C));
    //Nvector = Nvector.Normirate();
	//return Nvector;

	return ((A-B)&(A-C)).Normirate();
}
//---------------------------------------------------------------------------
float TMatrix::ADp(TMatrix Mtr,int ii, int jj)
{
	float Res, ap, am;
    int i;
    ap = 1;
    am = 1;
    for(i=0;i<2;i++)
     //for(i=0;i<3;i++)
     {
      ap *= Mtr.Item[((i<ii)?i:(i+1))][((i<jj)?i:(i+1))];
      am *= Mtr.Item[(((2-i)<ii)?(1-i):(2-i))][((i<jj)?i:(i+1))];
     }
    Res = (((ii+jj)%2)==1?-1:1)*Mtr.Item[ii][jj]*(ap-am);
    return Res;
}
void __fastcall TMatrix::EMatrix(void)
{
    int i,j;
    for(i=0;i<4;i++)
     for(j=0;j<4;j++)
      Item[i][j] = (i!=j? 0: 1);
}
TMatrix TMatrix::BackMatrix33(void)
{
	float Aopred;
    int i,j;
    TMatrix Bk;

    Aopred = ADp(*this,0,0)+ADp(*this,0,1)+ADp(*this,0,2);
    if(Aopred == 0)
    {
     for(i=0;i<4;i++)
      for(j=0;j<4;j++)
       Bk.Item[i][j] = (i!=j? 0: 1);
     return Bk;
    }
    for(i=0;i<3;i++)
     for(j=0;j<3;j++)
      Bk.Item[j][i] = ADp(*this,i,j)/Aopred;
    return Bk;
}
TMatrix TMatrix::BackMatrix332(void)
{
	TMatrix Bk,E;
    TPoint3d XYZ;
    int i,j,k,l,ijmax;
    double VD;//
    ijmax = 4;
    E = E*0;
    Bk = Bk*0;
    for(i=0;i<ijmax;i++)
    {
     for(j=0;j<ijmax;j++)
     {
      E.Item[i][j] = (i!=j? 0: 1);
      //Bk.Item[i][j] = Item[i][j];
     }
    }
    //XYZ.Point3d(1,0,0);
    //VD = (Bk.Item[0][0]/Bk.Item[1][0]);
    for(l=0;l<ijmax;l++)//прямое
    {
     Bk = Bk*0;
     for(i=0;i<ijmax;i++)
     {
      for(j=0;j<ijmax;j++)
      {
       Bk.Item[i][j] = Item[i][j];
      }
     }
     for(k=0;k<ijmax;k++)//прямое
     {
      if(Bk.Item[k][k]==0)
      {
       for(i=k+1;i<ijmax;i++)
       {
        if(Bk.Item[i][k]!=0)
        {
         for(j=k;j<ijmax;j++)
         {
          VD = Bk.Item[i][j];
          Bk.Item[i][j] = Bk.Item[k][j];
          Bk.Item[k][j] = VD;
         }
         VD = E.Item[i][l];
         E.Item[i][l] = E.Item[k][l];
         E.Item[k][l] = VD;
         break;
        }
       }
      }
      for(i=k+1;i<ijmax;i++)
      {
       if(Bk.Item[i][k]!=0)
       {
        VD = (Bk.Item[k][k]/Bk.Item[i][k]);
        E.Item[i][l] = E.Item[k][l]-VD*E.Item[i][l];
        for(j=k;j<ijmax;j++)
        {
         Bk.Item[i][j] = Bk.Item[k][j]-VD*Bk.Item[i][j];
        }
       }
      }
     }
     //E.Item[ijmax][l]= E.Item[ijmax][l]/Bk.Item[ijmax][ijmax];
     for(k=ijmax-1;k>=0;k--)//обратное
     {
      VD = 0.0;
      for(j=k+1;j<ijmax;j++)
      {
       VD = VD + Bk.Item[k][j]*E.Item[j][l];
      }
      E.Item[k][l]= (E.Item[k][l]-VD)/Bk.Item[k][k];
     }
    }
    return E;
}
TMatrix TMatrix::BackMatrix(void)
{
	TMatrix Bk,E;
    int i,j,k;
    double VD;//
    for(i=0;i<4;i++)
    {
     for(j=0;j<4;j++)
     {
      E.Item[i][j] = (i!=j? 0: 1);
      Bk.Item[i][j] = Item[i][j];
     }
    }

    for(k=0;k<3;k++)//прямое
    {
     for(i=k+1;i<4;i++)
     {
      if(Bk.Item[i][k]!=0)
      {
       VD = (Bk.Item[k][k]/Bk.Item[i][k]);
       for(j=k;j<4;j++)
       {
        E.Item[i][j]  =  E.Item[k][j]-VD* E.Item[i][j];
        Bk.Item[i][j] = Bk.Item[k][j]-VD*Bk.Item[i][j];
       }
      }
     }
    }

    for(k=3;k>0;k--)//обратное
    {
     for(i=k-1;i>=0;i--)
     {
      if(Bk.Item[i][k]!=0)
      {
       VD = (Bk.Item[k][k]/Bk.Item[i][k]);
       for(j=k;j>=i;j--)
       {
        E.Item[i][j] =   E.Item[k][j]-VD* E.Item[i][j];
        Bk.Item[i][j] = Bk.Item[k][j]-VD*Bk.Item[i][j];
       }
      }
     }
    }

    for(i=0;i<4;i++)//приведение к единичной матрице
    {
     for(j=0;j<4;j++)
     {
      E.Item[i][j] /= Bk.Item[i][i];
     }
     Bk.Item[i][i] /= Bk.Item[i][i];
    }

    return E;
}
TMatrix TMatrix::BackMatrixMTH(void)
{
	double a,b,c,d,e,f,g,h,i,determ;
    TMatrix Bk;
    //int ii,jj;

    //for(ii=0;ii<4;ii++)
    // for(jj=0;jj<4;jj++)
    //  Bk.Item[ii][jj] = (ii!=jj? 0: 1);
    Bk.EMatrix();

    a = Item[0][0];
    b = Item[0][1];
    c = Item[0][2];
    d = Item[1][0];
    e = Item[1][1];
    f = Item[1][2];
    g = Item[2][0];
    h = Item[2][1];
    i = Item[2][2];
    determ = a*e*i-a*b*h-d*b*i+d*c*h+g*b*f-g*c*e;
    Bk.Item[0][0] = (e*i-f*h)/determ;
    Bk.Item[0][1] =-(b*i-c*h)/determ;
    Bk.Item[0][2] = (b*f-c*e)/determ;
    Bk.Item[1][0] = (-d*i+f*g)/determ;
    Bk.Item[1][1] = (a*i-c*g)/determ;
    Bk.Item[1][2] =-(a*f-c*d)/determ;
    Bk.Item[2][0] =-(-d*h+e*g)/determ;
    Bk.Item[2][1] =-(a*h-b*g)/determ;
    Bk.Item[2][2] = (a*e-b*d)/determ;
    return Bk;
}
//определитель матрици 3х3
float __fastcall TMatrix::Opred(void)
{
    float s = 0,p=1;
    int i,j;
    for(i = 0; i<3; i++)
    {
     p=1;
     for(j = 0; j<3; j++)
     {
      p *= Item[(i+j)%3][j];
     }
     s += p;
     p=1;
     for(j = 0; j<3; j++)
     {
      p *= Item[(i+j)%3][2-j];
     }
     s -= p;
    }
    return s;
}
//делает матрицу поворота вокруг оси Z на угол Angle от X к Y
void __fastcall TMatrix::RollZ_XOY(float Angle)
{
    //int i,j;
    //for(i=0;i<4;i++)
    // for(j=0;j<4;j++)
    //  Item[i][j] = (i!=j? 0: 1);
    EMatrix();
    Item[0][0] = Item[1][1] = cos(Angle);
    Item[0][1] = -(Item[1][0] = sin(Angle));
}
//делает матрицу поворота вокруг оси X на угол Angle от Y к Z
void __fastcall TMatrix::RollX_YOZ(float Angle)
{
    //int i,j;
    //for(i=0;i<4;i++)
    // for(j=0;j<4;j++)
    //  Item[i][j] = (i!=j? 0: 1);
    EMatrix();
    Item[1][1] = Item[2][2] = cos(Angle);
    Item[1][2] = -(Item[2][1] = sin(Angle));
}
//делает матрицу поворота вокруг оси Y на угол Angle от Z к X
void __fastcall TMatrix::RollY_ZOX(float Angle)
{
    //int i,j;
    //for(i=0;i<4;i++)
    // for(j=0;j<4;j++)
    //  Item[i][j] = (i!=j? 0: 1);
    EMatrix();
    Item[2][2] = Item[0][0] = cos(Angle);
    Item[2][0] = -(Item[0][2] = sin(Angle));
}
//делает матрицу поворота вокруг оси vec на угол Angle
void __fastcall TMatrix::Roll(float Angle, TPoint3d vec)
{
/*
2.3 Поворот вокруг произвольной оси относительно центра координат.
Вращение вокруг произвольной оси немного сложнее. Его нужно непременно знать и понимать.
Формулы поворота на угол A вокруг произвольной оси (alpha, beta, gamma)
temp = 1.0-cos(A);
x' = x*(alpha*temp*alpha + cos(A)) + y*(beta*temp*alpha - sin(A)*gamma) + z*(gamma*temp*alpha + sin(A)*beta);
y' = x*(alpha*temp*beta + sin(A)*gamma) + y*(beta*temp*beta + cos(A)) + z*(gamma*temp*beta - sin(A)*alpha);
z' = x*(alpha*temp*gamma - sin(A)*beta) + y*(beta*temp*gamma + sin(A)*alpha) + z*(gamma*temp*gamma + cos(A));
*/
    float A = Angle;
    float alpha,beta, gamma;
    float temp = 1.0-cos(A);
    TPoint3d v = vec.Normirate();
    alpha = v.x;
    beta  = v.y;
    gamma = v.z;
    EMatrix();
    //x
    Item[0][0] = alpha*temp*alpha + cos(A);
    Item[0][1] = beta*temp*alpha - sin(A)*gamma;
    Item[0][2] = gamma*temp*alpha + sin(A)*beta;
    //y
    Item[1][0] = alpha*temp*beta + sin(A)*gamma;
    Item[1][1] = beta*temp*beta + cos(A);
    Item[1][2] = gamma*temp*beta - sin(A)*alpha;
    //z
    Item[2][0] = alpha*temp*gamma - sin(A)*beta;
    Item[2][1] = beta*temp*gamma + sin(A)*alpha;
    Item[2][2] = gamma*temp*gamma + cos(A);
}
//---------------------------------------------------------------------------

/*
__fastcall TCamera::TCamera(float XSz, float YSz, float Dst)
{
	//Вектора стандартной камеры
	//Sp = (0,0,dist)
	//Sq = (xSize/2,0,0)
	//Sr = (0,ySize/2,0)
	//Ss = (0,0,-dist)
    XSize = XSz; 					//ширина экрана
    YSize = YSz; 					//ширина экрана
	Dist = Dst;  					//фокусное расстояние (от точки центра экрана до точки фокуса)

	Location = Point3d(0,0,-Dst); 	//положение (или S)
    Target = Point3d(0,0,0);      	//направление (точнее, точкой, в которую направлена эта камера)
    FOV = 3.14/2,         		  	//угол зрения
    Roll = 0;             		  	//угол поворота относительно своей оси
    CalculateMatrix();
}
void __fastcall TCamera::CalculateMatrix(void)
{
    int i,j;
    float LP,LR,LQ,Tmp;
	TMatrix RollMatrix,T, T1, MoveMatrix
    		//, BackT1,BackT133
            , RollTeta, RollPhi
            ;

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
//	TPoint3d P,Q,R,S;



	// 1.	Считаем p = target - location
    P = Target - Location;
	// 2.	Если p.x == 0 и p.z == 0, то q = (0, 0, 1); иначе q = (p.z, 0, -p.x)
    if((P.x == 0)&(P.z == 0))
    {
     Q.x = 0;
     Q.y = 0;
     Q.z = 1;
    }
    else
    {
     Q.x = P.z;
     Q.y = 0;
     Q.z = -P.x;
    }
    Q = Q.Normirate();
	// 3.	Считаем r = crossProduct(p, q) - векторное произведение p на q
    R = (P & Q);
    R = R.Normirate();
	// 4.	Считаем lp = length(p) - длина p
	// 5.	Приводим r и q к длине 2*lp*tan(FOV/2)
    Q = Q*(2*P.Length()*tan(FOV/2));
    R = R*(2*P.Length()*tan(FOV/2));
    S = Location;

    // [ x' ] = [ cos(alpha)  -sin(alpha)  0 ] [ x ]
    // [ y' ] = [ sin(alpha)   cos(alpha)  0 ] [ y ]
    // [ z' ] = [ 0            0           1 ] [ z ]
    //for(i=0;i<4;i++)
    // for(j=0;j<4;j++)
    //  RollMatrix.Item[i][j] = (i!=j? 0: 1);
    RollMatrix.EMatrix();
    RollMatrix.Item[0][0] = RollMatrix.Item[1][1] = cos(Roll);
    RollMatrix.Item[1][0] = -(RollMatrix.Item[0][1] = sin(Roll));

	//Матрица параллельного переноса теперь определяется как
	//[ 1 0 0 dx ]
	//[ 0 1 0 dy ]
	//[ 0 0 1 dz ]
	//[ 0 0 0 1  ]
    //for(i=0;i<4;i++)
    // for(j=0;j<4;j++)
    //  MoveMatrix.Item[i][j] = 0;
    //for(i=0;i<4;i++)
    //  MoveMatrix.Item[i][i] = 1;
    MoveMatrix.EMatrix();
    for(i=0;i<3;i++)
      MoveMatrix.Item[i][3] = S.Coord[i]+(i==2? Dist: 0);

	//	  [ qx*2/xSize  rx*2/ySize  px/dist ]   [ qx1 rx1 px1 ]
	//T = [ qy*2/xSize  ry*2/ySize  py/dist ] = [ qy1 ry1 py1 ]
	//    [ qz*2/xSize  rz*2/ySize  pz/dist ]   [ qz1 rz1 pz1 ]
	//     [ qx1/lq  qy1/lq  qz1/lq ]
	//T1 = [ rx1/lr  ry1/lr  rz1/lr ]
	//     [ px1/lp  py1/lp  pz1/lp ]
	//где
	//lp = px1*px1 + py1*py1 + pz1*pz1
	//lq = qx1*qx1 + qy1*qy1 + qz1*qz1
	//lr = rx1*rx1 + ry1*ry1 + rz1*rz1
    for(i=0;i<4;i++)
     for(j=0;j<4;j++)
      T1.Item[i][j] = (i!=j? 0: 1);

    for(i=0;i<3;i++)
    {
     T1.Item[i][0] = Q.Coord[i]*2/XSize;
     T1.Item[i][1] = R.Coord[i]*2/YSize;
     T1.Item[i][2] = P.Coord[i]/Dist;
    }
    T = T1;
    //BackT1 = T1.BackMatrix();
    //BackT133 = T1.BackMatrix33();

    LP=0;
    LR=0;
    LQ=0;
    for(i=0;i<3;i++)
    {
     LP += T1.Item[i][2]*T1.Item[i][2];
     LR += T1.Item[i][1]*T1.Item[i][1];
     LQ += T1.Item[i][0]*T1.Item[i][0];
    }

    for(i=0;i<4;i++)
     for(j=0;j<4;j++)
     {
      Tmp = T1.Item[i][j];
      T1.Item[i][j] = T1.Item[j][i];
      T1.Item[j][i] = Tmp;
     }
    for(j=0;j<3;j++)
    {
     T1.Item[0][j] /= LQ;
     T1.Item[1][j] /= LR;
     T1.Item[2][j] /= LP;
    }
    T1.Item[3][3] = 1;


	TPoint3d sP,sQ,sR,sS;
    sP = T1*P;
    sQ = T1*Q;
    sR = T1*R;

    RollTeta.RollY_ZOX(-P.AngleTeta());
    RollPhi.RollX_YOZ(M_PI/2-P.AnglePhi());
    T = RollPhi*RollTeta;

    //T1 = T.BackMatrixMTH();
    //T1 = T;

    //BackT133 = T.BackMatrix33();

	//FinalCameraMatrix = RollMatrix * T1 * MoveMatrix
	//RollMatrix - матрица поворота камеры на угол Roll относительно своей оси
	//MoveMatrix - матрица паралеьного переноса (точки s )
	//T1-матрица превода (векторов p,q,r) произвольной камеры к стандартной камере (векторам Sp,Sq,Sr)
    CameraMatrix = RollMatrix * T1 * MoveMatrix;
}
bool __fastcall TCamera::N1Plosc(TPoint3d Pnt)
{
	float A,B,C,D;
    TPoin3d M0;
    M0.Point(0,0,-Dist);
    A = 0;
    B = -Dist;
    C = YSize;
    D = -A*M0.x -B*M0.y -C*M0.z;
    return (A*Pnt.x + B*Pnt.y + C*Pnt.z + D) > 0;
}
bool __fastcall TCamera::N2Plosc(TPoint3d Pnt)
{
	float A,B,C,D;
    TPoin3d M0;
    M0.Point(0,0,-Dist);
    A = -Dist;
    B = 0;
    C = XSize;
    D = -A*M0.x -B*M0.y -C*M0.z;
    return (A*Pnt.x + B*Pnt.y + C*Pnt.z + D) > 0;
}
bool __fastcall TCamera::N3Plosc(TPoint3d Pnt)
{
	float A,B,C,D;
    TPoin3d M0;
    M0.Point(0,0,-Dist);
    A = 0;
    B = Dist;
    C = YSize;
    D = -A*M0.x -B*M0.y -C*M0.z;
    return (A*Pnt.x + B*Pnt.y + C*Pnt.z + D) > 0;
}
bool __fastcall TCamera::N4Plosc(TPoint3d Pnt)
{
	float A,B,C,D;
    TPoin3d M0;
    M0.Point(0,0,-Dist);
    A = Dist;
    B = 0;
    C = XSize;
    D = -A*M0.x -B*M0.y -C*M0.z;
    return (A*Pnt.x + B*Pnt.y + C*Pnt.z + D) > 0;
}
//видна ли точка из камеры
int __fastcall TCamera::Visibled(TPoint3d Pnt)
{
	int Vsbld = 0, bit;
    bit = N1Plosc(Pnt);
    Vsbld = bit;
    bit = N2Plosc(Pnt);
    Vsbld |= bit<<8;
    bit = N3Plosc(Pnt);
    Vsbld |= bit<<16;
    bit = N4Plosc(Pnt);
    Vsbld |= bit<<24;
	return Vsbld;
}

TSide2d __fastcall TCamera::DisplaySide(TSide Side)
{
	TSide2d S2d;
    int VsbldA, VsbldB, VsbldC;
    Side.A = CameraMatrix * Side.A;
    Side.B = CameraMatrix * Side.B;
    Side.C = CameraMatrix * Side.C;

    VsbldA = Visibled(Side.A);
    VsbldB = Visibled(Side.B);
    VsbldC = Visibled(Side.C);
       //if((VsbldA & VsbldB & VsbldC) == 0)
    if(VsbldA == VsbldB == VsbldC == 0)
    {
     //виден
    }
    else
    {
     if(VsbldC == 0)
     {
      //точка С видна
      if((VsbldA & VsbldB ) == 0)
      {
       //видимость АВ неочевидна
      }
      else
      {
       //АВ невиден
      }
     }
     else
     {
      //точка С не видна
     }
    }

	//sx = xSize/2+x*Dist/(z+Dist),
	//sy = ySize/2-y*Dist/(z+Dist).
    S2d.A.x = XSize/2+Side.A.x*Dist/(Side.A.z+Dist);
    S2d.A.y = YSize/2-Side.A.y*Dist/(Side.A.z+Dist);
    S2d.B.x = XSize/2+Side.B.x*Dist/(Side.B.z+Dist);
    S2d.B.y = YSize/2-Side.B.y*Dist/(Side.B.z+Dist);
    S2d.C.x = XSize/2+Side.C.x*Dist/(Side.C.z+Dist);
    S2d.C.y = YSize/2-Side.C.y*Dist/(Side.C.z+Dist);
    return S2d;
}
TPoint2d __fastcall TCamera::DisplayPoint(TPoint3d Pnt)
{
	TPoint2d P2d;
    Pnt = CameraMatrix * Pnt;
	//sx = xSize/2+x*Dist/(z+Dist),
	//sy = ySize/2-y*Dist/(z+Dist).
    P2d.x = XSize/2+Pnt.x*Dist/((!(Pnt.z+Dist))?1:(Pnt.z+Dist));
    P2d.y = YSize/2-Pnt.y*Dist/((!(Pnt.z+Dist))?1:(Pnt.z+Dist));

    return P2d;
}
//---------------------------------------------------------------------------
*/
__fastcall TMatrix::TMatrix(double * Mtr)
{
    int i,j;
    for(i=0;i<4;i++)
     for(j=0;j<4;j++)
      Item[i][j] = Mtr[i*4+j];
}
//---------------------------------------------------------------------------
TMatrix __fastcall TMatrix::Transpose(void)
{
    int i,j;
    TMatrix TransposeMatrix;
    for(i=0;i<4;i++)
    {
     for(j=0;j<4;j++)
     {
      TransposeMatrix.Item[i][j] = Item[j][i];
     }
    }
    return TransposeMatrix;
}
//---------------------------------------------------------------------------

