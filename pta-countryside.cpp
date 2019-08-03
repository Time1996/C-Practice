//转录于https://blog.csdn.net/Invokar/article/details/80150527

#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 1003
#define INFINITY 65536
int MGraph[MaxVertexNum][MaxVertexNum];
int dist[MaxVertexNum] = {INFINITY};
int parent[MaxVertexNum] = {0};//如果需要输出联通路径，这里不需要，可无视

int FindMinDist(int Nv)
{
    //寻找未被收录的当前最短路径的顶点下标
    int MinDist = INFINITY, V, Min;
    for(V = 1; V<=Nv; V++)
    {
        if(dist[V]!=0 && dist[V]<MinDist)
        {
            //如果节点V未被收录(为0表示被收录)并且小于最短距离
            MinDist = dist[V]; //更新最短距离
            Min = V;//设置V的父亲节点为0
        }
    }
    if(MinDist<INFINITY)
        return Min; //如果找到返回顶点下标
    else
        return 0;
}

int Prim(int Nv)
{
    int TotalCost = 0, Vcount = 0, V, W;
    for(V=1; V<=Nv; V++)
    {
        //初始化dist,并设置所有节点的父节点为1
        dist[V] = MGraph[1][V];
        parent[V] = 1;
    }
    //把1点收入
    dist[1] = 0;
    parent[1] = -1;
    Vcount++;

    while(1)
    {
        V = FindMinDist(Nv);
        if(!V)
            break;
        Vcount++;
        TotalCost += dist[V];
        dist[V] = 0;//把V点收录进来
        for(W=1; W<=Nv; W++)
        {
            if(dist[W]!=0 && MGraph[V][W]<dist[W])
            {
                //如果W未被收录 并且V<->W之间的距离变小
                dist[W] = MGraph[V][W];
                parent[W] = V;
            }
        }
    }
    if(Vcount == Nv)//如果最小生成树的边数正好为Nv-1
        return TotalCost;
    else//反之，无法构成最小生成树
        return -1;
}

int main(int argc, char const *argv[])
{
    int N, M, v, w, cost, MinCost;
    scanf("%d %d", &N, &M);
    //初始化图
    for(int i = 1; i<=N; i++)
    {
        for(int j = 1; j<=N; j++)
            MGraph[i][j] = INFINITY;
    //输入图信息并更新图
    for(int i = 1; i<=M; i++)
    {
        scanf("%d %d %d", &v, &w, &cost);
        MGraph[v][w] = cost;
        MGraph[w][v] = cost;
    }
    MinCost = Prim(N);
    printf("%d\n", MinCost); //输出结果

    return 0;
    }
}