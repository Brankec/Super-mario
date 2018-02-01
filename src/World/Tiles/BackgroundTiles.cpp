#include "BackgroundTiles.h"
#include <string>

BackgroundTiles::BackgroundTiles(int TilePositionX, int TilePositionY, sf::Texture& tileTexture, sf::Vector2f tileIndex)
{
	tileRec.setSize({ 64,64 });
	tileRec.setPosition(TilePositionX, TilePositionY);

	tileTextureSize.x = 16;
	tileTextureSize.y = 16;

	tileRec.setTexture(&tileTexture);
	setTileTexture(tileIndex);
}

void BackgroundTiles::setTileTexture(sf::Vector2f tileIndex) //the index is the actual tile texture position.
{
	tileRec.setTextureRect(sf::IntRect(tileIndex.x, tileIndex.y, tileTextureSize.x, tileTextureSize.y));
}

void BackgroundTiles::setTilePosition(sf::Vector2f tPosition)
{
	tileRec.setPosition(tPosition);
}

void BackgroundTiles::drawTile(sf::RenderTarget & renderer)
{
	if ((tileRec.getPosition().x + 64 + tileRec.getSize().x / 2) >= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2) && //draws only within our view on X axis
		(tileRec.getPosition().x - tileRec.getSize().x / 2) <= (Camera::getView().getCenter().x + Camera::getView().getSize().x / 2))
	{
		renderer.draw(tileRec);
	}
}


