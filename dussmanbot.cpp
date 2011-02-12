#include<stdio.h>
#include<curl/curl.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>
#define _FILE_OFFSET_BITS 64 /* for pre libcurl 7.19.0 curl_off_t magic */
/*
 * TODO:    grep -A (lines after found) :DONE Done
 *
 *          cut -c foo   the first foo characs --> extra function, 'cause many
 *          NULL pointers in cut needed :DONE Done
 *
 *          tail selbiges wie unten??? nö :DONE    F I X M E 
 *
 *          head geht das nicht mit verschieben des Lesepointers???? kein Plan,
 *          jetzt eine extra Funktion:DONE Done    F I X M E
 *
 *          curl :DONE
 *
 *          cat -b and cat -n (number first: non-blank lines, second: all lines)
 * 			 -- das kann man über eine einfache Funktion machen wie bei find und
 * 			so
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
int loginandcookie(char* userid, char* passwd);
int kalwochen(char* userid, char* passwd);
char* frstln(const char inputfile[]);
char* lstln(const char inputfile[]);
char* frstnchr(char* input, int n);
char* cut(char* input, const char* delim, int fieldstart, int fieldstop);
int find(const char inputfile[], const char searchstring[], int linesafter = 0);
FILE* findfile;

int main()
{
	char uid[5], pwd[5];
	//char** slynmbwochen;
	printf("Herzlich willkommen. Ich bin ihr persönlicher Essensberater!\n \n");
	printf("Was ist ihre Benutzernummer: ");
	scanf("%s",uid);
	printf("Was ist ihr Passwort: ");
	scanf("%s",pwd);
	//loginandcookie(uid,pwd);
	////find("kalendera","<select name=\"sel_datum\" class=\"no_print\" onchange=\"document.form_sel_datum.submit()\">",12);
	kalwochen(uid, pwd); //wat solls MEGA FICKEN.
    char text[] = "Guten Tagderefd\npens\0i";
    char *cutten = cut(text, "t", 2, 2);
    printf("%s",cutten);
    //find("testfile", "ent");
    ////printf("%s\n",frstnchr(text,7));
    //printf("%s", frstln("testfile"));
}


char* frstln(const char inputfile[])
{
    FILE* input;
    char c;
    int charcount=2000;
    input = fopen(inputfile, "r");
    if (input == NULL) return NULL;
//    while((c=fgetc(input)) != '\n')
//    {
//        charcount++;
//    }
    rewind(input);
    char* output = (char*) malloc(charcount * sizeof(char*));
    fgets(output, charcount, input);
    fclose(input);
    //printf("%s",output);
    char* firstline=output;
    //printf("%s",firstline);
    free(output);
    //printf("%s",firstline);
    return firstline;
    
}

char* lstln(const char inputfile[])
{
    FILE* input;
    input = fopen(inputfile, "r");
    if (input == NULL) return NULL;
    int numlines=0;
    char c;
    char* lastline= (char*)malloc(2000);
    while ((c = fgetc(input)) != EOF)
    {
        if (c == '\n')
        {
            numlines++;
        }
    }
    rewind(input);
    for(int i=1; i<=numlines; i++)
    {
        fgets(lastline, 2000, input);
    }
    fclose(input);
    //printf("%s",lastline);
    char* lstline=lastline;
    free(lastline);
    return lstline;


}

char* frstnchr(char* input, int n)
{
    char* outputstr;
    if (n >= strlen(input))
    {
        outputstr = (char*) malloc(sizeof (input));
        outputstr = input;
    }
    else
    {
        outputstr = (char*) malloc(n + 1);
        for (int i = 0; i < n; i++) outputstr[i] = input[i];
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
    int counter = 1;
    bool began = false;
    char* output;
    int maxlength;
    int startpos=0;
    int charcount=0;
    int fldcount=1;
    printf("stringlenge %i\n",strlen(input));
    //output = (char*) malloc(strlen(input));
    int outputstart = -2;
    for(int i=0;i<strlen(input);i++)
    {
		if(input[i]==delim[0]) fldcount++;

		if((fldcount>=fieldstart) && (fldcount<=fieldstop) && (input[i]!=delim[0])) charcount++;
				if(input[i]<32) break;
	}
	printf("fotze %i\n",charcount);
    output = (char*) malloc(charcount);
    for (int i = 0; i < strlen(input); i++)
    {
        if (outputstart != -2) outputstart++;
        if ((input[i] == delim[0]))
        {
            counter++;
        }
        if (counter > fieldstop) 
        {
			output[outputstart]='\0';
			break;
		}
		if(i+1-charcount>startpos) {output[outputstart]='\0';break;}
		if((input[i]=='\n') || (input[i]=='\0')){break; output[outputstart]=='\0';}
		//if(outputstart+startpos>strlen(input))
		//{
			//output[outputstart]='\0'; break;
		//}
		//if(input[i]<=10) break;

        if ((counter == fieldstart) && (began == false))
        {
            began = true;
            startpos=i;
            printf("startpos %i\n",startpos);
            if (fieldstart != 1) outputstart = -1;
            if (fieldstart == 1) outputstart = 0;
        }
        if ((counter >= fieldstart) && (outputstart >= 0))
        {
            output[outputstart] = input[i];
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
    INPUT = fopen(inputfile, "rt"); //Open File
    if (INPUT == NULL) printf("Error!");

    int numlines = 0;
    int everfound = 0;
    char c;
    while ((c = fgetc(INPUT)) != EOF)
    {
        if (c == '\n') numlines++;
    }
    //printf("%d\n", numlines);
    fclose(INPUT);
    //printf("%d", numlines ); now it works --> go to toilet

    INPUT = fopen(inputfile, "r");
    char** lines;
    lines = (char **) calloc(numlines, sizeof (char *));
    for (int i = 0; i < numlines; i++)
    {
        lines[i] = (char*) malloc(2000 * sizeof (char*));
        //printf("test %i\n",i);
        fgets(lines[i], 2000, INPUT);
    } //HOLY Shit: It WORKS! --> Implement finding a substring in those lines
    //puts("testblablub");
    //putchar(lines[4][2]);
    
    int foundlines[numlines];
    for (int i = 0; i < numlines; i++) 
    {
		foundlines[i] = 0;
		//printf("%s",lines[i]);
	}
    //printf("penis\n");
    for (int i = 0; i < numlines; i++)
    {
        int position;
        position = 0;
        int found = 0;
		//printf("penis %i   \n",i);
		//int platz = strlen(lines[i]) - strlen(searchstring);
		if( (strlen(lines[i]) - strlen(searchstring)) >=0)
		{
			//puts("ficken");
			if(strstr(lines[i],searchstring) != NULL)
			{
				//printf("pimmerle %i   \n",i);
				everfound=1;
				foundlines[i]=1;
			}
		}
/*
        //while (position <= platz)
        //{
			//if(position > platz) break;
			
            //if (searchstring[0] == lines[i][position])
            //{
                //int stillok = 1;
                //for (int j = 0; j < strlen(searchstring); j++)
                //{ // TODO: printf(differenz stringlänge lines und searchstring ausgeben für debuggen)
					
                    //if (stillok)
                    //{
                        //if (searchstring[j] == lines[i][position + j])
                        //{
							//printf("%i  ",strlen(lines[i]));
							//printf("%i\n",i);
                            //stillok = 1;
                        //}
                        //else
                        //{
                            //stillok = 0;
                            //position++; //if not we'd have an infinite loop
                            //break;
                        //}
                    //}
                    

                    //if ((stillok) && j == strlen(searchstring) - 1)
                    //{
                        //everfound = 1;
                        //found = 1;
                        //foundlines[i] = 1; //ab zum nächsten
                        ////printf("%s",lines[i]);
                        //position++;
                    //}
                    //if(position > platz) break;
                //}

            //}
            //else position++;

            //if (found) break;

        //} */
    }
    //puts("haben wirs geschafft?");
    //nun auf den linesafter Parameter eingehen
    for (int i = 0; i < numlines; i++)
    {
        //printf("%i\n",foundlines[i]);
        if (foundlines[i] == 1)
        {
            if (i + linesafter < numlines)
            {
                for (int j = 1; j <= linesafter; j++)
                {
                    if (foundlines[i + j] != 1) foundlines[i + j] = 2;
                }
            }
            else
            {
                for (int j = 1; i + j < numlines; j++)
                {
                    if (foundlines[i + j] != 1) foundlines[i + j] = 2;
                }
            }
        }
    }

    findfile = fopen("findoutput", "w");
    for (int i = 0; i < numlines; i++)
    {
        //printf("%i\n",foundlines[i]);
        if ((foundlines[i] == 1) || (foundlines[i] == 2))
        {
            //puts("in file schreiben");
            fputs(lines[i], findfile);
        }
    }
    fclose(findfile);

    //irgendwo,irgendwie die gefundenen zeilen speichern, sodass andere fkt.
    //darauf zugreifen können. :DONE
    free(lines);
    //free(*lines);
    
    
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
    if (everfound)
        return 1;
    else
        return 0;


}

