#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	//File to compress
	FILE *fp;
	errno_t err;
	
	//Dictionary
	unsigned int dict[20];
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