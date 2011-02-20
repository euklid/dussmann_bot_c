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
 *          is cut -f3- <-- the minus   already implement??? test it! nope F I X M E :Done 
 *
 *          learn how to add lines to a file and how to create a file :DONE
 *
 *          add rating of food if no rating was there including making new
 *          groups and adding food to this groups --> SEE CHANGED CONCEPT
 *
 *          extracting the parts of food and find the value for it and getting
 *          the best food for the day by comparing the sums
 * 
 * TODO: Werte für die Arraygrößen bei hidden und bergruen und bergruend usw. übergeben
 * 
 * TODO: Desserts nicht vergessen!!
 *
 */
 
int loginandcookie(char* userid, char* passwd);
int kalwochen(char* userid, char* passwd);
void tagesauswahl();
void getsel_datums();
void createmenufiles(char* userid, char* passwd);
void gethiddenandbestellt();
void getdatensatz();
void getrating();
char* frstln(char* dest, int size, char inputfile[]);
char* lstln(const char inputfile[]);
char* frstnchr(char* input, int n);
//char* cut(char* input, const char* delim, int fieldstart, int fieldstop);
char* cut2(char* inputstring, char* delim, int fieldstart, int fieldstop);
int find(const char inputfile[], const char searchstring[], int linesafter = 0);
FILE* findfile;
int startwoche=0, anzwoche=0;
int** setdates; //Array, das speichert, für welche Tage bestellt werden soll.
char** slynmbwochen; //Array, das Werte für sel_datum speichert, sodass bestellt werden kann.
char**** wocheplustagplusdaten; //[woche][tag][datensatz], datensatz=1: Menüname, 2: Variablenname, 3:wert, das gleich für menü 2 und vegetarisch weiter indizieren 
char*** hidden; //[woche][datensatz] datensätze: variablenname=wert
char*** bergruen; //speichert nur die grünen menüs, nicht die grünen dessert!!!
char*** bergruend; //der speichert die Desserts :-)
int ** wirkbestellen; //Für welche Tage wirklich bestellt werden soll
char*** bestelldaten; //Daten, die nicht hidden sind, also die Bestelldaten

int main()
{
	char uid[5], pwd[5];
	printf("Herzlich willkommen. Ich bin ihr persönlicher Essensberater!\n \n");
	printf("Was ist ihre Benutzernummer: ");
	scanf("%s",uid);
	printf("Was ist ihr Passwort: ");
	scanf("%s",pwd);
	//loginandcookie(uid,pwd);
	//////find("kalendera","<select name=\"sel_datum\" class=\"no_print\" onchange=\"document.form_sel_datum.submit()\">",12);
	kalwochen(uid, pwd); 
	tagesauswahl();
	getsel_datums();
	//createmenufiles(uid,pwd);
	gethiddenandbestellt();
	getdatensatz();
    //char text[] = "Guten Tagderefd\npens\0i";
    //char *cutten = cut(text, "t", 2, 2);
    //printf("%s",cutten);
    //find("testfile", "ent");
    ////printf("%s\n",frstnchr(text,7));
    //printf("%s", frstln("testfile"));
}

/*
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
    char* output = (char*) malloc(charcount * sizeof(char));
    fgets(output, charcount, input);
    fclose(input);
    //printf("%s",output);
	output[strlen(output)]='\0';
	//printf("%i",strlen(output));
	if(output[strlen(output)-1]=='\n') output[strlen(output)-1]='\0';
	return output;
    
} */

