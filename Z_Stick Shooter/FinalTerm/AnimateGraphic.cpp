#include "AnimateGraphic.h"
//특정 속도로 애니메이션을 렌더링하는 클래스
AnimateGraphic::AnimateGraphic(const LoaderParams* pParams, int animSpeed) :
	SDLGameObject(pParams), m_animSpeed(animSpeed)
{} //생성자
void AnimateGraphic::draw() {
	SDLGameObject::origDraw();
}
void AnimateGraphic::update() {

	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % 2));
	SDLGameObject::update();
}