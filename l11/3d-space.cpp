#include <iostream>
#include <cmath>
using namespace std;

/*
    Author: Alessandra Vertrees
    Course: CSCI-136
    Instructor: Nick Crister
    Assignment: Lab 11A
    
    Description:
    Task A: function length() receives the coordinates of a point P passed as a pointer, 
    and computes the distance from the origin to the point P:
    
    Task B: receives the coordinates of two points (passed as pointers), 
    and returns the pointer of the point that is farther away from the origin.
    
    Compilationg Command:
    g++ 3d-space.cpp -o 3d-space or g++ -std=c++11 3d-space.cpp -o 3d-space

*/

struct Coord3D {
    double x;
    double y;
    double z;
};

//task A
double length(Coord3D *p);
bool test_length();

//task B
Coord3D * fartherFromOrigin(Coord3D *p1, Coord3D *p2);
bool test_fartherFromOrigin();

//task C
void move(Coord3D *ppos, Coord3D *pvel, double dt);

//taskE
//allocate memory and initiate
Coord3D* createCoord3D(double x, double y, double z);

// free memory
void deleteCoord3D(Coord3D *p);

int main() {
    Coord3D pointP = {10, 20, 30};
    Coord3D pointQ = {-20, 21, -22};
    Coord3D pos = {0, 0, 100.0};
    Coord3D vel = {1, -5, 0.2};
    
    //taskA
    if(test_length){
        cout << "passed tests for task A" << endl;
    }
    cout << length(&pointP) << endl; // would print 37.4166

    //taskB
    cout << "Address of P: " << &pointP << endl;
    cout << "Address of Q: " << &pointQ << endl << endl;

    Coord3D * ans = fartherFromOrigin(&pointP, &pointQ);
   
    cout << "ans = " << ans << endl; // So which point is farther?
   
    //taskC 
    move(&pos, &vel, 2.0); // struct pos gets changed
    cout << pos.x << " " << pos.y << " " << pos.z << endl;
    // prints: 2 -10 100.4
    
    //taskD
    double x, y, z;
    cout << "Enter position: ";
    cin >> x >> y >> z;
    Coord3D *ppos = createCoord3D(x,y,z);
    
    cout << "Enter velocity: ";
    cin >> x >> y >> z;
    Coord3D *pvel = createCoord3D(x,y,z);

    move(ppos, pvel, 10.0);

    cout << "Coordinates after 10 seconds: " 
         << (*ppos).x << " " << (*ppos).y << " " << (*ppos).z << endl;
    // prints: 65 6 107.7
    
    deleteCoord3D(ppos); // release memory
    deleteCoord3D(pvel);
}

double length(Coord3D *p){
    //dereference p first 
    double length = sqrt(pow((*p).x, 2.0) + pow((*p).y, 2.0) + pow((*p).z, 2.0));
    return length;
}            

bool test_length(){
    const int LEN=1;    //length of array = 3 bc we are testing three cases
    Coord3D test_a[LEN]={{10,20,30}};
    double res[LEN] = {37.4166}; 
    bool pass = false;  //if one cases passes, it is false
    bool allpass = true;    //if all cases pass, it is ture
    for(int i=0; i<LEN; i++){ //iterate through each array
        pass = length(&test_a[i]) == res[i];                    
        allpass = allpass && pass;
        if(!pass){  //if there is an error, print it
            cout << "ta:" << test_a[i].x << ":" << test_a[i].y << ":" << test_a[i].z
                << "\ntexpected:" << res[i] << endl;
        } 
    }
    return allpass; //return the value of all pass
}

//task B
Coord3D * fartherFromOrigin(Coord3D *p1, Coord3D *p2){
    //the coordinates of two points (passed as pointers), and returns the pointer of the point  
    //that is farther away from the origin.
    if(length(p1) > length(p2)) {
        return p1;
    } else {
        return p2;
    }
}

void move(Coord3D *ppos, Coord3D *pvel, double dt){
    /*gets the position and the velocity of an object and
    has to compute object’s new coordinates after the time interval dt.*/
    //update coordinates
    
    (*ppos).x = (*ppos).x+(*pvel).x*dt; 
    (*ppos).y = (*ppos).y+(*pvel).y*dt;
    (*ppos).z = (*ppos).z+(*pvel).z*dt;
}

Coord3D * createCoord3D(double x, double y, double z){
    Coord3D *p;
    p = new Coord3D;
    *p = {x, y, z};
    return p; //memory location of coord
}

void deleteCoord3D(Coord3D *p){
    delete p;
}
