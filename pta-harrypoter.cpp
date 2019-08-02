//转录于https://www.cnblogs.com/yuxiaoba/p/8341693.html
/*
解题思路：1、先用图的最短路径Floyd算法求出每个动物变成其他动物所需的最小魔咒字符数矩阵

                 2、找出每个动物变成其他动物需要的最长魔咒字符

                 3、在这些最长魔咒字符中找出最小字符便是答案

                 4、若图不连通，则只带1只动物是不可能完成所有变形要求的，输出0

                 5、最后再补充一点是Floyd算法是一个三重循环的算法，时间复杂度O(N^3),当面临需要求所有顶点到所有顶点

                      的最短路径是比较推荐，但如果是单源最短路径，还是用Dijkstra吧
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 105
#define INFINITY 65535

void CreateGraph();
void Floyd();
void FindAnimal();
int FindMax(int i);

int G[MAXVEX][MAXVEX], Nv, Ne;
int D[MAXVEX][MAXVEX]; //存储最短路径矩阵

int main()
{
    CreateGraph();
    FindAnimal();
    return 0;
}

void CreateGraph()
{
    //用邻接矩阵表示图
    int i, j;
    int v1, v2, w;
    scanf("%d %d", &Nv, &Ne);
    for(i=1; i<=Nv; i++)
    {
        for(j=1; j<=Nv; j++)
        {
            if(i==j){
                G[i][j] = 0;
            }
            else G[i][j] = INFINITY; //初始化
        }
    }

    for(i=0; i<Ne; i++)//注意这里是读入边
    {
        scanf("%d %d %d", &v1, &v2, &w);
        G[v1][v2] = w; //读入权值
        G[v2][v1] = G[v1][v2]; //无向图对称
    }
}

void FindAnimal()
{
    int max, min;
    int animal;
    int i;

    Floyd();

    min = INFINITY;
    for(i=1; i<=Nv; i++)
    {
        //比较每行最大距离，寻找其中最小值
        max = FindMax(i);
        if(max == INFINITY)
        {
            //判断图是否连通
            printf("0\n");
            return;
        }
        if(min>max)
        {
            min = max;
            animal = i;
        }
    }
    printf("%d %d\n", animal, min);
}

int FindMax(int i)
{
    int max;
    int j;

    max = 0;
    for(j=1; j<=Nv; j++)
    {
        if(i!=j && D[i][j]>max)
        {
            max = D[i][j];
        }
    }
    return max;
}

void Floyd()
{
    int i, j, k;

    for(i=1; i<=Nv; i++)
    {
        for(j=1; j<=Nv; j++)
        {
            D[i][j] = G[i][j];
        }
    }
        //注意动物是从下标1开始编号
    for(k=1; k<=Nv; k++)
    {
        for(i=1; i<=Nv; i++)
        {
            for(j=1; j<=Nv; j++)
            {
                if(D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}