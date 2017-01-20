// By: BU
// P.K.B. Team ©
// 2016
#include <stdlib.h>
#include <stdio.h>
#include "library.h"

int stringlength(char *string){

        int i =0;

        while (string[i]!='\0') {
                i++;
        }
        return i;
}
int stringcompare(char *string01, char *string02){

        int i =0;
        int len1=stringlength(string01);
        int len2=stringlength(string02);

        while ((string01[i]==string02[i])&&((string01[i]!='\0') || (string02[i] != '\0'))) {
                i++;
        }
        if ((len1>i)||(len2>i)) {
                if (string01[i]>string02[i]) {
                        return 1;
                }
                if (string01[i]<string02[i]) {
                        return -1;
                }
        }
        return 0;
}
int stringswap(char *string01,char *string02){

        int len1=stringlength(string01);
        int len2=stringlength(string02);
        int i=0;
        int max=0;
        char c;

        if (len1>=len2) {
                max=len1;
        }
        else{
                max=len2;
        }
        for (i=0; i<max+1; i++) {
                c=string01[i];
                string01[i]=string02[i];
                string02[i]=c;
        }
        return 0;

}
int mysortstr01(char array[][81], int n){
        for (int i=0; i<n-1; i++) {
                for (int k=0; k<n-1; k++) {
                        if (stringcompare(array[k],array[k+1]) == 1) {
                                stringswap(array[k],array[k+1]);
                        }
                }
        }
        return 0;
}
int mysortstr02(char* array[], int n){
        for (int i=0; i<n-1; i++) {
                for (int k=0; k<n-1; k++) {
                        if (stringcompare(array[k],array[k+1]) == 1) {
                                char *temp=array[k];
                                array[k]=array[k+1];
                                array[k+1]=temp;
                        }
                }
        }
        return 0;
}
char* mygetstring(){
        int i=0;
        char *stroka;
        if (!(stroka=(char*)malloc(sizeof(char)))) {
                printf("Error: can't allocate memory");
                exit(4);
        }
        char current;
        while ((current =getchar()) != '\n') {
                if (!(stroka=realloc(stroka, (++i)*sizeof(char)))) {
                        printf("Error: can't reallocate memory");
                        exit(4);
                }
                stroka[i-1]=current;

        }
        if (!(stroka=realloc(stroka, (++i)*sizeof(char)))) {
                printf("Error: can't reallocate memory");
                exit(4);
        }
        stroka[i-1]='\0';
        return stroka;
}
