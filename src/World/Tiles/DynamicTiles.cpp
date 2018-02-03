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

	playAnimation = true;
	firstPositionY = tileRec.getPosition().y;//for determing how far should it go up nefore going down when hit
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

void DynamicTiles::Collision(Player & entity)
{
	if (doesCollide)
	{
		CheckForGround(tileRec, entity);
		HitBrickUnderPlayer(tileRec, entity, isTileHit);
	}
}

void DynamicTiles::drawTile(sf::RenderTarget & renderer)
{
	if ((tileRec.getPosition().x + 64 + tileRec.getSize().x / 2) >= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2) && //draws only within our view on X axis
		(tileRec.getPosition().x - tileRec.getSize().x / 2) <= (Camera::getView().getCenter().x + Camera::getView().getSize().x / 2))
	{
		renderer.draw(tileRec);
	}
}

void DynamicTiles::jumpTile()
{
	animationPositionY = tileRec.getPosition().y;

	if (playAnimation)
	{
		if (animationPositionY < firstPositionY - 20)
		{
			brickNudge.playSound(30);
			playAnimation = false;
		}
		animationPositionY--;
	}
	else
	{
		if (animationPositionY > firstPositionY - 1)
		{
			isTileHit = false;
			playAnimation = true;
		}

		if(isTileHit)
		animationPositionY++;
	}
	tileRec.setPosition(tileRec.getPosition().x, animationPositionY);
}

sf::RectangleShape DynamicTiles::getTile()
{
	return tileRec;
}


