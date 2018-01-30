#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "EntitySounds/Jump.h"
#include <iostream>
#include <algorithm>
#include "Entity.h"

#pragma once
class Gumbo : public Entity
{
public:
	Gumbo();

public:
	void loadGumboAnimation();
	void GumboUpdate(float deltaTime);
	void setPos();
	void GumboAnimation();

	bool isOnGround;

private:
	sf::IntRect GumboFrame[12][2];
	sf::Vector2u frameStage = { 0,0 };
	float frameDelay = 0;
};

