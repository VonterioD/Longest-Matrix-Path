#ifndef MAXSCORE_H
#define MAXSCORE_H

#include <iostream>
#include <list>
#include <vector>
using namespace std;

class MatrixScore {
    
public:
    MatrixScore(int** matrix, int rows, int cols);
    int getScoreWrapper();
    int memoMaximzeScore(int rOld, int rNew, int colNum, list<pair<int,int>> &path);
    int* getPenalty(int rOld, int rNew, int* col);
    int* grabColArray(int colNum);
    string getScorePath();
    
    
private:
    int** startArray;
    int*** memoMap;
    int numRows;
    int numCols;
    vector<int> finalPath;
    list<pair<int,int>> pathHolder;
    
};



#endif
