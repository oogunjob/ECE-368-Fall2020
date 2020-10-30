#ifndef __PA_HELPER__
#define __PA_HELPER__

Tnode *Build_Tree(int *keys, char *children, int size, int *index);
Tnode *Build_AVL_Tree(FILE *file);

Tnode *insert(Tnode *node, int key, char *balance);
Tnode *delete(Tnode *node, int key, char *balance);

Tnode *Rotate_Right(Tnode *node);
Tnode *Rotate_Left(Tnode *node);
Tnode *Rotate_Right_Left(Tnode *node);
Tnode *Rotate_Left_Right(Tnode *node);

void Evaluate_Tree(FILE *file);
void deleteTree(Tnode *node);
void deleteEvaluation(Tnode *node);

void Print_Binary_Tree(Tnode *node, FILE *file);

int BST(Tnode *node);
int HBT(Tnode *node);
int Find_Balance(Tnode *node, int *evaluation);

#endif