char* cut2(char* inputstring, char* delim, int fieldstart, int fieldstop)
{
	int fieldcount=1;
	int fldstart=fieldstart, fldstop=fieldstop;
	char* pch;
	char** fields;
	//char* output;
	int outputsize;
	char inputcpy[strlen(inputstring)+1];
	strcpy(inputcpy,inputstring);
	//puts("hello");
	pch=strtok(inputcpy, delim);
	while (pch != NULL)
	{
		//printf("%s\n",pch);
		pch = strtok (NULL,delim);
		fieldcount++;
		//printf("%i\n",fieldcount);
	}
	//puts("hillo");
	fieldcount--;
	//printf("%i",fieldcount);
	if(fieldstop>fieldcount) fldstop=fieldcount;
	if(fieldstart>fieldcount) return '\0';
	if(fieldstart>fieldcount) return'\0';
	if(fieldstart<=0) fldstart=1;
	fields=(char**)calloc(fieldcount,sizeof(char*));
	fieldcount=0;
	//puts("hallo");
	strcpy(inputcpy,inputstring);
	//puts("hi");
	pch=strtok(inputcpy,delim);
	fields[0]=(char*)malloc(sizeof(char)*(strlen(pch)+1));
	//puts("penis");
	strcpy(fields[0],pch);
	//printf("%s",fields[0]);
	//puts("haha");
	//printf("%s",fields[0]);
	do
	{
		pch=strtok(NULL,delim);
		fieldcount++;
		if(pch!=NULL) 
		{
			fields[fieldcount]=(char*)malloc(sizeof(char)*(strlen(pch)+1));
			strcpy(fields[fieldcount],pch);
		}
	}while(pch!= NULL);
	outputsize=fldstop-fldstart+1;
	for(int i=fldstart-1; i<fldstop;i++)
	{
		//printf("%s\n",fields[i]);
		outputsize+=strlen(fields[i]);
	}
	//printf("%i",outputsize);
	//puts("foo");
	//puts("bar");
	//output=(char*)malloc(outputsize); 
	strcpy(inputstring,fields[fldstart-1]);if(fldstart<fldstop) strcat(inputstring,delim);
	for(int i=fldstart; i<fldstop-1;i++)
	{
		strcat(inputstring,fields[i]);strcat(inputstring,delim);	
	}
	if(fldstart<fldstop) strcat(inputstring,fields[fldstop-1]);
	inputstring[outputsize-1]='\0';
	//output=(char*)malloc(outputsize);
	//for(int i=fldstart-1; i<fldstop-1;i++)
	//{
	//	strcat(output,fields[i]);strcat(output," ");	
	//}
	//strcat(output,fields[fldstop-1]);
	//output[outputsize-1]='\0';
	free(fields);
	//inputstring=strcpy(inputstring, output);
	//free(output);
	//printf("%s",inputstring);
	return inputstring;
}

char* frstln(char* dest,int size ,char inputfile[])
{
	FILE* input;
	input=fopen(inputfile,"r");
	fgets(dest, size, input);
	if(dest[strlen(dest)-1]=='\n') dest[strlen(dest)-1]='\0';
	else { if(strlen(dest)<size) dest[strlen(dest)]='\0';
			else dest[strlen(dest)-1]='\0';};
	fclose(input);
	return dest;
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
        outputstr = (char*) malloc(strlen(input)+1);
        outputstr = input;
    }
    else
    {
        outputstr = (char*) malloc(n + 1);
        for (int i = 0; i < n; i++) outputstr[i] = input[i];
        outputstr[n]='\0';
    }
    return outputstr;
    free(outputstr);
}

/******************************************************************************
 * The following routine is for cutting strings, does not include the start or*
 * end delimiter, but all characters that are between them                    *
 ******************************************************************************/

/*char* cut2(char inputstring[], char* delim, int fieldstart, int fieldstop)
{
	int fieldcount=1;
	int fldstart=fieldstart, fldstop=fieldstop;
	char* pch;
	char** fields;
	char* output;
	int outputsize;
	char inputcpy[strlen(inputstring)+1];
	strcpy(inputcpy,inputstring);
	//puts("hello");
	pch=strtok(inputcpy, delim);
	while (pch != NULL)
	{
		//printf("%s\n",pch);
		pch = strtok (NULL,delim);
		fieldcount++;
		//printf("%i\n",fieldcount);
	}
	//puts("hillo");
	fieldcount--;
	//printf("%i",fieldcount);
	if(fieldstop>fieldcount) fldstop=fieldcount;
	if(fieldstart>fieldcount) return '\0';
	if(fieldstart>fieldcount) return'\0';
	if(fieldstart<=0) fldstart=1;
	fields=(char**)calloc(fieldcount,sizeof(char*));
	fieldcount=0;
	//puts("hallo");
	strcpy(inputcpy,inputstring);
	//puts("hi");
	pch=strtok(inputcpy,delim);
	fields[0]=(char*)malloc(sizeof(char)*(strlen(pch)+1));
	//puts("penis");
	strcpy(fields[0],pch);
	//printf("%s",fields[0]);
	//puts("haha");
	//printf("%s",fields[0]);
	do
	{
		pch=strtok(NULL,delim);
		fieldcount++;
		if(pch!=NULL) 
		{
			fields[fieldcount]=(char*)malloc(sizeof(char)*(strlen(pch)+1));
			strcpy(fields[fieldcount],pch);
		}
	}while(pch!= NULL);
	outputsize=fieldstop-fieldstart+1;
	for(int i=fldstart-1; i<fldstop;i++)
	{
		//printf("%s\n",fields[i]);
		outputsize+=strlen(fields[i]);
	}
	//printf("%i",outputsize);
	//puts("foo");
	//puts("bar");
	output=(char*)malloc(outputsize); 
	strcpy(output,fields[fldstart-1]);if(fldstart<fldstop) strcat(output,delim);
	for(int i=fldstart; i<fldstop-1;i++)
	{
		strcat(output,fields[i]);strcat(output,delim);	
	}
	strcat(output,fields[fldstop-1]);
	output[outputsize-1]='\0';
	free(fields);
	return output;	
} */

