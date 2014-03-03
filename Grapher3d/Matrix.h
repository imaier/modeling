//---------------------------------------------------------------------------
#ifndef Classes3dH
#define Classes3dH
//2d
//����� �� ��������� (2d-�����)
/*class TPoint2d
{
public:
	float Coord[2];
    __property float x = {read = Coord[0], write = Coord[0]};
    __property float y = {read = Coord[1], write = Coord[1]};
};
//�������� ����� - �����������
class TSide2d
{
public:
    int Count;//������� ����� ���������� ��� �������� �����
    TPoint2d Points[7];
    //��� �����, �����������
    __property TPoint2d A = {read = Points[0], write = Points[0]};
    __property TPoint2d B = {read = Points[1], write = Points[1]};
    __property TPoint2d C = {read = Points[2], write = Points[2]};
    //�� �������� ��� 4 ����� ��� �������� ������������
    __property TPoint2d D = {read = Points[3], write = Points[3]};
    __property TPoint2d E = {read = Points[4], write = Points[4]};
    __property TPoint2d F = {read = Points[5], write = Points[5]};
    __property TPoint2d G = {read = Points[6], write = Points[6]};
};
*/
//3d
//����� � ������������� (3d-�����)
class TPoint3d
{
public:
	float Coord[3];
    __property float x = {read = Coord[0], write = Coord[0]};
    __property float y = {read = Coord[1], write = Coord[1]};
    __property float z = {read = Coord[2], write = Coord[2]};
    TPoint3d operator =(const TPoint3d &Pnt)//�������� ������������ �������� (*this = Pnt)
    {
     x = Pnt.x;
     y = Pnt.y;
     z = Pnt.z;
     return *this;
    }
    TPoint3d operator -(TPoint3d A)//�������� ��������� �������� (B = *this - A)
    {
     int i;
     TPoint3d B;
     for(i=0;i<3;i++)
      B.Coord[i] = Coord[i] - A.Coord[i];
     return B;
    }
    TPoint3d operator +(TPoint3d A)//�������� �������� �������� (B = *this + A)
    {
     int i;
     TPoint3d B;
     for(i=0;i<3;i++)
      B.Coord[i] = Coord[i] + A.Coord[i];
     return B;
    }
    TPoint3d operator *(float a)//�������� ��������� ������� �� ����� (B = (*this) * a)
    {
     int i;
     TPoint3d B;
     for(i=0;i<3;i++)
      B.Coord[i] = Coord[i] * a;
     return B;
    }
    float operator *(TPoint3d A)//�������� ���������� ������������ �������� (S = (*this , A))
    {
     int i;
     float S = 0;
     for(i=0;i<3;i++)
      S += Coord[i] * A.Coord[i];
     return S;
    }
    TPoint3d operator &(TPoint3d A)//�������� ���������� ������������ �������� (B=[*this,A])
    {
     int i;
     TPoint3d B;
     for(i=0;i<3;i++)
      B.Coord[i] = Coord[(i+1)%3] * A.Coord[(i+2)%3]-Coord[(i+2)%3] * A.Coord[(i+1)%3];
     return B;
    }
    //�������� ���������� ���������
    bool operator ==(TPoint3d Pnt)//�������� ��������� 2-� ������� (*this == Pnt)
    {
     return ((x == Pnt.x)&(y == Pnt.y)&(z == Pnt.z));
    }
    bool operator !=(TPoint3d Pnt)//�������� ����������� 2-� ������� (*this != Pnt)
    {
     return !((x == Pnt.x)&(y == Pnt.y)&(z == Pnt.z));
    }

    float __fastcall Length(void);//����� (������) �������
    //void __fastcall Normirate(void);//����������� ������
    TPoint3d __fastcall Normirate(void);//��������� ������������� ������
    float __fastcall AngleXOY(void);//��������� ���� ����� ���� X � ��������� ������� �� ��������� XOY (�������� ����� ���� ����� �� ��� � ���� ��� �������� ����� ��� Z)
    float __fastcall AngleYOZ(void);//��������� ���� ����� ���� Y � ��������� ������� �� ��������� YOZ (�������� ����� ���� ����� �� ��� � ���� ��� �������� ����� ��� X)
    float __fastcall AngleZOX(void);//��������� ���� ����� ���� Z � ��������� ������� �� ��������� ZOX (�������� ����� ���� ����� �� ��� � ���� ��� �������� ����� ��� Y)
    //�������� ����������
    float __fastcall AnglePhi(void);//��������� ���� Phi � �������� ����������� (���� YOP - ���� ����� ���� Y � �������� P (0..180))
    float __fastcall AngleTeta(void);//��������� ���� Teta � �������� ����������� (���� ����� ���� Z � ��������� ������� P �� ��������� ZOX (0..360))

    float __fastcall AngleBetwinVectors(const TPoint3d &_b);//��������� ���� ����� ��������� *this � b (0..360)

    void __fastcall Point3d(float _x,float _y, float _z);//������ � ������ ����� ����������
    //������������
    __fastcall TPoint3d(void){};
    __fastcall TPoint3d(float _x,float _y, float _z);
};
TPoint3d Point3d(float _x,float _y, float _z);

