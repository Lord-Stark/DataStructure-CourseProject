//Binary Tree on Linked Storage Structure
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//编译预处理
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define MAX_SIZE 20
#define Set_MAXSIZE 50
#define FILENAME_LENGTH 30

//定义状态返回值类型和数据元素类型
typedef int status;
typedef int ElemType;

//定义二叉链表节点类型
typedef struct Node
{
    struct Node *LeftChild;
    ElemType data;
    struct Node *RightChild;
} Node, *BiTree;

//函数声明
status InitBiTree(BiTree *T, BiTree BiTreeSet[]);
status DestroyBiTree(BiTree *T, BiTree BiTreeSet[]);
status CreateBiTree(BiTree *T);
status ClearBiTree(BiTree *T, BiTree BiTreeSet[]);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
Node *Root(BiTree T);
ElemType Value(BiTree T, Node *e);
status Assign(BiTree T, Node *e, ElemType value);
Node *Parent(BiTree T, Node *e);
Node *LeftChild(BiTree T, Node *e);
Node *RightChild(BiTree T, Node *e);
Node *LeftSibling(BiTree T, Node *e);
Node *RightSibling(BiTree T, Node *e);
status InsertChild(BiTree T, Node *p, int LR, BiTree c);
status DeleteChild(BiTree T, Node *p, int LR, BiTree BiTreeSet[]);
status PreOrderTraverse(BiTree T, status (*visit)(ElemType e));
status InOrderTraverse(BiTree T, status (*visit)(ElemType e));
status PostOrderTraverse(BiTree T, status (*visit)(ElemType e));
status LevelOrderTraverse(BiTree T, status (*visit)(ElemType e));
//status LevelTraverse(BiTree T,int Level_Now,int Level_Destination,status (*visit)(ElemType e))
status GetNode(BiTree T, int num, Node **node);
status SaveBiTree(BiTree T);
status WriteNodeToFile(BiTree T, FILE *fp);
status LoadBiTree(BiTree *T, BiTree BiTreeSet[]);
status ReadNodeFromFile(BiTree *T, FILE *fp);
status CreatAnotherBiTree(BiTree *T, BiTree BiTreeSet[]);
status ChooseBiTree(BiTree *T, BiTree BiTreeSet[]);

status visit (ElemType e)
{
    printf(" %d ", e);
    return OK;
}

