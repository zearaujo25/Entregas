#include <stdio.h>
#include <stdlib.h>

void swap(int *p1,int *p2);
int main()
{
    int x =10,y=20;
    swap(&x,&y);
    printf("x= %d,y= %d",x,y);
    return 0;
}
void swap(int *p1,int *p2){
int aux ;
aux=*p1;
*p1=*p2;
*p2=aux;

}
