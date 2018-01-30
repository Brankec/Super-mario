#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "../World/Map.h"

#pragma once
class Entity
{
public:
	Entity();
	void loadTextureToRec(std::string textureName = "mario_small");
	void loadTextureToSpr(std::string textureName = "entities");
	void loadAudioBuffer(std::string audioName = "placeholder");

	sf::FloatRect getAABB();
	sf::Vector2f getPos();

public:
	sf::RectangleShape entityRec;
	sf::Texture entityTex;
	sf::Sprite entitySpr;

	float speedMAX = 0;
	float gravity = 0.6f;
	sf::Vector2f velocity = { 0, 0 };

	int Angle = 90;

	bool isColliding[4];//collision goes clock wise 0) is left, 1) is bottom, 2) is right, 3) is top

protected:
	int currentHealth = 10;
	int maxHealth = 10;
	float stamina = 100;
	bool isStaminaFull = true;
};
