#include "Background.h"
#include "Game.h"

Background::Background(const LoaderParams* pParams) :SDLGameObject(pParams) {}

void Background::draw() {
	SDLGameObject::origDraw();
}
void Background::update() {
	
	SDLGameObject::update();
}

