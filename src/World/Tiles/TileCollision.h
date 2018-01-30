#include <iostream>
#include "../../Entities/Player.h"

#pragma once

class TileCollision
{
public:
	TileCollision();



protected:
	void CheckForGround(sf::RectangleShape& tile, sf::FloatRect entity, bool* isCollide);
	void Collide(sf::RectangleShape& tile, sf::FloatRect entity, bool* isCollide);
};

