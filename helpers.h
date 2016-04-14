//void print_usage(); /* Prints the usage of the program */
void rle_exit();

void get_current_time(); 

void log_debug(char *message);

void log_error(char *error_message); /* Prints The Error message to stderr */

int file_exists(char *filename); /* Verifies if the file exists in the system */

void * rle_malloc(size_t size, char *module); /* Defensive aproach for malloc() */

void rle_free(void *ptr, char *pointer_name); /* Defensive approach for free() */