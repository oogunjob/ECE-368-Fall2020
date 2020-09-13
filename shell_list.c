#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "list_of_list.h"
#include "sequence.h"

static void insertNode(Node *previous, long value);
static void bubbleSort(Node **head, Node *node, long *n_comp, int sorted);
static void deleteList(List *subList);

static Node *deleteNode(Node **head);

static List *addList(Node *sublist);
static List *addSublist(List *head, int k, long *n_comp, int sorted);

Node *List_Load_From_File(char * filename){
  FILE * file = fopen(filename, "rb"); // opens binary file of numbers to store in linked list
  
  if(file == NULL){
    fprintf(stderr, "ERROR: File is NULL.\n");
	  fclose(file); // closes file
    return NULL; // returns NULL value back to node
  }

  long value; // the value read from the file 
 
  Node * head = NULL; // creates a head node of linked list
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

  fclose(file); // closes the file
  return head; // returns the head of the list
}

Node *List_Shellsort(Node *list, long *n_comp){
  Node * current = list;  // head of the linked list
  int size = 0;  // size of the linked list

  // counts the number of nodes in the linked list
  while (current != NULL){ 
    size++; // increments count of size
    current = current -> next; // positions to next node in the linked list
  } 

  int sequenceSize = 0; // number of elements in the sequence
  long *sequence = Generate_2p3q_Seq(size, &sequenceSize); // Pratt's sequence based on the size of the linked list

  // if the linked list is empty, frees the sequence array and returns the array
  if(size == 0){
    free(sequence);
    return list;
  }

  int count = 1; // loop control variable that determines value of k
  int k; // sequence control variable
  
  k = sequence[sequenceSize - count]; // highest value of k
  
  List * head = malloc(sizeof(*head)); // head of list of lists
  head -> node = list; // first node in the list of lists points to the original list
  head -> next = head; // head of the list of lists points back to itself

  int sorted = 0; // determines wheter list need to be sorted up (0 indicates false, and 1 indicates true)

  // creates sub lists from list and sorts k sub lists based on sequence and rearanges original list in sorted order 
  while(count <= sequenceSize){
    if(!sorted){
      sorted = 1;
    }
    else{
      sorted = 0;
    }

    head = addSublist(head, k, n_comp, sorted); // adds sub lists to head of linked list of linked lists
    
    // selection of k for lists that will be created
    if(k != 1){
    k = sequence[sequenceSize - ++(count)];
    }
    else{
      count++; // increments count to go to the next number in the sequence array
    }
  }

  list = head -> node; // head of list points to the head in the linked list of linked lists
  free(head); // frees the head in the linked list of linked lists

  free(sequence); // frees the sequence array
  return list; 
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
 
  // deletion of linked list
  Node * current = list; // current position in linked list
  Node * next; // next node from current node in linked list
  
  while(current != NULL){ 
    next = current -> next; 
    free(current); 
    current = next; 
  } 

  fclose(file); // closes the file
  return elements;
}

static void insertNode(Node *previous, long value){ 
  Node* new_node = malloc(sizeof(*new_node)); // creates new node
  new_node -> value = value; // assigns given value to new node's value
  
  new_node -> next = previous -> next; // new node's next points to the next of previous node
  previous -> next = new_node; // previous node now points to new node
}

static List *addSublist(List *head, int k, long *n_comp, int sorted){
  List * previous = head; // previous list points the head passed from function
  List * current = NULL; // traversal node that is evaluated
  Node * node = NULL; // placeholder node
  
  int i; // loop control variable

  for(i = 0; i < k; i++){
    node = deleteNode(&(previous -> node)); // deletes the previous list's head node
    
    if (!i){
      head = addList(node); // adds the node to the head of the list
      current = head; // current node is now the head of the list
    }
        
    else{
      current -> next = addList(node); // current node's next node comes from a new node
      current = current -> next; // current is now the node after the current node

      if(node == NULL){ 
        previous =  previous -> next; // previous node is now the node after previous 
        break; // completes loop
      }
            
      node -> next = NULL;
      current -> node = node;

    }
    previous = previous -> next;
  }

  current -> next = head;
  
  if (k == 1) 
    sorted = 1; 
  
  // sorting of linked list
  while(1){
    node = deleteNode(&( previous -> node));
    current = current -> next;
    if(node == NULL)
      break;
        
    bubbleSort(&(current ->node), node, n_comp, sorted); // bubble sort of sub list
    previous =  previous -> next;
  }
    
  deleteList(previous);
  return head;
}

// add nodes to sublists and sort them
static void bubbleSort(Node **head, Node *node, long *n_comp, int sorted){ 
  Node * temp = *head; // creation of temporary node that serves as placeholder
  
  // bubble sorting implementation for linkled list O(n^2) time complexity
  if (sorted){ 
    if(node -> value < (*head) -> value){
      node -> next = *head;
      *head = node;
      return;
    }
        
    else{
      while((temp -> next != NULL) && (((temp -> next) -> value) < (node -> value))){
        temp = temp -> next;
        (*n_comp)++;
      }
    }
  }
    
  else{ 
    if(node -> value > (*head) -> value){
      node -> next = *head;
      *head = node;
      return;
    }

    while((temp -> next != NULL) && (((temp -> next) -> value) > (node -> value))){
      temp = temp -> next;
      (*n_comp)++;
    }
  }
    
  node -> next = temp -> next;
  temp -> next = node;
}

static Node *deleteNode(Node **head){
  // if head is already empty, return NULL back to caller function
  if(*head == NULL){
    return NULL;
  }

  else{
    Node * deleted = *head; // 'deleted' node points to head node
    *head = (*head) -> next; // new head is the node after head
    deleted -> next = NULL; // node after deleted is null

    return deleted; // returns 'deleted' node
  }
}

static void deleteList(List *subList){
  // if sublist is already null, return to caller function
  if(!subList){
    return;
  }

  List * subListNext = subList -> next; // node that points to the node after the sub list 
  
  // if the next node after the sub list is not the sub list, free every node up until then
  if(subListNext != subList){
    List * temp = NULL; // temporary placeholder list
    
    while(subList != subListNext){
      temp = subListNext; // temporary list is the next list in the sublist
      subListNext = subListNext -> next;
      free(temp); // deletes the list
    }
  }

  free(subList); // completely frees sublist
}

static List *addList(Node *sublist){
  List * list = malloc(sizeof(*list)); // allocates memory for new sub list
  
  list -> node = sublist; // head of sublist points to the list
  list -> next = NULL; // next of sub list is null
  
  return list; // returns new list
} 
