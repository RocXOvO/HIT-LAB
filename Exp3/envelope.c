#include <stdio.h>
#include <stdlib.h>

// 信封结构体
typedef struct {
    int width;
    int height;
} Envelope;

int maxEnvelopes(Envelope* envelopes, int n) {
    // 宽度从小到大排序，如果高度相同，把大的放前面。
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (envelopes[j].width > envelopes[j + 1].width 
                || envelopes[j].width == envelopes[j + 1].width 
                && envelopes[j].height < envelopes[j + 1].height) {
                Envelope tmp = envelopes[j];
                envelopes[j] = envelopes[j + 1];
                envelopes[j + 1] = tmp;
            }
        }
    }
    int *dp = malloc(sizeof(int) * n);
    int maxlen = 1;
    for (int i = 0; i < n; i++){
        dp[i] = 1;
        for (int j = 0; j < i; j++){
            if (envelopes[j].height < envelopes[i].height && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
        if (maxlen < dp[i]) maxlen = dp[i];
    }
    free(dp);
    return maxlen;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Envelope* envelopes = (Envelope*)malloc(n * sizeof(Envelope));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &envelopes[i].width, &envelopes[i].height);
    }
    
    int result = maxEnvelopes(envelopes, n);
    printf("%d\n", result);
    
    free(envelopes);
    return 0;
}