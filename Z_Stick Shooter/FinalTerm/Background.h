#pragma once
#include"SDLGameObject.h"
#include "InputHandler.h"

class Background : public SDLGameObject {
public:
	Background(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
private:
};