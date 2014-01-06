#pragma once

#include "IGameState.h"

class MenuState : public IGameState
{
private:
	static const float DEFAULT_SCALE;
	float m_scaleFactor;
	float m_playScale;
	float m_quitScale;
	int m_selected;
	Console *m_pConsole;

public:
	MenuState();
	~MenuState();

	void Init(Game *pGame);
	void Shutdown();

	void Pause();
	void Resume();

	void Update(float delta);
	void Render();
};