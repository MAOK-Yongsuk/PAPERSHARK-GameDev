#pragma once
#include"textTag.h"
#define MAX_ITEMS 3 //start leaderbaord exit

class Menu
{
private:
	Sprite menuBackgrond;
	Texture menuBackgrondTex;

	sf::Font font;
	sf::Text menu[MAX_ITEMS];

	int selectthis = 0;

public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void selectItem(sf::RenderWindow& window);
	int GetPressedItem() { return selectthis; }
 
};

