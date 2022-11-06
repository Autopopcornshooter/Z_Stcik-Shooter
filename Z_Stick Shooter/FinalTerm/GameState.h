#pragma once
#include"SDLGameObject.h"
#include <string>
#include <vector>
class GameObject;
class GameState {
public:
	
	virtual void update();
	virtual void render();		//Game 클래스에서 정의한 것과 유사
	virtual bool onEnter() = 0;
	virtual bool onExit();		//Game 클래스의 load, clean과 유사
	virtual std::string getStateID() const = 0;
	static const int screenWidth = 1200;
	static const int screenHeight = 500;
	static const int bg_Width = 4268;
	static const int bg_Height = 700;
protected:
	std::vector<GameObject*>m_bullets;
	std::vector<GameObject*>m_enemies;
	std::vector<GameObject*>m_gameObjects;	//GameState 단위 별로 GameObject 배열 관리

};

typedef GameState TheGameState;