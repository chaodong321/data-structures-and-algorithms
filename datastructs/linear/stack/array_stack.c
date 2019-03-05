#include <stdio.h>
#include <stdlib.h>

typedef enum {true, false} bool;
typedef struct AStack{
    int *data;
    int top;
    int len;
}aStack, *paStack;

//函数声明
void init_stack(paStack pas, int len); //初始化一个栈
bool is_empty(paStack pas); //判断栈是否位空
bool is_full(paStack pas); //判断栈是否满
bool push(paStack pas, int val); //压栈
void traverse(paStack pas); //遍历栈
bool pop(paStack pas, int *pVal); //出栈
void clear_stack(paStack pas); //清空栈内所有元素

int main(int argc, const char * argv[]) {
    // insert code here...
    aStack pas;
    int val;

    init_stack(&pas, 6);
    push(&pas, 1);
    push(&pas, 2);
    push(&pas, 3);
    push(&pas, 4);
    push(&pas, 5);
    push(&pas, 6);
    traverse(&pas);

    if ( pop(&pas, &val) == true ) //将出栈结果保存到val中
    {
        printf("删除成功，删除的值为：%d\n", val);
    }
    else
    {
        printf("删除失败!\n");
    }
    traverse(&pas);

    clear_stack(&pas);
    traverse(&pas);

    return 0;
}

void init_stack(paStack pas, int len){
    pas->data = (int *)malloc(sizeof(int)*len);
    if (pas->data == NULL) {
        printf("内存分配失败\n");
        exit(-1);
    }else{
        pas->len = len;
        pas->top = -1;
    }

    return;
}

bool is_empty(paStack pas){
    if (pas->top < 0) {
        return true;
    }else{
        return false;
    }
}

bool is_full(paStack pas){
    if (pas->top >= pas->len) {
        return true;
    }else{
        return false;
    }
}

bool push(paStack pas, int val){
    if (is_full(pas) == true) {
        return false;
    }else{
        pas->top++;
        pas->data[pas->top] = val;
        return true;
    }
}

void traverse(paStack pas){
    int i, n;
    n = pas->top;
    for (i=n; i>=0; i--) {
        printf("%d ", pas->data[i]);
    }
    printf("\n");

    return;
}

bool pop(paStack pas, int *pVal){
    if (is_empty(pas) == true) {
        return false;
    }else{
        *pVal = pas->data[pas->top];
        pas->top--;
        return true;
    }
}

void clear_stack(paStack pas){
    if (is_empty(pas) == true){
        printf("顺序栈为空!\n");
        exit(-1);
    }else{
        pas->top = -1;
        printf("顺序栈已置为空！\n");
    }

    return;
}