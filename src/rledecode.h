'''
Function Prototypes
'''
void print_usage(); /* Prints the usage of the program */

void print_error(char *error_message); /* Prints The Error message to stderr */

int file_exists(char *filename); /* Verifies if the file exists in the system */

int verify_rlefile(char *filename); /* Verifies if the file entered is an rlefile */

void *rle_malloc(size_t size); /* Defensive aproach for malloc() */

void *rle_free(void *ptr); /* Defensive approach for free() */