//�����
class TSide
{
private:
	TPoint3d __fastcall GetNorm(void);
public:
	TPoint3d A, B, C;//��� �����, �������� ����� (���������)
    __property TPoint3d N = {read =GetNorm};//������ ������� � ���������
};
//�������
class TMatrix
{
private:
	float ADp(TMatrix Mtr,int ii, int jj);//������������ ��������������� ����������
public:
	//float Item[4][4];//�������� �������
	double Item[4][4];//�������� �������
    void __fastcall EMatrix(void);//������ ��������� �������
    TMatrix BackMatrix(void);//�������� ������� ������� ������ ( [A|E] ->[E|A] )- ����������
    TMatrix BackMatrix33(void);//�������� ������� "� ���" - ������ ����������
    TMatrix BackMatrixMTH(void);//�������� ������� "� ���" �� Mathcad'����� - ������ ��������
    TMatrix BackMatrix332(void);
    float __fastcall Opred(void);//������������ ������� 3�3
    void __fastcall RollZ_XOY(float Angle);//����� ������� �������� ������ ��� Z �� ���� Angle �� X � Y
    void __fastcall RollX_YOZ(float Angle);//������ ������� �������� ������ ��� X �� ���� Angle �� Y � Z
    void __fastcall RollY_ZOX(float Angle);//������ ������� �������� ������ ��� Y �� ���� Angle �� Z � X
    void __fastcall Roll(float Angle, TPoint3d vec);//������ ������� �������� ������ ��� vec �� ���� Angle

    TMatrix operator =(TMatrix A)//�������� ������������ ������
    {
     int i,j;
     for (i=0;i<4;i++)
      for (j=0;j<4;j++)
       Item[i][j] = A.Item[i][j];
     return *this;
    }
    TMatrix operator +(TMatrix A)//�������� �������� ������
    {
     int i,j;
     TMatrix B;
     for (i=0;i<4;i++)
      for (j=0;j<4;j++)
       B.Item[i][j] = Item[i][j] + A.Item[i][j];
     return B;
    }
    TMatrix operator *(float A)//�������� ��������� ������� �� �����
    {
     int i,j;
     TMatrix B;
     for (i=0;i<4;i++)
      for (j=0;j<4;j++)
       B.Item[i][j] = Item[i][j] * A;
     return B;
    }
    TPoint3d operator *(TPoint3d Pnt)//�������� ��������� ������� �� ������
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
    TMatrix operator *(TMatrix A)//�������� ��������� ������
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
    bool __fastcall N1Plosc(TPoint3d Pnt);//����� �� ����� �� ��������� � 1-�� ��������� ������
    bool __fastcall N2Plosc(TPoint3d Pnt);//����� �� ����� �� ��������� � 2-�� ��������� ������
    bool __fastcall N3Plosc(TPoint3d Pnt);//����� �� ����� �� ��������� � 3-�� ��������� ������
    bool __fastcall N4Plosc(TPoint3d Pnt);//����� �� ����� �� ��������� � 4-�� ��������� ������
    int __fastcall Visibled(TPoint3d Pnt);//����� �� ����� �� ������
public:
    float XSize, //������ ������
    	  YSize, //������ ������
          Dist;  //�������� ���������� (�� ����� ������ ������ �� ����� ������)
	TPoint3d Location, //��������� (��� S)
    		 Target;   //����������� (������, ������, � ������� ���������� ��� ������)
    float FOV,         //���� ������
    	  Roll;        //���� �������� ������������ ����� ���

// 1.	������� p = target - location
// 2.	���� p.x == 0 � p.z == 0, �� q = (0, 0, 1); ����� q = (p.z, 0, -p.x)
// 3.	������� r = crossProduct(p, q) - ��������� ������������ p �� q
// 4.	������� lp = length(p) - ����� p
// 5.	�������� r � q � ����� 2*lp*tan(FOV/2)

//������� ������������ ������
//p - ������ "������" ��������� ����� ������������� � ����� ������,
//q - ������ "������" ��������� ����� ������ � ������ ��� �������,
//r - ������ "�����", ��������������, ����� ������ � ������� ��� �������,
//s - ����� ������������� (�����)

//������� ����������� ������
//Sp = (0,0,dist)
//Sq = (xSize/2,0,0)
//Sr = (0,ySize/2,0)
//Ss = (0,0,-dist)
	TPoint3d P,Q,R,S;
//FinalCameraMatrix = RollMatrix * T1 * MoveMatrix
//RollMatrix - ������� �������� ������ �� ���� Roll ������������ ����� ���
//MoveMatrix - ������� ����������� �������� (����� s )
//T1-������� ������� (�������� p,q,r) ������������ ������ � ����������� ������ (�������� Sp,Sq,Sr)
    TMatrix CameraMatrix;

    void __fastcall CalculateMatrix(void);
    TSide2d __fastcall DisplaySide(TSide Side);
	TPoint2d __fastcall DisplayPoint(TPoint3d Pnt);


    __fastcall TCamera(float XSz, float YSz, float Dst);//����������
};
*/
//�������� ������ ��� Z
// [ x' ] = [ cos(alpha)  -sin(alpha)  0 ] [ x ]
// [ y' ] = [ sin(alpha)   cos(alpha)  0 ] [ y ]
// [ z' ] = [ 0            0           1 ] [ z ]
//�������� ������ ��� X
// [ x' ] = [ 1            0           0 ] [ x ]
// [ y' ] = [ 0   cos(alpha)  -sin(alpha)] [ y ]
// [ z' ] = [ 0   sin(alpha)   cos(alpha)] [ z ]
//�������� ������ ��� Y
// [ x' ] = [ cos(alpha)   0   sin(alpha)] [ x ]
// [ y' ] = [ 0            1   0         ] [ y ]
// [ z' ] = [ -sin(alpha)  0   cos(alpha)] [ z ]

//class TPlosc //���������
//{
//
//};
//---------------------------------------------------------------------------
#endif
