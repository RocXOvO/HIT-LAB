#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int *data;
    int top;
    int capacity;
}Stack;

typedef struct quene{
    int *data;
    int front;
    int last;
    int capacity;
}Quene;

/**Create a new Stack.
 * capacity means the capacity.
 */
Stack* CreatStack(int capacity){
    Stack *newStack = malloc(sizeof(Stack));
    if (newStack == NULL){
        printf("内存分配错误");
        exit(1);
    }
    newStack -> top = -1;
    newStack -> capacity = capacity;
    newStack -> data = malloc(newStack -> capacity * sizeof(int));
    if (newStack -> data == NULL){
        printf("内存分配错误");
        exit(1);
    }
    return newStack;
}

int isEmpty(Stack *stack){
    return stack -> top == -1;
}

int pushStack(Stack *stack, int value){
    if (stack -> top > stack -> capacity -1){
        printf("栈满");
        return 0;
    }
    stack -> data[++stack -> top] == value;
    return value;
}

int popStack(Stack *stack){
    if(isEmpty){
        printf("栈空");
        return 0;
    }
    int value = stack -> data[stack -> top--];
    return value;
}

Quene* CreateQuene(int capacity){
    Quene *newQuene = malloc(sizeof(Quene));  
    if (newQuene == NULL){
        prinf("内存分配错误");
        exit(1);
    }
    newQuene -> capacity = capacity;
    newQuene -> front = 0;
    newQuene -> last = capacity - 1;
    newQuene -> data = malloc(newQuene ->capacity * sizeof(int));
    if (newQuene -> data == NULL){
        prinf("内存分配错误");
        exit(1);
    }
}


int main(){
    return 0;
}