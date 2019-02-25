#include <stdio.h>
#include "array_queue.h"

int main(void)
{
    int value;          //用于保存出队的元素
    //创建队列对象
    queue *PQueue = (queue *)malloc(sizeof(queue));
    if(!PQueue)
    {
        printf("给队列对象分配内存失败\n");
        return -1;
    }

    //调用初始化队列的函数
    initQueue(PQueue,MAX_SIZE);
    //调用出队函数
    enQueue(PQueue, 11);
    enQueue(PQueue, 2);
    enQueue(PQueue, 333);
    enQueue(PQueue, 44);
    enQueue(PQueue, 50);
    enQueue(PQueue, 6);
    enQueue(PQueue, 777);
    enQueue(PQueue, 8888);
    //调用遍历队列的函数
    queueTraverse(PQueue);
    //调用出队函数
    if(deQueue(PQueue, &value))
    {
        printf("出队一次，元素为：%d\n", value);
    }
    queueTraverse(PQueue);
    if(deQueue(PQueue, &value))
    {
        printf("出队一次，元素为：%d\n", value);
    }
    queueTraverse(PQueue);

    free(PQueue);
    PQueue = NULL;

    getchar();
    return 0;
}