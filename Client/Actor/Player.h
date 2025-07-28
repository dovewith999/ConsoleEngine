#pragma once
#include "Actor/Actor.h"

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(const Vector2& position);
	virtual ~Player();

public:
	virtual void Tick(float deltaTime) override;
	
};