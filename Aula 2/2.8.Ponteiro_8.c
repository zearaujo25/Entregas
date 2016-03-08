#include <stdio.h>
#include <stdlib.h>
#define N 10
int main()
{
    int n[N];
    int i ;
    for(i=0;i<N;i++){
    *(n+i)=i+10;
    printf("n[%d]:%d \n",i,*(n+i));
    }

    return 0;
}