/*char* cut(char input[], const char delim[], int fieldstart, int fieldstop) // ICH bin im Arsch --> nun mit strtok schreiben!
{
	
    int counter = 1;
    bool began = false;
    char* output;//free(output);
    int maxlength;
    int startpos=0;
    int charcount=0;
    int fldcount=1;
    //printf("stringlenge %i\n",strlen(input));
    //output = (char*) malloc(strlen(input));
    int outputstart = -2;
    for(int i=0;i<strlen(input);i++)
    {
		if(input[i]==delim[0]) fldcount++;

		if((fldcount>=fieldstart) && (fldcount<=fieldstop) && (input[i]!=delim[0])) charcount++;
		if(input[i]<32) break;
	}

	//printf("fotze %i\n",charcount);
    output = (char*)malloc(sizeof(char*)*charcount);free(output);    output = (char*)malloc(sizeof(char*)*charcount);//printf("fotze %i\n",charcount);
    //printf("Das ist outputs groeße: %i",sizeof(output));
    for (int i = 0; i < strlen(input); i++)
    {
		//printf("%i \n",strlen(output));
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
		if(i-charcount>startpos) { output[outputstart]='\0';break;}
		if((input[i]=='\n') || (input[i]=='\0')){ output[outputstart]=='\0';break;}

        if ((counter == fieldstart) && (began == false))
        {
            began = true;
            startpos=i;
            //printf("startpos %i\n",startpos);
            if (fieldstart != 1) outputstart = -1;
            if (fieldstart == 1) outputstart = 0;
        }
        if ((counter >= fieldstart) && (outputstart >= 0))
        {
            output[outputstart] = input[i];
            
        }
        //putchar(output[i-startpos-1]);
    }
    //printf("Das ist outputslenge: %i",strlen(output));
    return output;
    
} */

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
	curl_easy_setopt(hnd, CURLOPT_PROXY, "192.168.0.1:3128");
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
	//int numwochen=0;
	//int startwoche;
	//char* startwochenbuffer;
	//startwochenbuffer=(char*)malloc(sizeof(char*)*4);
	FILE* wochenliste;
	//if(kalender==NULL) return 0;
	find("kalendera","<select name=\"sel_datum\" class=\"no_print\" onchange=\"document.form_sel_datum.submit()\">",12);
	find("findoutput","KW");
	find("findoutput","selected=\"selected\"",12);
	wochenliste=fopen("findoutput","r");
	char c;
	while((c=fgetc(wochenliste)) != EOF)
	{
		if(c == '\n') anzwoche++;
	}
	fclose(wochenliste);
	//wochenliste=fopen("findoutput","r");
	puts("test");
	//fgets(buffer,130,wochenliste);
	//buffer[strlen(buffer)-1]='\0';
	char* puffer=(char*)malloc(150);
	frstln(puffer,150,"findoutput");
	printf("%s\n",puffer);
	//char*tmp=strdup(puffer);
	cut2(puffer,":",2,2);	
	//fclose(wochenliste);
	printf("%s \n",puffer);
	cut2(puffer," ",1,1);
	//free(puffer);
	printf("buffer is %s\n",puffer);
	//startwochenbuffer[1]+=4;
	//printf("pimmel %c\n",startwochenbuffer[1]);
	for(int i=48; i<=53; i++)
	{
		if(puffer[0]==i) 
		{
			startwoche=10*(i-48);
			break;
		}
	}
	for(int i=48;i<=57; i++)
	{
		if(puffer[1]==i)
		{
			startwoche+=(i-48);
			break;
		}
	}
	printf("startwoche: %i und anzahlwochen: %i\n",startwoche,anzwoche);
	//free(buffer);
	free(puffer)	;
	//free(puffer);
	return 1;		
}

