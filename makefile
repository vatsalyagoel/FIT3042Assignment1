CC 	   = gcc
CFLAGS = -g -Wall -I.

all: clean rledecode rledecode_test

rledecode: rledecode rledecode.c decompress.c helpers.c rle.c main.c
	$(CC) $(CFLAGS) -o rledecode rledecode.c decompress.c helpers.c rle.c main.c

tests: clean_tests rledecode_test

rledecode_test: tests/rledecode_tests.c
	$(CC) $(CFLAGS) -o tests/rledecode_tests tests/rledecode_tests.c

clean: clean_bin clean_output clean_tests

clean_bin:
	$(RM) rledecode

clean_output:
	$(RM) ./ppm/*.ppm

clean_tests:
	$(RM) tests/rledecode_test