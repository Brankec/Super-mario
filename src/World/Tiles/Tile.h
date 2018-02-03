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

	sf::Vector2i tileTextureSize = { 32, 32 }; //default

	bool doesCollide = false; //default

public:
	bool isTileHit = false; //default
};

