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

//用map的性质来做这题，转录于https://blog.csdn.net/hebau_pss/article/details/79362457

#include <bits/stdc++.h>
using namespace std;

map<long long, int> p;
int main()
{
    int i, n, max;
    long long s, temp;
    scanf("%d", &n);
    max = 0;
    for(i = 0; i < 2 * n; i++)
    {
        scanf("%lld", &s);
        if(!p.count(s))
        {
            p[s]=0;
        }
        p[s]++;
        if(p[s]>max)
            max=p[s];
    }
    map<long long, int>::iterator t;
    long long numb;
    int flag = 0;
    int count = 0;
    for(t=p.begin();t!=p.end();t++)
    {
        if(t->second == max)
        {
            count++;
            if(count == 1)
                numb=t->first;
        }
    }
    cout<<numb;
    printf("%d", max);
    if(count>1)
        printf("%d", count);
    return 0;
}