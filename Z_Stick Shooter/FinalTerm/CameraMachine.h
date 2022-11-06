#pragma once
#include "SDLGameObject.h"

class CameraMachine :public SDLGameObject {
public:
	CameraMachine(const LoaderParams* pParams);
	virtual void update();
	
};