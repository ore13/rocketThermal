#include "vectorMath.hpp"
#include <vector>
#include <cmath>


void multiply(std::vector<double> &array, double multiplier)
{
    for (int i = 0; i < array.size(); i++)
    {
        array[i] = multiplier * array[i];
    }
}

void add(std::vector<double> &array, double added)
{
    for (int i = 0; i < array.size(); i++)
    {
        array[i] = added + array[i];
    }
}

std::vector<double>& multiply(std::vector<double> &v1, std::vector<double> &v2)
{
    // To make an error occur if the vectors are different lengths
    int length = std::max(v1.size(), v2.size());
    for (int i = 0; i < length; i++)
    {
        v1[i] = v1[i] * v2[i];
    }
    return v1;
}

std::vector<double>& add(std::vector<double> &v1, std::vector<double> &v2)
{
    // To make an error occur if the vectors are different lengths
    int length = std::max(v1.size(), v2.size());
    for (int i = 0; i < length; i++)
    {
        v1[i] = v1[i] + v2[i];
    }
    return v1;
}

std::vector<double>& arcLengthArray(std::vector<double> &arc, std::vector<double> x, std::vector<double> y)
{
    // To make an error occur if the vectors are different lengths
    int length = std::max(x.size(), y.size());
    arc.push_back(0); // Start at position zero
    for (int i = 0; i < length - 1; i++)
    {
        double delta_length = sqrt(pow(y[i + 1] - y[i], 2) + pow(x[i+1] - x[i], 2));
        arc.push_back(arc[i] + delta_length);
    }
    return arc;
}

std::vector<double>& tangentAngle(std::vector<double> &tangent, std::vector<double> x, std::vector<double> y)
{
    // To make an error occur if the vectors are different lengths
    int length = std::max(x.size(), y.size());
    tangent.push_back(0); // initial value is zero
    for (int i = 0; i < length - 1; i++)
    {
        tangent.push_back(atan( (y[i+1] - y[i]) / (x[i+1] - x[i]) ));
    }
    return tangent;
}