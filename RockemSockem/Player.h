// Player.h - Class for player1 and all its data
// By Wesley Sun

#pragma once

// Neccessary included files
#include "DarkGDK.h"
#include "Input.h"
#include "Player2.h"
class Player2;

// Player class creates a Player1 object
class Player{
public:
	// Default constructor
	Player();
	// Sets up the player i.e. sprites
	void PlayerSetup();
	// Updates player actions like moving or atacking
	void PlayerUpdate(Player2& user2);
	// Resets the players health if it died
	void PlayerHealthReset();
	// Gets the X Position of player
	float GetPosX() const;
	// Gets the Y Position of player
	float GetPosY() const;
	// Creates a gravity for the player
	void Gravity();
	// Checks to see if the player ran out of lives
	bool CheckMatchEnd() const;
	// Checks to see if the player fired a shot
	void PlayerFire(Player2& user2);
	// Checks to see if player hit the enemy
	void PlayerCheckHitEnemies(Player2& user2);
	// Decreases Player1 health if hit
	void DecreaseHealth();
private:
	// Used to create a X Velocity
	float Vx;
	// Used to create a Y Velocity
	float Vy;
	// Used to keep track of Player's X Position
	float PosX;
	// Used to keep track of Player's Y Position
	float PosY;
	// Used to determine how fast the player will move
	float Speed;
	// Used to determine how much Lives the player has left
	int Lives;
	// Used to determine how much Health the player has left
	int Health;
	// Used to determine the position of the player's bullet
	float playerBullet;
	// Checks to see if player is firing or not
	bool playerIsFiring;
	// Used to inflict how much gravity there is
	int gravity;
	// Checks to see if player is jumping or not
	bool playerJumping;
	// Checks to see if the game is over
	bool matchEnd;
	// Sets the direction of the bullet
	bool directionBullet;
};