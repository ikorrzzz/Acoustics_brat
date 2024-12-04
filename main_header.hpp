#pragma once
#include <vector>
#include <string>
#include <complex>

using complex = std::complex<double>;
using complex_vector = std::vector<complex>;
const double PI = 3.141592653589793;

struct DataPoints {
    double x;//Первое значение
    double y;//Второе значение
    double z;//Третье значение

    DataPoints() : x(0), y(0), z(0) {}
    DataPoints(double x, double y, double z): x(x), y(y), z(z) {}
    DataPoints operator - (const DataPoints &Point) const{
        return DataPoints(x-Point.x, y-Point.y, z-Point.z);
    }
    DataPoints operator + (const DataPoints &Point) const{
        return DataPoints(x+Point.x, y+Point.y, z+Point.z);
    }
    DataPoints operator * (const double a) const{
        return DataPoints(x*a, y*a, z*a);
    }
    DataPoints operator / (const double a) const{
        return DataPoints(x/a, y/a, z/a);
    }
    double length() const{
        return sqrt(x*x + y*y + z*z);
    }
};

struct NameAndLength {
    std::string Name;// Имя
    int Len;// длинна таблицы
};

struct DataFrame {
    int A;//Первое значение
    int B;//Второе значение
    int C;//Третье значение
};

struct DVectors {
    std::vector<DataPoints>XYZ;// Объявляем вектор хранящий данные x,y,z
    std::vector<DataFrame>ABC;// Объявляем вектор хранящий данные позиций А,В,С
};

int getVectorsDataAndPos(DVectors &dvectors, const std::string &path);

int full_b(const DVectors &grid, const DataPoints &v0, complex_vector &b, double k);
int full_A(complex (*f)(const DataPoints &, const DataPoints &, const DataPoints &, double),
           const DVectors &grid, complex_vector &A_matix, const double k);
complex subintegrative_function(const DataPoints &normal,
                                const DataPoints &x_point,
                                const DataPoints &y_point,
                                const double k);

extern "C"{
    extern void zgesv_(int *N, int *Nrhs, std::complex<double> *A, int *ldA, int *Ipvt, std::complex<double> *B, int *ldB, int *info);
}

int full_sigma_tau(const DVectors &grid, const complex_vector &g,
                       std::vector <double> &sigma_tau, double k, const int parts);

complex subintegrative_function_2(const DataPoints &normal_x,
                                const DataPoints &x_point,
                                const DataPoints &normal_y,
                                const DataPoints &y_point,
                                const double k);

int full_A_mod(complex (*f)(const DataPoints &, const DataPoints &, const DataPoints &, const DataPoints &, double),
           const DVectors &grid, complex_vector &A_matix, const double k);
