#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shell_list.h"
#include "sequence.h"
#include "list_of_list.h"

static void insertNode(Node* previous, long value);

static void pushList(List ** head);
static void bubblesort(Node * head);
static void swap(Node *a, Node *b);

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
  Node * current = head; // current node points the head of the linked list
 
  // Stores the the values in the linked list
  while(fread(&value, sizeof(long), 1, file)){
    if(head == NULL){
      head = malloc(sizeof(*head));
      head -> value = value;
      head -> next = NULL;
      current = head;
    } 
    
    else{
      insertNode(current, value);
      current = current -> next;
    }
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
  
  List * currentList = head; // current list points the head in the list of lists
  Node * currentHead = head -> node; // current head points the the first node in the first linked list of linked lists
  currentList -> node = currentHead; // head of the current list points the 
  
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

  // bubblesort(list);

  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // time taken (in seconds)
  
  // fprintf(stdout, "Function: Sort List took %f seconds to execute.\n", time_taken); // *** need to remove

  // deletion of list of lists
  currentList = head; // current position in linked list
  List * next; // next list from current list in linked list
  
  while(currentList != NULL){ 
    next = currentList -> next; 
    free(currentList); // make sure to delete every not in the list along with the list 
    currentList = next; 
  } 
  
  currentList = NULL; // ensures list is empty 

  free(sequence); // frees the sequence array
  return list; 
}

static void pushList(List ** head){
  List * list = malloc(sizeof(*list)); // allocates memory for new node
  
  list -> next = (*head); // makes new node the head of the linked list
  
  (*head) = list; // moves the head to point to the new node
} 

static Node * getNode(Node *head, int index){ 
  int count = 0; 
  
  //if count equal too n return node->value 
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
 
  // deletion of linked list
  Node * current = list; // current position in linked list
  Node * next; // next node from current node in linked list
  
  while(current != NULL){ 
    next = current -> next; 
    free(current); 
    current = next; 
  } 
  
  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // time taken (in seconds)
  
  // fprintf(stdout, "Function: Save List took %f seconds to execute.\n\n", time_taken); // *** need to remove
  fclose(file); // closes the file
  return elements;
}

static void bubblesort(Node *start){ 
  int swapped;
  int i;

  Node * ptr1; 
  Node * lptr = NULL; 
  
  // checks for empty list
  if (start == NULL) 
    return; 
  
  do
  { 
    swapped = 0; 
    ptr1 = start; 
  
    while (ptr1 -> next != lptr){ 
      if (ptr1 -> value > ptr1 -> next -> value){  
        swap(ptr1, ptr1 -> next); 
        swapped = 1; 
      } 
      
      ptr1 = ptr1 -> next; 
    } 
      lptr = ptr1; 
    } while (swapped); 
} 
  
static void swap(Node * a, Node * b){ 
  long temp = a -> value; 
  
  // swaps values or a and b
  a -> value = b -> value; 
  b -> value = temp; 
}

static void insertNode(Node* previous, long value){ 
  Node* new_node = malloc(sizeof(*new_node)); // creates new node
  new_node -> value = value; // assigns given value to new node's value
  
  new_node -> next = previous -> next; // new node's next points to the next of previous node
  previous -> next = new_node; // previous node now points to new node
}
