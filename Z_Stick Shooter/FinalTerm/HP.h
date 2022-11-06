#pragma once
#include "SDLGameObject.h"

class HP :public SDLGameObject {

public:
	HP(const LoaderParams* pParams);
	virtual void update();
	virtual void draw();
};
