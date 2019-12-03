#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "maxscore.hpp"
using namespace std;

MatrixScore::MatrixScore(int** matrix, int rows, int cols){
    
    startArray = matrix;
    numRows = rows;
    numCols = cols;
}

int MatrixScore::getScoreWrapper(){
    
    //initial rOld and rNew variables, starting range
    int rOld = 1;
    int rNew = 1;
    
    //create map and initialize sentinl values to -500
    memoMap = new int**[numRows];
    for(int i = 0; i < numRows; i++){
        memoMap[i] = new int*[numRows];
        
        for (int j = 0; j < numRows; j++){
            memoMap[i][j] = new int[numCols];
            for (int k = 0; k < numCols; k++)
                memoMap[i][j][k] = -500;
        }
    }
    
    return memoMaximzeScore(rOld, rNew, 0, pathHolder);
}

int MatrixScore::memoMaximzeScore(int rOld, int rNew, int colNum, list<pair<int,int>> &path){
    
    //Initializing of vars
    list<pair<int,int>> tempScores;
    int maxScore;
    int* currCol = grabColArray(colNum); //Get values within the column
    int* penalties = getPenalty(rOld, rNew, currCol); //Get penalties assigned to each value in the column
    
    //If value is in map return
    if (memoMap[rOld-1][rNew-1][colNum] != -500){
        return memoMap[rOld-1][rNew-1][colNum];
    }
    
    //At last row which is a base case
    else if (colNum == numCols - 1){
        
        //Go through each value in column and subtract penalty from it, then push to temp scores list
        for (int i = 0; i < numRows; i++){
            int score = currCol[i] - penalties[i];
            tempScores.push_front(make_pair(score,i));
            tempScores.sort();
        }
        
        //Get maximum score of column
        maxScore = tempScores.back().first;
        
        //Make pair and add to reference path of max score and row it was found on
        path.push_front(make_pair(maxScore,tempScores.back().second));
        
        //Update Map
        memoMap[rOld-1][rNew-1][colNum] = maxScore;
    }
    
    else {
        for (int i = 0; i < numRows; i++){
            int score = currCol[i] - penalties[i] + memoMaximzeScore(rNew, i+1, colNum + 1, path);
            tempScores.push_front(make_pair(score,i));
            tempScores.sort();
        }
        
        //Get the maximum score of values in the column
        maxScore = tempScores.back().first;
        
        //Push pair of max score and the row it was found on
        path.push_front(make_pair(maxScore,tempScores.back().second));
        
        //Update memoization map
        memoMap[rOld-1][rNew-1][colNum] = maxScore;
    }

    return memoMap[rOld-1][rNew-1][colNum];
}

int* MatrixScore::grabColArray(int colNum){
    //Create 1d array
    int* arr = new int[numRows];
    
    //put value from each row of column you are looking for in the array
    for (int i = 0; i < numRows; i++)
        arr[i] = startArray[i][colNum];
    
    return arr;
}

int* MatrixScore::getPenalty(int rOld, int rNew, int* col){
    
    int* penaltyArr = new int[numRows];
    
    //Doing this so array arithmetic matches up with 0 indexing
    int newROld = rOld - 1;
    int newRNew = rNew - 1;
    
    //Variables to get range of free rows
    int lowerBound, upperBound;
    if (newROld <= newRNew){
        lowerBound = newROld;
        upperBound = newRNew;
    }
    
    else{
        lowerBound = newRNew;
        upperBound = newROld;
    }
    
    //Check if value is out range of free rows, add penalty to array
    int penalty = 0;
    for (int i = 0; i < numRows; i++){
        if (i < lowerBound)
            penalty = 2*(lowerBound - i);
        else if (i > upperBound)
            penalty = 2*(i - upperBound);
        
        penaltyArr[i] = penalty;
        penalty = 0;
    }
    return penaltyArr;
}

string MatrixScore::getScorePath(){
    
    //Based on how my memo function works, it fills in a list of pairs with the pair
    //being the score, and row picked for that score and that is what "patholder" is
    
    //Sort pathholder because since this is beginning we will find the max score, which after sorting
    //Will be in the back of list
    int rOld = 1, rNew;
    pathHolder.sort();
    int row = pathHolder.back().second;
    
    //Append to final path vector
    finalPath.push_back(row);
    
    //Update r new and pop pair from pathholder
    rNew = row +1;
    pathHolder.pop_back();
    
    //For each column starting in col 2 (first one done from original memo function call to get max score)
    for (int i = 1; i < numCols; i++){
        
        //Find new maximum value
        int value = memoMaximzeScore(rOld, rNew, i, pathHolder);
        
        //Search pathholder list for the new maximum
        for (list<pair<int,int>>::iterator listIT = pathHolder.end(); listIT != pathHolder.begin(); --listIT){
            
            //Once found push to final path vector and update new, and repeat loo
            if((*listIT).first == value){
                finalPath.push_back((*listIT).second);
                row = (*listIT).second;
                break;
            }
        }
        rOld = rNew;
        rNew = row + 1;
    }
    
    string result = "The path is: ";
    //Print path to terminal
    for (vector<int>::iterator it = finalPath.begin(); it != finalPath.end(); ++it){
        result += to_string(*it) + " ";
    }
    return result;
}
