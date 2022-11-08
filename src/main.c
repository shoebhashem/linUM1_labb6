#include <stdlib.h>
#include <stdio.h>

#include "resistance.h"

int main() {

	float volt;
	char conn;
	int count;
	int i;
	float *array;

	printf("Ange spänningskälla i V:");
	scanf("%f", &volt);

//printf( "spänningen är %f", volt);
	printf("\nAnge koppling[S|P]:");
	scanf(" %c", &conn);

	printf("\nAnge antal komponenter:");
	scanf("%d", &count);
	array = malloc(count*sizeof(float));
	//float array []=new float array [count];
	for (i=1; i<=count;i++){
		printf("Komponent %d i ohm:", i);
		scanf("%f", &array[i-1]);
		printf("\n");
	}

	printf("Ersättningsresistans:\n");
	float er_r = calc_resistance(count, conn, array);
	printf("%f ohm\n", er_r);

	free(array);
   return 0;
}