int main(void)
{
    int op = 1, state;		//op=1:程序入口,state:接受返回值，表示函数返回状态
    int i, e, LR;			//LR:左子树（LR=0），右子树（LR=1）
    BiTree T = NULL;		//T:二叉树名、头指针
    BiTree BiTreeSet[MAX_SIZE] = {NULL};				//BiTreeSet：存储二叉树的头指针
    Node *Temp = NULL, *NewTree = NULL;
    while(op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Binary Tree on Linked Storage Structure      \n");
        printf("------------------------------------------------------------\n");
        printf("        0. Exit \n");
        printf("        1. InitBiTree          2. DestroyBiTree \n");
        printf("        3. CreateBiTree        4. ClearBiTree \n");
        printf("        5. BiTreeEmpty         6. BiTreeDepth \n");
        printf("    	7. BiTreeRoot          8. GetNodeValue \n");
        printf("    	9. AssignNode         10. GetNodeParent \n");
        printf("       11. GetLeftChild       12. GetRightChild \n");
        printf("       13. GetLeftSibling     14. GetRightSibling \n");
        printf("       15. InsertChild        16. DeleteChild \n");
        printf("       17. PreOrderTraverse   18. InOrderTraverse \n");
        printf("       19. PostOrderTraverse  20. LevelOrderTraverse \n");
        printf("       21. SaveBiTree         22. LoadBiTree \n");
        printf("       23. CreatAnothBiTree   24. ChooseBiTree \n");
        printf("------------------------------------------------------------\n");
        printf("    请选择你的操作[0~24]:");

        //若输入数字之外的字符，清空标准输入流里的数据，并将op置为default
        if(scanf("%d", &op) != 1)
        {
            fflush(stdin);
            op = 25;
        }

        switch(op)
        {
        case 1:
            state = InitBiTree(&T, BiTreeSet);
            if(state == OK) printf("二叉树初始化成功！\n");
            else printf("二叉树已存在！\n");
            system("pause");
            break;

        case 2:
            if(T == NULL) printf("二叉树不存在，无需销毁！\n");
            else
            {
                if(DestroyBiTree(&T, BiTreeSet) == OK) printf("二叉树销毁成功！\n");
                else printf("二叉树销毁失败！\n");
            }
            system("pause");
            break;

        case 3:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data != 0x7fffffff) printf("非空二叉树已存在！若要对其进行创建操作，请先清空该树！\n");
            else
            {
                printf("请输入先序遍历结果的二叉树，叶子节点的左右孩子节点为0：");
                if(CreateBiTree(&T) == OK) printf("创建成功！\n");
                else printf("创建失败！\n");
            }
            system("pause");
            break;

        case 4:
            state = ClearBiTree(&T, BiTreeSet);
            if(state == OK) printf("二叉树清空成功！\n");
            else printf("二叉树清空失败！\n");
            system("pause");
            break;


        case 5:
            state = BiTreeEmpty(T);
            if(state == TRUE) printf("该树是空树！\n");
            else if(state == FALSE) printf("该树不是空树！\n");
            system("pause");
            break;

        case 6:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else printf("该二叉树的深度为%d！\n", BiTreeDepth(T));
            system("pause");
            break;

        case 7:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else printf("该二叉树根节点的数据元素为%d！\n", Root(T)->data);
            system("pause");
            break;

        case 8:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i，获取二叉树层序遍历下第i个数据元素的值：");
                scanf("%d", &i);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else
                {
                    state = Value(T, Temp);
                    if(state == ERROR) printf("操作失败！\n");
                    else printf("二叉树层序遍历下第%d个数据元素的值为%d!\n", i, Value(T, Temp));
                }
            }
            system("pause");
            break;

        case 9:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i,e，将二叉树层序遍历下第i个数据元素赋值为 e ：");
                scanf("%d%d", &i, &e);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else
                {
                    state = Assign(T, Temp, e);
                    if(state == ERROR) printf("操作失败！\n");
                    else printf("赋值成功!\n");
                }
            }
            system("pause");
            break;

        case 10:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i，获取二叉树层序遍历下第i个数据元素的父亲节点的值 ：");
                scanf("%d", &i);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else
                {
                    Temp = Parent(T, Temp);
                    if(Temp == NULL) printf("操作失败！该节点没有父亲节点！\n");
                    else printf("二叉树层序遍历下第%d个数据元素的父亲节点的值为%d！\n", i, Value(T, Temp));
                }
            }
            system("pause");
            break;

        case 11:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i，获取二叉树层序遍历下第i个数据元素的左孩子节点的值 ：");
                scanf("%d", &i);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else
                {
                    Temp = LeftChild(T, Temp);
                    if(Temp == NULL) printf("操作失败！该节点没有左孩子节点！\n");
                    else printf("二叉树层序遍历下第%d个数据元素的左孩子节点的值为%d！\n", i, Value(T, Temp));
                }
            }
            system("pause");
            break;

        case 12:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i，获取二叉树层序遍历下第i个数据元素的右孩子节点的值 ：");
                scanf("%d", &i);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else
                {
                    Temp = RightChild(T, Temp);
                    if(Temp == NULL) printf("操作失败！该节点没有右孩子节点！\n");
                    else printf("二叉树层序遍历下第%d个数据元素的右孩子节点的值为%d！\n", i, Value(T, Temp));
                }
            }
            system("pause");
            break;

        case 13:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i，获取二叉树层序遍历下第i个数据元素的左兄弟节点的值 ：");
                scanf("%d", &i);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else
                {
                    Temp = LeftSibling(T, Temp);
                    if(Temp == NULL) printf("操作失败！该节点没有左兄弟节点！\n");
                    else printf("二叉树层序遍历下第%d个数据元素的左兄弟节点的值为%d！\n", i, Value(T, Temp));
                }
            }
            system("pause");
            break;

        case 14:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i，获取二叉树层序遍历下第i个数据元素的右兄弟节点的值 ：");
                scanf("%d", &i);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else
                {
                    Temp = RightSibling(T, Temp);
                    if(Temp == NULL) printf("操作失败！该节点没有右兄弟节点！\n");
                    else printf("二叉树层序遍历下第%d个数据元素的右兄弟节点的值为%d！\n", i, Value(T, Temp));
                }
            }
            system("pause");
            break;

        case 15:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i，以二叉树层序遍历下第i个节点为根节点，插入新树 ：");
                scanf("%d", &i);
                printf("请选择：\n0.插入到该节点的左子树。\n1.插入到该节点的右子树。\n");
                scanf("%d", &LR);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else if(LR != 0 && LR != 1) printf("输入错误！请输入0或1以选择插入到该节点的左子树或右子树。\n");
                else
                {
                    //初始化NewTree，将NewTree置为空树
                    NewTree = (BiTree)malloc(sizeof(Node));
                    NewTree->data = 0x7fffffff;
                    NewTree->LeftChild = NewTree->RightChild = NULL;
                    printf("请输入先序遍历结果的二叉树，叶子节点的左右孩子节点为0，同时保证该二叉树右子树为空：\n");
                    CreateBiTree(&NewTree);
                    state = InsertChild(T, Temp, LR, NewTree);
                    if(state == ERROR) printf("操作失败！\n");
                    else printf("操作成功！\n");
                }
            }
            system("pause");
            break;

        case 16:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                printf("输入i，删除以二叉树层序遍历下第i个数据元素为根节点的子树：");
                scanf("%d", &i);
                printf("请选择：\n0.删除以该节点为根节点的左子树。\n1.删除以该节点为根节点的右子树。\n");
                scanf("%d", &LR);
                if(GetNode(T, i, &Temp) == ERROR) printf("输入错误，不存在第%d个数据元素！\n", i);
                else
                {
                    state = DeleteChild(T, Temp, LR, BiTreeSet);
                    if(state == ERROR) printf("操作失败！\n");
                    else printf("删除成功！\n");
                }
            }
            system("pause");
            break;

        case 17:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                if(PreOrderTraverse(T, visit) == OK) printf("\n前序遍历成功！\n");
                else printf("\n前序遍历失败！\n");
            }
            system("pause");
            break;


        case 18:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                if(InOrderTraverse(T, visit) == OK) printf("\n中序遍历成功！\n");
                else printf("\n中序遍历失败！\n");
            }
            system("pause");
            break;

        case 19:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                if(PostOrderTraverse(T, visit) == OK) printf("\n后序遍历成功！\n");
                else printf("\n后序遍历失败！\n");
            }
            system("pause");
            break;

        case 20:
            if(T == NULL) printf("二叉树不存在！\n");
            else if(T->data == 0x7fffffff) printf("该二叉树为空二叉树！\n");
            else
            {
                if(LevelOrderTraverse(T, visit) == OK) printf("\n层序遍历成功！\n");
                else printf("\n层序遍历失败！\n");
            }
            system("pause");
            break;

        case 21:
            if(SaveBiTree(T) == OK) printf("二叉树保存成功！\n");
            else printf("二叉树保存失败！\n");
            system("pause");
            break;

        case 22:
            if(LoadBiTree(&T, BiTreeSet) == OK) printf("二叉树加载成功！\n");
            else printf("二叉树加载失败！\n");
            system("pause");
            break;

        case 23:
            if(CreatAnotherBiTree(&T, BiTreeSet) == OK) printf("创建新的二叉树成功！\n");
            else printf("操作失败！\n");
            system("pause");
            break;

        case 24:
            if(ChooseBiTree(&T, BiTreeSet) == OK) printf("成功选中该二叉树！\n");
            else printf("操作失败！\n");
            system("pause");
            break;

        case 0:
            break;

        default:
            printf("输入无效！菜单功能选择失败！\n");
            system("pause");
            break;

        }//end of switch

    }//end of while

    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()

