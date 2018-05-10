#include "inputHandler.h"

InputHandler::InputHandler(DirectX::Keyboard* keyboard,
	DirectX::Mouse* mouse) {
	m_pKeyboard = keyboard;
	m_pMouse = mouse;
}

InputHandler::~InputHandler() {}
void InputHandler::Update() {
	m_pInputData = new InputData();
	auto kb = m_pKeyboard->GetState();
	auto ms = m_pMouse->GetState();
	
	if (kb.A || kb.Left) {
		m_pInputData->xAxis += 1;
	}
	if (kb.D || kb.Right) {
		m_pInputData->xAxis -= 1;
	}
	if (kb.W || kb.Up) {
		m_pInputData->yAxis += 1;
	}
	if (kb.S || kb.Down) {
		m_pInputData->yAxis -= 1;
	}
}
