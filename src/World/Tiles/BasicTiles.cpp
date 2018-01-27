#include "BasicTiles.h"
#include <string>

BasicTiles::BasicTiles(int TilePositionX, int TilePositionY, sf::Texture& tileTexture, sf::Vector2f tileIndex)
{
	tileRec.setSize({ 16,16 });
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

sf::RectangleShape BasicTiles::getTile()
{
	return tileRec;
}
