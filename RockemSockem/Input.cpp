// Input.cpp - Implementation of Input.h
// By Wesley Sun

#include "Input.h"

// Player 1 controls
// Checks if "A" was hit
bool checkLeft(void){
	if(dbKeyState(30))
		return true;
	return false;
}
// Checks if "D" was hit
bool checkRight(void){
	if(dbKeyState(32))
		return true;
	return false;
}
// Checks if "G" was hit
bool checkAttack(void){
	if(dbKeyState(34))
		return true;
	return false;
}
// Checks if "W" was hit
bool checkJump(void){
	if(dbKeyState(17))
		return true;
	return false;
}

// Player 2 controls
// Checks to see if Left Arrow Key was hit
bool checkLeft2(void){
	if(dbKeyState(203))
		return true;
	return false;
}
// Checks to see if Right Arrow Key was hit
bool checkRight2(void){
	if(dbKeyState(205))
		return true;
	return false;
}
// Checks to see if "L" was hit
bool checkAttack2(void){
	if(dbKeyState(38))
		return true;
	return false;
}
// Checks to see if Up Arrow Key was hit
bool checkJump2(void){
	if(dbUpKey())
		return true;
	return false;
}

// Checks to see if space bar was hit - used to start the game
bool checkSpace(void){
	if(dbKeyState(57))
		return true;
	return false;
}