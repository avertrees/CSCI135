#include <iostream>
#include <cmath>
using namespace std;

/*
    Author: Alessandra Vertrees
    Course: CSCI-136
    Instructor: Nick Crister
    Assignment: Lab 11F
    
    Description:
        
    Compilationg Command:
    g++ particle.cpp -o particle or g++ -std=c++11 particlecpp -o particle

*/

struct Coord3D {
    double x;
    double y;
    double z;
};

void deleteCoord3D(Coord3D *p);

struct Particle {
    Coord3D pos;
    Coord3D vel;
};
//dynamically creates Coord3D
Coord3D * createCoord3D(double x, double y, double z);

// dynamically allocate memory for a particle and initialize it
Particle * createParticle(double x, double y, double z, //Coord3D pos
                         double vx, double vy, double vz); //Coord3D vel

// set its velocity to (vx, vy, vz)
void setVelocity(Particle *p, double vx, double vy, double vz); //Coord3D vel

// get its current position
Coord3D getPosition(Particle *p); //Coord3D pos

// update particle's position after elapsed time dt
void move(Particle *p, double dt); //both vel and pos

// delete all memory allocated for the particle passed by pointer
void deleteParticle(Particle *p);

int main() {
    // make new particle
    Particle *p = createParticle(1.0, 1.5, 2.0, 0.1, 0.2, 0.3);
    double time = 0.0;
    double dt = 0.1;
    while(time < 3.0) {
        // update its velocity
        setVelocity(p, 10.0 * time, 0.3, 0.1);

        // move the particle
        move(p, dt);
        time += dt;

        // reporting its coordinates
        cout << "Time: " << time << " \t";
        cout << "Position: "
             << getPosition(p).x << ", "
             << getPosition(p).y << ", "
             << getPosition(p).z << endl;
    }
    // remove the particle, deallocating its memory
    deleteParticle(p);
}

/*expected output
$ ./a.out
Time: 0.1 	Position: 1, 1.53, 2.01
Time: 0.2 	Position: 1.1, 1.56, 2.02
Time: 0.3 	Position: 1.3, 1.59, 2.03
Time: 0.4 	Position: 1.6, 1.62, 2.04
*/

//Particle* createParticle(double x, double y, double z, double vx, double vy, double vz);
Particle * createParticle(double x, double y, double z, double vx, double vy, double vz){
    Particle *p;
    Coord3D *pos = createCoord3D(x, y, z);
    Coord3D *vel = createCoord3D(vx, vy, vz);

    p = new Particle;
    *p = {*pos, *vel};
    deleteCoord3D(pos);
    deleteCoord3D(vel);
    return p; //memory location of coord
}

Coord3D * createCoord3D(double x, double y, double z){
    Coord3D *p;
    p = new Coord3D;
    *p = {x, y, z};
    return p; //memory location of coord
}
// set its velocity to (vx, vy, vz)
//void setVelocity(Particle *p, double vx, double vy, double vz); //Coord3D vel
void setVelocity(Particle *p, double vx, double vy, double vz){
    Coord3D pvel = (*p).vel;
    pvel.x = vx;
    pvel.y = vy;
    pvel.z = vz;
    (*p).vel = pvel;
}

// get its current position
//Coord3D getPosition(Particle *p); //Coord3D pos
Coord3D getPosition(Particle *p){
    return (*p).pos;
}

// void move(Particle *p, double dt); //both vel and pos
void move(Particle *p, double dt){
    /*gets the position and the velocity of an object and
    has to compute object’s new coordinates after the time interval dt.*/
    //update coordinates
    Coord3D ppos = (*p).pos;
    Coord3D pvel = (*p).vel;

    ppos.x = ppos.x + pvel.x * dt; 
    ppos.y = ppos.y + pvel.y *dt;
    ppos.z = ppos.z + pvel.z *dt;

    *p = {ppos, pvel};
}

//void deleteParticle(Particle *p);
void deleteParticle(Particle *p){
    delete p;
}

void deleteCoord3D(Coord3D *p){
    delete p;
}
