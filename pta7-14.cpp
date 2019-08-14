//转录于https://www.cnblogs.com/8023spz/p/8145740.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char s[200000][12];
int cmp(const void *a, const void *b)
{
    return strcmp((char*)a,(char*)b)>0?1:-1;
}
int main()
{
    int n;
    int c = 1, d = 1;
    int maxi = 0;
    char ans[12] = "00000000000";
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%s%s", s[i*2], s[i*2+1]);
    }
    qsort(s, 2*n, sizeof(s[0]), cmp);
// for(int i = 0; i < n * 2 + 1; i++)
// printf("%s\n",s[i]);
    for(int i = 1; i < n * 2 + 1; i++)
    {
        if(strcmp(s[i], s[i-1]) == 0)d++;
        else
        {
            if(d>maxi)
            {
                strcpy(ans, s[i -1]);
                maxi = d;
                c =1;
            }
            d = 1;
        }
    }
    printf("%s %d", ans, maxi);
    if(c>1)printf("%d", c);
}