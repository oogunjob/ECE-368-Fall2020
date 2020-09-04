#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "sequence.h"

static Node * addNode(Node * head, long value);
static Node * createNode();

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
  size = ftell(file) / sizeof(long) / 2;
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
  while (current != NULL) 
  { 
    size++; // increments count of size
    current = current->next; // positions to next node in the linked list
  } 

  int sequenceSize = 0; // number of elements in the sequence
  long *sequence = Generate_2p3q_Seq(size, &sequenceSize); // computes Pratt's sequence based on the size of the linked list

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

Node * createNode() 
{
  Node * temp = malloc(sizeof(*temp)); // allocates new memory for node
  temp -> next = NULL; // next of temp points to NULL
 
  return temp; //returns the new node
}

int List_Save_To_File(char *filename, Node *list)
{

  fprintf(stdout, "Test");

  FILE * file = fopen(filename, "wb"); // opens binary file that will be written to
 
  // if the linked list is empty, closes the file and returns a count of no elements written
  if(list == NULL)
  {
    fclose(file);
    return 0;
  }
 
  // writes elements of array to file
  int elements = 0; // number of elements written to the file
  
  Node * temp = list; // temporary position in linked list
  long value; // value of the node in linked list
  
  while(temp != NULL)
  {
	// writes the value stored in linked list to the file
	value = temp -> value;
	fwrite(&value, sizeof(long), 1, file);   
	temp = temp -> next;
	
	elements++; // increments number of iterations
  }
 
  // deletion of linked list process
  Node * current = list; // current position in linked list
  Node * next; // next node from current node in linked list
  
  while(current != NULL)  
  { 
    next = current -> next; 
    free(current); 
    current = next; 
  } 
  
  list = NULL;
  
  fclose(file); // closes the file

  return elements;
}