#include <iostream>
#include <stdexcept>

#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"

const char* TITLE = "Cowbows";
const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* argv[])
{
	Game* game = Game::GetInstance();
	game->SetDebug(true);

	try
	{
		game->Init(TITLE, WIDTH, HEIGHT);

#ifndef _DEBUG
		game->AddState("Menu", new MenuState);
#endif
		game->AddState("Play", new PlayState);

		game->Start();
	} catch (std::runtime_error &e)
	{
		std::cout << "FATLE ERROR: " << e.what() << std::endl;
	}

	game->Shutdown();

	return 0;
}