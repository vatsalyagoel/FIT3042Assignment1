#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "helpers.h"

// void print_usage()
// {

// }
static char s_time[32];

void get_current_time()
{
	time_t ltime; /* calendar time */
	struct tm tim;
    
    ltime=time(NULL); /* get current cal time */
    localtime_r(&ltime, &tim);
    asctime_r(&tim, s_time);

    s_time[strcspn(s_time, "\n")] = 0;
}

void log_debug(char *message)
{
	get_current_time();
	fprintf(stdout, "%s : %s\n", s_time , message);
}

void log_error(char *error_message)
{
	get_current_time();
	fprintf(stderr, "%s : %s\n", s_time , error_message);
}

int file_exists(char *filename) /* Verifies if the file exists in the system */
{
	if( access( filename, F_OK ) != -1 )
	{
	    return 1;
	} 
	else 
	{
	    return 0;
	}
}

void * rle_malloc(size_t size, char *module) /* Defensive aproach for malloc() */
{
	void *ptr = malloc(size);
	get_current_time();
	fprintf(stdout,"%s : Allocated %d bytes for Module %s\n", s_time, (int)size, module);

	if(ptr != NULL)
	{
		fprintf(stdout, "%s : Successfully Allocated %d bytes for Module %s\n", s_time, (int)size, module);
	}
	else
	{
		fprintf(stderr, "%s : Unable to allocate %d bytes for Module %s\n", s_time, (int)size, module);
		rle_exit();
	}
	return ptr;
}


void rle_free(void *ptr, char *pointer_name) /* Defensive aproach for malloc() */
{
	free(ptr);
	get_current_time();
	fprintf(stdout, "%s : freeing pointer %s\n", s_time, pointer_name );

	if(ptr != NULL)
	{
		fprintf(stdout, "%s : Successfully freed pointer %s\n", s_time, pointer_name );
	}
	else
	{
		fprintf(stderr, "%s : Error freeing pointer %s\n", s_time, pointer_name );
		rle_exit();
	}
}

void rle_exit()
{
	fprintf(stdout, "An Error Occured. The program will exit now.\n");
	fprintf(stdout, "An Error Occured. The logs can be accessed at ~/rledecode/error.log");
	exit(-1);
}
