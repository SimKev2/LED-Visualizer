
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sndfile.h>
#include "monos.h"
#define BLOCK_SIZE 512

int main (int argc, char*argv[]) {
    
    if (argc!=2) {
        usage_exit();
    }
    
//    char        *outfilename = "out.wav";
    char        *infilename;
    SNDFILE	 	*infile = NULL ;
//    SNDFILE		*outfile = NULL ;
    SF_INFO	 	sfinfo;
    
//    remove (outfilename) ;
    infilename = argv [1];
//    memset (&sfinfo, 0, sizeof (sfinfo)) ;
    infile = sf_open (infilename, SFM_READ, &sfinfo);
    printf("%lld \n",sfinfo.frames); //prints number of samples (frames)
    
    
    
    if (sfinfo.channels == 1)
    {	printf ("Input file '%s' already mono. Exiting.\n", argv [argc - 2]) ;
        sf_close (infile) ;
        exit (0) ;
    } ;
    
    /* Force output channels to mono. */
    int channels = sfinfo.channels = 1 ;

    double buf [channels * BLOCK_SIZE];
    int k, readcount;
//    double maxVal = 0, minVal = 0;
    double buffer [1024] ;
    sf_count_t count ;
    
    while ((readcount = sfx_mix_mono_read_double (infile, buffer, ARRAY_LEN (buf))) > 0) {
    
        for (k = 0 ; k < readcount ; k++) {
                double curr = buffer[k*channels];
                printf (" % 12.10lf", curr); //prints each value
//                if (curr>maxVal) maxVal = curr;
//                if (curr<minVal) minVal = curr;
            printf ("\n");
            }
    }
//    printf("\nMax:\n%12.10f\n",maxVal);
//    printf("\nMin:\n%12.10f\n",minVal);
    
    
    sf_close (infile);
    //remove ("out.wav");
}
