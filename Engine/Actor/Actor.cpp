#include "Actor.h"
#include <Windows.h>
#include <iostream>

Actor::Actor(const char image, Color color)
	: image(image), color(color)
{
}

Actor::~Actor()
{
}

void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

void Actor::Tick(float deltaTime)
{
}

void Actor::Render()
{
	// Win32 API.
	// 커서 위치 이동

	//콘솔 출력 제어를 위한 핸들 가져오기
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	//커서 포지션 이동
	COORD coord;
	coord.X = static_cast<short>(position.x);
	coord.Y = static_cast<short>(position.y);

	SetConsoleCursorPosition(handle, coord);
	
	SetConsoleTextAttribute(handle, static_cast<WORD>(color));

	//그리기
	std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
#pragma region 꼼수
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	//커서 포지션 이동
	COORD coord;
	coord.X = static_cast<short>(position.x);
	coord.Y = static_cast<short>(position.y);

	SetConsoleCursorPosition(handle, coord);
	std::cout << ' ';
#pragma endregion

	position = newPosition;
}

Vector2 Actor::GetPosition() const
{
	return position;
}
