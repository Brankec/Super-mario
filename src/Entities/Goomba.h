#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "EntitySounds/Jump.h"
#include <iostream>
#include <algorithm>
#include "Entity.h"

class Goomba : public Entity
{
public:
	Goomba(sf::Vector2f position);

public:
	void loadGumboAnimation();
	void GumboUpdate(float deltaTime);
	sf::Vector2f getGoombaPos();
	void GumboAnimation(float deltaTime);

	bool isOnGround;

private:
	sf::IntRect GumboFrame[1][2];
	sf::Vector2u frameStage = { 0,0 };
	float frameDelay = 0;
};

