/*
 * title  : Min Heap(Array)
 * func   : build heap, insert, deleteMin
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-20
 * writed by CHR

 * 가장 작은 값을 트리의 root로하는 min heap이다. array로 구현하였으며, array의 1번째 index부터 값을 채우기 시작한다.
 * BuildHeap은 따로 테스트를 넣지 않았다.
 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HEAP_SIZE 10

typedef int ElementType;
typedef struct HeapStruct *PriorityQueue;

void Insert(ElementType X,PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
void Print(PriorityQueue H);
int IsFull(PriorityQueue H);
int Power(int a,int b);
void Error(char* string);
PriorityQueue InitializePriorityQueue(int capacity);
PriorityQueue BuildHeap(PriorityQueue H);


struct HeapStruct{
	int Capacity; // max heap capacity
	int Size; // current heap size
	ElementType *Elements;
};

int main(void){
	//R의 초기화
	char select=0;
	char selectD[5];
	int num=0;

	PriorityQueue H;

	H = InitializePriorityQueue(HEAP_SIZE);
	
	//커맨드 입력
	while(1){
		scanf("%c",&select);
		if(select == 'i'){
			scanf("%d",&num);
			Insert(num,H);
		}
		
		else if(select == 'b'){
			H = BuildHeap(H);
		}

		else if(select == 'p'){
			Print(H);
		}
		
		else if(select == 'd'){
			gets(selectD);
			if(strcmp(selectD,"min"))
				DeleteMin(H);
		}
		else if(select == 'q'){
			return 0;
		}
	}
}

PriorityQueue BuildHeap(PriorityQueue H){
	int i,N;
	N = H->Size;
	printf("N : %d\ni : %d\n\n",N,N/2);
	for(i = N/2; i > 0; i--){
		int j = i;
		int temp;
		while(2*j <= H->Size){
			if(2*j+1 > H->Size || H->Elements[2*j] < H->Elements[2*j+1]){
				if(H->Elements[2*j] < H->Elements[j]){
					printf("%d and %d\n",2*j,j);
					printf("%d and %d\n",H->Elements[2*j],H->Elements[j]);
					printf("\n");
					temp = H->Elements[2*j];
					H->Elements[2*j] = H->Elements[j];
					H->Elements[j] = temp;
					j = 2*j;
				}
				else
					break;
			}
			else if(2*j+1 <= H->Size && H->Elements[2*j] > H->Elements[2*j+1]){
				if(H->Elements[2*j+1] < H->Elements[j]){
					printf("%d and %d\n",2*j+1,j);
					printf("%d and %d\n",H->Elements[2*j+1],H->Elements[j]);
					printf("\n");
					temp = H->Elements[2*j+1];
					H->Elements[2*j+1] = H->Elements[j];
					H->Elements[j] = temp;
					j = 2*j+1;
				}
				else
					break;
			}
		}
	}

	return H;
}

void Error(char* string){
	printf("%s\n",string);
}

PriorityQueue InitializePriorityQueue(int capacity){
	PriorityQueue H;
	H=(PriorityQueue)malloc(sizeof(struct HeapStruct));	
	if(H == NULL){
		Error("Out of space !!!");
		return 0;
	}

	H->Elements=(int*)malloc(sizeof(int)*(capacity+1));
	if(H->Elements == NULL){
		Error("Out of space !!!");
		return 0;
	}
	H->Capacity = capacity;
	H->Size = 0;

	return H;
}


int IsFull(PriorityQueue H){
	if(H->Capacity==H->Size)
		return 1;	
	else
		return 0;
}


void Insert(ElementType X,PriorityQueue H){
	int i;
	if (IsFull(H)){
		Error("Priority queue is full");
		return;
	}
	for( i = ++H->Size; H->Elements[ i/2 ] > X; i /= 2 )
		H->Elements[ i ] = H->Elements[ i/2 ];
	H->Elements[ i ] = X;
}

ElementType DeleteMin(PriorityQueue H){
	int i, Child;
	ElementType MinElement, LastElement;
	MinElement = H->Elements[ 1 ];
	LastElement = H->Elements[ H->Size-- ];

	for( i = 1; i*2 <= H->Size; i = Child )	{
		Child = i * 2;

		if( Child != H->Size && H->Elements[ Child + 1 ] < H->Elements[ Child ] )
			Child++;
		if( LastElement > H->Elements[ Child ] )
			H->Elements[ i ] = H->Elements[ Child ];
		else
			break;
	}
	H->Elements[ i ] = LastElement;
	return MinElement;
}

void Print(PriorityQueue H){
	int i=1,size=0,k,isIOK=0;
	size=H->Size;
	if(H->Elements[i]==NULL)
		return;
	while(size){
		int k;
		isIOK=0;
		printf("%d",H->Elements[i]);
		i++;
		size--;
		for(k=0;k<10;k++){
			if(i==Power(2,k))
				isIOK=1;
		}
		if(isIOK==1){
			printf("\n");
		}
		else{
			printf(" ");
		}
	}
	if(isIOK==0)
		printf("\n");
}

int Power(int a,int b){
	int i=a;
	if(b==0)
		return 1;
	else{
		while(b-1){
			a*=i;
			b--;
		}

		return a;
	}
}