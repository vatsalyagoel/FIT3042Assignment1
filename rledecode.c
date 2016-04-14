#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "helpers.h"
#include "rle.h"
#include "decompress.h"

/*************************************************************
*   FUNCTIONS DEFINED FOR THE PURPOSE OF DECODING RLE
*                     	   OBJECTS
*************************************************************/

/*********************************************************
* Desc   : Function to split current frame data to seperate
*		   into different RGB channels
*
* Params : dimensions          - The Pixel size of each frame
*		   *current_frame_data - decompressed VPackbit data
*		   *frame 		   	   - pointer to the frame object
*
* Return : None
*********************************************************/
void split_rgb_values(unsigned char *current_frame_data, Frame *frame, int dimensions)
{
    int red_index = 0;
    int green_index = 0;
    int blue_index = 0;
	int i = 0;

	while(i++ < (dimensions *3))
    {
        if (i < dimensions)
        {
            frame -> red[red_index++] = current_frame_data[i];
        }
        else if (i < (dimensions * 2))
        {
            frame -> green[green_index++] = current_frame_data[i];
        }
        else if (i < (dimensions * 3))
        {
            frame -> blue[blue_index++] = current_frame_data[i];
        }
    }
}

/*********************************************************
* Desc   : Function take in an existing rlefile and convert
*		   to RLE object
*
* Params : *rlefile - The name of the file
*
* Return : rle - pointer to rle object
*********************************************************/
Rle * parse_rle(char *rlefile)
{
	FILE *rle_file_pointer;

	Rle *rle = rle_malloc(sizeof(Rle), "New RLE object");
	rle -> header = rle_malloc(sizeof(Header), "New Header object");
	rle -> header -> property = rle_malloc(sizeof(Property), "New Property object");

	char dimension_buffer[20];
	char read = NULL;

	unsigned char *current_frame_data = NULL;

	rle_file_pointer = fopen(rlefile, "r");

	fgets(rle -> header -> id_string, 11, rle_file_pointer);
	fgets(dimension_buffer, 256, rle_file_pointer);


	if(strcmp(rle -> header -> id_string, "RLEPLAYv1\n") != 0)
	{
		log_error("The Header for the file is not correct and should be RLEPLAYv1");
		rle_exit();
	}

	rle -> header -> property -> width = atoi(strtok(dimension_buffer, " "));
	rle -> header -> property -> height = atoi(strtok(NULL, " "));
	if(!rle -> header -> property -> width || !rle -> header -> property -> height)
	{
		log_error("There was a problem in reading the dimensions of the file");
		rle_exit();
	}
	rle -> num_images = 0;
	
	while((read = fgetc(rle_file_pointer)) != EOF)
	{
		if(read == 'K')
		{
			current_frame_data = (unsigned char *)rle_malloc(rle -> header -> property -> width * rle -> header -> property -> height * 3 * sizeof(unsigned char), "current_frame_data");

			rle_packbit_decompress(rle_file_pointer, current_frame_data, (rle -> header -> property -> width*rle -> header -> property -> height));
			
			rle -> frames[rle -> num_images++] = new_frame((rle -> header ->property -> width*rle -> header ->property -> height), current_frame_data);	
		}
		if (read == 'E')
		{
			log_debug("Reached End of File");
		}
	}
	return rle;
}

/*********************************************************
* Desc   : Function take in an rlef object and save it to
*		   a file. if prefix is - it will be saved to stdout
*
* Params : *rle    - Pointert to RLE object
*		   *prefix - Prefix for file names | "-" if stdout
*
* Return : None
*********************************************************/
void generate_ppm_files(Rle *rle, char *prefix)
{
	FILE *ppm_file;
	int i;
	for(i = 0; i < rle -> num_images; i++ )
	{
		char fname[512];
		sprintf(fname, "./ppm/%s-%04d.ppm", prefix, (i+1)); 
		if(strcmp(prefix,"-") == 0)
		{
			ppm_file = stdout;
		}
		else
		{
			ppm_file = fopen(fname, "wb");
		}

		int index = 0;
		int h;
		int w;
		
		fprintf(ppm_file, "P6\n");
		fprintf(ppm_file, "%d %d\n", rle -> header ->property -> width, rle -> header ->property -> height);
		fprintf(ppm_file, "255\n");

	    index = 0;
	    for (h = 1; h <= rle -> header -> property -> height; h++)
	    {
	        for (w = 1; w <= rle -> header -> property -> width; w++)
	        {
	            fprintf(ppm_file, "%c", rle -> frames[i] -> red[index]);
	            fprintf(ppm_file, "%c", rle -> frames[i] -> green[index]);
	            fprintf(ppm_file, "%c", rle -> frames[i] -> blue[index]);
	            index++;
	        }
	    }
	}
}