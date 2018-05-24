#include "inputHandler.h"

InputHandler::InputHandler(DirectX::Keyboard* keyboard,
	DirectX::Mouse* mouse) {
	m_pKeyboard = keyboard;
	m_pMouse = mouse;
	m_pInputData = new InputData();
}

InputHandler::~InputHandler() {}
void InputHandler::Update() {
	m_pInputData->xAxis = 0;
	m_pInputData->yAxis = 0;
	m_pInputData->button4 = 0;
	auto kb = m_pKeyboard->GetState();
	//auto ms = m_pMouse->GetState();
	if (kb.Escape) {
		PostQuitMessage(0);
	}
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
	if (kb.L) {
		m_pInputData->button4 = 1;
	}
}
