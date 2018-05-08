
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
const int MAX_ROBOT_NUM = 50;

int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions y = row and x = col;

bool findHelper = false;

//array of robot id's and location in program
int bots[MAX_ROWS][MAX_COLS];
	//reference 'bots[row][col] == id'

bool debris[MAX_ROWS][MAX_COLS]; // array of debris and location 
	//refernce 'debris[row][col] == true or 'debris[row][col] == false

bool brokenBots[MAX_ROBOT_NUM];
int helperBots[MAX_ROBOT_NUM]; //stores malfunctioning bot id at index of the helper bot 
	//reference 'helperBots[helper bot id] = malfunctioning bot id'

//designates robots action when looking for debris to collect
Action findDebris(int id, Loc loc, Area &area, ostream &log);

//returns true if there is a bot in the area between bot and debris
bool botInArea(int row, int col, int x2, int y2);

void findHelperBot(int id, Loc loc, Area &area, ostream &log);

void findNewHelperBot(int id, Loc loc, Area &area, ostream &log);
//calculates debris in a given area
int debrisInArea(int row, int col, int x2, int y2);

//calculates debris in steps
int debrisInSteps(int row, int col, int x2, int y2); 

//designates robots action when looking for robot to repair
Action repairRobot(int id, Loc loc, Area &area, ostream &log);

