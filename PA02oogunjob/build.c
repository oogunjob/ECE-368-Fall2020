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
  if(head == NULL){
    return list;
  }
    
  if((head -> root) -> frequency <= (list -> root) -> frequency){
    head -> next = insert(head -> next, list);
    return head;
  }
    
  list -> next = head;
  return list;
}






ListNode * constructHuffmanTree(long * frequencies, FILE * file){
  int ind = 0;
  while (frequencies[ind] == 0){
    ind++;
  }
    
  if (ind == 256){ //no frequency
    return NULL;
  }
    
  ListNode * head = NULL;
  while (ind < 256){
    if (frequencies[ind]){
      HBTNode * tree = makeHBTNode(ind, frequencies[ind]);
      ListNode * node = makeListNode(tree);
      head = insert(head, node);
    }
        
    ind ++;
  }

  while ((head -> next) != NULL){ //merge linked list to a tree
    ListNode * num2 = head->next;
    ListNode * num3 = num2->next;
    HBTNode * tn1 = head->root;
    HBTNode * tn2 = num2->root;
    free(head);
    free(num2);
    head = num3;
    HBTNode * merg = malloc(sizeof(HBTNode));
    merg->left = tn1;
    merg->right = tn2;
    merg->data = 0;
    merg->frequency = tn1->frequency+tn2->frequency;
    ListNode * ln = makeListNode(merg);
    head = insert(head, ln);
  }
    
  printTree(file, head -> root);

  // printTree(head->root, output);
  return head;
}