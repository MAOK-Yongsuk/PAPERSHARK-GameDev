#pragma once

#include"textTag.h"

class Enemy
{
private:
	Texture* texture;
	Sprite sprite;
	Vector2u windowBounds;
	Vector2f direction;

	float dtMultiplier;

	int type;

	int hp;
	int hpMax;
	int damageMin;
	int damageMax;

	//sprite sheet
	float xpos = 0;
	Clock aniTime;


public:
	Enemy(Texture* texture, Vector2u windowBounds,
		Vector2f position, 
		Vector2f direction,
		Vector2f scale, int type,
		int damageMax, int damageMin);

	virtual ~Enemy();

	//Accessors
	inline const int getDamage()const { return rand() % this->damageMax + this->damageMin; }
	inline const int getHP()const { return this->hp; }
	//inline const int getHPMax()const { return this->hpMax; }
	inline FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition()const { return this->sprite.getPosition(); }

	void takeDamage(int damage);
	void Update(const float &dt);
	void Draw(RenderTarget &target);

};

