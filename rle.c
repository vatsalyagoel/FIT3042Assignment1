#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "rle.h"

Frame * new_frame(int dimensions, unsigned char *current_frame_data)
{
	Frame *frame = rle_malloc(sizeof(frame), "New Frame");

	frame -> red = (unsigned char *) rle_malloc(dimensions * sizeof(unsigned char), "Red data");
	frame -> green = (unsigned char *) rle_malloc(dimensions * sizeof(unsigned char), "Green data");
	frame -> blue = (unsigned char *) rle_malloc(dimensions * sizeof(unsigned char), "Blue data");

	split_rgb_values(current_frame_data, frame, dimensions);

	return frame;
}

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