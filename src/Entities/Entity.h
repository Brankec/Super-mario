#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Entity
{
public:
	Entity();
	void loadTextureToRec(std::string textureName = "enemies");
	void loadTextureToSpr(std::string textureName = "placeholder");
	void loadAudioBuffer(std::string audioName = "placeholder");

public:
	sf::RectangleShape entityRec;
	sf::Texture entityTex;
	sf::Sprite entitySpr;

	float speedMAX = 0;
	float gravity = 0.3f;
	sf::Vector2f velocity = { 0, 0 };

protected:
	bool isDead = false;
};
