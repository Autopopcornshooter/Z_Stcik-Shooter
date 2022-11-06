#include "PauseState.h"
#include "Game.h"
#include "MenuButton.h"
#include"MenuState.h"
#include "SoundCard.h"
#include <iostream>

const std::string PauseState::s_pauseID = "PAUSE";
PauseState* PauseState::s_pInstance = NULL;
void PauseState::update() {
	GameState::update();
}

void PauseState::render() {
	GameState::render();
}

void PauseState::s_pauseToMain() {
	TheGame::Instance()->
		getStateMachine()->changeState(new MenuState());
}
void PauseState::s_resumePlay() {
	TheGame::Instance()->getStateMachine()->popState();
}

bool PauseState::onEnter() {
	
	SDL_ShowCursor(SDL_ENABLE);
	if (!TheTextureManager::Instance()->
		load("assets/resume.png", "resumebutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->
		load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* button1 =
		new MenuButton(new LoaderParams(500, 100, 200, 80,0, "mainbutton"), s_pauseToMain);
	GameObject* button2 =
		new MenuButton(new LoaderParams(500, 300, 200, 80,0, "resumebutton"), s_resumePlay);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit() {
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
	std::cout << "exiting PauseState\n";
	return GameState::onExit();
}