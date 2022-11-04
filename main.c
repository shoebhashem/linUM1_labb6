#include <stdlib.h>
#include <stdio.h>

int main() {
	// printf() displays the string inside quotation
	float volt;
	char conn;
	int count;
	int i;
	float **array;

	printf("Ange spänningskälla i V:");
	scanf("%f", &volt);

//printf( "spänningen är %f", volt);
	printf("\nAnge koppling[S|P]:");
	scanf(" %c", &conn);

	printf("\nAnge antal komponenter:");
	scanf("%d", &count);
	array = malloc(count*sizeof(float *));
	//float array []=new float array [count];
	for (i=1; i<=count;i++){
		array[i]=(float*)malloc(100 *sizeof(float));
		printf("Komponent %d i ohm:", i);
		scanf("%f",array[i]);
		printf("\n");
	}

   return 0;
}
