#include <iostream>
using namespace std;

/*
    Author: Alessandra Vertrees
    Course: CSCI-136
    Instructor: Nick Crister
    Assignment: Lab 10E
    
    Description:
        The program uses the struct 'Time' in the functions 'minutesUntil' and 'minutesSinceMidnight' to determine how many minutes are between two moments in time.
    
    Compilationg Command:
    g++ -std=c++11 time.cpp -o time

*/
enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

struct Time {
    int h;
    int m;
}; 

struct Movie {
    string title;     
    Genre genre;    // only one genre per movie
    int duration;   // in minutes
};

struct TimeSlot {
    Movie movie;    // what movie
    Time startTime; // when it starts
};

//Time is the struct and time is the parameter
//Task A

int minutesSinceMidnight(Time time);
bool test_minutesSinceMidnight();

int minutesUntil(Time earlier, Time later);
bool test_minutesUntil();

//Task B
Time addMinutes(Time time0, int min);
bool test_addMinutes();

//Task D
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie);
// bool test_scheduleAfter(); -- not sure how to do this


//Task E
bool timeOverlap(TimeSlot ts1, TimeSlot ts2);
//bool test_timeOverlap(); -- in making


// VOID FUNCTIONS
void printTime(Time time) {
    cout << time.h << ":" << time.m;
}

