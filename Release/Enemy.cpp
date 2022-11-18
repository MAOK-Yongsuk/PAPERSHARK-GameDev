#include "Enemy.h"
#include"textTag.h"

enum eTypes { MOVEMENT = 0, FOLLOW, FOLLOWFAST, FOLLOWSHOOT };

Enemy::Enemy(Texture *texture, Vector2u windowBounds,
	Vector2f position, Vector2f direction,
	Vector2f scale, int type,
	int damageMax, int damageMin)

{
	this->dtMultiplier = 62.5f;

	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(scale);
	this->windowBounds = windowBounds;

	this->direction = direction;
	this->sprite.setPosition(windowBounds.x, (rand() % windowBounds.y) - (this->sprite.getGlobalBounds().height/4));

	this->type = type;

	this->hp = hp;

	this->damageMax = damageMax;
	this->damageMin = damageMin;

}

Enemy::~Enemy()
{

}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
		this->hp = 0;
}

void Enemy::Update(const float& dt)
{
	switch (this->type)
	{
	case 0:

		this->sprite.move(this->direction.x * 10.f * dt * this->dtMultiplier, 
			this->direction.y * 10.f * dt * this->dtMultiplier);

		break;

	default:

		break;
	}
}

void Enemy::Draw(RenderTarget& target)
{
	target.draw(this->sprite);	
}


