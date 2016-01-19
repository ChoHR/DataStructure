/*
 * title  : Linear Hashing(Open Hashing)
 * func   : find, insert, delete, print, quit, rehash
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-19
 * writed by CHR

 * Hash()�� �ſ� ������ ��ⷯ ������ ����Ͽ���. better Scattering�� ���Ѵٸ�, Hash()���� �ٲپ��ָ� �ȴ�.
 * collision�� �Ͼ ���, linear�ϰ� probe�Ѵ�.
 * Hash()���� Key�� char*�� ����ϰ��ִ�. int �� ���� key�� ����� ���� �̸� ������־�� �Ѵ�.
 * 1. #define ElementType char*�� #define ElementType int�� �ٲپ��ش�.
 * 2. strcmp()�� Key���� ���� ������ ==�� ����Ͽ� ���ϴ� ������ �ٲ۴�.
 * 3. Hash()�� int ���Ŀ� �°� �ٲپ� �־�� �Ѵ�.
 * Rehashing�� MaxTableSize�� �Ѿ �� ����. HashTable Size�� 3/4 �̻��� ������ �� ���, HashTable Size�� �� ��� ���Ҵ��Ѵ�.

 * Retrieve()�� �̱��� �����̴�.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE 4
#define MinTableSize 4
#define MaxTableSize 10

#define ElementType char*

typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable( HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
void Delete(ElementType Key, HashTable H);
ElementType Retrieve(Position P, HashTable H);
HashTable Rehash(HashTable H);
unsigned Hash(char *Key,int HashSize);
void PrintTable(HashTable H);

enum KindOfEntry{Legitimate, Empty, Deleted};

struct HashEntry{
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl{
	int TableSize;
	int Counter;
	Cell *TheCells;
};

void Error(char* string){
	printf("%s\n",string);
}
void FatalError(char* string){
	printf("%s\n",string);
}

int NextPrime(int TableSize){
	int size;

	/*
	 * TableSize���� ũ�� s^n�� �ָ� ������ �Ҽ� ã��.
	 */
	size = TableSize;
	printf("table size is %d\n",size);

	return size;
}

HashTable InitializeTable(int TableSize){
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(struct HashTbl));
	if(H == NULL)
		FatalError("Out of space !!!");

	H->TableSize = NextPrime(TableSize);

	H->TheCells = (Cell*)malloc(sizeof(Cell) * H->TableSize);
	H->Counter = 0;
	if(H->TheCells == NULL){
		FatalError("Out of space!!!");
	}

	for(i = 0; i < H->TableSize; i++){
		H->TheCells[i].Element = (char*)malloc(sizeof(char)*20);
		H->TheCells[i].Info = Empty;
	}

	return H;
}

Position Find(ElementType Key, HashTable H){
	Position CurrentPos;
	int CollisionNum;

	CollisionNum = 0;
	CurrentPos = Hash(Key, H->TableSize);
	while(H->TheCells[CurrentPos].Info != Empty &&
		strcmp(H->TheCells[CurrentPos].Element, Key) != 0){
			// linear hashing
			CurrentPos = (CurrentPos+1)%H->TableSize;
	}
	return CurrentPos;
}


// rehash the hashtable, tablesize is double.
HashTable ReHash(HashTable old_H){
	HashTable new_H = (HashTable)malloc(sizeof(struct HashTbl));
	int i;
		
	new_H = (HashTable)malloc(sizeof(struct HashTbl));
	if(new_H == NULL)
		FatalError("Out of space !!!");

	new_H->TableSize = NextPrime(old_H->TableSize*2);
	
	if(new_H->TableSize > MaxTableSize){
		new_H->TableSize = MaxTableSize;
		printf("tablesize is over MaxTableSize\n");
	}

	new_H->TheCells = (Cell*)malloc(sizeof(Cell) * new_H->TableSize);
	if(new_H->TheCells == NULL){
		FatalError("Out of space!!!");
	}
	new_H->Counter = 0;
	
	for(i = 0; i < new_H->TableSize; i++){
		new_H->TheCells[i].Element = (char*)malloc(sizeof(char)*20);
		new_H->TheCells[i].Info = Empty;
	}

	for(i = 0; i < old_H->TableSize; i++){
		if(old_H->TheCells[i].Info == Legitimate)
			Insert(old_H->TheCells[i].Element,new_H);
	}
	
	free(old_H);

	return new_H;
}

void Insert(ElementType Key, HashTable H){
	Position Pos;

	if(H->Counter == H->TableSize){
		printf("Table is full\n");
		return;
	}

	Pos = Find(Key, H);
	if(H->TheCells[Pos].Info == Legitimate){
		printf("\"%s\" already exist in the Hash\n",Key);
	}
	if(H->TheCells[Pos].Info != Legitimate){
		H->TheCells[Pos].Info = Legitimate;		
		strcpy(H->TheCells[Pos].Element,Key);
		H->Counter++;
	}
}

void Delete(ElementType Key, HashTable H){
	Position Pos;

	Pos = Find(Key, H);
	if(H->TheCells[Pos].Info == Legitimate){
		H->TheCells[Pos].Info = Deleted;
		H->Counter--;
	}
}

int main(void){
	char select;
	char string[20];

	HashTable H = InitializeTable(HASH_SIZE);
	
	//i,f,p,q �� ����
	while(1){
		scanf("%c",&select);
		if(select == 'i'){
			scanf("%s",string);
			Insert(string,H);
			
			if(H->Counter*4 >= 3*H->TableSize){
				printf("There are Contents over 3/4 of tablesize\n");
				if(H->TableSize > MaxTableSize)
					printf("TableSize is over the MaxTableSize\n");
				else
					H = ReHash(H);				
			}
		}
		
		else if(select == 'd'){
			scanf("%s",string);
			Delete(string,H);
		}
		else if(select == 'p'){
			PrintTable(H);
		}
	
		else if(select == 'q'){
			return 0;
		}
	}
	return 0;
}


unsigned int Hash(ElementType Key, int TableSize){
	unsigned int HashVal = 0;

	for( HashVal = 0; *Key != '\0'; Key++)
		HashVal = *Key + 31 * HashVal;
	return HashVal%TableSize;
}

//hash�� ����� ���� ���. �ϼ�
void PrintTable(HashTable H){
	int i;
	printf("Index\n");
	for(i=0;i<H->TableSize;i++){
		if(H->TheCells[i].Info==Legitimate)
			printf("%s\n",H->TheCells[i].Element);
		else
			printf("empty\n");
	}
}