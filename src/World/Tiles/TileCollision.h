#include <iostream>
#include "../../Entities/Player.h"

#pragma once

class TileCollision
{
public:
	TileCollision();



protected:
	void CheckForGround(sf::RectangleShape& tile, Player &entity);
	void Collide(sf::RectangleShape& tile, Player &entity);
};

