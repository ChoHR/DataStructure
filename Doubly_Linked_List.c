/*
 * title  : Doubly Linked List
 * func   : search, insert, delete, print, quit
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-06
 * writed by CHR
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

typedef int Element;
typedef int ElementType;

struct Node{
ElementType value;
struct Node *next;
struct Node *prev;
};


int IsLast(Position P, List L){
	return P->next == NULL;
}

Position Find(ElementType X, List L){
	Position P;
	P=L;
	while(P!=NULL&&P->value!=X){
		P = P->next;
	}
	return P;
}

int FindOrder(Element X, List L){
	Position P;
	int order = 0;

	P=L;

	while(!IsLast(P,L)&&P->value!=X){
		P = P->next;
		order++;
	}
	if(P->value == X)
		return order;
	else
		return 0;
}

// insert new node behind P
void insertNodeBehindP(ElementType X, List L, Position P){
	Position TmpCell;

	TmpCell = (Position)malloc(sizeof(struct Node));
	if(TmpCell == NULL){
		printf("error : Out of space\n");
		return;
	}
	TmpCell->value = X;

	if(P->next == NULL){
		P->next = TmpCell;
		TmpCell->prev = P;
		return;
	}
	else{	
		TmpCell->next = P->next;
		TmpCell->next->prev = TmpCell;
		P->next = TmpCell;
		TmpCell->prev = P;
	}
}

// insert new node behind the last node
void insertNode(ElementType X, List L){
	struct Node *New= (struct Node*)malloc(sizeof(struct Node));
	Position Point;
	New->value = X;
	New->next = NULL;
	New->prev = NULL;

	if(L->next == NULL){
		L->next=New;
		New->prev = L;
	}
	else{
		Point=L->next;
		while(!IsLast(Point,L)) 
			Point=Point->next;
		Point->next=New;
		New->prev = Point;
	}
}

void deleteNode(ElementType X, List L){
	Position P,TmpCell;
	P = Find(X,L);

	if(P == NULL)
		return;

	if(P->next == NULL){
		P->prev->next = NULL;
	}
	else{
		P->prev->next = P->next;
		P->next->prev = P->prev;
	}

	free(P);
}

void display(List L){
	Position P;
	P = L->next;
	while(1){
		if(L->next == NULL){
			printf("NULL");
			break;
		}
		else if(IsLast(P,L)){
			printf("%d -> ",P->value);
			break;
		}
		else{
			printf("%d -> ",P->value);
			P=P->next;
		}
	}
	printf("\n");
}

Position CreateEmptyList(){
	List L=(struct Node*)malloc(sizeof(struct Node));
	L->value=0;
	L->next=NULL;
	L->prev=NULL;

	return L;
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

int main(void){
	char select;
	int num;
	int c;

	List L;
	
	//initialize List
	L = CreateEmptyList();
	
	printf("enter command\ns : search\ni : insert\nd : delete\np : print\nq : exit\n");
	
	//select function. (i,d,s,p,q)
	while(1){
		printf("> ");
		scanf("%c",&select);

		while((c = getchar())!='\n' && c != EOF)
			;

		if(select == 'i'){
			printf("enter the item that you want to insert\n");
			scanf("%d",&num);
			while((c = getchar())!='\n' && c != EOF)
				;
			insertNode(num,L);
		}
		else if(select == 'd'){
			printf("enter the item that you want to delete\n");
			scanf("%d",&num);
			while((c = getchar())!='\n' && c != EOF)
				;
			deleteNode(num,L);
		}
		else if(select == 'p'){
			display(L);
		}
		else if(select == 's'){
			printf("enter the item that you want to search\n");
			scanf("%d",&num);
			while((c = getchar())!='\n' && c != EOF)
				;
			if(FindOrder(num,L) != 0)
				printf("order of the list having the \"%d\" is \"%d\"\n",num,FindOrder(num,L));
			else
				printf("\"%d\" don't exist in the List\n",num);
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

	}	

	return 0;
}