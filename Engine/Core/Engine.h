#pragma once
#include "Core.h"
#include "Input.h"
#include <Windows.h>

class Level;
class Engine_API Engine
{
public:
	// 생성자, 소멸자
	Engine();
	virtual ~Engine();

public:
	static Engine& GetInstance();
	
public:
	// 엔진 실행함수
	void Run();

	void AddLevel(Level* newLevel);

	void CleanUp();

	// 엔진 종료함수
	void Quit();

private: /*Function*/
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

protected:
	// 엔진 종료 플래그
	bool isQuit = false; 
	
	//메인 레벨
	Level* mainLevel = nullptr;

	// 입력 관리자
	Input input;

	static Engine* instance;
};