#include<stdio.h>
#include<curl/curl.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>

/*
 * TODO:    grep -A (lines after found) :DONE Done
 *
 *          cut -c foo   the first foo characs --> extra function, 'cause many
 *          NULL pointers in cut needed :DONE Done
 *
 *          tail selbiges wie unten???
 *
 *          head geht das nicht mit verschieben des Lesepointers????
 *
 *          curl :DONE
 *
 *          cat -b and cat -n (number first: non-blank lines, second: all lines)
 *
 *          is cut -f3- <-- the minus   already implement??? test it! :DONE Done
 *
 *          learn how to add lines to a file and how to create a file :DONE
 *
 *          add rating of food if no rating was there including making new
 *          groups and adding food to this groups --> SEE CHANGED CONCEPT
 *
 *          extracting the parts of food and find the value for it and getting
 *          the best food for the day by comparing the sums
 *
 */
char* frstln(const char inputfile[]);
char* lstln(const char inputfile[]);
char* frstnchr(char* input, int n);
char* cut(char* input, const char* delim, int fieldstart, int fieldstop);
int find(const char inputfile[], const char searchstring[], int linesafter=0);
FILE* findfile;
int main()
{
    char text[]="Guten Tag";
    char *cutten=cut(text,"t",2,1);
    find("testfile" , "ent",25);
    //printf("%s\n",frstnchr(text,7));
    printf("%s",frstln("testfile"));

}

char* frstln(const char inputfile[])
{
    FILE* input;
    char* output=(char*)malloc(2000);
    input=fopen(inputfile,"r");
    if(input==NULL) return NULL;
    fgets(output, 2000, input);
    return output;
    free(output);
}

char* frstnchr(char* input, int n)
{
    char* outputstr;
    if(n>=strlen(input))
    {
        outputstr=(char*)malloc(sizeof(input));
        outputstr=input;
    }
    else
    {
        outputstr=(char*)malloc(n+1);
        for(int i=0;i<n;i++) outputstr[i]=input[i];
    }
    return outputstr;
    free(outputstr);
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

int find(const char inputfile[], const char searchstring[], int linesafter)
{
    FILE *INPUT; //File-Pointer
    INPUT=fopen(inputfile, "rt");//Open File
    if (INPUT==NULL) printf("Error!");

    int numlines=0;
    int everfound=0;
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
    for(int i=0;i< numlines;i++) foundlines[i]=0;
    for(int i = 0; i< numlines; i++)
    {
        //puts("phasezero");
        int position;
        position=0;
        int found=0;

        while(position <= (strlen(lines[i])-strlen(searchstring)))
        {
            //puts("phase1");
            //puts("Das ist der Searchstring:");putchar(searchstring[0]);puts("");

            if( searchstring[0] == lines[i][position])
            {
                //puts("phase2");
                int stillok=1;
                for(int j=0; j<strlen(searchstring);j++)
                {
                    //puts("phase3");
                    if(stillok)
                    {
                        //puts("phase4");
                        if(searchstring[j]== lines[i][position+j])
                        {
                            //puts("phase5");
                            stillok=1;
                        }else
                        {
                          //  puts("phase6");
                            stillok=0;
                            position++; //if not we'd have an infinite loop
                            break;
                        }
                    }


                    if((stillok) && j==strlen(searchstring)-1)
                    {
                        //puts("phase7");
                        everfound=1;
                        found=1;
                        foundlines[i]=1; //ab zum nächsten
                        //printf("%s",lines[i]);
                        position++;
                    }
                }

            } else {//puts("phase8");
                    position++ ;}
            
            if (found) {//puts("phase9");
                        break;}

        }
    }
        //nun auf den linesafter Parameter eingehen
    for(int i=0; i< numlines; i++)
    {
        //printf("%i\n",foundlines[i]);
        if (foundlines[i]==1)
        {
            if (i+linesafter<numlines)
            {
                for(int j=1; j<=linesafter; j++)
                {
                    if(foundlines[i+j]!=1) foundlines[i+j]=2;
                }
            }
            else
            {
                for(int j=1; i+j<numlines;j++)
                {
                    if(foundlines[i+j]!=1) foundlines[i+j]=2;
                }
            }
        }


    }

    findfile=fopen("findoutput","w");
    for(int i=0; i<numlines;i++)
    {
        //printf("%i\n",foundlines[i]);
        if((foundlines[i]==1) || (foundlines[i]==2))
        {
            //puts("in file schreiben");
            fputs(lines[i],findfile);
        }
    }
    fclose(findfile);

    //irgendwo,irgendwie die gefundenen zeilen speichern, sodass andere fkt.
    //darauf zugreifen können. :DONE
    free(lines);
    free(*lines);
    //printf("Das ist linesafter: %i\n",linesafter);
    



//    INPUT=fopen(inputfile, "r");
//    char stringtest[100];
//    for (int i=1; i<=numlines;i++)
//    {
//        fgets(stringtest, 99, INPUT); !!!!THIS works... use it as example
//        printf("%s",stringtest);
//    }
//     fclose(INPUT);
//     return 0;//alles crap--> nochma nachschauen wegen array of chars
    if(everfound)
        return 1 ;
    else 
        return 0;


}
