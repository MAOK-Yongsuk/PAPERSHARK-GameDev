#define _CRT_SECURE_NO_DEPRECATE
#include "Game.h"
#include <stdio.h>  
#include <SFML/Graphics.hpp>
#include <math.h>  
#include <stdlib.h>
#include"TextBox.h"
using namespace std;



enum textures { player = 0,
				shark,garbage01, garbage02, garbage03, swfish, 
				coins,
				squid, pufferfish, tigerfish,
				bigsquid, daco, submarine};


Game::Game(RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(200);
	this->dtMultiplier = 62.5f;
	this->speed = -1.0f;
	//--------- sound ---------------------------------------------
	buffer.loadFromFile("Sound/underwater.wav");	
	sound.setBuffer(buffer);	
	sound.play();
	sound.setLoop(true);

	diverBf.loadFromFile("Sound/diver.wav");
	diversound.setBuffer(diverBf);
	diversound.setVolume(10);
	diversound.play();
	diversound.setLoop(true);

	coinBf.loadFromFile("Sound/coin.wav");
	coinsound.setBuffer(coinBf);
	coinsound.setVolume(30);

	damageBf.loadFromFile("Sound/damage.wav");
	damagesound.setBuffer(damageBf);
	damagesound.setVolume(30);

	damageBf.loadFromFile("Sound/damage.wav");
	damagesound.setBuffer(damageBf);
	damagesound.setVolume(30);
	//-------------------------------------------------------------------
	Game_clock.restart();
	//------------------------ Init Font ------------------------------------
	this->font.loadFromFile("Fonts/Plasebo Studio - Alaca-Bold.otf");
	//----------------------- Init textures ----------------------------------
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/sprite-diver.png");
	this->textures.push_back(Texture());
	this->textures[shark].loadFromFile("Textures/sprite-shark.png");
	//this->textures.push_back(Texture());
	//this->textures[shark2].loadFromFile("Textures/HammerShark.png");
	
	this->textures.push_back(Texture());
	this->textures[garbage01].loadFromFile("Textures/garbage01.png");
	this->textures.push_back(Texture());
	this->textures[garbage02].loadFromFile("Textures/garbage02.png");
	this->textures.push_back(Texture());
	this->textures[garbage03].loadFromFile("Textures/garbage03.png");

	this->textures.push_back(Texture());
	this->textures[swfish].loadFromFile("Textures/swordfish.png");
	this->textures.push_back(Texture());
	this->textures[coins].loadFromFile("Textures/coin01.png");

	this->textures.push_back(Texture());
	this->textures[squid].loadFromFile("Textures/Giantsquid.png");
	this->textures.push_back(Texture());
	this->textures[pufferfish].loadFromFile("Textures/pufferfish.png");
	this->textures.push_back(Texture());
	this->textures[tigerfish].loadFromFile("Textures/tigerfish.png");

	this->textures.push_back(Texture());
	this->textures[bigsquid].loadFromFile("Textures/bigsquid.png");
	this->textures.push_back(Texture());
	this->textures[daco].loadFromFile("Textures/Daco.png");
	this->textures.push_back(Texture());
	this->textures[submarine].loadFromFile("Textures/submarine.png");
		
	//----------------------- Init world ---------------------------
	this->initWorld();
	
	//Init player/Charetor
	this->players.push_back(Player(this->textures));
	this->sharks.push_back(Shark(&this->textures[shark]));

	//---------------------- player alive ---------------------------
	this->playersAlive = this->players.size();

	//// number of enemies ////
	this->enemySpawnTimerMax = 18;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->InitUI();
}

Game::~Game()
{
	
}

