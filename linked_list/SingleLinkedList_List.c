#include <stdio.h>
#include <malloc.h>
#include <memory.h>
 
/* �����������:
1, 2, 3, 4, 5, 6, 7, 8, 9, 10
List is not empty.
List's length is 10
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
1, 2, 3, 4, 5, 6, 7, 8, 9, 10
*/

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct Node
{
	int nData;
	struct Node* pNext;
} Node;

/*
 * ����             ����
 * CreateList       ��������
 * IsListEmpty      �ж������Ƿ�Ϊ��
 * GetListLength    �õ�����ĳ���
 * GetHead          �õ������ͷ���
 * GetTail          �õ������β���
 * GetPrior         �õ�����ǰһ�����
 * GetNext          �õ����ĺ�һ�����
 * InsertHead       ������ͷ��������
 * InsertTail       ������β��������
 * DeleteHead       ɾ������ͷ���Ľ��
 * DeleteTail       ɾ������β���Ľ��
 * ClearList        ��������еĽ��
 * DestroyList      ���������еĽ��
 * OutputList       ������������н�������
 * MakeNode         ������
 * FreeNode         �ͷŽ��
 */
Node* CreateList(const int* pData, int nLength);
BOOL IsListEmpty(const Node* pHead);
int GetListLength(const Node* pHead);
Node* GetHead(Node* pHead);
Node* GetTail(Node* pHead);
Node* GetPrior(Node* pHead, Node* pNode);
Node* GetNext(Node* pNode);
Node* InsertHead(Node* pHead, int nData);
Node* InsertTail(Node* pHead, int nData);
Node* DeleteHead(Node* pHead);
Node* DeleteTail(Node* pHead);
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
	if (IsListEmpty(pHead))
	{
		printf("List is empty.\n");
	}
	else
	{
		printf("List is not empty.\n");
	}
	printf("List's length is %d\n", GetListLength(pHead));

	pHead = InsertHead(pHead, 0);
	pHead = InsertTail(pHead, 11);
	OutputList(pHead);
	pHead = DeleteHead(pHead);
	pHead = DeleteTail(pHead);
	OutputList(pHead);

	return 0;
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

BOOL IsListEmpty(const Node* pHead)
{
	return (pHead == NULL);
}

int GetListLength(const Node* pHead)
{
	int nLength = 0;
	for (; pHead != NULL; pHead = pHead->pNext)
	{
		++nLength;
	}
	return nLength;
}

Node* GetHead(Node* pHead)
{
	return pHead;
}

Node* GetTail(Node* pHead)
{
	if (pHead != NULL)
	{
		while (pHead->pNext != NULL)
		{
			pHead = pHead->pNext;
		}
	}
	return pHead;
}

Node* GetPrior(Node* pHead, Node* pNode)
{
	if (pNode == NULL)
	{
		return NULL;
	}

	if (pHead != NULL)
	{
		while (pHead->pNext != NULL)
		{
			if (pHead->pNext == pNode)
			{
				return pHead;
			}
			pHead = pHead->pNext;
		}
	}

	return NULL;
}

Node* GetNext(Node* pNode)
{
	if (pNode != NULL)
	{
		return pNode->pNext;
	}
	return NULL;
}

Node* InsertHead(Node* pHead, int nData)
{
	Node* pNode = NULL;

	pNode = MakeNode(nData);
	pNode->pNext = pHead;
	pHead = pNode;

	return pHead;
}

Node* InsertTail(Node* pHead, int nData)
{
	Node* pTail = pHead;
	Node* pNode = NULL;

	pNode = MakeNode(nData);

	if (pTail == NULL)
	{
		pHead = pNode;
	}
	else
	{
		while (pTail->pNext != NULL)
		{
			pTail = pTail->pNext;
		}
		pTail->pNext = pNode;
	}

	return pHead;
}

Node* DeleteHead(Node* pHead)
{
	Node* pNode = pHead;
	if (pNode != NULL)
	{
		pHead = pHead->pNext;
		FreeNode(pNode);
	}

	return pHead;
}

Node* DeleteTail(Node* pHead)
{
	Node* pTail = pHead;
	Node* pNode = NULL;

	if (pTail != NULL)
	{
		if (pTail->pNext == NULL)
		{
			pNode = pTail;
			pHead = NULL;
		}
		else
		{
			while (pTail->pNext->pNext != NULL)
			{
				pTail = pTail->pNext;
			}
			pNode = pTail->pNext;
			pTail->pNext = NULL;
		}

		FreeNode(pNode);
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
