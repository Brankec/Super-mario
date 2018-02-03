#include "PlayTileSound.h"



PlayTileSound::PlayTileSound()
{

}

void PlayTileSound::playSound(int volume)
{
	entitySound.emplace_back(soundBuffer, volume);
}

void PlayTileSound::update(float deltaTime)
{
	isSoundOver();
}

void PlayTileSound::isSoundOver()
{
	for (int i = 0; i < entitySound.size(); i++)
	{
		if (entitySound[i].isSoundStop())
		{
			//entitySound.erase(entitySound.begin() + i); //for some reason this interrupts the jump sound when I jump again before this one finished
		}
	}
}

