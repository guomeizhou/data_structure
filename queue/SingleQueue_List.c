#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * �������(��ʽ)
 */

/* �����������:
��Ӻ�Ķ��У�12, 3, 8, 34, 6, 9, 56, 78, 4, 90
���г��ȣ�10
����Ϊ�ǿ�
�������ݣ�12
���Ӻ�Ķ��У�3, 8, 34, 6, 9, 56, 78, 4, 90
�������ݣ�3
���Ӻ�Ķ��У�8, 34, 6, 9, 56, 78, 4, 90
*/

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct QueueNode
{
    int nData;
    struct QueueNode* pNext;
} QueueNode;

typedef struct
{
    QueueNode* pFront; /* ��ͷָ�� */
    QueueNode* pRear;  /* ��βָ�� */
    int nLength; /* ���еĳ��� */
} Queue;

typedef void (*OutputQueueType)(int, BOOL);

/*
 * ����             ����
 * InitQueue        ��ʼ������
 * IsQueueEmpty     �ж϶����Ƿ�Ϊ��
 * GetQueueLength   �õ����еĳ���
 * GetQueueHead     �õ����е�ͷ���
 * GetQueueTail     �õ����е�β���
 * EnQueue          ���
 * DeQueue          ����
 * ClearQueue       ��������еĽ��
 * DestroyQueue     ���ٶ����еĽ��
 * TraverseQueue    �������������еĽ��
 * OutputQueue      ���������ĳ��������
 * MakeNode         ������
 * FreeNode         �ͷŽ��
 */
BOOL InitQueue(Queue* pQueue);
BOOL IsQueueEmpty(const Queue* pQueue);
int GetQueueLength(const Queue* pQueue);
QueueNode* GetQueueHead(Queue* pQueue);
QueueNode* GetQueueTail(Queue* pQueue);
BOOL EnQueue(Queue* pQueue, int nData);
BOOL DeQueue(Queue* pQueue, int* pData);
void ClearQueue(Queue* pQueue);
void DestroyQueue(Queue* pQueue);
void TraverseQueue(const Queue* pQueue, OutputQueueType pFunc);
void OutputQueue(int nData, BOOL bLast);
QueueNode* MakeNode(int nData);
void FreeNode(QueueNode* pNode);

int main()
{
    Queue q;
    int nData = 0;
    int nLength = 0;
    BOOL bEmpty = FALSE;

    InitQueue(&q);
    EnQueue(&q, 12);
    EnQueue(&q, 3);
    EnQueue(&q, 8);
    EnQueue(&q, 34);
    EnQueue(&q, 6);
    EnQueue(&q, 9);
    EnQueue(&q, 56);
    EnQueue(&q, 78);
    EnQueue(&q, 4);
    EnQueue(&q, 90);
    printf("��Ӻ�Ķ��У�");
    TraverseQueue(&q, OutputQueue);

    nLength = GetQueueLength(&q);
    printf("���г��ȣ�%d\n", nLength);

    bEmpty = IsQueueEmpty(&q);
    printf("����Ϊ%s\n", bEmpty ? "��" : "�ǿ�");

    DeQueue(&q, &nData);
    printf("�������ݣ�%d\n", nData);
    printf("���Ӻ�Ķ��У�");
    TraverseQueue(&q, OutputQueue);

    DeQueue(&q, &nData);
    printf("�������ݣ�%d\n", nData);
    printf("���Ӻ�Ķ��У�");
    TraverseQueue(&q, OutputQueue);

    DestroyQueue(&q);

    return 0;
}

BOOL InitQueue(Queue* pQueue)
{
    if (pQueue == NULL)
    {
        return FALSE;
    }

    pQueue->pFront = NULL;
    pQueue->pRear = NULL;
    pQueue->nLength = 0;

    return TRUE;
}

BOOL IsQueueEmpty(const Queue* pQueue)
{
    if (pQueue->nLength == 0)
    {
        return TRUE;
    }

    return FALSE;
}

int GetQueueLength(const Queue* pQueue)
{
    return pQueue->nLength;
}

QueueNode* GetQueueHead(Queue* pQueue)
{
    return pQueue->pFront;
}

QueueNode* GetQueueTail(Queue* pQueue)
{
    return pQueue->pRear;
}

BOOL EnQueue(Queue* pQueue, int nData)
{
    QueueNode* pNode = NULL;
    
    pNode = MakeNode(nData);
    if (pNode == NULL)
    {
        return FALSE;
    }

    if (pQueue->nLength == 0)
    {
        pQueue->pFront = pNode;
        pQueue->pRear = pQueue->pFront;
        pQueue->nLength = 1;
    }
    else
    {
        pQueue->pRear->pNext = pNode;
        pQueue->pRear = pNode;
        ++(pQueue->nLength);
    }

    return TRUE;
}

BOOL DeQueue(Queue* pQueue, int* pData)
{
    QueueNode* pNode = NULL;

    if (pQueue->nLength == 0)
    {
        return FALSE;
    }
    else if (pQueue->nLength == 1)
    {
        pNode = pQueue->pFront;
        pQueue->pFront = NULL;
        pQueue->pRear = NULL;
        pQueue->nLength = 0;
    }
    else
    {
        pNode = pQueue->pFront;
        pQueue->pFront = pNode->pNext;
        --(pQueue->nLength);
    }

    *pData = pNode->nData;
    free(pNode);
    pNode = NULL;

    return TRUE;
}

void ClearQueue(Queue* pQueue)
{
    QueueNode* pNode = NULL;
    QueueNode* pDeleteNode = NULL;

    pNode = pQueue->pFront;
    while (pNode != NULL)
    {
        pDeleteNode = pNode;
        pNode = pNode->pNext;
        free(pDeleteNode);
    }

    pQueue->pFront = NULL;
    pQueue->pRear = NULL;
    pQueue->nLength = 0;
}

void DestroyQueue(Queue* pQueue)
{
    ClearQueue(pQueue);
}

void TraverseQueue(const Queue* pQueue, OutputQueueType pFunc)
{
    QueueNode* pNode = pQueue->pFront;

    while (pNode != NULL)
    {
        if (pNode->pNext == NULL)
        {
            pFunc(pNode->nData, TRUE);
        }
        else
        {
            pFunc(pNode->nData, FALSE);
        }

        pNode = pNode->pNext;
    }
}

void OutputQueue(int nData, BOOL bLast)
{
    printf("%d", nData);

    if (bLast)
    {
        printf("\n");
    }
    else
    {
        printf(", ");
    }
}

QueueNode* MakeNode(int nData)
{
    QueueNode* pNode = NULL;

    pNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (pNode == NULL)
    {
        return NULL;
    }

    pNode->nData = nData;
    pNode->pNext = NULL;

    return pNode;
}

void FreeNode(QueueNode* pNode)
{
    if (pNode != NULL)
    {
        free(pNode);
    }
}
