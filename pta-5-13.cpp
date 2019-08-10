//转录于https://www.cnblogs.com/gk2017/p/7141143.html

#include <stdio.h>
int T[51] = {0};

int main()
{
    int i, N, x;
    scanf("%d", &N);
    for(i=0; i<N; i++)
    {
        scanf("%d", &x);
        T[x]++;
    }
    for(i=0; i<51; i++)
    {
        if(T[i])
            printf("%d:%d\n", i, T[i]);
    }
}