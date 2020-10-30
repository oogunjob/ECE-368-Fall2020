#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "pa4.h"

Tnode *Build_AVL_Tree(FILE * file){
  // checks the size of the file
  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  
  // if file is empty, print zero to standard output and return NULL to node node
  if(size == 0){
    fprintf(stdout, "0\n");
    return NULL;
  }

  fseek(file, 0, SEEK_SET); // returns to start of file
  
  int label; // label for each node
  int nodeLabel; // label assigned to the node

  char operation; // operation to be applied to the node
  int nodeOperation; // operation assigned to the node

  size = 0; // resets size to 0

  do{
    nodeLabel = fread(&label, sizeof(int), 1, file); // reads in the node label of each node
    
    // when end of file is met, break from iteration loop
    if(feof(file)){
      break;
    }
        
    if(nodeLabel != 1){
      fprintf(stdout, "0\n");
      return NULL;
    }
        
    nodeOperation = fread(&operation, sizeof(char), 1, file); // reads in the operation of each node
    if(nodeOperation != 1){
      fprintf(stdout, "0\n");
      return NULL;
    }
        
    // when end of file is met, break from iteration loop
    if(feof(file)){
      break;
    }
        
    size++; // increments number of nodes counted

  }while(1);

  Tnode * node = NULL;
  char insertBalance = 'n';
  char deleteBalance = 'n';

  fseek(file, 0, SEEK_SET); // returns to the start of the file

  for(int i = 0; i < size; i++){   
    (void)(fread(&label, sizeof(int), 1, file) + 1);
    (void)(fread(&operation, sizeof(char), 1, file) + 1);
		
    // delete node operation is performed
    if(operation == 'd'){
	  node = delete(node, label, &deleteBalance);
    }
        
    // insert node operation is performed
    else if(operation == 'i'){
	  node = insert(node, label, &insertBalance);
	}
		
    else{
	  printf("0\n");
      return node;
	}  
  }
	
  fprintf(stdout, "1\n");
  return node;

  return NULL;
}

Tnode *insert(Tnode *node, int key, char * balance){
  if(node == NULL){
    *balance = 'n';

    // allocates space for node
	Tnode *newNode = malloc(sizeof(*node));
	
    // assigns attributes to each new node
    newNode -> key = key;
    newNode -> balance = 0;
    
    newNode -> left = NULL;
    newNode -> right = NULL;
    
    
    if(newNode == NULL){
	  fprintf(stdout, "0\n");
	}
		
    return newNode; // returns new node
  }
	
  *balance = 'y';
  
  if(node -> key < key){
    node -> right = insert(node -> right, key, balance);
	
    if(*balance == 'n'){
      node -> balance -= 1; // subtracts from node's balance
	}
		
    if(node -> balance == 0){
      *balance = 'y';
	}
  }
	
  else{
    node -> left = insert(node -> left, key, balance);
	
	if(*balance == 'n'){
	  node -> balance += 1; // increments node balance
	}
		
    if(node -> balance == 0){
	  *balance = 'y';
	}
  }

  if(node -> balance == 2){
    
	Tnode * leftNode = node -> left;
	if(leftNode -> balance == 1){
	  node = Rotate_Right(node); // right rotation of the node
	  node -> balance = 0;
	  node -> right -> balance = 0;
	}
		
    if(leftNode -> balance == -1){
	  node = Rotate_Left_Right(node);
	}
		
	*balance = 'y';		
  }
	if(node -> balance == -2)
	{
		Tnode * rightNode = node -> right;
		if(rightNode -> balance == -1)
		{
			node = Rotate_Left(node);
			node -> balance = 0;
			node -> left -> balance = 0;
		}
		if(rightNode -> balance == 1)
		{
			node = Rotate_Right_Left(node);
		}
		*balance = 'y';
	}

	return node;
}