void Game::InitUI()
{
	Text tempText;
	for (size_t i = 0; i < this->players.size(); i++)
	{
		// Follow Text Init		
		tempText.setFont(font);
		tempText.setCharacterSize(20);
		tempText.setFillColor(Color::Red);
		tempText.setString(std::to_string(i));
		this->followPlayerTexts.push_back(Text(tempText));
		
		//Static Text Init
		tempText.setFont(font);
		tempText.setCharacterSize(50);
		tempText.setFillColor(Color::White);
		tempText.setString("");
		this->staticPlayerTexts.push_back(Text(tempText));
	}
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setString("GAME OVER!!");
	this->gameOverText.setPosition(this->window->getSize().x/2 - 150.f, this->window->getSize().y / 2.3);

	this->ScoreText.setFont(this->font);
	this->ScoreText.setFillColor(sf::Color::Color(31, 78, 121, 255));
	this->ScoreText.setCharacterSize(60);
	this->ScoreText.setPosition(this->window->getSize().x / 2 - 170.f, this->window->getSize().y / 2);

	// handUI
	this->handtexUI[1].loadFromFile("Textures/hand2.png");
	this->handUI[1].setTexture(this->handtexUI[1]);
	this->handUI[1].setPosition(50, 30);
	this->handUI[1].setScale(0.1, 0.1);

	this->handtexUI[0].loadFromFile("Textures/hand1.png");
	this->handUI[0].setTexture(this->handtexUI[0]);
	this->handUI[0].setPosition(50, 30);
	this->handUI[0].setScale(0.1, 0.1);
}

void Game::initWorld()
{
//--------------------------------- BG -------------------------------------		
	//------------------------- Level 1 -------------------------------
	this->worldBackgrondTex[0].loadFromFile("Textures/BGly01.png");
	this->worldBackgrond[0].setTexture(this->worldBackgrondTex[0]);
	this->worldBackgrond[0].setScale(0.903, 0.765);
	
	this->worldBackgrondTex[1].loadFromFile("Textures/BGly02.png");
	this->worldBackgrond[1].setTexture(this->worldBackgrondTex[1]);
	this->worldBackgrond[1].setPosition(0, 660);
	this->worldBackgrond[1].setScale(1.065, 0.989);

	this->worldBackgrondTex[2].loadFromFile("Textures/BGly03.png");
	this->worldBackgrond[2].setTexture(this->worldBackgrondTex[2]);
	this->worldBackgrond[2].setPosition(0, 660);
	this->worldBackgrond[2].setScale(1.065, 0.989);

	this->worldBackgrondTex[3].loadFromFile("Textures/BGly04.png");
	this->worldBackgrond[3].setTexture(this->worldBackgrondTex[3]);
	this->worldBackgrond[3].setPosition(0, 920);
	this->worldBackgrond[3].setScale(1.065, 0.989);

	//------------------------- Level 2 -------------------------------
	this->worldBackgrondTex[4].loadFromFile("Textures/BG2ly01.png");
	this->worldBackgrond[4].setTexture(this->worldBackgrondTex[4]);
	this->worldBackgrond[4].setScale(0.903, 0.765);

	this->worldBackgrondTex[5].loadFromFile("Textures/BG2ly03.png");
	this->worldBackgrond[5].setTexture(this->worldBackgrondTex[5]);
	this->worldBackgrond[5].setPosition(0, 320);
	this->worldBackgrond[5].setScale(1.68, 1.68);

	//-------------------------- Lavel 3 -------------------------------
	this->worldBackgrondTex[6].loadFromFile("Textures/BG3ly01.png");
	this->worldBackgrond[6].setTexture(this->worldBackgrondTex[6]);
	this->worldBackgrond[6].setScale(1.0665, 1);
	//------------------------------------------------------------------

	// TapeTexture
	this->tape01tex.loadFromFile("Textures/tape01.png");
	this->tape01.setTexture(this->tape01tex);
	this->tape01.setPosition(1710, -62);
	this->tape01.setScale(1.2, 1.2);

	//Coral
	this->coraltex.loadFromFile("Textures/sprite-coral.png");
	this->coral.setTexture(this->coraltex);
	this->coral.setTextureRect(IntRect(xposcoral, 0.00, 205.34, 165));
	this->coral.setPosition(990, 920);
	this->coral.setScale(0.8, 0.95); 

	// Plant01
	this->plant01tex.loadFromFile("Textures/sprite-plant01.png");
	this->plant01.setTexture(this->plant01tex);
	this->plant01.setTextureRect(IntRect(xposplant01, 0, 104, 179));
	this->plant01.setPosition(70, 850);
	this->plant01.setScale(1, 1);

	// Plant02
	this->plant02tex.loadFromFile("Textures/sprite-plant02.png");
	this->plant02.setTexture(this->plant02tex);
	this->plant02.setTextureRect(IntRect(xposplant02, 0, 79, 153));
	this->plant02.setPosition(1825, 900);
	this->plant02.setScale(1, 1);

	// water01
	this->water01tex.loadFromFile("Textures/water.png");
	this->water01.setTexture(this->water01tex);
	this->water01.setTextureRect(IntRect(xposwater01, 0, 159, 410));
	this->water01.setPosition(-10, 600);
	this->water01.setScale(1, 1);

	// water02
	this->water02tex.loadFromFile("Textures/water.png");
	this->water02.setTexture(this->water02tex);
	this->water02.setTextureRect(IntRect(xposwater01, 0, 159, 410));
	this->water02.setPosition(1700, 250);
	this->water02.setScale(1, 2.2);

	//HammerShark level.2
	this->HumSharkloadingtex.loadFromFile("Textures/HumSharkloading.png");
	this->HumSharkloading.setTextureRect(IntRect(xposHumSharkloading, 0, 508, 332));
	this->HumSharkloading.setScale(5, 5);

	//shipwreck level.3
	this->shipwrecktex.loadFromFile("Textures/Level3.png");
	this->shipwreck.setScale(0.9, 0.9);

	// handVIP
	this->handtex.loadFromFile("Textures/hand.png");
	this->hand.setScale(1.5, 1.5);

	// annoy
	this->annoy01tex.loadFromFile("Textures/tropicalfish.png");	
	this->annoy01.setScale(1, 1);
	this->annoy02tex.loadFromFile("Textures/Itemseaweed.png");
	this->annoy02.setScale(1, 1);
	this->annoy03tex.loadFromFile("Textures/cnidaria.png");
	this->annoy03.setScale(1, 1);

	// SHADOW
	this->shadowtex.loadFromFile("Textures/shadow.png");
	this->shadow.setTexture(this->shadowtex);
	this->shadow.setScale(1.07, 1);
	this->shadow.setPosition(-31, 0);
	
}

