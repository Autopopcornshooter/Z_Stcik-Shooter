#pragma once
#pragma once
#include "GameState.h"
#include "SDLGameObject.h"
#include "Game.h"
#include "Bullet.h"
#include "Vector2D.h"
class Vector2D;
class Bullet;
class GameObject;


class PlayState : public GameState {
public:
	
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	int getbottom() { return bottom; }
	void shoot(int i);
	void floorCheck(SDLGameObject* p1);
	float angleCal(SDLGameObject* p1, SDLGameObject* p2);
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	virtual std::string getStateID() const { return s_playID; }
	GameObject* getObject(int i) { return m_gameObjects[i]; }
	GameObject* getE(int i) { return m_enemies[i]; }
	int getESize() { return m_enemies.size(); }
	GameObject* getB(int i) { return m_bullets[i]; }
	int getBSize() { return m_bullets.size(); }
	int calPositionX(SDLGameObject* p1);
	int calPositionY(SDLGameObject* p1);
	int getCameraX() { return cameraX; }
	int getCameraY() { return cameraY; }
	int getAmmo() { return ammo; }
	int cameraX;
	int cameraY;
	SDLGameObject* SDLObj(GameObject* p1) { return dynamic_cast<SDLGameObject*>(p1); }
	void spawnZombie();
	void spawnJZombie();
	void spawnPZombie();
	
	static PlayState* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new PlayState();
			return s_pInstance;
		}
		return s_pInstance;
	}
	void popBullets(int i);
	void popEnemies(int i);
	void reload();
	
	int bottom = bg_Height-48;

	
private:
	PlayState() {}
	bool spawnState1=true;
	bool spawnState2=true;
	bool spawnState3=true;
	const int fullAmmo = 12;
	int fillAmmo;
	int finishFill=120;
	int ammo=12;
	int shootTime;
	int shootDelay=15;
	int time1;
	int time2;
	int time3;
	int delayTime1;
	int delayTime2;
	int delayTime3;
	static PlayState* s_pInstance;
	
	bool fireState = false;
	static const std::string s_playID;
};