void tagesauswahl()
{
	//puts("hallo");
	setdates=(int**)calloc(anzwoche,sizeof(int*));
	//int setdates[anzwoche][7];
	for(int i=0; i<anzwoche;i++) setdates[i]=(int*)calloc(7,sizeof(int));
	char janein1=32, janein3[7]; for(int i=0;i<7;i++) janein3[i]=32;
	char janein2=32;
	//int lauf1=0, lauf2=0, lauf3[]={0,0,0,0,0,0,0};
	char wochentage[][11]={"Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Samstag","Sonntag"};
	for(int i=0; i<anzwoche; i++)
	{
		janein1=32; for(int f=0;f<7;f++) janein3[f]=32; janein2=32;
		//puts("hallihallo");
		printf("Willst du in der %i. Woche bestellen? Bitte nur j oder n eingeben:", startwoche+i);
		//puts("keinbock");
		do
		{ 	//lauf1++;
			//puts("keinelust");
			//scanf("%c",&janein1);
			getchar();
			janein1=getchar(); //wait(5000);
			
			//puts("nanunana");
			//if(lauf1==1)continue;
			if(janein1=='n' || janein1=='j')
			{
				if(janein1=='n')
				{
					for(int j=0; j<7;j++)
					{
						setdates[i][j]=0;
					}
				} 
				else
				{
					printf("Alles bestellen? Bitte nur j oder n eingeben:");
					do
					{
						//lauf2++;
						getchar();
						scanf("%c",&janein2);//if(lauf2==1)continue;
						//usw.
						if((janein2=='n') || (janein2=='j'))
						{
							if(janein2=='j')
							{
								for(int j=0;j<7;j++)
								{
									setdates[i][j]=1; printf("%i",setdates[i][j]);
								}
							}
							else
							{
								for(int k=0; k<7; k++)
								{
									do
									{
										//lauf3[k]++;
										printf("Für %s bestellen? Bitte nur j oder n eingeben.:",wochentage[k]);
										getchar();
										scanf("%c",&janein3[k]);
										//if(lauf3[k]==1)continue;
										if((janein3[k]=='n') || (janein3[k]=='j'))
										{
											puts("hi");
											if(janein3[k]=='j') { setdates[i][k]=1; printf("%i",setdates[i][k]);}
											else setdates[i][k]=0; 
										} else printf("Falsche Eingabe! Nochmal bitte:");										
									
									}while((janein3[k]!='j') && (janein3[k]!='n'));
								}
							}
							
						} else puts("Falsche Eingabe! Nochmal bitte.");
					}while((janein2!='n') && (janein2!='j'));
				}
				
			} else puts("Falsche Eingabe! Nochmal bitte.");
		}while((janein1!='n') && (janein1!='j')) ;
	}
	//printf("%i",setdates[0][0]);
	
}

void getsel_datums()
{
	FILE* wochenliste;
	//puts("hihi");
	//wochenliste=fopen("findoutput","r");
	//puts("ho");
	char* buffer; //puts("duda"); 
	buffer=(char*)malloc(150*sizeof(char)); 
	//puts("hihohehohehi");
	//find("findoutput","selected=\"selected\"",anzwoche); //--> schon nach selected bla in kalwochen suchen :DONE Done
	slynmbwochen=(char**)calloc(anzwoche,sizeof(char*));
	for(int i=0;i<anzwoche;i++) slynmbwochen[i]=(char*)malloc(11);
	//puts("muhahaha");
	//printf("%i",setdates[0][0]);
	wochenliste=fopen("findoutput","r");
	//puts("dreimalschwarzerkater");
	for(int i=0;i<anzwoche;i++)
	{
		int bestellen=0;
		fgets(buffer, 150, wochenliste);
		for(int j=0;j<7;j++)
		{
			if(setdates[i][j]==1)
			{
				//printf("%i %i %i",i,j,setdates[i][j]);
				bestellen=1;break;
			}	
		}
		if(bestellen==1) 
		{
			strcpy(slynmbwochen[i],cut2(buffer,"\"",2,2)); //get silly numbers
			printf("%s\n",slynmbwochen[i]);
		}
		else strcpy(slynmbwochen[i],"0");
	}	
	fclose(wochenliste);	
}

