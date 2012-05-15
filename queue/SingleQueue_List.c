#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * 单向队列(链式)
 */

/* 程序输出如下:
入队后的队列：12, 3, 8, 34, 6, 9, 56, 78, 4, 90
队列长度：10
队列为非空
出队数据：12
出队后的队列：3, 8, 34, 6, 9, 56, 78, 4, 90
出队数据：3
出队后的队列：8, 34, 6, 9, 56, 78, 4, 90
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
    QueueNode* pFront; /* 队头指针 */
    QueueNode* pRear;  /* 队尾指针 */
    int nLength; /* 队列的长度 */
} Queue;

typedef void (*OutputQueueType)(int, BOOL);

/*
 * 名称             功能
 * InitQueue        初始化队列
 * IsQueueEmpty     判断队列是否为空
 * GetQueueLength   得到队列的长度
 * GetQueueHead     得到队列的头结点
 * GetQueueTail     得到队列的尾结点
 * EnQueue          入队
 * DeQueue          出队
 * ClearQueue       清除队列中的结点
 * DestroyQueue     销毁队列中的结点
 * TraverseQueue    遍历队列中所有的结点
 * OutputQueue      输出队列中某结点的数据
 * MakeNode         分配结点
 * FreeNode         释放结点
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
    printf("入队后的队列：");
    TraverseQueue(&q, OutputQueue);

    nLength = GetQueueLength(&q);
    printf("队列长度：%d\n", nLength);

    bEmpty = IsQueueEmpty(&q);
    printf("队列为%s\n", bEmpty ? "空" : "非空");

    DeQueue(&q, &nData);
    printf("出队数据：%d\n", nData);
    printf("出队后的队列：");
    TraverseQueue(&q, OutputQueue);

    DeQueue(&q, &nData);
    printf("出队数据：%d\n", nData);
    printf("出队后的队列：");
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
