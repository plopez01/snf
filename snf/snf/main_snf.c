#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	//File to compress
	FILE *fp;
	errno_t err;
	
	//Open file to compress
	err = fopen_s(&fp, argv[1], "rb");

	if (err == 0) {
		
		//Gets file size
		fseek(fp, 0L, SEEK_END);
		unsigned int sz = ftell(fp);
		rewind(fp);

		//Reserves memory to store file data
		unsigned char* buffer = malloc(sz * sizeof(unsigned char));

		//Reads binary data from the file
		size_t fcontent = fread(buffer, sz, 1, fp);

		//Prints the binary data
		for (int i = 0; i < sz; i++)
			printf("%u ", buffer[i]);

		//Closes read file
		fclose(fp);

		//Free allocated memory
		free(buffer);

		return 0;
	}
	else {
		//ERROR
		fprintf(stderr, "Cannot open file");
		return 1;
	}

	
}