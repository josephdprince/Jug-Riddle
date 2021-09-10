#include <iostream>
using namespace std;

#include "Jug.h"

int main() {

   int aSize;
   int bSize;
   int goal;
   string solution;

   cout << "Size of Jug A: ";
   cin >> aSize;
   cout << "Size of Jug B: ";
   cin >> bSize;
   cout << "Goal: ";
   cin >> goal;

   Jug head(aSize, bSize, goal, 1, 1, 1, 1, 1, 1);
   int errorNum = head.solve(solution);
   if (errorNum == -1) {
      cout << "\nError: Invalid Input\n";
   }
   else if (errorNum == 0){
      cout << "\nError: No Solution Found\n";
   }
   else {
      cout << endl << solution << endl;
   }

    return 0;
}
