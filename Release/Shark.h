#pragma once

#include"textTag.h"

class Shark
{
private:
	float dtMultiplier;
	unsigned sharkNumber;

	Texture* texture;
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


public:
	Shark(Texture* texture);

	virtual ~Shark();

	inline const Vector2f& getProsition()const { return this->sprite.getPosition(); }

	void Movement(Vector2u windowBounds,const float& dt);
	void Update(Vector2u windowBounds, const float& dt);
	void Draw(RenderTarget& target);
	void initAnimation();
	

	//Statics
	static unsigned sharks;
};

