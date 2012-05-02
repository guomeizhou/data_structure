#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * �����
 * parent��ͬ�����еĺ��ӽ��ʹ��˫������ṹ���д洢��
 */

/* �����������Ľṹ���£�
 * 66
 * |
 * ----------------------
 * |               |    |
 * 33              99   44
 * |                    |
 * -------------        |
 * |   |   |   |        |
 * 11  77  22  55       100
 *     |
 *     88
 */

/* �����������:
���������
66 33 11 77 88 22 55 99 44 100
���������
11 88 77 22 55 33 99 100 44 66
���������

���Ƿǿյ�
���������4
-----------------------------------------------------
��ӽ��111�ɹ�
���������
66 33 11 77 88 22 55 111 99 44 100
���������
11 88 77 22 55 111 33 99 100 44 66
���������

���Ƿǿյ�
���������4
-----------------------------------------------------
ɾ�����111�ɹ�
���������
66 33 11 77 88 22 55 99 44 100
���������
11 88 77 22 55 33 99 100 44 66
���������

���Ƿǿյ�
���������4
*/

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define NO_POS -1

typedef struct TreeNode
{
    int nData;
    struct TreeNode* pParent;
    struct TreeNode* pChild;
    struct TreeNode* pPrevSibling;
    struct TreeNode* pNextSibling;
} TreeNode;

typedef struct ParentChildSiblingInfo
{
    int nData;
    // NO_POS: ��ʾû��parent
    int nParentPos;
    // NO_POS: ��ʾû��child
    int nChildPos;
    int nPrevSiblingPos;
    int nNextSibling;
} ParentChildSiblingInfo;

typedef void (*OutputFuncType)(int nData);

/*
 * ����: ��������
 * ����: CreateTree��
 * ����: const ParentChildSiblingInfo* pData��ָ��һ����Ÿ�ĸ�����ֵܹ�ϵ��Ϣ�����顣
 * ����: int nLength��������ĳ��ȡ�
 * ����ֵ: TreeNode*��ָ������ͷ����ָ�롣
 */
TreeNode* CreateTree(const ParentChildSiblingInfo* pData, int nLength);
/*
 * ����: ��������
 * ����: DestroyTree��
 * ����: const TreeNode* pRoot��ָ�����ĸ���㡣
 * ����ֵ: void��
 */
void DestroyTree(TreeNode** ppRoot);
/*
 * ����: ������ӽ�㡣
 * ����: AddTreeNode��
 * ����: TreeNode** ppRoot��ָ�����ĸ����ĵ�ַ��
 * ����: TreeNode* pParent��ָ�򸸽�㣬��������ӽ��ĸ���㡣
 * ����: int nData������ӽ�������ֵ��
 * ����ֵ: TreeNode*��ָ������ӵĽ�㡣
 */
TreeNode* AddTreeNode(TreeNode** ppRoot, TreeNode* pParent, int nData);
/*
 * ����: ɾ�����е�ĳ����㡣
         ����ý�����ӽ�㣬��Ҳ�ᱻɾ����
 * ����: DeleteTreeNode��
 * ����: TreeNode** ppRoot��ָ�����ĸ����ĵ�ַ��
 * ����: TreeNode* pDeleteNode��ָ��ɾ���Ľ�㡣
 * ����ֵ: BOOL��TRUE��ʾɾ���ɹ���FALSE��ʾɾ��ʧ�ܡ�
 */
BOOL DeleteTreeNode(TreeNode** ppRoot, TreeNode* pDeleteNode);
/*
 * ����: �ж����Ƿ�Ϊ�ա�
 * ����: IsTreeEmpty��
 * ����: const TreeNode* pRoot��ָ�����ĸ���㡣
 * ����ֵ: BOOL��TRUE��ʾ�գ�FALSE��ʾ�ǿա�
 */
BOOL IsTreeEmpty(const TreeNode* pRoot);
/*
 * ����: �õ�������ȡ�
 * ����: GetTreeDepth��
 * ����: const TreeNode* pRoot��ָ�����ĸ���㡣
 * ����ֵ: int����ʾ������ȡ�
 */
