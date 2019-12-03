#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>

#include "maxscore.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


int main(){
    int r, c;
    ifstream f("input.txt");
    if (f.is_open() == false){
        cout << "Could not find file, sorry" << endl;
        return 0;
    }
    f >> r >> c;
    
    //Sets up the array
    int** arr = new int*[r];
    for(int i = 0; i < r; i++)
        arr[i] = new int[c];
    
    //Fills in the array
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            f >> arr[i][j];
    
    //Initial call to start algo
    MatrixScore maximize(arr, r, c);
    
    ofstream output_file;
    output_file.open("output.txt");
    int score = maximize.getScoreWrapper();

    output_file <<  "Max Score is " << score << endl << maximize.getScorePath();
    output_file.close();
    return 0;
}
