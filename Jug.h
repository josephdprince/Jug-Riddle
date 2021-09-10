#include <iostream>
#include <list>
#include <vector>
using namespace std;

struct Vertex {
    vector<pair<Vertex*, int>> neighborWeight;
    vector<pair<Vertex*, string>> tag;
    int A;
    int B;
    Vertex *prev = NULL;
    long long distance;
};

class Jug {
 public:
    Jug(int,int,int,int,int,int,int,int,int);
    ~Jug();

    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution);
 private:
    // Ca == capacity of jug A
    // Cb == capacity of jug B
    // n == goal
    // cfA == the weight of the edge of filling A (for a graph)
    // cfB == the weight of the edge of filling B (for a graph)
    // ceA == the weight of the edge of emptying A (for a graph)
    // ceB == the weight of the edge of emptying B (for a graph)
    // cpAB == the weight of the edge of pouring A into B (for a graph)
    // cpBA == the weight of the edge of pouring B into A (for a graph)
    
    int Ca;
    int Cb;
    int N;
    int cfA;
    int cfB;
    int ceA;
    int ceB;
    int cpAB;
    int cpBA;
    int size = 0;
    Vertex *start;
    list<Vertex*> *adjaList;
    
    void MakeGraph();
    bool ValidInput();
    Vertex* Fill_A(Vertex*);
    Vertex* Fill_B(Vertex*);
    Vertex* Empty_A(Vertex*);
    Vertex* Empty_B(Vertex*);
    Vertex* Pour_AB(Vertex*);
    Vertex* Pour_BA(Vertex*);
    Vertex* New_Vertex(Vertex*, Vertex, int, string);
    bool compareVertices(Vertex*, Vertex*);
    void ShortestPath();
    void SetSolution(string&, Vertex*);
};
