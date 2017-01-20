#include <stdio.h>

void rt(int *t){
  *t=1;
}

int main(){
  int t=0;
  printf("t=%d\n",t);
  rt(&t);
  printf("t=%d\n",t);


  return 0;
}
