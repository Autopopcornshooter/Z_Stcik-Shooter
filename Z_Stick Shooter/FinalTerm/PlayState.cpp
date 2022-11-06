#include "PlayState.h"
#include "PauseState.h"
#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Block.h"
#include "Aim.h"
#include "InputHandler.h"
#include "CameraMachine.h"
#include "Floor.h"
#include "Enemy.h"
#include <time.h>
#include <stdlib.h>
#include "SDL_mixer.h"
#include "GameOverState.h"
#include "HP.h"
#include "bulletRemain.h"
#include "SoundCard.h"
#include <iostream>



const std::string PlayState::s_playID = "PLAY";
PlayState* PlayState::s_pInstance = NULL;

Bullet* bullet;
void PlayState::update() {
	SDL_ShowCursor(SDL_DISABLE);

	if (TheInputHandler::Instance()->getMousePosition()->getX() > calPositionX(SDLObj(m_gameObjects[0])) + SDLObj(m_gameObjects[0])->getWidth() / 2) {
		SDLObj(m_gameObjects[0])->direction = 1;
	}
	else
		SDLObj(m_gameObjects[0])->direction = 0;

	cameraX = SDLObj(m_gameObjects[0])->getPosition().getX() + (SDLObj(m_gameObjects[0])->getWidth() / 2) - (screenWidth / 2);
	cameraY = SDLObj(m_gameObjects[0])->getPosition().getY() + (SDLObj(m_gameObjects[0])->getHeight() / 2) - (2 * screenHeight / 3);
	if (cameraX < 0)
		cameraX = 0;
	if (cameraY < 0)
		cameraY = 0;
	if (cameraX > bg_Width - screenWidth)
		cameraX = bg_Width - screenWidth;
	if (cameraY > bg_Height - screenHeight)
		cameraY = bg_Height - screenHeight;


	if (spawnState1 == false) {
		spawnZombie();
		spawnState1 = true;
	}
	else {
		delayTime1 = 200;
		time1++;
		if (time1 >= delayTime1) {
			spawnState1 = false;
			time1 = 0;
		}
	}

	if (spawnState2 == false) {
		spawnJZombie();
		spawnState2 = true;
	}
	else {
		delayTime2 = 700;
		time2++;
		if (time2 >= delayTime2) {
			spawnState2 = false;
			time2 = 0;
		}
	}

	if (spawnState3 == false) {
		SoundCard::Instance()->PzomRoarSound(0);
		spawnPZombie();
		spawnState3 = true;
	}
	else {
		delayTime3 = 1500;
		time3++;
		if (time3 >= delayTime3) {
			spawnState3 = false;
			time3 = 0;
		}
	}
	
	for (int i = 0; i < m_enemies.size(); i++) {
		for (int j = 0; j < m_bullets.size(); j++) {
			if (checkCollision(SDLObj(m_enemies[i]), SDLObj(m_bullets[j]))) {
				if (SDLObj(m_enemies[i])->getHP() > 0) {
					popBullets(j);
					SDLObj(m_enemies[i])->getHIt();
				}
			}
		
		}
		if (checkCollision(SDLObj(m_enemies[i]), SDLObj(m_gameObjects[0]))) {
			if (SDLObj(m_gameObjects[0])->getHP() > 0&&SDLObj(m_enemies[i])->getHP()>0) {
				popEnemies(i);
				SDLObj(m_gameObjects[0])->getHIt();
			}
			if (SDLObj(m_gameObjects[0])->getHP() == 0) {
				TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
			}
		}
		else if (SDLObj(m_enemies[i])->getDeathTime()>500) {
			popEnemies(i);
		}
	}
	

	for (int i = 0; i < m_bullets.size(); i++) {
		if (calPositionX(SDLObj(m_bullets[i])) < -getCameraX() ||
			calPositionX(SDLObj(m_bullets[i])) > bg_Width - getCameraX() ||
			calPositionY(SDLObj(m_bullets[i])) < -getCameraY() ||
			calPositionY(SDLObj(m_bullets[i])) > bg_Height - getCameraY()) {
			popBullets(i);
		}
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}
	if (ammo > 0) {
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
			if (fireState == false) {
				shoot(0);
				ammo -= 1;
				fireState = true;
			}
			shootTime++;
		}
		else {
			shootTime++;
			if (shootTime > shootDelay) {
				shootTime = 0;
				fireState = false;
			}

		}
	}
	if(ammo==0){
		reload();
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R))
		ammo = 0;

	GameState::update();

}

