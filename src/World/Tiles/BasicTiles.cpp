#include "BasicTiles.h"
#include <string>

BasicTiles::BasicTiles(int TilePositionX, int TilePositionY, sf::Texture& tileTexture, sf::Vector2f tileIndex)
{
	tileRec.setSize({ 64,64 });
	tileRec.setPosition(TilePositionX, TilePositionY);

	tileTextureSize.x = 16;
	tileTextureSize.y = 16;

	tileRec.setTexture(&tileTexture);
	setTileTexture(tileIndex);
}

void BasicTiles::setTileTexture(sf::Vector2f tileIndex) //the index is the actual tile texture position.
{
	tileRec.setTextureRect(sf::IntRect(tileIndex.x, tileIndex.y, tileTextureSize.x, tileTextureSize.y));
}

void BasicTiles::setTilePosition(sf::Vector2f tPosition)
{
	tileRec.setPosition(tPosition);
}

void BasicTiles::ToggleCollision(bool set)
{
	doesCollide = set;
}

void BasicTiles::Collision(Player & entity)
{
	if (doesCollide)
	{
		CheckForGround(tileRec, entity);
		Collide(tileRec, entity);
	}
}

void BasicTiles::drawTile(sf::RenderTarget & renderer)
{
	renderer.draw(tileRec);
}

sf::RectangleShape BasicTiles::getTile()
{
	return tileRec;
}


