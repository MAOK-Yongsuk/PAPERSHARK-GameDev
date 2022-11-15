#include "Menu.h"
#include "Game.h"
#include "textTag.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Fonts/Plasebo Studio - Alaca-Bold.otf")) 
	{
		//handle error
	}

	// Menu
	menu[0].setFont(font);
	menu[0].setCharacterSize(80);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setStyle(sf::Text::Style::Underlined);
	menu[0].setString("PLAY");
	menu[0].setOrigin(menu[0].getGlobalBounds().width / 2, menu[0].getGlobalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1)*1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("HIGH SCORE");
	menu[1].setOrigin(menu[1].getGlobalBounds().width / 2, menu[1].getGlobalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("EXIT");
	menu[2].setOrigin(menu[2].getGlobalBounds().width / 2, menu[2].getGlobalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3));

	// menu BG
	this->menuBackgrondTex.loadFromFile("Textures/menubg.jpg");
	this->menuBackgrond.setTexture(this->menuBackgrondTex);
	this->menuBackgrond.setScale(2.37, 2);
}

Menu::~Menu()
{

}

void Menu::selectItem(sf::RenderWindow& window)
{
	if (menu[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setStyle(sf::Text::Underlined);
	}

	else if (menu[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		menu[1].setFillColor(sf::Color::Red);
		menu[1].setStyle(sf::Text::Underlined);
	}
	else if (menu[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		menu[2].setFillColor(sf::Color::Red);
		menu[2].setStyle(sf::Text::Underlined);
	}
	else 
	{
		menu[0].setFillColor(sf::Color::White);
		menu[0].setStyle(0);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setStyle(0);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setStyle(0);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (menu[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		{
			selectthis = 1;
		}
		else if (menu[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		{
			selectthis = 2;
		}
		else if (menu[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		{
			selectthis = 3;
			window.close();
		}
	}
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(this->menuBackgrond);

	for (int i = 0; i < MAX_ITEMS; i++) 
	{
		window.draw(menu[i]);
	}
}


