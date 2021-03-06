#include <stdio.h>
#include "hbt.h"

//Evaluation part
void Preorder(Tnode *node); //print the tree for debugging
Tnode *Tree_Load_From_File(char *filename, int *INFOR);
int Test_BST(Tnode *root);
int Test_HB(Tnode *node, int *height);


//Build part
Tnode *Build_Tree_From_File(char *filename, int *INFOR2);
void Preorder2(Tnode *node);
int Tree_save_to_file(char *filename, Tnode *node);