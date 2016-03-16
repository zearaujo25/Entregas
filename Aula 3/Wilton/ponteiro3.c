#include <stdio.h> 
#include <stdlib.h> 


int main() 
{
    
    int i , array[5];    

    for (i = 0; i < 5; i++) 
    { 
	    * (array + i) = rand();

        printf("array[%d]:%d \n", i, * (array + i));
    }

    return 0;
}