void createmenufiles(char* userid, char* passwd)
{
	FILE* menus[anzwoche];
	char postfield[25];
	char menufilename[8];
	char menunumber[2];
	for(int i=0;i<anzwoche;i++)
	{
		if(strlen(slynmbwochen[i])>2)
		{
		strcpy(menufilename,"menu");
		menunumber[0]=48+i; menunumber[1]='\0';
		strcat(menufilename,menunumber); strcat(menufilename,"\0");
		printf("%s\n",menufilename) ;
		menus[i]=fopen(menufilename, "w");
		strcpy(postfield,"sel_datum=");
		strcat(postfield,slynmbwochen[i]);
		printf("%s\n",postfield);
		CURLcode ret;
		CURL *hnd = curl_easy_init();
		curl_easy_setopt(hnd, CURLOPT_WRITEDATA, menus[i]);
		curl_easy_setopt(hnd, CURLOPT_INFILESIZE_LARGE, -1);
		curl_easy_setopt(hnd, CURLOPT_URL, "http://www.dussmann-lpf.rcs.de/index.php?m=1;3");
		curl_easy_setopt(hnd, CURLOPT_PROXY, "192.168.0.1:3128");
		curl_easy_setopt(hnd, CURLOPT_PROXYUSERPWD, NULL); 
		curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, postfield);
	 	curl_easy_setopt(hnd, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; U; Linux i686; de; rv:1.9.2.12) Gecko/20101027 Firefox/3.6.12");
		curl_easy_setopt(hnd, CURLOPT_COOKIEFILE, "Cookiedatei");
		curl_easy_setopt(hnd, CURLOPT_COOKIEJAR, NULL);
		ret = curl_easy_perform(hnd);
		curl_easy_cleanup(hnd);
		fclose(menus[i]);
		} else continue;
	}
}

