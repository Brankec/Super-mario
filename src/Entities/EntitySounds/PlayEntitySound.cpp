#include "PlayEntitySound.h"



PlayEntitySound::PlayEntitySound()
{

}

void PlayEntitySound::playSound(int volume)
{
	entitySound.emplace_back(soundBuffer, volume);
}

void PlayEntitySound::update()
{
	isSoundOver();
}

void PlayEntitySound::isSoundOver()
{
	for (int i = 0; i < entitySound.size(); i++)
	{
		if (entitySound[i].isSoundStop())
		{
			//entitySound.erase(entitySound.begin() + i);  //for some reason this interrupts the jump sound when I jump again before this one finished
		}
	}
}

