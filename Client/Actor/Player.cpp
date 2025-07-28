#include "Player.h"
#include "Engine.h"

Player::Player(const Vector2& position)
	: super('P', Color::Red, position)
{
	SetSortingOrder(3);
}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 입력처리
	if (Engine::GetInstance().GetKeyDown(VK_ESCAPE))
	{
		Engine::GetInstance().Quit();
		return;
	}
	if (Engine::GetInstance().GetKeyDown(VK_RIGHT))
	{
		Vector2 position = GetPosition();
		position.x += 1;
		SetPosition(position);
	}
	if (Engine::GetInstance().GetKeyDown(VK_LEFT))
	{
		Vector2 position = GetPosition();
		position.x -= 1;
		SetPosition(position);
	}
	if (Engine::GetInstance().GetKeyDown(VK_UP))
	{
		Vector2 position = GetPosition();
		position.y -= 1;
		SetPosition(position);
	}
	if (Engine::GetInstance().GetKeyDown(VK_DOWN))
	{
		Vector2 position = GetPosition();
		position.y += 1;
		SetPosition(position);
	}
}