//初始化二叉树：初始条件是二叉树T不存在；操作结果是构造空二叉树T。
//二叉树不存在：T==NULL
//空二叉树：T!=NULL&&T->data==0x7fffffff
status InitBiTree(BiTree *T, BiTree BiTreeSet[])
{
    int i;
    if((*T) == NULL)										//初始条件：二叉树T不存在
    {
        (*T) = (BiTree)malloc(sizeof(Node));				//为根节点分配空间
        (*T)->data = 0x7fffffff;							//数据域置为0x7fffffff，将该树置为空二叉树
        (*T)->LeftChild = (*T)->RightChild = NULL;			//左右孩子节点指针置为NULL
        for(i = 0; i < MAX_SIZE; i++) if(BiTreeSet[i] == NULL) break;		//找到二叉树头指针数组第一个为NULL的位置
        if(i == MAX_SIZE) exit(OVERFLOW);					//ERROR：OVERFLOW
        BiTreeSet[i] = (*T);								//将该二叉树添加至链表头指针数组
        return OK;
    }
    else return ERROR;									//ERROR:二叉树已经存在
}

//销毁二叉树：初始条件是二叉树T已存在；操作结果是销毁二叉树T。
status DestroyBiTree(BiTree *T, BiTree BiTreeSet[])
{
    int i;
    if((*T) == NULL) return OK;							//返回OK：空节点
    DestroyBiTree(&(*T)->LeftChild, BiTreeSet);			//销毁左子树
    DestroyBiTree(&(*T)->RightChild, BiTreeSet);			//销毁右子树
    for(i = 0; i < MAX_SIZE; i++) if(BiTreeSet[i] == *T) break;	//在二叉树头指针数组中查找该头指针
    if(i < MAX_SIZE)										//若该二叉树存在于头指针数组中时，将其删除
    {
        //在二叉树头指针数组中删除该头指针，后续元素前移
        //特殊情况：
        //1.数组存储了MAX_SIZE个二叉树；
        //2.T为第MAX_SIZE个二叉树
        while(i < MAX_SIZE - 1 && BiTreeSet[i] != NULL)
        {
            BiTreeSet[i] = BiTreeSet[i + 1];
            i++;
        }
        BiTreeSet[MAX_SIZE - 1] = NULL;						//处理BiTreeSet[MAX_SIZE-1]
    }
    free(*T);											//释放根节点
    (*T) = NULL;											//头指针置空
    return OK;
}

