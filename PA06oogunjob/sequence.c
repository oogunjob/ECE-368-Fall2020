#include <stdio.h>
#include <stdlib.h>
#include "pa6.h"

int findSequence(char * tablefile, char * tabletextfile, char * sequencefile){
  // opens necessary files to be read and written
  FILE * binaryTable = fopen(tablefile, "rb");
  FILE * textTable = fopen(tabletextfile, "w");
  FILE * sequenceFile = fopen(sequencefile, "wb");

  // if binary table file cannot be opened, return 0 to main
  if(binaryTable == NULL){
    // closes open files
    fclose(textTable);
    fclose(sequenceFile);
    return 0;
  }

  short rows; // number of rows in the table
  short columns; // number of columns in the table

  fread(&rows, sizeof(short), 1, binaryTable); // reads the number of rows from file
  fread(&columns, sizeof(short), 1, binaryTable); // reads the number of columns from file

  // creates the table from the binary table
  short table[rows][columns];
  
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      // reads each number from binary table into the 2D array
      fread(&(table[i][j]), sizeof(short), 1, binaryTable);
    }
  }

  // prints the binary table as a text file
  fprintf(textTable, "%hd %hd\n", rows, columns);
  for(int row = 0; row < rows; row++){
    for(int column = 0; column < columns; column++){
      if(column == columns - 1){
        fprintf(textTable, "%hd", table[row][column]);  
      }
      else{
        // prints each row in the binary table
        fprintf(textTable, "%hd ", table[row][column]);
      }
    }
    fprintf(textTable, "\n");
  }













  // closes necessary files
  fclose(binaryTable);
  fclose(textTable);
  fclose(sequenceFile);

  return 1;
}