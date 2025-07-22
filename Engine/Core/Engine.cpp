#include "Engine.h"
#include <iostream>
//#include <chrono>

// 2가지
// 윈도우즈.
// 단순입력처리(키보드)
// 타이머(시간계산)

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	// 밀리 세컨드 단위로 시간을 알려줌
	// float currentTime = timeGetTime();

	LARGE_INTEGER currentTime;	// 현재 시간
	LARGE_INTEGER previousTime; // 이전 시간		
	QueryPerformanceCounter(&currentTime); // 현재 시간의 카운트
	previousTime = currentTime; // 이전 시간 초기화	

	// 하드웨어 시계의 정밀도(주파수) 가져오기
	// 나중에 초로 변환하기 위해
	LARGE_INTEGER frequency; // 카운트의 주파수
	QueryPerformanceFrequency(&frequency); // 카운트의 주파수	

	// 타겟 프레임 지정
	float targetFrameRate = 60.f;

	// 타겟 한 프레임 시간
	float oneFrameTime = 1.0f / targetFrameRate;

	while (!isQuit)
	{
		// 프레임 시간 계산
		// 현재 시간 - 이전 시간 / 주파수 = 초 단위의 시간.
		QueryPerformanceCounter(&currentTime);

		// 프레임 시간
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / static_cast<float>(frequency.QuadPart);

		ProcessInput();

		if (oneFrameTime <= deltaTime)
		{
			Update(deltaTime); // deltaTime can be calculated based on frame time
			Render();

			// 시간 갱신
			previousTime = currentTime;
		}
	}
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// ESC 키 입력 처리	
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		Quit();
	}
}

void Engine::Update(float deltaTime)
{
	std::cout << "DeltaTime: " << deltaTime << " FPS: " << (1.0f / deltaTime) << '\n';
}

void Engine::Render()
{
}