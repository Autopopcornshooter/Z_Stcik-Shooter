#pragma once
#include "SDLGameObject.h"



class Floor :public SDLGameObject {
public:
	Floor(const LoaderParams* pParams);

private:
}; 
Floor::Floor(const LoaderParams* pParams) :SDLGameObject(pParams) {}

