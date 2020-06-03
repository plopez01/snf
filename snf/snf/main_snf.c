#include <stdio.h>

int main(int argc, char *argv[]) {

	//File to compress
	FILE *fp;
	errno_t err;

	//File buffer
	unsigned char buffer[10];
	
	//Reads file to compress
	err = fopen_s(&fp, argv[1], "rb");

	if (err == 0) {
		size_t fcontent = fread(buffer, sizeof(buffer), 1, fp);

		for (int i = 0; i < sizeof(buffer); i++)
			printf("%u ", buffer[i]);


		return 0;
	}
	else {
		//ERROR
		fprintf(stderr, "Cannot open file");
		return 1;
	}

	
}