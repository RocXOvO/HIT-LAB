#include <stdio.h>
#include <stdlib.h>

/******************* 排序 *******************/
// 这个res_num[i]
void sortJumbled(int *mapping, int *nums, int numsSize) {
    typedef struct{
        int num;// 原值
        int mapped;// 存映射后的值
        int index;// 存原来的顺序
    } numMap;
    numMap *arr = malloc(numsSize * sizeof(numMap));
    for (int i = 0; i < numsSize; i++){
        int n = nums[i];
        int mapped = 0,base = 1;
        if (n == 0) {
            mapped = mapping[0];
        } else {
            int tmp = n;
            while (tmp > 0) {
                int cur = tmp % 10;// 取当前数字的个位。
                mapped += mapping[cur] * base;
                tmp = tmp / 10;
                base = base * 10;
            }
        }
        arr[i].num = nums[i];
        arr[i].mapped = mapped; 
        arr[i].index = i;
    }

    // index 区分大小。从小到大是非递减数列
    for (int i = 0; i < numsSize; i++){
        for (int j = i + 1; j < numsSize;j++){
            if (arr[i].mapped > arr[j].mapped || arr[i].mapped == arr[j].mapped && arr[i].index > arr[j].index) {
                numMap tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }


    
    for(int i = 0; i < numsSize; i++){
        printf("%d ", arr[i].num);
    }   
    printf("\n");
}
/*****************************************************/

/******************* 读取数据 *******************/
void readInput(int **mapping, int **nums, int *numsSize) {
    scanf("%d", numsSize);

    *mapping = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        scanf("%d", &((*mapping)[i]));
    }

    *nums = (int *)malloc((*numsSize) * sizeof(int));
    for (int i = 0; i < *numsSize; i++) {
        scanf("%d", &((*nums)[i]));
    }
}
/*****************************************************/

int main() {
    int *mapping, *nums, numsSize;
    readInput(&mapping, &nums, &numsSize);
    sortJumbled(mapping, nums, numsSize);

    return 0;
}