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

void BasicTiles::Collision(sf::FloatRect entity, bool* isColliding)
{
	if (doesCollide)
	{
		//CheckForGround(tileRec, entity, isColliding);
		Collide(tileRec, entity, isColliding);
	}
}

void BasicTiles::drawTile(sf::RenderTarget & renderer)
{

	if ((tileRec.getPosition().x + 64 + tileRec.getSize().x / 2) >= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2) && //draws only within our view on X axis
		(tileRec.getPosition().x - tileRec.getSize().x / 2) <= (Camera::getView().getCenter().x + Camera::getView().getSize().x / 2))
	{
		renderer.draw(tileRec);
	}
}

sf::RectangleShape BasicTiles::getTile()
{
	return tileRec;
}


