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

//堆排序
void PrecDown(long A[], int p, int N)
{
    int parent, child;
    long x = A[p];
    for(parent = p; (2*parent+1) < N; parent = child)
    {
        child = 2*parent + 1;
        if(child!=N-1 && A[child+1]>A[child])
            child++; //存在右儿子并且右儿子比左儿子大
        if(A[child] < x)
            break;
        else
            A[parent] = A[child];
    }
    A[parent] = x;
}

void Heap_sort(long A[], int N)
{
    for(int i = N/2; i >= 0; i--)
        PrecDown(A, i, N); //建立堆
    for(int i = N-1; i > 0; i--)
    {
        swap(A[0], A[i]);
        PrecDown(A, 0, i);
    }
}
//堆排序结束

//归并排序（递归版）
void Merge(long A[], long temp[], int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int Num = RightEnd - L + 1;
    int temIdx = L, i;
    while(L <= LeftEnd && R <= RightEnd)
    {
        if(A[L] <= A[R])
            temp[temIdx++] = A[L++];
        else
            temp[temIdx++] = A[R++];
    }
    while(L <= LeftEnd) //如果左边部分有多余
        temp[temIdx++] = A[L++];
    while(R <= RightEnd)//如果右边部分右多余
        temp[temIdx++] = A[R++];
    for(i=0; i<Num; i++, RightEnd--)
        A[RightEnd] = temp[RightEnd];//加temp中的元素返回给A
}

void MSort(long A[], long temp[], int L, int RightEnd)
{
    int center;
    if(L < RightEnd)
    {
        center = (L + RightEnd) / 2;
        MSort(A, temp, L, center);
        MSort(A, temp, center+1, RightEnd);
        Merge(A, temp, L, center+1, RightEnd);
    }
}

void Merge_sort(long A[], int N)
{
    //归并排序入口程序
    long *temp;
    temp = (long*)malloc(N * sizeof(long));
    MSort(A, temp, 0, N-1);
    free(temp);
}
//归并排序结束（递归版）

//归并排序(循环版)
void Merge1(long A[], long temp[], int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int temIdx = L;
    while(L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
            temp[temIdx++] = A[L++];
        else
            temp[temIdx++] = A[R++];
    }
    while(L <= LeftEnd) //如果左边部分有多余
        temp[temIdx++] = A[L++];
    while(R <= RightEnd) //如果右边部分有多余
        temp[temIdx++] = A[R++];
    //与Merge比少了最后一步
}

void Merge_pass(long A[], long temp[], int N, int length)
{
    int i, j;
    for(i = 0; i < N-2*length; i += 2*length)
        Merge1(A, temp, i, i+length, i+2*length-1);
    if(i+length <= N-1)//超过一个子序列 =号必须加
        Merge1(A, temp, i, i+length, N-1);
    else //只剩一个子序列不到了
        for(j = i; j <= N-1; j++)
            temp[j] = A[j];
}

void Merge_sort1(long A[], int N)
{
    long *temp;
    int length =1;
    temp = (long*)malloc(N * sizeof(long));
    while(length < N)
    {
        //这么做A就是排好序的数组
        Merge_pass(A, temp, N, length);
        length *= 2;
        Merge_pass(temp, A, N, length);
        length *= 2;
    }
}
//归并排序结束（循环版）

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