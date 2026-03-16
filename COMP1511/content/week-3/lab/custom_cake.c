// Custom Cake
// custom_cake.c
//
// This program was written by Lucas Cheung (z5763342)
// on 05-03-2026
//
// Create a custom cake

#include <stdio.h>

int main(void) {
	int layer_number;
	printf("How many layers: ");
	scanf("%d", &layer_number);

	printf("Please enter layers: ");

	char layers[layer_number];

	int i = 0;
	while (i < layer_number) {
		scanf(" %c", &layers[i]);
		i++;
	}

	for (int k = 0; k < layer_number; k++) {
		for (int j = 0; j < layer_number; j++) {
			printf("%c", layers[k]);
		}
		printf("\n");
	}
	return 0;
}
