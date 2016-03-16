#include <stdio.h>
#include <stdlib.h>
int main()
{    
    int i, array[20];    
    printarray(array);
    return 0;
}

void printarray(int *array)
{
    int i;

    for(i =  0; i < 20; i++)
    {
        *(array+i)=i+10;

        printf("array[%d]:%d \array",i,*(array+i));
    }
}