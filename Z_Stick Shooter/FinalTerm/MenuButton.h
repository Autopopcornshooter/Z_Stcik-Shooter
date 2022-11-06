#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"

class LoaderParams;	//클래스 전방 선언
class MenuButton :public SDLGameObject {
public:
	MenuButton(const LoaderParams* pParams, void (*callback)());
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	bool m_bReleased;
	void(*m_callback)();	//클래스 콜백 함수-->함수 포인터

};

enum button_state {	//열거형 버튼상태 선언
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};