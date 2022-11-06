#pragma once
#include "SDL.h"
#include "Game.h"
#include <vector>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler {
public:
	~InputHandler() {}
	static InputHandler* Instance() {		//레이지 인스턴스(싱글턴패턴) 적용
		if (s_pInstance == 0) {
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	bool isKeyDown(SDL_Scancode key);	//특정 키 눌렸는지 조사
	bool isKeyUp(SDL_Scancode key);
	bool isKeyOneDown(SDL_Scancode key);
	bool getMouseButtonState(int buttonNumber);


	void onMouseMove(SDL_Event event);
	void onMouseButtonDown(SDL_Event event);
	void onMouseButtonUp(SDL_Event event);

	void onKeyDown();
	void onKeyUp();
	Vector2D* getMousePosition();

	void update();		//SDL_PollEvent 함수를 이용하여입력장치 조사 및 상태 갱신
	void clean();
private:
	bool pushed;
	InputHandler();
	static InputHandler* s_pInstance;
	const Uint8* m_keystates;		//8비트의 부호 없는 정수형 배열
	std::vector<bool>m_mouseButtonStates;
	Vector2D* m_mousePosition;
protected:

};

typedef InputHandler TheInputHandler;