//创建二叉树：初始条件是definition 给出二叉树T的定义；操作结果是按definition构造二叉树T。
status CreateBiTree(BiTree *T)
{
    ElemType Data;
    if(scanf("%d", &Data) != EOF && Data != 0)					//输入二叉树节点的值（非0）
    {
        if((*T) == NULL)									//若节点为NULL，创建节点
        {
            (*T) = (BiTree)malloc(sizeof(Node));			//分配空间
            (*T)->LeftChild = (*T)->RightChild = NULL;		//左右孩子节点指针置为NULL
            if((*T) == NULL) exit(OVERFLOW);				//ERROR:OVERFLOW
        }
        (*T)->data = Data;								//节点数据域赋值
        CreateBiTree(&(*T)->LeftChild);					//递归：创建该节点的右子树
        CreateBiTree(&(*T)->RightChild);				//递归：创建该节点的左子树
        return OK;
    }
    else return ERROR;									//ERROR：根节点为0
}

//清空二叉树：初始条件是二叉树T存在；操作结果是将二叉树T清空。
status ClearBiTree(BiTree *T, BiTree BiTreeSet[])
{
    if((*T) == NULL)
    {
        printf("二叉树不存在，无需清空！\n");
        return ERROR;
    }
    else if((*T)->data == 0x7fffffff)
    {
        printf("该二叉树为空二叉树！\n");
        return ERROR;
    }
    if(DestroyBiTree(T, BiTreeSet) == OK && InitBiTree(T, BiTreeSet) == OK) return OK;		//清空=销毁+初始化
    else return ERROR;
}

//判定空二叉树：初始条件是二叉树T存在；操作结果是若T为空二叉树则返回TRUE，否则返回FALSE。
status BiTreeEmpty(BiTree T)
{
    if(T == NULL)
    {
        printf("二叉树不存在!\n");
        return ERROR;
    }
    else if(T->data == 0x7fffffff)	return TRUE;		//TRUE：空二叉树
    else return FALSE;									//FALSE：非空二叉树
}


