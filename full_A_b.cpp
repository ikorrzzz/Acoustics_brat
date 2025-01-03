#include <cmath>
#include "main_header.hpp"

double dot_points(const DataPoints &v_1,
                  const DataPoints &v_2) {
    return v_1.x*v_2.x + v_1.y*v_2.y + v_1.z*v_2.z;
}

DataPoints vec_prod(const DataPoints &a, const DataPoints &b) {
    return DataPoints(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

DataPoints normal_calculation(const DataPoints &A, const DataPoints &B,
                       const DataPoints &C) {
    auto AB = B - A;
    auto AC = C - A;
    auto normal = vec_prod(AB, AC);
    auto length = normal.length();
    if(length > 1e-15) {
        normal = normal/length;
    } else {
        normal.x = normal.y = normal.z = 0;
    }
    return normal;
}

DataPoints colloc_point_calc(const DataPoints &A, const DataPoints &B,
                       const DataPoints &C) {
    return (A + B + C)/3;
}

complex subintegrative_function(const DataPoints &normal,
                                const DataPoints &x_point,
                                const DataPoints &y_point,
                                const double k) {
    auto x_minus_y = x_point - y_point;
    auto r = x_minus_y.length();
    if(r < 1e-14) {
        return 0;
    }
    auto cexpr = std::exp(complex(0, k*r));
    auto ikr_1 = complex(-1, k*r);
    return dot_points(normal, x_minus_y)/(4*PI*r*r*r) * cexpr * ikr_1;
}


complex integrator(complex (*f)(const DataPoints &, const DataPoints &, const DataPoints &, double),
                   const DataPoints &A, const DataPoints &B,
                   const DataPoints &C, const DataPoints &normal,
                   const DataPoints &colloc_point, const double k,
                   int recursion_depth, const int max_recursion_depth) {
    ++recursion_depth;
    if (recursion_depth >= max_recursion_depth) {

        auto S_ABC = vec_prod(B-A, C-A).length()/2;
        return S_ABC*f(normal, colloc_point, colloc_point_calc(A,B,C), k);
    }
    auto result = integrator(f, A, (A+B)/2, (A+C)/2, normal, colloc_point, k, recursion_depth, max_recursion_depth);
    result += integrator(f, (A+B)/2, B, (B+C)/2, normal, colloc_point, k, recursion_depth, max_recursion_depth);
    result += integrator(f, (A+B)/2, (B+C)/2, (A+C)/2, normal, colloc_point, k, recursion_depth, max_recursion_depth);
    result += integrator(f, (A+C)/2, (B+C)/2, C, normal, colloc_point, k, recursion_depth, max_recursion_depth);
    return result;
}


int full_A(complex (*f)(const DataPoints &, const DataPoints &, const DataPoints &, double),
           const DVectors &grid, complex_vector &A_matix, const double k) {
    A_matix.clear();
    const auto max_recursion_depth = 3;
    for(auto j = 0; j < grid.ABC.size(); ++j) {
        auto A = grid.XYZ[grid.ABC[j].A];
        auto B = grid.XYZ[grid.ABC[j].B];
        auto C = grid.XYZ[grid.ABC[j].C];
        auto y = colloc_point_calc(A,B,C);
        auto S_ABC = vec_prod(B-A, C-A).length()/2;
        for(auto i = 0; i < grid.ABC.size(); ++i) {
            auto coloc_point = colloc_point_calc(grid.XYZ[grid.ABC[i].A], grid.XYZ[grid.ABC[i].B], grid.XYZ[grid.ABC[i].C]);
            auto normal = normal_calculation(grid.XYZ[grid.ABC[i].A], grid.XYZ[grid.ABC[i].B], grid.XYZ[grid.ABC[i].C]);
            auto A_ij = i==j? -0.5 : integrator(f, A, B, C, normal, coloc_point, k, 0, max_recursion_depth);
            //~ auto A_ij = i==j? -0.5 : S_ABC*f(normal, coloc_point, y, k);
            A_matix.push_back(A_ij);
        }
    }
    return A_matix.size();
}

complex subintegrative_function_2(const DataPoints &normal_x,
                                const DataPoints &x_point,
                                const DataPoints &normal_y,
                                const DataPoints &y_point,
                                const double k) {
    auto x_minus_y = x_point - y_point;

    auto r = x_minus_y.length();

    if(r < 1e-14) {
        return 0;
    }
    auto exp_ikr = std::exp(complex(0,-k*r));
    return ((k*k*exp_ikr - 3.*complex(0,k)*exp_ikr/r - (3.*exp_ikr-3.)/(r*r))*dot_points(x_minus_y, normal_x)*dot_points(x_minus_y, normal_y) +
    (exp_ikr + complex(0,k*r)*exp_ikr - 1.)*dot_points(normal_x, normal_y))/(4*PI*r*r*r);
}

int full_b(const DVectors &grid, const DataPoints &v0, complex_vector &b, double k) {
    b.clear();
    for(auto element : grid.ABC) {
        auto A = grid.XYZ[element.A];
        auto B = grid.XYZ[element.B];
        auto C = grid.XYZ[element.C];
        auto n_i = normal_calculation(A, B, C);
        auto x_i = colloc_point_calc (A, B, C);
        auto v_0_norm = v0/v0.length();
        auto v0_dot_n_i = dot_points(v_0_norm, n_i);
        auto v0_dot_x_i = dot_points(v_0_norm, x_i);
        auto b_i = std::exp(complex(0, k*v0_dot_x_i))*complex(0, k*v0_dot_n_i);
        b.push_back(b_i);
    }
    return b.size();
}

complex final_func(const DataPoints &normal,
                   const DataPoints &tau,
                   const DataPoints &y_point,
                   const double k) {
    return std::exp(complex(0, -k*dot_points(tau, y_point)));
}

int full_sigma_tau(const DVectors &grid, const complex_vector &g,
                   std::vector <double> &sigma_tau, double k, const int parts) {
    sigma_tau.clear();

    const auto max_recursion_depth = 1;
    for(auto phi = 0.; phi < 2*PI; phi += 2*PI/parts) {
        complex sum = 0;
        for(auto j = 0; j < grid.ABC.size(); ++j) {
            auto A = grid.XYZ[grid.ABC[j].A];
            auto B = grid.XYZ[grid.ABC[j].B];
            auto C = grid.XYZ[grid.ABC[j].C];
            auto normal = normal_calculation(A,B,C);
            auto S_ABC = vec_prod(B-A, C-A).length()/2;
            DataPoints tau(cos(phi), sin(phi), 0);
            sum += g[j] * S_ABC * final_func(normal, tau, colloc_point_calc(A,B,C), k);
        }
        sigma_tau.push_back(abs(sum*sum)/(4*PI));
        }
    return sigma_tau.size();
}
