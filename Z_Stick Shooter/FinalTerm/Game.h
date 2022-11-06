#pragma once
#include<vector>
#include "SDLGameObject.h"

class GameStateMachine;
class GameObject;
class Game {
public:


	~Game() {}
	bool init(const char*, int, int, int, int, int);
	void render();
	bool running() { return m_bRunning; }
	void handleEvents();
	void clean();
	void update();
	void quit(){ m_bRunning = false; }


	static Game* Instance() {			//싱글턴 패턴
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer()const { return m_pRenderer; }
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

private:
	Game() {}
	static Game* s_pInstance;		//정적 멤버변수

	//std::vector<GameObject*>m_gameObjects;		//GameObject*의 배열 선언
	int m_currentFrame;
	//TextureManager m_textureManager;	//TextureManager 헤더파일을 먼저 가져오지 않는다, 필요에 의해 호출 시 Game.cpp파일에서 직접 참조함

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer; //렌더러 선언
	bool m_bRunning;
	GameStateMachine* m_pGameStateMachine;

};
typedef Game TheGame;
