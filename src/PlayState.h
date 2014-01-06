#include "IGameState.h"

class PlayState : public IGameState
{
private:
	Console *m_Console;

public:
	PlayState();
	~PlayState();

	void Init(Game *pGame);
	void Shutdown();

	void Pause();
	void Resume();

	void Update(float delta);
	void Render();

private:
	void DrawBorder();
};