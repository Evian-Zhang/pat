#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

struct Node {
    int value;
    Node *lchild;
    Node *rchild;
};

int n;
int *post;
int *in;

Node *createTree(int postL, int postR, int inL, int inR) {
    if (postL > postR) {
        return NULL;
    }

    int rootPost = postR;
    int rootIn = inL;
    for (rootIn = inL; rootIn < inR; rootIn++) {
        if (in[rootIn] == post[rootPost]) {
            break;
        }
    }
    int lchildRootPost = rootPost - 1 - (inR - rootIn);
    int rchildRootPost = rootPost - 1;
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = post[rootPost];
    node->lchild = createTree(postL, lchildRootPost, inL, rootIn - 1);
    node->rchild = createTree(lchildRootPost + 1, rchildRootPost, rootIn + 1, inR);

    return node;
}



int main() {
    scanf("%d", &n);
    post = (int *)malloc(n * sizeof(int));
    in = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", post + i);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", in + i);
    }
    Node *root = createTree(0, n - 1, 0, n - 1);
    queue<Node *> levelOrder;
    printf("%d", root->value);
    if (root->lchild != NULL) {
        levelOrder.push(root->lchild);
    }
    if (root->rchild != NULL) {
        levelOrder.push(root->rchild);
    }
    while (!levelOrder.empty()) {
        Node *node = levelOrder.front();
        levelOrder.pop();
        printf(" %d", node->value);
        if (node->lchild != NULL) {
            levelOrder.push(node->lchild);
        }
        if (node->rchild != NULL) {
            levelOrder.push(node->rchild);
        }
    }

    return 0;
}