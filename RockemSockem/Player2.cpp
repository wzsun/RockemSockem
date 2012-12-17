// Player2.cpp - Implementation of Player2.h, creates P2 Object and functions associated with it
// By Wesley Sun

#include "Player2.h"

// Constants to set user's health, life, respawn, and others
// Initial X velocity
#define INITIAL_VX 0.0f
// Initial Y velocity
#define INITIAL_VY 0.0f
// sets Players speed stat
#define SPEED 3.0f
// sets Playes lives
#define LIVES 3
// sets Players health
#define HEALTH 5
// sets the Gravity effect on player
#define GRAVITY 1
// the ends of the stage
#define END_STAGE_RIGHT dbScreenWidth()-175
#define END_STAGE_LEFT 100
// sets the ground level
#define GROUND 250.0f
// P2 X Start Position
#define P2_START_POSITION 450
// P2 sprite ID
#define P2_SPRITE 2
// P1 sprite ID
#define P1_SPRITE 1
// Respawn Height
#define RESPAWN_HEIGHT 0
// Respwan X position
#define RESPAWN_WIDTH 450.0f
// Sets the jump velocity
#define JUMP_VELOCITY -15
// Sprite ID for lives
#define START_LIFE_COUNTER_ID 300
// width of the life bar
#define LIFE_BAR_WIDTH 50
// X position for life bars
#define LIFE_BAR 600
// Y position of the life bar
#define BASE_OF_LIFE_BAR 450
// Y position of the health bar
#define BASE_OF_HEALTH_BAR 425
// Sprite ID for health 
#define START_HEALTH_COUNTER_ID 450
// X Position for Health bar
#define HEALTH_BAR 600
// health bar width
#define HEALTH_BAR_WIDTH 30
// Sprite ID for bullet
#define BULLET 15
// Hit Buffer area for the shot
#define HIT_BUFFER 20
// Sets the height of the  bullet shot respective to the player
#define BULLET_SHOT_HEIGHT 10
// Sets the velocity of the bullet
#define BULLET_VELOCITY 8

// Default constructor that sets all the user's starting values
Player2::Player2(){
	Vx = INITIAL_VX;
	Vy = INITIAL_VY;
	PosX = P2_START_POSITION;
	PosY = GROUND;
	Speed = SPEED;
	Lives = LIVES-1;
	Health = HEALTH-1;
	gravity = GRAVITY;
	playerJumping = false;
	matchEnd = false;
}

// Sets the gravity for the user
void Player2::Gravity(){
	// Creates the acceleration effect
	Vy += gravity;
	PosY += Vy;
	// If the player is off the stage, they fall
	if(PosY > GROUND && (PosX < END_STAGE_RIGHT && PosX > END_STAGE_LEFT)){
		PosY = GROUND;
		Vy=INITIAL_VY;
		playerJumping = false;
	}
	// moves the sprite
	dbSprite(P2_SPRITE,dbSpriteX(P2_SPRITE),PosY,P2_SPRITE);
}

// Sets the items for player2
void Player2::PlayerSetup(){
	// Loads up the sprite
	dbCreateAnimatedSprite ( P2_SPRITE, "goku.png", 4, 2, P2_SPRITE);
	dbSprite(P2_SPRITE, PosX, PosY, P2_SPRITE);
	// Loads the life bar
	int lifeBarWidth = LIFE_BAR;
	for(int i=0; i<LIVES; i++){
		dbLoadImage("life.png",START_LIFE_COUNTER_ID+i);
		dbSprite(START_LIFE_COUNTER_ID+i,lifeBarWidth, BASE_OF_LIFE_BAR, START_LIFE_COUNTER_ID+i);
		lifeBarWidth += LIFE_BAR_WIDTH;
	}
	// Places the user health
	PlayerHealthReset();
	// Loads the bullet
	dbLoadImage("bullet.png", BULLET);
}

// Resets the players health, for example if he dies
void Player2::PlayerHealthReset(){
	int healthBar = HEALTH_BAR;
	for(int i=0; i<HEALTH; i++){
		dbLoadImage("health.png",START_HEALTH_COUNTER_ID+i);
		dbSprite(START_HEALTH_COUNTER_ID+i,healthBar, BASE_OF_HEALTH_BAR, START_HEALTH_COUNTER_ID+i);
		healthBar += HEALTH_BAR_WIDTH;
	}
}
// Gets the X position of player
float Player2::GetPosX() const{
	return PosX;
}

// Gets the Y position of player
float Player2::GetPosY() const{
	return PosY;
}

