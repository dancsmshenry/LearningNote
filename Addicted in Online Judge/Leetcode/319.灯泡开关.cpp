#include <stdio.h>
int main()
{ 
    int i, n, sum = 0;
    scanf("%d", &n); 

    while (1)
        if (i * i < n)
        {
            i++;
            continue;
        }
        else if (i * i == n)
        {
            sum = i;
            break;
        }
        else
        {
            sum = i - 1;
            break;
        }
    
    printf("%d", sum);
    return 0;
 } 
