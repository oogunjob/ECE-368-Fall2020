#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "pa4.h"

void Evaluate_Tree(FILE * file){
  fseek(file, 0, SEEK_END); // seeks the the end of the file
  int size = ftell(file); // returns the size of the file
  
  // if the file is empty, print zeros to standard output and return
  if(size == 0){
    fprintf(stdout, "0,0,0\n");
    return;
  }

  int label; // label read from the file
  int nodeLabel; // the label that will be assigned to each node

  char balance; // balance read from the file
  int nodeBalance; // the balance that will be assigned to each node
	
  size = 0; // number of nodes in the binary search tree
	
  fseek(file, 0, SEEK_SET); // returns to beginning of file
	
  do{
    nodeLabel = fread(&label, sizeof(int), 1, file); // loads the label of the node to nodeLabel variable
    
    // when the end of the file is reached, break from the looping through file
    if(feof(file)){
      break;
	  }

    // if the label of the node is less than or greater than 1, print zeros to standard output and return to main function
	  else if (nodeLabel < 1 || nodeLabel > 1){
	    fprintf(stdout, "0,0,0\n");
      return;
    }
        
    nodeBalance = fread(&balance, sizeof(char), 1, file); // loads the balance of the node to nodeBalance variable
		
    // if node balance is less than or greater than 1, print zeros to standard output and return to main function
    if(nodeBalance < 1 || nodeBalance > 1){
      fprintf(stdout, "0,0,0\n");
	    return;
  	}

    // if the balance is less than 0 or greater than 3, print zeros to standard output and return to main function
	  else if(balance < 0 || balance > 3){
	    fprintf(stdout, "0,0,0\n");
	    return;
	  }

	  size++; // counts how many nodes are in the binary search tree

    // when the end of the file is reached, break from looping through file
	  if(feof(file)){
      break;
	  }

  }while(1);

  fseek(file, 0, SEEK_SET); // returns to start of the file

  int * keys = malloc(size * sizeof(int)); // allocates space for keys for nodes
  char * children = malloc(size * sizeof(char)); // allocates space for balances for nodes

  int index; // loop control variable
	
  // loads keys and balance from file into seperate arrays for storage
  for(index = 0; index < size; index++){
	  (void)(fread(&keys[index], sizeof(int), 1, file) + 1);
    (void)(fread(&children[index], sizeof(char), 1, file) + 1); 
  }

  index = 0;

  Tnode * root = Build_Tree(keys, children, size, &index); // builds the binary search tree given keys and children nodes
	
  // print to standard output required integers based on strucutre of binary tree
  if(root){
    fprintf(stdout, "1,%d,%d\n", BST(root), HBT(root));
	  deleteEvaluation(root); // deletes the binary tree
  }
	
  // frees allocated space of keys and children
  free(keys);
  free(children);
	
  return;
}

Tnode *Build_Tree(int *keys, char *children, int size, int *index){
  if(size != (*index))
  {
    Tnode * node = malloc(sizeof(*node)); // creates new node
	
	  // assigns attributes of key and balance to node
	  node -> key = keys[*index];
	  node -> balance = 0;

    // assigns NULL pointers to left and right nodes of node
	  node -> left = NULL;
	  node -> right = NULL;
	
	  int prevIndex = *index;
	  *index += 1; // increments the index by 1
		
	  if((children[prevIndex] == 2) || (children[prevIndex] == 3)){
	    node -> left = Build_Tree(keys, children, size, index);
	  }
	
	  if((children[prevIndex] == 1) || (children[prevIndex] == 3)){
	    node -> right = Build_Tree(keys, children, size, index);
	  }

    return node; // return the node allocated
  }
	
  return NULL; // returns NULL pointer if size is equal to the index
}

int BST(Tnode * node){
  // if the node is not NULL, perform proper evaluation to determine if tree is a binary search tree
  if(node){
    if(node -> right && (node -> key > (node -> right -> key))){
      return 0;
	  }
		
	  else if(node -> left && (node -> key < (node -> left -> key))){
	    return 0;
	  }
		
	  else if((!!!BST(node -> right))){
	    return 0;
	  }
	
	  else if (!!!BST(node -> left)){
	    return 0;
	  }
  }
  
  return 1; 
}

int HBT(Tnode *node){
  int evaluation = 1; // determination of wheter tree is height balanced or not
  Find_Balance(node, &evaluation); // computes the balance of the binary search tree
  
  return evaluation;
}

int Find_Balance(Tnode *node, int *evaluation){
  int balance = 0; // balance of the binary search tree
  
  if(node){
    int rightSide = Find_Balance(node -> right, evaluation); // computes balance of the right side of binary tree
	  int leftSide = Find_Balance(node -> left, evaluation); // computes the balance of the left side of the binary tree

	  node -> balance = rightSide - leftSide; // finds the balance
	
	  if(node -> balance != 1 && node -> balance != 0 && node -> balance != -1){
      *evaluation = 0;
	  }
	
	  // computes what the balance is supposed to be
	  if(rightSide > leftSide){
	    balance = rightSide;
	  }
	
	  else{
      balance = leftSide;
	  }
		
	  balance += 1; // increments the size of the balance
  }
	
  return balance;
}

void deleteEvaluation(Tnode *node){
  // if node is empty, return
  if(node == NULL){
    return;
  }

  deleteEvaluation(node -> left); // traverses left side of binary tree
  deleteEvaluation(node -> right); // traverses right side of binary tree
  
  free(node); // frees allocated space of node
  
  return;
}