//求二叉树深度：初始条件是二叉树T存在；操作结果是返回T的深度。
int BiTreeDepth(BiTree T)
{
    int Depth = 0, Depth_L, Depth_R;						//Depth_L:左子树深度；Depth_R:右子树深度
    if(T == NULL) return 0;								//return 0:二叉树不存在
    else
    {
        Depth_L = BiTreeDepth(T->LeftChild);				//递归：获取左子树深度
        Depth_R = BiTreeDepth(T->RightChild);				//递归：获取右子树深度
        //以该节点为根节点的树的深度是左、右子树深度的最大值加一
        Depth += 1 + ( Depth_L > Depth_R ? Depth_L : Depth_R);
        return Depth;									//返回深度
    }
}

//获得根结点：初始条件是二叉树T已存在；操作结果是返回T的根。
Node *Root(BiTree T)
{
    return T;
}

//获得结点：初始条件是二叉树T已存在，e是T中的某个结点；操作结果是返回e的值。
ElemType Value(BiTree T, Node *e)
{
    return e->data;										//返回该节点数据域的值
}

//结点赋值：初始条件是二叉树T已存在，e是T中的某个结点；操作结果是结点e赋值为value。
status Assign(BiTree T, Node *e, ElemType value)
{
    e->data = value;										//节点数据域赋值
    return OK;
}

//获得双亲结点：初始条件是二叉树T已存在，e是T中的某个结点。
//操作结果是若e是T的非根结点，则返回它的双亲结点指针，否则返回NULL。
Node *Parent(BiTree T, Node *e)
{
    Node *Queue[Set_MAXSIZE] = {NULL};					//节点数组：存储层序遍历的每个结点指针
    Node *LeftChild = NULL, *RightChild = NULL;
    //游走监视哨：i指向数组的下一个空位，j指向正在遍历的节点的父亲节点
    int i = 1, j = 0;
    Queue[0] = T;											//首先遍历根节点
    while(i > j)											//循环结束条件：j>=i
    {
        if (Queue[j])									//若Queue[j]!=NULL,访问其左右孩子节点
        {
            LeftChild = Queue[j]->LeftChild;
            RightChild = Queue[j]->RightChild;
            if(LeftChild) Queue[i++] = LeftChild;			//存储j的非空左孩子结点，i++
            if(RightChild) Queue[i++] = RightChild;		//存储j的非空右孩子结点,i++
        }
        j++;											//j指向上一层的下一个节点
    }
    //遍历该数组，寻找左孩子或者右孩子为e的节点
    for(i = 0; Queue[i] != NULL; i++)
        if(Queue[i]->LeftChild == e || Queue[i]->RightChild == e) break;
    return Queue[i];									//返回该节点
}

//获得左孩子结点：初始条件是二叉树T存在，e是T中某个节点。
//操作结果是返回e的左孩子结点指针。若e无左孩子，则返回NULL。
Node *LeftChild(BiTree T, Node *e)
{
    return e->LeftChild;								//返回其左孩子节点
}

//获得右孩子结点：初始条件是二叉树T已存在，e是T中某个结点。
//操作结果是返回e的右孩子结点指针。若e无右孩子，则返回NULL。
Node *RightChild(BiTree T, Node *e)
{
    return e->RightChild;								//返回其右孩子节点
}

//获得左兄弟结点：初始条件是二叉树T存在，e是T中某个结点。
//操作结果是返回e的左兄弟结点指针。若e是T的左孩子或者无左兄弟，则返回NULL。
Node *LeftSibling(BiTree T, Node *e)
{
    Node *parents = Parent(T, e);							//parents:获取该节点的父亲节点
    if(parents == NULL) return NULL;						//ERROR:该节点没有父亲节点
    //若该节点是其父亲节点的右孩子节点，返回该节点的左兄弟
    if(parents->RightChild == e) return parents->LeftChild;
    else return NULL;									//ERROR:该节点是其父亲节点的左孩子节点
}

//获得右兄弟结点：初始条件是二叉树T已存在，e是T中某个结点。
//操作结果是返回e的右兄弟结点指针。若e是T的右孩子或者无右兄弟，则返回NULL。
Node *RightSibling(BiTree T, Node *e)
{
    Node *parents = Parent(T, e);							//parents:获取该节点的父亲节点
    if(parents == NULL) return NULL;						//ERROR:该节点没有父亲节点
    //若该节点是其父亲节点的左孩子节点，返回该节点的右兄弟
    if(parents->LeftChild == e) return parents->RightChild;
    else return NULL;									//ERROR:该节点是其父亲节点的右孩子节点
}

