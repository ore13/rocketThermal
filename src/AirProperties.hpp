#ifndef AIR_PROPERTIES
#define AIR_PROPERTIES

/*
Compute the specific heat based on the polynomial by 
Zografos and Sutherland
*/
double specific_heat(double &T);

/* 
Compute the viscosity using sutherland's law with coefficients from
White, Fluid Mechanics. (valid 200 - 2500K)
*/
double viscosity(double &T);

/* 
Compute the thermal conductivity (valid 200 - 2500K)
*/
double thermal_conductivity(double &T);

/*
Compute the density based on the ideal gas law (valid 200 - 2500K)
*/
double density(double &Pressure, double &Temperature);

/*
Compute the prandtl number (valid 200 - 2500K)
*/
double prandtl_number(double &T);

/*
Compute the enthalpy of air based on temperature (valid 200 - 2500K)
*/
double enthalpy(double &T);

/*
Compute the temperature of air based on enthalpy (valid 200 - 2500K)
*/
double temperature(double &h);

/*
Compute the speed of sound
*/
double sound_speed(double &T);
#endif