#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include "rledecode.h"

/* Flag for optional arguments */
static int tween_flag = 0;
static unsigned long scale_factor = 1, tween_factor;
static char *prefix, *rlefile;
static FILE *;
int main(int argc, char *argv[])
{
	char *inptr;
	long int input;

	if(argc < 2) /* 2 required arguments */
	{
		print_usage() /* printing how to use the application */
	}
	else
	{
		*prefix = argv[2];
		*rlefile = argv[1];

		if(!file_exists(*filename))
		{
			fprintf(stderr, "The file you entered does not exist\n");
			goto exit;
		}

		if(!verify_rlefile(*rlefile))
		{
			fprintf(stderr, "The file you entered is not a valid rlefile\n");
			goto exit;
		}

		for(i = 3; i < argc; i++) /* Exluding Program name and required arguments */
		{
			if(strcmp(argv[i], "--scale") == 0) /* Handling scale flag */
			{
				*inptr = NULL;
				input = strtol(argv[i+1], &inptr, 10);

				if(inptr != NULL && *inptr == (char)0)
				{
					scale_factor = input;
				}
				else
				{
					scale_factor = 1;
					fprintf(stderr, "You must enter a valid integer for scale factor. Using default value of 1\n");
				}
			}	

			if(strcmp(argv[i], "--tween") == 0) /* Handling tween flag */
			{
				tween_flag = 1;
				*inptr = NULL;
				input = strtol(argv[i+1], &inptr, 10);

				if(inptr != NULL && *inptr == (char)0)
				{
					tween_factor = input;
				}
				else
				{
					scale_factor = 1;
					fprintf(stderr, "You must enter a valid integer for tween factor. Not going to tween images\n");
				}
			}
		}
	}



	exit:
		printf("An Error Occured. The program will exit now.\n");
		return;
}
