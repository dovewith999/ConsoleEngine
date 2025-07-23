#pragma once
#include "Actor/Actor.h"

class TestActor : public Actor
{
public:
	TestActor() = default;
	virtual ~TestActor() = default;

public:
	virtual void Tick(float deltaTime) override;
};

