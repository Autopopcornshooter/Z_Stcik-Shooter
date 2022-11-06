#pragma once
#include "GameState.h"
#include <vector>
#include <iostream>
#include <string>

class GameStateMachine {
public:
	
	void changeState(GameState* pState);
	void pushState(GameState* pState);
	void popState();
	void update();
	void render();

	//void shift();
private:
	std::vector<GameState*>m_gameStates;
};