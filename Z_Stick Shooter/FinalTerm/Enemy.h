#pragma once
#include "SDLGameObject.h"

class Enemy :public SDLGameObject {
public:
	Enemy(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void onDie();
	void JZombie();
	void NZombie();
	void PZombie();
	virtual void getHIt();
	bool touchGround();
	
private:
	
	int jumpForce = 16;
	bool jumpState = false;
	int timeGo=0;
	int delayTime=120;
};