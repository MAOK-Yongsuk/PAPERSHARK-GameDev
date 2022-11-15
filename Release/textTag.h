#pragma once

#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include <iostream>
#include<vector>
#include<random>
#include<math.h>
#include<fstream>
#include<sstream>
#include<windows.h>
#include<stdio.h>
#include<utility>
#include<algorithm>
#include<string>
#include <iostream>
//#include<pthread.h>

using namespace sf;

class textTag
{
private:
	float dtMultiplier;

	Font* font;
	Text text;

	float speed;
	Vector2f direction;
	float timerMax;
	float timer;

public:
	textTag(Font* font, std::string text, const Color color,
		Vector2f position, unsigned int size);

	virtual ~textTag();

	//Accessors
	inline const float& getTimer()const { return this->timer; }

	void Update(const float &dt);
	void Draw(RenderTarget &target);
};