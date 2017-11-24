#include <stdio.h>
#include <strings.h>
#include <stdlib.h>


int main()
{
	unsigned int **matrix = malloc(sizeof(unsigned int *) * 10);
	unsigned int row = 0, col = 0;
	while (row < 10) {
		*(matrix+row) = malloc(sizeof(unsigned int) * 10);
		while (col < 10) {
			*(*(matrix+row)+col) = col * row;
			col++;
		}
		row++;
		col = 0;
	}
	while (row > 0) free(*(matrix + --row));
	free(matrix);
	return 0;
}
