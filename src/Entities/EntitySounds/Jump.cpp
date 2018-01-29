#include "Jump.h"

Jump::Jump(std::string audioName)
{
	soundBuffer.loadFromFile("res/entities/audio/" + audioName + ".wav");
}
