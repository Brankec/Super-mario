#pragma once
#include <SFML/Graphics/Texture.hpp>

namespace res
{
	void loadResources();

	sf::Texture getPlayerTexture();
	sf::Texture getNPCTexture();
	sf::Texture getTilesTexture();

	static sf::Texture NPC, Player, Tiles;
}