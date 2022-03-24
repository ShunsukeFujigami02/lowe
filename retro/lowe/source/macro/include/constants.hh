#ifndef CONSTANTS_HH
#define CONSTANTS_HH
const double v_light = 29.9792458; // (cm/ns)
const double n_water = 1.38072381233779451; 
const double v_light_in_water = v_light/n_water; //(cm/ns)
const double rv_light_in_water = 1./v_light_in_water;
const double PI = 3.14159265359;
const double SKRadius = 1696.32; // (cm)
const double SKLength = 3637.84; // (cm)
const double HKRadius = 3550.53; // (cm)
const double HKLength = 5497.84; // (cm)
const double e = 2.718281828459;
const double offset = 950.; // (ns)

#endif
