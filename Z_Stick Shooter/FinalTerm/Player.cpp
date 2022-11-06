#include "Player.h"
#include "SoundCard.h"

Player::Player(const LoaderParams* pParams) :SDLGameObject(pParams) {}



void Player::update() {

	floor = PlayState::Instance()->getbottom();
	m_velocity.setX(0);

	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

		handleInput();
	
	SDLGameObject::update();
}
void Player::draw() {
	SDLGameObject::draw();
}
	
void Player::getHIt() {
	SoundCard::Instance()->playerHitSound(0);
	SDLGameObject::getHIt();
}
void Player::handleInput() {	
	if (!touchGround()) {
		m_acceleration.setY(0.5);
	}
	else {
		m_position.setY(floor - m_height);
		m_velocity.setY(0);
		m_acceleration.setY(0);
		m_jumpRemain = 2;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LSHIFT)) {
		currSpeed = maxSpeed;
	}
	if (TheInputHandler::Instance()->isKeyUp(SDL_SCANCODE_LSHIFT)) {
		currSpeed = normalSpeed;
	}
	
	if (m_position.getX() <4268-m_width) {
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
			m_velocity.setX(currSpeed);
			//printf("%d, %d\n", m_position.getX(), m_position.getY());
		}
	}
	if (m_position.getX() > 0) {
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
			m_velocity.setX(-currSpeed);
		}

	}
	if (TheInputHandler::Instance()->isKeyOneDown(SDL_SCANCODE_W)) {
		if (touchGround()||m_jumpRemain>0) {
			m_velocity.setY(-jumpForce);
			m_jumpRemain -= 1;
		}
	}	
	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) || TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
		if (direction == 1)
			m_currentRow = 2;
		if (direction == 0)
			m_currentRow = 3;
	}
	else {
		if (direction == 1)
			m_currentRow = 0;
		if (direction == 0)
			m_currentRow = 1;
	}
}

bool Player::touchGround() {
	if (m_position.getY() + m_height >= floor) {
		return  true;
	}
	else {
		return false;
	}
}
void Player::clean() {}
