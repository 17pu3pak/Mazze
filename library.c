#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "library.h"

//цветовая палитра
#define nc  "\x1B[0m"
#define red  "\x1B[31m"
#define green  "\x1B[32m"
#define yellow  "\x1B[33m"
#define blue  "\x1B[34m"
#define magenta  "\x1B[35m"
#define cyan  "\x1B[36m"
#define white  "\x1B[37m"
#define reset  "\033[0m"


int ind(int j, int i, int sizze) {
        if ((i < 0) ||( j < 0) ||( i > sizze-1 )||( j > sizze-1)) {
                return -1;
        }
        return (i + j * sizze);
}


int mygetch( ) {
        struct termios oldt,
                       newt;
        int ch;
        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
        return ch;
}
void SetCursor(int X,int Y){
        printf("\033[%d;%dH",Y,X);
}
void Pauza(){
        printf("\n");
        printf("Press 'ENTER' to continue\n");
        unsigned char inp = mygetch();
        inp = tolower(inp);
        switch(inp) {

        case 10: {

        }
        break;
        }
}

void Prt_time_spd(int timmer, int ext_timmer){
        int day;
        int ho;
        int min;
        int sec;
        int end_t=(clock()-timmer+ext_timmer)/1000;
        day = end_t/(24*60*60);
        end_t=end_t%(24*60*60);
        ho = end_t/(60*60);
        end_t=end_t%(60*60);
        min = end_t/(60);
        sec=end_t%(60);
        printf(red "You spend %d days %d hours %d minutes %d seconds. \n",day, ho, min, sec);
        printf(reset);
}

void Save(Cell *array, int sizze,int diff,int timmer,int ext_timmer){
        char PathName[100];
        char PathName2[100];
        // Переменная, в которую буднт помещен указатель на PathName
        char PN;

        // Определяем путь к текущей директории
        PN = *getwd (PathName);
        PN = *getwd (PathName2);
        FILE * fo;

        char name[100];
        system("clear");
        printf ("Enter name for a save file: ");
        scanf("%s",name);
        strcat(strcat(strcat(PathName,"/saves/"),name),".pkb");
        if ((fo = fopen(PathName, "r")) != NULL){
          fclose(fo);
          printf ("File with this name already exist. Rewrite?\n");
          printf ("1) Yes\n");
          printf ("2) No\n");
          int c;
          scanf("%d", &c);
          if (c == 1){
            char rm[100]="rm '";
            strcat(rm,strcat(PathName2,"'"));
            system(rm);
          }
          else{
            printf("Save canceled.\n");
            sleep(1);
            system("clear");
            return;
          }
        }
        fo = fopen(PathName,"wt");
        fprintf( fo, "%d\n",sizze );
        for (int i=0; i<sizze*sizze; i++) {
                fprintf( fo, "%d\n", array[i].i);
                fprintf( fo, "%d\n", array[i].j);
                fprintf( fo, "%d\n", array[i].index);
                fprintf( fo, "%d\n", array[i].top);
                fprintf( fo, "%d\n", array[i].right);
                fprintf( fo, "%d\n", array[i].bottom);
                fprintf( fo, "%d\n", array[i].left);
                fprintf( fo, "%d\n", array[i].visited);
                fprintf( fo, "%d\n", array[i].empty);
                fprintf( fo, "%d\n", array[i].ply);
                fprintf( fo, "%d\n", array[i].endd);
                fprintf( fo, "%d\n", array[i].wall);
        }
        fprintf( fo, "%d\n", diff);
        ext_timmer=(clock()-timmer+ext_timmer)/1000;
        fprintf( fo, "%d\n", ext_timmer);
        fclose(fo);
        system("clear");
        printf("Saved.\n");
        sleep(1);
        system("clear");
        return;
}

void Load(Cell *array,int *diff,int *ext_timmer,char PathName[100]){
        // Переменная, в которую буднт помещен указатель на PathName

        // Определяем путь к текущей директории
        FILE * fo;

        int tmp;

        fo = fopen(PathName,"rt");
        fscanf( fo, "%d\n",&tmp );
        int sqr=tmp*tmp;
        printf ("tmp%d\n",tmp);

        sqr=tmp*tmp;
        printf("%d\n",sqr );

        for (int i=0; i<sqr; i++) {
                fscanf( fo, "%d\n", &tmp);
                array[i].i=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].j=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].index=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].top=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].right=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].bottom=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].left=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].visited=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].empty=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].ply=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].endd=tmp;
                fscanf( fo, "%d\n", &tmp);
                array[i].wall=tmp;
        }

        fscanf( fo, "%d\n", &tmp);
        *diff=tmp;
        fscanf( fo, "%d\n", &tmp);
        *ext_timmer=tmp;
        fclose(fo);
        system("clear");
        return;
}
void Load2(int *sizze, char PathName[100]){

        // Переменная, в которую буднт помещен указатель на PathName

        // Определяем путь к текущей директории
        FILE * fo;

        int tmp;

        //fo = fopen(PathName,"rt");
        if ((fo = fopen(PathName, "r")) == NULL){
          printf("File does'n exist\n");
          sleep(1);
          main();
        }

        fscanf( fo, "%d\n",&tmp );
        *sizze=tmp;

        return;
}
