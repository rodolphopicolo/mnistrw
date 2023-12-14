#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../bitmap/bitmap.c"


//https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

int read_labels(char* file_path, char **labels);
int read_images(char* file_path, char **images);
void create_images(char *output_dir, char *name, int name_size, char *labels, int labels_size, char *images);

char* create_file_name(char *output_dir, char *name, int name_size, int label, int occurrence);


char* create_file_name(char *output_dir, char *name, int name_size, int label, int occurrence){
	int const CHAR_ZERO = 48;
	char *file_name = malloc(128);
	char label_char = CHAR_ZERO + (char)label;

	sprintf(file_name,"%s/%s-%05d-%c.bmp", output_dir, name, occurrence, label_char);

	return file_name;
}


void create_images(char *output_dir, char *name, int name_size, char *labels, int labels_size, char *images){
	mkdir(output_dir, 0771);
	char const char_zero = 48;

	int const WIDTH = 28;
	int const HEIGHT = 28;
	int const SIZE = WIDTH * HEIGHT;
	int const DPI = 96;

	struct rgb_data *pixels = malloc(sizeof(struct rgb_data)*SIZE);
	for(int i = 0; i < labels_size; i++){
		int label = (int)*(labels + i);
		char *file_name = create_file_name(output_dir, name, name_size, label, i+1);

		int image_first_index = i * SIZE;
		int image_last_index = image_first_index + SIZE - 1;

		for(int j = 0; j < SIZE; j++){
			int index = i * SIZE + j;
			unsigned char value = images[index];
			// struct rgb_data *pixel = pixels + j; //Desse jeito a imagem fica de ponta cabeça, temos que inverter.
			
			int col = j % WIDTH;
			int row = (j - col)/28;
			int inverted_row = HEIGHT - row - 1;
			int inverted_row_first_position = inverted_row * WIDTH;
			int pixel_position = inverted_row_first_position + col;
			struct rgb_data *pixel = pixels + pixel_position;

			pixel->r = value;
			pixel->g = value;
			pixel->b = value;
		}
		save_bitmap(file_name, WIDTH, HEIGHT, DPI, pixels);
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
	char* test_labels_file_path = "resource/mnist-dataset-binary/t10k-labels.idx1-ubyte";
	char* test_images_file_path = "resource/mnist-dataset-binary/t10k-images.idx3-ubyte";
	char* train_labels_file_path = "resource/mnist-dataset-binary/train-labels.idx1-ubyte";
	char* train_images_file_path = "resource/mnist-dataset-binary/train-images.idx3-ubyte";

	char *labels_address_initializer = NULL;
	char **labels = &labels_address_initializer;
	
	char *images_address_initializer = NULL;
	char **images = &images_address_initializer;

	char *output_dir = "./output";

	int test_labels_size = read_labels(test_labels_file_path, labels);
	int test_images_size = read_images(test_images_file_path, images);
	char *test_name = "test";
	create_images(output_dir, test_name, 4, *labels, test_labels_size, *images);

	int train_labels_size = read_labels(train_labels_file_path, labels);
	int train_images_size = read_images(train_images_file_path, images);
	char *train_name = "train";
	create_images(output_dir, train_name, 5, *labels, train_labels_size, *images);

}
 