int GetTreeDepth(const TreeNode* pRoot);
/*
 * ����: �����������
         �ȱ�������㣬������ӽ�㡣
 * ����: PreOrderTraverseTree��
 * ����: const TreeNode* pRoot��ָ�����ĸ���㡣
 * ����: OutputFuncType pFunc��ָ��������н�㺯����ָ�롣
 * ����ֵ: void��
 */
void PreOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc);
/*
 * ����: �����������
         �ȱ����ӽ�㣬���������㡣
 * ����: PostOrderTraverseTree��
 * ����: const TreeNode* pRoot��ָ�����ĸ���㡣
 * ����: OutputFuncType pFunc��ָ��������н�㺯����ָ�롣
 * ����ֵ: void��
 */
void PostOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc);
/*
 * ����: �����������
         �ȱ�������㣬����������ӽ�㡣
 * ����: LevelOrderTraverseTree��
 * ����: const TreeNode* pRoot��ָ�����ĸ���㡣
 * ����: OutputFuncType pFunc��ָ��������н�㺯����ָ�롣
 * ����ֵ: void��
 */
void LevelOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc);
/*
 * ����: ���������е����ݡ�
 * ����: OutputTreeNodeData��
 * ����: int nData��������е����ݡ�
 * ����ֵ: void��
 */
void OutputTreeNodeData(int nData);
TreeNode** MakeTreeNodeList(int nLength);
void FreeTreeNodeList(TreeNode** ppNodeList);
TreeNode* MakeTreeNode();
void FreeTreeNode(TreeNode* pNode);

int main()
{
    ParentChildSiblingInfo arrData[10] =
    {
        {66, NO_POS, 1, 0, 0},
        {33, 0, 4, 3, 2},
        {99, 0, NO_POS, 1, 3},
        {44, 0, 8, 2, 1},
        {11, 1, NO_POS, 7, 5},
        {77, 1, 9, 4, 6},
        {22, 1, NO_POS, 5, 7},
        {55, 1, NO_POS, 6, 4},
        {100, 3, NO_POS, 8, 8},
        {88, 5, NO_POS, 9, 9}
    };
    TreeNode* pRoot = NULL;
    TreeNode* pParent = NULL;
    TreeNode* pNode = NULL;
    int nNodeData = 111;
    BOOL bResult = FALSE;
    int nTreeDepth = 0;
    
    pRoot = CreateTree(arrData, sizeof(arrData) / sizeof(arrData[0]));
    printf("���������\n");
    PreOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("���������\n");
    PostOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("���������\n");
    LevelOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");

    bResult = IsTreeEmpty(pRoot);
    printf("����%s��\n", bResult ? "��" : "�ǿ�");

    nTreeDepth = GetTreeDepth(pRoot);
    printf("���������%d\n", nTreeDepth);

    printf("-----------------------------------------------------\n");

    pParent = pRoot->pChild;
    pNode = AddTreeNode(&pRoot, pParent, nNodeData);
    printf("��ӽ��%d%s\n", nNodeData, (pNode != NULL) ? "�ɹ�" : "ʧ��");
    printf("���������\n");
    PreOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("���������\n");
    PostOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("���������\n");
    LevelOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");

    bResult = IsTreeEmpty(pRoot);
    printf("����%s��\n", bResult ? "��" : "�ǿ�");

    nTreeDepth = GetTreeDepth(pRoot);
    printf("���������%d\n", nTreeDepth);

    printf("-----------------------------------------------------\n");

    bResult = DeleteTreeNode(&pRoot, pNode);
    pNode = NULL;
    printf("ɾ�����%d%s\n", nNodeData, bResult ? "�ɹ�" : "ʧ��");
    
    printf("���������\n");
    PreOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("���������\n");
    PostOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("���������\n");
    LevelOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");

    bResult = IsTreeEmpty(pRoot);
    printf("����%s��\n", bResult ? "��" : "�ǿ�");

    nTreeDepth = GetTreeDepth(pRoot);
    printf("���������%d\n", nTreeDepth);

    DestroyTree(&pRoot);
    
    return 0;
}

