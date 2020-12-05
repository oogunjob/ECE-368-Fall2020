#ifndef __PA6__
#define __PA6__

int Evaluate(char * tablefile, char * sequencefile);
int strictlyIncreasing(short sequence[], int length);
int maximalStart(short ** table, short * start, short rows, short columns);
int maximalEnd(short ** table, short * end, short rows, short columns);

int findSequence(char * tablefile, char * tabletextfile, char * sequencefile);
int longestIncreasingPath(short ** table, short ** solutionTable, short * Row_Column, short rows, short columns);
int DFS(short ** table, short ** solutionTable, int row, int column, int ROWS, int COLUMNS);
int max(int x, int y);

#endif