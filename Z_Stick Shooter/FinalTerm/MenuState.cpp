#include "MenuState.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "Background.h"
#include "SoundCard.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";	//ID 정의
MenuState* MenuState::s_pInstance = NULL;
void MenuState::update() {
	
	GameState::update();
}

void MenuState::render() {
	GameState::render();
}
void MenuState::s_menuToPlay() {
	std::cout << "Play button clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}

void MenuState::s_exitFromMenu() {
	std::cout << "Exit button clicked\n";
	TheGame::Instance()->quit();
}


bool MenuState::onEnter() {
	SDL_ShowCursor(SDL_ENABLE);
	SoundCard::Instance()->PmenuMusic();

	if (!TheTextureManager::Instance()->load("assets/button.png", "playbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/exit.png", "exitbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/MenuBg.png", "background", TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* backgroud = new Background(new LoaderParams(0, 0, 1200, 500, 0, "background"));
	GameObject* button1 = new MenuButton(new LoaderParams(400, 100, 400, 100,0, "playbutton"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(400, 300, 400, 100,0, "exitbutton"), s_exitFromMenu);

	m_gameObjects.push_back(backgroud);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit() {
	

	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

	std::cout << "exiting MenuState\n";
	return GameState::onExit();
}