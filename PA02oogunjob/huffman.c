#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "huffman.h"

HBTFile * openFile(char * filename){
  FILE * file = fopen(filename, "rb"); // opens the input file
  HBTFile * head = malloc(sizeof(*head)); // allocates space for HBT file that will hold information

  fread(&(head -> encodedSize), sizeof(long), 1, file); // loads encoded bytes size
  fread(&(head -> topoSize), sizeof(long), 1, file); // loads topology bytes size 
  fread(&(head -> unencodedSize), sizeof(long), 1, file); // loads unencoded bytes size

  fprintf(stdout, "Encoded Size: %ld\n", head -> encodedSize);
  fprintf(stdout, "Topology Size: %ld\n", head -> topoSize);
  fprintf(stdout, "Unencoded Size: %ld\n", head -> unencodedSize);

  loadTree(file, head, head -> topoSize);

  fclose(file); // closes file
  return head;  
}

void loadTree(FILE * file, HBTFile * HBT, long topoSize){
  int * bitArray = decodeInput(file, topoSize); // array that holds the bytes read from file
  
  int count = 0; // loop control variable
  int size = 0; // size of the bytes read
  
  int * decodedArray = malloc(sizeof(*decodedArray) * size); // the array that stores all the numbers 

  int index = 0;
  int ascii;
  uint8_t ascii_temp;
  uint8_t ascii_temp1;
  uint8_t ascii_result = 0x0;


  while(count < (topoSize * 8)){
    if(bitArray[count] == 0){
      size += 1; // increases the size
      decodedArray = realloc(decodedArray, sizeof(*decodedArray) * size); // resizes the array
      decodedArray[index] = 0;
      
      count += 1; // increments size of loop control variable
      index += 1; // updates index in array
    }
        
    else{
      size += 1; // increments size of the array
      decodedArray = realloc(decodedArray, sizeof(*decodedArray) * size); // resizes the array
      decodedArray[index] = 1; // changes index in array to 1

      index += 1; // updates index in array

      ascii = concat(bitArray[count+1], bitArray[count + 2], bitArray[count + 3], bitArray[count+4], bitArray[count+5], bitArray[count + 6], bitArray[count + 7], bitArray[count + 8]);
      ascii = convert_to_decimal(ascii);
            
      ascii_temp = (uint8_t) ascii;

      for(int i = 7; i >= 0; i--){
        ascii_temp1 = ascii_temp >> (7-i);
        ascii_temp1 = ascii_temp1 << 7;
        ascii_temp1 = ascii_temp1 >> (7-i);
        ascii_result = ascii_result | ascii_temp1;
      }

      ascii = (int) ascii_result;
      ascii_result = 0x0;

      size++;
      decodedArray = realloc(decodedArray, sizeof(*decodedArray) * size);
      decodedArray[index] = ascii; // important
      
      count = count + 9;
      index++;
    }
  }
  
  for(count = 0; count < size; count++){
    fprintf(stdout, "%d ", decodedArray[count]);
  }
  fprintf(stdout, "\n"); // new line

  HBTNode * root = buildTree(decodedArray, size); // builds binary tree from array
  HBT -> tree = root; // assings root of binary tree to HBTFile

  // frees both bitArray and decodedArray
  free(bitArray);
  free(decodedArray);

  return;
}

HBTNode * buildTree(int * array, int size){
  HBTNode * head = NULL; // head of the binary tree
  HBTNode * current = NULL; // current node in the binary tree
  HBTNode * deletedNode = NULL; // node used to 

  STACK * Stack = malloc(sizeof(*Stack)); // creates the new stack
  
  int data; // data read from the array
  fprintf(stdout, "The size of this shit is: %d\n", size);

  // need to change back to size
  for(int count = 0; count < size - 1; count++){
    data = array[count];
    
    // if the head is empty, create memory for the head and assign attributes
    if(head == NULL){
      head = createNode(data); // allocates space for the head of the binary tree
      
      // if the head of the linked list is not a leaf node, add to stack
      if(data == 0){
        push(Stack, head);
      }
      // if the head of the linked list is a leaf node, assign next data point
      else if (data == 1){
        // might even need to add a while loop here
        head -> data = array[++count];
      }
    }

    else if(Stack -> top -> left == NULL){
      Stack -> top -> left = createNode(data); // creates node to the left of the node in stack
      // if the node is not a leaf node, add it to the stack
      if(data == 0){
        push(Stack, Stack -> top -> left); // pushes the node to the stack
      }
      // if the node is a leaf node, assign next data point
      else if(data == 1){
        Stack -> top -> left -> data = array[++count];
      }
    }

    else if(Stack -> top -> right == NULL){
      Stack -> top -> right = createNode(data);
      // if the node is not a leaf node, add it to the stack
      if(data == 0){
        current = Stack -> top -> right;
        deletedNode = top(Stack); 
        
        push(Stack, current);
      }
      // if the node is a leaf node, assign next data point
      else if(data == 1){
        current = top(Stack);
        current -> right -> data = array[++count];
      }
    }
  }  
  
  free(Stack); // frees allocated memory for stack

  return head;
}

