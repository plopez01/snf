#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *array;
	size_t used;
	size_t size;
} DynamicArray;

typedef struct {
	DynamicArray* array;
	size_t used;
	size_t size;
} MultiDynamicArray;

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


void initMultiArray(MultiDynamicArray* a, size_t initialSize) {
	a->array = malloc(initialSize * sizeof(char));
	a->used = 0;
	a->size = initialSize;
}

void insertMultiArray(MultiDynamicArray* a, DynamicArray element) {

	if (a->used == a->size) {
		a->size *= 2;
		a->array = realloc(a->array, a->size * sizeof(char));
	}
	a->array[a->used++] = element;
}

void freeMultiArray(MultiDynamicArray* a) {
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
	DynamicArray dict1;

	MultiDynamicArray test;
	initMultiArray(&test, 4);


	initArray(&dict, 1);
	initArray(&dict1, 1);


	//Calculated compression dictionary
	char str[15] = "Hola que tal";

	char arr[5][15];

	int compressed[10];

	char* wordbuffer = malloc(strlen(str) * sizeof(char));

	int buffersize = 0;
	int wordcount = 0;
	int charcount = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') {
			
			buffersize = 0;
			continue;
		}
		buffersize++;
	}
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') {
			wordcount++;
			charcount = 0;
			continue;
		}
		arr[wordcount][charcount] = str[i];
		charcount++;
		//printf("%c", str[i]);
	}

	

	insertArray(&dict, 'H');
	insertArray(&dict, 'o');
	insertArray(&dict, 'l');
	insertArray(&dict, 'a');

	insertArray(&dict1, 'M');
	insertArray(&dict1, 'i');
	insertArray(&dict1, 'n');
	insertArray(&dict1, 'e');

	insertMultiArray(&test, dict);
	insertMultiArray(&test, dict1);

	

	printf("%c", test.array[1].array[0]);


	return 0;
	
	// Reprogramming Compression
	for (int i = 0; i < wordcount + 1; i++) {
		
		//Check if already on dict
		for (int x = 0; x < dict.size; x++) {
			if (strcmp(arr[i], dict.array[x])) {
				compressed[i] = x;
				break;
			}
		}

		
		//If not, add to dict and write to compressed array

		//If exist just write to compressed array with correspondent id

	}


	//START DEPRECATION

	//Creation of the dictionary
	for (int i = 0; i < wordcount; i++) {
		int isRepeated = 0;
		for (int j = 0; j < sizeof(dict.array); i++) {
			if (dict.array[j] == arr[i]) {
				isRepeated = 1;
			}
		}
		if (!isRepeated) {
			dict.array[i] = arr[i];
		}
	}

	//File compression with dictionary
	//static int compressed[15];
	for (int i = 0; i < wordcount; i++) {
		for (int j = 0; j < sizeof(dict.array); j++) {
			if (arr[i] == dict.array[j]) {
				compressed[i] = j;
			}
		}
	}

	//END DEPRECATION


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
		while (fgets(buffer, sz, fp)) {
			printf("%s", buffer);
		}

		printf("\n%d", sz);

			

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