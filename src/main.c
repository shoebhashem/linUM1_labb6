#include <stdlib.h>
#include <stdio.h>
#include <power.h>
#include <resistance.h>
#include <component.h>

int main() {

	float volt;
	char conn;
	int count;
	int i;
	float *array;

	printf("Ange spänningskälla i V:");
	scanf("%f", &volt);

//printf( "spänningen är %f", volt);
	printf("Ange koppling[S|P]:");
	scanf(" %c", &conn);

	printf("Ange antal komponenter:");
	scanf("%d", &count);
	array = malloc(count*sizeof(float));
	//float array []=new float array [count];
	for (i=1; i<=count;i++){
		printf("Komponent %d i ohm:", i);
		scanf("%f", &array[i-1]);
	}

	printf("Ersättningsresistans:\n");
	float er_r = calc_resistance(count, conn, array);
	printf("%.1f ohm\n", er_r);
	printf("Effekt:\n");
	float power = calc_power_r(volt, er_r);
	printf("%.2f W\n",power);
	printf("Ersätningsresistanser i E12-serien kopplade i serie:\n");
	free(array);
	float res_array [3];
	count = e_resistance(er_r, res_array);
	for (i=0; i<count;i++){
		printf("%.0f\n", res_array[i]);
	}
   return 0;
}
