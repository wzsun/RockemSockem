// Player2.h - Creates player2 object and all the functions associated with it
// By Wesley Sun

#pragma once
#include "DarkGDK.h"
#include "Input.h"
#include "Player.h"

class Player;

// Player 2 class, very similiar to class 1, but adjusted some of the sprite and respawn aspects.
class Player2{
public:
	// Default constructor - loads all the lives, health, etc.
	Player2();
	// Sets up the player's sprites to be used
	void PlayerSetup();
	// Updates how the player will move/shoot/die
	void PlayerUpdate(Player& user1);
	// Resets the players health if he died
	void PlayerHealthReset();
	// Places gavity on the player
	void Gravity();
	// Gets the X Position of player
	float GetPosX() const;
	// Gets the Y position of player
	float GetPosY() const;
	// Checks to see if the match is over
	bool CheckMatchEnd() const;
	// Decreases health if player is hit
	void DecreaseHealth();
	// Checks to see if player fired a shot
	void PlayerFire(Player& user1);
	// Checks to see if player hit enemy
	void PlayerCheckHitEnemies(Player& user1);
private:
	// X velocity of player
	float Vx;
	// Y velocity of player
	float Vy;
	// X position of player
	float PosX;
	// Y position of player
	float PosY;
	// Speed of which the palyer will move
	float Speed;
	// Lives of the player
	int Lives;
	// Health of the palyer
	int Health;
	// Gravity effect placed on player
	int gravity;
	// Checks to see if player is jumping
	bool playerJumping;
	// Checks to see if the match is over
	bool matchEnd;
	// Checks to see if the player is firing
	bool playerIsFiring;
	// X pos of the player's bullet
	float playerBullet;
	// direction of bullet
	bool directionBullet;
};