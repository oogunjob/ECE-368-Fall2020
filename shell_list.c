#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "sequence.h"
#include "list_of_list.h"

static Node * addNode(Node * head, long value);
static Node * createNode();
static Node * getNode(Node * head, int index); // ***

/* Takes head pointer of the linked list and index 
    as arguments and return data at index*/
Node * getNode(Node *head, int index){ 
  int count = 0; 
  
  //if count equal too n return node->data 
  if(count == index){ 
    return head; 
  }
      
  //recursively decrease n and increase  
  // head to next pointer  
  return getNode(head-> next, index - 1);  
} 

Node * List_Load_From_File(char * filename){
  FILE * file = fopen(filename, "rb"); // opens binary file of numbers to store in linked list
  
  if(file == NULL){
    fprintf(stderr, "ERROR: File is NULL.\n");
	  fclose(file); // closes file
    return NULL; // returns NULL value back to node
  }

  int size; // number of elements in the file
 
  // Determines the amount of nodes for the file
  fseek(file, 0, SEEK_END);
  size = ftell(file) / sizeof(long);
  fseek(file, 0, SEEK_SET);

  long value; // the value read from the file 
  int count; // loop control variable
 
  Node * head = NULL; // creates a head node
 
  // Stores the the values in the linked list
  for(count = 0; count < size; count++){
    fread(&value, sizeof(long), 1, file);
    head = addNode(head, value); // adds new nodes into linked storing values from file
  }

  fclose(file); // closes the file
  return head; // returns the head of the list
}

Node *List_Shellsort(Node *list, long *n_comp){ 
  int size = 0;  // size of the linked list
  Node* current = list;  // head of the linked list
  
  // counts the number of nodes in the linked list
  while (current != NULL){ 
    size++; // increments count of size
    current = current -> next; // positions to next node in the linked list
  } 

  int sequenceSize = 0; // number of elements in the sequence
  long *sequence = Generate_2p3q_Seq(size, &sequenceSize); // Pratt's sequence based on the size of the linked list

  // need to implement shell sort of linked list here
  // need to add a clause if the sequence is empty or sequenceSize is still 0 ***

  int count = 1; // loop control variable that determines value of k
  int k; // sequence control variable
  int i; // loop control variable for comparison
  long temp_r; // temporary number
  
  // shell sort implementation (too slow)
  for(count = (sequenceSize - 1); count >= 0; count--){
    k = sequence[count]; // selects the value of k from sequence array
  
    for(int j = k; j <= (size - 1); j++){
      temp_r = getNode(list, j) -> value;
      i = j;

      while(i >= k && getNode(list, i - k) -> value > temp_r){
        *n_comp += 1; // increments the number of comparisons made
        getNode(list, i) -> value = getNode(list, i - k) -> value;
        i = i - k;
      }
      getNode(list, i) -> value = temp_r;
    }
  }

  free(sequence); // frees the sequence array
  return list; 
}

Node * addNode(Node * head, long value){
  // creation of nodes 
  Node * temp; // temporary node
  Node * p; // position node
  temp = createNode(); // creates temporary node
  temp -> value = value; // add element's value to data part of node
 
  if(head == NULL){
    head = temp; // when linked list is empty
  }

  else{ 
    p = head; //assign head to p
    while(p -> next != NULL){
      p = p -> next; //traverse the list until p is the last node.The last node always points to NULL
    }

    p -> next = temp; // point the previous last node to the new node created
  }

   return head; // returns head of linked list
}

Node * createNode(){
  Node * temp = malloc(sizeof(*temp)); // allocates new memory for node
  temp -> next = NULL; // next of temp points to NULL
 
  return temp; //returns the new node
}

int List_Save_To_File(char *filename, Node *list){
  FILE * file = fopen(filename, "wb"); // opens binary file that will be written to
 
  // if the linked list is empty, closes the file and returns a count of no elements written
  if(list == NULL){
    fclose(file);
    return 0;
  }
 
  // writes elements of array to file
  int elements = 0; // number of elements written to the file
  
  Node * temp = list; // temporary position in linked list
  long value; // value of the node in linked list
  
  while(temp != NULL){
	// writes the value stored in linked list to the file
	value = temp -> value;
	fwrite(&value, sizeof(long), 1, file);   
	temp = temp -> next;
	
	elements++; // increments number of iterations
  }
 
  // deletion of linked list process
  Node * current = list; // current position in linked list
  Node * next; // next node from current node in linked list
  
  while(current != NULL){ 
    next = current -> next; 
    free(current); 
    current = next; 
  } 
  
  list = NULL; // ensures list is empty
  
  fclose(file); // closes the file
  return elements;
}