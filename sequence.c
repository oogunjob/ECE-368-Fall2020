#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"

long *Generate_2p3q_Seq(int length, int *seq_size){
  long * sequence = malloc(sizeof(*sequence)); // subject to change

  long power_q = 1; // power that corresponds to q
  long power_p = 0; // power that corresponds to p
  
  // computes powers for Pratt's sequence array
  while(power_q <= length){
    power_p = power_q;

    while(power_p <= length){
      // need to append the power_p to the list here
      power_p = power_p * 2;
    }

    power_q = power_q * 3;

  }