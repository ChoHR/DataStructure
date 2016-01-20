/*
 * title  :Binary Search Tree
 * func   : Find, Insert, Delete, Print(Inorder, Preorder, Postorder), Init
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-21
 * writed by CHR
 
 * 항상 Lnode < parant < Rnode인 tree이다.
 * 재귀호출로 Print함수를 구현하였다.
 * FindMax는 여기서 쓰이지 않는다.
 * 선언된 함수는 전부 구현하였다.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int ElementType;
typedef struct Tree *BSTree;
typedef BSTree Position;

struct Tree{
	ElementType Element;
	BSTree Rnode;
	BSTree Lnode;
};

Position Insert(ElementType X, BSTree T);
Position Find(ElementType X, BSTree T);
Position FindMin(BSTree T);
Position FindMax(BSTree T);
void printInorder(BSTree T);
void printPreorder(BSTree T);
void printPostorder(BSTree T);
void creat(BSTree T);
Position Delete(ElementType X, BSTree T);
BSTree InitializeBSTree();
void Error(char* string);

int main(void){
	//R의 초기화
	char select=0;
	int num;
	char flag[5]="";
	BSTree T;

	T = InitializeBSTree();

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

BSTree InitializeBSTree(){
	BSTree T = (BSTree)malloc(sizeof(struct Tree));
	if(T == NULL)
		Error("Out of space !!!");

	creat(T);

	return T;
}

Position Delete(ElementType X, BSTree T){
	Position TmpCell;

	if(T == NULL){
		Error("Element not found");
	}
	else if(X < T->Element){
		T->Lnode = Delete(X,T->Lnode);
	}
	else if(X > T->Element)
		T->Rnode = Delete(X, T->Rnode);
	
	// T->Element == X.
	else if(T->Lnode && T->Rnode){ // two children
		TmpCell = FindMin(T->Rnode);
		T->Element = TmpCell->Element;
		T->Rnode = Delete(T->Element, T->Rnode);
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
	}
	return T;
}

void creat(struct Tree* T){
	T->Lnode=NULL;
	T->Rnode=NULL;
	T->Element=NULL;
}

void Error(char* string){
	printf("%s\n",string);
}

Position Insert(ElementType X, BSTree T){
	if(T == NULL){
		T = InitializeBSTree();
		T->Element = X;
	}
	else if(T->Element == NULL){
		T->Element = X;
	}
	else if(X < T->Element){
		T->Lnode = Insert(X,T->Lnode);
	}
	else if(X > T->Element){
		T->Rnode = Insert(X,T->Rnode);
	}
	return T;
}

Position FindMin(BSTree T){
	if(T == NULL){
		return NULL;
	}
	else if(T->Lnode == NULL)
		return T;
	else
		return FindMin(T->Lnode);
}

Position FindMax(BSTree T){
	if(T == NULL){
		return NULL;
	}
	else if(T->Rnode == NULL)
		return T;
	else
		return FindMax(T->Rnode);
}

Position Find(ElementType X, BSTree T){
	if(T==NULL)
		return T;
	if(T->Element > X)
		return Find(X,T->Lnode);
	else if(T->Element < X)
		Find(X, T->Rnode);
	else 
		return T;
}

void printInorder(BSTree T){
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
void printPreorder(BSTree T){
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
void printPostorder(BSTree T){
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