HBTNode * createNode(int data){
  HBTNode * temp = malloc(sizeof(*temp)); // allocates memory for the node
  temp -> data = data; // assigns data to data attribute of node

  // assigns NULL pointers to left, right, and next of the node
  temp -> left = NULL;
  temp -> right = NULL;
  temp -> next = NULL;

  return temp; // returns temp node
}

int * decodeInput(FILE * file, long topoSize){
  uint8_t temporary; // temporary variable
  uint8_t byte; // byte read from file
  int lcv; // loop control variable
  
  int count = 0;
  int countByte = 0;

  int * bitArray = malloc(sizeof(*bitArray) * (topoSize * 8)); // array that will hold the bits read from file

  for(count = 0; count < topoSize; count++){
    fread(&byte, 1, 1, file); 
    for(lcv = 7; lcv >= 0; lcv--){
      temporary = byte << lcv;
      temporary = temporary >> 7;

      bitArray[countByte] = (int) temporary;
      countByte++; // increments count of bytes
    }
  }

  return bitArray;
}



int convert_to_decimal(int n) {
  int dec = 0;
  int i = 0;
  int rem = 0;
    
  while(n != 0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    i++;
  }
    
  return dec;
}

int concat(int a, int b, int c, int d, int e, int f, int g, int h){ 
  
    char s1[20]; 
    char s2[20]; 
    char s3[20]; 
    char s4[20]; 
    char s5[20]; 
    char s6[20]; 
    char s7[20]; 
    char s8[20]; 
  
    sprintf(s1, "%d", a); 
    sprintf(s2, "%d", b);
    sprintf(s3, "%d", c); 
    sprintf(s4, "%d", d); 
    sprintf(s5, "%d", e); 
    sprintf(s6, "%d", f); 
    sprintf(s7, "%d", g); 
    sprintf(s8, "%d", h); 
  
    strcat(s1, s2);
    strcat(s1, s3); 
    strcat(s1, s4); 
    strcat(s1, s5);  
    strcat(s1, s6); 
    strcat(s1, s7); 
    strcat(s1, s8); 
  
    int result = atoi(s1);
  
    return result; 
} 

void push(STACK * Stack, HBTNode *node){
  // if the stack is empty, push the node to the top of the stack
  if(Stack == NULL){
    Stack -> top = node;
    Stack -> top -> next = NULL;
    return;
  }

  HBTNode * temp = Stack -> top; // temporary node is the current top of the stack
  Stack -> top = node; // new top of the stack is the new node
  Stack -> top -> next = temp; // the node after top is the previous top
  return;
}

HBTNode *top(STACK *stack){
  HBTNode * current = stack -> top; // assigns top of stack as current node
  stack -> top = stack -> top -> next; // new top becomes the node after previous top
  
  return current; // returns the previous top node
}

void printTree(FILE * file, HBTNode* node) { 
  if(node == NULL){ 
    return;
  }

  if(node -> left == NULL && node -> right == NULL){
    fprintf(file, "%d", 1);
  }

  if(node -> data != 0){
    // prints node character
    fprintf(file, "%c", node -> data);
  }
  else{
    // prints node integer data
    fprintf(file, "%d", node -> data);
  }


  // fprintf(file, "%d ", node -> data);
  
  // traverses the left side of the tree
  printTree(file, node -> left);   

  // traverses the right side of the tree
  printTree(file, node -> right); 
}

void deleteTree(HBTNode *node){
  // if node is empty, do nothing
  if(node == NULL){
    return;
  }

  deleteTree(node -> left); // traverses left side of the node
  deleteTree(node -> right); // traverses right side of the node
  
  free(node); // free the allocated memory of the node
  return;
}