//插入子树：初始条件是二叉树T存在，p指向T中的某个结点，LR为0或1。
//非空二叉树c与T不相交且右子树为空。
//操作结果是根据LR为0或者1，插入c为T中p所指结点的左或右子树，p所指结点的原有左子树或右子树则为c的右子树。
status InsertChild(BiTree T, Node *p, int LR, BiTree c)
{
    if(c->RightChild != NULL) return ERROR;				//ERROR：c的右子树不为空
    if(LR == 0)											//插入到左子树
    {
        c->RightChild = p->LeftChild;						//将p的左子树移动到c的右子树
        p->LeftChild = c;									//将c插入到p的左子树
    }
    else if(LR == 1) 										//插入到右子树
    {
        c->RightChild = p->RightChild;					//将p的右子树移动到c的右子树
        p->RightChild = c;								//将c插入到p的右子树
    }
    return OK;
}

//删除子树：初始条件是二叉树T存在，p指向T中的某个结点，LR为0或1。
//操作结果是根据LR为0或者1，删除c为T中p所指结点的左或右子树。
status DeleteChild(BiTree T, Node *p, int LR, BiTree BiTreeSet[])
{
    if(LR == 0)
    {
        DestroyBiTree(&(p->LeftChild), BiTreeSet);    //销毁左子树
        return OK;
    }
    else if(LR == 1)
    {
        DestroyBiTree(&(p->RightChild), BiTreeSet);    //销毁右子树
        return OK;
    }
    else return ERROR;									//ERROR：LR!=0&&LR!=1（输入错误）
}

//前序遍历：初始条件是二叉树T存在；操作结果：先序遍历T，对每个结点调用函数visit一次。
status PreOrderTraverse(BiTree T, status (*visit)(ElemType e))
{
    if(T == NULL) return OK;								//return OK:空树
    visit(T->data);										//访问该根节点
    PreOrderTraverse(T->LeftChild, visit);				//递归：遍历左子树
    PreOrderTraverse(T->RightChild, visit);				//递归：遍历右子树
    return OK;
}

//中序遍历：初始条件是二叉树T存在；操作结果是中序遍历T，对每个结点调用函数visit一次。
status InOrderTraverse(BiTree T, status (*visit)(ElemType e))
{
    if(T == NULL) return OK;								//return OK:空树
    InOrderTraverse(T->LeftChild, visit);				//递归：遍历左子树
    visit(T->data);										//访问该根节点
    InOrderTraverse(T->RightChild, visit);				//递归：遍历右子树
    return OK;
}

//后序遍历：初始条件是二叉树T存在；操作结果是后序遍历T，对每个结点调用函数visit一次。
status PostOrderTraverse(BiTree T, status (*visit)(ElemType e))
{
    if(T == NULL) return OK;								//return OK:空树
    PostOrderTraverse(T->LeftChild, visit);				//递归：遍历左子树
    PostOrderTraverse(T->RightChild, visit);				//递归：遍历右子树
    visit(T->data);										//访问该根节点
    return OK;
}

//按层遍历：初始条件是二叉树T存在；操作结果是层序遍历T，对每个结点调用函数visit一次。
status LevelOrderTraverse(BiTree T, status (*visit)(ElemType e))
{
    Node *Queue[Set_MAXSIZE] = {NULL};					//节点数组：存储层序遍历的每个结点指针
    Node *LeftChild = NULL, *RightChild = NULL;
    //游走监视哨：i指向数组的下一个空位，j指向正在遍历的节点的父亲节点
    int i = 1, j = 0;
    Queue[0] = T;											//首先遍历根节点
    while(i > j)											//循环结束条件：j>=i
    {
        if (Queue[j])									//若Queue[j]!=NULL,访问其左右孩子节点
        {
            visit(Queue[j]->data);						//访问j指向的节点
            LeftChild = Queue[j]->LeftChild;
            RightChild = Queue[j]->RightChild;
            if(LeftChild) Queue[i++] = LeftChild;			//存储j的非空左孩子结点，i++
            if(RightChild) Queue[i++] = RightChild;		//存储j的非空右孩子结点,i++
        }
        j++;											//j指向上一层的下一个节点
    }
    return OK;
}

