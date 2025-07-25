#pragma once
#include "Core.h"
#include <Windows.h>

/*
* TODO : 2025/07/25 작업 목록
- Engine을 Singleton 구현
*/
const int MAX_KEY_NUMBER = 255;

class Level;
class Engine_API Engine
{
	/// <summary>
	/// 키입력 확인을 위한 구조체
	/// </summary>
	struct KeyState
	{
	public:
		bool isKeyDown = false;		  // 현재 프레임에 키가 눌렸는지 여부
		bool previousKeyDown = false; // 이전 프레임에 키가 눌렸는지 여부
	};

public:
	// 생성자, 소멸자
	Engine();
	~Engine();

public:
	static Engine& GetInstance();
	
public:
	// 엔진 실행함수
	void Run();

	void AddLevel(Level* newLevel);

	// 키 확인 함수
	FORCEINLINE bool GetKey(int keyCode) const;
	FORCEINLINE bool GetKeyDown(int keyCode) const;
	FORCEINLINE bool GetKeyUp(int keyCode) const;

	// 엔진 종료함수
	void Quit();

private: /*Function*/
	void ProcessInput();
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

	void Free();

private:
	bool isQuit = false; // 엔진 종료 플래그

	KeyState keyStates[MAX_KEY_NUMBER] = {}; // 키 입력 정보 관리 컨테이너
	//메인 레벨
	Level* mainLevel = nullptr;

	static Engine* instance;
};