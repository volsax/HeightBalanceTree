#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"
#include "pa2.h"

void deallocate (Tnode* node)
{
    if(node==NULL)
        return;

    deallocate(node->right);
    deallocate(node->left);

    free(node);
}

int main(int argc, char *argv[]){
    
    Tnode *root = NULL;
    
    if(strcmp("-e", argv[1])==0){
        //INFOR is incorrect format flag
        int isBST = 0, isHB = 0, height = 0, fileCheck = 0, INFOR = 0;
        root = Tree_Load_From_File(argv[2], &INFOR);

        //Check the input file validility
        if(root == NULL && INFOR == 0){
            fileCheck = -1; //input file error
            fprintf(stdout, "%d,%d,%d\n", fileCheck, isBST, isHB);
            return EXIT_FAILURE;
        }
        else if(INFOR == 1){
            fileCheck = 0; //input format incorrect
            fprintf(stdout, "%d,%d,%d\n", fileCheck, isBST, isHB);
            return EXIT_FAILURE;
        }
        else{
            fileCheck = 1;
        }

        //Test BST
        isBST = Test_BST(root);

        //Test Height balance
        isHB = Test_HB(root, &height);
        
        fprintf(stdout, "%d,%d,%d\n", fileCheck, isBST, isHB);
        deallocate(root); //free the tree
        return EXIT_SUCCESS;
    }

    else if(strcmp("-b", argv[1])==0){
        int fileCheck2;
        int INFOR2 = 0; //INFOR2 is the incorrect input format flag 
        //build the tree
        root = Build_Tree_From_File(argv[2], &INFOR2);

        //return EXIT_FAILURE if the file cannot be opened
        if(root == NULL && INFOR2 == -1){
            fileCheck2 = -1;
            fprintf(stdout, "%d\n", fileCheck2);
            return EXIT_FAILURE;
        }
        Tree_save_to_file(argv[3], root);
        if(INFOR2 == 1){
            fileCheck2 = 0;
            fprintf(stdout, "%d\n", fileCheck2);
            deallocate(root); //free the tree
            return EXIT_FAILURE;
        }
        else {
            fileCheck2 = 1;
            fprintf(stdout, "%d\n", fileCheck2);
            deallocate(root); //free the tree
            return EXIT_SUCCESS;
        }
    }

    else{
        printf("Wrong Command!!\n");
        return EXIT_FAILURE;
    }
}