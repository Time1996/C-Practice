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

void Insert_sort(long A[], int N)
{
    //插入排序
    int P, i;
    for (P = 1; P < N; P++)
    {
        long temp = A[P];
        for(i=P; i>=1 && temp<A[i-1]; i--)
        {
            A[i] = A[i-1];
        }
        A[i] = temp;
    }
}

void Shell_sort(long A[], int N)
{
    //原始的希尔排序
    int P, i, D;
    for(D=N/2; D>=1; D/=2)//希尔增量序列
    {
        for(P=D; P<N; P++)//最后利用插入排序
        {
            long temp = A[P];
            for(i=P; i>=D && temp<A[i-D]; i-=D)
                A[i] = A[i-D];
            A[i] = temp;
        }
    }
}

void ShellHib_sort(long A[], int N)
{
    //Hibbard增量序列的希尔排序
    int k = log2(N), P, i, D;
    for(D=pow(2, k)-1; D>-1 && k>=1; D=pow(2, --k)-1)//增量序列：Dk = 2k -1相邻元素互质
    {
        for(P=D; P<N; P++)
        {
            long temp = A[P];
            for(i=P; i>=D && temp<A[i-D]; i-=D)
                A[i] = A[i-D];
            A[i] = temp;
        }
    }
}

void ShellSed_sort(long A[], int N)
{
    //Sedgewick增量序列的希尔排序
    int D, P, j, i = 0;
    int Sedgewick[] = {3905, 929, 505, 209, 109, 41, 19, 5, 1, 0};
    for(D=Sedgewick[i]; D>=N; D=Sedgewick[i++]);
    for(D=Sedgewick[i]; D>0; D=Sedgewick[++i])
    {
        for(P=D; P<N; P++)
        {
            long temp = A[P];
            for(j=P; j>=D && temp<A[j-D]; j-=D)
                A[j] = A[j-D];
            A[j] = temp;
        }
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