void Game::UpdateUI()
{
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++)
	{
		this->followPlayerTexts[i].setPosition(this->players[i].getProsition().x+60, this->players[i].getProsition().y - 20.f);
		this->followPlayerTexts[i].setString("HP : " + this->players[i].getHpAsString());
	}
	
	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{
		this->staticPlayerTexts[i].setPosition(40,0);
		this->staticPlayerTexts[i].setString("Score : " + this->players[i].getScore());
		getscore = this->players[i].getScore();
	}
}

void Game::Update(const float &dt)
{			
	GameTime = Game_clock.getElapsedTime();
	if (this->playersAlive > 0)
	{		
		//Update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer += 1.2f * dt * this->dtMultiplier;

		//---------------------- VIP -------------------------
		if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {	
			clockVIP.restart();
			for (int i = 0; i < this->players.size(); i++)
			{				
				if (this->players[i].showScore() >= VIP) {
					activate = true;					
					VIP += 40;
					coin = 2;
					//handVIP
					this->hand.setTexture(this->handtex);
					this->hand.setPosition(-800, -155);										
				}
			}
		}
		if (activate == true) {				
			this->hand.move(+3.5, 0);			
			vip = clockVIP.getElapsedTime();
			if(vip.asSeconds() >= 5) { 
				activate = false; 
				coin = 3;
			}
		}

		//---------------- loading screen -----------------------		
				
		if (GameTime.asSeconds() >= lv3time && londingS == 2) {
			//shipwreck level.3
			this->shipwreck.setTexture(this->shipwrecktex);
			this->shipwreck.setPosition(1900, 150);
			stoptime1 = GameTime.asSeconds();			
			londingS = 3;
			speed -= 0.16f;
		}
		else if (GameTime.asSeconds() >= lv2time && londingS == 1) {
			//HammerShark level.2
			this->HumSharkloading.setTexture(this->HumSharkloadingtex);
			this->HumSharkloading.setPosition(1500, -300);
			stoptime1 = GameTime.asSeconds();				
			londingS = 2;
			speed -= 0.15f;
			enemySpawnTimerMax -= 8;
		}
				
		if (GameTime.asSeconds() <= stoptime1 + 12) {
			this->HumSharkloading.move(-7.5, 0);
			this->shipwreck.move(-3.5, 0);
		}		
		//-------------------- annoytime ------------------------
		if (GameTime.asSeconds() >= annoytime) {
			if (londingS == 2 || londingS == 1) {
				if (rand() % 2 + 1 == 1) {
					this->annoy01.setTexture(this->annoy01tex);
					this->annoy01.setPosition(1800, 30);
					annoytime += rand() % 30 + 15;
					stoptime2 = GameTime.asSeconds();
				}
				else {
					this->annoy02.setTexture(this->annoy02tex);
					this->annoy02.setPosition(1800, -30);
					this->annoy02.setScale(0.5, 1);
					annoytime += rand() % 30 + 15;
					stoptime2 = GameTime.asSeconds();
				}
			}	
			else if (londingS == 3) {
				this->annoy03.setTexture(this->annoy03tex);
				this->annoy03.setPosition(0, 1005);
				annoytime += rand() % 20 + 10;
				stoptime2 = GameTime.asSeconds();
			}
		}	

		if (GameTime.asSeconds() <= stoptime2 + 8) {
			this->annoy01.move(-4.2, 0);
			this->annoy02.move(-3, 0);
			this->annoy03.move(0, -2);
		}				
		// ---------------------------------------------------------

		//Spawn enemies, coin
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			if (londingS == 1) {
				if (rand() % coin + 1 == 1)
				{
					this->enemies.push_back(Enemy(
						&this->textures[coins], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.15f, 0.15f), 0, 1, 0));
				}
				else if (rand() % 2 + 1 == 2 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[swfish], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.14f, 0.14f), 0, 3, 1));
				}
				else if (rand() % 3 + 1 == 1 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[garbage01], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.35f, 0.35f), 0, 3, 1));
				}
				else if (rand() % 3 + 1 == 2 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[garbage02], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.35f, 0.35f), 0, 3, 1));
				}
				else if (rand() % 3 + 1 == 3 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[garbage03], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.35f, 0.35f), 0, 3, 1));
				}
			}
			else if (londingS == 2) {
				if (rand() % coin + 1 == 1)
				{
					this->enemies.push_back(Enemy(
						&this->textures[coins], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.15f, 0.15f), 0, 1, 0));
				}

				else if (rand() % 2 + 1 == 2 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[tigerfish], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.35f, 0.35f), 0, 2, 1));
				}
				else if (rand() % 3 + 1 == 1 && activate == false) 
				{
					this->enemies.push_back(Enemy(
						&this->textures[pufferfish], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.48f, 0.48f), 0, 2, 1));
				}
				else if (rand() % 3 + 1 == 2 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[squid], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.35f, 0.35f), 0, 3, 3));
				}
			}
			else if (londingS == 3){
				if (rand() % coin + 1 == 1)
				{
					this->enemies.push_back(Enemy(
						&this->textures[coins], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.15f, 0.15f), 0, 1, 0));
				}
				else if (rand() % 2 + 1 == 2 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[daco], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.3f, 0.3f), 0, 2, 1));
				}
				else if (rand() % 3 + 1 == 1 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[bigsquid], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(1.f, 1.f), 0, 2, 1));
				}
				else if (rand() % 3 + 1 == 2 && activate == false)
				{
					this->enemies.push_back(Enemy(
						&this->textures[submarine], this->window->getSize(),
						Vector2f(0.f, 0.f),
						Vector2f(speed, 0.f), Vector2f(0.7f, 0.7f), 0, 3, 3));
				}
			}
			
			this->enemySpawnTimer = 0;
		}
	
		//PLAYER
		for (size_t i = 0; i < this->players.size(); i++)
		{			
			//UPDATE PLAYER
			this->players[i].Update(this->window->getSize(),dt);
			intscore = this->players[i].showScore();
		}

		// SHARK
		for (size_t j = 0; j < this->sharks.size(); j++)
		{
			this->sharks[j].Update(this->window->getSize(), dt);
		}

		//UPDATE enemies
		for (size_t i = 0; i < this->enemies.size(); i++)
		{
			this->enemies[i].Update(dt);

			for (size_t k = 0; k < this->players.size(); k++)
			{
				if (this->players[k].isAlive())
				{					
					if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds()))
					{
						int damage = this->enemies[i].getDamage();
						this->players[k].takeDamage(damage);

						// Score
						if (damage == 0)
						{
							coinsound.play();
							this->players[k].getScore(1);
							this->textTags.push_back(
								textTag(&this->font,
									"+" + std::to_string(1),
									Color::Yellow,
									Vector2f(this->players[k].getProsition().x + 100.f,
										this->players[k].getProsition().y - 50.f), 28));
						}
						else {
							damagesound.play();
							this->textTags.push_back(
								textTag(&this->font,
									"-" + std::to_string(damage),
									Color::Red,
									Vector2f(this->players[k].getProsition().x + 100.f,
										this->players[k].getProsition().y - 50.f), 28));
						}

						
						if (!this->players[k].isAlive())
						{
							this->playersAlive--;
						}							
						this->enemies.erase(this->enemies.begin() + i);
						return; //return!!						
					}
				}
			}

			if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
			{
				this->enemies.erase(this->enemies.begin() + i);
				break; //return!!
			}
		}

		//Text Tags
		for (size_t i = 0; i < this->textTags.size(); i++)
		{
			this->textTags[i].Update(dt);			
			if (this->textTags[i].getTimer() <= 0.f)
			{
				this->textTags.erase(this->textTags.begin() + i);
				break;
			}
		}

		//UPDATE UI
		this->UpdateUI();
	}
	else if(this->playersAlive <= 0 && die == false) {	
		die = true;	
		
		FILE* fp;
		char temp[255];
		int score[6];
		String name[6];
		vector <pair<int, string>> userScore;
		fp = fopen("./Score.txt", "r");
		for (int i = 0; i < 6; i++)
		{
			fscanf(fp, "%s", &temp);
			name[i] = temp;
			fscanf(fp, "%d", &score[i]);
			userScore.push_back(make_pair(score[i], name[i]));
		}
		score[5] = intscore;
		userScore.push_back(make_pair(score[5], name[5]));
		sort(userScore.begin(), userScore.end());
		fclose(fp);

		fopen("./Score.txt", "w");
		for (int i = 6; i >= 2; i--)
		{
			strcpy(temp, userScore[i].second.c_str());
			fprintf(fp, "%s %d\n", temp, userScore[i].first);
		}
		fclose(fp);
	}
}

