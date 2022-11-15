#define _CRT_SECURE_NO_DEPRECATE
#include"Game.h"
#include"textTag.h"
#include"TextBox.h"


using namespace std;

void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font){
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Color(51, 25, 0, 255));
	window.draw(text);
}

int main() 
{	
	sf::RenderWindow window(VideoMode(1920, 1080), "PAPERSHARK", Style::Fullscreen);
	
	Clock clock;	
	float dt = 0.f;	
	float width = window.getSize().x;
	//----------------------------------- Menu --------------------------------------
	sf::Font plasebo;
	sf::Font brushscriptmt;
	if (!plasebo.loadFromFile("Fonts/Plasebo Studio - Alaca-Bold.otf"))
	{
		// error
	}
	if (!brushscriptmt.loadFromFile("Fonts/HarlowSolidPlain.otf"))
	{
		// error
	}
	//--------------------------------------------------------------------------------
	Sprite title;
	Texture titletex;
	float xpostitle = 0;
	Clock aniTimetitle;

	titletex.loadFromFile("Textures/title.png");
	title.setTexture(titletex);
	title.setTextureRect(IntRect(xpostitle, 0, 752.25, 359));
	title.setPosition(sf::Vector2f(610, 25));
	title.setScale(0.92, 0.92);
	//-------------------------------------------------------------------------

	sf::Text playtext("PLAY", plasebo, 70);
	playtext.setOrigin(playtext.getGlobalBounds().width / 2, playtext.getGlobalBounds().height / 2);
	playtext.setPosition(sf::Vector2f(width /2, 550));

	sf::Text hightext("HIGH SCORE", plasebo, 70);
	hightext.setOrigin(hightext.getGlobalBounds().width / 2, hightext.getGlobalBounds().height / 2);
	hightext.setPosition(sf::Vector2f(width / 2, 680));

	sf::Text exittext("EXIT", plasebo, 70);
	exittext.setOrigin(exittext.getGlobalBounds().width / 2, exittext.getGlobalBounds().height / 2);
	exittext.setPosition(sf::Vector2f(width / 2, 810));

	Textbox text1(40, sf::Color::Color(75, 50, 25, 255), true);
	text1.setPosScale ({720, 446}, 1,1);
	text1.setLimit(true, 12);
	text1.setFont(brushscriptmt);

	//-------------------------------------- Menu BG --------------------------------------------------
	sf::Sprite menuBackgrond;
	sf::Texture menuBackgrondTex;
	menuBackgrondTex.loadFromFile("Textures/menubg.png");
	menuBackgrond.setTexture(menuBackgrondTex);
	menuBackgrond.setScale(0.64, 0.64);
	//------------------------------------- HighScore BG -----------------------------------------------
	sf::Sprite HighScore;
	sf::Texture HighScoreTex;
	HighScoreTex.loadFromFile("Textures/HIGHSCORE.png");
	HighScore.setTexture(HighScoreTex);
	HighScore.setScale(0.64, 0.64);
	//-------------------------------------- Game loop ------------------------------------------------
	while (window.isOpen())
	{
		Event event;		
		while (window.pollEvent(event)) 
		{					
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();	
			if (event.type == Event::TextEntered)
				text1.typedOn(event);
		}
		//------------------------------ Menu text -------------------------------------
		if (playtext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, 
			sf::Mouse::getPosition(window).y))
		{
			playtext.setFillColor(sf::Color::Color(31, 78, 121, 255));
			playtext.setStyle(sf::Text::Underlined);
		}
		else if (hightext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, 
			sf::Mouse::getPosition(window).y))
		{
			hightext.setFillColor(sf::Color::Color(31, 78, 121, 255));
			hightext.setStyle(sf::Text::Underlined);
		}
		else if (exittext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, 
			sf::Mouse::getPosition(window).y))
		{
			exittext.setFillColor(sf::Color::Color(31, 78, 121, 255));
			exittext.setStyle(sf::Text::Underlined);
		}
		else
		{
			playtext.setFillColor(sf::Color::White);
			playtext.setStyle(0);
			hightext.setFillColor(sf::Color::White);
			hightext.setStyle(0);
			exittext.setFillColor(sf::Color::White);
			exittext.setStyle(0);
		}

		// Put States		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{					
			if (playtext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{	
				string myStr = text1.getText() + " " + "0";
				FILE* file = fopen("Score.txt", "a");
				if (file)
				{
					fwrite(myStr.data(), sizeof(char), myStr.size(), file);
				}
				fclose(file);
				text1.resetText();

				sf::RenderWindow GameWindow(VideoMode(1920, 1080), "PAPERSHARK", Style::Fullscreen);
				Game game(&GameWindow);
				while (GameWindow.isOpen())
				{
					Event aevent;
					while (GameWindow.pollEvent(aevent))
					{
						if (aevent.type == Event::Closed)
							GameWindow.close();
						if (aevent.key.code == Keyboard::Escape)
							GameWindow.close();
					}
					dt = clock.restart().asSeconds();
					//printf("%f\n", dt);
					game.Update(dt);
					game.Draw();	
				}	
				GameWindow.clear();
				
			}
			else if (hightext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{			
				FILE* hp;
				int hscore[5];
				char hname[5][12];
				hp = fopen("./Score.txt", "r");
				for (int i = 0; i < 5; i++)
				{
					fscanf(hp, "%s %d", &hname[i], &hscore[i]);
				}
				fclose(hp);

				sf::RenderWindow HighWindow(sf::VideoMode(1920, 1080), "HighScore", Style::Fullscreen);
				while (HighWindow.isOpen())
				{
					sf::Event hevent;
					while (HighWindow.pollEvent(hevent))
					{
						if (hevent.type == sf::Event::Closed)
							HighWindow.close();
						if (hevent.key.code == Keyboard::Escape)
							HighWindow.close();
					}
					HighWindow.draw(HighScore);

					showHighScore(700, 400, hname[0], HighWindow, &plasebo);
					showHighScore(1200, 400, to_string(hscore[0]), HighWindow, &plasebo);

					showHighScore(700, 480, hname[1], HighWindow, &plasebo);
					showHighScore(1200, 480, to_string(hscore[1]), HighWindow, &plasebo);

					showHighScore(700, 560, hname[2], HighWindow, &plasebo);
					showHighScore(1200, 560, to_string(hscore[2]), HighWindow, &plasebo);

					showHighScore(700, 640, hname[3], HighWindow, &plasebo);
					showHighScore(1200, 640, to_string(hscore[3]), HighWindow, &plasebo);
					
					showHighScore(700, 720, hname[4], HighWindow, &plasebo);
					showHighScore(1200, 720, to_string(hscore[4]), HighWindow, &plasebo);

					HighWindow.display();					
				}
				HighWindow.clear();
			}
			else if (exittext.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				window.close();
			}
		}
		
		//-------------------------------------------------------------------------------
		if (aniTimetitle.getElapsedTime().asSeconds() >= 0.5f)
		{
			xpostitle += 752.25;
			if (xpostitle >= 3009) xpostitle = 0;
			title.setTextureRect(IntRect(xpostitle, 0, 752.25, 359));
			aniTimetitle.restart();
		}

		window.clear();
		window.draw(menuBackgrond);
		window.draw(title);
		window.draw(playtext);
		window.draw(hightext);
		window.draw(exittext);
		text1.drawTo(window);
		window.display();
	}
	return 0;
}







