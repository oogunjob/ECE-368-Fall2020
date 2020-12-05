#ifndef __PA6__
#define __PA6__

int Evaluate(char * tablefile, char * sequencefile);
int strictlyIncreasing(short sequence[], int length);
int maximalStart(short ** table, short * start, short rows, short columns);
int maximalEnd(short ** table, short * end, short rows, short columns);

int findSequence(char * tablefile, char * tabletextfile, char * sequencefile);
int longestIncreasingPath(short ** table, short ** solutionTable, short rows, short columns);
int DFS(short ** table, short ** solutionTable, short row, short column, short ROWS, short COLUMNS);
void findPath(short ** table, short * sequenceRow, short * sequenceColumn, short row, short column, short ROWS, short COLUMNS, int index, int length);
int computePath(short ** table, short row, short column, short ROWS, short COLUMNS);
int max(int x, int y);
int findLargest(int directions[]);

#endif