void Game::renderWorld()
{		
	if (GameTime.asSeconds() >= lv3time) {
		this->window->draw(this->worldBackgrond[6]);
	}
	else if (GameTime.asSeconds() >= lv2time) {
		this->window->draw(this->worldBackgrond[4]);		
		this->window->draw(this->worldBackgrond[5]);
	}	
	else {
		this->window->draw(this->worldBackgrond[0]);
		this->window->draw(this->worldBackgrond[1]);
		this->window->draw(this->worldBackgrond[2]);
	}
	this->window->draw(this->worldBackgrond[3]);
		
	this->window->draw(this->tape01);
	this->window->draw(this->coral);
	this->window->draw(this->plant01);
	this->window->draw(this->plant02);
	this->window->draw(this->water01);
	this->window->draw(this->water02);
	
			
	/// Coral-animation
	if (this->aniTimecoral.getElapsedTime().asSeconds() >= 0.5f)
	{
		xposcoral += 205.34;
		if (xposcoral >= 616.02) xposcoral = 0.00;
		this->coral.setTextureRect(IntRect(xposcoral, 0.00, 205.34, 165));
		this->aniTimecoral.restart();
	}

	/// Plant01-animation
	if (this->aniTimeplant01.getElapsedTime().asSeconds() >= 0.5f)
	{
		xposplant01 += 104;
		if (xposplant01 >= 312) xposplant01 = 0;
		this->plant01.setTextureRect(IntRect(xposplant01, 0, 104, 176));
		this->aniTimeplant01.restart();
	}

	/// Plant02-animation
	if (this->aniTimeplant02.getElapsedTime().asSeconds() >= 0.5f)
	{
		xposplant02 += 79;
		if (xposplant02 >= 316) xposplant02 = 0;
		this->plant02.setTextureRect(IntRect(xposplant02, 0, 79, 153));
		this->aniTimeplant02.restart();
	}

	// water01
	if (this->aniTimewater01.getElapsedTime().asSeconds() >= 0.5f)
	{
		xposwater01 += 159;
		if (xposwater01 >= 954) xposwater01 = 0;
		this->water01.setTextureRect(IntRect(xposwater01, 0, 159, 410));
		this->water02.setTextureRect(IntRect(xposwater01, 0, 159, 410));
		this->aniTimewater01.restart();
	}
	
	//SharkLoading
	if (this->aniTimeHumSharkloading.getElapsedTime().asSeconds() >= 0.3f)
	{
		xposHumSharkloading += 508;
		if (xposHumSharkloading >= 1524) xposHumSharkloading = 0;
		this->HumSharkloading.setTextureRect(IntRect(xposHumSharkloading, 0, 508, 332));
		this->aniTimeHumSharkloading.restart();
	}
}

