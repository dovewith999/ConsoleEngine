#include "Engine.h"
#include <iostream>
#include "Level/Level.h"
#include <Windows.h>
//#include <chrono>

// 2가지
// 윈도우즈.
// 단순입력처리(키보드)
// 타이머(시간계산)

Engine* Engine::instance = nullptr;

Engine::Engine()
{
	instance = this;


	// 콘솔 커서 끄기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	
	//모든 텍스트 색상 변경
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
}

Engine::~Engine()
{
	Free();
}

Engine& Engine::GetInstance()
{
	return *instance;
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
			BeginPlay();
			Tick(deltaTime); // deltaTime can be calculated based on frame time
			Render();

			// 시간 갱신
			previousTime = currentTime;

			// 현재 프레임의 입력을 기록
			for (int i = 0; i < MAX_KEY_NUMBER; ++i)
			{
				keyStates[i].previousKeyDown = keyStates[i].isKeyDown;
			}
		}
	}

	// Engine 정리
	// 텍스트 색상 원래대로 돌려놓기
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::AddLevel(Level* newLevel)
{
	if (newLevel == nullptr)
	{
		return;
	}

	// 기존에 있던 레벨 제거

	if (mainLevel != nullptr)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	mainLevel = newLevel;
}

bool Engine::GetKey(int keyCode) const
{
	return keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyDown(int keyCode) const
{
	return !keyStates[keyCode].previousKeyDown && keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyUp(int keyCode) const
{
	return keyStates[keyCode].previousKeyDown && !keyStates[keyCode].isKeyDown;
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// 키 입력 확인
	for (int i = 0; i < MAX_KEY_NUMBER; ++i)
	{
		keyStates[i].isKeyDown = GetAsyncKeyState(i) & 0x8000;
	}
}

void Engine::BeginPlay()
{
	if (mainLevel == nullptr)
	{
		return;
	}

	mainLevel->BeginPlay();
}

void Engine::Tick(float deltaTime)
{
	if (mainLevel == nullptr)
	{
		return;
	}

	//std::cout << "DeltaTime: " << deltaTime << " FPS: " << (1.0f / deltaTime) << '\n';
	
	// 알파벳은 소문자는 입력이 안됨. 그냥 대문자로 체크해야 함
	//if (GetKeyDown('A'))
	//{
	//	std::cout << "Key Down\n";
	//}
	//if (GetKey('A'))
	//{
	//	std::cout << "Key\n";
	//}
	//if (GetKeyUp('A'))
	//{
	//	std::cout << "Key Up\n";
	//}

	//레벨 업데이트
	mainLevel->Tick(deltaTime);

	//if (GetKeyDown(VK_ESCAPE))
	//{
	//	Quit();
	//}
}

void Engine::Render()
{
	if (mainLevel == nullptr)
	{
		return;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	mainLevel->Render();
}

void Engine::Free()
{
	if (mainLevel != nullptr)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
}