#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sndfile.h>
#include <math.h>
#include <limits.h>

#define BLOCK_SIZE 512

#define ARRAY_LEN(x)	((int) (sizeof (x) / sizeof (x [0])))
#define MAX(x, y)		((x) > (y) ? (x) : (y))
#define MIN(x, y)		((x) < (y) ? (x) : (y))

static void
usage_exit (void)
{
    puts ("\n"
          "Usage :\n\n"
          "    <input file>\n"
          ) ;
    exit (0) ;
}

sf_count_t
sfx_mix_mono_read_double (SNDFILE * file, double * data, sf_count_t datalen)
{
    SF_INFO info ;
    
    sf_command (file, SFC_GET_CURRENT_SF_INFO, &info, sizeof (info)) ;
    
    if (info.channels == 1)
        return sf_read_double (file, data, datalen) ;
    
    static double multi_data [2048] ;
    int k, ch, frames_read ;
    sf_count_t dataout = 0 ;
    
    while (dataout < datalen)
    {	int this_read ;
        
        this_read = MIN (ARRAY_LEN (multi_data) / info.channels, datalen - dataout) ;
        
        frames_read = sf_readf_double (file, multi_data, this_read) ;
        if (frames_read == 0)
            break ;
        
        for (k = 0 ; k < frames_read ; k++)
        {	double mix = 0.0 ;
            
            for (ch = 0 ; ch < info.channels ; ch++)
                mix += multi_data [k * info.channels + ch] ;
            data [dataout + k] = mix / info.channels ;
        } ;
        
        dataout += frames_read ;
    } ;
    
    return dataout ;
} /* sfx_mix_mono_read_double */





int main (int argc, char*argv[]) {
    
    if (argc!=2) {
        usage_exit();
    }
    char       *infilename;
    SNDFILE    *infile = NULL ;
    SF_INFO    sfinfo;

    infilename = argv [1];

    infile = sf_open (infilename, SFM_READ, &sfinfo);
    printf("%lld \n",sfinfo.frames); //prints number of samples (frames)
    
    
    if (sfinfo.channels == 1)
    {
        float buf [BLOCK_SIZE];
        int k, readcount;
        // float maxVal = 0, minVal = 0;
        while ((readcount = sf_readf_float (infile, buf, BLOCK_SIZE)) > 0) {
            for (k = 0 ; k < readcount ; k++) {
                    float curr = buf[k];
                    printf (" % 12.10f\n", curr); //prints each value
                    // if (curr>maxVal) maxVal = curr;
                    // if (curr<minVal) minVal = curr;
            }
        }
    }
    
    else {
        /* Force output channels to mono. */
        int channels = sfinfo.channels = 1 ;

//        double buf [channels * BLOCK_SIZE];
        int k, readcount;
//    double maxVal = 0, minVal = 0;
        double buffer [1024] ;
        sf_count_t count ;
        while ((readcount = sfx_mix_mono_read_double (infile, buffer, ARRAY_LEN (buffer))) > 0) {
        for (k = 0 ; k < readcount ; k++) {
            double curr = buffer[k*channels];
            printf (" % 12.10lf\n", curr); //prints each value
//          if (curr>maxVal) maxVal = curr;
//          if (curr<minVal) minVal = curr;
            }
        }
//    printf("\nMax:\n%12.10f\n",maxVal);
//    printf("\nMin:\n%12.10f\n",minVal);
    }
    
    sf_close (infile);
}
