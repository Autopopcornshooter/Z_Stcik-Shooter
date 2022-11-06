#pragma once
#include "SDLGameObject.h"

class bulletRemain :public SDLGameObject {

public:
	bulletRemain(const LoaderParams* pParams);
	virtual void update();
	virtual void draw();
};

