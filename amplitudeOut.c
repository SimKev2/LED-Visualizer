
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sndfile.h>

#define BLOCK_SIZE 512

int main (int argc, char*argv[]) {
    char        *infilename;
    SNDFILE	 	*infile = NULL ;
//  FILE		*outfile = NULL ;
    SF_INFO	 	sfinfo ;
    
    infilename = argv [1];
    infile = sf_open (infilename, SFM_READ, &sfinfo);
    printf("%lld \n",sfinfo.frames);
    int channels = sfinfo.channels;
    
    
    float buf [channels * BLOCK_SIZE];
    int k, m, readcount;
    float maxVal = 0, minVal = 0;
    while ((readcount = sf_readf_float (infile, buf, BLOCK_SIZE)) > 0) {
    
        for (k = 0 ; k < readcount ; k++) {
            for (m = 0 ; m < channels ; m++) {
                float curr = buf[k*channels+m];
                printf (" % 12.10f", curr) ;
//                if(curr>maxVal) maxVal = curr;
//                if (curr<minVal) minVal = curr;
                }
            printf ("\n") ;
            }
    }
//    printf("\nMax:\n%12.10f\n",maxVal);
//    printf("\nMin\n%12.10f\n",minVal);
    
    
    sf_close (infile);
}
