#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "huffman.h"




// going to need to come back and fix this for binary1
void printEncoded(FILE * file, char * filename, HBTFile * HBT){
  long numberEncoded;
  uint8_t temporary;
  uint8_t byte;
  
  int count = 0;
  int countByte = 0;
  
  int lcv; // loop control variable
  int size; // size of the encodedArray

  numberEncoded = HBT -> encodedSize - HBT -> topoSize - 24;

  size = numberEncoded * 8; // computes the size of the encodedArray
  fseek(file, HBT -> topoSize + 24, SEEK_SET); // sets file to begin at topology order

  int * encodedArray = malloc(sizeof(*encodedArray) * size);

  // used to update the resultant character that will be used to store in encoded array 
  while(count != numberEncoded){
    fread(&byte, 1, 1, file);

    for(lcv = 7; lcv >= 0; lcv--){
      temporary = byte << lcv;
      temporary = temporary >> 7;
      
      encodedArray[countByte] = (int) temporary;
      countByte += 1;
    }
    count += 1;
  }
  
  fclose(file); // closes the input file

  count = 0; // resets count to 0
  lcv = 0; // loop control variable
  
  file = fopen(filename, "w"); // opens argv[3] to be written to
  HBTNode * head = HBT -> tree;
  HBTNode * current = head;

  while(count != HBT -> unencodedSize){
    countByte = encodedArray[lcv++]; // sets the count byte to the top number in the encoded array
    
    if(countByte == 0){
      current = current -> left; // if the count byte is 0, traverse to the left of the tree
      if(current == NULL){
         break;
       }
    }
    else{
      current = current -> right; // if the count byte is 1, traverse to the left of the tree
       if(current == NULL){
         break;
       }
    }

    if(current -> data != -1){
      fprintf(file, "%c", current -> data);
      current = head;
      count++;
    }
  }

  fclose(file);
  free(encodedArray);

  return;
}

HBTFile * openFile(char * filename){
  FILE * file = fopen(filename, "rb"); // opens the input file
  HBTFile * head = malloc(sizeof(*head)); // allocates space for HBT file that will hold information

  fread(&(head -> encodedSize), sizeof(long), 1, file); // loads encoded bytes size
  fread(&(head -> topoSize), sizeof(long), 1, file); // loads topology bytes size 
  fread(&(head -> unencodedSize), sizeof(long), 1, file); // loads unencoded bytes size

  loadTree(file, head, head -> topoSize);

  fclose(file); // closes file
  return head;  
}

void loadTree(FILE * file, HBTFile * HBT, long topoSize){
  int * bitArray = decodeInput(file, topoSize); // array that holds the bytes read from file
  
  int size = 0; // size of the bytes read
  int * decodedArray = malloc(sizeof(*decodedArray) * size); // the array that stores all the numbers 

  int count = 0; // loop control variable
  int index = 0; // index control of the array
  int lcv; // loop control variable for ASCII helper
  int ASCII; // ASCII character code

  uint8_t tempASCII; // temporary ASCII value
  uint8_t ASCIIHelper; // helper to tempASCII
  uint8_t result = 0x0;

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

      ASCII = concatenate(bitArray[count + 1], bitArray[count + 2], bitArray[count + 3], bitArray[count + 4], bitArray[count + 5], bitArray[count + 6], bitArray[count + 7], bitArray[count + 8]);
      ASCII = convert2decimal(ASCII);
            
      tempASCII = (uint8_t) ASCII;

      // used to update the resultant character that will be used to store in decoded array
      for(lcv = 7; lcv >= 0; lcv--){
        ASCIIHelper = tempASCII >> (7 - lcv);
        ASCIIHelper = ASCIIHelper << 7;
        ASCIIHelper = ASCIIHelper >> (7 - lcv);
        result = result | ASCIIHelper;
      }

      ASCII = (int) result;
      result = 0x0;

      size += 1; // increments size
      
      decodedArray = realloc(decodedArray, sizeof(*decodedArray) * size); // resizes the decoded array
      decodedArray[index] = ASCII; // important
      
      count += 9; // increments count by 9
      index += 1; // increments index by 1
    }
  }
  
  // computes where to stop in the array without the need of the extra padded zeros
  count = 1;
  int num = decodedArray[size - count];
  while(num == 0){
    num = decodedArray[size - ++count];
  }
  count--; // subtracts one from the count to account for extra iteration
  
  HBTNode * root = buildTree(decodedArray, size - count); // builds binary tree from array
  HBT -> tree = root; // assings root of binary tree to HBTFile

  // frees both bitArray and decodedArray
  free(bitArray);
  free(decodedArray);

  return;
}

