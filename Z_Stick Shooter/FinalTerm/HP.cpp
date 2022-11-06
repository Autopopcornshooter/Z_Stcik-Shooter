#include "HP.h"
#include "PlayState.h"
HP::HP(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{} //생성자
void HP::draw() {
	SDLGameObject::origDraw();
}
void HP::update() {
	m_currentRow=dynamic_cast<SDLGameObject*>(PlayState::Instance()->getObject(0))->getHP()-1;

	SDLGameObject::update();
}