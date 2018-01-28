#include <iostream>
#include "../../Entities/Player.h"

#pragma once

class TileCollision
{
public:
	TileCollision();

protected:
	void Collide(sf::RectangleShape& tile, Player &entity);
};

