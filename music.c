#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SONG_LENGTH 1200 //read from file (10*seconds)
#define SAMPLE_RATE 44100.0 //read from file

void importFreq(double raw[], double refine[]);//FINISH_ME
void playDisplay(double refine[]);

int main(void)
{
    double refineFreq [SONG_LENGTH];
    double rawFreq [(int)SAMPLE_RATE/10];

    importFreq(rawFreq, refineFreq);

    playDisplay(refineFreq);


    return 0;
}

void importFreq(double raw[], double refine[]){//FIX_ME
    //magic importation

    srand(time(NULL));

    int i, j;
    double rawImport=0;

    for(i=0;i< SONG_LENGTH;i++){
        for(j=0;j<SAMPLE_RATE/10;j++){
            //raw[j] = 2.0*(double)rand()/(double)RAND_MAX - 1;//temp

            scanf("%lf\n", raw[j]);//final
            //printf("%lf # ",raw[j]);//test

            raw[j]++;
            rawImport += raw[j];
        }

        //printf("\n%lf\n",rawImport);//test

        refine[i] = ((rawImport/(SAMPLE_RATE/10.0)))*10;

        //printf("%lf\n",refine[i]);//test

        rawImport =0;
    }
    printf("Frequency imported\n");//TEMP

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
    printf("end");
}
//44100 samples per sec
