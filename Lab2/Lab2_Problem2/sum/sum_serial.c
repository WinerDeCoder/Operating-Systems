#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {

  int n = atoi(argv[1]);
  int sum =0;
  
  //scanf("%d", &n);

  for(int i = 1; i <= n; i +=1){

    sum = sum + i;

  }
  printf("\n%d", sum);
}