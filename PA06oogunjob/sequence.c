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
  fclose(textTable); // closes the file


  // creates the solution table 
  short ** solutionTable;
  solutionTable = malloc(sizeof(*solutionTable) * rows);
  int solutionLCV; 

  // allocated space for each column for all rows in the table
  for(solutionLCV = 0; solutionLCV < rows; solutionLCV++){ 
    solutionTable[solutionLCV] = malloc(sizeof(*solutionTable[solutionLCV]) * columns);
  }  

  for(int x = 0; x < rows; x++){
    for(int y = 0; y < columns; y++){
      // fills solution table with zeros
      solutionTable[x][y] = 0;
    }
  }
  // end of creation of solution table


  // finds the length of the longest path in the matrix
  short * Row_Column = malloc(sizeof(*Row_Column) * 2); // the position of the row and column with the longest path
  int length = longestIncreasingPath(table, solutionTable, Row_Column, rows, columns); // length of the longest path
  
  short * sequenceRow = malloc(sizeof(*sequenceRow) * length); // row of each number in the sequence
  short * sequenceColumn = malloc(sizeof(*sequenceColumn) * length); // row of each number in the sequence
  
  sequenceRow[0] = Row_Column[0]; // stores the first row of the longest path in the array
  sequenceColumn[0] = Row_Column[1]; // stores the first column of the longest path in the array


  // frees necessary storage
  free(Row_Column); // frees the allocated memory
  free(sequenceRow);
  free(sequenceColumn);
  
  fwrite(&(length), sizeof(int), 1, sequenceFile); // writes the length of the path to the file


  // frees all space allocated for each column for all rows in the table
  for(lcv = 0; lcv < rows; lcv++){ 
    free(table[lcv]);
  }  
  free(table); // frees allocated memory from table

  // frees all space allocated for each column for all rows in the solution table
  for(solutionLCV = 0; solutionLCV < rows; solutionLCV++){ 
    free(solutionTable[solutionLCV]);
  }  
  free(solutionTable); // frees allocated memory from solution table

  // closes necessary files
  fclose(binaryTable);
  fclose(sequenceFile);

  return 1;
}

int longestIncreasingPath(short ** table, short ** solutionTable, short * Row_Column, short rows, short columns){
  if (table == NULL) 
    return 0;
        
  int pathLength = 0;
  
  for(int row = 0; row < rows; row++) {
    for(int column = 0; column < columns; column++) {
      pathLength = max(pathLength, DFS(table, solutionTable, row, column, rows, columns));
    }
  }  
  
  return pathLength;
}

int DFS(short ** table, short ** solutionTable, int row, int column, int ROWS, int COLUMNS){
  if(solutionTable[row][column] > 0){ 
    return solutionTable[row][column];
  }
        
  int result = 1;
  
  // if(row == 0 && column == 4){
  //   fprintf(stdout, "This is the index position that I want, the value at this position is %hd.\n", table[row][column]);
  // }


  if(row + 1 < ROWS && table[row + 1][column] > table[row][column])
    result = max(result, 1 + DFS(table, solutionTable, row + 1, column, ROWS, COLUMNS));

  if(row - 1 >= 0 && table[row - 1][column] > table[row][column]) 
    result = max(result, 1 + DFS(table, solutionTable, row - 1, column, ROWS, COLUMNS));

  if(column + 1 < COLUMNS && table[row][column + 1] > table[row][column]) 
    result = max(result, 1 + DFS(table, solutionTable, row, column + 1, ROWS, COLUMNS));

  if(column - 1 >= 0 && table[row][column - 1] > table[row][column]){ 
    result = max(result, 1 + DFS(table, solutionTable, row, column - 1, ROWS, COLUMNS));
  }
        
  solutionTable[row][column] = result;
  
  return solutionTable[row][column];
}

int max(int x, int y){
  // returns the max number between the two passed integers
  return (x > y ) ? x : y;
}
