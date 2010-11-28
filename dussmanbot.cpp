#include<stdio.h>
#include<curl/curl.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>

char* cut(char* input, const char* delim, int fieldstart, int fieldstop);

int main()
{
    char text[]="Guten Tag";
    char *cutten=cut(text,"t",2,4);
    printf("%s\n",cutten);
}

char* cut(char input[], const char delim[], int fieldstart, int fieldstop)
{
    int counter=1;
    bool began = false;
    char* output;
    output=(char*)malloc(sizeof(input)+1);
    int outputstart=-2;
    for(int i=0;i<strlen(input) ;i++)
    {
        if (outputstart!=-2) outputstart++;
        if ((input[i]==delim[0]))
        {
            counter++;
        }
        if (counter>fieldstop) break;
        if (/*(fieldstart!=1) && */(counter==fieldstart) && (began==false))
        {
            began=true;
            if (fieldstart!=1) outputstart=-1;
            if (fieldstart==1) outputstart=0;
        }
        if ((counter>=fieldstart) && (outputstart>=0))
        {
           output[outputstart]=input[i];
        }
    }
    return output;
    free(output);
}