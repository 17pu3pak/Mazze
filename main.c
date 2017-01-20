#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
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

//TODO: проврека на обновления
//TODO: git
//TODO: ls в загрузке DONE
//TODO: проверка файлов
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

        //загрузка
        if (strt == 2) {
                system("clear");
                char PathName[100];
                char Path[100];
                char Path2[100];
                char PN;
                char lss[1000]="ls '";
                char rmm[100]="rm '";

                // Определяем путь к текущей директории
                PN = *getwd (PathName);
                PN = *getwd (Path);
                PN = *getwd (Path2);
                //удалаяем файл a.txt
                strcat(Path2,"/saves/a.txt'");
                strcat(rmm,Path2);
                system(rmm);
                strcat(lss,strcat(Path,"/saves' >> '"));
                strcat(lss,Path2);
                //делаем ls что бы узнать какие у нас есть сохраниея
                system(lss);
                PN = *getwd (Path2);
                strcat(Path2,"/saves/a.txt");

                FILE * fo;

                fo = fopen(Path2,"rt");

                //Массив указателей на слова
                char **words;
                //Строка, которая используется для считывания введённого пользователем слова
                char buffer[100];
                //Счётчик слов
                int wordCounter = 0;
                //Длина введённого слова
                int length;
                int size = 1;
                int i,sz,p;

                //Выделяем память под массив из size указателей
                if( !( words = (char**) malloc(size*sizeof(char*)))) {
                        //Проверяем на наличие ошибок
                        printf("Error: can't allocate memory");
                        exit(1);
                }
                //получаем список сохранений
                while (fscanf(fo, "%s", buffer) == 1) { // expect 1 successful conversion
                        length = stringlength(buffer);

                        //Определяем длину слова
                        //В том случае, если введено слов больше, чем длина массива, то
                        //увеличиваем массив слов
                        if (wordCounter >= size) {
                                size++;
                                if  (!(words = (char**) realloc(words, size*sizeof(char*)))) {
                                        printf("Error: can't reallocate memory");
                                        exit(2);
                                }
                        }
                        //Выделяем память непосредственно под слово
                        //на 1 байт больше, так как необходимо хранить терминальный символ
                        if (!(words[wordCounter] = (char*) malloc((length + 1)*sizeof(char)))) {
                                //Проверяем на наличие ошибок
                                printf("Error: can't allocate memory");
                                exit(3);
                        }
                        //Копируем слово из буфера по адресу, который
                        //хранится в массиве указателей на слова
                        p=0;
                        while(p<=length) {
                                words[wordCounter][p]=buffer[p];
                                p++;
                        }
                        wordCounter++;
                }
                //sz=sizze(wordCounter);
                //удаяем лишние файлы и расширения сохранений
                for (int i=0; i<wordCounter; i++) {
                        int length = stringlength(words[i]);
                        if (length > 4) {
                                if ((words[i][length-4] == '.') && (words[i][length-3] == 'p') && (words[i][length-2] == 'k') && (words[i][length-1] == 'b')) {
                                        words[i][length-4]='\0';
                                }
                                else{
                                        words[i][0]='\0';
                                }
                        }
                        else{
                                words[i][0]='\0';
                        }
                }
                //предлагаем выбрать сохранения
                printf ("Chouse name of a save file: \n");
                int *ids;
                int numbr=1;
                for (i = 0; i < wordCounter; i++) {
                        if (stringlength(words[i]) != 0) {
                                ids=(int*)realloc(ids, numbr*sizeof(int));
                                ids[numbr-1]=i;
                                printf ("%d) %s\n",numbr,words[i]);
                                numbr++;
                        }
                }
                //выбираем сохранение
                printf (":");
                int get;
                scanf("%d",&get);
                //получаме размера лаберинта из файла
                strcat(strcat(strcat(PathName,"/saves/"),words[ids[get-1]]),".pkb");
                Load2( &sizze,PathName);
                printf("NAME %s\n",PathName);
                //выделяем память под лаберинт
                array=malloc(sizze*sizze*sizeof(Cell));
                //загружаем лаберинт
                Load(array, &diff, &ext_timmer,PathName);
                int tmp=sizze*sizze;
                //находим точку начала и конца
                for (int i=0; i<tmp; i++) {
                        if (array[i].ply==1) {
                                current=&array[i];
                        }
                        if (array[i].endd==1) {
                                end_cell=&array[i];
                        }
                }
                timmer =clock();
                system("clear");
                //играем)))
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
