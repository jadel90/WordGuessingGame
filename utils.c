/*
#include <stdio.h>
#include <stdlib.h>
#define DICT_SIZE 5757
#define WORD_SIZE 5


void load_word_list(char dictionary[DICT_SIZE][WORD_SIZE+1]){
    
    char *file_name = "./word_list.txt";
	
	FILE* f = fopen(file_name, "r");
	int idx = 0;

	if (f == NULL){
		printf("%s does not exist. Please ensure you have downloaded it from Canvas.", file_name);
		printf("\n");
	}
	else{
		while(fscanf(f, "%s", dictionary[idx++]) != EOF);
	}

	
}
*/

#include <stdio.h>
#include <stdlib.h>

#define DICT_SIZE 5757
#define WORD_SIZE 5

void load_word_list(char dictionary[DICT_SIZE][WORD_SIZE + 1]) {
	const char *file_name = "./word_list.txt"; // Ensure the path is correct
	FILE *f = fopen(file_name, "r");
	int idx = 0;

	if (f == NULL) {
		perror("Error opening file"); // Use perror for more detailed error messages
		exit(EXIT_FAILURE); // Exit if the file cannot be opened
	} else {
		// Read words from the file until EOF or dictionary is full
		while (idx < DICT_SIZE && fscanf(f, "%5s", dictionary[idx]) == 1) {
			idx++;
		}
		fclose(f); // Close the file after reading
	}
}