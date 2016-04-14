#ifndef FRAME_H
#define FRAME_H
	typedef struct
	{
		unsigned char *red;
		unsigned char *green;
		unsigned char *blue;
	} Frame;
#endif

#ifndef PROPERTY_H
#define PROPERTY_H
	typedef struct
	{
		unsigned int width;
		unsigned int height;
	} Property;
#endif

#ifndef HEADER_H
#define HEADER_H
	typedef struct
	{
		char id_string[10];
		Property *property;
	} Header;
#endif

#ifndef RLE_H
#define RLE_H
	typedef struct
	{
		Header *header;
		Frame *frames[100000];
		unsigned int num_images;
	} Rle;
#endif

Frame * new_frame(int dimensions, unsigned char *current_frame_data);

void free_rle_object(Rle *rle);

void split_rgb_values(unsigned char *current_frame_data, Frame *frame, int dimensions);

Rle * parse_rle(char *filename); 

void generate_ppm_files(Rle *rle, char *prefix);