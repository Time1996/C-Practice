//转录于https://blog.csdn.net/Invokar/article/details/80202438

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

using namespace std;

void Bubble_sort(long A[], int N)
{
    //冒泡排序
    for(int P = N-1; P >= 1; P--)
    {
        int flag = 0;
        for (int i = 0; i < P; i++)
        {
            if(A[i] > A[i+1])
            {
                swap(A[i], A[i+1]);
                flag  = 1;
            }
        }
        if(flag == 0) //如果一轮循环没有交换位置，就说明是已经有序了
            break;
    }
}

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d", &N);
    long A[N];
    for(int i = 0; i < N; i++)
        scanf("%ld", &A[i]);
    Bubble_sort(A, N);
    for(int i = 0; i < N; i++)
    {
        if(i != 0)
            printf(" ");
        printf("%ld", A[i]);
    }
    return 0;
}