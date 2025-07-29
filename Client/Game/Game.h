#pragma once
#include "Engine.h"
class Game : public Engine
{
public:
	Game();
	virtual ~Game();

public:
	FORCEINLINE Game& GetInstance() const;
private:
	static Game* instance;
};