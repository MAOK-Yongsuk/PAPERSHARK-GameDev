#pragma once
#include"textTag.h"

class TreasureScore
{
private:
	Sprite shape;

	int HP;
	int HPMax;


public:	

	TreasureScore(Texture* texture, Vector2u windowSize);

	virtual ~TreasureScore();

	inline FloatRect getGlobalBounds()const { return this->shape.getGlobalBounds(); }
	inline Vector2f getPosition()const { return this->shape.getPosition(); }

	void Draw(RenderTarget& target);
	void Update();
	
};

