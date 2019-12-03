# Longest-Matrix-Path
Algorithms Class Project

Project Decription:

In this problem, you are given a matrix of positive integers, and your goal is to maximize a sum byselecting one element from every column in the matrix, moving left-to-right.  As you move throughthe matrix column-by-column, though, there may be a penalty to your sum depending on how youmove relative to your previous two positions.  If the next row you select is between the previous twoselected rows, there is no penalty; however, there is a penalty of 2 to your sum for every row abovethe maximum of the previous two or below the minimum of the previous two.  You always start inthe first column of the matrix and your previous two rows are considered to be the top row.

For example, if you start with row 3 in column 1 of the matrix, there will be a penalty of 4,since 3 is 2 more than max(1,1).  If you then move to row 2 in column 2, there would be no penaltybecause 2 is between 1 and 3.  If you then moved to row 7, there would be a penalty of 8 because7 is 4 more than the max of 2 and 3.

The total “score” of the elements you select from the matrix will be the sum of the elements youselected, minus any penalties you accrued, and your algorithm should find the maximum possible score for the given matrix as well as the path taken to achieve.

My solution uses a memoized dynamic programming algorithm in c++11 to obtain the maximum score and path. Input (2 samples provided) has to come from a file input.txt (can change if you want, but need to change in main file) and output is written to output.txt.

To run: in terminal g++ *.cpp -o matrix OR g++ main.cpp maxScore.cpp
