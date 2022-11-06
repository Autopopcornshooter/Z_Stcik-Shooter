#pragma once
#include "SDLGameObject.h"

class AnimateGraphic :public SDLGameObject {
	int m_animSpeed;

public:
	AnimateGraphic(const LoaderParams* pParams, int animSpeed);
	virtual void update();
	virtual void draw();
};