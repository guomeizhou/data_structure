#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * 多叉树
 * parent相同的所有的孩子结点使用双向链表结构进行存储。
 */

/* 创建树后，树的结构如下：
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

/* 程序输出如下:
先序遍历：
66 33 11 77 88 22 55 99 44 100
后序遍历：
11 88 77 22 55 33 99 100 44 66
层序遍历：

树是非空的
树的深度是4
-----------------------------------------------------
添加结点111成功
先序遍历：
66 33 11 77 88 22 55 111 99 44 100
后序遍历：
11 88 77 22 55 111 33 99 100 44 66
层序遍历：

树是非空的
树的深度是4
-----------------------------------------------------
删除结点111成功
先序遍历：
66 33 11 77 88 22 55 99 44 100
后序遍历：
11 88 77 22 55 33 99 100 44 66
层序遍历：

树是非空的
树的深度是4
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
    // NO_POS: 表示没有parent
    int nParentPos;
    // NO_POS: 表示没有child
    int nChildPos;
    int nPrevSiblingPos;
    int nNextSibling;
} ParentChildSiblingInfo;

typedef void (*OutputFuncType)(int nData);

/*
 * 功能: 创建树。
 * 名称: CreateTree。
 * 参数: const ParentChildSiblingInfo* pData，指向一个存放父母孩子兄弟关系信息的数组。
 * 参数: int nLength，该数组的长度。
 * 返回值: TreeNode*，指向链表头结点的指针。
 */
TreeNode* CreateTree(const ParentChildSiblingInfo* pData, int nLength);
/*
 * 功能: 销毁树。
 * 名称: DestroyTree。
 * 参数: const TreeNode* pRoot，指向树的根结点。
 * 返回值: void。
 */
void DestroyTree(TreeNode** ppRoot);
/*
 * 功能: 给树添加结点。
 * 名称: AddTreeNode。
 * 参数: TreeNode** ppRoot，指向树的根结点的地址。
 * 参数: TreeNode* pParent，指向父结点，它是新添加结点的父结点。
 * 参数: int nData，新添加结点的数据值。
 * 返回值: TreeNode*，指向新添加的结点。
 */
TreeNode* AddTreeNode(TreeNode** ppRoot, TreeNode* pParent, int nData);
/*
 * 功能: 删除树中的某个结点。
         如果该结点有子结点，将也会被删除。
 * 名称: DeleteTreeNode。
 * 参数: TreeNode** ppRoot，指向树的根结点的地址。
 * 参数: TreeNode* pDeleteNode，指向删除的结点。
 * 返回值: BOOL，TRUE表示删除成功，FALSE表示删除失败。
 */
BOOL DeleteTreeNode(TreeNode** ppRoot, TreeNode* pDeleteNode);
/*
 * 功能: 判断树是否为空。
 * 名称: IsTreeEmpty。
 * 参数: const TreeNode* pRoot，指向树的根结点。
 * 返回值: BOOL，TRUE表示空，FALSE表示非空。
 */
BOOL IsTreeEmpty(const TreeNode* pRoot);
/*
 * 功能: 得到树的深度。
 * 名称: GetTreeDepth。
 * 参数: const TreeNode* pRoot，指向树的根结点。
 * 返回值: int，表示树的深度。
 */
int GetTreeDepth(const TreeNode* pRoot);
/*
 * 功能: 先序遍历树。
         先遍历根结点，后遍历子结点。
 * 名称: PreOrderTraverseTree。
 * 参数: const TreeNode* pRoot，指向树的根结点。
 * 参数: OutputFuncType pFunc，指向输出树中结点函数的指针。
 * 返回值: void。
 */
void PreOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc);
/*
 * 功能: 后序遍历树。
         先遍历子结点，后遍历根结点。
 * 名称: PostOrderTraverseTree。
 * 参数: const TreeNode* pRoot，指向树的根结点。
 * 参数: OutputFuncType pFunc，指向输出树中结点函数的指针。
 * 返回值: void。
 */
void PostOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc);
/*
 * 功能: 层序遍历树。
         先遍历根结点，后遍历所有子结点。
 * 名称: LevelOrderTraverseTree。
 * 参数: const TreeNode* pRoot，指向树的根结点。
 * 参数: OutputFuncType pFunc，指向输出树中结点函数的指针。
 * 返回值: void。
 */
void LevelOrderTraverseTree(const TreeNode* pRoot, OutputFuncType pFunc);
/*
 * 功能: 输出树结点中的数据。
 * 名称: OutputTreeNodeData。
 * 参数: int nData，树结点中的数据。
 * 返回值: void。
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
    printf("先序遍历：\n");
    PreOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("后序遍历：\n");
    PostOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("层序遍历：\n");
    LevelOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");

    bResult = IsTreeEmpty(pRoot);
    printf("树是%s的\n", bResult ? "空" : "非空");

    nTreeDepth = GetTreeDepth(pRoot);
    printf("树的深度是%d\n", nTreeDepth);

    printf("-----------------------------------------------------\n");

    pParent = pRoot->pChild;
    pNode = AddTreeNode(&pRoot, pParent, nNodeData);
    printf("添加结点%d%s\n", nNodeData, (pNode != NULL) ? "成功" : "失败");
    printf("先序遍历：\n");
    PreOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("后序遍历：\n");
    PostOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("层序遍历：\n");
    LevelOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");

    bResult = IsTreeEmpty(pRoot);
    printf("树是%s的\n", bResult ? "空" : "非空");

    nTreeDepth = GetTreeDepth(pRoot);
    printf("树的深度是%d\n", nTreeDepth);

    printf("-----------------------------------------------------\n");

    bResult = DeleteTreeNode(&pRoot, pNode);
    pNode = NULL;
    printf("删除结点%d%s\n", nNodeData, bResult ? "成功" : "失败");
    
    printf("先序遍历：\n");
    PreOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("后序遍历：\n");
    PostOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");
    
    printf("层序遍历：\n");
    LevelOrderTraverseTree(pRoot, OutputTreeNodeData);
    printf("\n");

    bResult = IsTreeEmpty(pRoot);
    printf("树是%s的\n", bResult ? "空" : "非空");

    nTreeDepth = GetTreeDepth(pRoot);
    printf("树的深度是%d\n", nTreeDepth);

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
                // 把pNode放在pParent的所有孩子结点的末尾，所有的孩子结点使用双向链表结构进行存储。
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
        
        // 加上根结点pRoot的深度
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
