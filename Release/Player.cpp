#include "Player.h"

unsigned Player::players = 0;

Player::Player(std::vector<Texture> &textures)

	:hp(20), hpMax(20),damage(1)
{
	//Dt
	this->dtMultiplier = 62.5f;

	//Texture & Sprites
	this->sprite.setTexture(textures[0]);
	this->sprite.setTextureRect(IntRect(xpos, 0, 514, 331));
	this->sprite.setScale(0.35f, 0.35f);	
	this->sprite.setPosition(350, 450);


	this->maxVelocity = 10.f;
	this->acceleration = 1.f;
	this->stabilizerForce = 0.2f;

	this->playrtNumber = Player::players;
	Player::players++;

	this->initAnimation();
	
}

void Player::initAnimation()
{
	this->aniTime.restart();
}

Player::~Player()
{

}

void Player::Movement(Vector2u windowBounds,const float& dt)
{
	// up
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->direction.x = 0.f; 
		this->direction.y = -1.f;

		if (this->currentVelocity.x < -this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;

		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;	
	}

	// down
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
		this->direction.x = -0.4f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	// right
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->direction.x = 0.3f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	// Drag force
	if (this->currentVelocity.x > 0)
	{
		this->currentVelocity.x -= this->stabilizerForce 
			* dt * this->dtMultiplier;

		if (this->currentVelocity.x < 0)
			this->currentVelocity.x = 0;
	}
		
	else if (this->currentVelocity.x < 0)
	{
		this->currentVelocity.x += this->stabilizerForce
			* dt * this->dtMultiplier;

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
	//std::cout << direction.y << " " << this->currentVelocity.y << " " << this->acceleration;
	this->sprite.move(this->currentVelocity.x * dt * this->dtMultiplier,
		this->currentVelocity.y * dt * this->dtMultiplier);

	//Window collision

	if (this->getProsition().x <= 0)
	{
		this->sprite.setPosition(0.f, this->sprite.getPosition().y);
		this->currentVelocity.x = 0;
	}

	if (this->getProsition().y <= 0)
	{
		this->sprite.setPosition(this->sprite.getPosition().x,0.f);
		this->currentVelocity.y = 0.f;
	}

	else if (this->getProsition().x >= 1800)
	{
		this->sprite.setPosition(1800, this->sprite.getPosition().y);
		this->currentVelocity.x = 0.f;
	}

	else if (this->getProsition().y >= 1000)
	{
		this->sprite.setPosition(this->sprite.getPosition().x, 1000);
		this->currentVelocity.y = 0.f;
	}
}

void Player::Update(Vector2u windowBounds, const float& dt)
{
	this->Movement(windowBounds,dt);
}

void Player::Draw(RenderTarget &target)
{
	target.draw(this->sprite);	

	if (this->aniTime.getElapsedTime().asSeconds() >= 0.28f)
	{
		xpos += 514;
		if (xpos >= 2056) xpos = 0;
		this->sprite.setTextureRect(IntRect(xpos, 0, 514, 331));	
		this->aniTime.restart();
	}
	
	
}
