#include <stdio.h>
#include "rledecode.h"

typedef struct
{
	uint *compressed;
	uint *uncompressed;
} Packbit;

Packbit * new_packbit(uint *compressed)
{
	Packbit *packbit;

	packbit.compressed = compressed;

	packbit.uncompressed = rle_uncompress(packbit.compressed);

	return *packbit;
}