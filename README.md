# Jug Riddle
This project solves the popular jug riddle where you have two jugs (jug A and jug B) with one of them able to hold three gallons (A) and the other able to hold five gallons. The task is to get exactly 4 gallons of water in the jug B using only six steps
* Fill A entirely
* Fill B entirely
* Empty A
* Empty B
* Pour contents of A into B
* Pour contents of B into A

This project also gets user input so that each jug size can be manually chosen as well as the goal. It will then find the fastest solution to reach the goal. 

## Solution
The solution involves creating a graph of all the possible combinations of each step and running an algorithm to find the quickest path. The weight of each edge of the graph is defaulted to 1, but can be changed in main.cpp when creating a Jug object. The success message also contains the sum of all the weights after the word "success". An error message will be outputted if there is no solution.

Ex. If Jug A's size is 3 gallons, Jug B's size is 5 gallons, and goal is 4 gallons
* fill B
* pour B A
* empty A
* pour B A
* fill B
* pour B A
* empty A
* success 7

Note. the program looks for Jug A being empty and Jug B containing the goal so even though the riddle is technically solved while A is full, the program will always make sure Jug A is empty before giving us a success.

## Getting Started
There are a few prerequisites before using this project.
* Download and set up a c++ compiler (MinGW)
* Either clone this repository in your development environment or simply download the zip file
* Compile each .cpp file (g++ main.cpp Jug.cpp)
* run the executable

You will be prompted to enter the size of jug A, B, and the goal. The program will then calculate the fastest method of reaching the goal in jug B while considering the weight of each transaction in the graph (defaulted to 1). The solution will be stored in a string that will be outputted to the terminal. Error messages will be outputted with invalid input or no solution.
