#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include <string>	
//#include <map>		//표준 라이브러리 헤더파일--> std::를 붙이고 사용한다.	map은 선언을 한 해당 파일에서만 필요함, 다른데서 선언할 필요가없다.

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {			//모든 텍스처들을 가지고 있다.
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());		//c_str()--> 자료형 string을 char* 형으로 바꾸어준다 -->map사용
	if (pTempSurface == 0) {
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) {

		if (m_textureMap[id] == NULL) {
			m_textureMap[id] = pTexture;	//m_textureMap[id]= pTexture로 초기화
			return true;
		}
		else
		{
			return true;
		}


	}

	return false;
}

bool TextureManager::check(std::string id) {
	return 0;
}


void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,double angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;	//원본상자
	SDL_Rect destRect;	//대상상자
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}
void TextureManager::drawCamera(std::string id, int x, int y, int width, int height, int camposX,
	int camposY, double angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;	//원본상자
	SDL_Rect destRect;	//대상상자
	srcRect.x = camposX;
	srcRect.y = camposY;
	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}