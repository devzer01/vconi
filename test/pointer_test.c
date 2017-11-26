#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
	unsigned char *data = "abcdef";
	unsigned char **matrix = malloc(sizeof(unsigned char *) * 2);
	*matrix = malloc(sizeof(unsigned char) * 3);
	//memcpy(matrix, data, 6);
	*(matrix)   = (data);
	*(matrix+1) = (data+3);

	for (int i = 0; i < 2; i++) {
		for (int x = 0; x < 3; x++) {
			printf("%c ", matrix[i][x]);
		}
	}
	printf("%c ", matrix[0][0]);
/*
	*(matrix) = malloc(sizeof(unsigned int) * 1);
	*(matrix+1) = malloc(sizeof(unsigned int) * 2);
	*(matrix+2) = malloc(sizeof(unsigned int) * 3);
	*(matrix+4) = malloc(sizeof(unsigned int) * 4);

	*(*(matrix)) = 0xFAFAFAFA;
	*(*(matrix+1)) = 0xFFFFFFFF;
	*(*(matrix+1)+1) = 0xFFFFFFFA;

	printf("%d \n", **matrix+1);*/


	/*unsigned int row = 0, col = 0;
	while (row < 10) {
		*(matrix+row) = malloc(sizeof(unsigned int) * (row + 1));
		while (col < 10) {
			*(*(matrix+row)+col) = col * row;
			col++;
		}
		row++;
		col = 0;
	}
	while (row > 0) free(*(matrix + --row));
	free(matrix);*/
	return 0;
}
