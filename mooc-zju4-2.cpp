typedef struct AVLNode *Position;
typedef Position AVLTree;//AVL树类型
struct AVLNode{
	ElementType Data;//节点数据
	AVLTree Left;//指向左子树
	AVLTree Right;//指向右子树
	int Height;//树高
};

int Max(int a, int b)
{
	return a > b ? a : b;
}

AVLTree SingleLeftRotation(AVLTree A)
{
	//注意：A必须有一个左子节点B
	//将A与B做左单旋，更新A与B的高度，返回新的根节点B
	

	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A:
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right))+1;
	B->Height = Max(GetHeight(B->left), A->Height)+1;

	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
	//注意：A必须有一个左字节点B,且B必须有一个有字节点C
	//将A、B与C做两次单旋，返回新的根节点C
	//将B与C做右单旋，C被返回
	A->Left = SingLeRightRotation(A->Left);
	return SingleLeftRotation(A);
}

AVLTree Insert(AVLTree T, ElementType X)
{
	//将X插入AVL树T中，并且返回调整后的AVL树
	if(!T){
		//若插入空树，则新建包含一个节点的树
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}
	else if(X < T->Data){
		//插入T的左子树
		T->Left = Insert(T->Left, X);
		//如果需要左旋
		if(GetHeight(T->Left)-GetHeight(T->Right) == 2)
			if(X < T->Left->Data)
				T = SingleLeftRotation(T);//左单旋
			else
				T = DoubleLeftRightRotation(T);//左右双旋
	}
	else if(X > T->Data){
		//插入T的右子树
		T->Right = Insert(T->Right, X);
		//如果需要右旋
		if(GetHeight(T->Left)-GetHeight(T->Right) == -2)
			if(X > T->Right->Data)
				T = SingleRightRotation(T);//右单旋
			else
				T = DoubleRightLeftRotation(T);//右-左双旋
	}

	//别忘了更新树高
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right))+1;
	return T;
}
