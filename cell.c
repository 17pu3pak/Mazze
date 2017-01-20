#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "library.h"


//Создание массива ячеек
int CreateCell(Cell *array,int sizze){
        for (int j=0; j<sizze; j++) {
                for (int i=0; i<sizze; i++) {
                        // Прописывание начальных параметров для каждой ячейки (для надежности)
                        int index=ind(j,i,sizze);
                        array[index].i=i;
                        array[index].j=j;
                        array[index].index=index;
                        array[index].visited=0;
                        array[index].top=1;
                        array[index].right=1;
                        array[index].bottom=1;
                        array[index].left=1;
                        array[index].empty=0;
                        array[index].ply=0;
                        array[index].endd=0;
                        array[index].wall=0;
                }
        }
        return 0;
}

//поиск соседей текущей ячейки (генерация лаберинат)
int FindNeighbors(int *neighbors_ids, int sizze, Cell *array,  int *start_point_x  , int *start_point_y  , int *end_point_x  , int *end_point_y){
        srand(time(NULL));
        int stack_size=0;
        Cell *current;
        stack st=create_stack(sizeof(int));
        //ячейка для начала генерации выбирается случайным образом
        current=&array[rand()%(sizze*sizze)];
        *start_point_y=current->j;
        *start_point_x=current->i;
        current->ply=1;
        //каждую текущую ячейку добавляем в стек (наш путь)
        push(st,&current->index);
        stack_size++;
        int max=0;

find:   ;
        // если стек опустошен, то мы вернулись в первую ячейку
        if (stack_size>max){
          max=stack_size;
          array[ind(*end_point_y, *end_point_x, sizze)].endd=0;
          *end_point_x=current->i;
          *end_point_y=current->j;
          array[ind(current->j, current->i, sizze)].endd=1;
        }
        if (stack_size==0) {
          array[ind(*end_point_y, *end_point_x, sizze)].endd=1;
                return 0;

        }
        // отмечаме что мы уже были в текущей ячейке
        current->visited=1;
        int empty=1;
        // найдем адреса всех соседних не посещенных ячеек (если нет соседа с какой либо стороны, то -1)
        if (array[ind(current->j-1,current->i,sizze)].visited!=1) {
                neighbors_ids[0]=ind(current->j-1,current->i,sizze);
        }
        else{
                neighbors_ids[0]=-1;
        }
        if (array[ind(current->j+1,current->i,sizze)].visited!=1) {
                neighbors_ids[1]=ind(current->j+1,current->i,sizze);
        }
        else{
                neighbors_ids[1]=-1;
        }
        if (array[ind(current->j,current->i-1,sizze)].visited!=1) {
                neighbors_ids[2]=ind(current->j,current->i-1,sizze);
        }
        else{
                neighbors_ids[2]=-1;
        }
        if (array[ind(current->j,current->i+1,sizze)].visited!=1) {
                neighbors_ids[3]=ind(current->j,current->i+1,sizze);
        }
        else{
                neighbors_ids[3]=-1;
        }
        // проверим, что мы нашли хотябы одного соседа
        int i;
        for (i=0; i<4; i++) {
                if (neighbors_ids[i] != -1) {
                        empty=0;
                }
        }
        srand(time(NULL)*current->index*(rand()%100));
        //если еще есть непосещенные соседи
        if (empty == 0) {
                int next=-1;
                // выберем случайного соседа
                while (next == -1) {
                        int rnd=rand()%4;
                        next=neighbors_ids[rnd];
                }
                // посмотрим, где он распологается отностительно нас
                int b=current->j-array[next].j;
                int a=current->i-array[next].i;
                // удялим границу между нами и соседом
                if (a == -1) {
                        array[current->index].right=0;
                        array[next].left=0;
                }
                if (a == 1) {
                        array[current->index].left=0;
                        array[next].right=0;
                }
                if (b == -1) {
                        array[current->index].bottom=0;
                        array[next].top=0;
                }
                if (b == 1) {
                        array[current->index].top=0;
                        array[next].bottom=0;
                }
                array[next].visited=1;
                // переходим в выбраную соседнюю ячейку
                current=&array[next];
                // записываме эту ячейку в стек
                push(st,&current->index);
                stack_size++;
                goto find;
        }
        // если же соседей не осталось, вернемся на одну ячейку назад (по уже пройденному пути)
        else{
                //вытягиваем ячейку из стека
                pop(st);
                current=&array[ *(int *)st->buffer];
                stack_size--;
                goto find;
        }
        array[ind(*end_point_y, *end_point_x, sizze)].endd=1;
        return 0;
}
