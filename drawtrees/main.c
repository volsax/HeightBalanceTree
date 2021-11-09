#include <graphviz/gvc.h>
#include "hbt.h"

Agraph_t* createGraph()
{
    Agraph_t *g;
    g = agopen("G", Agdirected, NULL);

    Agnode_t *n;
    n = agnode(g, "2", TRUE);
    n = agnode(g, "1", TRUE);
    n = agnode(g, "3", TRUE);

    Agedge_t *e;
    agedge(g, agnode(g, "2", FALSE), agnode(g, "3", FALSE), NULL, TRUE);
    agedge(g, agnode(g, "2", FALSE), agnode(g, "1", FALSE), NULL, TRUE);

    return g;
    
}

Agraph_t* createTree(Tnode *root, Agraph_t *G) 
{
    if (G == NULL)
        G = agopen("G", Agdirected, NULL);

    if (!root)
        return G;

    char buffer[200];
    Agnode_t *n;
    sprintf(buffer, "%d %p", root->key, root);
    n = agnode(G, buffer, TRUE);

    createTree(root->left, G);
    createTree(root->right, G);

    if (root->left) {
        sprintf(buffer, "%d %p", root->left->key, root->left);
        agedge(G, n, agnode(G, buffer, FALSE), NULL, TRUE);
    }

    if (root->right) {
        sprintf(buffer, "%d %p", root->right->key, root->right);
        agedge(G, n, agnode(G, buffer, FALSE), NULL, TRUE);
    }

    return G;

}

void drawGraph(Agraph_t* G, GVC_t* gvc) {
    fprintf(stdout, "Printing graph to out.png\n");
    gvRenderFilename(gvc, G, "png", "out.png");
}

int main(void) 
{
    Agraph_t* G;
    GVC_t* gvc;
    gvc = gvContext(); /* library function */
    Tnode* root = buildTree(0, 1500);
    //G = createGraph ();
    G = createTree(root, NULL);
    gvLayout (gvc, G, "dot"); /* library function */
    drawGraph(G, gvc);
    gvFreeLayout(gvc, G); /* library function */
    agclose (G); /* library function */
    gvFreeContext(gvc);
    freeTree(root);
}
