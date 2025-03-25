#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct CardAList{
    int *elem;
    int length;
    int listsize;
} AList;

//initialize the AList.
AList *CreateCardAList(int n){
    AList *L = malloc(sizeof(AList));
    if (L == NULL){
        printf("内存分配错误");
        exit(1);
    }
    L -> listsize = 1;
    L -> length = 0;
    L -> elem = (int*)malloc(L -> listsize * sizeof(int));
    if (L -> elem){
        printf("内存分配错误");
        free(L);
        exit(1);
    }
    L -> elem[0] = 0;
    for (int i = 1;i < n; i++){
        L -> elem[i] = 1;
    }
    return L;
}

//imitate flop the cards.
//**L just use the return of former function.
void flopCard(int n){
    AList *L = CreateCardAList(n);
    for (int k = 2;k < L -> listsize;k++){
        for (int i = 1;i * k < L -> length;i++){
            int index = k * i;
            reverseElem(index, L);
        }
    }
}

//reverse the Elem.
void reverseElem(int index, AList *L){
    int *Elem = &L -> elem[index];
    if (*Elem == 1){
        *Elem = 0;
    }else if (Elem == 0){
        *Elem = 1;
    }
}

int main(){
    return 0;
}