#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shell_list.h"
#include "sequence.h"
#include "list_of_list.h"

static void insertNode(Node* previous, long value);

static List * addSubList(List * head, int k, long *n_comp, bool sortUp);
static void addAndSort(Node** head, Node* ins, long *n_comp, bool sortUp);
static Node* removeNode(Node** head);
static void freeSubList(List * subList);
static List * addList(Node * sublist);

static List * addList(Node * sublist)
{
    List * new = malloc(sizeof(List));
    new -> node = sublist;
    new -> next = NULL;
    return new;
} 

Node * List_Load_From_File(char * filename){
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

  // need to add a clause if the sequence is empty or sequenceSize is still 0 ***

  int count = 1; // loop control variable that determines value of k
  int k; // sequence control variable
  
  k = sequence[sequenceSize - count]; // highest value of k
  
  List * head = malloc(sizeof(*head)); // head of list of lists
  head -> node = list; // first node in the list of lists points to the original list
  head -> next = head; // head of the list of lists points back to itself

  bool sortUp = false;

  while(count <= sequenceSize){
    if(sortUp == false){
      sortUp = true;
    }
    else{
      sortUp = false;
    }

    head = addSubList(head, k, n_comp, sortUp);
    k = sequence[sequenceSize - ++(count)];
  }

  list = head -> node;
  free(head);

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

static void insertNode(Node* previous, long value){ 
  Node* new_node = malloc(sizeof(*new_node)); // creates new node
  new_node -> value = value; // assigns given value to new node's value
  
  new_node -> next = previous -> next; // new node's next points to the next of previous node
  previous -> next = new_node; // previous node now points to new node
}

static List * addSubList(List * head, int k, long *n_comp, bool sortUp){
    List * prevList = head;
    List * listptr = NULL;; // traversal
    Node * node = NULL;
    //printf("\npointer to newList %p", (void*)newList);
    for(int i = 0; i < k; i++)
    {
        node = removeNode(&(prevList -> node));
        if (i == 0)
        {
            head = addList(node);
            listptr = head;
        }
        else
        {
            listptr -> next = addList(node);
            listptr = listptr -> next;

            if(node == NULL) // empty
            {
                prevList =  prevList ->next;
                break; 
            }
            node -> next = NULL;
            listptr -> node = node;
            //printf("%p\n", (void*)listptr);
        }
        prevList =  prevList -> next;
    }

    listptr -> next = head; // circular link
    if (k == 1) // sort upwards for last sort
        sortUp = true;
    // shell sort
    while(true)
    {
        node = removeNode(&( prevList -> node));
        listptr = listptr -> next;
        if(node == NULL)
            break;
        addAndSort(&(listptr ->node), node,n_comp, sortUp);
        prevList =  prevList -> next;
    }
    freeSubList(prevList);
    return head;
}

// add nodes to sublists and sort them
static void addAndSort(Node** head, Node* ins, long *n_comp, bool sortUp)
{
    Node * temp = NULL;
    temp = *head;
    (*n_comp)++;
    if (sortUp == true) // sort upward
    {
        if( ins -> value < (*head) -> value )
        {
            ins -> next = *head;
            (*head) = ins;
            return;
        }
        else
        {
            while((temp -> next != NULL) && (((temp -> next) -> value) < (ins -> value)))
            {
                temp = temp -> next;
                (*n_comp)++;
            }
        }
    }
    else // sort downward
    {
        if(ins -> value > (*head) -> value)
        {
            ins -> next = *head;
            (*head) = ins;
            return;
        }

        while((temp -> next != NULL) && (((temp -> next) -> value) > (ins -> value)))
        {
            temp = temp -> next;
            (*n_comp)++;
        }
    }
    ins -> next = temp -> next;
    temp -> next = ins;

    return;
}
static Node* removeNode(Node** head)
{
    if (*head == NULL)
    {
        return NULL;
    }
    else
    {
        Node * removed = *head;
        *head = (*head) -> next;
        removed -> next = NULL;

        return removed;
    }
}


// free sub list nodes
static void freeSubList(List * subList){
    if(subList == NULL){
        return;
    }

    List * subListNext = subList -> next;
    if(subListNext == subList)
    {
        // empty
    }
    else
    {
        List * temp = NULL;
        while((subList != subListNext))
        {
            temp = subListNext;
            subListNext = subListNext -> next;
            free(temp);
        }
    }
    free(subList);
    return;
}
