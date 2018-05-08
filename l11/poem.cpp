#include <iostream>
#include <cmath>
using namespace std;

/*
    Author: Alessandra Vertrees
    Course: CSCI-136
    Instructor: Nick Crister
    Assignment: Lab 11D
    
    Description:
    Fix this program poem.cpp. It should still keep creating poems, but all dynamically allocated
    memory should get deleted when it is not needed.
      
    Compilationg Command:
    g++ poem.cpp -o poem

*/

string * createAPoemDynamically() {
    string *p = new string;
    *p = "Roses are red, violets are blue\n";
    return p;
}

int main() {
    string *p;
    while(true) {
        p = createAPoemDynamically();

        // assume that the poem p is not needed at this point
        cout << *p;
        delete p;
    }
    
    delete p;
}