void printMovie(Movie mv){
    string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

void printTimeSlot(TimeSlot ts) {
    //Back to the Future COMEDY (116 min) [starts at 9:15, ends by 11:11]
    // Time startTime = ts.StartTime;
    Movie mv = ts.movie; //separate movie
    Time endTime = addMinutes(ts.startTime, mv.duration); //declare end time
    printMovie(mv); //print movie
    cout << " [starts at " << ts.startTime.h << ":" << ts.startTime.m 
        << " , ends by " <<  endTime.h << ":" << endTime.m << "]" << endl;
}

int main() {

    cout << "TESTING_minutesSinceMidnight" << endl;
    bool resMinutesSinceMidnight = test_minutesSinceMidnight();//define booleon to run test

    cout << "TESTING_minutesUntil" << endl;    
    bool resMinutesUntil = test_minutesUntil();
    
    cout << "TESTING_addMinutes" << endl;    
    bool resAddMinutes = test_addMinutes();

    if ((!resMinutesSinceMidnight)||(!resMinutesUntil)||(!resAddMinutes)){
        cout << "FAILED_TESTS" << endl;
    } else {    //if result is true
        cout << "PASSED_TESTS" << endl;
    }

    Movie movie1 = {"Back to the Future", COMEDY, 116};
    Movie movie2 = {"Black Panther", ACTION, 134};
    Movie movie3 = {"A Quiet Place", DRAMA, 90};
    TimeSlot morning1 = {movie1, {9, 15}};
    printTimeSlot(morning1);  
    TimeSlot daytime1 = {movie2, {12, 15}};
    printTimeSlot(daytime1); 
    TimeSlot evening1 = {movie2, {16, 45}};
    printTimeSlot(evening1);
    TimeSlot daytime2 = {movie3, {16, 15}}; 
    printTimeSlot(daytime2);
    TimeSlot evening2 = {movie3, {19, 10}};
    printTimeSlot(evening2);
    printTimeSlot(scheduleAfter(evening2, movie3));

    //tests for overlap
    Movie movie4 = {"Back to the Future", COMEDY, 80};
    Movie movie5 = {"Black Panther", ACTION, 134};
    Movie movie6 = {"A Quiet Place", DRAMA, 63};
    TimeSlot morn1 = {movie4, {10, 30}};
    printTimeSlot(evening1);
    TimeSlot morn2 = {movie6, {8, 30}}; 
    printTimeSlot(daytime2);
    TimeSlot eve1 = {movie5, {19, 10}};

    cout << timeOverlap(morn1,morn2) << endl;
    cout << timeOverlap(morning1, daytime2) << endl;
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

bool test_minutesSinceMidnight(){
    const int LEN=3;    //length of array = 3 bc we are testing three cases
    Time test_a[LEN]={{8,10},{12,00},{23,59}};
    int res[LEN] = {490, 720, 1439}; 
    bool pass = false;  //if one cases passes, it is false
    bool allpass = true;    //if all cases pass, it is ture
    for(int i=0; i<LEN; i++){ //iterate through each array
        pass = minutesSinceMidnight(test_a[i]) == res[i];                    
        allpass = allpass && pass;
        if(!pass){  //if there is an error, print it
            cout << "tIn:" << test_a[i].h << ":" << test_a[i].m
                 << "tResult" << minutesSinceMidnight(test_a[i])
                << "texpected:" << res[i] << endl;
        } 
    }
    return allpass; //return the value of all pass
}

int minutesUntil(Time earlier, Time later){
    //turn both times into minutes
    int earlierMins = minutesSinceMidnight(earlier);
    int laterMins = minutesSinceMidnight(later);
    int diff = 0;
    
    diff = laterMins - earlierMins;

    return diff;
}

bool test_minutesUntil(){
    const int LEN=3;    //length of array = 3 bc we are testing three cases
    Time test_a[LEN]={{8,10},{13,40},{10,30}};
    Time test_b[LEN]={{12,00},{10,30},{13,40}};
    int res[LEN] = {230, -190, 190}; 
    bool pass = false;  //if one cases passes, it is false
    bool allpass = true;    //if all cases pass, it is ture
    for(int i=0; i<LEN; i++){ //iterate through each array
        pass = minutesUntil(test_a[i], test_b[i]) == res[i];                    
        allpass = allpass && pass;
        if(!pass){  //if there is an error, print it
            cout << "ta:" << test_a[i].h << ":" << test_a[i].m
                << "\ttb:" << test_b[i].h << ":" << test_b[i].m
                << "\ntResult" << minutesUntil(test_a[i], test_b[i])
                << "\ntexpected:" << res[i] << endl;
        } 
    }
    return allpass; //return the value of all pass
}

Time addMinutes(Time time0, int min){
    //this function should create and return a new moment of time that is 'min' minutes after     
    //'time0'.
    //ie. addMinutes({8, 10}, 75) should return {9, 25}
    //compute total minutes and turn into hours
            //make helper function?>? maybe not useful????
    int totalMinutes = minutesSinceMidnight(time0) + min;
    int h = totalMinutes/60;
    int m = totalMinutes%60;
    Time newTime = {h, m};

    return newTime;    
}

bool test_addMinutes(){
    //Time {h, m}
    const int LEN=1;    //length of array = 3 bc we are testing three cases
    Time test_a[LEN]= {{8,10}};
    int test_b[LEN]= {75};
    Time res[LEN] = {{9,25}}; 
    bool pass = false;  //if one cases passes, it is false
    bool allpass = true;    //if all cases pass, it is ture
    for(int i=0; i<LEN; i++){ //iterate through each array
        pass = ( (addMinutes(test_a[i], test_b[i]).h == res[i].h) && (addMinutes(test_a[i], test_b[i]).m == res[i].m) );                    
        allpass = allpass && pass;
        if(!pass){  //if there is an error, print it
            cout << "ta:" << test_a[i].h << ":" << test_a[i].m
                << "\ttb:" << test_b[i]
                << "\ntexpected:" << res[i].h << ":" << res[i].m << endl;
        } 
    }
    return allpass; //return the value of all pass
}

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie){
    //The function should produce and return a new 
    //TimeSlot for the movie nextMovie, scheduled immediately after the time slot ts.
    Movie movie = ts.movie; // new movie
    Time newStartTime = addMinutes(ts.startTime, movie.duration); // startTime = endTime
    TimeSlot newTimeSlot = {nextMovie, newStartTime}; //newTimeSlot
    return newTimeSlot;
}

/* Test for scheduleAfter that I cannot figure out how to test rn
bool test_scheduleAfter(){
    struct TimeSlot { movie, Time startTime }
    scheduleAfter(TimeSlot ts, Movie nextMovie)
    const int LEN=3;    //length of array = 3 bc we are testing three cases
    TimeSlot test_a[LEN]= {{{"A Quiet Place", DRAMA, 90},{14,10}},{{"Black Panther", ACTION, 134},{9, 15}},{{"Back to the Future", COMEDY, 116},{19, 10}}; //timeSlot
    Movie test_b[LEN]= {{"Back to the Future", COMEDY, 116},{"A Quiet Place", DRAMA, 90},{"Black Panther", ACTION, 134}};   //nextMovie
    TimeSlot res[LEN] = {{{"Back to the Future"},{}},{{"A Quiet Place", DRAMA, 90},{}},{{"Black Panther", ACTION, 134},{}}}; 
    bool pass = false;  //if one cases passes, it is false
    bool allpass = true;    //if all cases pass, it is ture
    for(int i=0; i<LEN; i++){ //iterate through each array
        pass = ( (scheduleAfter(test_a[i], test_b[i]).h == res[i].h) && (addMinutes(test_a[i], test_b[i]).m == res[i].m) );                    
        allpass = allpass && pass;
        if(!pass){  //if there is an error, print it
            cout << "ta:" << test_a[i].h << ":" << test_a[i].m
                << "\ttb:" << test_b[i]
                << "\ntexpected:" << res[i].h << ":" << res[i].m << endl;
        } 
    }
    return allpass; //return the value of all pass
}
*/

bool timeOverlap(TimeSlot ts1, TimeSlot ts2){
    /*The function should return true if the two time 
    slots overlap, otherwise return false.
    (Take into account the starting times of 
    the time slots and the duration of the scheduled movies.)
    Hint: You may use minutesUntil to check which time slot is
    earlier, then find the how long is the interval between 
    their starting times. 

    */
    bool res = false;

    Movie movie1 = ts1.movie;
    Time startTime1 = ts1.startTime;
    int dur1 = movie1.duration;

    Movie movie2 = ts2.movie;
    Time startTime2 = ts2.startTime;
    int dur2 = movie2.duration;

    int interval = minutesUntil(startTime1, startTime2);

    /*
    //They overlap if the movie duration 
    is greater than the interval between the time slots’ starting 
    times. Alternatively, converting times into minutes since midnight 
    can be a good idea as well.
    */

    //if interval is positive, startTime1 is earlier
    if (interval > 0) { 
        if (dur1 > interval) {
            res = true;
        } else {
            res = false;
        }
    } else if (interval < 0) { // startTime2 is earlier if int is negative
        int newInterval = minutesUntil(startTime2, startTime1);
        if (dur2 > newInterval){
            res = true;
        } else {
            res = false;
        }
    } else if (interval == 0) {
        res = true;
    }
    return res;
}

//bool test_timeOverlap();
    //test for timeOverlap that I may not have time to write
    //can we plz go over how to write tests for structs of structs next lab





