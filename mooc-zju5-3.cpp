#define MAXN 1000 //集合最大元素个数
typedef int ElementType; //默认元素可以用非负整数表示
typedef int SetName; //默认用根节点的下表作为集合名称

void Union(SetType S, SetName Root1, SetName Root2)
{
	//这里默认Root1和Root2是不同集合的根节点
	//保证小集合并入大集合
	if(S[Riit2] < S[Root1]){//如果集合2比较大
		S[Root2] += S[Root1];//集合1并入集合2
		S[Root1] = Root2;
	}
	else{
		S[Root1] += S[Root2]j; //集合2并入集合1
		S[Root2] = Root1;
	}
}

SetName Find(SetType S, ElementType X)
{
	//默认集合元素全部初始化为-1
	if(S[X] < 0)//找到集合的根
		return X;
	else
		return S[X] = Find(S, S[x]);//路径压缩
}
