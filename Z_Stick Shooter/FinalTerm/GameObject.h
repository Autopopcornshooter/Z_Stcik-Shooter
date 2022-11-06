
#pragma once
#include <SDL.h>
#include <string>
#include "LoaderParams.h"

//#include "TextureManager.h"
//#include "InputHandler.h"


class GameObject {									// 최상위 클래스가 될 것
public:
	virtual void origDraw() = 0;  //순수가상함수로 선언!
	virtual void draw() = 0;  //순수가상함수로 선언!
	virtual void update() = 0;
	virtual void clean() = 0;

protected:
	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}
	std::string m_textureID;
	int status = 0;
	int m_currentFrame = 0;
	int m_currentRow = 0;
	int m_x = 0;
	int m_y = 0;
	int m_width = 0;
	int m_height = 0;
};
