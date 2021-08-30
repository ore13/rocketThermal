#ifndef AERO_HEATING
#define AERO_HEATING
#include <vector>
#include <string>

using namespace std;

double adiabatic_temperature(double &T, double &V);

double boundary_layer_temperature_eber(double &T, double &V);

/*
Parameters:
    T: free air temperature (K)
    V: Velocity (m/s)
    P: Absolute air pressure (Pa)
    vertex_angle: Nose Cone angle (degrees)
    nose_length: Length of the nose cone (m)
Returns:
    double h: The convective heat transfer coefficient for the nose cone.
*/
double convective_coefficient_eber(double &T, double &V, double &P, double &vertex_angle, double &nose_length);

int transient_0d(vector<double> &time, vector<double> &air_temperature, vector<double> &pressure, vector<double> &velocity, double &vertex_angle, double &nose_length, double &G, double &emissivity, double &absorptivity, string filename);

#endif