#pragma once

#include "Game.h"

class IGameState
{
protected:
	Game *m_pGame;

public:
	virtual ~IGameState() {}

	virtual void Init(Game *pGame) = 0;
	virtual void Shutdown() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
};