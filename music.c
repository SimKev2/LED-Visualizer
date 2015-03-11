#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 44100.0 //read from file samples per second
#define DISPLAY_RATE 10.0
#define DISPLAY_MOD 30.0

void importFreq(double raw[], double refine[]);//FINISH_ME
void playDisplay(double refine[]);
double minFreq(double array[]);
double maxFreq(double array[]);
double avgFreq(double array[]);

int main(void)
{
    int songLength;//10*seconds

    //songLength = 20 * SAMPLE_RATE;//test
    scanf("%d\n", &songLength);//real

    songLength = songLength / SAMPLE_RATE * DISPLAY_RATE;

    double rawFreq[(int)SAMPLE_RATE/DISPLAY_RATE];

    double refineFreq[songLength];

    double testRefineFreq[songLength];

    importFreq(rawFreq, refineFreq);

    playDisplay(refineFreq);


    return 0;
}

void importFreq(double raw[], double refine[]){//FINISH_ME

    srand(time(NULL));

    int i, j;
    double rawImport=0.0;

    double max, min, average;

    for(i=0;i< songLength;i++){
        for(j=0;j<SAMPLE_RATE/DISPLAY_RATE;j++){//importing sound
            //raw[j] = 2.0*(double)rand()/(double)RAND_MAX - 1;//test

            scanf("%lf\n", &raw[j]);//real import

            rawImport += fabs(raw[j]);
        }

        refine[i] = ((rawImport / (SAMPLE_RATE/DISPLAY_RATE)) * DISPLAY_MOD);//change to be percent based off of the average value of the song.

        //find min, max, and average.

        rawImport =0.0;
    }
    printf("Frequency imported\n");//test

}

void playDisplay(double refine[]){
    int i = 0, j = 0;
    double t = clock()/((double)CLOCKS_PER_SEC);
    while(refine[i]!= '\0'){
        if(t <= clock()/((double)CLOCKS_PER_SEC) - .1){
            for(j=0;j<refine[i];j++){
                printf("*");
            }
            printf("\n");
            i++;
            t = clock()/((double)CLOCKS_PER_SEC);
        }
    }
    printf("end");//test
}

double minFreq(double array[]){
    double min;
    int i;
    for(i=0;array[i]!= '\0';i++){
        if(min > array[i]) min = array[i];
    }
    return min;
}

double maxFreq(double array[]){
    double max;
    int i;
    for(i=0;array[i]!= '\0';i++){
        if(max < array[i]) max = array[i];
    }
    return max;
}

double avgFreq(double array[]){
    double avg;
    int i;
    for(i=0;array[i]!= '\0';i++){
        avg+= array[i];
    }
    avg = avg/i;
    return avg;
}
