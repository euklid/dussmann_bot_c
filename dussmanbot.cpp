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
    find("testfile" , "ent");
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
    printf("%d\n",numlines);
    fclose(INPUT);
    //printf("%d", numlines ); now it works --> go to toilet

    INPUT=fopen(inputfile,"r");
    char** lines;
    lines = (char **)calloc(numlines, sizeof (char *));
    for(int i = 0; i < numlines; i++)
    {
        lines[i] = (char*)malloc(2000*sizeof(char*));
        fgets(lines[i],2000 , INPUT);
    }   //HOLY Shit: It WORKS! --> Implement finding a substring in those lines
    //putchar(lines[4][96]);

    int foundlines[numlines];
    for(int i = 0; i< numlines; i++)
    {
        //puts("phasezero");
        int position;
        position=0;
        int found=0;

        while(position <= (strlen(lines[i])-strlen(searchstring)))
        {
          //  puts("phase1");
            //puts("Das ist der Searchstring:");putchar(searchstring[0]);puts("");

            if( searchstring[0] == lines[i][position])
            {
              //  puts("phase2");
                int stillok=1;
                for(int j=0; j<strlen(searchstring);j++)
                {
                //    puts("phase3");
                    if(stillok)
                    {
                  //      puts("phase4");
                        if(searchstring[j]== lines[i][position+j])
                        {
                    //        puts("phase5");
                            stillok=1;
                        }else
                        {
                      //      puts("phase6");
                            stillok=0;
                            position++; //if not we'd have an infinite loop
                            break;
                        }
                    }


                    if((stillok) && j==strlen(searchstring)-1)
                    {
                        //puts("phase7");
                        found=1;
                        foundlines[i]=1; //ab zum nächsten
                        printf("%s",lines[i]);
                        position++;
                    }
                }

            } else {//puts("phase8");
                    position++ ;}
            
            if (found) {//puts("phase9");
                        break;}

        }
        //irgendwo,irgendwie die gefundenen zeilen speichern, sodass andere fkt.
        //darauf zugreifen können.
    }


//    INPUT=fopen(inputfile, "r");
//    char stringtest[100];
//    for (int i=1; i<=numlines;i++)
//    {
//        fgets(stringtest, 99, INPUT); !!!!THIS works... use it as example
//        printf("%s",stringtest);
//    }
//     fclose(INPUT);
//     return 0;//alles crap--> nochma nachschauen wegen array of chars

}
