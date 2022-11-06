#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "GameState.h"
#include "PlayState.h"
#include <vector>

class Player :public SDLGameObject{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void handleInput();
	bool touchGround();
	virtual void getHIt();

	PlayState* playState;
private:
	int currSpeed = 3;
	const int maxSpeed = 4;
	const int normalSpeed = 3;
	int m_jumpRemain;
	bool move=false;
	const int jumpForce = 8;
	int drawstate = 0;
	int jumpstate = 0;
	int idlestate = 1;
	int movingstate = 0;

};