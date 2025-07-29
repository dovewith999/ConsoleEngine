#include "Game.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;
}

Game::~Game()
{
}

Game& Game::GetInstance() const
{
	return *instance;
}
