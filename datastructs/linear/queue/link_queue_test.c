/*********************************************
 * C实现链式队列   2017/10/26   by nieXianFeng
 *********************************************/
#include <stdio.h>
#include "link_queue.h"

int main()
{
    int value;          //用于保存出队的元素

    //给头结点申请内存
    LinkQueue *pQHead= (LinkQueue*)malloc(sizeof(LinkQueue));
    if(!pQHead) //检测是否申请失败
    {
        printf("pQHead malloc error!\n");
        return ERROR;
    }

    //调用初始化队列的函数
    initQueue(pQHead);
    //调用出队函数
    enQueue(pQHead, 21);
    enQueue(pQHead, 24);
    enQueue(pQHead, 3);
    enQueue(pQHead, 54);
    enQueue(pQHead, 5);
    enQueue(pQHead, 6);
    enQueue(pQHead, 79);
    enQueue(pQHead, 800);
    //调用遍历队列的函数
    queueTraverse(pQHead);

    //调用出队函数
    if(deQueue(pQHead, &value)==OK)
    {
        printf("出队一次，元素为：%d\n", value);
    }
    queueTraverse(pQHead);
    if(deQueue(pQHead, &value)==OK)
    {
        printf("出队一次，元素为：%d\n", value);
    }
    queueTraverse(pQHead);

    printf("队列长度是%d\n",getQueueLen(pQHead));

    clearQueue(pQHead);   //清空队列
    queueTraverse(pQHead);

    free(pQHead);
    pQHead = NULL;

    return 0;
}