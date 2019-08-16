//转录于https://blog.csdn.net/invokar/article/details/80374096
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MaxTableSzie 100000

typedef struct Info* PtrToNode;
struct Info{
    long ID;
    char PWD[17];
    PtrToNode next;
};
typedef struct Info* list;

typedef struct HashNode* HashTable;
struct HashNode
{
    list Heads;
    int size;
};

int GetNextPrime(int x)
{
    //如果当前数不是素数，找最小的素数
    int i, p = x % 2 == 1 ? x : x+1;
    while(p <= MaxTableSzie)
    {
        for(i = sqrt(p); i >= 2; i--)
            if(p%i == 0)
                break;
        if(i == 1)
            break;
        else
            p += 2;
    }
    return p;
}

int Hash(int key, int HashTableSize)
{
    //给出映射位置
    return key % HashTableSize;
}

HashTable CreateTable(int n)
{
    //创建散列表
    HashTable H = (HashTable)malloc(sizeof(HashNode));
    H->size = GetNextPrime(n);
    H->Heads = (PtrToNode)malloc(H->size * sizeof(Info)); //这里别忘记
    for(int i = 0; i < H->size; i++)
    {
        H->Heads[i].ID = 0;
        H->Heads[i].PWD[0] = '\0';
        H->Heads[i].next = NULL;
    }
    return H;
}

void Insert(HashTable H, long ID, char PWD[])
{
    //插入信息
    int pos = Hash(ID, H->size);
    PtrToNode check = H->Heads[pos].next;
    while(check)
    {
        //确认是否已经有该信息了
        if(check->ID == ID)
            break;
        check = check->next;
    }
    if(check)//如果check不为NULL，说明已经存在
        printf("ERROR:Exist\n");
    else
    {
        //如果不存在，采用头插法插入
        PtrToNode NewNode = (PtrToNode)malloc(sizeof(Info));
        NewNode->ID = ID;
        strcpy(NewNode->PWD, PWD);
        NewNode->next = H->Heads[pos].next;
        H->Heads[pos].next = NewNode;
        printf("New:OK\n");
    }    
}

void Login(HashTable H, long ID, char PWD[])
{
    //登陆账号
    int pos = Hash(ID, H->size);
    PtrToNode user = H->Heads[pos].next;
    while(user)//遍历
    {
        if(user->ID != ID)//如果该节点ID不为用户ID，往后遍历
            user = user->next;
        else
        {
            if(strcmp(user->PWD, PWD) == 0)
                printf("Login:OK\n");
            else
                printf("ERROR:Wrong PW\n");
            break;
        }
        
    }
    if(user == NULL)//如果用户不存在
        printf("ERROR:Not Exist\n");
}

int main(int argc, char const *argv[])
{
    int N, size;
    long ID;
    char PWD[17], cmd;
    scanf("%d", &N);
    getchar();//挡掉回车
    size = GetNextPrime(N);
    HashTable H = CreateTable(size);
    for(int i = 0; i < N; i++)
    {
        scanf("%c %ld %s", &cmd, &ID, PWD);
        if(cmd == 'L')
            Login(H, ID, PWD);
        else
            Insert(H, ID, PWD);
        getchar();//挡掉回车
    }
    return 0;
}