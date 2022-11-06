#include "GameState.h"
#include "GameObject.h"
#include "SoundCard.h"

void GameState::update() {
	if (m_gameObjects.size() !=NULL) {
		for (int i = 0; i < m_gameObjects.size(); i++) {
			//printf("%d\n", i);

			m_gameObjects[i]->update();
		}
	}
	if (m_bullets.size() != NULL) {
		for (int i = 0; i < m_bullets.size(); i++) {
			//printf("%d\n", i);
			m_bullets[i]->update();
		}
	}
	if (m_enemies.size() != NULL) {
		for (int i = 0; i < m_enemies.size(); i++) {
			//printf("%d\n", i);
			m_enemies[i]->update();
		}
	}
}

void GameState::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		
		m_gameObjects[i]->draw();
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		//printf("%d\n", i);
		m_bullets[i]->draw();
	}
	for (int i = 0; i < m_enemies.size(); i++) {
		//printf("%d\n", i);
		m_enemies[i]->draw();
	}
}

bool GameState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	for (int i = 0; i < m_bullets.size(); i++) {
		//printf("%d\n", i);
		m_bullets[i]->clean();
	}
	for (int i = 0; i < m_enemies.size(); i++) {
		//printf("%d\n", i);
		m_enemies[i]->clean();
	}
	m_gameObjects.clear();	//오브젝트 삭제
	m_bullets.clear();
	m_enemies.clear();
	return true;
}