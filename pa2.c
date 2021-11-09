#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"
#include "pa2.h"

int main(int argc, char *argv[]){
    
    Tnode *root = NULL;
    
    if(strcmp("-e", argv[1])==0){
        //INFOR is incorrect format flag
        int isBST = 0, isHB = 0, height = 0, fileCheck = 0, INFOR = 0;
        root = Tree_Load_From_File(argv[2], &INFOR);

        //Check the input file validility
        if(root == NULL && INFOR == 0){
            fileCheck = -1;
            printf("Input file Error\n");
            return EXIT_FAILURE;
        }
        else if(INFOR == 1){
            fileCheck = 0;
            printf("Input format incorrect\n");
            return EXIT_FAILURE;
        }
        else{
            fileCheck = 1;
            printf("Input is good\n");
        }
        //print the tree
        Preorder(root);

        //Test BST
        isBST = Test_BST(root);
        if(isBST) printf("\nIt is BST\n");
        else printf("\nIt's not BST\n");

        //Test Height balance
        isHB = Test_HB(root, &height);
        if(isHB) printf("\nIt is Height Balance\n");
        else printf("\nIt's not Height Balance\n");
        
        return EXIT_SUCCESS;
    }

    if(strcmp("-b", argv[1])==0){
        //build the tree
        root = Build_Tree_From_File(argv[2]);

        //print the tree
        //Preorder2(root);
    }
}