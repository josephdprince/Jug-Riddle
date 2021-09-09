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
