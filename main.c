#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rle.h"
#include "helpers.h"

/* Flag for optional arguments */
static int tween_flag = 0;
static unsigned long scale_factor = 1, tween_factor;
static char *prefix, *rlefile;
static Rle *rle;

int main(int argc, char *argv[])
{
	char *inptr;
	long int input;

	/* Setup the streams */
	freopen( "./logs/error.log", "w", stderr );

	/* Send the streams some text */ 
	log_error("Start of rledecode" );
	
	if(argc < 2) /* 2 required arguments */
	{
		//print_usage() /* printing how to use the application */
		return 0;
	}
	else
	{
		prefix = argv[2];
		rlefile = argv[1];

		if(!file_exists(rlefile))
		{
			log_error("The file you entered does not exist");
			rle_exit();
		}

		rle = parse_rle(rlefile);

		generate_ppm_files(rle, prefix);
		int i;
		for(i = 3; i < argc; i++) /* Exluding Program name and required arguments */
		{
			if(strcmp(argv[i], "--scale") == 0) /* Handling scale flag */
			{
				//*inptr = "\0";
				input = strtol(argv[i+1], &inptr, 10);

				if(inptr != NULL && *inptr == (char)0)
				{
					scale_factor = input;
				}
				else
				{
					scale_factor = 1;
					log_error("You must enter a valid integer for scale factor. Using default value of 1");
				}
			}	

			if(strcmp(argv[i], "--tween") == 0) /* Handling tween flag */
			{
				tween_flag = 1;
				//*inptr = "\0";
				input = strtol(argv[i+1], &inptr, 10);

				if(inptr != NULL && *inptr == (char)0)
				{
					tween_factor = input;
				}
				else
				{
					tween_factor = 1;
					log_error("You must enter a valid integer for tween factor. Not going to tween images");
				}
			}
		}
	}
	free_rle_object(rle);
	return 0;
}
