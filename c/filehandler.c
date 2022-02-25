#include "filehandler.h"
#define MAX_LINE_LENGTH 1024

size_t total_line_numbers(const char *filename){
	FILE *fp = NULL;
	size_t linecount = 0;

	if(filename == NULL){
		printf("filehandler.c: no filename specified for total_line_numbers() to open\n");
		exit(1);
	}

	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("filehandler.c: %s unable to be opened by ", filename);
		printf("total_line_numbers()\n");
		exit(1);
	}

	char line[MAX_LINE_LENGTH];
	while(fgets(line, MAX_LINE_LENGTH, fp) != NULL){
		linecount += 1;
	}
	fclose(fp);
	return linecount;
}

/* Note: to free an array of strings, free all elements first */
char** extract_to_string_array(const char *filename){
	char **pointer_to_array = NULL;
	char line[MAX_LINE_LENGTH];
	FILE *fp = NULL;

	/*
	 * Allocating memory for holding <linecount> of chars
	 * (Forming dimension 1 of array)
	 */
	size_t linecount = total_line_numbers(filename);
	//keep this line around for future debugging
	//printf("malloc-ing size %d\n", linecount * sizeof(char*));

	/*
	 * Extra element allocated to memory just to assign it to null
	 * This is to facilitate deallocation
	 */
	pointer_to_array = malloc((linecount * sizeof(char*)) + 1);
	if(pointer_to_array == NULL){
		printf("filehandler.c: unable to allocate memory for forming dimension ");
		printf("1 of string array in extract_to_string_array()\n");
		return NULL;
	}
	pointer_to_array[linecount] = NULL;


	/*
	 * Copying file contents to array
	 * (Forming dimension 2 of array)
	 */
	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("sorth.c: %s unable to be opened by ", filename);
		printf("extract_to_string_array() while copying file to str array\n");
		return NULL;
	}
	int i = 0;
	while(fgets(line, MAX_LINE_LENGTH, fp) != NULL){
		pointer_to_array[i] = malloc((strlen(line)+1) * sizeof(char));
		/* 
		 * for greater speed, but less stability on devices with
		 * miniscule heap space, consider commenting the following out
		 */
		if(pointer_to_array[i] == NULL){
			printf("filehandler.c: extract_to_string_array() ran out of ");
			printf("heap space while copying file contents to string array\n");
			return NULL;
		}		
		strcpy(pointer_to_array[i], line);
		i++;
	}
	fclose(fp);

	return pointer_to_array;
}

/* untested */
void* free_string_array(char **strArray){
	if(strArray == NULL){
		printf("filehandler.c: null pointer input detected by free_string_array() ");
		printf("input unmodified\n");
		return *strArray;
	}
	//char *str = &strArray;
	int i = 0;
	while(strArray[i] != NULL){
		free(strArray[i]);
	}
	free(strArray);
	strArray = NULL;
	return NULL;
}
