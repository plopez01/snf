#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Objecto de C
typedef struct {
	char *array;
	size_t used;
	size_t size;
} DynamicArray;


//Based from https://stackoverflow.com/questions/3536153/c-dynamically-growing-array and adapted to the program
//TODO: Maybe change system to only reserve necessary memory
void initArray(DynamicArray *a, size_t initialSize) {
	a->array = malloc(initialSize * sizeof(char));
	a->used = 0;
	a->size = initialSize;
}

void insertArray(DynamicArray *a, int element) {

	if (a->used == a->size) {
		a->size *= 2;
		a->array = realloc(a->array, a->size * sizeof(char));
	}
	a->array[a->used++] = element;
}

void freeArray(DynamicArray *a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

int main(int argc, char *argv[]) {

	//File to compress
	FILE *fp;
	errno_t err;
	
	//Dynamic array dictionary
	DynamicArray dict;
	initArray(&dict, 1);

	//Open file to compress
	err = fopen_s(&fp, argv[1], "r");

	if (err == 0) {
		
		//Gets file size
		fseek(fp, 1, SEEK_END);
		unsigned int sz = ftell(fp);
		rewind(fp);

		//Reserves memory to store file data
		char* buffer = malloc(sz * sizeof(char));

		//Reads text data from the file
		size_t fcontent = fgets(buffer, sz, fp);

		printf("%d\n", sz);

		//Prints the text data
		for (int i = 0; i < sz; i++) {

			printf("%c ", buffer[i]);
		}		

		//Closes read file
		fclose(fp);

		//Free allocated memory
		free(buffer);

		return 0;
	}
	else {
		//Prints error
		//TODO: print error details
		fprintf(stderr, "Cannot open file");
		return 1;
	}

	
}