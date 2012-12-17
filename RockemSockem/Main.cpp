// Main.cpp - Rockem Sockem Game
// 2 Player game in which the players fight each other by shooting bullets, each player is able to withstand 5 shots.
// If the player's health reaches 0, then he loses a life. Players have 3 lives. Whoever runs out of lives first, loses. 
// Additionally if the player jumps off the stage he loses a life and player is respanwed.
// P1 controls are | P2 controls are
// "W" - Jump      | "Up arrow key" - Jump
// "A" - Left      | "Left arrow key" - Left
// "D" - Right     | "Right arrow key" - Right
// "G" - Shoot     | "L" - Shoot

// Additionally to pause press "p" and to start the game press the space bar

// Now the code
#include "DarkGDK.h"
#include "Player.h"
#include "Player2.h"
#include "Input.h"

// Constants used to define game

// Key ID for "p"
#define PAUSE_KEY 25
// Sprite ID for Start
#define START 100
// Sprite ID for pause
#define PAUSE 3
// X Position for Pause
#define PAUSE_X 30
// Y Position for Pause
#define PAUSE_Y 0
// Sprite ID for Background IMG
#define BACKGROUND 4
// Sync rate - frames per second
#define SYNC_RATE 60
// sets display width
#define DISPLAY_WIDTH 800
// sets display height
#define DISPLAY_HEIGHT 500
// timer set for pause function
#define TIMER_PLUS 500
// Sprite ID for end game
#define END_GAME 3
// end game X position
#define END_GAME_X 0
// end game Y position
#define END_GAME_Y 0

using namespace std;

// Used to create states for the game
enum Mode{
	// GameTitle state loads the start screen
	GameTitle, 
	// StartGame loads the game itself so players can be moved
	StartGame, 
	// End Game brings up the end game screen
	EndGame
};
// Sets the initial game mode
Mode gameMode = GameTitle;
// Creates the players
Player user1;
Player2 user2;
// Lets the pause work at any time
bool isPaused = false;
int timer = dbTimer();

// Sets up the Start up screen, press space to start the game
void gameTitle(){
	// Loads Start splash screen
	dbLoadImage("Start.png", START);
	dbSprite(START,0,0,START);
	// Checks to see if space is hit to start the game
	if(checkSpace()){
		dbDeleteSprite(START);
		gameMode = StartGame;
	}
}

// Starts the game with pause function
void startGame(){
	// Loads the pause function
	dbCLS();
	// If "p" is hit pause is triggerd
	if(dbKeyState(PAUSE_KEY) && (dbTimer() > timer+TIMER_PLUS)){
		timer = dbTimer();
		if(!isPaused)
			isPaused=true;
		else
			isPaused=false;
	}
	// It then loads the Pause img
	if(isPaused){
		dbLoadImage("pause.png",PAUSE);
		dbSprite(PAUSE,PAUSE_X,PAUSE_Y,PAUSE);
	}
	// Otherwise the game continues to run as normal
	else{
		dbDeleteSprite(PAUSE);
		// Player Gravity is activated
		user1.Gravity();
		user2.Gravity();
		// PlayerUpdate is initiated to allow movement
		user1.PlayerUpdate(user2);
		user2.PlayerUpdate(user1);
		// Checks to see if either of the player has died completely, if so, the end game screen is brought up
		if(user1.CheckMatchEnd() || user2.CheckMatchEnd()){
			gameMode = EndGame;
		}
	}
}

// Loads the end game screen
void endGame(){
	// Loads the end splash img
	dbLoadImage("endgame.png",END_GAME);
	dbSprite(END_GAME,END_GAME_X,END_GAME_Y,END_GAME);
}

// Switches the states of the game
void Game(){
	switch(gameMode){
	// Starts at GameTitle
	case GameTitle:
		gameTitle(); break;
	// Loads the StartGame if that state is in check
	case StartGame:
		startGame(); break;
	// Loads the EndGame if that state is in check
	case EndGame:
		endGame(); break;
	}
}

// the main entry point for the application is this function
void DarkGDK ( void )
{
	// Sets the display size and the sync rate
	dbSetDisplayMode ( DISPLAY_WIDTH ,DISPLAY_HEIGHT, 32 );
	dbSyncOn ( );
	
	// Loads the background image
	dbLoadImage("Backdrop2.png",BACKGROUND);
	dbSprite(BACKGROUND,0,0,BACKGROUND);

	// Sets up how much times the screen can update per second
	dbSyncRate (SYNC_RATE);
	
	// Sets up the player's sprites and information
	user1.PlayerSetup();
	user2.PlayerSetup();
	
	// This is what updates during the game
	while ( LoopGDK ( ) )
	{
		// Call our switch function to change the game states
		Game();
		dbSync ( );
	}

	// return back to windows
	return;
}