TreeNode* CreateTree(const ParentChildSiblingInfo* pData, int nLength)
{
    TreeNode** ppNodeList = NULL;
    TreeNode* pRootNode = NULL;
    TreeNode* pTempNode = NULL;
    int i = 0;
    int nTempParentPos = 0;
    int nTempChildPos = 0;
    int nTempPrevSiblingPos = 0;
    int nTempNextSiblingPos = 0;
    
    ppNodeList = MakeTreeNodeList(nLength);
    
    for (; i < nLength; ++i)
    {
        if (pData[i].nParentPos == NO_POS)
        {
            pRootNode = ppNodeList[i];
            nTempChildPos = pData[i].nChildPos;
            
            pRootNode->nData = pData[i].nData;
            pRootNode->pParent = NULL;
            pRootNode->pChild = ppNodeList[nTempChildPos];
            pRootNode->pPrevSibling = pRootNode;
            pRootNode->pNextSibling = pRootNode;
        }
        else
        {
            pTempNode = ppNodeList[i];
            nTempParentPos = pData[i].nParentPos;
            nTempChildPos = pData[i].nChildPos;
            nTempPrevSiblingPos = pData[i].nPrevSiblingPos;
            nTempNextSiblingPos = pData[i].nNextSibling;
            
            pTempNode->nData = pData[i].nData;
            pTempNode->pParent = ppNodeList[nTempParentPos];
            if (nTempChildPos == NO_POS)
            {
                pTempNode->pChild = NULL;
            }
            else
            {
                pTempNode->pChild = ppNodeList[nTempChildPos];
            }
            pTempNode->pPrevSibling = ppNodeList[nTempPrevSiblingPos];
            pTempNode->pNextSibling = ppNodeList[nTempNextSiblingPos];
        }
    }
    
    FreeTreeNodeList(ppNodeList);
    ppNodeList = NULL;
    
    return pRootNode;
}

void DestroyTree(TreeNode** ppRoot)
{
    TreeNode* pNode = NULL;
    TreeNode* pDestroyNode = NULL;
    
    if (*ppRoot != NULL)
    {
        pNode = *ppRoot;
        do
        {
            if (pNode->pChild != NULL)
            {
                DestroyTree(&pNode->pChild);
            }
            pDestroyNode = pNode;
            pNode = pNode->pNextSibling;
            
            FreeTreeNode(pDestroyNode);
        } while (pNode != (*ppRoot));

        *ppRoot = NULL;
    }
}

TreeNode* AddTreeNode(TreeNode** ppRoot, TreeNode* pParent, int nData)
{
    TreeNode* pRoot = NULL;
    TreeNode* pNode = NULL;
    
    if (ppRoot == NULL)
    {
        return NULL;
    }
    pRoot = *ppRoot;
    
    pNode = MakeTreeNode();
    pNode->nData = nData;
    pNode->pParent = pParent;
    pNode->pChild = NULL;
    pNode->pPrevSibling = pNode;
    pNode->pNextSibling = pNode;
    
    if (pRoot == NULL)
    {
        *ppRoot = pNode;
    }
    else
    {
        if (pParent == NULL)
        {
            // unimpl
            FreeTreeNode(pNode);
            return NULL;
            /*pNode->pPrevSibling = pRoot->pPrevSibling;
            pNode->pNextSibling = pRoot;
            pRoot->pPrevSibling->pNextSibling = pNode;
            pRoot->pPrevSibling = pNode;*/
        }
        else
        {
            if (pParent->pChild == NULL)
            {
                pParent->pChild = pNode;
            }
            else
            {
                // ��pNode����pParent�����к��ӽ���ĩβ�����еĺ��ӽ��ʹ��˫������ṹ���д洢��
                pNode->pPrevSibling = pParent->pChild->pPrevSibling;
                pNode->pNextSibling = pParent->pChild;
                pParent->pChild->pPrevSibling->pNextSibling = pNode;
                pParent->pChild->pPrevSibling = pNode;
            }
        }
    }
    
    return pNode;
}

