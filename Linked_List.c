/*
 * title  : Linked List
 * func   : search, insert, delete, print, quit
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-06
 * writed by CHR
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Element;

typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

struct Node{
Element data;
struct Node *next;
} *L;

int IsEmpty(List L){
	return L->next == NULL;
}

int IsLast(Position P, List L){
	return P->next == NULL;
}

// insert new node behind the last node
void insertNode(Element X, List L){
	struct Node *New= (struct Node*)malloc(sizeof(struct Node));
	Position Point;
	New->data=X;
	New->next=NULL;
	
	if(IsEmpty(L)){
		L->next=New;
	}
	else{
		Point=L->next;
		while(!IsLast(Point,L)) 
			Point=Point->next;
		Point->next=New;
	}
}

Position FindPrevious(Element X, List L){
	Position P;

	P = L;
	while(!IsLast(P,L)&&P->next->data!=X)
		P=P->next;
	return P;
}

void deleteNode(Element X, List L){
	Position P,TmpCell;

	P = FindPrevious(X,L);
	if(!IsLast(P,L)){
		TmpCell = P->next;
		P->next = TmpCell->next;
		free(TmpCell);
	}
	else{
		free(P->next);
		P->next = NULL;
	}
}

void DeleteList(List L){
	Position P,Tmp;

	P = L->next;
	L->next = NULL;
	while(P!=NULL){
		Tmp = P->next;
		free(P);
		P=Tmp;
	}
}


void display(List L){
	Position P;
	P = L->next;
	while(1){
		if(IsEmpty(L)){
			printf("NULL");
			break;
		}
		else if(IsLast(P,L)){
			printf("%d -> ",P->data);
			break;
		}
		else{
			printf("%d -> ",P->data);
			P=P->next;
		}
	}
	printf("\n");
}

Position Find(Element X, List L){
	Position P;
	
	P=L->next;
	while(!IsLast(P,L)&&P->data!=X)
		P = P->next;
	
	return P;
}

int FindOrder(Element X, List L){
	Position P;
	int order = 0;

	P=L;

	while(!IsLast(P,L)&&P->data!=X){
		P = P->next;
		order++;
	}
	return order;
}
	
int main(void){
	char select;
	int num;
	
	//L의 초기화
	
	L=(struct Node*)malloc(sizeof(struct Node));
	L->data=0;
	L->next=NULL;
	
	printf("enter command\ns : search\ni : insert\nd : delete\np : print\nq : exit\n");
	
	//s,i,d,p,q 중 선택
	while(1){
		printf("> ");
		scanf("%c",&select);
		rewind(stdin);

		if(select == 's'){
			printf("enter the item that you want to search\n");
			scanf("%d",&num);
			if(FindOrder(num,L) != 0)
				printf("order of the list having the \"%d\" is \"%d\"\n",num,FindOrder(num,L));
			else
				printf("\"%d\" don't exist in the List\n",num);
		}
		else if(select == 'i'){
			printf("enter the item that you want to insert\n");
			scanf("%d",&num);
			insertNode(num,L);
		}
		else if(select == 'd'){
			printf("enter the item that you want to delete\n");
			scanf("%d",&num);
			deleteNode(num,L);
		}
		else if(select == 'p'){
			display(L);
		}	
		else if(select == 'q'){
			DeleteList(L);
			printf("success to delete all List\n");
			return 0;
		}
		else{
			printf("\"%c\" is not right command\n",select);
			printf("enter command\ns : search\ni : insert\nd : delete\np : print\nq : exit\n");
		}
		rewind(stdin);
	}	

	return 0;
}