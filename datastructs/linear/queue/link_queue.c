#include "link_queue.h"

/*********************************************************************
 * 刚开始创建空队列时，队列的队头和队尾指针相等都指向头结点，头结点的数据域不存放数据
 * 第一次入队，创建新结点，其数据域保存新插入元素，头结点的next指向新结点,
 * 并且队列的队尾指针指向新结点,队列的队头指针仍然指向头结点,依次类推
 * 第一次出队，则队列的队头指针指向头结点的next,依次类推
 *********************************************************************/

//创建空队列： pQHead即为队列头结点
status initQueue(LinkQueue *pQHead)
{
    //队列头结点的队头和队尾指针申请内存
    pQHead->front = pQHead->rear = (LQNode*)malloc(sizeof(LQNode));
    if(!pQHead->front) //检测是否申请失败
    {
        printf("pQHead->front malloc error!\n");
        return ERROR;
    }

    //设置头结点指针域为空
    pQHead->front->next = NULL;

    return OK;
}

//销毁队列
void destroyQueue(LinkQueue *pQHead)
{
    free(pQHead->front);
    free(pQHead->rear);
    pQHead->front = pQHead->rear = NULL;
}

//清空队列
void clearQueue(LinkQueue *pQHead)
{
    pQHead->front = pQHead->rear;
}

//判断队列是否为空
status isEmpityQueue(LinkQueue *pQHead)
{
    //队头指针与队尾指针相等，说明队列为空
    if(pQHead->front == pQHead->rear)
        return TRUE;

    return FALSE;
}

//获得队列长度
int getQueueLen(LinkQueue *pQHead)
{
    LQNode *temp = pQHead->front;
    int length = 0;
    while(temp != pQHead->rear)
    {
        ++length;
        temp = temp->next;
    }

    return length;
}

//新元素入队:即链式队列的尾结点指针，指向存放新元素的新结点
status enQueue(LinkQueue *pQHead, ElemType element)
{
    //创建新结点,并申请内存
    LQNode  *temp = (LQNode*)malloc(sizeof(LQNode));
    if(!temp)
    {
        printf("temp malloc error!\n");
        return ERROR;
    }

    temp->data = element; //将要插入元素存入新结点的数据域内
    temp->next = NULL; //队列只能从队尾插入所以下一个结点初始化为NULL

    //链式队列元素为结点(LQNode)
    //pQHead->rear为队列的最后一个结点，当插入新结点temp时,pQHead->rear->next = temp
    //使前一个结点的next指向新结点，建立队列各结点之间的联系
    pQHead->rear->next = temp; //将队尾结点的后继指针指向新结点,如果第一次入队，
                      //则pQueue->rear->next相当于pQueue->front->next
    // pQHead->rear总是指向队列的最后一个结点
    pQHead->rear = temp;    //将队尾结点的指针指向新结点temp,temp变为最后一个结点

    return OK;
}

status deQueue(LinkQueue *pQHead,ElemType *pElement)
{
    //如果队列为空,则返回ERROR
    if(isEmpityQueue(pQHead)==TRUE)
    {
        printf("queue is NULL!\n");
        return ERROR;
    }

    //值入队一次后就出队，则pQueue->front->next==pQHead->rear->next,为第一个插入的结点
    LQNode *temp = pQHead->front->next; //初始化temp为要出队的结点的指针

    //如果要出队的结点为最后一个结点,使q->rear指向头结点防止出现悬空的指针
    if(pQHead->front->next == pQHead->rear)
        pQHead->rear = pQHead->front;

    *pElement = temp->data; //将出队的数据元素存入*e
    pQHead->front->next = temp->next; //使下一个结点成为队头,如果没有下一个结点则为NULL
    free(temp); //删除要出队的结点
    temp = NULL;

    return OK;
}

//遍历队列
void queueTraverse(LinkQueue *pQHead)
{
    //如果队列为空
    if(isEmpityQueue(pQHead)==TRUE)
    {
        printf("\nqueue is NULL!\n");
    }

    LQNode *temp = pQHead->front;

    printf("将队列中的所有元素出队:\n");
    while(temp != pQHead->rear)
    {

        temp = temp->next;
        printf("%d  ", temp->data);
    }
    printf("\n");
}