Tnode *delete(Tnode *node, int key, char *balance){
  // if node is empty, return node back to calling function
  if(node == NULL){
    return node;
  }

  *balance = 'y';
  
  if(node -> key > key){
    node -> left = delete(node -> left, key, balance);
	
    if(*balance == 'n'){
	  node -> balance -= 1; // subtracts from balance
    }
		
    if(node -> balance == -1){
      *balance = 'y';
    }
  }
	
  else if(node -> key < key){
    node -> right = delete(node -> right, key, balance);
    
	if(*balance == 'n'){
	  node -> balance += 1; // increments balance
	}
		
    if(node -> balance == 1){
	  *balance = 'y';
	}
  }
	
  else{
    if(node -> left == NULL || node -> right == NULL){
      Tnode * temp = node;
      
	  if(node -> right == NULL && node -> left == NULL){
        node = NULL;
      }
            
	  else if(node -> left == NULL){
        node = node -> right;
      }
            
	  else{
        node = node -> left;
      }

      free(temp); // frees the temporary node
      
	  *balance = 'n';
      return node;
    }
        
    else{
      Tnode *previous = node -> left; // node to left of current node
      while(previous -> right != NULL){
        previous = previous -> right;
      }
            
	  node -> key = previous -> key;
      previous -> key = key + 1;
      node -> left = delete(node -> left, key + 1, balance);
      
	  if(*balance == 'n'){
        node -> balance -= 1;
      }
            
	  if(node -> balance == -1){
        *balance = 'y';
      }
    }
  }

  if(node -> balance == 2){
    Tnode * leftNode = node -> left;
	
	  if(leftNode -> balance == 1){
	    node = Rotate_Right(node); // right rotation of the node
	    node -> balance = 0;
	    node -> right -> balance = 0;
	    *balance = 'y';
	  }
		
	  else if(leftNode -> balance == -1){
	    node = Rotate_Left_Right(node); // left to right rotation of the node
      if (node -> left -> left != NULL){
        *balance = 'y';
      }
	  }
		
	  else if(leftNode -> balance == 0){
	    node = Rotate_Right(node); // right rotation of the node
	    node -> balance = -1;
	    node -> right -> balance = 1;
	    *balance = 'y';
	  }
  }
	
  if(node -> balance == -2){
    Tnode * rightNode = node -> right;
	
	  if(rightNode -> balance == -1){
	    node = Rotate_Left(node); // left rotation of the node
	    node -> balance = 0;
	    node -> left -> balance = 0;
	    *balance = 'y';
	  }
		
	  else if(rightNode -> balance == 1){
	    node = Rotate_Right_Left(node); // right to left rotation of the bode
      if(node -> right -> right != NULL){
        *balance = 'y';
      }
    }
		
	  else if(rightNode -> balance == 0){
	    node = Rotate_Left(node); // left rotation of the node
	    node -> balance = 1;
	    node -> left -> balance = -1;
	    *balance = 'y';
	  }
  }

  return node;
}

Tnode *Rotate_Right(Tnode *node){
  // right rotation of the binary tree
  Tnode * newNode = node -> left;
  Tnode * temp = newNode -> right;
  
  newNode -> right = node;
  node -> left = temp;

  return newNode;
}

Tnode * Rotate_Left(Tnode *node){
  // left rotation of the binary tree
  Tnode * newNode = node-> right;
  Tnode * temp = newNode -> left;
  
  newNode -> left = node;
  node -> right = temp;

  return newNode;
}

Tnode * Rotate_Right_Left(Tnode *node){
  // right to left rotation of binary tree
  node -> right = Rotate_Right(node -> right);
  node = Rotate_Left(node);
	
  if(node -> right -> right == NULL){
    node -> left -> balance = 0;
	node -> right -> balance = 0;
  }
	
  if(node -> balance == 1){
    node -> balance = 0;
    node -> left -> balance = 0;
	node -> right -> balance = -1;	
  }
	
  if(node -> balance == -1){
    node -> balance = 0;
	node -> left -> balance = 1;
	node -> right ->balance = 0;
  }
    
  return node;
}

Tnode * Rotate_Left_Right(Tnode *node){
  // left to right rotation of binary tree
  node -> left = Rotate_Left(node -> left);
  node = Rotate_Right(node);
    
  if(node -> left -> left == NULL){
    node -> left -> balance = 0;
	node -> right -> balance = 0;
  }
	
  if(node -> balance == 1){
    node -> balance = 0;
	node -> left -> balance = 0;
	node -> right ->balance = -1;
  }
	
  if(node -> balance == -1){
    node -> balance = 0;
	node -> left -> balance = 1;
	node -> right -> balance = 0;
  }
    
  return node;
}

void Print_Binary_Tree(Tnode *node, FILE *file){
  if(node == NULL){
    return;
  }
    
  char balance; // the balance of the node

  // if the node has two children, balance becomes 3
  if(node -> left && node -> right){
    balance = 3;
  }

  // if node only has one left child, the balance becomes 2	
  else if(node -> left){
	balance = 2;
  }

  // if the node only has a right child, the balance becomes 1	
  else if(node -> right){
	balance = 1;
  }

  // if node has no children, the balance becomes 0		
  else{
    balance = 0;
  }
		
  // prints the output file in preorder traversal
  fwrite(&(node -> key), sizeof(int), 1, file); 
  fwrite(&balance, sizeof(char), 1, file);

  Print_Binary_Tree(node -> left, file); // traverses the left side of the binary tree
  Print_Binary_Tree(node -> right, file); // traverses the right side of the binary tree
  
  return;
}

void deleteTree(Tnode *node){
  // if node is empty, return
  if(node == NULL){
    return;
  }

  deleteTree(node -> left); // traverses left side of binary tree
  deleteTree(node -> right); // traverses right side of binary tree
  
  free(node); // frees allocated space of node
  
  return;
}
