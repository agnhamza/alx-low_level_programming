#include "main.h"
#include "stdio.h"

/**
 * times_table - prints the 9 times table, starting with 0
 */
void times_table(void){
	int tab[10][10];
	int k =0;
	for (int i = 0 ; i < 10; i++){
		for (int j = 0 ; j < 10;j++){
	   		tab[i][j]=k+k;
			printf("%d, ",k+k);
		}
	printf("\n");
	k++;

	}

}