bool isRepaired(int id, Loc loc, Area &area, ostream &log);

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr, Area &area, ostream &log){
	NUM = num;	// save the number of robots and the map dimensions
	ROWS = rows; 
	COLS = cols;

	for(int row = 0; row < ROWS; row++){	//fill bots array with -1 so any location that isn't a bot is -1
		for(int col = 0; col < COLS; col++){
			bots[row][col] = -1;
		}
	}

	for (int i = 0; i<num; i++){	//store robot information in array
		int row = area.locate(i).r;	// row coordinate of the robot ID
		int col = area.locate(i).c;	// column coordinate of the robot ID
		bots[row][col] = i;
		helperBots[i] = -1;	//store -1 to remove garbage
		brokenBots[i] = false;
	}

	for(int row = 0; row < ROWS; row++){	//store debris information in array
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
	bots[area.locate(id).r][area.locate(id).c] = id;;
	Action action; 

	if(helperBots[id] != -1){
		brokenBots[helperBots[id]] = true;
		if (debris[row][col]) { //Collect
			bots[area.locate(id).r][area.locate(id).c] = -1;
			bots[row][col] = id;
			debris[row][col] = area.inspect(row,col);
			action = COLLECT;
		} else {
			bots[area.locate(helperBots[id]).r][area.locate(helperBots[id]).c] = helperBots[id];
			bots[area.locate(id).r][area.locate(id).c] = -1;
			bots[row][col] = id;
			action = repairRobot(id, loc, area, log);
		}
		if(isRepaired(id, loc, area, log)){
			brokenBots[helperBots[id]] = false;
			helperBots[id] = -1;
			action = findDebris(id, loc, area, log); 
		}
	} else {
		if(brokenBots[id] == false){
			helperBots[id] = -1;
			if (debris[row][col]) { //Collect
				bots[area.locate(id).r][area.locate(id).c] = -1;
				bots[row][col] = id;
				debris[row][col] = area.inspect(row,col);
				action = COLLECT;
			} else {
				bots[area.locate(id).r][area.locate(id).c] = -1;
				bots[row][col] = id;
				action = findDebris(id, loc, area, log);
			} 
		} else {
			bots[area.locate(id).r][area.locate(id).c] = -1;
			bots[row][col] = id;
		}
	} 

	if(action == REPAIR_DOWN || action == REPAIR_UP || action == REPAIR_RIGHT || action == REPAIR_LEFT){ //if bot is closer to broken bot than assigned helper
		if(helperBots[id] == -1){ 
			int repairID; //find broken bot id
			if(action == REPAIR_DOWN){
				repairID = brokenBots[bots[row+1][col]];
			} else if (action == REPAIR_UP) {
				repairID = brokenBots[bots[row-1][col]];
			} else if (action == REPAIR_RIGHT){
				repairID = brokenBots[bots[row][col+1]];
			} else {
				repairID = brokenBots[bots[row][col-1]];
			}

			for (int i = 0; i < NUM; i++){ // tell helperBot that they no longer need to help this bot
				if(helperBots[i] == repairID){
					helperBots[i] = -1;
				}
			}
			brokenBots[repairID] = false; //update broken bot array
		}
	}

	return action;
}

Action findDebris(int id, Loc loc, Area &area, ostream &log) {
	//steps for debris
	int row = loc.r; // current row and column
	int col = loc.c;

	int minDist = ROWS;
	int minY = 0; //row
	int minX = 0; //col

	Action action;

	//calculate distance
	for (int y2 = 0; y2 < ROWS; y2++){
		for (int x2 = 0; x2 < COLS; x2++){
			if((debris[y2][x2]) && (bots[y2][x2] == -1)){ //if in debris and not a bot
				int dist = abs(x2-col) + abs(y2-row);
				if(dist < minDist){
					if(!botInArea(row, col, x2, y2)){
						minDist = dist;
						minY = y2;
						minX = x2;
					}
				}
			}
		}
	}

	int distY = abs(row - minY); //row
	int distX = abs(col - minX); //col

	int diffY = row - minY;
	int diffX = col - minX;
	if(distY >= distX){
		if (diffY < 0) {
			if (bots[row+1][col] != -1 && (bots[row-1][col] == -1)){
				action = UP;	
			} else if (bots[row+1][col] != -1 && (bots[row][col-1] == -1)){
				action = LEFT;
			} else {
				action = DOWN;
			}
			
		} else { ////debris is above
			if (bots[row-1][col] != -1 && (bots[row+1][col] == -1)){
				action = DOWN;	
			} else if (bots[row-1][col] != -1 && (bots[row][col+1] == -1)){
				action = RIGHT;
			} else {
				action = UP;
			}	
		} 
	} else {
		if (diffX < 0) { //debris is to the right
			if (bots[row][col+1] != -1 && (bots[row][col-1] == -1)){
				action = LEFT;
			} else if (bots[row][col+1] != -1 && (bots[row+1][col] == -1)){
				action = DOWN;
			} else {
				action = RIGHT;
			}
		} else { //debris is to the left
			if (bots[row][col-1] != -1 && (bots[row][col+1] == -1)){
				action = RIGHT;
			} else if (bots[row][col-1] != -1 && (bots[row-1][col] == -1)){
				action = UP;
			} else {
				action = LEFT;
			}
		} 
	}
	return action;
}

bool botInArea(int row, int col, int x2, int y2){
	bool bot = false;
	int num = 0;
	int r1, r2, c1, c2;

	if (row > y2) {	// compare debris starting from y2
		r1 = y2;
		r2 = row;
	} else {	// compare debris starting from y1
		r1 = row;
		r2 = y2;
	}
	
	if (col > x2) {	// compare debris starting from point x1
		c1 = x2;
		c2 = col; 
	} else { //	compare debris starting from x2 
		c1 = col;
		c2 = x2;
	}

	for(int r = r1; r< r2; r++){
		for(int c = c1; c<c2; c++){
			if(bots[r][c] != -1){
				bot = true;
				num++;
			}
		}
	}

	return bot;
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log){
	if(helperBots[id] != -1) {
		int bb = helperBots[id];
		brokenBots[id] = true;
		brokenBots[bb] = true;
		log << "Helper Robot " << id << " is damaged." << " " << endl;
		log << helperBots[id] << " is being reassigned a new helper" << " " << endl;
		findNewHelperBot(bb, loc, area, log);
		findHelperBot(id, loc, area, log);
	} else {
		brokenBots[id] = true;
		log << "Robot " << id << " is damaged." << " " << endl;
		findHelperBot(id, loc, area, log);
	}

	//Comparing distance to find closest helper robot: 
	//Calculate manhattan distance: 
	//Manhattan distance = steps without debris

	// log << "Row: "<< row << " Col: " << col << endl;
}


void findHelperBot(int id, Loc loc, Area &area, ostream &log){
	int row = loc.r; 
	int col = loc.c;
	findHelper = true;

	int minDist = ROWS;
	int minY = 0; //helper bot row
	int minX = 0; //helper bot col
	int helperID;

	//Calculate manhattan distance: steps without debris
	for (int y2 = 0; y2 < ROWS; y2++){
		for (int x2 = 0; x2 < COLS; x2++){
			bool possibleHelper = ((bots[y2][x2] != id) && (helperBots[bots[y2][x2]] == -1) && (brokenBots[bots[y2][x2]] == false));
			if(possibleHelper){ //if location in bots array is a bot
				int dist = abs(x2-col) + abs(y2-row); //calculate manhattan distance
				if(dist < minDist){
					int area = abs(col - x2) * abs(row - y2);
					int areaDebris = debrisInArea(row, col, x2, y2); //how much debris is in area of minX + malRobotX 
					int stepsDebris = debrisInSteps(row, col, x2, y2); //how much debris is in manhattan distance
					minDist = dist;
					minY = y2;
					minX = x2;
					//Comparing distance to find closest helper robot
					if ((dist > 0) && (area > 0) && (stepsDebris/dist) <= (areaDebris/area)){
						helperID = bots[y2][x2];
						helperBots[helperID] = id;
					} else {
						helperID = bots[minY][minX];
						helperBots[helperID] = id;
					}
				}
			}
		}
	}
	log << "Robot "<< helperID << " will help bot " << id << " " << endl;
}

void findNewHelperBot(int id, Loc loc, Area &area, ostream &log){
	int row = loc.r; 
	int col = loc.c;
	findHelper = true;

	int minDist = ROWS;
	int minY = 0; //helper bot row
	int minX = 0; //helper bot col
	int helperID;

	// int oldID = helperBots[id];

	//Calculate manhattan distance: steps without debris
	for (int y2 = 0; y2 < ROWS; y2++){
		for (int x2 = 0; x2 < COLS; x2++){
			//if bot is a bot, and id in bots array does not equal this id. and id in bots array does not equal old 
			bool possibleHelper = ((bots[y2][x2] != -1) && (bots[y2][x2] != id) && (helperBots[bots[y2][x2]] == -1) && (brokenBots[bots[y2][x2]] == false));
			if(possibleHelper){ //if location in bots array is a bot
				int dist = abs(x2-col) + abs(y2-row); //calculate manhattan distance
				if(dist < minDist){
					minDist = dist;
					int area = abs(col - x2) * abs(row - y2);
					int areaDebris = debrisInArea(row, col, x2, y2); //how much debris is in area of minX + malRobotX 
					int stepsDebris = debrisInSteps(row, col, x2, y2); //how much debris is in manhattan distance
					//Comparing distance to find closest helper robot
					if ((dist > 0) && (area > 0) && (stepsDebris/dist) <= (areaDebris/area)){
						minY = y2;
						minX = x2;
						helperID = bots[y2][x2];
						helperBots[helperID] = id;
					}
				}
			}
		}
	}
	log << "New helper bot "<< helperID << " will help bot " << id << " " << endl;
}

int debrisInArea(int row, int col, int x2, int y2){
	int deb = 0;
	int r1, r2, c1, c2;

	if (row > y2) {	// compare debris starting from y2
		r1 = y2;
		r2 = row;
	} else {	// compare debris starting from y1
		r1 = row;
		r2 = y2;
	}
	
	if (col > x2) {	// compare debris starting from point x1
		c1 = x2;
		c2 = col; 
	} else { //	compare debris starting from x2 
		c1 = col;
		c2 = x2;
	}

	for(int r = r1; r< r2; r++){
		for(int c = c1; c<c2; c++){
			if(debris[r][c]){
				deb++;
			}
		}
	}
	return deb;
}

int debrisInSteps(int row, int col, int x2, int y2) {
	int deb = 0;
	int r1, r2, c1, c2;

	if (row > y2) {	// compare debris starting from y2
		r1 = y2;
		r2 = row;
	} else {	// compare debris starting from y1
		r1 = row;
		r2 = y2;
	}
	
	if (col > x2) {	// compare debris starting from point x1
		c1 = x2;
		c2 = col; 
	} else { //	compare debris starting from x2 
		c1 = col;
		c2 = x2;
	}

	//number of debris in col
	for(int r = r1; r < r2; r++){	
		if(debris[r][c2]){
			deb++;
		}
	}

	//number of debris in row
	for(int c = c1; c < c2; c++){
		if(debris[r2][c]){
			deb++;
		}
	}
	return deb;
}

//designates robots action when looking for robot to repair
Action repairRobot(int id, Loc loc, Area &area, ostream &log){
	int row = loc.r; // current row and column
	int col = loc.c;

	int repairID = helperBots[id];
	int x2 = area.locate(repairID).c;
	int y2 = area.locate(repairID).r;

	int diffY = row - y2;
	int diffX = col - x2;

	int minY = abs(row - y2); //row
	int minX = abs(col - x2); //col

	Action action;

	// if(brokenBots[repairID] && helperBots[id] != -1){
	if(!isRepaired(id, loc, area, log)){
		if(minX >= minY){
			if (diffX < 0) { //debris is to the right
				action = RIGHT;
			} else { //debris is to the left
				action = LEFT;
			}
		} else {
			if (diffY < 0) {
				action = DOWN;
			} else { ////debris is above
				action = UP;
			}
		}
	} else {
		log << " helper bot id " << id << " is repairing " << helperBots[id] << " " << endl;
		//repair direction
		if (bots[row+1][col] == repairID){
			log << helperBots[id] << " is DOWN" << endl;
			action = REPAIR_DOWN;
		} else if (bots[row-1][col] == repairID){
			log << helperBots[id] << " is UP" << endl;
			action = REPAIR_UP;
		} else if (bots[row][col+1] == repairID){
			log << helperBots[id] << " is RIGHT" << endl;
			action = REPAIR_RIGHT;
		} else {
			log << helperBots[id] << " is LEFT" << endl;
			action = REPAIR_LEFT;
		}	
	}
	return action;
}

bool isRepaired(int id, Loc loc, Area &area, ostream &log){
	int row = loc.r; // current row and column
	int col = loc.c;
	int repairID = helperBots[id];
	// int repairRow = area.locate(repairID).r;
	// int repairCol = area.locate(repairID).c;
	bool res = ((bots[row+1][col] == repairID) || (bots[row-1][col] == repairID) || (bots[row][col+1] == repairID) || (bots[row][col-1] == repairID));
	// bool res = (row == repairRow && (abs(col-repairCol) == 1)) || (col == repairCol && (abs(row-repairRow) == 1));
	return res;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}

