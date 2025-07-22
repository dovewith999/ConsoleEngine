#pragma once
#include "Core.h"
#include <Windows.h>

class Engine_API Engine
{
public:
	// 생성자, 소멸자
	Engine();
	~Engine();
	
public:
	// 엔진 실행함수
	void Run();

	// 엔진 종료함수
	void Quit();

private: /*Function*/
	void ProcessInput();
	void Update(float deltaTime = 0.0f);
	void Render();

private:
	bool isQuit = false;
};