// Updates the bullet if player has fired one or checks if he hasn't
void Player2::PlayerFire(Player& user1){
	// If the player has already fired
	if(playerIsFiring){
		// Checks which way the direction of the bullet is and adds the velocity of it
		if(directionBullet == true)
			playerBullet -= BULLET_VELOCITY;
		else
			playerBullet += BULLET_VELOCITY;
		// moves the bullet
		dbSprite(BULLET,playerBullet,dbSpriteY(BULLET),BULLET);
		// Checks to see if enemy was hit
		PlayerCheckHitEnemies(user1);
		// If the bullet travels outside of the screen, it's deleted and player can fire again
		if(playerBullet < 0 || playerBullet > dbScreenWidth()){
			dbDeleteSprite(BULLET);
			playerIsFiring = false;
		}
	}
	// If the player hasn't fired then it checks that, and allows player to fire
	if(checkAttack2() == true && playerIsFiring == false){
		playerIsFiring = true;
		// Sets the direction the bullet will go
		if(PosX > user1.GetPosX())
			directionBullet = true;
		else
			directionBullet = false;
		// Creates the bullet coming out of player
		playerBullet = PosX;
		dbSprite(BULLET,playerBullet+(dbSpriteWidth(P2_SPRITE)/2),PosY+BULLET_SHOT_HEIGHT, BULLET);
	}
}

// Checks to see if player has hit anyone
void Player2::PlayerCheckHitEnemies(Player& user1){
	// Makes the bullet the front of it at the center
	int bulletX = dbSpriteX(BULLET)+dbSpriteWidth(BULLET);
	int bulletY = dbSpriteY(BULLET)+(dbSpriteHeight(BULLET)/2);
	// If the bullet is within the sprite width and height w/ a buffer zone, player is hit
	if(bulletX > user1.GetPosX() + HIT_BUFFER && bulletX < user1.GetPosX() + dbSpriteWidth(P1_SPRITE)){
		if(bulletY > user1.GetPosY() && bulletY < user1.GetPosY() + dbSpriteHeight(P1_SPRITE)){
			// Deletes the bullet and decreases P1's health
			dbDeleteSprite(BULLET);
			user1.DecreaseHealth();
			playerIsFiring = false;
		}
	}
}
// P2's decrease health function used if player is hit
void Player2::DecreaseHealth(){
	// If player has no health it checks if he has more lives or not
	if(Health == 0){
		// If player has more lives, then a life is taken away and health is reset and respwans
		if(Lives > 0){
			dbDeleteSprite(START_HEALTH_COUNTER_ID+Health);
			dbDeleteSprite(START_LIFE_COUNTER_ID+Lives);
			Lives--;
			Health = HEALTH-1;
			PlayerHealthReset();
			PosX = RESPAWN_WIDTH;
			PosY = RESPAWN_HEIGHT;
		}
		// Otherwise the last health is taken away and game is over
		else{
			dbDeleteSprite(START_HEALTH_COUNTER_ID+Health);
			Health--;
			dbDeleteSprite(START_LIFE_COUNTER_ID+Lives);
			matchEnd=true;
		}
	}
	// If the player has more health, then a health is just taken away 
	else{
		dbDeleteSprite(START_HEALTH_COUNTER_ID+Health);
		Health--;
	}
}

// Updates the player, to see if he moves or shoots
void Player2::PlayerUpdate(Player& user1){
	// Moves the player left if left arrow is hit
	if(checkLeft2()){
		PosX -= Speed;
	}
	// Moves the player right if right arrow is hti
	if(checkRight2()){
		PosX += Speed;
	}
	// Lets the player jump if he hits up arrow key
	if(checkJump2()){
		// if the player is already jumping, it won't let him jump again
		if(playerJumping == false){
			Vy=JUMP_VELOCITY;
			playerJumping=true;
		}
	}

	//alternates sprite if they pass each other so they always face each other
	if(PosX < user1.GetPosX()){
		dbPlaySprite (P1_SPRITE, 1, 8, 200);
		dbSprite(P1_SPRITE, PosX, PosY, P2_SPRITE);
	}
	else{
		dbPlaySprite (P2_SPRITE, 1, 8, 200);
		dbSprite(P2_SPRITE, PosX, PosY, P2_SPRITE);
	}
	
	// If the palyer is off the screen i.e. falling off, a life is taken away or the match ends
	if(PosY > dbScreenHeight()){
		// Checks if the player has anymore life, if so, then life is taken away and health is reset, and player respawns
		if(Lives>0){
			Health = HEALTH-1;
			PlayerHealthReset();
			dbDeleteSprite(START_LIFE_COUNTER_ID+Lives);
			Lives--;
			PosX=RESPAWN_WIDTH;
			PosY=RESPAWN_HEIGHT;
		}
		// Else the game ends and the player's health is gone
		else{
			// Delets the rest of his lives
			dbDeleteSprite(START_LIFE_COUNTER_ID+Lives);
			// Deletes the rest of his health
			for(int i=Health; i>=0; i--){
				dbDeleteSprite(START_HEALTH_COUNTER_ID+i);
			}
			matchEnd = true;
		}
	}
	// Checks to see if player fired a shot
	PlayerFire(user1);
}

// Used to check if match is over
bool Player2::CheckMatchEnd() const{
	return matchEnd;
}
