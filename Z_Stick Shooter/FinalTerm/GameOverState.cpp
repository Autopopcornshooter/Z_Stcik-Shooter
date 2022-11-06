#include "GameObject.h"
#include "GameOverState.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "SoundCard.h"
#include "PlayState.h"
#include "AnimateGraphic.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";
GameOverState* GameOverState::s_pInstance = NULL;

void GameOverState::s_gameOverToMain() {
	TheGame::Instance()->getStateMachine()->changeState(new MenuState);
}

void GameOverState::s_restartPlay() {
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}
void GameOverState::update() {
	GameState::update();
}

void GameOverState::render() {
	GameState::render();
}

bool GameOverState::onEnter() {
	SoundCard::Instance()->PdeadMusic();
	SDL_ShowCursor(SDL_ENABLE);
	if (!TheTextureManager::Instance()->load("assets/gameover.png", "gameovertext", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/restart.png", "restartbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}

	GameObject* gameOverText = new AnimateGraphic(
		new LoaderParams(515, 100, 190, 30,0, "gameovertext"), 20);
	GameObject* button1 = new MenuButton(
		new LoaderParams(515, 200, 200, 80,0, "mainbutton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(
		new LoaderParams(515, 300, 200, 80,0, "restartbutton"), s_restartPlay);

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering GameOverState\n";
	return true;
}

bool GameOverState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();	//오브젝트 삭제
	TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
	std::cout << "exiting GameOverState\n";
	return true;

}