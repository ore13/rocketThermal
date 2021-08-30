#ifndef VECTOR_MATH
#define VECTOR_MATH
#include <vector>

void multiply(std::vector<double> &array, double multiplier);

void add(std::vector<double> &array, double added);

std::vector<double>& multiply(std::vector<double> &v1, std::vector<double> &v2);

std::vector<double>& add(std::vector<double> &v1, std::vector<double> &v2);

std::vector<double>& arcLengthArray(std::vector<double> &arc, std::vector<double> x, std::vector<double> y);

std::vector<double>& tangentAngle(std::vector<double> &tangent, std::vector<double> x, std::vector<double> y);

#endif