int loginandcookie(char* userid, char* passwd)
{
	FILE* essen;
	essen=fopen("kalendera","w");
	char postfield[100];
	strcpy(postfield,"Login_Name=");
	strcat(postfield,userid);
	strcat(postfield,"&Login_Passwort=");
	strcat(postfield,passwd);
	CURLcode ret;
	CURL *hnd = curl_easy_init();
	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, essen);
	curl_easy_setopt(hnd, CURLOPT_INFILESIZE_LARGE, -1);
	curl_easy_setopt(hnd, CURLOPT_URL, "http://www.dussmann-lpf.rcs.de/index.php?m=1;3&a=akt_login");
	curl_easy_setopt(hnd, CURLOPT_PROXY, NULL);
	curl_easy_setopt(hnd, CURLOPT_PROXYUSERPWD, NULL); 
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, postfield);
 	curl_easy_setopt(hnd, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; U; Linux i686; de; rv:1.9.2.12) Gecko/20101027 Firefox/3.6.12");
	curl_easy_setopt(hnd, CURLOPT_COOKIEFILE, NULL);
	curl_easy_setopt(hnd, CURLOPT_COOKIEJAR, "Cookiedatei");
	ret = curl_easy_perform(hnd);
	curl_easy_cleanup(hnd);
	fclose(essen);
	return (int)ret;
	
	
}

