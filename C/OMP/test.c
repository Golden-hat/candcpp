#include <omp.h>
#include <stdio.h>

#define LIMIT 1000000

int main(void)
{
        double serie = 0;
        long long i;
        #pragma omp parallel
        {
                #pragma omp for reduction(+:serie)
                for(i = 1;i <= LIMIT;i++)
                serie += 1.0/i;
        }

        printf("Valor de la Serie: %.5f\n",serie);
return 0;
}