#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>


//https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

int read_labels(char* file_path, char **labels);
int read_images(char* file_path, char **images);
void create_images(char *name, int name_size, char *labels, int labels_size, char *images);

char* create_file_name(char *name, int name_size, int label, int occurrence);


char* create_file_name(char *name, int name_size, int label, int occurrence){
	int const CHAR_ZERO = 48;
	char *file_name = malloc(17);
	char label_char = CHAR_ZERO + (char)label;

	sprintf(file_name,"%s-%05d-%c.bmp", name, occurrence, label_char);

	return file_name;
}


void create_images(char *name, int name_size, char *labels, int labels_size, char *images){
	char *output_path = "./output";
	mkdir(output_path, 0771);
	char const char_zero = 48;

	for(int i = 0; i < labels_size; i++){
		int label = (int)*(labels + i);
		char *file_name = create_file_name(name, name_size, label, i+1);

		printf("\n%d - %s", label, file_name);
	}
}


int read_labels(char* file_path, char **labels){
	FILE *file = fopen(file_path, "rb");
	int const buffer_block_size = 11000;
	int buffer_blocks = 1;

	*labels = malloc(buffer_blocks * buffer_block_size);

	char first_8_bytes[8];;
	fread(first_8_bytes, 8, 1, file);
	int buffer_size = 2048;
	char buffer[buffer_size];
	int bytes_read;
	int quantity_of_buffers_to_read = 1;
	int quantity_of_bytes_to_read = buffer_size;
	int next_free_position = 0;
	while((bytes_read = fread(buffer, quantity_of_buffers_to_read, quantity_of_bytes_to_read, file)) > 0){

		int labels_buffer_size = buffer_blocks * buffer_block_size;
		int labels_buffer_free_size = labels_buffer_size - next_free_position;
		while (labels_buffer_free_size < bytes_read){
			buffer_blocks++;
			*labels = realloc(*labels, buffer_blocks * buffer_block_size);
			labels_buffer_size = buffer_blocks * buffer_block_size;
			labels_buffer_free_size = labels_buffer_size - next_free_position;
		}

		memcpy(*labels+next_free_position, buffer, bytes_read);
		next_free_position += bytes_read;
	}
	fclose(file);

	return next_free_position;
}

int read_images(char* file_path, char **images){
	FILE *file = fopen(file_path, "rb");
	int const buffer_block_size = 11000;
	int buffer_blocks = 1;

	*images = malloc(buffer_blocks * buffer_block_size);

	char first_16_bytes[16];
	fread(first_16_bytes, 16, 1, file);
	int buffer_size = 28*28*1000;
	char buffer[buffer_size];
	int bytes_read;
	int quantity_of_buffers_to_read = 1;
	int quantity_of_bytes_to_read = buffer_size;
	int next_free_position = 0;
	while((bytes_read = fread(buffer, quantity_of_buffers_to_read, quantity_of_bytes_to_read, file)) > 0){

		int labels_buffer_size = buffer_blocks * buffer_block_size;
		int labels_buffer_free_size = labels_buffer_size - next_free_position;
		while (labels_buffer_free_size < bytes_read){
			buffer_blocks++;
			*images = realloc(*images, buffer_blocks * buffer_block_size);
			labels_buffer_size = buffer_blocks * buffer_block_size;
			labels_buffer_free_size = labels_buffer_size - next_free_position;
		}

		memcpy(*images+next_free_position, buffer, bytes_read);
		next_free_position += bytes_read;
	}
	fclose(file);

	return next_free_position;
}



void main(){
	printf("mnistrw");

	char* test_labels_file_path = "resource/mnist-dataset-binary/t10k-labels.idx1-ubyte";
	char* test_images_file_path = "resource/mnist-dataset-binary/t10k-images.idx3-ubyte";
	char* train_labels_file_path = "resource/mnist-dataset-binary/train-labels.idx1-ubyte";
	char* train_images_file_path = "resource/mnist-dataset-binary/train-images.idx3-ubyte";

	char char_zero_1 = '0';
	char *labels_address_initializer = &char_zero_1;
	char **labels;
	
	labels = &labels_address_initializer;

	char char_zero_2 = '0';
	char *images_address_initializer = &char_zero_2;
	char **images;
	
	images = &images_address_initializer;


	int test_labels_size = read_labels(test_labels_file_path, labels);
	int test_images_size = read_images(test_images_file_path, images);

	char *test_name = "test";
	create_images(test_name, 4, *labels, test_labels_size, *images);

	int train_labels_size = read_labels(train_labels_file_path, labels);
	int train_images_size = read_images(train_images_file_path, images);

	char *train_name = "train";
	create_images(train_name, 5, *labels, train_labels_size, *images);

}
 