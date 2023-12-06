#include <stdio.h>
#include <string.h>

//https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

int read_labels(char* file_path, char **labels);
int read_images(char* file_path, char **images);

int read_labels(char* file_path, char **labels){
	FILE *file = fopen(file_path, "rb");
	int const buffer_block_size = 11000;
	int buffer_blocks = 1;

	*labels = malloc(buffer_blocks * buffer_block_size);

	int first_8_bytes;
	fread(&first_8_bytes, 8, 1, file);
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

	printf("\n\n");
	int const char_zero_ascii = 48;
	for(int i = 0; i < next_free_position; i++){
		char c = (*labels)[i]+char_zero_ascii;
		printf("%c", c);
	}
	printf("\n\n");
	return next_free_position;
}

int read_images(char* file_path, char **images){
	FILE *file = fopen(file_path, "rb");
	int const buffer_block_size = 11000;
	int buffer_blocks = 1;

	*images = malloc(buffer_blocks * buffer_block_size);

	int first_16_bytes;
	fread(&first_16_bytes, 16, 1, file);
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
			*images = realloc(*images, buffer_blocks * buffer_block_size);
			labels_buffer_size = buffer_blocks * buffer_block_size;
			labels_buffer_free_size = labels_buffer_size - next_free_position;
		}

		memcpy(*images+next_free_position, buffer, bytes_read);
		next_free_position += bytes_read;
	}
	fclose(file);

	printf("\n\n");
	int const char_zero_ascii = 48;
	for(int i = 0; i < next_free_position; i++){
		char c = (*images)[i]+char_zero_ascii;
		printf("%c", c);
	}
	printf("\n\n");
	return next_free_position;
}



void main(){
	printf("mnistrw");

	char* test_labels_file_path = "resource/mnist-dataset-binary/t10k-labels.idx1-ubyte";
	char* test_images_file_path = "resource/mnist-dataset-binary/t10k-images.idx3-ubyte";
	char* train_labels_file_path = "resource/mnist-dataset-binary/train-labels.idx1-ubyte";
	char* train_images_file_path = "resource/mnist-dataset-binary/train-images.idx3-ubyte";

	char char_zero = '0';
	int int_zero = 0;
	char *labels_address_initializer = &char_zero;
	int *labels_size_address_initializer = &int_zero;
	char **labels;
	int **labels_size;
	
	labels = &labels_address_initializer;
	labels_size = &labels_size_address_initializer;

	int test_labels_size = read_labels(test_labels_file_path, labels);
	int train_labels_size = read_labels(train_labels_file_path, labels);

}
 