void gethiddenandbestellt()
{
	char menufilename[8];
	char menunumber[2];
	hidden=(char***)calloc(anzwoche,sizeof(char**));
	for(int i=0;i<anzwoche; i++)
	{
		int numlines=0;
		char c;
		char* tmp=(char*)malloc(sizeof(char)*300);
		char* tmp2=(char*)malloc(sizeof(char)*300);
		char* puffer=(char*)malloc(sizeof(char)*50);
		FILE* listhidden;
		hidden[i]=(char**)calloc(35,sizeof(char*));
		printf("dudel\n");
		for(int k=0;k<35;k++) {hidden[i][k]=(char*)malloc(50);strcpy(hidden[i][k],"\0");}
		if(strlen(slynmbwochen[i])>2)
		{
			strcpy(menufilename,"menu");
			menunumber[0]=48+i; menunumber[1]='\0';
			strcat(menufilename,menunumber); strcat(menufilename,"\0");
			find(menufilename,"\"hidden\" name");
			listhidden=fopen("findoutput","r");
			while((c=fgetc(listhidden))!= EOF)
			{
				if(c=='\n') numlines++;
			}
			rewind(listhidden);
			for(int j=0;j<numlines;j++)
			{
				fgets(tmp,300,listhidden);
				tmp2=strcpy(tmp2,tmp);
				strcpy(puffer,cut2(tmp2,"\"",4,4));
				tmp2=strcpy(tmp2,tmp);
				strcat(puffer,"=");
				strcat(puffer,cut2(tmp2,"\"",6,6));
				printf("%s\n",puffer);
				hidden[i][j]=strcpy(hidden[i][j],puffer);
				printf("diedeldu %s\n",hidden[i][j]);
			}
			fclose(listhidden);
		}
		free(tmp);
		free(tmp2);
		free(puffer);
	}
	bergruen=(char***)calloc(anzwoche,sizeof(char**));
	for(int i=0;i<anzwoche; i++)
	{
		int numlines=0;
		char c;
		char* tmp=(char*)malloc(sizeof(char)*300);
		char* tmp2=(char*)malloc(sizeof(char)*300);
		char* puffer=(char*)malloc(sizeof(char)*50);
		FILE* listgruen;
		bergruen[i]=(char**)calloc(35,sizeof(char*));
		printf("dudel\n");
		for(int k=0;k<35;k++) {bergruen[i][k]=(char*)malloc(50);strcpy(bergruen[i][k],"\0");}
		if(strlen(slynmbwochen[i])>2)
		{
			strcpy(menufilename,"menu");
			menunumber[0]=48+i; menunumber[1]='\0';
			strcat(menufilename,menunumber); strcat(menufilename,"\0");
			find(menufilename,"gruen pointer\"",3);
			find("findoutput","type=\"radio\"");
			listgruen=fopen("findoutput","r");
			while((c=fgetc(listgruen))!= EOF)
			{
				if(c=='\n') numlines++;
			}
			rewind(listgruen);
			for(int j=0;j<numlines;j++)
			{
				fgets(tmp,300,listgruen);
				tmp2=strcpy(tmp2,tmp);
				strcpy(puffer,cut2(tmp2,"\"",4,4));
				tmp2=strcpy(tmp2,tmp);
				strcat(puffer,"=");
				strcat(puffer,cut2(tmp2,"\"",6,6));
				printf("%s\n",puffer);
				bergruen[i][j]=strcpy(bergruen[i][j],puffer);
				printf("diedeldu %s\n",bergruen[i][j]);
			}
			fclose(listgruen);
		}
		free(tmp);
		free(tmp2);
		free(puffer);
	}
	bergruend=(char***)calloc(anzwoche,sizeof(char**));
	for(int i=0;i<anzwoche; i++)
	{
		int numlines=0;
		char c;
		char* tmp=(char*)malloc(sizeof(char)*300);
		char* tmp2=(char*)malloc(sizeof(char)*300);
		char* puffer=(char*)malloc(sizeof(char)*50);
		FILE* listgruend;
		bergruend[i]=(char**)calloc(35,sizeof(char*));
		printf("dudel\n");
		for(int k=0;k<35;k++) {bergruend[i][k]=(char*)malloc(50);strcpy(bergruend[i][k],"\0");}
		if(strlen(slynmbwochen[i])>2)
		{
			strcpy(menufilename,"menu");
			menunumber[0]=48+i; menunumber[1]='\0';
			strcat(menufilename,menunumber); strcat(menufilename,"\0");
			find(menufilename,"gruen pointer\"",3);
			find("findoutput","type=\"hidden\" name=\"fld_");
			listgruend=fopen("findoutput","r");
			while((c=fgetc(listgruend))!= EOF)
			{
				if(c=='\n') numlines++;
			}
			rewind(listgruend);
			for(int j=0;j<numlines;j++)
			{
				fgets(tmp,300,listgruend);
				tmp2=strcpy(tmp2,tmp);
				strcpy(puffer,cut2(tmp2,"\"",12,12));
				tmp2=strcpy(tmp2,tmp);
				strcat(puffer,"=");
				strcat(puffer,cut2(tmp2,"\"",14,14));
				printf("%s\n",puffer);
				bergruend[i][j]=strcpy(bergruend[i][j],puffer);
				printf("diedeldu %s\n",bergruend[i][j]);
			}
			fclose(listgruend);
		}
		free(tmp);
		free(tmp2);
		free(puffer);
	}
}

