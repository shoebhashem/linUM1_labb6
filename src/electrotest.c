#include <resistance.h>
#include <stdio.h>

int main(void)
{
  float res[2] = {1000, 2000};
  float r = calc_resistance(2, 'S', res);
  printf("%f\n", r);
}
