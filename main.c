#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//#include <conio.h>
#include "library.h"

#define nc  "\x1B[0m"
#define red  "\x1B[31m"
#define green  "\x1B[32m"
#define yellow  "\x1B[33m"
#define blue  "\x1B[34m"
#define magenta  "\x1B[35m"
#define cyan  "\x1B[36m"
#define white  "\x1B[37m"
#define reset  "\033[0m"



int main(){
  Cell *array;
        int sizze,result;
        int stack_size=0;
        int diff,strt;
        int start_point_x;
        int start_point_y;
        int end_point_x;
        int end_point_y;
        int *neighbors_ids;
        Cell *current;
        Cell *end_cell;
        int timmer =0;
        int ext_timmer =0;
start:
        current=malloc(sizeof(Cell));
        end_cell=malloc(sizeof(Cell));


        system("clear");
        printf(cyan "P.K.B. Team © 2016\n");
        printf(reset);
        printf("\n" );
        printf (green "Select:\n");
        printf (green "1) New game\n");
        printf (green "2) Load\n");
        scanf ("%d",&strt);
        if (strt == 2) {
              int  tmp = 2;
              if (!(array=malloc(4*sizeof(Cell)))) {
                      printf("Malloc error 1\n");
                      exit(1);
              }
                Load(array, &sizze, &diff, &ext_timmer);
                printf ("sizze=%d\n",sizze);
                printf ("diff=%d\n",diff);
                printf ("ext_timmer=%d\n",ext_timmer);
                 tmp=sizze*sizze;
                printf("sizze%d\n",tmp );
                                            //FIXME: в array возвращаются неправельные значения
                for (int i=0; i<tmp; i++) {
                  printf ("ind%d\n",array[i].index);
                        if (array[i].ply==1) {
                                current=&array[i];
                        }
                        if (array[i].endd==1) {
                                end_cell=&array[i];
                        }

                        printf("I = %d\n",i );
                        printf("cur%d\n",current->index );
                        printf("end%d\n",end_cell->index );
                }
                Debugger(100);
                timmer =clock();
                Update(array,current,end_cell,sizze,diff,timmer,ext_timmer);
        }
        if ((strt < 1) || (strt > 2)) {
                printf("Error.\n");
                sleep(1);
                goto start;
        }
err1:
        system("clear");
        printf(cyan "P.K.B. Team © 2016\n");
        printf(reset);
        printf("\n" );
        printf (green "Select difficult:\n");
        printf (green "1) Easy\n");
        printf (green "2) Medium\n");
        printf (green "3) Hard\n");
        scanf ("%d",&diff);

        printf("\n");

        if (diff == 4) {
                printf(magenta "Comming soon...\n");
                printf(reset);
                exit(1);

        }
        if ((diff<1)||(diff>4)) {
                printf("Error.\n");
                sleep(1);
                goto err1;
        }
        printf (green "Enter maze size:\n");
        scanf ("%d",&sizze);
        if (!(array=malloc(sizze*sizze*sizeof(Cell)))) {
                printf("Malloc error 1\n");
                exit(1);
        }


        result = CreateCell(array,sizze);

        if (!(neighbors_ids=malloc(4*sizeof(int)))) {
                printf("Malloc error 3\n");
                exit(3);
        }

        result = FindNeighbors(neighbors_ids, sizze, array, &start_point_x,&start_point_y,&end_point_x,&end_point_y);



        int tmp=sizze*sizze;
        printf("sizze%d\n",tmp );
        for (int i=0; i<tmp; i++) {
                if (array[i].ply==1) {
                        current=&array[i];
                }
                if (array[i].endd==1) {
                        end_cell=&array[i];
                }
                printf("%d\n",i );
                printf("cur%d\n",current->index );
                printf("end%d\n",end_cell->index );
        }


        system("clear");
        timmer =clock();
        Update(array,current,end_cell,sizze,diff,timmer,ext_timmer);
        return 0;


}