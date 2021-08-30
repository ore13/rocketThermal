#include <cmath>
using namespace std;


double specific_heat(double &T)
{
    return 1040 - 0.24*T + 6.86e-4*pow(T, 2) - 4.33e-7*pow(T,3) + 9.45e-11*pow(T,4);
}

double enthalpy(double &T)
{
    return 1040*T - 1/2*0.24*pow(T, 2) + 1/3*6.86e-4*pow(T, 3)
     - 1/4*4.33e-7*pow(T, 4) + 1/5*9.45e-11*pow(T, 5);
}

double temperature(double &h)
{
    return -6.04027396e-11*pow(h, 2) + 1.00798096e-03*h -1.66741616e+00;
}

double viscosity(double &T)
{
    double mu0 = 1.71e-5; // base viscosity
    double T0 = 273; // base temperature
    double S = 110.4; // Sutherland constant
    return mu0 * pow((T/T0), 3.0f/2.0f) * (T0 + S)/(T + S);
}

double thermal_conductivity(double &T)
{
    return -1.29e-2 + 2.43e-5*T - 3.39e-9*pow(T, 2) + 1.88e-3 * sqrt(T);
}

double density(double &Pressure, double &Temperature)
{
    return Pressure / (287.0 * Temperature);
}

double prandtl_number(double &T)
{
    return 0.815 - 5.31e-4*T + 7.13e-7*pow(T, 2) - 
    3.69e-10*pow(T, 3) + 7.10e-14*pow(T, 4);
}

double sound_speed(double &T)
{
    return sqrt(1.4*287.0*T);
}