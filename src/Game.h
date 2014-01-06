#pragma once

#include "Console.h"
#include "InputManager.h"

#include <map>
#include <string>


class IGameState;

class Game
{
protected:
	static Game* pInstance;	// Singleton instance

protected:
	std::map<std::string, IGameState*> m_States;
	IGameState* m_pActiveState;

	bool m_Running;
	bool m_Debug;	// Used for logging, could use #ifdef _DEBUG instead...

	Console *m_pConsole;

	Game(); // Keep this private/protected (singleton)
	~Game();

public:
	static InputManager InputManager;
	static Game* GetInstance();

	void Start();

	void Init(const char* title, int width, int height);
	void Shutdown();

	void Update(float delta);
	void Render();

	void AddState(std::string name, IGameState* state);
	void ChangeState(std::string name);
	IGameState* GetCurrentState() { return m_pActiveState; }

	float GetTime();

	void Quit() { m_Running = false; }
	bool IsRunning() { return m_Running; }

	bool IsDebug() { return m_Debug; }
	void SetDebug(bool debug) { m_Debug = debug; }

	Console* GetConsole() { return m_pConsole; }
};