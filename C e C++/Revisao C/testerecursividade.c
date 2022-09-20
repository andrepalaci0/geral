#include <stdio.h>

int fat(int n);

int main()
{
    int n = 6;
    printf("fatorial = %i" , fat(n));
    return 0;
}

int fat( int n)
{
    int fa;
    if(n > 1){
        fa = n * fat(n-1);
    }else{
        return 1;
    }
    return fa;
}