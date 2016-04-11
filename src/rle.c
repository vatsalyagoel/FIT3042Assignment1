#include <stdio.h>
#include "rledecode.h"

typedef struct
{
	Header *header;
	Frame *frames;
} Rle;