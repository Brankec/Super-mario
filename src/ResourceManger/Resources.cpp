#include "Resources.h"
#include <iostream>

void res::loadResources()
{
	NPC.loadFromFile("res/entities/sprite/enemies.png");
	Player.loadFromFile("res/entities/sprite/mario.png");
	Tiles.loadFromFile("res/tiles/world.png");
}

sf::Texture res::getPlayerTexture()
{
	return Player;
}

sf::Texture res::getNPCTexture()
{
	return NPC;
}

sf::Texture res::getTilesTexture()
{
	return Tiles;
}
