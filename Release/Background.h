#pragma once
#include"textTag.h"

class Background
{
public:
	Background(sf::Texture* text, float speed);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body[2];
	sf::Vector2f position;
	sf::Vector2f size;

	Sprite worldBackgrond;
	Texture worldBackgrondTex[5];

	float speed;

};

