/* 
 * title  : Stack
 * func   : CreateStack, MakeEmpty, Pop, Push
 * school : Hanyang univ 
 * major  : CSE
 * date   : 2016-01-11
 * writed by CHR
 *
 * Header�� Element�� Stack�� size�� �����Ѵ�.
 * ù��° �����ʹ� Header->Next���� �����Ѵ�.
 
 * push X : ���� X�� ���ÿ� �ִ� �����̴�.
 * pop    : ���ÿ��� ���� ���� �ִ� ������ ����, �� ���� ����Ѵ�.
            ���� ���ÿ� ����ִ� ������ ���� ��쿡�� -1�� ����Ѵ�.
 * size   : ���ÿ� ����ִ� ������ ������ ����Ѵ�.
 * empty  : ������ ��������� 1, �ƴϸ� 0�� ����Ѵ�.
 * top    : ������ ���� ���� �ִ� ������ ����Ѵ�.
            ���� ���ÿ� ����ִ� ������ ���� ��쿡�� -1�� ����Ѵ�.
 * BAEKJOON ONINE JUDGE 10828�� ���̱⵵ �ϴ�.
 * 
 */

#include <iostream>
#include <string.h>
#include <stdlib.h>

#define ElementType int

using namespace std;

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node{
	ElementType Element;
	PtrToNode Next;
};

void FatalError(char* string){
	printf("%s\n",string);
}

void Error(char* string){
	printf("%s\n",string);
}

bool IsEmpty(Stack S){
	if(S->Next == NULL)
		return true;
	else
		return false;
}

void Pop(Stack S){
	if(!IsEmpty(S)){
		Stack temp = S->Next;
		printf("%d\n",temp->Element);
		S->Next = temp->Next;
		free(temp);
		S->Element--;
	}
	else{
		printf("-1\n");
	}
}

void Push(ElementType X, Stack S){
	Stack New = (Stack)malloc(sizeof(struct Node));
	if(New == NULL)
		FatalError("Out of space!!!");
	else{
		New->Element = X;
		if(IsEmpty(S))
			New->Next = NULL;
		else
			New->Next = S->Next;
		S->Next = New;
		S->Element++;
	}
}

void MakeEmpty(Stack S){
	if(S == NULL)
		Error("Must use CreateStack first");
	else{
		while(!IsEmpty(S)){
			Pop(S);
		}
	}
	S->Next = NULL;
	S->Element = 0;
}

Stack CreateStack(void){
	Stack S;
	S = (Stack)malloc(sizeof(struct Node));
	if(S == NULL)
		FatalError("Out of space !!!");
	S->Element = 0;
	S->Next = NULL;
	MakeEmpty(S);
	return S;
}

int main(void){
	int N;
	int i,j,k;
	int X;
	char string[6];

	Stack S;
	S = CreateStack();

	cin >> N;

	for(i = 0; i < N; i++){
		scanf("%s",string);
		if(strcmp(string,"push") == 0){
			cin >> X;
			Push(X,S);
		}
		else if(strcmp(string,"pop") == 0){
			Pop(S);
		}
		else if(strcmp(string,"size") == 0){
			cout << S->Element << endl;
		}
		else if(strcmp(string,"empty") == 0){
			if(IsEmpty(S))
				cout << 1 << endl;
			else
				cout << 0 << endl;
		}
		else if(strcmp(string,"top") == 0){
			if(IsEmpty(S)){
				cout << -1 << endl;
			}
			else
				cout << S->Next->Element << endl;
		}

	}

	return 0;
}
