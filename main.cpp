#include "main_header.hpp"
#include <fstream>
#include <iostream>
#include <omp.h>

int main() {
    DVectors grid;
    std::string path = "sphere_4k.obj";
    //std::string path = "sphere_7k.obj";
    if(getVectorsDataAndPos(grid, path))
        return 0;
    DataPoints v0(-1,0,0);
    complex_vector b;
    complex_vector A;
    double k = 0.1;
    auto size_b = full_b(grid, v0, b, k);

    double start = omp_get_wtime();
    auto size_A = full_A(subintegrative_function, grid, A, k);

    double time_n = omp_get_wtime() - start;

    std::cout << "Matrix A size: " << size_A << " Time to full: " << time_n << std::endl;

    int info, bn = 1;
    std::vector <int> Ipiv(size_b);

    start = omp_get_wtime();
    zgesv_(&size_b, &bn, A.data(), &size_b, Ipiv.data(), b.data(), &size_b, &info);
    time_n = omp_get_wtime() - start;
    std::cout << "Time to solve: " << time_n << std::endl;
    std::vector <double> sigma_tau;

    auto parts = 360;
    auto size_sigma_tau = full_sigma_tau(grid, b, sigma_tau, k, parts);

    std::ofstream out;
    out.open("epr.txt");
    if (out.is_open()) {
        out << sigma_tau.size() << std::endl;
        for(auto elem : sigma_tau) {
            out << elem << std::endl;
        }
    }
    out.close();

    return 0;
}
