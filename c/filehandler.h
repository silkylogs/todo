#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t total_line_numbers(const char *filename);
char** extract_to_string_array(const char *filename);
void* free_string_array(char **strArray);

#endif