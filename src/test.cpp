#include <iostream>
#include <vector>
#include <fstream>
#include "CsvReader.hpp"
#include "vectorMath.hpp"
#include "AeroHeating.hpp"
#include "stringHelper.hpp"

enum METHOD {zero_dimensions, one_dimension};

// Model control struct
struct ModelControls
{
    std::string flight_data_file;
    std::string domain;
    std::string outfile;
    METHOD method; 
};


// Read the model controls file
int readControls(ModelControls &controls, std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "could not read file - exiting" << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line))
    {
        int sep_position = line.find(":");
        if (sep_position < line.size())
        {
            std::string parameter_name = line.substr(0, sep_position);
            std::string parameter_value = line.substr(sep_position + 1, line.size());
            parameter_name = trim(parameter_name);
            parameter_value = trim(parameter_value);
            if (parameter_name.compare("FLIGHTDATA") == 0)
            {
                controls.flight_data_file = parameter_value;
            } 
            else if (parameter_name.compare("DOMAIN") == 0)
            {
                controls.domain = parameter_value;
            } else if (parameter_name.compare("METHOD") == 0)
            {
                if (parameter_value.compare("transient0d") == 0)
                {
                    controls.method = zero_dimensions;
                } 
                else if (parameter_value.compare("transient1d") == 0)
                {
                    controls.method = one_dimension;
                } else
                {
                    std::cout << "Invalid computation method" << std::endl;
                }
            } else if (parameter_name.compare("OUTFILE") == 0)
            {
                controls.outfile = parameter_value;
            } else 
            {
                std::cout << "Unrecognised parameter: " << parameter_name << std::endl;
            }
        }
    }
    return 0;
}

// Test basic usage of the CsvReader class
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments" << std::endl;
        return 1; // Should only get one argument
    }

    // Read the control file
    ModelControls controls;
    readControls(controls, argv[1]);

    // Declarations
    CsvReader flightDataReader;
    CsvReader thermalDataReader;
    std::vector<double> X, R, density, specific_heat, thickness, thermal_conductivity, emissivity, absorptivity;
    std::vector<double> time, air_temperature, pressure, velocity;

    // Read the flight data
    flightDataReader.readFile(controls.flight_data_file);
    flightDataReader.getColumn(time, 0);
    flightDataReader.getColumn(air_temperature, " Air temperature (°C)");
    flightDataReader.getColumn(pressure, " Air pressure (mbar)");
    flightDataReader.getColumn(velocity, " Total velocity (m/s)");

    // Convert units
    add(air_temperature, 273.15); // Convert deg C to K
    multiply(pressure, 1.0e2f); // Convert mbar to Pa

    // Read the geometry and thermal data
    thermalDataReader.readFile(controls.domain);
    thermalDataReader.getColumn(X, "X");
    thermalDataReader.getColumn(R, "R");
    thermalDataReader.getColumn(density, "DENSITY");
    thermalDataReader.getColumn(specific_heat, "SPECIFIC HEAT");
    thermalDataReader.getColumn(thickness, "THICKNESS");
    thermalDataReader.getColumn(thermal_conductivity, "THERMAL_CONDUCTIVITY");
    thermalDataReader.getColumn(emissivity, "EMISSIVITY");
    thermalDataReader.getColumn(absorptivity, "ABSORPTIVITY");

    // Calculate the arc length and total heat capacity
    std::vector<double> G, l, theta;
    G = multiply(density, multiply(specific_heat, thickness));
    l = arcLengthArray(l, X, R);
    theta = tangentAngle(theta, X, R);
    multiply(theta, 2.0f);

    // Run the simulation
    std::cout << "Running simulation" << std::endl;

    // Start from index 1 as this is first nonzero value - HT = 0 at X = 0
    for (int i = 1; i < X.size(); i++)
    {
        std::string outfile = controls.outfile + to_string(i) + ".csv";
        transient_0d(time, air_temperature, pressure, velocity, theta[i], l[i], G[i], emissivity[i], absorptivity[i], outfile);
    }
    std::cout << "Simulation Done" << std::endl;
    return 0;
}