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
   if (head.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << endl << solution << endl;

    return 0;
}
