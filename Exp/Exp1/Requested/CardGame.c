#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct {
    ElemType *elem;    // 空间基地址，空间存放纸牌正反面状态值,正/反分别用1/0表示
    int length;        // 存放纸牌数
    int listsize;      // 存放空间的容量
} SqList;  

SqList *CreateCardSqList(int n){
    SqList *L = malloc(sizeof(SqList));
    if (L == NULL){
        printf("内存分配错误");
        exit(1);
    }
    L -> listsize = n + 1;
    L -> length = n;
    L -> elem = (int*)malloc(L -> listsize * sizeof(int));
    if (L -> elem == NULL){
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

void flipCard(SqList *L){
    for (int k = 1;k < L -> length;k++){
        for (int i = 1;i * (k+1) < L -> length;i++){
            int index = (k + 1) * i;
            reverseElem(index, L);
        }
    }
}

void reverseElem(int index, SqList *L){
    int *Elem = &L -> elem[index];
    if(*Elem == 1){
        *Elem = 0;
    }else if (*Elem == 0){
        *Elem = 1;
    }
}

int CalculateNum(SqList *L){
    int cnt = 0;
    for (int i = 1;i < L -> length;i++){
        if(L -> elem[i] == 1){
            printf("%d ",i);
            cnt++;
        }
    }
    return cnt;
}

int main(){
    int cnt = 0;
    int num;
    scanf("%d",&num);
    SqList *CardList = CreateCardSqList(num);
    flipCard(CardList);
    cnt = CalculateNum(CardList);
    printf("\n%d",cnt);
}