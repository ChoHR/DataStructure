/*
 * title  : Circular Array Queue
 * func   : Print, Enqueue, Dequeue
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-11
 * writed by CHR
 
 * MAX_QUEUE_SIZE�� QUEUE�� capacity�̴�.

 * Succ(Value, Queue)�� Queue�� Circular�� ������ش�.
     Array�� ���� 0��° index�� �������ִ� �Լ��̴�.
     Circular�̱� ������ Front�� Rear�� ���������� ���� 0�� �ʿ䰡 ����.
     Front�� Rear���� 1 ũ�� �ʱ�ȭ�Ͽ��µ�, �̴� ���û����̴�.
     Succ �Լ��� ��ġ�� ���������ν� �� �� ���� �ʱ�ȭ�Ͽ� �� ���� �ִ�.
 */

#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define MAX_QUEUE_SIZE 10

struct QueueRecord;
typedef struct QueueRecord *Queue;

struct QueueRecord{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;
};

void Error(char* string){
	printf("%s\n",string);
}

bool IsFull(Queue Q){
	return Q->Size == Q->Capacity;
}

bool IsEmpty(Queue Q){
	return Q->Size == 0;
}


void MakeEmpty(Queue Q){
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}

Queue CreateQueue(){
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QueueRecord));
	if(Q == NULL)
		Error("Out of space !!!");
	MakeEmpty(Q);
	Q->Capacity = MAX_QUEUE_SIZE;
	Q->Array = (ElementType*)malloc(sizeof(ElementType)*MAX_QUEUE_SIZE);
	if(Q->Array == NULL)
		Error("Out of space !!!");
	return Q;
}


/*
 * Circular Queue�� �����ϱ����� �Լ�
 */
static int Succ(int Value, Queue Q){
	if(++Value == Q->Capacity)
		Value = 0;
	return Value;
}

void Enqueue(ElementType X, Queue Q){
	if(IsFull(Q))
		Error("Full queue");
	else{
		Q->Size++;
		Q->Rear = Succ(Q->Rear,Q);
		Q->Array[Q->Rear] = X;
	}
}

void Dequeue(Queue Q){
	if(IsEmpty(Q))
		Error("Empty queue");
	else{
		Q->Size--;
		Q->Array[Q->Front] = 0;
		Q->Front = Succ(Q->Front,Q);
	}
}

void PrintQueue(Queue Q){
	int cur;

	cur = Q->Front;
	
	if(!IsEmpty(Q)){
	while(cur != Q->Rear){
		printf("%d ->",Q->Array[cur]);
		cur = Succ(cur,Q);
	}
	printf("%d\n",Q->Array[cur]);
	}
	else
		Error("Queue is Empty");
}

int main(void){
	int i,j;
	char select;
	int num;
	Queue Q = CreateQueue();
	
	//i,d �� ����
	while(1){
		scanf("%c",&select);
		if(select == 'i'){
			scanf("%d",&num);
			Enqueue(num,Q);
		}
		else if(select == 'd'){
			Dequeue(Q);
		}
		else if(select == 'p'){
			PrintQueue(Q);
		}
		else if(select == 'x'){
			return 0;
		}
	}

	return 0;
}