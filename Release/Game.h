#pragma once

#include"Shark.h"
#include"Player.h"
#include"Enemy.h"
#include"textTag.h"
#include<sstream>
#include<vector>
#include "Background.h"


class Game
{
private:
	RenderWindow *window;
	float dtMultiplier;
	float speed;
	Clock Game_clock;
	Time GameTime;

	//------------------ Text --------------------------
	Font font;
	Font font2;
	std::vector<Text> followPlayerTexts;
	std::vector<Text> staticPlayerTexts;
	Text gameOverText;
	Text ScoreText;
	
	//------------------ World -------------------------
	Sprite worldBackgrond[7];
	Texture worldBackgrondTex[7];
	//--------------- texture in game ------------------
	Sprite tape01;
	Texture tape01tex;

	Sprite coral;
	Texture coraltex;
	float xposcoral = 0.00;
	Clock aniTimecoral;

	Sprite plant01;
	Texture plant01tex;
	int xposplant01 = 0;
	Clock aniTimeplant01;

	Sprite plant02;
	Texture plant02tex;
	int xposplant02 = 0;
	Clock aniTimeplant02;

	Sprite water01;
	Texture water01tex;
	Sprite water02;
	Texture water02tex;
	int xposwater01 = 0;
	Clock aniTimewater01;

	Sprite annoy01;
	Texture annoy01tex;

	Sprite annoy02;
	Texture annoy02tex;

	Sprite annoy03;
	Texture annoy03tex;
	int annoytime = 20;

	Sprite shadow;
	Texture shadowtex;

	// ------------ Loading Screen --------------------
	
	Sprite HumSharkloading;
	Texture HumSharkloadingtex;
	int xposHumSharkloading = 0;
	Clock aniTimeHumSharkloading;
	int londingS = 1;

	Sprite shipwreck;
	Texture shipwrecktex;

	float stoptime1;
	float stoptime2;

	int lv2time = 60;
	int lv3time = 110;
	//----------------------- Texture ------------------
	std::vector<Texture> textures;

	//-------------------- TextTag -------------------
	std::vector<textTag> textTags;

	//-------------------- Charetor ------------------
	std::vector<Player> players;
	std::vector<Shark> sharks;
	int playersAlive;

	//---------------------- Enemies --------------------
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	//---------------------- VIP -------------------------
	int VIP = 30;
	int coin = 3;
	bool activate = false;
	Clock clockVIP;
	Time vip;

	Sprite hand;
	Texture handtex;

	Sprite handUI[2];
	Texture handtexUI[2];
	//---------------------------------------------------
	String getscore;
	int intscore;
	//---------------------------------------------------
	bool die = false;
	//--------------------- sound ------------------------
	SoundBuffer buffer;
	Sound sound;

	SoundBuffer coinBf;
	Sound coinsound;

	SoundBuffer damageBf;
	Sound damagesound;

	SoundBuffer diverBf;
	Sound diversound;

	SoundBuffer sharkBf;
	Sound sharksound;

	SoundBuffer lv2Bf;
	Sound lv2sound;
	//---------------------------------------------------
	
public:
	Game(RenderWindow *window);
	virtual ~Game();

	//Accessors
	inline RenderWindow& getWindow() { return *this->window; }
	

	//Setters

	//Functions
	void DrawUI();
	void InitUI(); 
	void UpdateUI();
	void Update(const float& dt);
	void Draw();
	void renderWorld();
	void initWorld();
};

