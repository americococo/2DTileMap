#include <Windows.h>
#include <time.h>
#include "GameSystem.h"

int WINAPI WinMain(HINSTANCE hInstance/*현재 인스턴스 핸들*/, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow/*어떻게 보여줄지*/)
{
	srand(time(NULL));

	GameSystem::GetInstance()->InitSystem(hInstance, nCmdShow);

	return GameSystem::GetInstance()->Update();
}

//길찾기
//1그래프
//2길 도출
//3-탐색(queue)
//알고리즘에 따라
//p m													. d(1 ld(2  l(6   l(9 
//큐에 입력된 위치를 기준으로 8방향 탐색 (큐에 입력)		. p   l(3   lu(7  m(10  m 도착)
//탐색된 타일 전 타일 기억								. u(5 lu(4  lu(8
// m 도착 -> 탐색된 타일 역추적
//탐색 우선순위(가중치)에 타라 결과가 다름

//statckoverflow
//http://jobs.gamasutra.com/
//https://www.gamedev.net/blogs/
//https://www.tigsource.com/