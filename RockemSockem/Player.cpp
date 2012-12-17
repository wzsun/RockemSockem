// Player.cpp - Player.h implementation
// By Wesley Sun

// This code creates the Player1 object and regulated that object

#include "Player.h"

// Constants to set user's health, life, respawn, and others
// Used to determine the end of the stage
#define END_STAGE_RIGHT dbScreenWidth()-175
// Used to determine the end of the stage
#define END_STAGE_LEFT 100
// Sets the ground level
#define GROUND 250.0f
// Used to determine the Life Sprite IDS
#define START_LIFE_COUNTER_ID 200
// Used to set the Y position of the Life bars
#define BASE_OF_LIFE_BAR 450
// Used to set the first X position of the first Life Bar
#define LIFE_BAR 50
// Width of the life bar
#define LIFE_BAR_WIDTH 50
// Sprite number of Player 1
#define P1_SPRITE 1
// Sprite number of Player 2
#define P2_SPRITE 2
// Sets the jump velocity
#define JUMP_VELOCITY -15
// Sets the respawn height
#define RESPAWN_HEIGHT 0
// sets the respwan X Position
#define RESPAWN_WIDTH 200.0f
// sets the Initial velocity X 
#define INITIAL_VX 0.0f
// sets the initial velocity Y
#define INITIAL_VY 0.0f
// sets P1 start position X
#define P1_START_POSITION 300.0f
// sets the Speed of how fast the player will move
#define SPEED 3.0f
// sets the number of lives
#define LIVES 3
// sets how much health player has
#define HEALTH 5
// sets the gravity effect
#define GRAVITY 1
// sets the Y pos of the health bar
#define BASE_OF_HEALTH_BAR 425
// sets Sprite ID for the health bar
#define START_HEALTH_COUNTER_ID 400
// Sets the X position of health bar
#define HEALTH_BAR 50
// width of each health bar chunk
#define HEALTH_BAR_WIDTH 30
// sets Sprite ID for bullet
#define BULLET 10
// Creates a hit buffer for hit detection
#define HIT_BUFFER 20
// Sets the height of bullet shot w/ respect to player
#define BULLET_SHOT_HEIGHT 10
// sets the bullet velocity
#define BULLET_VELOCITY 8

// Default Constructor, sets all the neccessary values at begining to put the 
// player in position and have the correct amount of health, lives, the ground level, etc.
Player::Player(){
	Vx=INITIAL_VX;
	Vy=INITIAL_VY;
	PosX=P1_START_POSITION;
	PosY=GROUND;
	Speed=SPEED;
	Lives=LIVES-1;
	Health=HEALTH-1;
	gravity = GRAVITY;
	playerJumping = false;
	playerIsFiring = false;
	playerBullet = 0;
}

// Inflicts the Gravity effect onto the player
void Player::Gravity(){
	// This is to simulate the acceleration of falling/jumping
	Vy += gravity;
	PosY += Vy;
	// This says if the player is off the stage he falls off
	if(PosY > GROUND && (PosX < END_STAGE_RIGHT && PosX > END_STAGE_LEFT)){
		PosY = GROUND;
		Vy=INITIAL_VY;
		playerJumping = false;
	}
	// Moves the sprite location w/ respective to jump & gravity
	dbSprite(1,dbSpriteX(1),PosY,1);
}

// Sets up the player object, by loading all neccessary components
void Player::PlayerSetup(){
	// loads the player1 sprite
	dbCreateAnimatedSprite ( P1_SPRITE, "gokum.png", 4, 2, P1_SPRITE );
	dbSprite(P1_SPRITE, PosX, PosY, P1_SPRITE);
	// loads the life bar
	int lifeBarWidth = LIFE_BAR;
	for(int i=0; i<LIVES; i++){
		dbLoadImage("life.png",START_LIFE_COUNTER_ID+i);
		dbSprite(START_LIFE_COUNTER_ID+i,lifeBarWidth, BASE_OF_LIFE_BAR, START_LIFE_COUNTER_ID+i);
		lifeBarWidth += LIFE_BAR_WIDTH;
	}
	// loads the health bar
	PlayerHealthReset();
	// loads the bullet
	dbLoadImage("bullet.png", BULLET);
}

// Resets the Players health if he dies
void Player::PlayerHealthReset(){
	int healthBar = HEALTH_BAR;
	// Creates health chunks in lineaer order so it looks like a large health bar.
	for(int i=0; i<HEALTH; i++){
		dbLoadImage("health.png",START_HEALTH_COUNTER_ID+i);
		dbSprite(START_HEALTH_COUNTER_ID+i,healthBar, BASE_OF_HEALTH_BAR, START_HEALTH_COUNTER_ID+i);
		healthBar += HEALTH_BAR_WIDTH;
	}
}

// Gets the X Position of player
float Player::GetPosX() const{
	return PosX;
}

// Gets the Y Position of player
float Player::GetPosY() const{
	return PosY;
}

