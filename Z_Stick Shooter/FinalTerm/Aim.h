#pragma once
#include "SDLGameObject.h"



class Aim :public SDLGameObject {
public:
	Aim(const LoaderParams* pParams);
	virtual void update();
	virtual void draw();
	virtual void clean();

private:



};