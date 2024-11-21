#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <tuple>

// Define a type for a 3D point
using Point = std::vector<double>;

// Function to calculate the cross product of two 3D vectors
Point cross(const Point& v1, const Point& v2) {
    return {
        v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]
    };
}

// Function to calculate the magnitude of a vector
double magnitude(const Point& v) {
    return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

// Function to integrate over a triangle defined by three points in 3D
double integrate(const std::function<double(const Point&)>& f, const std::tuple<Point, Point, Point>& points) {
    const Point& A = std::get<0>(points);
    const Point& B = std::get<1>(points);
    const Point& C = std::get<2>(points);

    // Calculate vectors B - A and C - A
    Point b = { B[0] - A[0], B[1] - A[1], B[2] - A[2] };
    Point c = { C[0] - A[0], C[1] - A[1], C[2] - A[2] };

    // Calculate the area of the triangle using the cross product
    Point cross_product = cross(b, c);
    double area = magnitude(cross_product) / 2.0;

    // Calculate the centroid (collocation point)
    Point colloc_point = { (A[0] + B[0] + C[0]) / 3.0, (A[1] + B[1] + C[1]) / 3.0, (A[2] + B[2] + C[2]) / 3.0 };

    // Calculate the result of integration
    return f(colloc_point) * area;
}

// Function to perform recursion (you need to implement how you want points to be provided)
double recur(const std::function<double(const Point&)>& f, const std::vector<std::tuple<Point, Point, Point>>& all_points) {
    double res = 0.0;
    for (const auto& points : all_points) {
        res += integrate(f, points);
    }
    return res;
}