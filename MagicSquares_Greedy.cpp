//
// Created by Hubert Zhao on 10/14/2018.
//

#include "MagicSquares_Greedy.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sys/time.h>
#include <fstream>
using namespace std;

MagicSquares_Greedy::MagicSquares_Greedy(int size):n(size),colRowDiagSum(size*(size*size+1)/2) {
    for (int i = 0; i < n*n; i++) { //initialize needed data structures

        magicSquareComplement.push_back(i+1);//initialize magic square complement with ascending order

        checkPoints.insert((i+1)*n - 1); //checkpoints at each row
        checkPoints.insert((n-1)*n + i); //checkpoints at each column

        set<int> magicSquareSet;
        usedMap.insert(pair<int,set<int> >(i,magicSquareSet)); //initialize unused map
    }

}

MagicSquares_Greedy::~MagicSquares_Greedy() {}

void MagicSquares_Greedy::runComputations() { //method for finding magic squares
    ofstream myfile; //writes to log file
    myfile.open("log_greedy.txt");

    timeval *total1 = new timeval; //records time stamps for analysis
    gettimeofday(total1, NULL);//first time stamp for initialization
    myfile << "start: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    myfile << endl;
    cout << "start: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    cout << endl;



    while (!done) {
        /*for (std::vector<int> :: iterator it = magicSquareVector.begin(); it != magicSquareVector.end(); ++it ) {
            cout << *it << " ";
        }
        cout << endl;*/
        //cout << "hereA" << endl;
        if (checkPoints.find(index) != checkPoints.end()) { //if not at checkpoint (index starts at -1 initially)
            //cout << "hereB" << endl;
            if (checkSum()) {
                if (index == n * n - 1) {
                    //cout << "hereC" << endl;
                    gettimeofday(total1, NULL);
                    magicSquares.push_back(magicSquareVector);

                    myfile << magicSquares.size() << ": sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
                    cout <<  magicSquares.size() << ": sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
                    int count= 0;
                    for (vector<int> :: iterator it = magicSquareVector.begin(); it != magicSquareVector.end(); ++it ) {
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
                    myfile << endl;
                    cout << endl;

                    permute();
                } else {
                    //cout << "hereD" << endl;
                    fillToCheckpoint();
                }
            } else {
                //cout << "hereE" << endl;
                permute();
            }

        } else {
            //cout << "hereF" << endl;
            fillToCheckpoint();

        }


    }
    gettimeofday(total1, NULL);//first time stamp for initialization
    myfile << "finish: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    cout << "finish: sec: " << total1->tv_sec << " usec: " << total1->tv_usec << endl;
    delete total1;






}

bool MagicSquares_Greedy::checkSum() {
    if (index <= n*(n-1) - 1) { //checking first n-1 rows
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum+=magicSquareVector.at(index-i);
        }
        if (sum == colRowDiagSum) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (index == n*(n-1)) { //checking first column and top right to bottom left diagonal
        int sumCol = 0;
        int sumDiag = 0;
        for (int i = 0; i < n; i++) {
            sumCol+= magicSquareVector.at( index - i*n);
            sumDiag += magicSquareVector.at(index - i*(n-1));
        }
        if (sumCol == colRowDiagSum && sumDiag == colRowDiagSum){
            return true;
        }
        else
            return false;
    }
    else if (index == n*n - 1) {//checking last column, last row, and top left to bottom right diagonal
        int sumCol = 0;
        int sumDiag = 0;
        int sumRow = 0;
        for (int i = 0; i < n; i++) {
            sumCol+= magicSquareVector.at(index - i*n);
            sumDiag += magicSquareVector.at(index - i*(n+1));
            sumRow += magicSquareVector.at(index - i);
        }
        if (sumCol == colRowDiagSum && sumDiag == colRowDiagSum && sumRow == colRowDiagSum){
            return true;
        }
        else
            return false;
    }


    else { //checking middle n - 2 columns
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum+=magicSquareVector.at(index-i*n);
        }

        if (sum == colRowDiagSum) {
            return true;
        }
        else {
            return false;
        }
    }
}

void MagicSquares_Greedy::permute() {
    //if there are left values, change,
    while (true) {

        set<int> used = usedMap.at(index);
        int valueOn = -1;
        sort(magicSquareComplement.rbegin(), magicSquareComplement.rend());
        //cout << "here1" <<  endl;
        //cout << "size" << magicSquareComplement.size() << endl;
        for (std::vector<int>::reverse_iterator rit = magicSquareComplement.rbegin();
             rit != magicSquareComplement.rend(); ++rit) {
            //cout << "here2" <<  endl;
            if (used.find(*rit) == used.end()) {
                valueOn = *rit;
                break;
            }
        }
        if (valueOn != -1) {
            magicSquareComplement.push_back(magicSquareVector.back());
            magicSquareVector.pop_back();
            magicSquareVector.push_back(valueOn);//add to magicSquareVector
            magicSquareComplement.erase(remove(magicSquareComplement.begin(), magicSquareComplement.end(), valueOn),
                                        magicSquareComplement.end()); //remove from complement

            usedMap.at(index).insert(valueOn);
            break;

        } else {  //if not then move back
            usedMap.at(index).clear();

            magicSquareComplement.push_back(magicSquareVector.back());
            magicSquareVector.pop_back();
            index--;
            //cout << "index" << index << endl;
            if (index == -1) {
                done = true;
                break;
            }

        }
    }





}

void MagicSquares_Greedy::fillToCheckpoint() { //doesn't fill at current index


    do {
        index++;
        set<int> used = usedMap.at(index);

        //need to make sure not repeating values...
        //reverse iterate through unused to find first unused value and then add
        sort(magicSquareComplement.rbegin(), magicSquareComplement.rend()); //sort backwards
        int valueOn = -1;
        for (std::vector<int>::reverse_iterator rit = magicSquareComplement.rbegin();
             rit != magicSquareComplement.rend(); ++rit) {

            if (used.find(*rit) == used.end()) {
                valueOn = *rit;
                break;
            }
        }


        magicSquareVector.push_back(valueOn);//add to magicSquareVector
        magicSquareComplement.erase(remove(magicSquareComplement.begin(), magicSquareComplement.end(), valueOn), magicSquareComplement.end()); //remove from complement


        usedMap.at(index).insert(valueOn);

    } while (checkPoints.find(index) == checkPoints.end());







}
