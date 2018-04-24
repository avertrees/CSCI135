#include <iostream>
using namespace std;

/*
    Author: Alessandra Vertrees
    Course: CSCI-136
    Instructor: Nick Crister
    Assignment: Lab 10A
    
    Description:
        The program uses the struct 'Time' in the functions 'minutesUntil' and 'minutesSinceMidnight' to determine how many minutes are between two moments in time.
    
    Compilationg Command:
    g++ -std=c++11 time.cpp -o time

*/


//Time is the struct and time is the parameter
//Task A

int minutesSinceMidnight(Time time);
//bool test_minutesSinceMidnight();

int minutesUntil(Time earlier, Time later);
//bool test_minutesUntil();

/*
//Task B
Time addMinutes(Time time0, int min);
bool test_addMinutes();

//Task C
create new struct TimeSlot
create new struct Movie
TimeSlot printTimeSlot(TimeSlot ts);
bool test_printTimeSlot();

//Task D
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie);
bool test_scheduleAfter();

//Task E
bool timeOverlap(timeSlot tsl, TimeSlot ts2);
bool test_timeOverlap();

*/

struct Time {
    int h;
    int m;
}; //structs end in a semicolon

void printTime(Time time) {
    cout << time.h << ":" << time.m;
}

int main() {
    /*bool resMinutesSinceMidnight = test_minutesSinceMidnight();//define booleon to run test
    cout << "TESTING_minutesSinceMidnight" << endl;
    
    bool resMinutesSinceMidnight = test_minutesUntil();
    cout << "TESTING_minutesUntil" << endl;
    if ((!resMinutesSinceMidnight)&&(!resMinutesUntil)){  //if result is not true
        cout << "FAILED_TESTS" << endl;
    } else {    //if result is true
        cout << "PASSED_TESTS" << endl;
    }
    */
    
    Time morningClass = {8, 10};
    Time myAlarm;
    
    myAlarm = morningClass;
    
    printTime(morningClass); // will print 8:10
    cout << endl;
    

    cout << minutesSinceMidnight( {8,10} ) << endl;
    cout << minutesUntil( {8,10}, {8, 15} ) << endl;
           
}

int minutesSinceMidnight(Time time){
    //midnight = 0,0
    //time since midnight in h, m
    //mins = time.h*60 + time.m
    //return int minutes
    
    int mins = 0;
    mins = (time.h * 60) + time.m;
    return mins;
}

/*
bool test_minutesSinceMidnight(){
    const int LEN=3;    //length of array = 3 bc we are testing three cases
    Time test_n[LEN]={{8,10},{12,00},{23,59}};
    int res[LEN] = {490, 720, 1439}; 
    bool pass = false;  //if one cases passes, it is false
    bool allpass = true;    //if all cases pass, it is ture
    for(int i=0; i<LEN; i++){ //iterate through each array
        pass = minutesSinceMidnight(test_n[i]) == res[i];                    
        allpass = allpass && pass;
        if(!pass){  //if there is an error, print it
            cout << "tIn:" << test_n[i]
                << "tReturned:" << minutesSinceMidnight[i]
                << "texpected:" << res[i] << endl;
        } 
    }
    return allpass; //return the value of all pass
}
*/

int minutesUntil(Time earlier, Time later){
    //turn both times into minutes
    int earlierMins = minutesSinceMidnight(earlier);
    int laterMins = minutesSinceMidnight(later);
    int diff = 0;
    
    //check if 'earlier' is actually less than 'later'
    if(earlierMins < laterMins){ // if earlier is less than later, compute: later - earlier
        diff = laterMins - earlierMins;
    } else { // if false, compute: earlier - later
        diff = earlierMins - laterMins;
    }
    
    return diff;
}

/*

bool test_MinutesUntil(){
    const int LEN=3;    //length of array = 3 bc we are testing three cases
    Time test_a[LEN]={{8,10},{23,59},{10,30}};
    Time test_b[LEN]={{12,00},{12,00},{13,40}};
    int res[LEN] = {230, 721, 190}; 
    bool pass = false;  //if one cases passes, it is false
    bool allpass = true;    //if all cases pass, it is ture
    for(int i=0; i<LEN; i++){ //iterate through each array
        pass = minutesUntil(test_a[i], test_b[i]) == res[i];                    
        allpass = allpass && pass;
        if(!pass){  //if there is an error, print it
            cout << "ta:" << test_a[i]
                << "tb:" << test_b[i]
                << "tReturned:" << minutesUntil[i]
                << "texpected:" << res[i] << endl;
        } 
    }
    return allpass; //return the value of all pass
}

*/

/*Time addMinutes(Time time0, int min){
    //this function should create and return a new moment of time that is 'min' minutes after     
    //'time0'.
    //ie. addMinutes({}
}

bool test_addMinutes(){
//Time {h, m}
// minutesUntil({10, 30}, {13, 40}) should return 190 minutes
}

*/