// Checks if the player has fired or is firing
void Player::PlayerFire(Player2& user2){
	// If the player is already firing, let the bullet continue at a set velocity
	if(playerIsFiring){
		// Makes it so the direction once shot only heads the direction it was shot at
		if(directionBullet == true)
			playerBullet -= BULLET_VELOCITY;
		else
			playerBullet += BULLET_VELOCITY;
		// Moves the bullet
		dbSprite(BULLET,playerBullet,dbSpriteY(BULLET),BULLET);
		// Checks to see if an enemy was hit
		PlayerCheckHitEnemies(user2);
		// If the bullet goes to the edge of the screen it get's deleted and 
		// player can shoot again
		if(playerBullet < 0 || playerBullet > dbScreenWidth()){
			dbDeleteSprite(BULLET);
			playerIsFiring = false;
		}
	}
	// Checks to see if the player hit the shoot button
	// If player has already shot it does nothing, if it hasn't, it shoots
	if(checkAttack() == true && playerIsFiring == false){
		playerIsFiring = true;
		// Sets the direction the bullet is going
		if(PosX > user2.GetPosX())
			directionBullet = true;
		else
			directionBullet = false;
		// Displays the bullet shooting out of the sprite
		playerBullet = PosX;
		dbSprite(BULLET,playerBullet+(dbSpriteWidth(P2_SPRITE)/2),PosY+BULLET_SHOT_HEIGHT, BULLET);
	}
}

// Checks to see if the player has hit any enemies, namely P2
void Player::PlayerCheckHitEnemies(Player2& user2){
	// Gets the bullet position, so it is the front of the bullet at the center
	int bulletX = dbSpriteX(BULLET)+dbSpriteWidth(BULLET);
	int bulletY = dbSpriteY(BULLET)+(dbSpriteHeight(BULLET)/2);
	// Checks to see if the bullet position is within the width and height of the sprite
	if(bulletX > user2.GetPosX()+ HIT_BUFFER && bulletX < user2.GetPosX() + dbSpriteWidth(P2_SPRITE)){
		if(bulletY > user2.GetPosY() && bulletY < user2.GetPosY() + dbSpriteHeight(P2_SPRITE)){
			// If it is, the bullet is deleted and P2 loses health
			dbDeleteSprite(BULLET);
			user2.DecreaseHealth();
			// Player can fire again
			playerIsFiring = false;
		}
	}
}

// Decreases the players health if hit
void Player::DecreaseHealth(){
	// If health is 0, then it checks if he has more life
	if(Health == 0){
		// If he has more lives, then it justs deletes a life and resets his health and respawns
		if(Lives > 0){
			dbDeleteSprite(START_HEALTH_COUNTER_ID+Health);
			dbDeleteSprite(START_LIFE_COUNTER_ID+Lives);
			Lives--;
			Health = HEALTH-1;
			PlayerHealthReset();
			PosX = RESPAWN_WIDTH;
			PosY = RESPAWN_HEIGHT;
		}
		// If he has no more lives it deletes the sprites health and last life, and ends the match
		else{
			dbDeleteSprite(START_HEALTH_COUNTER_ID+Health);
			Health--;
			dbDeleteSprite(START_LIFE_COUNTER_ID+Lives);
			matchEnd=true;
		}
	}
	// If he has more health, it just gets rid of one
	else{
		dbDeleteSprite(START_HEALTH_COUNTER_ID+Health);
		Health--;
	}
}

// Updates the players action such as moving and shooting
void Player::PlayerUpdate(Player2& user2){
	// Moves the player left if "a" is hit
	if(checkLeft()){
		PosX -= Speed;
	}
	// Moves the player right if "d" is hit
	if(checkRight()){
		PosX += Speed;
	}
	// Jumps if user hits "w"
	if(checkJump()){
		// If the player isn't jumping then he jumps, otherwise he has to wait till the jump is finished
		if(playerJumping == false){
			Vy=JUMP_VELOCITY;
			playerJumping=true;
		}
	}

	// Moves the sprite so they will always face each other no matter the position
	if(PosX > user2.GetPosX()){
		dbPlaySprite (P2_SPRITE, 1, 8, 200);
		dbSprite(P2_SPRITE, PosX, PosY, P1_SPRITE);
	}
	else{
		dbPlaySprite(P1_SPRITE, 1, 8, 200);
		dbSprite(P1_SPRITE, PosX, PosY, P1_SPRITE);
	}

	// If the player falls off and gets below a certaint Y pos (namely off the screen) he dies
	if(PosY > dbScreenHeight()){
		// Checks if he has any more lives, if so his health is reset and a life is taken away, and he respawns
		if(Lives>0){
			Health = HEALTH-1;
			PlayerHealthReset();
			dbDeleteSprite(START_LIFE_COUNTER_ID+Lives);
			Lives--;
			PosX=RESPAWN_WIDTH;
			PosY=RESPAWN_HEIGHT;
		}
		// Otherwise the rest of his health is gone and the game is over
		else{
			dbDeleteSprite(START_LIFE_COUNTER_ID+Lives);
			for(int i=Health; i>=0; i--){
				dbDeleteSprite(START_HEALTH_COUNTER_ID+i);
			}
			//Lives--;
			matchEnd = true;
			//dbDeleteSprite(P1_SPRITE);
		}
	}
	
	// Checks to see if the player fires
	PlayerFire(user2);

}

// Checks to see if the match is over
bool Player::CheckMatchEnd() const{
	return matchEnd;
}
