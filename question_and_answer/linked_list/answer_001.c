#include <stdio.h>
#include <malloc.h>
#include <memory.h>
 
/* 程序输出如下:
1, 2, 3, 4, 5, 6, 7, 8, 9, 10
10, 9, 8, 7, 6, 5, 4, 3, 2, 1
*/

typedef struct Node
{
	int nData;
	struct Node* pNext;
} Node;

/*
 * 功能: 逆置单向链表。
 * 名称: ReverseList。
 * 参数: Node* pHead，指向链表头结点的指针。
 * 返回值: Node*，指向链表头结点的指针。
 */
Node* ReverseList(Node* pHead);
Node* CreateList(const int* pData, int nLength);
Node* ClearList(Node* pHead);
Node* DestroyList(Node* pHead);
void OutputList(const Node* pHead);
Node* MakeNode(int nData);
void FreeNode(Node* pNode);

int main()
{
	int arrData[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	Node* pHead = NULL;

	pHead = CreateList(arrData, sizeof(arrData) / sizeof(int));
	OutputList(pHead);

	pHead = ReverseList(pHead);
	OutputList(pHead);

	pHead = DestroyList(pHead);

	return 0;
}

Node* ReverseList(Node* pHead)
{
	Node* p = pHead;
	Node* q = NULL;

	if (pHead != NULL)
	{
		p = pHead->pNext;
		pHead->pNext = NULL;
		while (p != NULL)
		{
			q = p->pNext;
			p->pNext = pHead;
			pHead = p;
			p = q;
		}
	}

	return pHead;
}

Node* CreateList(const int* pData, int nLength)
{
	Node* pHead = NULL;
	Node* pTail = NULL;
	int i = 0;

	for (; i < nLength; ++i)
	{
		if (pHead == NULL)
		{
			pHead = MakeNode(pData[i]);
			pTail = pHead;
		}
		else
		{
			pTail->pNext = MakeNode(pData[i]);
			pTail = pTail->pNext;
		}
	}

	return pHead;
}

Node* ClearList(Node* pHead)
{
	Node* pNode = NULL;

	while (pHead != NULL)
	{
		pNode = pHead->pNext;
		FreeNode(pHead);
		pHead = pNode;
	}
	pHead = NULL;

	return pHead;
}

Node* DestroyList(Node* pHead)
{
	return ClearList(pHead);
}

void OutputList(const Node* pHead)
{
	for (; pHead != NULL; pHead = pHead->pNext)
	{
		printf("%d", pHead->nData);
		if (pHead->pNext == NULL)
		{
			printf("\n");
		}
		else
		{
			printf(", ");
		}
	}
}

Node* MakeNode(int nData)
{
	Node* pNode = NULL;

	pNode = (Node*)malloc(sizeof(Node));
	pNode->nData = nData;
	pNode->pNext = NULL;

	return pNode;
}

void FreeNode(Node* pNode)
{
	if (pNode != NULL)
	{
		free(pNode);
	}
}
