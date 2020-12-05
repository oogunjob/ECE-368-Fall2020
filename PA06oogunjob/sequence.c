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
  int length = longestIncreasingPath(table, solutionTable, rows, columns); // length of the longest path
  
  short * sequenceRow = malloc(sizeof(*sequenceRow) * length); // row of each number in the sequence
  short * sequenceColumn = malloc(sizeof(*sequenceColumn) * length); // row of each number in the sequence

  // finds the path with the longest sequence in the table
  for(short a = 0; a < rows; a++){
    for(short b = 0; b < columns; b++){
      if(solutionTable[a][b] == length){
        Row_Column[0] = a; // stores the row position
        Row_Column[1] = b; // stores the column position
      }
    }
  }

  // stores the the correct and colums of the path
  sequenceRow[0] = Row_Column[0]; // stores the first row in the row array
  sequenceColumn[0] = Row_Column[1]; // stores the first column in the column array

  findPath(table, sequenceRow, sequenceColumn, sequenceRow[0], sequenceColumn[0], rows, columns, 1, length);

  fwrite(&(length), sizeof(int), 1, sequenceFile); // writes the length of the path to the file

  // prints the path with row and columns to the output file
  for(int count = 0; count < length; count++){
    fwrite(&(sequenceRow[count]), sizeof(short), 1, sequenceFile);
    fwrite(&(sequenceColumn[count]), sizeof(short), 1, sequenceFile);
  }

  // frees necessary storage
  free(Row_Column);
  free(sequenceRow);
  free(sequenceColumn);
  
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

void findPath(short ** table, short * sequenceRow, short * sequenceColumn, short row, short column, short ROWS, short COLUMNS, int index, int length){
  // max length exceeded
  if(index == length){
    return;
  }
  
  int downResult = 1;
  int upResult = 1;
  int leftResult = 1;
  int rightResult = 1;
  
  // down result
  if(row + 1 < ROWS && table[row + 1][column] > table[row][column])
    downResult = max(downResult, 1 + computePath(table, row + 1, column, ROWS, COLUMNS));

  // up result
  if(row - 1 >= 0 && table[row - 1][column] > table[row][column]) 
    upResult = max(upResult, 1 + computePath(table, row - 1, column, ROWS, COLUMNS));  

  // going right
  if(column + 1 < COLUMNS && table[row][column + 1] > table[row][column]) 
    rightResult = max(rightResult, 1 + computePath(table, row, column + 1, ROWS, COLUMNS));

  // going left
  if(column - 1 >= 0 && table[row][column - 1] > table[row][column]){ 
    leftResult = max(leftResult, 1 + computePath(table, row, column - 1, ROWS, COLUMNS));
  }

  // determine which path has the longest path
  // store the row and column in the array, keep moving down
  int directions[4] = {downResult, upResult, rightResult, leftResult};
  int largest = findLargest(directions);
  
  if(downResult == largest){
    // store the row and column in the array and run it again down
    sequenceRow[index] = row + 1;
    sequenceColumn[index++] = column;
    findPath(table, sequenceRow, sequenceColumn, row + 1, column, ROWS, COLUMNS, index, length);
  }

  else if(upResult == largest){
    // store the row and column in the array and run it again down
    sequenceRow[index] = row - 1;
    sequenceColumn[index++] = column;
    findPath(table, sequenceRow, sequenceColumn, row - 1, column, ROWS, COLUMNS, index, length);
  }

  else if(rightResult == largest){
    // store the row and column in the array and run it again down
    sequenceRow[index] = row;
    sequenceColumn[index++] = column + 1;
    findPath(table, sequenceRow, sequenceColumn, row, column + 1, ROWS, COLUMNS, index, length);
  }

  else if(leftResult == largest){
    // store the row and column in the array and run it again down
    sequenceRow[index] = row;
    sequenceColumn[index++] = column - 1;
    findPath(table, sequenceRow, sequenceColumn, row, column - 1, ROWS, COLUMNS, index, length);
  }

  return;
}

int computePath(short ** table, short row, short column, short ROWS, short COLUMNS){
  int result = 1;
  
  // down result
  if(row + 1 < ROWS && table[row + 1][column] > table[row][column])
    result = max(result, 1 + computePath(table, row + 1, column, ROWS, COLUMNS));

  // up result
  if(row - 1 >= 0 && table[row - 1][column] > table[row][column]) 
    result = max(result, 1 + computePath(table, row - 1, column, ROWS, COLUMNS));  

  // going right
  if(column + 1 < COLUMNS && table[row][column + 1] > table[row][column]) 
    result = max(result, 1 + computePath(table, row, column + 1, ROWS, COLUMNS));

  // going left
  if(column - 1 >= 0 && table[row][column - 1] > table[row][column]){ 
    result = max(result, 1 + computePath(table, row, column - 1, ROWS, COLUMNS));
  }

  return result;
}

int findLargest(int directions[]){
  int largest = directions[0]; // makes first position in the array the largest

  // finds largest number in the array
  for(int i = 1; i < 4; i++){
    if(largest < directions[i]){
      largest = directions[i];
    }   
  }

  // returns the largest number in the array
  return largest;
}

int longestIncreasingPath(short ** table, short ** solutionTable, short rows, short columns){
  if (table == NULL) 
    return 0;
        
  int pathLength = 0;
  
  for(short row = 0; row < rows; row++) {
    for(short column = 0; column < columns; column++) {
      pathLength = max(pathLength, DFS(table, solutionTable, row, column, rows, columns));
    }
  }  
  
  return pathLength;
}

int DFS(short ** table, short ** solutionTable, short row, short column, short ROWS, short COLUMNS){
  if(solutionTable[row][column] > 0){ 
    return solutionTable[row][column];
  }

  int result = 1;

  // determine which way has the most outputed directions wheter it up up, down, left, or right
  // save that number in the array that keeps getting passed down

  // going down
  if(row + 1 < ROWS && table[row + 1][column] > table[row][column])
    result = max(result, 1 + DFS(table, solutionTable, row + 1, column, ROWS, COLUMNS));

  // going up
  if(row - 1 >= 0 && table[row - 1][column] > table[row][column]) 
    result = max(result, 1 + DFS(table, solutionTable, row - 1, column, ROWS, COLUMNS));

  // going right
  if(column + 1 < COLUMNS && table[row][column + 1] > table[row][column]) 
    result = max(result, 1 + DFS(table, solutionTable, row, column + 1, ROWS, COLUMNS));

  // going left
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
