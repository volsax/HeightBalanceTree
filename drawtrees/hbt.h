#ifndef __HBT_TREE__
#define __HBT_TREE__
#include<stdlib.h>

#define DEPTH 4

typedef struct _Tnode {
   int key;
   int height;
   struct _Tnode *left;
   struct _Tnode *right;
} Tnode;

static inline Tnode* buildTree(int depth, int value) {
    
    Tnode* root;
    root = malloc(sizeof(Tnode));
    root->key = value;
    root->left = NULL;
    root->right= NULL;
    if (depth < DEPTH) {
        root->left = buildTree(depth + 1, value/(DEPTH+1-depth));
        root->right= buildTree(depth + 1, value*(DEPTH+1-depth));
    }
    return root;
}

static inline void freeTree(Tnode *root)
{
    if (root->left != NULL) freeTree(root->left);
    if (root->right != NULL) freeTree(root->right);
    free(root);
}

#endif
