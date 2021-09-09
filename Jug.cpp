#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

#include "Jug.h"

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
    this->Ca = Ca;
    this->Cb = Cb;
    this->N = N;
    this->cfA = cfA;
    this->cfB = cfB;
    this->ceA = ceA;
    this->ceB = ceB;
    this->cpAB = cpAB;
    this->cpBA = cpBA;

    start = new Vertex;
    start->A = 0;
    start->B = 0;

    adjaList = new list<Vertex*> [5000];
    adjaList[0].push_back(start);
    ++size;
}

Jug::~Jug() {}

int Jug::solve(string &solution) {
    if (!ValidInput()) {
        solution = "";
        return -1;
    }
    MakeGraph();
    ShortestPath();

    for (int i = 0; i < size; ++i) {
        if (adjaList[i].front()->A == 0 && adjaList[i].front()->B == N) {
            if (adjaList[i].front()->distance < 9223372036854775807) {
                SetSolution(solution, adjaList[i].front());
                return 1;
            }
        }
    }
    solution = "";
    return 0;
}

bool Jug::ValidInput() {
    if (cfA < 0) {
        return false;
    }
    if (cfB < 0) {
        return false;
    }
    if (ceA < 0) {
        return false;
    }
    if (ceB < 0) {
        return false;
    }
    if (cpAB < 0) {
        return false;
    }
    if (cpBA < 0) {
        return false;
    }
    if (Ca <= 0) {
        return false;
    }
    if (Cb < Ca) {
        return false;
    }
    if (Cb < N) {
        return false;
    }
    if (1000 < Cb) {
        return false;
    }

    return true;
}

bool Jug::compareVertices(Vertex *a, Vertex *b) {
    return (a->A == b->A) && (a->B == b->B);
}

void Jug::MakeGraph() {
    Vertex* temp;
    queue<Vertex*> q;
    q.push(start);

    while(!q.empty()) {
        //---------------Fill A---------------
        temp = Fill_A(q.front()); //calls the Fill A function and sets the appropriate data. Returns the new vertex or NULL if that vertex already existed in the adja list
        if (temp != NULL) {
            q.push(temp);
        }
        //---------------Fill B---------------
        temp = Fill_B(q.front());
        if (temp != NULL) {
            q.push(temp);
        }
        //---------------Empty A--------------
        temp = Empty_A(q.front());
        if (temp != NULL) {
            q.push(temp);
        }
        //---------------Empty B--------------
        temp = Empty_B(q.front());
        if (temp != NULL) {
            q.push(temp);
        }
        //---------------Pour A B-------------
        temp = Pour_AB(q.front());
        if (temp != NULL) {
            q.push(temp);
        }
        //---------------pour B A-------------
        temp = Pour_BA(q.front());
        if (temp != NULL) {
            q.push(temp);
        }

        q.pop();
    }
}

Vertex* Jug::Fill_A(Vertex *curr) {
    Vertex temp;

    temp.A = Ca;
    temp.B = curr->B;

    if (compareVertices(&temp, curr)) { //if the new vertex is equal to the old vertex then we have a cycle to the same node. I dont want to do that
        return NULL;
    }

    return New_Vertex(curr, temp, cfA, "fill A");
}

Vertex* Jug::Fill_B(Vertex *curr) {
    Vertex temp;

    temp.A = curr->A;
    temp.B = Cb;

    if (compareVertices(&temp, curr)) {
        return NULL;
    }

    return New_Vertex(curr, temp, cfB, "fill B");
}

Vertex* Jug::Empty_A(Vertex *curr) {
    Vertex temp;

    temp.A = 0;
    temp.B = curr->B;

    if (compareVertices(&temp, curr)) {
        return NULL;
    }

    return New_Vertex(curr, temp, ceA, "empty A");
}

Vertex* Jug::Empty_B(Vertex *curr) {
    Vertex temp;

    temp.A = curr->A;
    temp.B = 0;

    if (compareVertices(&temp, curr)) {
        return NULL;
    }

    return New_Vertex(curr, temp, ceB, "empty B");
}

Vertex* Jug::Pour_AB(Vertex *curr) {
    Vertex temp;
    int tempValA = curr->A;
    int tempValB = curr->B;
    int AEmpty = tempValA;
    int BFull = Cb - tempValB;

    if (AEmpty > BFull) {
        tempValA -= BFull;
        tempValB += BFull;
    }
    else {
        tempValA -= AEmpty;
        tempValB += AEmpty;
    }

    temp.A = tempValA;
    temp.B = tempValB;

    if (compareVertices(&temp, curr)) {
        return NULL;
    }

    return New_Vertex(curr, temp, cpAB, "pour A B");
}