HBTNode * buildTree(int * array, int size){
  HBTNode * head = NULL; // head of the binary tree
  HBTNode * current = NULL; // current node in the binary tree
  HBTNode * deletedNode = NULL; // node poppped from the stack

  STACK * Stack = malloc(sizeof(*Stack)); // creates the new stack
  
  int data; // data read from the array

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
        head -> data = array[++count];
      }
    }

    else if(Stack -> top -> left == NULL){
      Stack -> top -> left = createNode(data); // creates node to the left of the node in stack

      // if the node is not a leaf node, add it to the stack
      if(data == 0){
        Stack -> top -> left -> data = -1; // sets the value of the node to NULL // COME BACK TO THIS
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
        Stack -> top -> right -> data = -1; // sets the value of the node to NULL // COME BACK TO THIS
        current = Stack -> top -> right;
        deletedNode = top(Stack);
        deletedNode -> data += 0; // adds nothing to deleted node data to remove gcc warning   
        
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

int convert2decimal(int num) {
  int count = 0; // count in loop
  int decimal = 0; // decimal conversion
  int remainder = 0; // remainder of the modulus operation
  
  // while loop that will compute decimal value while the number is not equal to 0
  while(num != 0) {
    remainder = num % 10;
    num = num / 10;
    
    decimal += remainder * pow(2, count); // computes the decimal value
    count += 1; // increments count by 1
  }
    
  return decimal;
}

int concatenate(int a, int b, int c, int d, int e, int f, int g, int h){ 
  // will need to come back and update this function
  char string1[20]; 
  char string2[20]; 
  char string3[20]; 
  char string4[20]; 
  char string5[20]; 
  char string6[20]; 
  char string7[20]; 
  char string8[20]; 

  int result; // result of the concatenation
  
  sprintf(string1, "%d", a); 
  sprintf(string2, "%d", b);
  sprintf(string3, "%d", c); 
  sprintf(string4, "%d", d); 
  sprintf(string5, "%d", e); 
  sprintf(string6, "%d", f); 
  sprintf(string7, "%d", g); 
  sprintf(string8, "%d", h); 
  
  strcat(string1, string2);
  strcat(string1, string3); 
  strcat(string1, string4); 
  strcat(string1, string5);  
  strcat(string1, string6); 
  strcat(string1, string7); 
  strcat(string1, string8); 
  
  result = atoi(string1);
  
  return result; 
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

int isLeafNode(HBTNode * node){
  // determines if node is leaf node or not
  if(node -> left == NULL && node -> right == NULL){
    return 1;
  }
  return 0;
}

void printTree(FILE * file, HBTNode* node) { 
  if(node == NULL)
    return;
   
  // if the node is a leaf node, print a 1 prior to its data
  if(isLeafNode(node)){
    fprintf(file, "%c", '1');
    fprintf(file, "%c", node -> data);
  }
  else{
    fprintf(file, "%c", '0');
  }

  // traverses the left side of the tree
  printTree(file, node -> left);   

  // traverses the right side of the tree
  printTree(file, node -> right); 
}

void printCount(FILE * input, char * filename){
  FILE * output = fopen(filename, "w"); // opens the output file
  
  long ASCII[256] = {0}; // count of every ASCII used 

  int c; // character read in the fie

  // loops through the file to see how many times each character in ASCII table is used
  while((c = fgetc(input))) {
    // break if end of file
    if(c == EOF) 
      break;

    // adds one to the count of that particular character
    ASCII[c] += 1;
  }

  fwrite(ASCII, sizeof(ASCII), 1, output); // write the contents of the array to the output file
  fclose(output); // closes output file

  return;
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
