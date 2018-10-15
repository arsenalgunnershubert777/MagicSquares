//
// Created by Hubert Zhao on 10/14/2018.
//

#ifndef MAGICSQUARES_MAGICSQUARES_GREEDY_H
#define MAGICSQUARES_MAGICSQUARES_GREEDY_H


#include<vector>
#include<map>
#include<set>
#include <queue>


namespace std {
    class MagicSquares_Greedy {

    public:
        MagicSquares_Greedy(int n);

        ~MagicSquares_Greedy();

        void runComputations();//method for printing squares

    private:
        vector <int> magicSquareVector;
        vector<int> magicSquareComplement;

        map<int, set<int> > usedMap;


        set<int> checkPoints;
        vector<vector<int> > magicSquares;

        int index = -1;
        bool done = false;
        const int n;
        const int colRowDiagSum;
        bool checkSum();
        void permute();
        void fillToCheckpoint();
    };


}




#endif //MAGICSQUARES_MAGICSQUARES_GREEDY_H
