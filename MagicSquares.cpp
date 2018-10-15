//
// Created by Hubert Zhao on 9/21/2018.
//



#include "MagicSquares.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <fstream>
using namespace std;

MagicSquares::MagicSquares() {
    // TODO Auto-generated constructor stub

}

MagicSquares::~MagicSquares() {
    // TODO Auto-generated destructor stub
}

void MagicSquares::printMagicSquares(int n) { //method for finding magic squares
    ofstream myfile; //writes to log file
    myfile.open("log.txt");

    timeval *total1 = new timeval; //records time stamps for analysis
    gettimeofday(total1, NULL);//first time stamp for initialization
    myfile << "init: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    cout << "init: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    myfile << endl;
    cout << endl;




    int rowSum[n];
    int columnSum[n];
    int diagonalSum[2];


    //below are variables for the algorithm
    //the method has a brute force algorithm to go through all possible permutations
    //each new permutation is checked by an algorithm that breaks immediately when one of the many checks determines the square not to be magic
    int numSquares = 0;

    bool isTwo = true;
    int w = 3;
    int sum = 0;
    int swapTrack[n*n-2];
    int checkSum[2*n + 2];
    int trackOrder[n*n-2][n*n];
    int temp = 0;

    bool isMagicSquare;
    bool searchingForMagicSquare;
    bool skip = false;
    vector <int> matrixArray;
    vector <int> tempVector;
    vector <int> tempVector2;
    vector <int> :: iterator it;
    vector <int> :: iterator it2;
    vector <int> magicSquareTrack;

    int tempSum = 0;


    for (int i = 0; i < n*n - 2; i++) {
        swapTrack[i] = 0;
        trackOrder[i][0] = 0;

    }
    for (int k = 0; k < n*n; k++) {//first populates magic square in increasing order
        if (k != 0) {
            matrixArray.insert(matrixArray.end(), matrixArray.at(k-1) + 1);
        }
        else {
            matrixArray.insert(matrixArray.end(), 1);
        }
    }



    gettimeofday(total1, NULL); //time stamp to start computations
    myfile << "start: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    cout << "start: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;

    myfile << endl;
    cout << endl;






    while (w != n*n+1) {//this algorithm processes the squares as a vector
        //it will go through all the permutations in increasing order

        if (isTwo) { //this side will flip the last two numbers of the vector

            isTwo = false;
            sum++;
            temp = matrixArray.at(n*n-1);
            matrixArray.at(n*n-1) = matrixArray.at(n*n-2);
            matrixArray.at(n*n-2) = temp;

            searchingForMagicSquare = true;
            isMagicSquare = true;


        }
        else {//this side will permute more than the last two numbers in order

            sum++;
            if (!skip) {
                w = 3;
                swapTrack[w-3]++;
                trackOrder[w-3][0]++;
            }
            while (true) {

                if (swapTrack[w-3] < w) {

                    tempVector.clear();
                    tempVector2.clear();

                    trackOrder[w-3][swapTrack[w-3]] = matrixArray.at(n*n-w);


                    it = matrixArray.begin() + n*n - w; //variable w tracks working position of permutations
                    it2 = matrixArray.end();
                    tempVector.insert(tempVector.end(), it, it2); //part of vector is removed and that part will be sorted with next unused number in order
                    tempVector2.insert(tempVector2.end(), it, it2);
                    matrixArray.erase(it, it2);

                    for (int m = 0; m < swapTrack[w-3]; m++) {//numbers already used to lead permutation of a sequence are removed for consideration to begin the series of numbers being added back to the vector
                        tempVector.erase(remove(tempVector.begin(), tempVector.end(), trackOrder[w-3][m+1]), tempVector.end());

                    }



                    int min; //gets minimum value of numbers that have not been used to start this permutation
                    //keeps it in increasing order
                    for (int i = 0; i < tempVector.size(); i++) {
                        if (i == 0) {
                            min = tempVector.at(0);
                        }
                        else if (tempVector.at(i) < min) {
                            min = tempVector.at(i);
                        }
                    }


                    //gets lowest number not already used
                    tempVector2.erase(remove(tempVector2.begin(), tempVector2.end(), min), tempVector2.end()); //will remove that beginning number from this vector, since beginning number will go before
                    sort(tempVector2.begin(), tempVector2.end());//sorts the rest of the numbers being added for a reset
                    tempVector2.insert(tempVector2.begin(), min); //adds beginning number to front
                    matrixArray.insert(matrixArray.end(), tempVector2.begin(), tempVector2.end()); //adds the rest of the numbers back to main vector

                    searchingForMagicSquare = true;
                    isMagicSquare = true;
                    skip = false;


                    break;
                }
                else { //checks if all permutations have been made at a certain level (how many numbers are used) and moves on to the next level
                    for (int i = 0; i <= w-3; i++) {//ie permuting the last 3 numbers until they are all done and moving left one to permute 4 numberes
                        swapTrack[i] = 0;
                        for (int p = 0; p < w-1; p++) {
                            trackOrder[w-3][p] = 0;
                        }

                    }
                    w++;
                    if (w == n*n+1) {
                        break;
                    }
                    else {
                        swapTrack[w-3]++;
                        trackOrder[w-3][0]++;
                    }
                }

            }

            isTwo = true;
        }
        while (searchingForMagicSquare && isMagicSquare) {//checks for magic squares

            if (isMagicSquare) {//checks sums of rows
                tempSum = 0;

                for (int e = 0; e < n; e++) {
                    for (int f = 0; f < n; f++) {
                        tempSum += matrixArray.at((e+1)*n + f  - (n-1) -1);
                    }
                    checkSum[e+n] =  tempSum;
                    tempSum = 0;
                    if (checkSum[e+n] != (n*(n*n + 1))/2) {
                        isMagicSquare = false;

                        break;
                    }
                }
            }


            if (isMagicSquare) {//checks sum of columns
                tempSum = 0;

                for (int c = 0; c < n; c++) {

                    for (int d = 0; d < n; d++) {
                        tempSum += matrixArray.at((d+1)*n-(n-1) + c -1);
                    }
                    checkSum[c] =  tempSum;
                    tempSum = 0;
                    if (checkSum[c] != (n*(n*n + 1))/2) {
                        isMagicSquare = false;
                        searchingForMagicSquare = false;
                        break;
                    }
                }
            }

            if (isMagicSquare) {//checks sum of diagonals
                tempSum = 0;

                for (int g = 0; g < 2; g++) {
                    for (int h = 0; h < n; h++) {
                        if (g == 0) {
                            tempSum += matrixArray.at((1 + h)*(n+1) - n-1);
                        }
                        else{
                            tempSum += matrixArray.at((1 + h)*(n-1));
                        }


                    }
                    checkSum[2*n + g] = tempSum;
                    tempSum = 0;
                    if (checkSum[2*n + g] != (n*(n*n + 1))/2) {
                        isMagicSquare = false;
                        searchingForMagicSquare = false;
                        break;
                    }

                }
            }
            if (isMagicSquare) {
                numSquares++;
                searchingForMagicSquare = false;
                magicSquareTrack.insert(magicSquareTrack.end(), matrixArray.begin(), matrixArray.end());//stores squares in a vector

               // cout << numSquares << ": ";
                //myfile << numSquares << ": ";
                /*for (int i = 0; i < n*n; i++) {
                    cout << matrixArray.at(i);
                    myfile << matrixArray.at(i);

                }*/

                gettimeofday(total1, NULL);
                myfile << numSquares << ": sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
                cout << numSquares << ": sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
                int count = 0;
                for (vector<int> :: iterator it = matrixArray.begin(); it != matrixArray.end(); ++it ) {
                    if (count < n - 1) {
                        cout << *it <<" ";
                        myfile << *it << " ";
                        count++;
                    }
                    else {
                        cout << *it << endl;
                        myfile << *it << endl;
                        count = 0;
                    }
                }



                cout << endl;
                myfile << endl;


            }

        }

    }



    gettimeofday(total1, NULL);
    myfile << "finish: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    cout << "finish: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;






    /*int matrix[numSquares][n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[0][i][j] = 0;
        }
    }


    int count = 0;

    for (int i = 0; i < numSquares; i++ ) {//converts vector to square arrays
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                matrix[i][j][k] = magicSquareTrack.at(count);
                count++;
            }
        }

    }

    magicSquareTrack.clear();

    cout << endl;
    //print out magic squares
    for (int k = 0; k < numSquares; k++) {
        cout << "Magic Square #" << k+1 << " is:" << "\n" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[k][i][j] < 10) {
                    cout << matrix[k][i][j] << "    ";
                }
                else if (matrix[k][i][j] < 100) {
                    cout << matrix[k][i][j] << "   ";
                }
                else {
                    cout << matrix[k][i][j] << "  ";
                }
            }
            cout << endl;

        }
        cout << endl;

        //verify sum

        for (int i = 0; i < n; i++) {
            rowSum[i] = 0;
            for (int j = 0; j < n; j++) {
                rowSum[i] += matrix[k][i][j];
            }

        }
        cout << "Checking the sums of every row:      ";
        for (int i = 0; i < n; i++) {
            cout << rowSum[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            columnSum[i] = 0;
            for (int j = 0; j < n; j++) {
                columnSum[i] += matrix[k][j][i];
            }

        }
        cout << "Checking the sums of every column:   ";
        for (int i = 0; i < n; i++) {
            cout << columnSum[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < 2; i++) {
            diagonalSum[i] = 0;
            for (int j = 0; j < n; j++) {
                if (i == 0) {
                    diagonalSum[i] += matrix[k][j][j];
                }
                else {
                    diagonalSum[i] += matrix[k][j][n-1-j];
                }
            }

        }
        cout << "Checking the sums of every diagonal: ";
        for(int i = 0; i < 2; i++) {
            cout << diagonalSum[i] << " ";
        }
        cout << endl;
        cout << endl;

    }

    gettimeofday(total1, NULL);
    myfile << "donePrint: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    cout << "donePrint: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    */
    delete total1;



}




