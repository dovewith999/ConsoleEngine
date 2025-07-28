#include "Player.h"

Player::Player(const Vector2& position)
	: super('P', Color::Red, position)
{
}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// TODO : 입력 처리 해야함
	
}
