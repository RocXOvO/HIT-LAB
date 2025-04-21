#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int value;
    int time;
}herb;

int dynamicCollect(herb *s, int numsType, int totalTime) {
    for (int i = 0; i < numsType; i++){
        scanf("%d %d",&s[i].time, &s[i].value);
    }
    int *dp = malloc(sizeof(int) * (totalTime + 1));
    for (int i = 0; i < totalTime; i++) dp[i] = 0;
    for (int i = 0; i < numsType; i++) {
        int ti = s[i].time; 
        int vi = s[i].value;
        for (int t = ti; t <= totalTime; t++) {
            if (dp[t] < dp[t - ti] + vi) {
                dp[t] = dp[t - ti] + vi;
            }
        }

    }
    int res = dp[totalTime];
    free(dp);
    return res;
}
int main(){
    int totalTime;
    int numsType;
    scanf("%d %d", &totalTime, &numsType);
    herb *s = malloc(sizeof(herb) * numsType);
    int res = dynamicCollect(s, numsType, totalTime);
    printf("%d",res);
    free(s);
    return 0;
}