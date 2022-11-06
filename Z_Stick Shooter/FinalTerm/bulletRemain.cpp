#include "bulletRemain.h"
#include "PlayState.h"
bulletRemain::bulletRemain(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{} //생성자
void bulletRemain::draw() {
	SDLGameObject::origDraw();
}
void bulletRemain::update() {
	m_currentRow = 12-PlayState::Instance()->getAmmo();

	SDLGameObject::update();
}