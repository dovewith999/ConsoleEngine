#include "Engine.h"
#include <iostream>
#include "Level/Level.h"
#include <Windows.h>
#include "Utils/Utils.h"
#include "Input.h"

Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine의 메모리 해제.
		Engine::GetInstance().CleanUp();
		return false;
		break;
	default:
		break;
	}

	return false;;
}

Engine::Engine()
{
	instance = this;

	// 콘솔 커서 끄기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	// 콘솔 창 이벤트 등록
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);
}

Engine::~Engine()
{
	CleanUp();
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

		input.ProcessInput();

		if (oneFrameTime <= deltaTime)
		{
			BeginPlay();
			Tick(deltaTime); // deltaTime can be calculated based on frame time
			Render();

			// 시간 갱신
			previousTime = currentTime;

			input.SavePreviouseKeyStates();
		}
	}

	// Engine 정리
	// 텍스트 색상 원래대로 돌려놓기
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); // 흰 색으로 설정
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

void Engine::Quit()
{
	isQuit = true;
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

	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	mainLevel->Render();
}

void Engine::CleanUp()
{
	SafeDelete(mainLevel);
}