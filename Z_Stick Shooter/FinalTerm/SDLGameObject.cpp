#include "SDLGameObject.h"
#include"Game.h"	//헤더파일에 선언하면 서로 간의 헤더 선언으로 인한 충돌로 오류가 생긴다.
#include "PlayState.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
	: GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0.0f, 0.0f) //생성자
{
	m_x = pParams->getX();
	m_y = pParams->getY();
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_angle = pParams->getAngle();
	m_textureID = pParams->getTextureID();
	m_currentRow = 0;
	m_currentFrame = 0;

}
void SDLGameObject::origDraw() {
	TextureManager::Instance()->drawFrame
	(m_textureID,
		(int)m_position.getX(),
		(int)m_position.getY(),
		m_width,
		m_height,
		m_currentRow,
		m_currentFrame,
		m_angle,
		TheGame::Instance()->getRenderer());
}
void SDLGameObject::draw() {

	TextureManager::Instance()->drawFrame
	(m_textureID,
		(int)m_position.getX() - PlayState::Instance()->getCameraX(),
		(int)m_position.getY() - PlayState::Instance()->getCameraY(),
		m_width,
		m_height,
		m_currentRow,
		m_currentFrame,
		m_angle,
		TheGame::Instance()->getRenderer());
}
void SDLGameObject::getHIt() {
	hp -= 1;
}

void SDLGameObject::update() {
	

	m_velocity += m_acceleration;	//속도에 가속도를 합하여 새로운 속도 계산
	m_position += m_velocity;		//위치의 변경->좌표+속도(벡터)=벡터의 크기만큼 이동

}

void SDLGameObject::clean() {
	std::string id = m_textureID;
	TheTextureManager::Instance()->destroyTexture(id);
	TheTextureManager::Instance()->clearFromTextureMap(id);
}