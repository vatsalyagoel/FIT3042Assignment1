/*********************************************************
*	STRUCT DEFINITIONS BASED ON THE FORMAT SPECIFIED
*********************************************************/

/*********************************************************
* Name - Frame
* Members - *red   - red channel data
*			*blue  - blue channel data
*			*green - green channel data	
*********************************************************/
#ifndef FRAME_H
#define FRAME_H
	typedef struct
	{
		unsigned char *red;
		unsigned char *green;
		unsigned char *blue;
	} Frame;
#endif

/*********************************************************
* Name - Property
* Members - width  - Width of image
*			height - Height of image
*********************************************************/
#ifndef PROPERTY_H
#define PROPERTY_H
	typedef struct
	{
		unsigned int width;
		unsigned int height;
	} Property;
#endif

/*********************************************************
* Name - Header
* Members - id_string[10]   - should be read "RLEPLAYv1\n"
*			*property  		- Pointer to the dimensions
*********************************************************/
#ifndef HEADER_H
#define HEADER_H
	typedef struct
	{
		char id_string[10];
		Property *property;
	} Header;
#endif

/*********************************************************
* Name - RLE
* Members - *header   		- Pointer to video headers
*			*frames[100000] - array of pointers to frames
*							  Limit of 100000 images
*			num_images		- Number of images in a video
*********************************************************/
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
Rle * parse_rle(char *filename); 
void free_rle_object(Rle *rle);
void split_rgb_values(unsigned char *current_frame_data, Frame *frame, int dimensions);
void generate_ppm_files(Rle *rle, char *prefix);