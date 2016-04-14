#FIT3042 - System Tools and Programming Languages 
-------------------------------------------------------------------------------------------
									   Assignment 1
									IMAGE DECOMPRESSOR
									   VATSALYA GOEL
									     25404776
-------------------------------------------------------------------------------------------

##Build and Run
There is a makefile included in the root of the directory
To build and run the program simply type the command `make`
This command cleans any previous executable code and recompiles the code
This produces an executable rledecode

###Usage:
	NAME:
		rledecode - decodes an rleplay file and produces a sequence of images in PPM format.
	USAGE:
		./rledecode rlefile prefix|"-" [--tween tweenfactor] [--scale scalefactor]
			1. ./rledecode - program binary
			2. rlefile - input rle file 
			3. prefix|"-" - prefix if outputting images to file or \"-\" to output to stdout
			4. [--tween tweenfactor] - optional to insert n(tweenfactor) consecutive tweened frames
			5. [--scale scalefactor] - optional to scale each image by n(scalefactor)

##Basic Functionality
I have tried to make this code as modular and object oriented as possible.
helpers.c is a set of functions used to log and safely allocate/deallocate memory.
rle.h contains a set of structs that represent an rle object
an frame object has a constructor
the rle object has a destructor
The code is defined in seperate header files
validation of scale and tween flags are done propely
The basic functionality of the code works as expected thus produces ppm files when given an rle file

This has been tested with 

1. sonic.rle
2. sigle-sonic.rle
3. virtua.rle
4. single-virtua.rle

I have also tested with invalid files which stops the execution of the code gracefully

Limitation: the decoder supports upto 100000 frames only and will break after that. this is because the array that holds the pointers for frames is statically allocated as dynamic reallocation of memory was causing leaks.

##Extended Functionality
Although checks are in place and the flags work as expected the functionality to scale and tween has not been implemented.

##Testing
Most of the testing was done using gdb and manually. This changed as I used a unittest framework called minunit. It is a 3 line header file that runs unittests for us.

if we run `make test` on the command line it will generate a executable that runs unit tests. This can be executed by running `./tests/rledecode_tests`
The framwork can be found here: http://www.jera.com/techinfo/jtns/jtn002.html

##Cleaning
`make clean` will remove all the generated ppm files and executables.