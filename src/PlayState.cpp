#include "PlayState.h"

PlayState::PlayState()
{

}

PlayState::~PlayState()
{

}

void PlayState::Init(Game *pGame)
{
	m_pGame = pGame;
	m_Console = m_pGame->GetConsole();
}

void PlayState::Shutdown()
{

}

void PlayState::Pause()
{

}

void PlayState::Resume()
{
	m_Console->SetBackground(125, 125, 125);
}

void PlayState::Update(float delta)
{

}

void PlayState::Render()
{
	DrawBorder();

}

void PlayState::DrawBorder()
{
	// Top
	for (int x = 0; x < 50; x++)
		m_Console->DrawChar(x,0,219);
	// Sides
	for (int y = 0; y < 30; y++)
	{
		m_Console->DrawChar(0,y,219);
		m_Console->DrawChar(49,y,219);
	}
	// Bottom
	for (int x = 0; x < 50; x++)
		m_Console->DrawChar(x,30,219);
}