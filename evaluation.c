#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"

//Global
int intCount, count=0;

static Tnode *Create_Node(int val){
    Tnode *node = malloc(sizeof(*node));
    if(node == NULL){
        fprintf(stderr, "Can't get momory\n");
    }

    node -> key = val;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

int i=0;
static Tnode *buildBT(char *keyArray, char *childarray){
    if(keyArray == NULL || childarray == NULL){
        return NULL;
    }

    //create a node
    Tnode *node = Create_Node(keyArray[i]);

    //use childarray determine the number of the child
    if(childarray[i] == 3){
        i+=1;
        node->left = buildBT(keyArray, childarray);
        i+=1;
        node->right = buildBT(keyArray, childarray);
    }
    if(childarray[i] == 2){
        i+=1;
        node->left = buildBT(keyArray, childarray);
    }
    if(childarray[i] == 1){
        i+=1;
        node-> right = buildBT(keyArray, childarray);
    }

    //return the node
    return node;
}

void Preorder(Tnode *node){
    if(node != NULL){
        printf("%d ", node->key);
        if(node->right != NULL && node->left != NULL){
            printf("3\n");
        }
        else if(node->right != NULL && node->left == NULL){
            printf("1\n");
        }
        else if(node->right == NULL && node->left != NULL){
            printf("2\n");
        }
        else{
            printf("0\n");
        }

        Preorder(node->left);
        Preorder(node->right);
    }
}


Tnode *Tree_Load_From_File(char *filename, int *INFOR){
    FILE *fp;
    int key, i=0;
    char op;
    char *keyArray, *childarray;
    Tnode *node;
    int fileSize;
    
    //open file
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        fclose(fp);
        return NULL;
    }
    
    //Get the size of the file
    fseek(fp, 0, SEEK_END);    //move to the end of the file
    fileSize = ftell(fp);      //return end postion
    rewind(fp);                //back to the head of the file

    //calculate how many the size for an array to store int
    //ex: 10 integer the fileSize will be 50 (4+1 = int + char)
    //    The size for an array to store 10 int is 40, 
    intCount = 4*(fileSize/5);
    keyArray = (char *)malloc(intCount); //Assign memory
    childarray = (char *)malloc(intCount/4);
    if(keyArray == NULL|| childarray == NULL || fileSize%5 != 0){
        *INFOR = 1;
        fclose(fp);
        free(keyArray);
        free(childarray);
        return NULL;
    }
    printf("n = %d\n", intCount);

    while(fread(&key, sizeof(int), 1, fp)){
        //read int in the while loop : key = int
        //read char from the file : op = char
        fread(&op, sizeof(char), 1, fp);
        if(op>3 || op<0) {
            *INFOR = 1;
            free(keyArray);
            free(childarray);
            fclose(fp);
            return NULL;
        }
        childarray[i] = op;
        keyArray[i] = key;
        i++;
    }

    //node = constructBST(keyArray,0, (intCount/sizeof(int))-1);
    node = buildBT(keyArray, childarray);
    free(keyArray);
    free(childarray);
    fclose(fp);
    return node;  
}

static void inorder(Tnode *root, char *array){
    if(root == NULL){
        return;
    }
    inorder(root->left, array);
    array[count] = root->key;
    count++;
    inorder(root->right, array);
}

int Test_BST(Tnode *root){
    int left;
    char *arr;

    arr = (char *)malloc(intCount); //Assign memory 4*key = intCount

    //inorder traversal to create a sorted array
    count = 0;
    inorder(root, arr);

    //check if the array sorted
    for(int i=1; i<intCount/4; i++){
        printf("%d ", arr[i]);
        if(arr[i] < arr[i-1]){
            free(arr);
            return 0;
        }
    }
    free(arr);
    return 1;
}

int Test_HB(Tnode *node, int *height){

    //lh = height of left subtree
    //rh = height of right subtree
    int rh=0, lh=0;

    //lb, rb will = 1 when left or right tree is balance
    int lb=0, rb=0;

    //return true if it is an empty tree
    if(node == NULL){
        *height = 0;
        return 1;
    }

    //store the height of left and right subtree into rb and lb
    lb = Test_HB(node->left, &lh);
    rb = Test_HB(node->right, &rh);

    //assign the height of the current node
    if(lh > rh){
        *height = lh + 1;
    }
    else {
        *height = rh + 1;
    }

    //determine wheter it is balance
    if(abs(lh-rh) >= 2){
        return 0;
    }
    else{
        return lb && rb;
    }
}


