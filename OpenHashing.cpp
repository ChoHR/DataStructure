/*
 * title  : Open Hashing(Separate Chaning)
 * func   : search, insert, delete, print, quit
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-13
 * writed by CHR

 * Hash()는 매우 간단한 모듈러 연산을 사용하였다. higher Scattering을 원한다면, Hash()식을 바꾸어주면 된다.
 * Hash()에서 Key는 int를 사용하고있다. char* 와 같은 string을 사용할 경우는 이를 고려해주어야 한다.
 * 1. typedef int ElementType을 바꾸어준다.
 * 2. Find()에서 주석을 단 부분을 바꾸어준다. strcmp()를 사용할 필요가 있다.
 * 3. Hash()를 char* 형식에 맞게 바꾸어 주어야 한다.

 * Retrieve()는 미구현 상태이다.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE 30
#define MIN_TABLE_SIZE 2
#define TABLESIZE 10

typedef unsigned int Index;
typedef struct ListNode *Position;
typedef Position List;
typedef int ElementType;
typedef struct HashTbl *HashTable;


struct ListNode{
	ElementType Element;
	Position Next;
};

struct HashTbl{
	int TableSize;
	List* TheLists;
};

void Error(char* string){
	printf("%s\n",string);
}

int Hash(ElementType Key, int TableSize){
	unsigned int HashVal = 0;
	HashVal = Key;
	return HashVal%TableSize;
}

HashTable InitializeTable(int TableSize){
	int i;
	HashTable H;

	if(TableSize < MIN_TABLE_SIZE){
		Error("Table size too small");
		return NULL;
	}

	H =	(HashTable)malloc(sizeof(struct HashTbl));
	if(H == NULL){
		Error("Out of space !!!");
		return NULL;
	}
	H->TableSize = TableSize;
	H->TheLists = (List*)malloc(sizeof(List)*TableSize);
	if(H->TheLists == NULL){
		Error("Out of space !!!");
		return NULL;
	}

	for(i = 0; i < TableSize; i++){
		H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
		if(H->TheLists[i] == NULL){
			Error("Out of space !!!");
			return NULL;
		}
		H->TheLists[i]->Next = NULL;
	}

	return H;
}

void DestroyTable(HashTable H){
	int TableSize = H->TableSize;
	Position P,temp;
	int i;

	for(i = 0; i < TableSize; i++){
		P = H->TheLists[i];
		if(P != NULL){
			while(P->Next != NULL){
				temp = P;
				P = P->Next;
				free(temp);
			}
			free(P);
		}
	}
	free(H->TheLists);
	free(H);
}

ElementType Retrieve(Position P){
	return 0;
}

Position Find(ElementType Key, HashTable H){
	Position P;
	List L;

	L = H->TheLists[Hash(Key,H->TableSize)];
	P = L->Next;

	// if ElementType is string, we have to use strcmp() 
	while(P!=NULL && P->Element!=Key)
		P = P->Next;
	return P;
}

void Insert(ElementType Key, HashTable H){
	Position pos, newCell;
	List L;

	pos = Find(Key, H);

	if(pos == NULL){
		newCell = (Position)malloc(sizeof(struct ListNode));
		if(newCell == NULL){
			Error("Out of space !!!");
			return;
		}
		L = H->TheLists[Hash(Key,H->TableSize)];
		newCell->Next = L->Next;
		newCell->Element = Key;
		L->Next = newCell;
	}
	else{
		Error("already exist");
	}
}

Position FindPrevious(ElementType Key,HashTable H){
	Position P;
	List L;

	L = H->TheLists[Hash(Key,H->TableSize)];
	P = L;

	// if ElementType is string, we have to use strcmp() 
	while(P->Next != NULL && P->Next->Element!=Key)
		P = P->Next;
	return P;
}

void Delete(ElementType Key, HashTable H){
	Position P,TmpCell;

	P = FindPrevious(Key,H);
	if(P->Next != NULL){
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
	else{
		free(P->Next);
		P->Next = NULL;
	}
}

void PrintList(List list){
	List temp;

	temp = list->Next;
	
	if(temp != NULL){		
		while(temp->Next != NULL){
			printf("%d -> ",temp->Element);
			temp = temp->Next;
		}	
		printf("%d\n",temp->Element);
	}
	else
		printf("NULL\n");
}

void PrintHash(HashTable H){
	int TableSize = H->TableSize;
	List list;
	int i;

	for( i = 0; i < TableSize; i++){
		list = H->TheLists[i];
		printf("index %d : ",i);
		if(list != NULL){
			PrintList(list);
		}
	}
}

int main(void){
	char select;
	int num;

	HashTable H;

	H = InitializeTable(TABLESIZE);

	
	//i,d 중 선택
	while(1){
		scanf("%c",&select);
		if(select == 'i'){
			scanf("%d",&num);
			Insert(num,H);
		}
		else if(select == 'd'){
			scanf("%d",&num);
			Delete(num,H);
		}
		else if(select == 'p'){
			PrintHash(H);
		}
		else if(select == 'x'){
			return 0;
		}
	}

	return 0;
}