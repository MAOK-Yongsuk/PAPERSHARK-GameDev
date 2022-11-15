#pragma once

#include"textTag.h"

using namespace sf;

class Player
{
private:
	float dtMultiplier;
	unsigned playrtNumber;

	Sprite sprite;
	RectangleShape hitBox;

	int controls[5];
	Vector2f currentVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
	float stabilizerForce;

	//sprite sheet
	int xpos = 0;
	Clock aniTime;

	// HP/Damage
	int hp;
	int hpMax;
	int damage;

	//Score
	int scores;


public:
	Player(std::vector<Texture> & textures);

	virtual ~Player();

	//Accessors
	inline const Vector2f& getProsition()const { return this->sprite.getPosition(); }
	inline const String getHpAsString()const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
	inline FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline void takeDamage(int damage) { this->hp -= damage; }

	inline const String getScore()const { return std::to_string(this->scores); }
	inline void getScore(int score) { this->scores += 1; }
	inline int showScore() { return this->scores; }

	inline bool isAlive()const { return this->hp > 0; }
	//bool isDamageCooldown() {return this->da}

	//Functions
	void Movement(Vector2u windowBounds,const float& dt);
	void Update(Vector2u windowBounds, const float& dt);
	void Draw(RenderTarget &target);
	void initAnimation();

	//Statics
	static unsigned players;
};

