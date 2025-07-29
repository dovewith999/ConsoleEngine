#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();
	virtual ~SokobanLevel();

	virtual bool CanPlayerMove(const Vector2& position, const Vector2& newPosition) override;

private:
	void ReadMapFile(const char* fileName);
	bool CheckGameClear();

private:
	// 게임 관련 변수들
	int targetScore = 0;
	bool isGameClear = false;
};