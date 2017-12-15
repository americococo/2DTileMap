#include <Windows.h>
#include <time.h>
#include "GameSystem.h"

int WINAPI WinMain(HINSTANCE hInstance/*���� �ν��Ͻ� �ڵ�*/, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow/*��� ��������*/)
{
	srand(time(NULL));

	GameSystem::GetInstance()->InitSystem(hInstance, nCmdShow);

	return GameSystem::GetInstance()->Update();
}

//��ã��
//1�׷���
//2�� ����
//3-Ž��(queue)
//�˰��� ����
//p m													. d(1 ld(2  l(6   l(9 
//ť�� �Էµ� ��ġ�� �������� 8���� Ž�� (ť�� �Է�)		. p   l(3   lu(7  m(10  m ����)
//Ž���� Ÿ�� �� Ÿ�� ���								. u(5 lu(4  lu(8
// m ���� -> Ž���� Ÿ�� ������
//Ž�� �켱����(����ġ)�� Ÿ�� ����� �ٸ�

//statckoverflow
//http://jobs.gamasutra.com/
//https://www.gamedev.net/blogs/
//https://www.tigsource.com/