BOOL DeleteTreeNode(TreeNode** ppRoot, TreeNode* pDeleteNode)
{
    if (*ppRoot == NULL || pDeleteNode == NULL)
    {
        return FALSE;
    }
    else if (*ppRoot == pDeleteNode)
    {
        DestroyTree(ppRoot);
        return TRUE;
    }
    else
    {
        if (pDeleteNode->pParent == NULL)
        {
            return FALSE;
        }

        if (pDeleteNode->pParent->pChild == pDeleteNode)
        {
            if (pDeleteNode->pNextSibling == pDeleteNode)
            {
                pDeleteNode->pParent->pChild = NULL;
            }
            else
            {
                pDeleteNode->pParent->pChild = pDeleteNode->pNextSibling;
            }
        }
        pDeleteNode->pPrevSibling->pNextSibling = pDeleteNode->pNextSibling;
        pDeleteNode->pNextSibling->pPrevSibling = pDeleteNode->pPrevSibling;
        pDeleteNode->pParent = NULL;
        pDeleteNode->pPrevSibling = pDeleteNode;
        pDeleteNode->pNextSibling = pDeleteNode;

        DestroyTree(&pDeleteNode);
        return TRUE;
    }
}

BOOL IsTreeEmpty(const TreeNode* pRoot)
{
    return (pRoot == NULL);
}

int GetTreeDepth(const TreeNode* pRoot)
{
    int nTotalDepth = 0;
    int nChildDepth = 0;
    const TreeNode* pNode = NULL;
    
    if (pRoot == NULL)
    {
        return 0;
    }
    else if (pRoot->pChild == NULL)
    {
        return 1;
    }
    else
    {
        pNode = pRoot->pChild;
        do
        {
            nChildDepth = GetTreeDepth(pNode);
            if (nChildDepth > nTotalDepth)
            {
                nTotalDepth = nChildDepth;
            }
            pNode = pNode->pNextSibling;
        } while (pNode != pRoot->pChild);
        
        // ���ϸ����pRoot�����
        ++nTotalDepth;
        return nTotalDepth;
    }
}

void PreOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc)
{
    const TreeNode* pNode = NULL;
    
    if (pRoot != NULL)
    {
        pNode = pRoot;
        do
        {
            if (pFunc != NULL)
            {
                pFunc(pNode->nData);
            }
            if (pNode->pChild != NULL)
            {
                PreOrderTraverseTree(pNode->pChild, pFunc);
            }
            pNode = pNode->pNextSibling;
        } while (pNode != pRoot);
    }
}

void PostOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc)
{
    const TreeNode* pNode = NULL;
    
    if (pRoot != NULL)
    {
        pNode = pRoot;
        do
        {
            if (pNode->pChild != NULL)
            {
                PostOrderTraverseTree(pNode->pChild, pFunc);
            }
            if (pFunc != NULL)
            {
                pFunc(pNode->nData);
            }
            pNode = pNode->pNextSibling;
        } while (pNode != pRoot);
    }
}

void LevelOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc)
{
    // unimpl
}

void OutputTreeNodeData(int nData)
{
    printf("%d ", nData);
}

TreeNode** MakeTreeNodeList(int nLength)
{
    TreeNode** ppNodeList = NULL;
    int i = 0;
    
    ppNodeList = (TreeNode**)malloc(sizeof(TreeNode*) * nLength);
    memset(ppNodeList, 0, sizeof(TreeNode*) * nLength);
    for (; i < nLength; ++i)
    {
        ppNodeList[i] = MakeTreeNode();
    }
    
    return ppNodeList;
}

void FreeTreeNodeList(TreeNode** ppNodeList)
{
    if (ppNodeList != NULL)
    {
        free(ppNodeList);
    }
}

TreeNode* MakeTreeNode()
{
    TreeNode* pNode = NULL;
    
    pNode = (TreeNode*)malloc(sizeof(TreeNode));
    memset(pNode, 0, sizeof(TreeNode));
    
    return pNode;
}

void FreeTreeNode(TreeNode* pNode)
{
    if (pNode != NULL)
    {
        free(pNode);
    }
}
