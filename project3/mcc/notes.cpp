/*
1). Start by tinkering with the provided functions, 
to see what can be done, and how the robot’s behavior changes in response to your code modifications. 
(The program must be recompiled each time with make for changes to take an effect.)

X 2). As you can see, robots’ movement is pretty chaotic now. Make them move more direct towards debris.

3). Improve their logic so they are not waiting for other robots and distribute work efficiently.

4). Make sure the robots work well for all possible map sizes, robot numbers, and debris density.

5). Identify how to make them work quicker, and implement that.

6). Further improvements include handling the problem of robots malfunctioning, when they occasionally break, 
and are shown red on the screen. It will be described later.
*/


/*
- Don't make them cluster near the same pieces of debris.

- Don't make them wait for other robots.

- Spread the robots so that roughly equal number of them goes after each piece of debris.

- Give priority to those robots who are closer to each debris piece.

- ? Maybe some other efficiency measures ? Where robots waste time? Make them avoid that.

 */
/*Action distance(){
	

	//if findHelperBot = false {
		//collect or move towards debris
		////neg if x2 is larger than x1 -- meaning debris is below
	//}
	// else {
		//if this bot is in helperBots {
			//if(helperBots[row][col] == id){
			//	helperBots[]
				//move towards dedicated needRepair bot
			//}
			
			//if row of helper bot != row of repair bot (+/- 1) {
				//collect or move up or down

			//} else if col of helper bot != col of repair bot (+/- 1) {
				//collect or move left or right

			//} else {
				//repair left/right/up/down
				//findHelperBot = false;
		//}
		//}
		// else {
		// 	collect or move
		// }
	//}

}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
	
	log << "Robot " << id << " is damaged." << endl;
	log << "Row: "<< row << " Col: " << col << endl;

	//needRepair[row][col] = id;

	findHelperBot = true;

	// int closestID = 0;

	// int minDist = ROWS;
	// int minY = 0; //row
	// int minX = 0; //col

	// //calculate distance
	// for (int y2 = 0; y2 < ROWS; y2++){
	// 	for (int x2 = 0; x2 < COLS; x2++){
	// 		if((bots[y2][x2] != -1) && (bots[y2][x2] != id)){ //if in debris and not a bot
	// 			int dist = sqrt(pow(x2 - col, 2) + pow(y2 - row, 2));
	// 			if(dist < minDist){
	// 				minDist = dist;
	// 				minY = y2;
	// 				minX = x2;
	// 			}
	// 		}
	// 	}
	// }
	
	// closestID = bots[minX][minY];
	// helperBots[row][col] = closestID;

	//row is malfunctioning bot row, col is malfunctioning bot row

	// find the closest robot to help

	//tell nearest bot to come to malfunctioning bot

	//tell helper bot to repair bot in direction of malfunctioning bot
	//if (area.inspect(row, col))

	//store helper bot and broken bot information in arrays
	
	//needRepair[index, id, row, col] 
	//helperBots[index, id, row, col]

	//incriment number of brokenBots
}

// Action immediateAction(int id, Loc loc, Area &area, ostream &log){
// 	int row = loc.r; // current row and column
// 	int col = loc.c;
// 	Action action = RIGHT;
// 	//if bot in way, determine next move

// 	if (bots[row+1][col] != -1){ //bot is below
// 		if(brokenBots[bots[row+1][col]]){ //bot is down
// 			action = REPAIR_DOWN;
// 		} else if (bots[row-1][col] != -1){ //bot is  up
// 				if (brokenBots[bots[row-1][col]]){
// 					action = REPAIR_UP;
// 				} 
// 		} else if (bots[row][col+1] != -1){ //bot is to the right
// 				if (brokenBots[bots[row][col+1]]) { // if bot 
// 					action = REPAIR_RIGHT;
// 				}
// 		} else if (bots[row][col-1] != -1){
// 				if(brokenBots[bots[row][col-1]]) { //bot is to the left
// 					action = REPAIR_LEFT;
// 				}
// 		} else {
// 			if (bots[row-1][col] == -1){ //bot is  up
// 				action = UP;
// 			} else if (bots[row][col+1] == -1){ 
// 				action = RIGHT;
// 			} else if (bots[row][col-1] == -1){
// 				action = LEFT;
// 			} 
// 		}
// 	} else {
// 		action = DOWN;
// 	}

// 	return action;
// }
*/