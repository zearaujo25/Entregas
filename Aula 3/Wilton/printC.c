#include<stdio.h>
 
int main()
{

	int total = 71, inicial = 3, divisivel = 0, contador = 2, j, i;

	printf("Primo 1: 2\n");

	for(i = 3 ; i <= total ; i++ )
	{
		
		for(j = 1 ; j <= i ; j++ )
		{
			
			if(i%j == 0)
			{
								
				divisivel++;
			}

		}

		if(divisivel == 2)
		{
			printf("Primo %d: %d\n",contador,i);
			contador++;
		}

		divisivel = 0;

	}	


	return 0;	
	
}