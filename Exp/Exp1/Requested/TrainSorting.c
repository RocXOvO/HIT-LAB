#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 定义栈结构体
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *s) {
    s -> top = -1;
    for (int i = 0;i < MAX_SIZE;i++){
        s -> data[i] = 0;
    }
}

// 判断栈是否为空
int isStackEmpty(Stack *s) {
    if(s -> top == -1){
        return 1;
    }
    return 0;
}

// 判断栈是否已满
int isStackFull(Stack *s) {
    if(s -> top == MAX_SIZE - 1){
        return 1;
    }
    return 0;
}

// 入栈操作
void push(Stack *s, int value) {
    if (isStackFull(s) == 1){
        return;
    }
    s -> data[++(s -> top)] = value;
}

// 出栈操作
int pop(Stack *s) {
    if (isStackEmpty(s) == 1){
        return -1;
    }
    return s->data[(s->top)--];
}

// 获取栈顶元素
int peek(Stack *s) {
    if (!isStackEmpty(s)){
        return s->data[s->top];
    }
    return -1;
}

// 定义队列结构体
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

// 初始化队列
void initQueue(Queue *q) {
    q -> front = 0;
    q -> rear = 0;
    for (int i = 0;i < MAX_SIZE;i++){
        q -> data[i] = 0;
    }
}

// 判断队列是否为空
int isQueueEmpty(Queue *q) {
    if (q -> front == q -> rear){
        return 1;
    }
    return 0;
}

// 判断队列是否已满
int isQueueFull(Queue *q) {
    if (q -> rear == MAX_SIZE - 1){
        return 1;
    }
    return 0;
}

// 入队操作
void enqueue(Queue *q, int value) {
    if (isQueueFull(q) != 1){
        q -> data[q -> rear++] = value;
    }
}

// 出队操作
int dequeue(Queue *q) {
    if (isQueueEmpty(q) != 1){
        return q -> data[q -> front++];
    }
}

// 获取队首元素
int front(Queue *q) {
    return q -> data[q -> front];
}

void input_data(Stack *s1, Stack *s2) {
    int num = 0;
    char ch;
    while (scanf("%d",&num) == 1){
        push(s1, num);
        ch = getchar();
        if (ch == '\n') break;
    }
    while (scanf("%d",&num) == 1){
        push(s2, num);
        ch = getchar();
        if (ch == '\n') break;
    }
}

void sort_data(Stack *s1, Stack *s2, Queue *q) {
    int num = 0;
    while (!isStackEmpty(s1) && !isStackEmpty(s2) && !isQueueFull(q))
        if (s1 -> data[s1 -> top] < s2 -> data[s2 -> top]){
            num = pop(s1);
            enqueue(q, num);
        }else{
            num = pop(s2);
            enqueue(q, num);
        }
    while (isStackEmpty(s1) || isStackEmpty(s2)){
        if (isStackEmpty(s1) && isStackEmpty(s2)){
            break;
        }
        if (isStackEmpty(s1)){
            num = pop(s2);
            enqueue(q, num);
        }else{
            num = pop(s1);
            enqueue(q, num);
        }
    }
    
}

void output_data(Queue *q) {
    int out = 0;
    while (!isQueueEmpty(q)){
        out = dequeue(q);
        printf("%d ",out);
    }
    
}

int main() {
    Stack s1, s2;
    Queue q;
    initStack(&s1);
    initStack(&s2);
    initQueue(&q); 

    input_data(&s1, &s2);
    sort_data(&s1, &s2, &q);
    output_data(&q);
    
    return 0;
}