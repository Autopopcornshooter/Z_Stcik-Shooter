#include "Game.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);			//SDL 초기화
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);							//윈도우 생성
			if (m_pRenderer != 0) {
				SDL_SetRenderDrawColor(m_pRenderer, 0, 102, 132, 255);
			
		
				m_pGameStateMachine = new GameStateMachine();
				m_pGameStateMachine->changeState(MenuState::Instance());


			}
			else {
				return false;															//렌더러 생성 실패
			}
		}
		else {
			return false;																//윈도우 생성 실패
		}
	}
	else {
		return false;																	//SDL 초기화 실패
	}

	m_bRunning = true;
	return true;

}

void Game::render() {


	SDL_RenderClear(m_pRenderer);		//지정된 색으로 윈도우 지우기
	/*
	for (int i = 0; i != m_gameObjects.size(); i++) {

		m_gameObjects[i]->draw();
	}
	*/
	m_pGameStateMachine->render();





	SDL_RenderPresent(m_pRenderer);		//렌 더링 기능은 백 버퍼에서 작동하여 화면에 직접 표시되지 않는데, RenderPresent는 그것을 화면에 표시해 주는 기능을 한다(더블 버퍼링)



}

void Game::update() {
	//m_go.update();
	//m_player.update();
	/*
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}*/
	m_currentFrame = int((SDL_GetTicks() / 100) % 6);
	m_pGameStateMachine->update();


}

void Game::handleEvents() {

	TheInputHandler::Instance()->update();
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {	//RETURN은 키보드의 enter 
		m_pGameStateMachine->changeState(PlayState::Instance());
	}

}

void Game::clean() {
	TheInputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	SDL_Quit();
}