/*
//按层遍历：初始条件是二叉树T存在；操作结果是层序遍历T，对每个结点调用函数visit一次。
status LevelOrderTraverse(BiTree T,status (*visit)(ElemType e))
{
	int Depth=BiTreeDepth(T),Level_Destination;			//获取二叉树的深度
	for(Level_Destination=1;Level_Destination<=Depth;Level_Destination++)
		LevelTraverse(T,1,Level_Destination,visit);		//依次输出每一层
	return OK;
}

//遍历输出二叉树的某一层：初始条件是二叉树T存在；操作结果是遍历输出二叉树的第i层。
//节点在第i层的另一层含义：从根节点到该节点的路径长度为i
status LevelTraverse(BiTree T,int Level_Now,int Level_Destination,status (*visit)(ElemType e))
{
	if(T==NULL) return ERROR;							//ERROR：该节点为空节点，返回
	//若该节点在目标层，输出该节点
	if(Level_Now==Level_Destination) visit(T->data);
	else
	{
		//若该节点不在目标层，依次检查其左、右孩子节点是否在目标层（保证层序从左到右）
		LevelTraverse(T->LeftChild,Level_Now+1,Level_Destination,visit);
		LevelTraverse(T->RightChild,Level_Now+1,Level_Destination,visit);
	}
	return OK;
}
*/

//获取节点：初始条件是二叉树T存在；操作结果是获取第num个节点
status GetNode(BiTree T, int num, Node **node)
{
    Node *Queue[Set_MAXSIZE] = {NULL};					//节点数组：存储层序遍历的每个结点指针
    Node *LeftChild = NULL, *RightChild = NULL;
    //游走监视哨：i指向数组的下一个空位，j指向正在遍历的节点的父亲节点
    int i = 1, j = 0;
    Queue[0] = T;											//首先遍历根节点
    while(i > j)											//循环结束条件：j>=i
    {
        if (Queue[j])									//若Queue[j]!=NULL,访问其左右孩子节点
        {
            LeftChild = Queue[j]->LeftChild;
            RightChild = Queue[j]->RightChild;
            if(LeftChild) Queue[i++] = LeftChild;			//存储j的非空左孩子结点，i++
            if(RightChild) Queue[i++] = RightChild;		//存储j的非空右孩子结点，i++
        }
        j++;											//j指向上一层的下一个节点
    }
    if(num < 1 || num > i) return ERROR;						//ERROR：没有第num个节点
    else
    {
        (*node) = Queue[num - 1];    //将节点赋值给node,实现获取
        return OK;
    }
}

//保存二叉树：初始条件是二叉树T存在且该二叉树不为空树；操作结果是将该二叉树保存到用户指定的文件中
status SaveBiTree(BiTree T)
{
    char filename[FILENAME_LENGTH] = {0};
    FILE *fp = NULL;
    if(T == NULL)
    {
        printf("二叉树不存在！\n");
        return ERROR;
    }
    else if(T->data == 0x7fffffff)
    {
        printf("该二叉树为空二叉树！\n");
        return ERROR;
    }
    printf("输入文件路径(长度应在%d字符以内)，将二叉树保存到该文件中：", FILENAME_LENGTH);
    scanf("%s", filename);								//输入文件路径
    fp = fopen(filename, "w");								//打开文件
    if(fp == NULL) return ERROR;							//ERROR：打开文件错误
    if(WriteNodeToFile(T, fp) == ERROR) return ERROR;		//ERROR：写入节点错误
    fclose(fp);											//关闭文件
    return OK;
}

//将节点写入文件：初始条件是文件已打开；操作结果是将该节点保存到用户指定的文件中
status WriteNodeToFile(BiTree T, FILE *fp)
{
    if(fp == NULL) return ERROR;							//ERROR:未打开文件
    if(T == NULL)
    {
        fprintf(fp, "0 ");    //空节点：将0写入文件
        return OK;
    }
    else												//非空节点
    {
        fprintf(fp, "%d ", T->data);						//将该节点写入文件
        WriteNodeToFile(T->LeftChild, fp);				//递归：将该节点的左孩子结点写入文件
        WriteNodeToFile(T->RightChild, fp);				//递归：将该节点的右孩子结点写入文件
        return OK;
    }
}

