#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INIT_BLOCK 43
#define SAMPLING_RATE 44100

int main()
{
    FILE *fp = NULL;
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    long int i = 0;
    void* buf;
    void* buf2;
    int t;
    int t1 = 8820;
    double g = 0.707;
    double order = 3;
    double* buft;
    double* buftt;
  
    fp = fopen("datat.wav", "r");
    if(fp == NULL)
	{
	    printf("FILE COULD NOT BE READ\n");
	    exit(-1);
	}
  
    fp1 = fopen("Newdatat.wav", "w");
    if(fp1 == NULL)
	{
	    printf("FILE COULD NOT BE OPENED\n");
	    exit(-1);
	}

    fp2 = fopen("rev.txt", "w");
    if(fp2 == NULL)
	{
	    printf("FILE COULD NOT BE OPENED\n");
	    exit(-1);
	}

    printf("PLEASE SET TIME OF SAMPLING : ");
    scanf("%d", &t);
    t = 2*t;
    getchar();
  
    buf = malloc(INIT_BLOCK*sizeof(short));
    buf2 = malloc(t*SAMPLING_RATE*(sizeof(short)));
    buft = malloc(t*SAMPLING_RATE*(sizeof(double)));
    buftt = malloc(t*SAMPLING_RATE*(sizeof(double)));
    
//============= Reading from file part ===================//
    i = 0;
    while(i<(INIT_BLOCK-1))
	{
	    i = i + fread(buf+i*sizeof(short), sizeof(short), INIT_BLOCK-i, fp);
	    printf("%ld\n",i);
	}
  
    i = 0;
    while(i<(t*SAMPLING_RATE-1))
	{
	    i = i + fread(buf2+i*sizeof(short), sizeof(short), t*SAMPLING_RATE-i, fp);
	    printf("%ld\n",i);
	}
//=======================================================//

    i=0;
    while(i<(t*SAMPLING_RATE-1))
	{
	    *(buft+i) = 0.05*(double)*(short*)(buf2+i*sizeof(short));
	    i++;
	}

    for(i = (order*t1); i<t*SAMPLING_RATE; i++)
	{
	    *(buftt+i) =  (   -g*( *(buft+i) ) + (1.0-g*g)*( *(buft+(i-t1)) + g*( *(buft+(i-2*t1))) + g*g*( *(buft+(i-3*t1))))   );
	}

    t1 = (int)((double)t1*0.33);
 
    for(i = (order*t1); i<t*SAMPLING_RATE; i++)
	{
	    *(buft+i) =  (   -g*( *(buftt+i) ) + (1.0-g*g)*( *(buftt+(i-t1)) + g*( *(buftt+(i-2*t1))) + g*g*( *(buftt+(i-3*t1))))   );
	}

    t1 = (int)((double)t1*0.31);

    for(i = (order*t1); i<t*SAMPLING_RATE; i++)
	{
	    *(buftt+i) = (   -g*( *(buft+i) ) + (1.0-g*g)*( *(buft+(i-t1)) + g*( *(buft+(i-2*t1))) + g*g*( *(buft+(i-3*t1))))   );
	}

    t1 = (int)((double)t1*0.34);
 
    for(i = (order*t1); i<t*SAMPLING_RATE; i++)
	{
	    *(buft+i) = (   -g*( *(buftt+i) ) + (1.0-g*g)*( *(buftt+(i-t1)) + g*( *(buftt+(i-2*t1))) + g*g*( *(buftt+(i-3*t1))))   );
	}
  
    t1 = (int)((double)t1*0.36);

    for(i = (order*t1); i<t*SAMPLING_RATE; i++)
	{
	    *(buftt+i) = (   -g*( *(buft+i) ) + (1.0-g*g)*( *(buft+(i-t1)) + g*( *(buft+(i-2*t1))) + g*g*( *(buft+(i-3*t1))))   );
	}

    t1 = (int)((double)t1*0.34);
 
    for(i = (order*t1); i<t*SAMPLING_RATE; i++)
	{
	    *(buft+i) = (   -g*( *(buftt+i) ) + (1.0-g*g)*( *(buftt+(i-t1)) + g*( *(buftt+(i-2*t1))) + g*g*( *(buftt+(i-3*t1))))   );
	}

    t1 = (int)((double)t1*0.32);

    for(i = (order*t1); i<t*SAMPLING_RATE; i++)
	{
	    *(buftt+i) = (   -g*( *(buft+i) ) + (1.0-g*g)*( *(buft+(i-t1)) + g*( *(buft+(i-2*t1))) + g*g*( *(buft+(i-3*t1))))  );
	}
    

    i = 0;
    while(i<(t*SAMPLING_RATE-1))
	{

	    *(buftt+i) = *(buftt+i)*22.0;
	    fprintf(fp2, "%lf\n", *(buftt+i));
	    *(short*)(buf2+i*sizeof(short)) = (short)(*(buftt+i));
	    i++;
	}

    free(buft);
    free(buftt);

//========== Writing to file part =======================//
    i = 0;
    while(i<INIT_BLOCK-1)
	i = i + fwrite(buf+i*sizeof(short), sizeof(short), INIT_BLOCK-i,  fp1);

    i = 0;
    while(i<(t*SAMPLING_RATE-1))
	i = i + fwrite(buf2+i*sizeof(short), sizeof(short), t*SAMPLING_RATE-i, fp1);
//=======================================================//

    free(buf);
    free(buf2);
        
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
  
    return 0;
}
