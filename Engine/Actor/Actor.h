#pragma once
#include "Math/Vector2.h"
#include "RTTI.h"

// 물체가 뭘 해야할까? 를 정의
// 위치 점령. 
// 콘솔 창에 그리기(How? Whar?)
// 엔진의 이벤트 함수 호출
// BeginPlay/Tick/Draw

//색상
enum class Color 
{
	Blue		= 1,
	Green		= 2,
	Red			= 4,
	White		= Red | Green | Blue,
	Intensity	= 8,
};

class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(const char image = ' ', Color color = Color::White);
	virtual ~Actor();
	
public:
	// 이벤트 함수
	//객체 생애주기(LifeTime)에 1번만 호출됨(초기화 목적)
	virtual void BeginPlay();
	// 프레임마다 호출(반복성, 지속성이 필요한 작업)
	virtual void Tick(float deltaTime);
	//그리기 함수
	virtual void Render();

	FORCEINLINE const bool HasBeganPlay() const { return hasBeganPlay; }

public:/*Getter & Setter*/
	FORCEINLINE void SetPosition(const Vector2& newPosition);
	FORCEINLINE Vector2 GetPosition() const;

private:
	// 개체의 위치
	Vector2 position;
	// 그려질 이미지 값
	char image = ' ';

	// 텍스트 색상 값
	Color color = Color::White;

	//BeginPlay 호출이 되었는지 확인.
	bool hasBeganPlay = false;
};