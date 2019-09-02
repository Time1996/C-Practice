BinTree Insert(BinTree BST, ElementType X)
{
	if(!BST){
		//若原树为空，生成并返回一个节点的二叉搜索树
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else{
		if(X < BST->Data)
				BST->Left = Insert(BST->Left, X);//递归插入左子树
		else if(X>BST->Data)
				BST->Right = Insert(BST->Right, X);//递归插入右子树
	}
	return BST;
}

BinTree Delete(BinTree BST, ElementType X)
{
	Position Tmp;

	if(!BST)
		printf("要删除的元素未找到");
	else{
		if(X<BSt->Data)
			BST->Left = Delete(BST->Lef, X);//从左子树递归删除
		else if(X > BST->Data)
			BST->Right = Delete(BST->Right, X);//从右子树递归删除
		else{
			//BST就是要删除的节点
			if(BST->Left && BST->Right){
				Tmp = FindMin(BST->Right);
				BST->Data = Tmp->Data;
				//从右子树中删除最小元素
				BST->Right = Delete(BST->Right, BST->Data)
			}
			else{
				//被删除节点有一个或无字节点
				Tmp = BST;
				if(BST = BST->Right; //只有右孩子或我无子节点
						BST = BST->Right;
				else
					BST = BST->Left;
				free(Tmp);
			}
		}
	}
	return BST;
}
