CC 	   = gcc
CFLAGS = -g -Wall -I.

all: clean rledecode

rledecode: rledecode decompress.c helpers.c rle.c rledecode.c main.c
	$(CC) $(CFLAGS) -o rledecode helpers.c rle.c decompress.c rledecode.c main.c

clean: clean_bin clean_output

clean_bin:
	$(RM) rledecode

clean_output:
	$(RM) ./ppm/*.ppm
