#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int value;
    int time;
}herb;

int recursiveCollectHelper(herb *s, int totaltime, int numsType) {
    if (totaltime <= 0){
        return 0;
    }
    int maxvalue = 0;
    for (int i = 0; i < numsType ; i++) {
        if (totaltime >= s[i].time){
            int v = recursiveCollectHelper(s,totaltime - s[i].time, numsType) + s[i].value;
            if (v > maxvalue) maxvalue = v;
        }
    }
    return maxvalue;
}

int recursiveCollect(herb *s, int totaltime, int numsType) {
    return recursiveCollectHelper(s, totaltime, numsType);
}
int main(){
    int totalTime;
    int numsType;
    scanf("%d %d", &totalTime, &numsType);
    herb *s = malloc(sizeof(herb) * numsType);
    for (int i = 0; i < numsType; i++){
        scanf("%d %d",&s[i].time, &s[i].value);
    }
    int value = recursiveCollect(s, totalTime, numsType);
    printf("%d", value);
    free(s);
    return 0;
}