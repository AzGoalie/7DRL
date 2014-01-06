#include "MenuState.h"
#include <iostream>

const float MenuState::DEFAULT_SCALE = 3;

MenuState::MenuState()
{
	m_playScale = DEFAULT_SCALE;
	m_quitScale = DEFAULT_SCALE;
	m_selected = 0;
	m_scaleFactor = 1;
}

MenuState::~MenuState()
{

}

void MenuState::Init(Game* pGame)
{
	m_pGame = pGame;
	m_pConsole = m_pGame->GetConsole();
}

void MenuState::Shutdown()
{

}

void MenuState::Pause()
{

}

void MenuState::Resume()
{

}

void MenuState::Update(float delta)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_DOWN])
		m_selected = 1;
	if (keys[SDL_SCANCODE_UP])
		m_selected = 0;

	if (keys[SDL_SCANCODE_RETURN])
	{
		if (m_selected == 0)
			m_pGame->ChangeState("Play");

		else
			m_pGame->Quit();
	}

	switch(m_selected)
	{
	case 0:
		m_playScale += m_scaleFactor * delta;
		m_quitScale = DEFAULT_SCALE;
		if (m_playScale > 4 || m_playScale < 3)
			m_scaleFactor = -m_scaleFactor;
		break;
	case 1:
		m_quitScale += m_scaleFactor * delta;
		m_playScale = DEFAULT_SCALE;
		if (m_quitScale > 4 || m_quitScale < 3)
			m_scaleFactor = -m_scaleFactor;
		break;
	}
}

void MenuState::Render()
{
	float pX = 407 - (m_pConsole->GetFont().GetStringWidth("Play!") * m_playScale)/2;
	float pY = 266 - (m_pConsole->GetFont().GetStringHeight("Play!") * m_playScale)/2;
	float qX = 410 - (m_pConsole->GetFont().GetStringWidth("Quit") * m_quitScale)/2;
	float qY = 330 - (m_pConsole->GetFont().GetStringHeight("Quit") * m_quitScale)/2;

	m_pConsole->DrawLine(400, 0, 400, 600);
	m_pConsole->DrawLine(0, 300, 800, 300);
	m_pConsole->DrawString(pX, pY, "Play!", m_playScale);
	m_pConsole->DrawString(qX, qY, "Quit", m_quitScale);
}