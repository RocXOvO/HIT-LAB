#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    int color;
    //color 0代表蓝色，1代表红色
 };
static int cnt = 0;
/******************* 染色 *******************/
void getNumber(struct TreeNode* root, int** ops, int opsSize){
    // TODO
    if (root == NULL){
        return;
    }
    root->color = 0;
    //染色，对每个节点一直循环，直到其ops最后一次操作，得到他应该有的颜色
    for (int i = 0; i < opsSize; i++){
        if (ops[i][0] == 0 && root->val >= ops[i][1] && root->val <= ops[i][2]){
            root->color = 0;
        } else if (ops[i][0] == 1 && root->val >= ops[i][1] && root->val <= ops[i][2]){
            root->color = 1;
        }
    }
    //得到染色个数
    if (root->color == 1){
        cnt += 1;
    }
    //递归，下一个节点继续染色
    getNumber(root->left, ops, opsSize);
    getNumber(root->right,ops, opsSize);
}
/*****************************************************/

/******************* 读取数据 *******************/
struct TreeNode* newTreeNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

struct TreeNode* constructTree(int size) {
    if (size == 0)
        return NULL;

    struct TreeNode** nodes = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));
    for (int i = 0; i < size; i++) {
        int val;
        scanf("%d", &val);
        if (val == -1) {
            nodes[i] = NULL;
        } else {
            nodes[i] = newTreeNode(val);
        }
    }

    for (int i = 0, j = 1; j < size; i++) {
        if (nodes[i] != NULL) {
            if (j < size)
                nodes[i]->left = nodes[j++];
            if (j < size)
                nodes[i]->right = nodes[j++];
        }
    }

    struct TreeNode* root = nodes[0];
    free(nodes);
    return root;
}

void readOps(int ***ops, int *opsSize) {
    scanf("%d", opsSize);

    *ops = (int **)malloc(*opsSize * sizeof(int *));
    while(getchar() != '[') {}
    for (int i = 0; i < *opsSize; i++) {
        (*ops)[i] = (int *)malloc(3 * sizeof(int));
        while(getchar() != '[') {}
        for (int j = 0; j < 3; j++) {
            scanf("%d", &((*ops)[i][j]));
        }
        while(getchar() != ']') {}
    }
}
/*****************************************************/

int main() {
    int nodeSize;
    scanf("%d", &nodeSize);
    struct TreeNode* root = constructTree(nodeSize);
    int **ops, opsSize;
    readOps(&ops, &opsSize);
    getNumber(root, ops, opsSize);
    printf("%d\n",cnt);
    return 0;
}