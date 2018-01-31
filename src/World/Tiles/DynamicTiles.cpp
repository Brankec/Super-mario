#include "DynamicTiles.h"
#include <string>

DynamicTiles::DynamicTiles(int TilePositionX, int TilePositionY, sf::Texture& tileTexture, sf::Vector2f tileIndex)
{
	tileRec.setSize({ 64,64 });
	tileRec.setPosition(TilePositionX, TilePositionY);

	tileTextureSize.x = 16;
	tileTextureSize.y = 16;

	tileRec.setTexture(&tileTexture);
	setTileTexture(tileIndex);

	ToggleCollision(true);
	ToggleDestructable(true);
}

void DynamicTiles::setTileTexture(sf::Vector2f tileIndex) //the index is the actual tile texture position.
{
	tileRec.setTextureRect(sf::IntRect(tileIndex.x, tileIndex.y, tileTextureSize.x, tileTextureSize.y));
}

void DynamicTiles::setTilePosition(sf::Vector2f tPosition)
{
	tileRec.setPosition(tPosition);
}

void DynamicTiles::ToggleCollision(bool set)
{
	doesCollide = set;
}

void DynamicTiles::ToggleDestructable(bool set)
{
	doesDestroy = set;
}

void DynamicTiles::Collision(Player & entity)
{
	if (doesCollide)
	{
		CheckForGround(tileRec, entity);
		CollidePlayer(tileRec, entity);
	}
}

void DynamicTiles::drawTile(sf::RenderTarget & renderer)
{
	renderer.draw(tileRec);
}

sf::RectangleShape DynamicTiles::getTile()
{
	return tileRec;
}


