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
int counter = 0;
//Отрисовывание лабиринта
void Draw(Cell *array,int sizze){
        SetCursor(0,0);
        if(counter ==10){
          //периодическая очистка экрана
          system("clear");
          counter = 0;
        }
        else{
          counter++;
        }
        printf(cyan "P.K.B. Team © 2016\n");
        printf(green "Maze size: %d\n",sizze );
        printf(reset);
        printf ("\n");
        printf("j / i");
        for (int i=0; i<sizze; i++) {
                printf("%3d ",i+1);
        }
        printf("\n");
        //top wall

        printf("    +");
        for (int i=0; i<sizze; i++) {
                printf("---+");
        }
        printf("\n");
        // rows
        for (int j=0; j<sizze; j++) {
                printf ("%3d ",j+1);
                // left/right walls
                printf("|");
                for (int i=0; i<sizze; i++) {

                        int index=ind(j,i,sizze);
                        if (array[index].endd==1) {
                                printf (green " # ");
                                printf(reset);
                        }
                        else if (array[index].ply==1) {
                                printf(yellow " * ");
                                printf(reset);
                        }
                        else{
                                printf("   ");
                        }
                        if (array[index].right != 0) {
                                printf("|");
                        }
                        else{
                                printf(" ");
                        }
                }
                printf("\n");
                printf("    +");
                // top/bottom walls
                for (int i=0; i<sizze; i++) {
                        int index=ind(j,i,sizze);
                        if (array[index].bottom != 0) {
                                printf("---+");
                        }
                        else{
                                printf("   +");
                        }
                }
                printf("\n");
        }



}

//Отрисовывание лабиринта
void Draw2(Cell *array,int sizze, Cell *current){
        SetCursor(0,0);
        Cell *drw=malloc(9*sizeof(int));
        int index;
        //ближние границы
        int pos=0;
        for (int j=-1; j<2; j++) {
                for (int i=-1; i<2; i++) {
                        index=ind(current->j+j, current->i+i,sizze);
                        if (index != -1) {
                                drw[pos]=array[index];
                                pos++;
                        }
                        else{
                                drw[pos].top=1;
                                drw[pos].right=1;
                                drw[pos].bottom=1;
                                drw[pos].left=1;
                                drw[pos].wall=1;
                                pos++;
                        }
                }
        }

        printf(cyan "P.K.B. Team © 2016\n");
        printf(green "Maze size: %d\n",sizze );
        printf(reset);
        printf ("\n");
        for (int j=0; j<3; j++) {
                printf("+");
                for (int i=0; i<3; i++) {
                        index=ind(j,i,3);
                        if (drw[index].top==1) {
                                printf("---+");
                        }
                        else{
                                printf("   +");
                        }
                }
                printf("\n");
                index=ind(j,0,3);
                if(drw[index].left == 1) {
                        printf("|");
                }
                else{
                        printf(" ");
                }
                for (int i=0; i<3; i++) {
                        index=ind(j,i,3);
                        if (drw[index].wall==1) {
                                printf (red " ! ");
                                printf(reset);
                        }
                        else if (drw[index].endd==1) {
                                printf (green " # ");
                                printf(reset);
                        }
                        else if (drw[index].ply==1) {
                                printf(yellow " * ");
                                printf(reset);
                        }
                        else{
                                printf("   ");
                        }
                        if (drw[index].right != 0) {
                                printf("|");
                        }
                        else{
                                printf(" ");
                        }
                }
                printf("\n");
        }
        printf("+");
        for (int i=0; i<3; i++) {
                index=ind(2,i,3);
                if (drw[index].bottom==1) {
                        printf("---+");
                }
                else{
                        printf("   +");
                }
        }
        printf("\n");
        free(drw);
}
