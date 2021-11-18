#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"

static int get_height(Tnode *node)
{
    if (node == NULL)
        return 0;
    else
        return node->height;
}

static int get_max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

static Tnode *get_predecessor(Tnode *node)
{
    //trverse down the right side of leftsubtree
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

void Preorder2(Tnode *node)
{
    if (node != NULL)
    {
        printf("%d ", node->key);
        if (node->right != NULL && node->left != NULL)
        {
            printf("3\n");
        }
        else if (node->right != NULL && node->left == NULL)
        {
            printf("1\n");
        }
        else if (node->right == NULL && node->left != NULL)
        {
            printf("2\n");
        }
        else
        {
            printf("0\n");
        }

        Preorder2(node->left);
        Preorder2(node->right);
    }
}

static Tnode *Create_Node(int val)
{
    Tnode *node = (Tnode *)malloc(sizeof(Tnode));
    if (node == NULL)
    {
        fprintf(stderr, "Can't get momory\n");
    }

    node->key = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

static Tnode *Right_Rotate(Tnode *old)
{
    //right rotate
    Tnode *new = old->left;
    old->left = new->right;
    new->right = old;

    //update the height of the node
    old->height = get_max(get_height(old->left), get_height(old->right)) + 1;
    new->height = get_max(get_height(new->left), get_height(new->right)) + 1;
    return new;
}

static Tnode *Left_Rotate(Tnode *old)
{
    //left rotate
    Tnode *new = old->right;
    old->right = new->left;
    new->left = old;

    //update the height of the node
    old->height = get_max(get_height(old->left), get_height(old->right)) + 1;
    new->height = get_max(get_height(new->left), get_height(new->right)) + 1;
    return new;
}

static Tnode *insertion(Tnode *node, int val)
{
    if (node == NULL)
    {
        return Create_Node(val);
    }

    //Do the normal insertion of the BST
    if (val <= node->key)
    {
        node->left = insertion(node->left, val);
    }
    else
    {
        node->right = insertion(node->right, val);
    }

    //update the height of the node
    int leftHeight = get_height(node->left);
    int rightHeight = get_height(node->right);
    node->height = get_max(leftHeight, rightHeight) + 1;

    //get the balance of the node
    int balance;
    if (node == NULL)
    {
        balance = 0;
    }
    else
        balance = leftHeight - rightHeight;

    //Start rotate if the tree is not balance
    //case 1 left left
    if (balance > 1 && val <= node->left->key)
    {
        return Right_Rotate(node);
    }

    //case2 right right
    if (balance < -1 && val > node->right->key)
    {
        return Left_Rotate(node);
    }

    //case3 left right
    if (balance > 1 && val > node->left->key)
    {
        node->left = Left_Rotate(node->left);
        return Right_Rotate(node);
    }

    //case4 right left
    if (balance < -1 && (val < node->right->key))
    {
        node->right = Right_Rotate(node->right);
        return Left_Rotate(node);
    }

    return node;
}

Tnode *Delete(Tnode *node, int val)
{
    //DO the BST deletion
    if (node == NULL)
    {
        return node;
    }

    if (val < node->key)
    {
        node->left = Delete(node->left, val);
    }
    else if (val > node->key)
    {
        node->right = Delete(node->right, val);
    }
    //find the same node
    else
    {
        //case 1: one or no child
        if (node->right == NULL || node->left == NULL)
        {
            Tnode *temp = NULL;
            if (node->right != NULL)
                temp = node->right;
            if (node->left != NULL)
                temp = node->left;

            //detect the no child case
            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;
            free(temp);
        }

        //case 2: two children
        else
        {
            Tnode *temp = get_predecessor(node->left);
            node->key = temp->key;
            node->left = Delete(node->left, temp->key);
            //free(temp);
        }
    }
    //If node is the only node after deletion, node = NULL
    if (node == NULL)
        return node;

    //Update the height as insertion part
    int leftHeight = get_height(node->left);
    int rightHeight = get_height(node->right);
    node->height = get_max(leftHeight, rightHeight) + 1;

    //get the balance of the node
    int balance;
    if (node == NULL)
    {
        balance = 0;
    }
    else
        balance = leftHeight - rightHeight;

    //Start rotate if the tree is not balance
    //case 1 left left
    if (balance > 1 && val <= node->left->key)
    {
        return Right_Rotate(node);
    }

    //case2 right right
    if (balance < -1 && val > node->right->key)
    {
        return Left_Rotate(node);
    }

    //case3 left right
    if (balance > 1 && val > node->left->key)
    {
        node->left = Left_Rotate(node->left);
        return Right_Rotate(node);
    }

    //case4 right left
    if (balance < -1 && val < node->right->key)
    {
        node->right = Right_Rotate(node->right);
        return Left_Rotate(node);
    }
    return node;
}

Tnode *Build_Tree_From_File(char *filename, int *INFOR2)
{
    FILE *fp;
    char op;
    int key;
    Tnode *node = NULL;

    //open file
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        fclose(fp);
        return NULL;
    }

    //Start reading file
    while (fread(&key, sizeof(int), 1, fp))
    {
        //read the operation and key
        fread(&op, sizeof(char), 1, fp);

        //start building tree
        if (op == 'i')
        {
            fprintf(stdout, "Insert %d\n", key);
            node = insertion(node, key);
            Preorder2(node);
        }
        else if (op == 'd')
        {
            fprintf(stdout, "Delete %d\n", key);
            node = Delete(node, key);
            Preorder2(node);
        }
        else
        {
            //input format incorrect
            //return node
            *INFOR2 = 1;
            fclose(fp);
            return node;
        }
    }
    fclose(fp);
    return node;
}

int Preorder_Write(Tnode *node, FILE *fp, int count){
    int op;
    if(node != NULL){
        count += fwrite(&node->key, sizeof(int), 1, fp);
        if(node->right != NULL && node->left != NULL){
            op = 3;
            count += fwrite(&op, sizeof(char), 1, fp);
        }
        else if(node->right != NULL && node->left == NULL){
            op = 1;
            count += fwrite(&op, sizeof(char), 1, fp);
        }
        else if(node->right == NULL && node->left != NULL){
            op = 2;
            count += fwrite(&op, sizeof(char), 1, fp);
        }
        else{
            op = 0;
            count += fwrite(&op, sizeof(char), 1, fp);
        }
        Preorder_Write(node->left, fp, count);
        Preorder_Write(node->right, fp, count);
    }
    return count;
}

int Tree_save_to_file(char *filename, Tnode *node){
    FILE *fp;
    int count = 0;

    fp = fopen(filename, "wb");
    if(fp == NULL){
        fclose(fp);
        return 0;
    }
    count = Preorder_Write(node, fp, count);
    fclose(fp);
    return count;
}

