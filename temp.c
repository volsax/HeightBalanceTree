#include <stdio.h>
#include "hbt.h"


static Tnode *constructBST(char *keyArray, int start, int end){
    if(start > end){
        return NULL;
    }

    Tnode *node = Create_Node(keyArray[start]);

    //find the element larger than the cuurent value
    int i;
    for(i=start; i<=end; i++){
        if(keyArray[i] > node->key){
            break;
        }
    }
    //Construct the left and right sub tree
    node->left = constructBST(keyArray, start+1, i-1);
    node->right = constructBST(keyArray, i, end);
    return node;
}