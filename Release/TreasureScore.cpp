#include "TreasureScore.h"
#include"textTag.h"

TreasureScore::TreasureScore(Texture* texture, Vector2u windowSize)
{
	this->HPMax = rand() % 3 + 1;
	this->HP = this->HPMax;

	this->shape.setTexture(*texture);
	this->shape.setScale(0.2f,0.2f);
	this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, (rand() % windowSize.y) + this->shape.getGlobalBounds().height);
}

TreasureScore::~TreasureScore()
{

}

void TreasureScore::Update()
{
	this->shape.move(-4.0f, 0.f);
}


void TreasureScore::Draw(RenderTarget& target)
{
	target.draw(this->shape);
}

