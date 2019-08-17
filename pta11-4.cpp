//转录于https://blog.csdn.net/invokar/article/details/80383159

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;
int Arr[1001];

int ConflictTimes(int i, int key, int tablesize)
{
    //计算每一个节点的冲突次数
    return (i - key%tablesize + tablesize) % tablesize;
}

int Hash(int key, int tablesize)
{
    //计算初始映射位置
    return key % tablesize;
}

struct cmp
{
    //比较函数 小顶堆
    bool operator()(int i, int j)
    {
        return Arr[i] > Arr[j];
    }
};

int main(int argc, char const *argv[])
{
    int N, x, flag = 0;
    scanf("%d", &N);
    int Indegree[N];
    vector<vector<int>>v(N);
    priority_queue<int, vector<int>, cmp> q;
    for(int i = 0; i < N; i++)
    {
        //计算每一个值的冲突次数也即入度
        scanf("%d", &x);
        Arr[i] = x;
        if(x >= 0)//跳过空位
        {
            int pos = Hash(x, N);
            Indegree[i] = ConflictTimes(i, x, N);
            if(Indegree[i])//如果入度不是0
                for(int j = 0; j <= Indegree[i]; j++)
                    v[Hash(pos+j, N)].push_back(i);
            else//如果入度为0则直接放入优先级队列
                q.push(i);
        }
    }
    while (!q.empty())
    {
        //如果队列不空，每次取队头元素，并将以队头元素为前驱的元素入度-1
        int pos = q.top();
        q.pop();
        if(flag == 1)
            printf(" ");
        printf("%d", Arr[pos]);
        flag = 1;
        for(int k = 0; k < v[pos].size(); k++)
            if(--Indegree[v[pos][k]] == 0)
                q.push(v[pos][k]);
    }
    return 0;
}