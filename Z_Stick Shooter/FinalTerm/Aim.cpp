#include "Aim.h"
#include "InputHandler.h"

Aim::Aim(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Aim::draw() {
	SDLGameObject::origDraw();
}
void Aim::update() {
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_position.setX(vec->getX()-10);
	m_position.setY(vec->getY()-10);
	
	SDLGameObject::update();
}
void Aim::clean() {}

