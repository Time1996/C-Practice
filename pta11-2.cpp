//转录于https://blog.csdn.net/Invokar/article/details/80372316

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int GetNextPrime(int x)
{
    //若为偶数，找当前数下一个最小的素数
    if(x == 1) //1不是素数
        return 2;
    int i, p = x % 2 == 1 ? x : x+1;
    while(1)
    {
        for(i = sqrt(p); i >= 2; i--)
            if(p % i == 0)
                break;
        if(i == 1)
            break;
        else
            p += 2;
    }
        return p;
}
int Hash(int key, int TableSize)
{
     //获取映射
    return key % TableSize;
}
int main(int argc, char const *argv[])
{
        int TableSize, N, x, pos, tempPos;
        scanf("%d %d", &TableSize, &N);
        TableSize = GetNextPrime(TableSize);
        int A[TableSize];
        for(int i = 0; i < TableSize; i++)
            A[i] = 0;
        for(int i = 0; i < N; i++)
        {
            if(i != 0)//规格化输出格式
                printf(" ");
            scanf("%d", &x);
            pos = Hash(x, TableSize);
            tempPos = pos;
            if(A[tempPos] == 0)
            {
                //如果当前下标未被使用
                A[tempPos] = x;
                printf("%d", pos);
            }
            else
            {
                int cnt, flag = 0;
                for(cnt = 1; cnt < TableSize; cnt++)
                {
                    pos = Hash(tempPos + cnt*cnt, TableSize);
                    if(A[pos] == 0)
                    {
                        //如果找到不冲突的点
                        flag = 1;
                        A[pos] = x;
                        printf("%d", pos);
                        break;
                    }
                }
                if(flag == 0)
                    printf("-");
            }
        }
        return 0;
}