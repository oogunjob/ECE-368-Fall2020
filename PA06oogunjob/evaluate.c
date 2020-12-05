#include <stdio.h>
#include <stdlib.h>
#include "pa6.h"

int Evaluate(char * tablefile, char * sequencefile){
  
  FILE * binaryTable = fopen(tablefile, "rb"); // opens the binary table file
  FILE * binarySequence = fopen(sequencefile, "rb"); // opens the sequence file

  // evaluation of the binary table file
  if(binaryTable == NULL){
    // if the file cannot be opened, print -1 to standard output
    fprintf(stdout, "-1"); // *COME BACK TO THIS
    // need to return back to main program
  }

  short rows; // number of rows in the table
  short columns; // number of columns in the table

  fread(&rows, sizeof(short), 1, binaryTable); // reads the number of rows from file
  fread(&columns, sizeof(short), 1, binaryTable); // reads the number of columns from file

  // computes the size of the binary table file
  fseek(binaryTable, 0, SEEK_END); // moves to the end of the file
  if(ftell(binaryTable) != (2 + rows * columns) * sizeof(short)){
    fprintf(stdout, "0"); // COME BACK TO THIS
  }
  else{
    // file evaluation passes all test cases
    fprintf(stdout, "1,");
    fseek(binaryTable, 0, SEEK_SET);

    // re-reads the rows and columns of the binary file
    fread(&rows, sizeof(short), 1, binaryTable);
    fread(&columns, sizeof(short), 1, binaryTable);
  }

  // evaluation of the binary table file
  if(binarySequence == NULL){
    // if the file cannot be opened, print -1 to standard output
    fprintf(stdout, "-1"); // *COME BACK TO THIS
    // need to return back to main program
  }

  int length; // the length of the longest strictly increasing sequence

  fread(&length, sizeof(int), 1, binarySequence); // reads in the length of the sequence from the file
  
  // computes the size of the binary sequence file
  fseek(binarySequence, 0, SEEK_END); // moves to the end of the file
  if(ftell(binarySequence) != (sizeof(int) + 2 * length * sizeof(short))){
    fprintf(stdout, "0"); // COME BACK TO THIS
  }
  else{
    // file evaluation passes all test cases
    fprintf(stdout, "1,");
    fseek(binarySequence, 0, SEEK_SET);

    // re-reads the rows and columns of the binary file
    fread(&length, sizeof(int), 1, binarySequence);
  } 

  // creates the table from the binary table
  short ** table;
  table = malloc(sizeof(*table) * rows);
  int lcv; 

  // allocated space for each column for all rows in the table
  for(lcv = 0; lcv < rows; lcv++){ 
    table[lcv] = malloc(sizeof(*table[lcv]) * columns);
  }  

  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      // reads each number from binary table into the 2D array
      fread(&(table[i][j]), sizeof(short), 1, binaryTable);
    }
  }

  // creates the sequence using the creating table
  short * sequence;
  sequence = malloc(sizeof(*sequence) * length);
  
  short row; // row index
  short column; // column index
  int index = 0;

  short * start = malloc(sizeof(*start) * 2);
  short * end = malloc(sizeof(*end) * 2);

  while(index < length){
    fread(&(row), sizeof(short), 1, binarySequence);
    fread(&(column), sizeof(short), 1, binarySequence);
    sequence[index++] = table[row][column];

    // assigns the index positions of the start in the sequence
    if(index - 1 == 0){
      start[0] = row;
      start[1] = column;
    }

    // assigns the index positions of the end in the sequence
    if(index - 1 == length - 1){
      end[0] = row;
      end[1] = column;
    }
  }

  // checks if the sequence is strictly increasing or not
  int strictlyIncreasingValue = strictlyIncreasing(sequence, length); 

  // if the sequence is strictly increasing, print 1
  if(strictlyIncreasingValue){
    fprintf(stdout, "1,");
  }
  // if the sequence is not strictly increasing, print 0
  else{
    fprintf(stdout, "0,");
  }

  int maxStart = maximalStart(table, start, rows, columns); // determines if the starting position is the maximal starting spot
  int maxEnd = maximalEnd(table, end, rows, columns); // determines if the ending position is the maximal ending position


  if(maxStart == 0 || maxEnd == 0){
    fprintf(stdout, "0\n");
  }
  else{
    fprintf(stdout, "1\n");
  }

  // frees all space allocated for each column for all rows in the table
  for(lcv = 0; lcv < rows; lcv++){ 
    free(table[lcv]);
  }  
 
  free(start); // frees the index positions of the start in the sequence
  free(end); // frees the index positions of the end in the sequence

  free(table); // frees allocated memory from table
  free(sequence); // frees allocated memory from sequence

  fclose(binaryTable); // closes the binary table file
  fclose(binarySequence); // closes the binary sequence file

  return 1;
}

int strictlyIncreasing(short sequence[], int length){
  int i;
  int result = 1;

  // loops through array to ensure that it is strictly increasing 
  for(i = 0; i < length - 1; i++){
    if(sequence[i] >= sequence[i + 1]){
      result = 0;
      break;
    }
  }   
 
  return result; // returns result of where it is strictly increasing or not
}

int maximalStart(short ** table, short * start, short rows, short columns){
  // check around the position given
  // if any of the numbers is less than the position, return 0

  // assignment of row and column of the starting position
  short row = start[0];
  short column = start[1];  

  if(row + 1 < rows && table[row + 1][column] < table[row][column])
    return 0;

  if(row - 1 >= 0 && table[row - 1][column] < table[row][column]) 
    return 0;

  if(column + 1 < columns && table[row][column + 1] < table[row][column]) 
    return 0;

  if(column - 1 >= 0 && table[row][column - 1] < table[row][column]){ 
    return 0;
  }
  
  // if the start is the maximal start then return 1
  return 1;
}

int maximalEnd(short ** table, short * end, short rows, short columns){
  // check around the position given
  // if any of the numbers is greater than the position, return 0

  // assignment of row and column of the ending position
  short row = end[0];
  short column = end[1];  

  if(row + 1 < rows && table[row + 1][column] > table[row][column])
    return 0;

  if(row - 1 >= 0 && table[row - 1][column] > table[row][column]) 
    return 0;

  if(column + 1 < columns && table[row][column + 1] > table[row][column]) 
    return 0;

  if(column - 1 >= 0 && table[row][column - 1] > table[row][column]){ 
    return 0;
  }
  
  // if the start is the maximal start then return 1
  return 1;
}
