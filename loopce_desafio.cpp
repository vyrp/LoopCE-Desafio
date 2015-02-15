#include <cstdio>
#include <cassert>

int main(){
	FILE *file = fopen("testImage.bmp", "rb");

	if (file) {
		printf("File opened.\n");
		
		int offset = 0, width = 0, height = 0;
		
		assert(fseek(file, 0xA, SEEK_SET) == 0);
		assert(fread(&offset, /*size*/ 4, /*count*/ 1, file) == 1);

		assert(fseek(file, 0x12, SEEK_SET) == 0);
		assert(fread(&width, /*size*/ 4, /*count*/ 1, file) == 1);
		
		assert(fseek(file, 0x16, SEEK_SET) == 0);
		assert(fread(&height, /*size*/ 4, /*count*/ 1, file) == 1);
		
		printf("Pixels offset: %d\n", offset);
		printf("Width: %d\n", width);
		printf("Height: %d\n", height);
		
		fclose(file);
	} else {
		printf("Could not open file.\n");
	}
	
	return 0;
}