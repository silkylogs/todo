/*
 * PROGRAM FEATURES
 * todo is a minimalist command line based note-taking application.
 * 
 * todo without arguements prints out the earliest note added
 * todo -a "note" adds a note
 * todo -l numerically lists all notes
 * todo -d <note number> deletes a certain note, <notenumber> defaults to 1
 * todo -h lists this text
 */

/*
 * COMPILATION INSTRUCTIONS
 * To compile, compile all c files in directory
 * gcc -Werror -o todo *.c
 */

#define SAVEFILE "./todo-savefile.txt"

#include <stdio.h>
#include "filehandler.h"

void ShowTopNote(){
	char **lines = extract_to_string_array(SAVEFILE);
	if(lines[0] == NULL){
		printf("No note added to savefile \"%s\"\n", SAVEFILE);
		printf("Please initalize it with todo -a \"\"\n");
	}
	else {
		printf("%s\n", lines[0]);
	}
}

void AddNote(char *note){
	FILE *fp = fopen(SAVEFILE, "a");
	if(fp == NULL){
		printf("main.c: Addnote() is unable to open %s\n", SAVEFILE);
	}
	fprintf(fp, "%s\n", note);
	fclose(fp);
}

void ListAllNotes(){
	char **lines = extract_to_string_array(SAVEFILE);
	for(size_t i = 0; i < total_line_numbers(SAVEFILE); i += 1){
		if(lines[i] == NULL) { break; }
		printf("%I64u. %s", i + 1, lines[i]);
	}
}

void DeleteNote(int argc, char **argv){
	size_t indexToExclude = 0, linecount = total_line_numbers(SAVEFILE);
	char **lines = extract_to_string_array(SAVEFILE);
	
	FILE *fp = fopen(SAVEFILE, "w");
	if(fp == NULL){
		printf("main.c: DeleteNote() is unable to open %s\n", SAVEFILE);
	}

	if(argc == 2) { indexToExclude = 0; }
	else{ indexToExclude = (size_t)atoi(argv[2]) - 1; }

	for(size_t i = 0; i < linecount; i++){
		if(i == indexToExclude) { continue; }
		fputs(lines[i], fp);
		printf("%I64d. %s", i+1, lines[i]);
	}
	
	fclose(fp);
}

void ShowHelp(){
	printf("Program usage:\n");
	printf("todo without arguements prints out the earliest note added\n");
	printf("todo -a \"note\" adds a note\n");
	printf("todo -l numerically lists all notes\n");
	printf("todo -d <note number> deletes a certain note, <notenumber> defaults to 1\n");
	printf("todo -h lists this help text\n");
	printf("Save file path: %s\n", SAVEFILE);
}

int main(int argc, char **argv){
	if(argc == 1)			{ ShowTopNote(); }
	else if(argv[1][1] == 'a')	{ AddNote(argv[2]); }
	else if(argv[1][1] == 'l')	{ ListAllNotes(); }
	else if(argv[1][1] == 'd')	{ DeleteNote(argc, argv); }
	else{ ShowHelp(); }

	return 0;
}