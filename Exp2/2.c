#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

TreeNode* buildTree(char** input, int n) {
    if (n == 0 || strcmp(input[0], "null")== 0) return NULL;

    TreeNode** queue = (TreeNode**)malloc(n * sizeof(TreeNode*));
    TreeNode* root = newNode(atoi(input[0]));
    queue[0] = root;
    int front = 0, rear = 1;

    for (int i = 1; i < n; i += 2) {
        TreeNode* current = queue[front++];

        if (strcmp(input[i], "null")!= 0) {
            current->left = newNode(atoi(input[i]));
            queue[rear++] = current->left;
        }

        if (i + 1 < n && strcmp(input[i + 1], "null")!= 0) {
            current->right = newNode(atoi(input[i + 1]));
            queue[rear++] = current->right;
        }
    }

    free(queue);
    return root;
}
int max(int a,int b){
    return a > b ? a : b;
}

int maxPathSumHelper(TreeNode * node, int *maxNum){
    if (node == NULL){
        return 0;
    }
    //与0做比较，当前节点儿子的单边贡献是否取（没包括自己），如果是负数就忽视，取0，如果是非负数就取前者。
    //假如一个节点的左子树是负数，其后面子树很大，也会递归到！
    int leftGain = max(maxPathSumHelper(node->left, maxNum), 0);
    int rightGain = max(maxPathSumHelper(node->right, maxNum), 0);

    //全局路径（包括了自己）
    int pathNum = node->val + leftGain + rightGain;

    *maxNum = max(pathNum, *maxNum);
    //找到该节点最优的单边和
    return node->val + max(leftGain, rightGain);
}

int maxPathSum(TreeNode* root) {
    int maxnum = INT_MIN;
    maxPathSumHelper(root, &maxnum);
    return maxnum;
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char input[1000];
    fgets(input, sizeof(input), stdin);
    char* token = strtok(input, " \n");
    char* inputs[100];
    int n = 0;
    while (token != NULL) {
        inputs[n++] = token;
        token = strtok(NULL, " \n");
    }
    TreeNode* root = buildTree(inputs, n);

    int result = maxPathSum(root);
    printf("%d\n", result);

    freeTree(root);

    return 0;
}