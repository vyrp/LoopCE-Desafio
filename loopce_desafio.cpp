#include <cstdio>

int main(){
	FILE *file = fopen("testImage.bmp", "rb");

	if (file) {
		printf("File opened.\n");
		
		// Header
		int offset = 0, width = 0, height = 0;
		
		fseek(file, 0xA, SEEK_SET);
		fread(&offset, /*size*/ 4, /*count*/ 1, file);

		fseek(file, 0x12, SEEK_SET);
		fread(&width, /*size*/ 4, /*count*/ 1, file);
		
		fseek(file, 0x16, SEEK_SET);
		fread(&height, /*size*/ 4, /*count*/ 1, file);
		
		printf("Pixels offset: %d\n", offset);
		printf("Width: %d\n", width);
		printf("Height: %d\n", height);
		
		
		// Pixels
		char byte = 0, ch = 0;
		int count = 0, padding = (4 - (3*width) % 4) % 4; // Assuming 24 bits per pixel
		
		fseek(file, offset, SEEK_SET);
		
		printf("\nMessage:\n\n");
		for(int row = 0; row < height; row++){
			for(int col = 0; col < width * 3; col++){
				// Read a byte and take its LSB
				fread(&byte, /*size*/ 1, /*count*/ 1, file);
				ch |= (byte & 1) << count;
				count++;
				
				// If character completed
				if (count == 8) {
					if (ch == 0) {
						goto eom; // Reached '\0'. Go to End of Message
					}
					printf("%c", ch);
					count = 0;
					ch = 0;
				}
			}
			
			// Ignore padding
			for(int col = 0; col < padding; col++){
				fread(&byte, /*size*/ 1, /*count*/ 1, file);
			}
		}
		
		eom:
		printf("\n<eom>\n");
		
		fclose(file);
	} else {
		printf("Could not open file.\n");
	}
	
	return 0;
}