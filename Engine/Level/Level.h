#pragma once
#include "Core.h"
#include <vector> // 크기가 알아서 변경되는 동적 배열

class Actor;
class Engine_API Level
{
public:
	Level();
	virtual ~Level();

	// 레벨에 액터를 추가할 때 사용
	void AddActor(Actor* newActor);

	// 엔진 이벤트 함수
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

private:
	std::vector<Actor*> actors;
};

