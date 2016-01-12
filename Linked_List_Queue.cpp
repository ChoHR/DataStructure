/*
 * Linked List를 이용한 Queue
 * 메모리를 탄력적으로 사용하는 게 장점.
 */

/*
 * title  : Linked List Queue
 * func   : Print, Enqueue, Dequeue
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-12
 * writed by CHR
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct QueueType *Queue;
typedef struct QueueNode *Node;

struct QueueType{
	Node front;
	Node rear;
};

struct QueueNode{
	int item;
	Node link;
};
	
//head의 값을 초기화
void MakeEmpty(struct QueueType *q){
	q->rear=NULL;
	q->front=NULL;
}

Queue CreateQueue(){
	Queue q=(Queue)malloc(sizeof(struct QueueType));
	q->rear=(Node)malloc(sizeof(struct QueueNode));
	q->front=(Node)malloc(sizeof(struct QueueNode));
	MakeEmpty(q);
	return q;
}

/* 
 * insert New node. queue -> front -> link -> ... -> link -> New -> NULL
 *                  queue -> rear  -> New  -> NULL
 */
void enqueue(struct QueueType *q, int item){
	struct QueueNode *New=(Node)malloc(sizeof(struct QueueNode));
	struct QueueNode *Point;

	New->item=item;
	New->link=NULL;

	if(q->front==NULL){
		q->rear=New;
		q->front=New;
	}
	else{
		Point=q->front;
		while(Point->link != NULL) {
			Point=Point->link;
		}
		Point->link=New;
		q->rear=New;
	}
}
/*
 * print nodes. if parameter is q->front, print front->item, front->link->item, front->link-> ... ->rear->item  
 *              if parameter is q->rear,  print rear ->item
 */
void PrintNode(Node node){
	Node n = node;
	if(n == NULL){
		printf("empty node !!!\n");
		return;
	}
	while(n->link != NULL){
		printf("%d -> ",n->item);
		n = n->link;
	}
	printf("%d\n",n->item);
}

bool IsEmpty(struct QueueType *q){
	if(q->rear==NULL){
		printf("queue is empty\n");
		return true;
	}
	return false;
}
/*
 * delete front's first node. 
 * if queue is q : 1 -> 2 -> 3 -> 4 -> NULL
 * front = 1, rear = 4. 
 * after dequeue(q)
 * front = 2, rear = 4.
 */
int dequeue(struct QueueType *q){
	Node P;

	if(IsEmpty(q))
		return 0;
	P = q->front;
	printf("%d\n",P->item);
	if(P->link!=NULL){
		q->front = P->link;
	}
	else{
		q->rear=NULL;
		q->front=NULL;
	}
	free(P);
	return 0;
}


int main(void){
	char select;
	int num;
	Queue q = CreateQueue();

	/*
	 * i : enqueue
	 * d : dequeue
	 * f : print front->links
	 * r : print rear
	 * x : exit
	 */
	while(1){
		scanf("%c",&select);
		if(select == 'i'){
			scanf("%d",&num);
			enqueue(q,num);
		}
		else if(select == 'd'){
			dequeue(q);
		}
		else if(select == 'f')
			PrintNode(q->front);
		else if(select == 'r')
			PrintNode(q->rear);
		else if(select == 'x'){
			return 0;
		}
	}
}