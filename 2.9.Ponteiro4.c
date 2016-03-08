#include <stdio.h>
#include <stdlib.h>
#define N 20
int main()
{
    int n[N];
    int i ;
    printarray(n);
    return 0;
}

void printarray(int *n)
{
    int i;
    for(i=0; i<N; i++)
    {
        *(n+i)=i+10;
        printf("n[%d]:%d \n",i,*(n+i));
    }
}
