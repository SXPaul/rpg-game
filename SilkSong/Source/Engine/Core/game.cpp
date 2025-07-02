#include"CoreMinimal.h"
#include"World.h"
#include"Objects/Level.h"

#include"Tools/ResourceManager.h"
#include"Tools/CollisionManager.h"
#include"Tools/LevelManager.h"

#include"GameplayStatics.h"

#include <easyx.h>
#include <windows.h>
#pragma comment(lib,"winmm.lib")

#include <thread>
#include <immintrin.h>


extern int WIN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
extern int WIN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);



/*----------------------------------
			    ����
  ----------------------------------*/
class Engine
{
public:
	static void Init()
	{
		WIN_WIDTH = 900, WIN_HEIGHT = 600;
		initgraph(WIN_WIDTH, WIN_HEIGHT);
		
		SetWindowLong(GetHWnd(), GWL_STYLE, WS_POPUP);
		SetWindowPos(GetHWnd(), HWND_TOP, 0, 0, WIN_WIDTH, WIN_HEIGHT, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		MoveWindow(GetHWnd(), (GetSystemMetrics(SM_CXSCREEN) - WIN_WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - WIN_HEIGHT) / 2,
			WIN_WIDTH, WIN_HEIGHT, FALSE);
		/*setaspectratio(float(WIN_WIDTH) / 1200, float(WIN_HEIGHT) / 800);*/
		 
		//ϵͳDebug���Ʋ���
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL);
		setfillcolor(LIGHTBLUE);
		setlinecolor(BLACK);
		
		//ϵͳ���ֲ���
		setbkmode(TRANSPARENT);
		settextstyle(25, 10, "Arial");
		settextcolor(WHITE);
	
		BeginBatchDraw();


		//��ʼ����Դ������
		mainWorld.resourcePool = new ResourceManager;
		mainWorld.resourcePool->Initialize();
		

		//��ʼ����ײ������
		mainWorld.collisionManager = new CollisionManager;
		mainWorld.collisionManager->Initialize();
		

		//��ʼ����Ϸ����
		mainWorld.levelManager = new LevelManager;
		mainWorld.levelManager->Initialize();
		mainWorld.FPSClock = new Timer;
		mainWorld.OverallClock = new Timer;
	}

	static void Tick(float deltaTime)//֡����
	{
		mainWorld.deltaTime = 0;
		mainWorld.Update(deltaTime);
		mainWorld.Render();
	}

	static void Tick_()//��Ƶ����
	{
		{
			std::lock_guard<std::mutex> lock(mainWorld.updateMutex);
			mainWorld.Input(); 
		}
		mainWorld.Update_();
	}

	static void Run()
	{
		double lastTime = 0;
		while (true)
		{
			lastTime = GameplayStatics::GetTimeSeconds();
			Engine::Tick(mainWorld.deltaTime);
			if (bFrameLimitOn)
			{
				double interval = double(1) / double(MaxFrame) - (GameplayStatics::GetTimeSeconds() - lastTime) - 0.001;
				if (interval > 0)std::this_thread::sleep_for(duration<double>(interval));
			}
			else _mm_pause();
			mainWorld.deltaTime += float(GameplayStatics::GetTimeSeconds() - lastTime);
		}
	}

	static void Exit()
	{
		delete mainWorld.gameInstance; 
	}
};



void CALLBACK timecallback(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR)
{
	Engine::Tick_();
}

#ifdef _DEBUG

int main()
{
	Engine::Init();
	timeSetEvent(1, 0, timecallback,0, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);
	Engine::Run();
	Sleep(INFINITE);
	return 0;
}

#endif



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Engine::Init();
	timeSetEvent(1, 0, timecallback, 0, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);
	Engine::Run();
	Sleep(INFINITE);
	return 0;
}