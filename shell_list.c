#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shell_list.h"
#include "sequence.h"
#include "list_of_list.h"

static void push(Node ** head, long value);
static void pushList(List ** head);

static Node * getNode(Node * head, int index); // *** need to remove

Node * List_Load_From_File(char * filename){
  // calculates the time taken by function
  clock_t t; 
  t = clock(); 

  FILE * file = fopen(filename, "rb"); // opens binary file of numbers to store in linked list
  
  if(file == NULL){
    fprintf(stderr, "ERROR: File is NULL.\n");
	  fclose(file); // closes file
    return NULL; // returns NULL value back to node
  }

  long value; // the value read from the file 
 
  Node * head = NULL; // creates a head node
 
  // Stores the the values in the linked list
  while(fread(&value, sizeof(long), 1, file)){
    push(&head, value); // adds new nodes into linked storing values from file
  }

  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // time taken (in seconds)
  
  fprintf(stdout, "Function: Load List took %f seconds to execute.\n", time_taken); // *** need to remove

  fclose(file); // closes the file
  return head; // returns the head of the list
}

Node *List_Shellsort(Node *list, long *n_comp){
  // calculates the time taken by function
  clock_t t; 
  t = clock(); 

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
  
  // given the number in the sequence will determine how many lists I need to create
  List * head = NULL; // list of lists *** may need to remove

  int listSize = 0; // numbers of lists within the list of lists *** may need to remove

  // creates sequence[sequenceSize - 1] sublists in the list of lists
  for(listSize = 0; listSize < sequence[sequenceSize - 1]; listSize++){
    pushList(&head);
  }

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
  
  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // time taken (in seconds)
  
  fprintf(stdout, "Function: Sort List took %f seconds to execute.\n", time_taken); // *** need to remove
  
  free(sequence); // frees the sequence array
  return list; 
}

void push(Node ** head, long value){
  Node * node = malloc(sizeof(*node)); // allocates memory for new node
  node -> value = value; // adds the given value to the node's value
  
  node -> next = (*head); // makes new node the head of the linked list
  
  (*head) = node; // moves the head to point to the new node
} 

void pushList(List ** head){
  List * list = malloc(sizeof(*list)); // allocates memory for new node
  
  list -> next = (*head); // makes new node the head of the linked list
  
  (*head) = list; // moves the head to point to the new node
} 

Node * getNode(Node *head, int index){ 
  int count = 0; 
  
  //if count equal too n return node->data 
  if(count == index){ 
    return head; 
  }
      
  //recursively decrease n and increase head to next pointer  
  return getNode(head-> next, index - 1);  
} 

int List_Save_To_File(char *filename, Node *list){
  // calculates the time taken by function
  clock_t t; 
  t = clock(); 

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
  
  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // time taken (in seconds)
  
  fprintf(stdout, "Function: Save List took %f seconds to execute.\n\n", time_taken); // *** need to remove
  fclose(file); // closes the file
  return elements;
}