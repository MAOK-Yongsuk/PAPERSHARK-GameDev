#include "Background.h"

Background::Background(sf::Texture* texture, float speed)
{
	this->speed = speed;
	this->size = sf::Vector2f(1980.0f, 1080.0f);

	this->worldBackgrondTex[0].loadFromFile("Textures/BGly01.png");
	this->worldBackgrond.setTexture(this->worldBackgrondTex[0]);
	this->worldBackgrond.setScale(1.065, 0.989);

	this->worldBackgrondTex[1].loadFromFile("Textures/BGly02.png");
	this->worldBackgrondTex[2].loadFromFile("Textures/BGly03.png");

	this->worldBackgrondTex[3].loadFromFile("Textures/BGly04.png");
	this->worldBackgrond.setTexture(this->worldBackgrondTex[3]);
	this->worldBackgrond.setScale(1.065, 0.989);

	std::vector<Background> backgrounds;
	backgrounds.push_back(Background(&worldBackgrondTex[0], -30.f));
	backgrounds.push_back(Background(&worldBackgrondTex[1], -50.f));
	backgrounds.push_back(Background(&worldBackgrondTex[2], -130.f));
	backgrounds.push_back(Background(&worldBackgrondTex[3], -100.f));

	body[0].setSize(size);
	body[1].setSize(size);
	body[0].setTexture(texture);
	body[1].setTexture(texture);

	if (speed < 0) //left
		body[1].setPosition(size.x - 2.0f, 0.0f);
	else body[1].setPosition(-size.x + 2.0f, 0.0f);

}

void Background::Update(float deltaTime)
{
	for (int i = 0; i < 2; i++)
	{
		position = body[i].getPosition();

		body[i].move(speed * deltaTime, 0);

		if (position.x <= -size.x && speed < 0)
			body[i].setPosition(size.x - 4.0f, position.y);
		else if(position.x >= size.x && speed > 0)
			body[i].setPosition(- size.x + 4.0f, position.y);
	}
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(body[0]);
	window.draw(body[1]);
}
