#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

HBTNode * makeHBTNode(int data, int frequency){
  HBTNode * temp = malloc(sizeof(*temp)); // creates space for temporary array
  
  // sets pointers to the left and right of node as NULL
  temp -> left = NULL;
  temp -> right = NULL;
  
  // assigns data and frequency attributes to node
  temp -> data = data;
  temp -> frequency = frequency;
    
  return temp;
}

ListNode * makeListNode(HBTNode * temp){
  ListNode * list = malloc(sizeof(*list)); // creates space for list
    
  list -> root = temp; // assigns the root of the list as the temporary node
  list -> next = NULL; // assigns the next node of list as NULL
    
  return list;
}

ListNode * insert(ListNode * head, ListNode * list){
  // if the head of the list is empty, return the head
  if(head == NULL){
    return list;
  }
    
  // if the head root's frequency is less than or equal to the frequency of the list's root
  // assign the next list to head as the list passed into function
  if((head -> root) -> frequency <= (list -> root) -> frequency){
    head -> next = insert(head -> next, list);
    return head;
  }
    
  list -> next = head; // makes the next list the head
  
  return list;
}

ListNode * constructHuffmanTree(long * frequencies, FILE * file){
  int count = 0; // loop control variable
  
  // checks every node in the frequency array for ASCII characters with no occurences
  while(frequencies[count] == 0){
    count++; // increments count by 1
  }
    
  // if there were no count of ASCII chracters in the frequency array
  // return NULL to head list
  if(count == 256){
    return NULL;
  }

  ListNode * head = NULL; // creates the head of a list node

  for(count = count; count < 256; count++){
    // if the frequency of an ASCII character is greater than one, creates a node for it
    if(frequencies[count]){
      HBTNode * tree = makeHBTNode(count, frequencies[count]);
      ListNode * node = makeListNode(tree);
      head = insert(head, node);
    }
  }

  // constructs binary huffman tree
  while ((head -> next) != NULL){ 
    ListNode * list2 = head -> next; // second list node 
    ListNode * list3 = list2 -> next; // third list node
    
    HBTNode * node1 = head -> root; // first HBT node
    HBTNode * node2 = list2 -> root; // second HBT node
    
    free(head); // fress the head of the list
    free(list2); // frees the second list
    head = list3; // head becomes the third list
    
    HBTNode * temp = malloc(sizeof(*temp)); // creates temporary node
    
    temp -> data = 0; // sets data as 0
    temp -> frequency = (node1 -> frequency) + (node2 -> frequency); // computes node frequency
    
    temp -> left = node1; 
    temp -> right = node2;
    
    ListNode * ln = makeListNode(temp);
    head = insert(head, ln);
  }
    
  // prints the binary huffman tree to file
  printTree(file, head -> root);

  return head;
}