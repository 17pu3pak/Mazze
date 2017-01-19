#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void Update(Cell *array, Cell *current, Cell *end_cell, int sizze, int diff, int timmer, int ext_timmer){
        if (end_cell->index==current->index) {
                printf ("\n");
                printf ("\n");
                printf(magenta "CONGRATULATIONS!\n");
                printf(magenta "You completed the maze.\n");
                Prt_time_spd(timmer, ext_timmer);
                printf(magenta "Thank you for playing.\n");
                printf(cyan "P.K.B. Team © 2016\n");
                printf(reset);
                exit(10);
        }
        if (diff != 3) {
                unsigned char inp = mygetch();
                inp = tolower(inp);
                int index;
                switch(inp) {

                case 97: {
                        index=ind(current->j-1, current->i, sizze);
                        if ((index!= -1) && (current->top != 1)) {
                                current->ply=0;
                                current=&array[index];
                                current->ply=1;
                        }
                        break;
                }

                case 100: {
                        index=ind(current->j, current->i-1, sizze);
                        if ((index!= -1) && (current->left != 1)) {
                                current->ply=0;
                                current=&array[index];
                                current->ply=1;
                        }                break;
                }

                case 98: {
                        index=ind(current->j+1, current->i, sizze);
                        if ((index!= -1) && (current->bottom != 1)) {
                                current->ply=0;
                                current=&array[index];
                                current->ply=1;
                        }                break;
                }

                case 99: {
                        index=ind(current->j, current->i+1, sizze);
                        if ((index!= -1) && (current->right != 1)) {
                                current->ply=0;
                                current=&array[index];
                                current->ply=1;
                        }                break;
                }
                case 'r': {
                        main();
                        break;
                }
                case 's': {
                        Save(array,sizze,diff,timmer,ext_timmer);
                        break;
                }
                case 'x': {
                        printf(magenta "Thank you for playing.\n");
                        printf(cyan "P.K.B. Team © 2016\n");
                        printf(reset);
                        free(array);
                        exit(5);
                }
                }
                if (diff == 1) {
                        Draw(array,sizze);
                }
                else if (diff == 2) {
                        Draw2(array,sizze,current);
                }

                printf("\n");
                printf(yellow " * ");
                printf(reset);
                printf(" - Player\n");
                printf(green " # ");
                printf(reset);
                printf(" - Goal\n");
                printf(red " s ");
                printf(reset);
                printf(" - Save\n");
                printf(cyan " r ");
                printf(reset);
                printf(" - Restart\n");
                printf(cyan " x ");
                printf(reset);
                printf(" - Exit\n");
                printf(cyan " up/down/left/right (arrows) ");
                printf(reset);
                printf(" - Controls\n");
        }
        else{
                system("clear");
                SetCursor(0,0);
                printf(cyan "P.K.B. Team © 2016\n");
                printf(green "Maze size: %d\n",sizze );
                printf(reset);
                printf ("\n");

                char *s;
                int index;

                printf("Command:\n" );
                s=mygetstring();



                if (stringcompare(s,"up") == 0) {
                        index=ind(current->j-1, current->i, sizze);
                        if ((index!= -1) && (current->top != 1)) {
                                current->ply=0;
                                current=&array[index];
                                current->ply=1;
                        }
                        else{
                                printf("There is a wall\n");
                                Pauza();
                        }
                }

                if (stringcompare(s,"left") == 0) {
                        index=ind(current->j, current->i-1, sizze);
                        if ((index!= -1) && (current->left != 1)) {
                                current->ply=0;
                                current=&array[index];
                                current->ply=1;
                        }
                        else{
                                printf("There is a wall\n");
                                Pauza();
                        }
                }

                if (stringcompare(s,"down") == 0) {
                        index=ind(current->j+1, current->i, sizze);
                        if ((index!= -1) && (current->bottom != 1)) {
                                current->ply=0;
                                current=&array[index];
                                current->ply=1;
                        }
                        else{
                                printf("There is a wall\n");
                                Pauza();
                        }
                }

                if (stringcompare(s,"right") == 0) {
                        index=ind(current->j, current->i+1, sizze);
                        if ((index!= -1) && (current->right != 1)) {
                                current->ply=0;
                                current=&array[index];
                                current->ply=1;
                        }
                        else{
                                printf("There is a wall\n");
                                Pauza();
                        }
                }
                if (stringcompare(s,"save") == 0) {
                        Save(array,sizze,diff,timmer,ext_timmer);
                }
                if (stringcompare(s,"restart") == 0) {
                        main();
                }
                if (stringcompare(s,"help") == 0) {
                        printf("'up' - to go up\n");
                        printf("'down' - to go down\n");
                        printf("'left' - to go left\n");
                        printf("'right' - to go right\n");
                        printf("'save' - to save progress\n");
                        printf("'restart' - to go restart the game\n");
                        printf("'exit' - to go exit the game\n");
                        Pauza();
                }
                if (stringcompare(s,"exit") == 0) {
                        printf(magenta "Thank you for playing.\n");
                        printf(cyan "P.K.B. Team © 2016\n");
                        printf(reset);
                        free(array);
                        exit(5);
                }

        }

        Update(array,current,end_cell,sizze,diff,timmer,ext_timmer);
}