void Game::DrawUI()
{
	for (size_t i = 0; i < this->followPlayerTexts.size(); i++)
	{
		if (this->players[i].isAlive())
		{
			this->window->draw(this->followPlayerTexts[i]);
		}		
	}

	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{
		this->window->draw(this->staticPlayerTexts[i]);
	}

	if (this->playersAlive <= 0)
	{
		this->ScoreText.setString("Your Score: " + getscore);
		this->window->draw(this->ScoreText);
		this->window->draw(this->gameOverText);
	}

	for (int i = 0; i < this->players.size(); i++)
	{
		if (this->players[i].showScore() >= VIP) {
			this->window->draw(this->handUI[0]);
		}
		else {
			this->window->draw(this->handUI[1]);
		}
	}	
}

void Game::Draw()
{
	window->clear();	
	this->renderWorld();

	for (size_t i = 0; i < this->players.size(); i++)
	{
		if (this->players[i].isAlive())
		{			
			this->players[i].Draw(*this->window);
		}
	}

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this-> window);
	}

	for (size_t j = 0; j < this->sharks.size(); j++)
	{
		this->sharks[j].Draw(*this->window);
	}

	for (size_t i = 0; i < this->textTags.size(); i++)
	{
		this->textTags[i].Draw(*this->window);
	}
					
	this->window->draw(this->annoy01);
	this->window->draw(this->annoy02);	
	this->window->draw(this->HumSharkloading);
	this->window->draw(this->shipwreck);
	if (GameTime.asSeconds() >= lv3time && this->playersAlive > 0) { this->window->draw(this->shadow);}
	this->window->draw(this->annoy03);	
	this->window->draw(this->hand);
	this->DrawUI();
	this->window->display();
}


