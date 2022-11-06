#include "Enemy.h"
#include "PlayState.h"
#include <time.h>
#include <stdlib.h>
#include "SoundCard.h"
Enemy::Enemy(const LoaderParams* pParams) :SDLGameObject(pParams) {}

void Enemy::draw() {
	SDLGameObject::draw();
}
void Enemy::update() {
	floor = PlayState::Instance()->getbottom();
	if (hp != 0) {
		if (Type == 1) {
			m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
			NZombie();
		}
		else if (Type == 2) {

			JZombie();
		}
		else if (Type == 3) {
			m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
			PZombie();
		}
	}
	else {
		onDie();
	}
	SDLGameObject::update();
}

void Enemy::NZombie() {
	srand(time(NULL));

	if (getPosition().getX() > dynamic_cast<SDLGameObject*>(PlayState::Instance()->getObject(0))->getPosition().getX()) {
		m_currentRow = 3;
		m_velocity.setX(-speed);
	}
	else if (getPosition().getX() < dynamic_cast<SDLGameObject*>(PlayState::Instance()->getObject(0))->getPosition().getX()) {
		m_currentRow = 2;
		m_velocity.setX(speed);
	}
	else {
		m_currentRow = 1;
		m_velocity.setX(0);
	}


}
void Enemy::PZombie() {
	if (getPosition().getX() > dynamic_cast<SDLGameObject*>(PlayState::Instance()->getObject(0))->getPosition().getX()) {
		m_currentRow = 1;
		m_velocity.setX(-speed);
	}
	else if (getPosition().getX() < dynamic_cast<SDLGameObject*>(PlayState::Instance()->getObject(0))->getPosition().getX()) {
		m_currentRow = 0;
		m_velocity.setX(speed);
	}
	else {
		m_currentRow = 1;
		m_velocity.setX(0);
	}
}

void Enemy::JZombie() {

	if (!touchGround()) {
		m_currentFrame = 4;
		m_acceleration.setY(0.5);

	}
	else {
		m_position.setY(floor - m_height);
		m_velocity.setY(0);
		m_velocity.setX(0);
		m_acceleration.setY(0);
	}
	if (touchGround()) {
		m_currentFrame = timeGo / 30;

		if (jumpState == false) {
			m_velocity.setY(-jumpForce);
			if (getPosition().getX() > dynamic_cast<SDLGameObject*>(PlayState::Instance()->getObject(0))->getPosition().getX()) {
				m_currentRow = 1;
				m_velocity.setX(-speed);
			}
			else if (getPosition().getX() < dynamic_cast<SDLGameObject*>(PlayState::Instance()->getObject(0))->getPosition().getX()) {
				m_currentRow = 0;
				m_velocity.setX(speed);
			}
			else {

				m_velocity.setX(0);
			}
			jumpState = true;
		}
		else {
			timeGo++;

			if (timeGo > delayTime) {
				printf("jumpState==false");
				jumpState = false;
				timeGo = 0;
			}
		}
	}

}

void Enemy::getHIt() {
	srand(time(NULL));
	int choose = rand() % 6;
	if (choose < 2)
		SoundCard::Instance()->zHIt1Sound(0);
	else if (choose < 4)
		SoundCard::Instance()->zHIt2Sound(0);
	SDLGameObject::getHIt();

}

void Enemy::onDie() {
	deathTime++;
	if (Type == 1) {
		m_position.setY(floor - m_height);
		m_height = m_width = 32;
		m_textureID = "zombieDie";
	}
	else if (Type == 2) {
		m_position.setY(floor - m_height);
		m_textureID = "jumpzombieDie";
	}
	else if (Type == 3) {
		m_position.setY(floor - m_height);
		m_textureID = "powerzombieDie";
	}
	m_acceleration.setY(0.5);
	m_currentFrame = 0;
	m_currentRow = 0;
	m_velocity.setX(0);
	m_velocity.setY(0);
}


bool Enemy::touchGround() {
	if (m_position.getY() + m_height >= floor) {
		return  true;
	}
	else {
		return false;
	}
}
void Enemy::clean() {
	SDLGameObject::clean();
}