#include<stdio.h>
#include<curl/curl.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>

char* cut(char* input, const char* delim, int fieldstart, int fieldstop);
char* find(const char inputfile[], const char searchstring[]);
int main()
{
    //char text[]="Guten Tag";
    //char *cutten=cut(text,"t",2,4);
    find("testfile" , "Ent");
    //printf("%s\n",cutten);
}


/******************************************************************************
 * The following routine is for cutting strings, does not include the start or*
 * end delimiter, but all characters that are between them                    *
 ******************************************************************************/
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

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

char* find(const char inputfile[], const char searchstring[])
{
    FILE *INPUT; //File-Pointer
    INPUT=fopen(inputfile, "rt");//Open File
    if (INPUT==NULL) printf("Error!");
    int numlines=0;
    char c;
    while( (c=fgetc(INPUT)) != EOF)
    {
        if (c =='\n') numlines++;
    }
    //printf("42"); //now it works --> go to toilet
    //printf("%d", numlines );
    //printf("42");
    return 0;

//    char* lines[numlines][];
//    for (int i=1; i<=numlines;i++)
//    {
//        fgets(lines[i][], sizeof(lines[i]), INPUT);
//    }

}
