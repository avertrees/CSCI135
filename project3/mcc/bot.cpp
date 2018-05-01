
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "bot.h"

using namespace std;

/*
Name: Alessandra Vertrees 
Instructor: Shankar
Class: CSCI 135
Assignment: Project 3

Description: ask is to program the robots’ logic so they do their work more efficiently. 
There is no hard cap on what you can do, the task is relatively open-ended. 
You can start with simple improvements, and progress towards more complex ones:

*/


const int MAX_ROWS = 40;
const int MAX_COLS = 40;
// const int MAX_DEBRIS = 40;
// const int MAX_ROBOT_NUM = 50;

int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions

//array of robot id's and location in program
int bots[MAX_ROWS][MAX_COLS];
	//reference 'bots[row][col] == id'

bool debris[MAX_ROWS][MAX_COLS]; // array of debris and location 
	//refernce 'debris[row][col] == true or 'debris[row][col] == false


bool findHelperBot = false;
//brokenBots = 0;

//needRepair[MAX_ROBOT_NUM][MAX_ROBOT_NUM]; //stores malfunction bot loc and id
	//reference 'needRepair[row][col] == id '

//helperBots[MAX_ROBOT_NUM][MAX_ROBOT_NUM]; //stores helper bot loc and id
	//reference 'helperBots[row][col] == id '

Action findDebris(int id, Loc loc, Area &area, ostream &log);

//Action findRobot(int id, Loc loc, Area &area, ostream &log);

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows; 
	COLS = cols;

	//fill bots array with -1 so any location that isn't a bot is -1
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col < COLS; col++){
			bots[row][col] = -1;
		}
	}

	//store robot information in array
	for (int i = 0; i<num; i++){
		int row = area.locate(i).r;   // row coordinate of the robot ID
		int col = area.locate(i).c;   // column coordinate of the robot ID
		bots[row][col] = i;
	}

	//store debris information in array
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col < COLS; col++){
			if (area.inspect(row,col) == DEBRIS){
					debris[row][col] = true;
			} else {
				debris[row][col] = false;
			}
		}
	}

	log << "Start!" << endl;
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
	
	if (debris[row][col]) { //Collect
		bots[area.locate(id).r][area.locate(id).c] = -1;
		bots[row][col] = id;
		debris[row][col] = area.inspect(row,col);
		if(id == 4 && row == 13){
			log << "expected id: 4 row: " << area.locate(id).r << " col: " << area.locate(id).c << endl;
			log << "expected area: " << area.inspect(row, col) << endl;
			log << "returned area: " << bots[row][col] << "row: " << row << " col: " << col << endl;
			log << "expected area: " << debris[row][col] << endl;
		}
		return COLLECT;
	} else {
		bots[area.locate(id).r][area.locate(id).c] = -1;
		bots[row][col] = id;
		return findDebris(id, loc, area, log);
	}

}

Action findDebris(int id, Loc loc, Area &area, ostream &log) {
	//steps for debris.
	int row = loc.r; // current row and column
	int col = loc.c;

	int minDist = ROWS;
	int minY = 0; //row
	int minX = 0; //col

	//calculate distance
	for (int y2 = 0; y2 < ROWS; y2++){
		for (int x2 = 0; x2 < COLS; x2++){
			if((debris[y2][x2]) && (bots[y2][x2] == -1)){ //if in debris and not a bot
				int dist = abs(x2-col) + abs(y2-row);
				if(dist < minDist){
					minDist = dist;

					minY = y2;
					minX = x2;

				}
			}
		}
	}

	int diffY = row - minY;
	int diffX = col - minX;
	
	if (diffY < 0) {
		if (bots[row+1][col] != -1 && (bots[row-1][col] == -1 )){
			return UP;
		}
		return DOWN;
	} else if (diffY > 0) { ////debris is above
		if (bots[row-1][col] != -1 && (bots[row+1][col] == -1 )){
			return DOWN;	
		} 
		return UP;
	} else if (diffX < 0) { //debris is to the right
		if (bots[row][col+1] != -1 && (bots[row][col-1] == -1 )){
			return LEFT;
		}
		return RIGHT;
	} else { //debris is to the left
		if (bots[row][col-1] != -1 && (bots[row][col+1] == -1 )){
			return RIGHT; 
		} 
		return LEFT;
	} 
}

/*
Robots can break in two situations:
- When they COLLECT
- if your onRobotAction function does not return a value by mistake (that is, "software defect" in your code).

(Repeating: In that state, robots remain functional, but stop collecting debris and 
leave debris anywhere they go. The condition for breaking are right above.)
*/

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
	
	log << "Robot " << id << " is damaged." << endl;
	log << "Row: "<< row << " Col: " << col << endl;

	findHelperBot = true;
	//needRepair[row][col] = id;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}


