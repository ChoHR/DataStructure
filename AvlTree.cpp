/*
 * title  :AVL Tree
 * func   : Find, Insert, Delete, Print(Inorder, Preorder, Postorder), Init
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-21
 * writed by CHR
 
 * 항상 Lnode < parant < Rnode인 tree이다.
 * O(nlogn)을 보장한다.
 * SingleRotateWithLeft
        3       2
	   2   ->  1 3
	  1
   DoubleRotateWithLeft
             7                    7                  4
	    2         8   ->      4       8   ->     2       7
	  1   4        9        2   5      9        1 3    5   8
	 0   3 5               1 3   6             0        6   9
		    6             0

 * Delete의 경우는 충분한 testcase가 없어 제대로 검사 못했지만, 아마 될 것이다...
 * 재귀호출로 Print함수를 구현하였다.
 * FindMax는 여기서 쓰이지 않는다.
 * 선언된 함수는 전부 구현하였다.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int ElementType;
typedef struct Tree *AvlTree;
typedef AvlTree Position;

struct Tree{
	int Height;
	ElementType Element;
	AvlTree Rnode;
	AvlTree Lnode;
};

Position Insert(ElementType X, AvlTree T);
Position SingleRotateWithLeft(Position P);
Position SingleRotateWithRight(Position P);
Position DoubleRotateWithLeft(Position P);
Position DoubleRotateWithRight(Position P);
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
void printInorder(AvlTree T);
void printPreorder(AvlTree T);
void printPostorder(AvlTree T);
void creat(AvlTree T);
Position Delete(ElementType X, AvlTree T);
AvlTree InitializeAvlTree();
void Error(char* string);
int Max(int H1, int H2);

int main(void){
	//R의 초기화
	char select=0;
	int num;
	char flag[5]="";
	AvlTree T;

	T = InitializeAvlTree();

	while(1){
		scanf("%c",&select);
		if(select == 'i'){
			scanf("%d",&num);
			T = Insert(num,T);
		}
		else if(select == 'p'){
			scanf("%s",flag);
			if(!strcmp(flag,"r")){
				printInorder(T);
				printf("\n");
			}
	
			else if(!strcmp(flag,"f")){
				printPreorder(T);
				printf("\n");
			}
		}
		else if(select == 'd'){
			scanf("%d",&num);
			T = Delete(num,T);
		}
		else if(select == 'q'){
			return 0;
		}
	}
	return 0;
}

int Max(int H1, int H2){
	if(H1 > H2)
		return H1;
	else
		return H2;
}

AvlTree InitializeAvlTree(){
	AvlTree T = (AvlTree)malloc(sizeof(struct Tree));
	if(T == NULL)
		Error("Out of space !!!");

	creat(T);

	return T;
}
void creat(struct Tree* T){
	T->Lnode   = NULL;
	T->Rnode   = NULL;
	T->Height  = 0;
	T->Element = NULL;
}
void Error(char* string){
	printf("%s\n",string);
}
int Height(Position P){
	if(P == NULL)
		return -1;
	else
		return P->Height;
}

Position Delete(ElementType X, AvlTree T){
	Position TmpCell;

	if(T == NULL){
		Error("Element not found");
	}
	else if(X < T->Element){
		T->Lnode = Delete(X,T->Lnode);
		if(Height(T->Lnode) - Height(T->Rnode) == -2){
			T = SingleRotateWithRight(T);
		}
	}
	else if(X > T->Element){
		T->Rnode = Delete(X, T->Rnode);
		if(Height(T->Rnode) - Height(T->Lnode) == -2){
			T = SingleRotateWithLeft(T);
		}
	}
	// T->Element == X.
	else if(T->Lnode && T->Rnode){ // two children
		TmpCell = FindMin(T->Rnode);
		T->Element = TmpCell->Element;
		T->Rnode = Delete(T->Element, T->Rnode);
		if(Height(T->Rnode) - Height(T->Lnode) == -2){
			T = SingleRotateWithLeft(T);
		}
	}
	else if(T->Lnode != NULL){ // only left child
		TmpCell = T;
		T = T->Lnode;
		free(TmpCell);
	}
	else if(T->Rnode != NULL){ // only right child
		TmpCell = T;
		T = T->Rnode;
		free(TmpCell);
	}
	else{ // 0 child
		TmpCell = T;
		T = NULL;
		free(TmpCell);
		return T;
	}

	T->Height = Max(Height(T->Lnode),Height(T->Rnode)) + 1;

	return T;
}

Position Insert(ElementType X, AvlTree T){
	if(T == NULL){
		T = InitializeAvlTree();
		creat(T);
		T->Element = X;
	}
	else if(T->Element == NULL){
		T->Element = X;
	}
	else if(X < T->Element){
		T->Lnode = Insert(X,T->Lnode);
		if(Height(T->Lnode)-Height(T->Rnode) == 2){
			if(X < T->Lnode->Element){
				printf("SL\n");
				T = SingleRotateWithLeft(T);
			}
			else{
				printf("DL\n");
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else if(X > T->Element){
		T->Rnode = Insert(X,T->Rnode);
		if(Height(T->Rnode) - Height(T->Lnode) == 2){
			if(X > T->Rnode->Element){
				printf("SR\n");
				T = SingleRotateWithRight(T);
			}else{	
				printf("DR\n");
				T = DoubleRotateWithRight(T);
			}
		}
	}

	T->Height = Max(Height(T->Lnode),Height(T->Rnode)) + 1;
	return T;
}

Position SingleRotateWithLeft(Position K2){
	Position K1;
	K1 = K2->Lnode;
	K2->Lnode = K1->Rnode;
	K1->Rnode = K2;
	K2->Height = Max(Height(K2->Lnode),Height(K2->Rnode)) + 1;
	K1->Height = Max(Height(K1->Lnode),Height(K1->Rnode)) + 1;
	
	return K1;
}
Position SingleRotateWithRight(Position K2){
	Position K1;
	K1 = K2->Rnode;
	K2->Rnode = K1->Lnode;
	K1->Lnode = K2;
	K2->Height = Max(Height(K2->Lnode),Height(K2->Rnode)) + 1;
	K1->Height = Max(Height(K1->Lnode),Height(K1->Rnode)) + 1;
	
	return K1;
}
Position DoubleRotateWithLeft(Position K3){
	K3->Lnode = SingleRotateWithRight(K3->Lnode);
	return SingleRotateWithLeft(K3);
}
Position DoubleRotateWithRight(Position K3){
	K3->Rnode = SingleRotateWithLeft(K3->Rnode);
	return SingleRotateWithRight(K3);
}


Position FindMin(AvlTree T){
	if(T == NULL){
		return NULL;
	}
	else if(T->Lnode == NULL)
		return T;
	else
		return FindMin(T->Lnode);
}

Position FindMax(AvlTree T){
	if(T == NULL){
		return NULL;
	}
	else if(T->Rnode == NULL)
		return T;
	else
		return FindMax(T->Rnode);
}

Position Find(ElementType X, AvlTree T){
	if(T==NULL)
		return T;
	if(T->Element > X)
		return Find(X,T->Lnode);
	else if(T->Element < X)
		Find(X, T->Rnode);
	else 
		return T;
}

void printInorder(AvlTree T){
	if(T==NULL)
		return;
	else{
		if(T->Lnode!=NULL)
			printInorder(T->Lnode);
		if(T->Element!=NULL)
			printf("%d ",T->Element);
		if(T->Rnode!=NULL)
			printInorder(T->Rnode);
	}
}
void printPreorder(AvlTree T){
	if(T==NULL)
		return;
	else{
		if(T->Element!=NULL)
			printf("%d ",T->Element);
		if(T->Lnode!=NULL)
			printPreorder(T->Lnode);
		if(T->Rnode!=NULL)
			printPreorder(T->Rnode);
	}
}
void printPostorder(AvlTree T){
	if(T==NULL)
		return;
	else{
		if(T->Rnode!=NULL)
			printPostorder(T->Rnode);
		if(T->Lnode!=NULL)
			printPostorder(T->Lnode);
		if(T->Element!=NULL)
			printf("%d ",T->Element);
	}
}