Vertex* Jug::Pour_BA(Vertex *curr) {
    Vertex temp;
    int tempValA = curr->A;
    int tempValB = curr->B;
    int BEmpty = tempValB;
    int AFull = Ca - tempValA;

    if (BEmpty > AFull) {
        tempValB -= AFull;
        tempValA += AFull;
    }
    else {
        tempValB -= BEmpty;
        tempValA += BEmpty;
    }

    temp.A = tempValA;
    temp.B = tempValB;

    if (compareVertices(&temp, curr)) {
        return NULL;
    }

    return New_Vertex(curr, temp, cpBA, "pour B A");
}

Vertex* Jug::New_Vertex(Vertex* curr, Vertex temp, int weight, string path) {
    for (int i = 0; i < size; ++i) { //iterate through the adjacency lists to see if the new vertex already exists in our graph
        if (compareVertices(adjaList[i].front(), &temp)) { //if we find the vertex already in our graph
            curr->neighborWeight.push_back(make_pair(adjaList[i].front(), weight)); //essentially pointing the node we are at to the node we found (setting the weight)
            curr->tag.push_back(make_pair(adjaList[i].front(), path));
            for (int j = 0; j < size; ++j) {
                if (compareVertices(adjaList[j].front(), curr)) {
                    adjaList[j].push_back(adjaList[i].front());
                }
            }
            return NULL;
        }
    }

    Vertex *newVert = new Vertex;
    newVert->A = temp.A;
    newVert->B = temp.B;
    curr->neighborWeight.push_back(make_pair(newVert, weight));
    curr->tag.push_back(make_pair(newVert, path));

    for (int i = 0; i < size; ++i) {
        if (compareVertices(adjaList[i].front(), curr)) {
            adjaList[i].push_back(newVert);
        }
    }
    adjaList[size].push_back(newVert);
    ++size;
    return newVert;
}

void Jug::ShortestPath() {
    vector<Vertex*> unvisitedList;
    Vertex* currentV;

    for (int i = 0; i < size; ++i) {
        currentV = adjaList[i].front();
        currentV->distance = 9223372036854775807; //essentially infinity

        currentV->prev = NULL;
        unvisitedList.push_back(currentV);
    }

    start->distance = 0;
    currentV = start;

    while (!unvisitedList.empty()) {
        for (int i = 0; i < size; ++i) {
            if (compareVertices(adjaList[i].front(), currentV)) { //finding the index of currentV in our adjacency list
                for (unsigned j = 0; j < currentV->neighborWeight.size(); ++j) {
                    int dist = currentV->neighborWeight.at(j).second + currentV->distance; //getting the weight
                    if (dist < currentV->neighborWeight.at(j).first->distance) { //if that weight is less that the distance at the node then update it and its prev pointer
                        currentV->neighborWeight.at(j).first->distance = dist;
                        currentV->neighborWeight.at(j).first->prev = currentV;
                    }
                }
                for (unsigned j = 0; j < unvisitedList.size(); ++j) { //deleting the loc of the visited vertex from the vector
                    if (compareVertices(unvisitedList.at(j), currentV)) {
                        unvisitedList.erase(unvisitedList.begin() + j, unvisitedList.begin() + j + 1);
                    }
                }
                if (!unvisitedList.empty()) {
                    int min = unvisitedList.at(0)->distance;
                    int k = 0;
                    for (unsigned j = 0; j < unvisitedList.size(); ++j) { //find the next min distance
                        if (unvisitedList.at(j)->distance < min) {
                            min = unvisitedList.at(j)->distance;
                            k = j;
                        }
                    }
                    currentV = unvisitedList.at(k); //update the next currentV to hold the next min distance
                }
                i = size;
            }
        }
    }
}

void Jug::SetSolution(string &solution, Vertex* goal) {
    stack<Vertex*> s;
    Vertex* curr = goal;

    while (curr->prev != NULL) {
        s.push(curr);
        curr = curr->prev;
    }
    s.push(start); // while loop doesnt get start vertex

    solution = "";
    while (!s.empty()) {
        curr = s.top();
        s.pop();
        if (!s.empty()) {
            for (unsigned i = 0; i < curr->tag.size(); ++i) {
                if (compareVertices(curr->tag.at(i).first, s.top())) {
                    solution = solution + curr->tag.at(i).second;
                    solution = solution + '\n';
                }
            }
        }
    }

    ostringstream oss;
    string temp = "success";
    int path = goal->distance;
    string total;

    oss << temp << ' ' << path;

    total = oss.str();

    solution = solution + total;
}
