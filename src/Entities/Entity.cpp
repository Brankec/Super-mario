#include "Entity.h"
#include <iostream>


Entity::Entity()
{
	loadTextureToRec();
}

void Entity::loadTextureToRec(std::string textureName)
{
	if (entityTex.loadFromFile("res/entities/sprite/" + textureName + ".png"))
	{
		//entityRec.setTexture(&entityTex);
	}
}

void Entity::loadTextureToSpr(std::string textureName)
{
	if (entityTex.loadFromFile("res/entities/sprite/" + textureName + ".png"))
		entitySpr.setTexture(entityTex);
}

void Entity::loadAudioBuffer(std::string audioName)
{
}

