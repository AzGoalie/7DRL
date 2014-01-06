#include "Game.h"

#include "IGameState.h"

#include <iostream>
#include <stdexcept>

Game* Game::pInstance = nullptr;
InputManager Game::InputManager;

Game::Game()
{
	m_pConsole = nullptr;
	m_pActiveState = nullptr;
	m_Running = false;
	m_Debug = false;
}

Game::~Game()
{
}

Game* Game::GetInstance()
{
	if (pInstance == nullptr)
		pInstance = new Game();
	return pInstance;
}

void Game::Init(const char* title, int width, int height)
{
	m_pConsole = new Console(title, width, height);
	if (!m_pConsole->Init("terminal.bmp"))
		throw std::runtime_error("Failed to initialize the console");

	m_Running = true;
}

void Game::Start()
{
	// Initalize and run game loop

	// Time and delta time
    // Time is the total time progressed, delta time is the
    // ammount of time inbetween each update
    float t = 0.0f;
    const float dt = 1.0f/100.0f;
    
    // Current time and accumulator
    // currentTime is the time since the main loop started, in seconds
    // accumulator is used to play "catch up" for updating
    float currentTime = GetTime();
    float accumulator = 0.0;
    
    // Other timing stuff
    int ups = 0;
    int fps = 0;
    double lastUpdateTime = 0;
    
    // Main game loop
    while (IsRunning()) {
        
        // Update
        float newTime = GetTime();
        float frameTime = newTime - currentTime;
        if ( frameTime > 0.25 )
            frameTime = 0.25;	  // note: max frame time to avoid spiral of death
        currentTime = newTime;
        
        accumulator += frameTime;
        
        while ( accumulator >= dt )
        {
            Update(dt);
            t += dt;
            accumulator -= dt;
            ups++;
        }
        
        // Render
		Render();
		fps++;

        if (currentTime-lastUpdateTime >= 1 && m_Debug) {
            std::cout << "Time: " << currentTime-lastUpdateTime << std::endl;
            std::cout << "FPS: " << fps << std::endl;
            std::cout << "UPS: " << ups << std::endl << std::endl;
            fps = ups = 0;
            lastUpdateTime = currentTime;
        }
    }
}

void Game::Update(float delta)
{
	// Poll Events
	InputManager.Update();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			Quit();
	}

	// Update IGameState
	m_pActiveState->Update(delta);
}

void Game::Render()
{
	// Clear Renderer
	m_pConsole->Clear();

	// Render IGameState
	m_pActiveState->Render();

	// Present Renderer
	m_pConsole->Present();
}

void Game::Shutdown()
{
	// If there are states, iteratate through and delete each state
    if (!m_States.empty()) {
        std::map<std::string, IGameState*>::iterator iter;
        for (iter = m_States.begin(); iter != m_States.end(); m_States.erase(iter++)) {
            if (iter->second != NULL) {
				iter->second->Shutdown();
                delete iter->second;
                iter->second = NULL;
            }
        }
    }

	// Shutdown managers, reverse order of Init()
	InputManager.Shutdown();


	if (m_pConsole != nullptr)
	{
		delete m_pConsole;
		m_pConsole = nullptr;
	}

	// ALWAY BE LAST 
	if (pInstance != nullptr)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void Game::AddState(std::string name, IGameState *state)
{
	state->Init(pInstance);
	m_States[name] = state;
	if (m_pActiveState == nullptr)
		m_pActiveState = state;
}

void Game::ChangeState(std::string state)
{
	if (!m_States.empty())
	{
		if (m_pActiveState != nullptr)
			m_pActiveState->Pause();
		if (m_States.find(state) != m_States.end())
		{
			m_pActiveState = m_States.find(state)->second;
			m_pActiveState->Resume();
		}
	}
}

float Game::GetTime()
{
	return SDL_GetTicks() * 0.001;
}