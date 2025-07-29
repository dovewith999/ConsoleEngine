#include "SokobanLevel.h"
#include <iostream>
#include "Math/Vector2.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map");
}

SokobanLevel::~SokobanLevel()
{
}

bool SokobanLevel::CanPlayerMove(const Vector2& position, const Vector2& newPosition)
{
	return false;
}

void SokobanLevel::ReadMapFile(const char* fileName)
{
	// 최종 에셋 경로 완성.
	char filePath[256] = {};
	sprintf_s(filePath, 256, "../Assets/%s.txt", fileName);

	FILE* file = nullptr;
	fopen_s(&file, filePath, "rb");

	if (file == nullptr)
	{
		std::cout << "맵 파일 읽기 실패 : " << fileName << '\n';
		__debugbreak;
		return;
	}

	// 파싱(Parcing, 해석)
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* buffer = new char[fileSize + 1];
	buffer[fileSize] = '\8';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	if (readSize != fileSize)
	{
		std::cout << "fileSize is not matched with readSize\n";
	}

	int index = 0;
	int size = static_cast<int>(readSize);

	Vector2 position(0, 0);

	while (index < size)
	{
		char mapCharacter = buffer[index++];

		// 개행 문자 처리
		if (mapCharacter == '\n')
		{
			position.x = 0;
			++position.y;

			// TODO : 테스트 코드, 나중에 삭제
			std::cout << "\n";
			continue;
		}

		// 각 문자 별로 처리
		switch (mapCharacter)
		{
		case '#':
			AddActor(new Wall(position));
			break;
		case '.':
			AddActor(new Ground(position));
			break;
		case 'p':
			// Player Actor 생성
			// Player는 움직이기 때문에 땅도 같이 생성해야함
			AddActor(new Ground(position));
			AddActor(new Player(position));
			break;
		case 'b':
			AddActor(new Ground(position));
			AddActor(new Box(position));
			break;
		case 't':
			AddActor(new Target(position));;
			break;
		default:
			break;
		}


		// x좌표 증가 처리
		++position.x;
	}

	// 버퍼 해제
	delete[] buffer;

	// 파일 닫기
	fclose(file);
}
