#ifndef MNISTRW_H
#define MNISTRW_H

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../bitmap/bitmap.c"


int read_labels(char* file_path, char **labels);
int read_images(char* file_path, char **images);
void create_images(char *output_dir, char *name, int name_size, char *labels, int labels_size, char *images);

char* create_file_name(char *output_dir, char *name, int name_size, int label, int occurrence);
void upside_down_to_up(char **image, int quantity_of_images);


#endif