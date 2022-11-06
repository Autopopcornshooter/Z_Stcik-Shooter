#pragma once
#include "SDL.h"
#include <string>	
#include <map>		//표준 라이브러리 헤더파일--> std::를 붙이고 사용한다.
//#include "Singleton.h"



class TextureManager {
	//public:
private:		//클래스 외부에서 생성자 호출 불가능--> 외부에서 객체 생성 불가능
	TextureManager() {}	    //생성자
	
	std::map <std::string, SDL_Texture*> m_textureMap; //std::string이 키, SDL_Texture가 값(value)	m_textureMap은 TextureManager.cpp를 넘지 않는 지역변수이다.
	//m_textureMap을 배열처럼 호출,사용한다.
	static TextureManager* s_pInstance;	//s_pInstance(정적 멤버변수) 선언
	// Instance() 호출 이전까지 s_pInstance에는 아무것도 할당되지 않고 반환도 하지 않는다


public:
	~TextureManager() {}	//소멸자
	bool load
	(std::string fileName,
		std::string id,
		SDL_Renderer* pRenderer);	//파일 이름, 객체 ID, 렌더러 선언(지역 변수)
	void draw(std::string id,
		int x,
		int y,
		int width,
		int height,
		int currentRow,
		int currentFrame,
		double angle,
		SDL_Renderer* pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawCamera(std::string id,
		int x,
		int y,
		int width,
		int height,
		int camposX,
		int camposY,
		double angle,
		SDL_Renderer* pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id,
		int x,
		int y,
		int width,
		int height,
		int currentRow,
		int currentFrame,
		double angle,
		SDL_Renderer* pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	//currentRow(나타낼 시트의 줄),currentFrame(나타낼 프레임)
	//pRenderer와 flip은 draw, drawFrame 메소드 내에서만 사용되는 변수

	bool check(std::string id);

	void destroyTexture(std::string id) {
		SDL_DestroyTexture(m_textureMap[id]);
	}
	void clearFromTextureMap(std::string id) {
		m_textureMap.erase(id);
	}

	static TextureManager* Instance() {	//호출 시에 s_pInstance에 TextureManager 클래스를 할당하며 또한 반환하여 코드 내부의 함수들이 실행될 수 있게 한다.
		if (s_pInstance == 0) {
			s_pInstance = new TextureManager();
		}
		return s_pInstance;
	}
};
typedef TextureManager TheTextureManager;
