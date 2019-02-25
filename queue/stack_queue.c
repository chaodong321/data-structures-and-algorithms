#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef int datatype_t;
typedef struct {
    datatype_t data[N];
    datatype_t top;
}seqstack_t;

typedef struct stackqueue_p{
    seqstack_t *front;
    seqstack_t *real;
    int count;
}sq_t;

/**
  *@brief 创建一个空的栈
 */
seqstack_t *seqstack_creat()
{
    seqstack_t *s;
    s=(seqstack_t *)malloc(sizeof(seqstack_t));
    if(NULL==s){
        printf(__FUNCTION__);
        printf("ERROR in line %d",__LINE__);
        return (seqstack_t *)-1;
    }
    bzero(s,sizeof(seqstack_t));
    s->top=-1;
}

/**
  *@brief 清空栈
 */
void seqstack_clear(seqstack_t *s)
{
    s->top=-1; //不是链式栈而是数组，所以不用释放内存，直接设置为-1，使用链式栈的话需要将链表节点内存释放
}

/**
  *@brief 栈满
 */
datatype_t seqstack_full(seqstack_t *s)
{
    if(s->top>=N-1){
        printf("static full!");
        return (datatype_t)1;
    }

    return (datatype_t)0;

}

/**
  *@brief 栈空
 */
datatype_t seqstack_empty(seqstack_t *s)
{
    if(s->top==-1){
        return (datatype_t)1;
    }

    return (datatype_t)0;
}

/**
  *@brief 入栈
 */
datatype_t seqstack_insert(seqstack_t *s,datatype_t value)
{
    if(seqstack_full(s)){
        return (datatype_t)-1;
    }

    s->top++;
    s->data[s->top]=value;

    return (datatype_t)0;
}

/**
  *@brief 出栈
 */
datatype_t seqstack_out(seqstack_t *s)
{
    datatype_t value=s->data[s->top];

    if(seqstack_empty(s)){
        return (datatype_t)-1;
    }

    s->top--;
    return value;
}

/**
  *@brief 打印栈数据
 */
datatype_t seqstack_show(seqstack_t *s)
{
    datatype_t i;
    if(seqstack_empty(s)){
        return (datatype_t)-1;
    }

    for(i=0;i<=s->top;i++){
        printf("top %d=%d.\n",i,s->data[i]);
    }

    return (datatype_t)0;
}

/**
  *@brief 创建一个空栈队列
 */
sq_t *stackqueue_create()
{
    sq_t *sq=(sq_t *)malloc(sizeof(sq_t));
    sq->front=seqstack_creat();
    sq->real=seqstack_creat();
    if(NULL==sq)
    {
        printf(__FUNCTION__);
        printf("error in line %d.\n",__LINE__);
        return (sq_t*)-1;
    }
    //sq->front->top=sq->real->top=-1;
    return sq;
}

/**
  *@brief 入队
 */
int push(sq_t *sq,int value)
{
    seqstack_insert(sq->real,value);
    return 0;

}

/**
  *@brief 出队
 */
datatype_t pop(sq_t *sq)
{
	datatype_t pop_val = -1;
    if(!seqstack_empty(sq->real));
    {
        while(!seqstack_empty(sq->real))
        {
            seqstack_insert(sq->front,seqstack_out(sq->real));
        }
		pop_val = seqstack_out(sq->front);
		
		if(!seqstack_empty(sq->front));
		{
			while(!seqstack_empty(sq->front))
			{
				seqstack_insert(sq->real,seqstack_out(sq->front));
			}
		}
    }

    return pop_val;
}

/**
  *@brief 打印队列
 */
void stackqueue_show(sq_t *sq)
{
    seqstack_show(sq->front);
    seqstack_show(sq->real);
}

int main(void)
{
    sq_t *p=stackqueue_create();
    push(p,1);
    push(p,2);
    push(p,3);
    push(p,4);
    push(p,5);
    pop(p);
    pop(p);
    pop(p);
    stackqueue_show(p);
}