int PlayState::calPositionX(SDLGameObject* p1) {
	return p1->getPosition().getX() - cameraX;
}

int PlayState::calPositionY(SDLGameObject* p1) {
	return p1->getPosition().getY() - cameraY;
}

void PlayState::render() {
	TheTextureManager::Instance()->drawCamera("bg",
		0,
		0,
		screenWidth,
		screenHeight,
		cameraX,
		cameraY,
		0,
		TheGame::Instance()->getRenderer());


	GameState::render();
}

bool PlayState::onEnter() {
	SoundCard::Instance()->PplayingMusic();
	if (!TheTextureManager::Instance()->
		load("assets/Idle.png", "player", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/BG.png", "bg", TheGame::Instance()->getRenderer())) {
		return false;
	}

	if (!TheTextureManager::Instance()->
		load("assets/Aim.png", "aim", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/Jzombie.png", "jumpzombie", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/Pzombie2.png", "powerzombie", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/PzombieDie.png", "powerzombieDie", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/JzombieDie.png", "jumpzombieDie", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/ZombieDie.png", "zombieDie", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/Reloading.png", "reload", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/zombie.png", "zombie", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/heart.png", "life", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/bulletR.png", "bulletR", TheGame::Instance()->getRenderer())) {
		return false;
	}

	
	GameObject* life = new HP(new LoaderParams(10, 10, 90, 30, 0, "life"));
	GameObject* bulletR = new bulletRemain(new LoaderParams(10, 40, 96, 24, 0, "bulletR"));
	GameObject* player = new Player(new LoaderParams(200, 400, 40, 80, 0, "player"));
	//GameObject* block = new Block(new LoaderParams(0, 0, 50, 50, 0, "block"));
	GameObject* aim = new Aim(new LoaderParams(10, 300, 40, 40, 0, "aim"));
	GameObject* reload = new Block(new LoaderParams(-20, -20, 50, 15, 0, "reload"));


	m_gameObjects.push_back(player);//0
	m_gameObjects.push_back(aim);	//2
	m_gameObjects.push_back(reload);
	m_gameObjects.push_back(life);
	m_gameObjects.push_back(bulletR);
	SDLObj(m_gameObjects[0])->hp = 3;
	ammo = fullAmmo;
	std::cout << "entering PlayState\n";
	fireState = true;

	return true;
}

bool PlayState::onExit() {


	TheTextureManager::Instance()->clearFromTextureMap("player");
	TheTextureManager::Instance()->clearFromTextureMap("block");
	TheTextureManager::Instance()->clearFromTextureMap("bg");
	TheTextureManager::Instance()->clearFromTextureMap("zombie");
	TheTextureManager::Instance()->clearFromTextureMap("bullet");
	for (int i = 0; i < m_gameObjects.size(); i++) {
		delete dynamic_cast<SDLGameObject*>(m_gameObjects[i]);
		//m_gameObjects.erase(m_gameObjects.begin());
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		delete dynamic_cast<SDLGameObject*>(m_bullets[i]);
		//m_bullets.pop_back();
	}
	for (int i = 0; i < m_enemies.size(); i++) {
		delete dynamic_cast<SDLGameObject*>(m_enemies[i]);
		//m_enemies.pop_back();
	}
	m_gameObjects.clear();
	m_bullets.clear();
	m_enemies.clear();
	std::cout << "exiting PlayState\n";
	return GameState::onExit();
}

void PlayState::reload() {
	SDLObj(m_gameObjects[2])->m_position.setX(SDLObj(m_gameObjects[0])->getPosition().getX() - 5);
	SDLObj(m_gameObjects[2])->m_position.setY(SDLObj(m_gameObjects[0])->getPosition().getY() - 15);
	fireState = true;
	fillAmmo++;
	if (fillAmmo >=  finishFill) {
		ammo = fullAmmo;
		fireState = false;
		fillAmmo = 0;
		SDLObj(m_gameObjects[2])->m_position.setX(-20);
		SDLObj(m_gameObjects[2])->m_position.setY(-20);
	}
}

void PlayState::shoot(int i) {
	SoundCard::Instance()->shootSound(0);
	TheTextureManager::Instance()->load("assets/bullet.png", "bullet", TheGame::Instance()->getRenderer());
	bullet =
		new Bullet(new LoaderParams(SDLObj(m_gameObjects[0])->getPosition().getX() + 20, SDLObj(m_gameObjects[0])->getPosition().getY() + 27, 16, 12, 0, "bullet"));

	bullet->m_angle = PlayState::angleCal(bullet, NULL);
	bullet->m_velocity.setX(TheInputHandler::Instance()->getMousePosition()->getX() - calPositionX(SDLObj(bullet)));
	bullet->m_velocity.setY(TheInputHandler::Instance()->getMousePosition()->getY() - calPositionY(SDLObj(bullet)));
	bullet->m_velocity.normalize();
	bullet->m_velocity *= 10;
	m_bullets.push_back(bullet);
	printf("bullet fired\n");

}

float PlayState::angleCal(SDLGameObject* p1, SDLGameObject* p2) {
	if (p2 != NULL) {
		float radian = atan2(calPositionY(dynamic_cast<SDLGameObject*>(p2)) - calPositionY(dynamic_cast<SDLGameObject*>(p1)),
			calPositionX(dynamic_cast<SDLGameObject*>(p2)) - calPositionX(dynamic_cast<SDLGameObject*>(p1)));
		float degree = radian * 180 / M_PI;

		return degree;
	}
	else {
		float radian = atan2(TheInputHandler::Instance()->getMousePosition()->getY() - calPositionY(SDLObj(p1)),
			TheInputHandler::Instance()->getMousePosition()->getX() - calPositionX(SDLObj(p1)));
		float degree = radian * 180 / M_PI;

		return degree;
	}


}


bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2) {	//오브젝트간의 충돌체크
	int leftA, leftB, rightA, rightB;
	int topA, topB, bottomA, bottomB;
	/*
	leftA = p1->getPosition().getX();	//a의 왼쪽면
	rightA = p1->getPosition().getX() + p1->getWidth();	//a의 오른쪽면
	topA = p1->getPosition().getY();	//a의 윗면
	bottomA = p1->getPosition().getY() + p1->getHeight();//a의 아랫면

	leftB = p2->getPosition().getX();	//b의 왼쪽면
	rightB = p2->getPosition().getX() + p2->getWidth();	//b의 오른쪽면
	topB = p2->getPosition().getY();	//b의 윗면
	bottomB = p2->getPosition().getY() + p2->getHeight();//b의 아랫면
*/
	leftA = calPositionX(p1);	//a의 왼쪽면
	rightA = calPositionX(p1) + p1->getWidth();	//a의 오른쪽면
	topA = calPositionY(p1);	//a의 윗면
	bottomA = calPositionY(p1) + p1->getHeight();//a의 아랫면

	leftB = calPositionX(p2);	//b의 왼쪽면
	rightB = calPositionX(p2) + p2->getWidth();	//b의 오른쪽면
	topB = calPositionY(p2);	//b의 윗면
	bottomB = calPositionY(p2) + p2->getHeight();//b의 아랫면

	if (bottomA <= topB)
		return false;	//a의 아랫면이 b의 윗면보다 작거나 같음
	if (topA >= bottomB)
		return false;		//a의 윗면이 b의 아랫면보다 크거나 같음
	if (rightA <= leftB)
		return false;		//a의 오른쪽면이 b의 왼쪽면보다 작거나 같음
	if (leftA >= rightB)
		return false;		//a의 왼쪽면이 b의 오른쪽면보다 크거나 같음

	return true;
}

void PlayState::spawnZombie() {


	GameObject* zombie = new Enemy(new LoaderParams(0, 400, 40, 80, 0, "zombie"));
	dynamic_cast<SDLGameObject*>(zombie)->speed = 1.5f;
	dynamic_cast<SDLGameObject*>(zombie)->hp = 4;
	dynamic_cast<SDLGameObject*>(zombie)->m_currentRow = 2;
	dynamic_cast<SDLGameObject*>(zombie)->Type = 1;
	srand(time(NULL));
	dynamic_cast<SDLGameObject*>(zombie)->m_position.setX((bg_Width * (rand() % 2)));
	dynamic_cast<SDLGameObject*>(zombie)->m_position.setY(bottom - dynamic_cast<SDLGameObject*>(zombie)->getHeight());
	m_enemies.push_back(zombie);
	printf("zombie spawn\n");

}

void PlayState::spawnJZombie() {

	GameObject* Jzombie = new Enemy(new LoaderParams(0, 400, 40, 80, 0, "jumpzombie"));
	dynamic_cast<SDLGameObject*>(Jzombie)->speed = 4;
	dynamic_cast<SDLGameObject*>(Jzombie)->hp =5;
	dynamic_cast<SDLGameObject*>(Jzombie)->m_currentRow = 0;
	dynamic_cast<SDLGameObject*>(Jzombie)->Type = 2;
	srand(time(NULL));
	dynamic_cast<SDLGameObject*>(Jzombie)->m_position.setX((bg_Width * (rand() % 2)));
	dynamic_cast<SDLGameObject*>(Jzombie)->m_position.setY(bottom - dynamic_cast<SDLGameObject*>(Jzombie)->getHeight());
	m_enemies.push_back(Jzombie);
	printf("Jzombie spawn\n");

}

void PlayState::spawnPZombie() {

	GameObject* Pzombie = new Enemy(new LoaderParams(0, 400, 75, 60, 0, "powerzombie"));
	dynamic_cast<SDLGameObject*>(Pzombie)->speed = 3.5f;
	dynamic_cast<SDLGameObject*>(Pzombie)->hp = 8;
	dynamic_cast<SDLGameObject*>(Pzombie)->m_currentRow = 0;
	dynamic_cast<SDLGameObject*>(Pzombie)->Type = 3;
	srand(time(NULL));
	dynamic_cast<SDLGameObject*>(Pzombie)->m_position.setX((bg_Width * (rand() % 2)));
	dynamic_cast<SDLGameObject*>(Pzombie)->m_position.setY(bottom - dynamic_cast<SDLGameObject*>(Pzombie)->getHeight());
	m_enemies.push_back(Pzombie);
	printf("Pzombie spawn\n");
}

void PlayState::popBullets(int i) {
	for (i; i < m_bullets.size() - 1; i++) {
		GameObject* temp;
		temp = m_bullets[i];
		m_bullets[i] = m_bullets[i + 1];
		m_bullets[i + 1] = temp;
	}
	m_bullets.pop_back();
}

void PlayState::popEnemies(int i) {
	for (i; i < m_enemies.size() -1; i++) {
		GameObject* temp;
		temp = m_enemies[i];
		m_enemies[i] = m_enemies[i + 1];
		m_enemies[i + 1] = temp;
	}
	m_enemies.pop_back();
}

void PlayState::floorCheck(SDLGameObject* p1) {
	SDLObj(m_gameObjects[0])->floor = p1->getPosition().getY();
}