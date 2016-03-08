#include<stdio.h>

 int main ( ) {
 int num1 , num2 , i , hcf ;

 printf ( "Numero 1 : \n" ) ;
 scanf ( "%d" , &num1 ) ;

 printf ( "Numero 2 : \n" ) ;
 scanf ( "%d" , &num2 ) ;
 hcf = MDC(num1,num2);

 printf ( "H.C. F o f %d and %d i s %d \n" , num1 , num2 , hcf ) ;
 return 0 ;
 }


 int MDC(int num1,int num2){
 int i,hcf;
 for ( i =1; (i<=num1) || (i<=num2) ; ++i ) {

 /* Checking whether i is a factor of both number */
 if ( num1%i==0 && num2%i ==0)
 hcf=i ;
 }
return hcf;
 }
