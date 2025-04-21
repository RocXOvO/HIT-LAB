#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* buildTreeHelper(int* preorder, int preStart, int preEnd,
    int* inorder, int inStart, int inEnd) {
        if (preStart > preEnd){
            return NULL;
        }
        int rootVal = preorder[preStart];
        struct TreeNode *root = (struct TreeNode*) malloc(sizeof(struct TreeNode));
        root->val = rootVal;
        root->left = NULL;
        root->right = NULL;

        //计算左子树节点个数.
        int inorderRootIndex = inStart;
        while (inStart <= inEnd && inorder[inorderRootIndex] != rootVal) {
            inorderRootIndex += 1;
        }
        //根左子树实际个数为:inorderRootIndex
        int leftNum = inorderRootIndex - inStart;

        root->left = buildTreeHelper(preorder, preStart + 1, preStart + leftNum, inorder, inStart, inorderRootIndex - 1);
        root->right = buildTreeHelper(preorder, preStart + leftNum + 1, preEnd, inorder, inorderRootIndex + 1, inEnd);
        return root;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    return buildTreeHelper(preorder, 0, preorderSize - 1, inorder,0 ,inorderSize - 1);
}

typedef struct{
    struct TreeNode **data;
    int front;
    int rear;
    int capacity;
} Quene;

Quene* initQuene(int capacity){
    Quene *quene = malloc(sizeof(Quene));
    if (quene == NULL) {
        exit(1);
    }
    quene->data = malloc(capacity * sizeof(struct TreeNode*));
    if (quene->data == NULL) {
        free(quene);
        return NULL;
    }
    return quene;
    quene->front = 0;
    quene->rear = 0;
    quene->capacity = capacity;
    return quene;
}

void enquene(Quene *quene,struct TreeNode* node){
    //不写resize操作，直接入队列；
    if (quene->rear == quene->capacity){
        return;
    }
    quene->data[quene->rear++] = node;
}

struct TreeNode* dequene(Quene *quene){
    if (quene->front == quene->rear){
        return NULL;
    }
    return quene->data[quene->front++];
}

void printTree(struct TreeNode* root) {
    if (root == NULL){
        printf("NULL");
        return;
    }
    Quene *treeQuene = initQuene(1000);
    enquene(treeQuene,root);

    while (treeQuene->front != treeQuene->rear){
        int levelsize = treeQuene->rear - treeQuene->front;
        for (int i = 0; i < levelsize; i++){
            struct TreeNode *node = dequene(treeQuene);
            if (node != NULL){
                printf("%d ",node->val);
                enquene(treeQuene,node->left);
                enquene(treeQuene,node->right);
            } else {
                printf("null ");
            }
        }
    }
    free(treeQuene->data);
    free(treeQuene);   
}


int main() {
    int preorderSize;
    scanf("%d", &preorderSize);
    int* preorder = (int*)malloc(preorderSize * sizeof(int));
    for (int i = 0; i < preorderSize; i++) {
        scanf("%d", &preorder[i]);
    }

    int inorderSize = preorderSize;
    int* inorder = (int*)malloc(inorderSize * sizeof(int));
    for (int i = 0; i < inorderSize; i++) {
        scanf("%d", &inorder[i]);
    }

    struct TreeNode* root = buildTree(preorder, preorderSize, inorder, inorderSize);
    printTree(root);

    return 0;
}