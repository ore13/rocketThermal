#include "AeroHeating.hpp"
#include "AirProperties.hpp"
#include "CsvWriter.hpp"
#include "vectorMath.hpp"
#include <cmath>
#include <vector>

using namespace std;

class flightData
{
    vector<double> *time_ptr;
    vector<double> *temperature_ptr;
    vector<double> *pressure_ptr;
    vector<double> *velocity_ptr;

    flightData(vector<double> &t, vector<double> &Temp, vector<double> &P, vector<double> &V)
    {
        time_ptr = &t;
        temperature_ptr = &Temp;
        pressure_ptr = &P;
        velocity_ptr = &V;
    }
};




double adiabatic_temperature(double &T, double &V)
{
    double T1 = T + pow(V, 2) / (2.0f * specific_heat(T));
    T1 = (T1 + T) / (2.0f);
    double T2 = T + pow(V, 2) / (2.0f * specific_heat(T1));
    return T2;
}

double boundary_layer_temperature_eber(double &T, double &V)
{
    double Tst = adiabatic_temperature(T, V);
    return T + 0.89*(Tst - T);
}

double convective_coefficient_eber(double &T, double &V, double &P, double &vertex_angle, double &l)
{
    double Tbl = boundary_layer_temperature_eber(T, V);
    double rho = density(P, Tbl);
    double mu = viscosity(Tbl);
    double k = thermal_conductivity(Tbl);
    double Pr = prandtl_number(Tbl);
    double Re = rho * V * l / mu;
    // double Nu = (0.0071 + 0.0154*sqrt(vertex_angle*3.1415f/180.0f)) * pow(Re, 0.8f);
    double Nu = 0.037 * pow(Re, 0.8f) * pow(Pr, 1.0f/3.0f);
    if (vertex_angle > 1e-6)
    {
        Nu = Nu * 1.15; // only apply cone correction for cones
    }
    return Nu * k / l;
}

int transient_0d(vector<double> &time, vector<double> &air_temperature, vector<double> &pressure, vector<double> &velocity, double &vertex_angle, double &nose_length, double &G, double &emissivity, double &absorptivity, string filename)
{
    // Loop variables:
    double Ts, P, V, T_free, T_bl, h, dt, qdot_rad_absorb, qdot_rad_emit, f, Ts_next;

    const double STEFAN_BOLTZMANN = 5.670374419e-8;

    // Vectors of output variables
    vector<double> boundary_layer_temperature(time.size(), 0);
    vector<double> skin_temperature(time.size(), 0);
    vector<double> convection_coefficient(time.size(), 0);

    // Initialise the skin temperature to the ambient air temperature at t = 0
    skin_temperature[0] = air_temperature[0];
    Ts = air_temperature[0];
    for (int i = 0; i < time.size(); i++)
    {
        P = pressure[i];
        V = velocity[i];
        T_free = air_temperature[i];

        // Calculations
        T_bl = boundary_layer_temperature_eber(T_free, V);
        h = convective_coefficient_eber(T_bl, V, P, vertex_angle, nose_length);
        dt = time[i+1] - time[i];

        // Heat transfer rates
        qdot_rad_absorb = absorptivity * STEFAN_BOLTZMANN * pow(T_free, 4);
        qdot_rad_emit = emissivity * STEFAN_BOLTZMANN * pow(Ts, 4);

        f = (h * (T_bl - Ts) + qdot_rad_absorb - qdot_rad_emit) / G;
        Ts_next = Ts + dt * f;

        // Logging of variables
        boundary_layer_temperature[i] = T_bl;
        convection_coefficient[i] = h;
        if (i != time.size() - 1) 
        {
            skin_temperature[i + 1] = Ts_next;
        }
        Ts = Ts_next;
    }
    CsvWriter writer;
    writer.addColumn("Time [s]", time);
    writer.addColumn("Free Stream Temperature [K]", air_temperature);
    writer.addColumn("Boundary Layer Temperature [K]", boundary_layer_temperature);
    writer.addColumn("Skin Temperature [K]", skin_temperature);
    writer.addColumn("Convective Heat Transfer Coefficient [W/m^2-K]", convection_coefficient);
    return writer.writeFile(filename, '\t');
}



