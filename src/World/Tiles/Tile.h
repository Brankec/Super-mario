#include <iostream>
#include <SFML/Graphics.hpp>

#pragma once

class Tile
{
public:
	Tile();

protected:
	sf::RectangleShape tileRec; //default
	sf::Texture tileTex;

	sf::Vector2f position;

	sf::Vector2i tileTextureSize = { 32, 32 }; //default

	bool doesCollide = true; //default
};

