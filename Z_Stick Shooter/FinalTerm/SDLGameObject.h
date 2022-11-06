#pragma once
#include "GameObject.h"
#include "TextureManager.h"
//#include "InputHandler.h"
#include "Vector2D.h"
class SDLGameObject : public GameObject {
public:

	SDLGameObject(const LoaderParams* pParams);
	Vector2D m_velocity;
	Vector2D m_acceleration;
	Vector2D getPosition() const { return m_position; }	//위치반환메소드
	Vector2D m_position;	//Vector 값:변수 2개가 들어 있는 m_position-->(x,y) m_x,m_y의 역할 대신
	int getWidth()const { return m_width; }				//너비 반환메소드
	int getHeight()const { return m_height; }			//높이 반환메소드

	
	virtual void origDraw();
	virtual void draw();
	virtual void update();
	virtual void clean();
	int getHP() { return hp; }
	virtual void getHIt();
	int getDeathTime() { return deathTime; }
	Uint32 direction;
	int m_currentRow;
	int m_currentFrame;
	int m_angle;
	int floor;
	int hp;
	float speed;
	int Type;


	
protected:
	int deathTime = 0;
	
	int m_width;
	int m_height;
	
	
	std::string m_textureID;
};