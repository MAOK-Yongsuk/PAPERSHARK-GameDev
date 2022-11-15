#include "Shark.h"

unsigned Shark::sharks = 0;


Shark::Shark(Texture* texture)

{
	//Dt
	this->dtMultiplier = 62.5f;

	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setTextureRect(IntRect(xpos, 0, 632, 362));
	this->sprite.setScale(0.45f, 0.45f);
	this->sprite.setPosition(15, 450);

	this->maxVelocity = 10.f;
	this->acceleration = 1.f;
	this->stabilizerForce = 0.2f;

	this->sharkNumber = Shark::sharks;
	Shark::sharks++;

	this->initAnimation();
}

void Shark::initAnimation()
{
	this->aniTime.restart();
}

Shark::~Shark()
{

}

void Shark::Movement(Vector2u windowBounds,const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;

		if (this->currentVelocity.x < -this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;

		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->direction.x = 0.f;
		this->direction.y = 1.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
			this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
	}

	// left
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->direction.x = -0.5f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	// right
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->direction.x = 0.5f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}
	
	if (this->currentVelocity.x > 0)
	{
		this->currentVelocity.x -= this->stabilizerForce * dt * this->dtMultiplier;

		if (this->currentVelocity.x < 0)
			this->currentVelocity.x = 0;
	}

	else if (this->currentVelocity.x < 0)
	{
		this->currentVelocity.x += this->stabilizerForce * dt * this->dtMultiplier;

		if (this->currentVelocity.x > 0)
			this->currentVelocity.x = 0;
	}

	if (this->currentVelocity.y > 0)
	{
		this->currentVelocity.y -= this->stabilizerForce * dt * this->dtMultiplier;

		if (this->currentVelocity.y < 0)
			this->currentVelocity.y = 0;
	}

	else if (this->currentVelocity.y < 0)
	{
		this->currentVelocity.y += this->stabilizerForce * dt * this->dtMultiplier;

		if (this->currentVelocity.y > 0)
			this->currentVelocity.y = 0;
	}

	//Final move
	this->sprite.move(this->currentVelocity.x * dt * this->dtMultiplier, 
		this->currentVelocity.y * dt * this->dtMultiplier);

	//Window collision

	if (this->getProsition().x <= -350)
	{
		this->sprite.setPosition(-350.f, this->sprite.getPosition().y);
		this->currentVelocity.x = 0;
	}

	if (this->getProsition().y <= 0)
	{
		this->sprite.setPosition(this->sprite.getPosition().x, 0.f);
		this->currentVelocity.y = 0.f;
	}

	else if (this->getProsition().x >= 1800 - 350)
	{
		this->sprite.setPosition(1800 - 350, this->sprite.getPosition().y);
		this->currentVelocity.x = 0.f;
	}

	else if (this->getProsition().y >= 980)
	{
		this->sprite.setPosition(this->sprite.getPosition().x, 980);
		this->currentVelocity.y = 0.f;
	}
}

void Shark::Update(Vector2u windowBounds, const float &dt)
{
	this->Movement(windowBounds,dt);
}

void Shark::Draw(RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->aniTime.getElapsedTime().asSeconds() >= 0.26f)
	{
		xpos += 630;
		if (xpos >= 1890) xpos = 0;
		this->sprite.setTextureRect(IntRect(xpos, 0, 632, 362));
		this->aniTime.restart();
	}
}