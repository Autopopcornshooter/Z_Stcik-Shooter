#include "Bullet.h"
//#include "InputHandler.h"

Bullet::Bullet(const LoaderParams* pParams) :SDLGameObject(pParams) {}

void Bullet::draw() {
	SDLGameObject::draw();
}
void Bullet::update() {

	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
	SDLGameObject::update();
}
void Bullet::clean() {
	SDLGameObject::clean();
}