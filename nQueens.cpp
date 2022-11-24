/*
 * Name: Lukas Bostick
 * Date Submitted: November 21, 2022
 * Lab Section: 003
 * Assignment Name: Lab 09
 */

#include <iostream>
#include <vector>

using namespace std;

void printArray(vector<vector<int>> arr) {
    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr.size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//function responsible for checking validity of placed queen
bool checkAbove(int currRow, vector<vector<int>> &arr) {
    //find point
    int currCol;
    for(int i = 0; i < arr.size(); i++) {
        if(arr[currRow][i] == 1) { currCol = i; }
    }
    
    //check attackable straight line
    for(int i = 0; i < currRow; i++) {
        if(arr[i][currCol] == 1) {return false;}
    }

    //check attackable left diagonal line
    int tempY = currCol-1;
    int tempX = currRow-1;
    while(tempX > -1 && tempY > -1) {
        if(arr[tempX][tempY] == 1) {return false;}
        tempY--;
        tempX--;
    }

    //check attackable right diagonal line
    tempY = currCol+1;
    tempX = currRow-1;
    while(tempX > -1 && tempY < arr.size()) {
        if(arr[tempX][tempY] == 1) {return false;}
        tempY++;
        tempX--;
    }

    return true;
}

//recursive function that uses recursion to find how many solutions there are
//for placing n queens on an nxn chess board
void nQueens(int currRow, vector<vector<int>> &arr, int &numS, int numQ) {
    //call checkAbove, checking every row above
    if(!checkAbove(currRow, arr)) { return; }

    //once grid is found to be valid, if there are n queens in the nxn grid,
    //a solution is found and increment numS.
    if(numQ == arr.size()) { 
        numS++; 
    }
    
    //base case (after checkAbove... last row must be checked and
    //can't do currRow == size, since the following call would cause 
    //a seg fault in arr[currRow+1].)
    if(currRow == arr.size() - 1) return; 
    

    //call itself recursively, adding a new row to check
    currRow++;
    numQ++;
    for(int i = 0; i < arr.size(); i++) {
        arr[currRow][i] = 1;
        
        nQueens(currRow, arr, numS, numQ);
        arr[currRow][i] = 0;
    }
}

//the initial function that calls the recursive overloaded function
//n times for each possible queen position in the first row.
int nQueens(int n) {
    vector<vector<int>> arr(n, vector<int>(n, 0));
    int numS = 0;
    int numQ = 1;
    for(int i = 0; i < n; i++) {
        arr[0][i] = 1;

        nQueens(0, arr, numS, numQ);
        arr[0][i] = 0;
    }
    return numS;
}

/*
int main()
{
    cout << "" << nQueens(7) << endl;
}
*/
