
#include "Game.h"
#include <iostream>
#include <windows.h>

Uint32 frameStart, frameTime;

Game* g_game = 0;

int main(int argc, char* argv[]) {

	int width = 1200;
	int height = 500;
	int xpos =300;
	int ypos =300;
	const int FPS = 60;	//프레임 60으로 설정(불변)
	const int DELAY_TIME = 1000.0f / FPS;		//DELAY_TIME은 프레임 하나당 렌더링 최소 지연 시간 계산 1초=1000밀리세컨드(불변)
	//int status = 0;



	if (TheGame::Instance()->init("Chapter 1", xpos, ypos, width, height, false)) {


		while (TheGame::Instance()->running()) {


			frameStart = SDL_GetTicks();	//loop 시작 시간 체크
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			frameTime = SDL_GetTicks() - frameStart;	///loop 끝난 시점에서 시작 시간 빼기-->loop시간 측정

			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));	//소요 시간이  DELAY_TIME보다 큰 경우 해당 차이만큼 Delay를 인위적으로 추가
			}
		}
	}
	else {
		std::cout << "game init failure" << SDL_GetError() << "\n";
		return-1;
	}
	TheGame::Instance()->clean();
	return 0;
}

