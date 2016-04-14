#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "helpers.c"
#include "minunit.h"

int tests_run = 0;

static char * test_filexists_true()
{
	printf("Test File exists True\n");
    char filename[1024];
    getcwd(filename, sizeof(filename));
    strcat(filename, "/tests/blank.txt");
	mu_assert("\nError: test_filexists_true\n", file_exists(filename) == 1);
    return 0;
}

static char * test_filexists_false()
{
	printf("Test File exists False\n");
	char *filename;
	filename = "./blah.txt";
	mu_assert("\nError: test_filexists_false\n", file_exists(filename) == 0);
    return 0;
}

static char * rle_malloc_test()
{
	printf("Test rle_malloc\n");
	mu_assert("\nError: test_rle_malloc\n", rle_malloc(50, "tests") != NULL);
	return 0;
}

static char * rle_free_test()
{
	printf("Test rle_free\n");
	void * ptr= rle_malloc(50, "tests");
	mu_assert("\nError: test_rle_free\n",  ptr!= NULL);
	rle_free(ptr, "test");
	return 0;
}

static char * all_tests()
{
    mu_run_test(test_filexists_true);
    mu_run_test(test_filexists_false);
    mu_run_test(rle_malloc_test);
    mu_run_test(rle_free_test);
    return 0;
}

int main(int argc, char **argv)
{
    printf("********************RLE DECODE TESTS**********************\n");

    char *result = all_tests();
    if (result != 0)
    {
        printf("\n*****************TESTS FAIL****************************");
        printf("%s\n", result);
    }
    else
    {
        printf("\n****************ALL TESTS PASSED***********************\n");
    }

    printf("Number of tests run: %d\n", tests_run);
    printf("***********************RLE DECODE TESTS************************\n");

    return result != 0;
}