#include "CameraMachine.h"
#include "PlayState.h"

CameraMachine::CameraMachine(const LoaderParams* pParams) :SDLGameObject(pParams) {}

void CameraMachine::update() {
	//Vector2D vec =dynamic_cast<SDLGameObject*>(PlayState::Instance()->getObject(0))->getPosition();
//	m_position = vec;
//	m_velocity = (vec - m_position) / 15;
	SDLGameObject::update();
}