#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}

	actors.clear();
}

void Level::AddActor(Actor* newActor)
{
	if (newActor == nullptr)
	{
		return;
	}

	//배열 맨 뒤에 새로운 항목을 추가하는 함수
	// emplace는 이동 - move 시멘틱
	// push_back은 참조 
	// 그래서 emplace_back이 성능이 더 좋음. 그러나 현재는 push_back도 발전해서 차이가 없음
	actors.emplace_back(newActor);
	//actors.push_back(newActor);
		
}

void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}


void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	for (Actor* const actor : actors)
	{
		actor->Render();
	}
}
