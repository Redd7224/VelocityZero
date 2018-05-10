#pragma once
#include "pch.h"
#include "inputData.h"

class InputHandler
{
public:
	InputHandler(DirectX::Keyboard* keyboard,
	DirectX::Mouse* mouse);
	~InputHandler();
	InputData* m_pInputData;
	void Update();
private:
	//std::unique_ptr<DirectX::Keyboard> m_pKeyboard;
	//std::unique_ptr<DirectX::Mouse> m_pMouse;
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Mouse* m_pMouse;

};