int kalwochen(char* userid, char* passwd)
{
	int numwochen=0;
	int startwoche;
	char* startwochenbuffer;
	startwochenbuffer=(char*)malloc(sizeof(char*)*3);
	FILE* wochenliste;
	//if(kalender==NULL) return 0;
	find("kalendera","<select name=\"sel_datum\" class=\"no_print\" onchange=\"document.form_sel_datum.submit()\">",12);
	find("findoutput","KW");
	wochenliste=fopen("findoutput","r");
	char c;
	while((c=fgetc(wochenliste)) != EOF)
	{
		if(c == '\n') numwochen++;
	}
	fclose(wochenliste);
	printf("penis %s\n",cut(frstln("findoutput"),":",2,2));
	startwochenbuffer=cut(cut(frstln("findoutput"),":",2,2)," ",2,2);
	//startwochenbuffer[1]+=4;
	//printf("pimmel %c\n",startwochenbuffer[0]);
	for(int i=48; i<=53; i++)
	{
		if(startwochenbuffer[0]==i) 
		{
			startwoche=10*(i-48);
			break;
		}
	}
	for(int i=48;i<=57; i++)
	{
		if(startwochenbuffer[1]==i)
		{
			startwoche+=(i-48);
			break;
		}
	}
	printf("startwoche: %i und anzahlwochen: %i\n",startwoche,numwochen);
	
		
}

