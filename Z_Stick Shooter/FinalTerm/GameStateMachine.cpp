#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState) {
	m_gameStates.push_back(pState);		//pState를 배열에 추가
	m_gameStates.back()->onEnter();
	printf("%d\n", m_gameStates.size());
}

void GameStateMachine::popState() {
	if (!m_gameStates.empty()) {
		if (m_gameStates.back()->onExit()) {
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeState(GameState* pState) {	//이전 state를 제거하고 다른 상태를 추가한다. 
	if (!m_gameStates.empty()) {//m_gameStates 배열이 비었는지 조사한다
			for (int i = 0; i < m_gameStates.size()-1; i++) {
				m_gameStates[i]->onExit();
				m_gameStates.erase(m_gameStates.begin());
			}
		if (m_gameStates.back()->getStateID() == pState->getStateID()) {
			//기존 state의 ID를 확인하여 인자로 받아온 ID와 동일한지 조사
			//기존 상태와 다른 상태가 동일한지 검사
			return;
			//동일하면 return
		}
		if (m_gameStates.back()->onExit()) {//back()--> 마지막 원소 참조--onExit() 실행
		//	GameStateMachine::shift();
			m_gameStates.push_back(pState);	//새로운 pState를 배열에 추가
			m_gameStates.back()->onEnter();	//새로운 상태 추가 후 onEnter호출
			delete m_gameStates.front();
			m_gameStates.erase(m_gameStates.begin());	//마지막 원소 제거
		}

	}
	else {
		m_gameStates.push_back(pState);	//새로운 pState를 배열에 추가
		m_gameStates.back()->onEnter();	//새로운 상태 추가 후 onEnter호출
	}
	
	printf("%d\n", m_gameStates.size());
	
}

void GameStateMachine::update() {	//배열이 비어있지 않다면 해당 state 의 update()반복 호출

	
	if (!m_gameStates.empty()) {
		m_gameStates.back()->update();
	}
}

void GameStateMachine::render() {	//배열이 비어있지 않다면 해당 state 의 render()반복 호출
	if (!m_gameStates.empty()) {
		m_gameStates.back()->render();
	}
}
/*
void GameStateMachine::shift() {
	GameState* temp;
	temp = m_gameStates.back();
	m_gameStates.back() = m_gameStates[m_gameStates.size() - 2];
	m_gameStates[m_gameStates.size() - 2] = temp;
}*/