void getdatensatz()
{
	wirkbestellen=(int**)calloc(anzwoche,sizeof(int*));
	for(int i=0;i<anzwoche;i++)
	{
		wirkbestellen[i]=(int*)malloc(7*sizeof(int));
		for(int j=0;j<7;j++)
		{
			wirkbestellen[i][j]=0;
			if(setdates[i][j]==1) wirkbestellen[i][j]=1; //ACHTUNG: Das kann noch zu viel sein!!
		}
	}
	wocheplustagplusdaten=(char****)calloc(anzwoche,sizeof(char***));
	for(int i=0;i<anzwoche;i++) 
	{
		wocheplustagplusdaten[i]=(char***)calloc(7,sizeof(char**));
		for(int j=0;j<7;j++) 
		{
			wocheplustagplusdaten[i][j]=(char**)calloc(9,sizeof(char*));
			for(int k=0;k<9;k++) 
			{
				wocheplustagplusdaten[i][j][k]=(char*)malloc(75*sizeof(char));
				strcpy(wocheplustagplusdaten[i][j][k],"\0");
			}
		}
	}
	char menufilename[8];
	char menunumber[2];
	for(int i=0;i<anzwoche;i++)
	{
		if(strlen(slynmbwochen[i])>3)
		{
			strcpy(menufilename,"menu");
			menunumber[0]=48+i; menunumber[1]='\0';
			strcat(menufilename,menunumber); strcat(menufilename,"\0");
			find(menufilename,"class=\" auflistung");
			FILE* auflistungen;
			auflistungen=fopen("findoutput","r");
			char* tmp=(char*)malloc(300);
			for(int j=0;j<21;j++) //21, weil bis dahin es zum sonntag menü 3 geht
			{
				fgets(tmp, 300,auflistungen);
				if(wirkbestellen[i][j%7]==1)
				{
					if(strstr(tmp,"pointer")==NULL) 
					{
						
						wirkbestellen[i][j%7]=0;
						continue; //--> Ausschließen des Tages, da dieser schon bestellt ==> alle folgenden unbestellt oder gruen
					}
					if(strstr(tmp,"gruen pointer")!=NULL)
					{
						wirkbestellen[i][j%7]=0;
						continue;
					}
					wirkbestellen[i][j%7]=1;
				}
			}
			rewind(auflistungen);
			for(int j=0; j<21;j++)
			{
				fgets(tmp,300,auflistungen);
				if(wirkbestellen[i][j%7]==1)
				{
					cut2(tmp,">",2,4); //hier muss noch fallunterscheidung wegen \n am ende rein!!!
					if((tmp[0]=='\n') &&(j<7)) {wirkbestellen[i][j%7]=0; continue;}
					if((tmp[0]=='\n') && (j/7==1)){continue;} //--> die leeren Menü2s bleiben '\0'
					strcpy(wocheplustagplusdaten[i][j%7][3*(j/7)],tmp); //Menünamen abspeichern, damit man nach ihm in den folgenden Zeilen suchen kann, damit man die restlichen Daten ermitteln kann
					printf("%i %i %s",i,j,wocheplustagplusdaten[i][j%7][3*(j/7)]);
				}
			}
			//free(tmp);//Nun weiß man die Tage, für welche MENÜS bestellt müssen, man weiß nicht, wo Desserts bestellt werden müssen 
			fclose(auflistungen);
			FILE* essendata;
			for(int j=0; j<21;j++)
			{
				if(wirkbestellen[i][j%7]==1)
				{
					if(strlen(wocheplustagplusdaten[i][j%7][3*(j/7)])>2) //--> Ausschließen, dass für ein leeres Menü 2 Daten gesammelt werden sollen
					{
						find(menufilename,wocheplustagplusdaten[i][j%7][3*(j/7)],2); //Suche nach Zeile über den Essensnamen
						find("findoutput","<input type=\"radio\" name=\"rad_");
						essendata=fopen("findoutput","r");
						fgets(tmp, 300, essendata);
						cut2(tmp,"\"",4,4);
						strcpy(wocheplustagplusdaten[i][j%7][3*(j/7)+1],tmp);
						printf("%s",wocheplustagplusdaten[i][j%7][3*(j/7)+1]);
						rewind(essendata);
						fgets(tmp,300, essendata);
						cut2(tmp,"\"",6,6);
						strcpy(wocheplustagplusdaten[i][j%7][3*(j/7)+2], tmp);
						printf("%s",wocheplustagplusdaten[i][j%7][3*(j/7)+2]);
						fclose(essendata);	
					}
				}
			} 
			free(tmp);
				//--> Die Daten für die Menüs für die wirklich zu bestellenden Tage sind abgespeichert.
				// --> Die Nummer des entsprechendenden Desserts lässt sich aus der rad_ nummer herleiten ==>
				// wenn die Suche nach der Nummer ergibt, dass die schon bereits grün ist, wird die nicht bestellt,
				// ansonsten wird diese bestellt
		}		
	}	
}

void getrating()
{
	
	
}

