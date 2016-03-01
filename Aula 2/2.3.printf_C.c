#include<stdio.h>
 
int main()
{
   int n=20, i = 3, count, c;
 
 
 
      printf("Primo 1: 2\n");
   
 
   for ( count = 2 ; count <= n ;  )
   {
      for ( c = 2 ; c <= i - 1 ; c++ )
      {
         if ( i%c == 0 )
            break;
      }
      if ( c == i )
      {
         printf("Primo %d:%d\n",count,i);
         count++;
      }
      i++;
   }
 
   return 0;
}