//加载二叉树：初始条件是二叉树T存在；操作结果是将用户指定的文件中的二叉树加载出来
status LoadBiTree(BiTree *T, BiTree BiTreeSet[])
{
    char filename[FILENAME_LENGTH] = {0};
    FILE *fp = NULL;
    if((*T) == NULL)
    {
        printf("二叉树不存在！\n");
        return ERROR;
    }
    if((*T)->data != 0x7fffffff)
    {
        *T = NULL;    //若该二叉树不是空二叉树，初始化该二叉树
        InitBiTree(T, BiTreeSet);
    }
    printf("输入文件路径(长度应在%d字符以内)，加载文件中的二叉树：", FILENAME_LENGTH);
    scanf("%s", filename);								//输入文件路径
    fp = fopen(filename, "r");								//打开文件
    if(fp == NULL) return ERROR;							//ERROR：打开文件错误
    if(ReadNodeFromFile(T, fp) == ERROR) return ERROR;	//ERROR：读取节点错误
    fclose(fp);											//关闭文件
    return OK;
}

//加载文件中的节点：初始条件是文件已打开；操作结果是将用户指定的文件中的节点加载到二叉树T中
status ReadNodeFromFile(BiTree *T, FILE *fp)
{
    ElemType Data;
    if(fscanf(fp, "%d ", &Data) != EOF && Data != 0)			//读取文件中二叉树节点的值（非0）
    {
        if((*T) == NULL)									//若节点为NULL，创建节点
        {
            (*T) = (BiTree)malloc(sizeof(Node));			//分配空间
            (*T)->LeftChild = (*T)->RightChild = NULL;		//左右孩子节点指针置为NULL
            if((*T) == NULL) exit(OVERFLOW);				//ERROR:OVERFLOW
        }
        (*T)->data = Data;								//节点数据域赋值
        ReadNodeFromFile(&(*T)->LeftChild, fp);			//递归：读取该节点的左孩子结点
        ReadNodeFromFile(&(*T)->RightChild, fp);			//递归：读取该节点的右孩子结点
        return OK;
    }
    else return ERROR;									//ERROR:ctrl+z或Data==0
}

//创建另一颗二叉树：初始条件是已经存在一颗二叉树
status CreatAnotherBiTree(BiTree *T, BiTree BiTreeSet[])
{
    BiTree *Temp = T;										//保存该二叉树头指针
    if((*T) == NULL)
    {
        printf("没有已存在的二叉树，无需再次创建二叉树!\n");
        return ERROR;
    }
    (*T) = NULL;											//二叉树头指针置空
    InitBiTree(T, BiTreeSet);							//初始化该二叉树
    printf("请输入先序遍历结果的二叉树，叶子节点的左右孩子节点为0：");
    if(CreateBiTree(T) == OK) return OK;					//创建二叉树
    else												//创建失败
    {
        DestroyBiTree(T, BiTreeSet);						//销毁该二叉树
        T = Temp;											//将保存好的头指针赋值给T
        return ERROR;
    }
}

//选择二叉树：初始条件是已经存在至少一棵二叉树
status ChooseBiTree(BiTree *T, BiTree BiTreeSet[])
{
    int i = 0, n;
    BiTree p = NULL;
    if(BiTreeSet[0] == NULL)
    {
        printf("没有可选择的二叉树！\n");
        return ERROR;
    }
    while(BiTreeSet[i] != NULL)							//遍历二叉树头指针数组
    {
        p = BiTreeSet[i];
        printf("第%d个二叉树：", i + 1);
        if(p->data != 0x7fffffff)							//若该二叉树不是空树
            PreOrderTraverse(p, visit);					//遍历该二叉树
        printf("\n");
        i++;
    }
    printf("输入n，选择第n个二叉树进行操作：");
    scanf("%d", &n);
    if(n > i || n < 1)
    {
        printf("不存在第%d个二叉树！\n", n);
        return ERROR;
    }
    (*T) = BiTreeSet[n - 1];								//实现选择二叉树
    if((*T) == NULL) return ERROR;
    else return OK;
}