#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "rle.h"

/*************************************************************
*   FUNCTIONS DEFINED FOR THE PURPOSE OF MANIPULATING RLE
*                     	   OBJECTS
*************************************************************/

/*************************************************************
* Desc   : Function to create a new Frame object and 
*		   assign memory for all the channels. It gets the
*		   current_frame_data, splits it into RGB.
*
* Params : dimensions          - The Pixel size of each frame
*		   *current_frame_data - decompressed VPackbit data
*
* Return : frame - pointer to the newly created frame object
**************************************************************/
Frame * new_frame(int dimensions, unsigned char *current_frame_data)
{
	Frame *frame = rle_malloc(sizeof(frame), "New Frame");

	frame -> red = (unsigned char *) rle_malloc(dimensions * sizeof(unsigned char), "Red data");
	frame -> green = (unsigned char *) rle_malloc(dimensions * sizeof(unsigned char), "Green data");
	frame -> blue = (unsigned char *) rle_malloc(dimensions * sizeof(unsigned char), "Blue data");

	split_rgb_values(current_frame_data, frame, dimensions);

	return frame;
}

/*********************************************************
* Desc   : Function to free all memory allocated to an
*		   Rle Object (Struct)
*
* Params : *rle - Pointer to RLE Object
*
* Return : None
*********************************************************/
void free_rle_object(Rle *rle)
{
	int num = rle -> num_images ;

	while(--num > 0)
	{
		rle_free(rle -> frames[num] -> red, "red");
		rle_free(rle -> frames[num] -> green, "green");
		rle_free(rle -> frames[num] -> blue, "blue");
		rle_free(rle -> frames[num], "frame");
	}

	rle_free(rle -> header -> property, "property");
	rle_free(rle -> header, "header");
	rle_free(rle, "rle");
}