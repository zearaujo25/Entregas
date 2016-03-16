#include<stdio.h>
 
int main()
{
   int n=20, i = 3, numero, primo;
      printf("Primo 1 = 2\n");

   for ( numero = 2 ; numero <= n ;  )
   {
      for ( primo = 2 ; primo <= i - 1 ; primo++ )
      {
         if ( i%primo == 0 )
            break;
      }
      if ( primo == i )
      {
         printf("Primo %d = %d\n",numero,i);
         numero++;
      }
      i++;
   }
 
   return 0;
}