typedef struct LNode *PtrToLNode;
struct LNode{
	ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

//查找

Position Find(List L, ElementType X)
{
	Position p = L;//p指向L的第一个结点

	while(p && p->Data!=X)
		p = p->Next;

	//下列语句可以用return p;替换
	if(p)
		return p;
	else
		return ERROR;
}

//带头节点的插入
bool Insert(List L, ElementType X, Position P)
{
	//这里默认L有头节点
	Position tmp, pre;
	for(pre=L; pre&&pre->Next!=P; pre=pre->Next
	if(pre==NULL){
		printf("插入位置参数错误\n");
		return false;
	}
	else{
	tmp=(Position)malloc(sizeof(struct LNode));//申请，填装节点
	tmp->Data = X;
	tmp->Next = P;
	pre->Next = tmp;
	return true;
	}
}

//带头节点的删除

bool Delete(List L, Position P)
{
	Position tmp, pre;

	for(pre=L; pre&&pre->Next!=P; pre=pre->Next);
	if(pre==NULL||P==NULL){
	//P所指的节点不在L中
		printf("删除位置参数错误\n");
		return false;
	}
	else{
		//找到了P的前一个节点pre
		//将P位置的节点删除
		pre-Next = P->Next;
		free(P);
		return true;
	}
}
