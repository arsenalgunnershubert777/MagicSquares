#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <vector>
#include "MagicSquares.h"

#include "MagicSquares_Greedy.h"
int main() {



	bool isCorrectInput = false;
	int type;
	//std::MagicSquares magicTest; //create object
	std::cout << "Type 1 for brute force and 2 for greedy" << std::endl;
	std::cin >> type;
	if (type == 1) {
	    int size;
        std::cout << "Enter size" << std::endl;
        std::cin >> size;
	    std:: MagicSquares magicTest;
	    magicTest.printMagicSquares(size);
	}
	else if (type == 2) {
	    int size;
        std::cout << "Enter size" << std::endl;
        std::cin >> size;
        std::MagicSquares_Greedy magicTest(size);

        magicTest.runComputations();

	}


	//std::cout << "Enter the size of a magic square: ";




    /*while (!isCorrectInput) {//make sure user input is correct

        while (!(std::cin >> size)) {
            std::cout << "Please enter odd integer greater than or equal to 3: "<<std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }

        if ((3 <= size) && (size%2 == 1)){
            isCorrectInput = true;
        }
        else {
            std::cout << "Please enter odd integer between 3 and 15: "<<std::endl;
            isCorrectInput = false;
        }
    }*/
    /*std::map <int, std::vector<int>> map;
    std::vector<int> vector;
    vector.push_back(2);
    map.insert(std::pair<int,std::vector<int>>(1,vector));
    map.at(1).push_back(3);
    std::vector<int>* tempVector = &map.at(1);
    tempVector->push_back(4);
    for (std::vector<int> :: iterator it = map.at(1).begin(); it != map.at(1).end(); ++it ) {
        std::cout << *it << std::endl;
    }
    for (std::vector<int> :: iterator it = tempVector->begin(); it != tempVector->end(); ++it ) {
        std::cout << *it << std::endl;
    }*/







    return 0;
}