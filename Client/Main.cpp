#include <iostream>
#include "Engine.h"
#include "Level/SokobanLevel.h"
#include "Game/Game.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game sokobanGame;
	sokobanGame.AddLevel(new SokobanLevel());
	sokobanGame.Run();

	return 0;
}