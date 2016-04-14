#include <stdio.h>
#include "decompress.h"

/*********************************************************
*      DECOMPRESS PACKBIT DATA USING VARIANT SCHEME
*********************************************************/

/*********************************************************
* Desc   : Function to read a file and uncompress 1 frame 
*          of VPackbit Data which is copied to the pointer 
*          passed to the function
*
* Params : *rle_file_pointer   - file pointer to the input
*                                stream
*          *current_frame_data - Byte array to store the 
*                                decompressed data 
*          dimensions          - The width * height value 
*                                of the image/video
*        
* Return : None 
*********************************************************/
void rle_packbit_decompress(FILE *rle_file_pointer, unsigned char *current_frame_data, int dimensions)
{    
   	int count_char;
    int current_char;
    int counter = 0;
    int min_run_length = 3;

    
    while (counter < (dimensions * 3))
    {
        count_char = fgetc(rle_file_pointer);

        /* Force it to have a sign */
        count_char = (char)count_char;

        if (count_char < 0)
        {
            /* Found a run, write out 2 - count_char copies */
            count_char = (min_run_length - 1) - count_char;

            if (EOF == (current_char = fgetc(rle_file_pointer)))
            {
                count_char = 0;
            }

            while (count_char > 0)
            {
            	//printf("%c", current_char);
                current_frame_data[counter] = current_char;
                counter++;
                count_char--;
            }
        }
        else
        {
            /* Found a block of count_char + 1 symbols to copy */
            for (count_char++; count_char > 0; count_char--)
            {
                if ((current_char = fgetc(rle_file_pointer)) != EOF)
                {
                	//printf("%c", current_char);
                    current_frame_data[counter] = current_char;
                    counter++;
                }
                else
                {
                    break;
                }
            }
        }
    }
}