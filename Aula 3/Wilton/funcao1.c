#include < stdio.h >

    int main() {
        int num1, num2, i, hcf;

        printf("Numero 1 : \n");
        scanf("%d", & num1);

        printf("Numero 2 : \n");

        scanf("%d", & num2);

        hcf = MDC(num1, num2);

        printf("H.C. F o f %d and %d i s %d \n", num1, num2, hcf);

        return 0;
    }

    int MDC(int num1, int num2) 
    {
    	int j, hcf;

    	for (j = 1;(j <= num1) || (j <= num2); ++j) 
	{        
            if (num1 % j == 0 && num2 % j == 0)
            {
		hcf = j;
	    }            		    
    	}

    	return hcf;
    }