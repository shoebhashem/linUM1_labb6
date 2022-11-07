/* This program calcultes power
*/
#include "libpower.h"
#include <stdio.h>

/**
@param voltage and resistance
return the calculted power
*/

float calc_power_r(float volt, float resistance)
{
	float power;
	power = (volt*volt)/resistance;
	return power;
}


/**
@param voltage and resistance
return the calculted power
*/
float calc_power_i(float volt, float current)
{
	float power;
	power = volt * current;
	return power;
}

// testing the code:

/*int main(){
float volt = 50;
float resistance = 1380;
float current = 25;
float power;
power = calc_power_r(volt, resistance);
printf("%f\n", power);
power = calc_power_i(volt, current);
printf("%f\n", power);
}*/-
