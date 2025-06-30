#include "ResourceManager.h"
#include <easyx.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")


//************************************************
//*********       �û���༭����          **********

void ResourceManager::Initialize()
{
	/*************
	 * ͼ����Դ���� 
	 *************/

	/** ���� **/
	//Player
	Load("player_idle", "Asset/Main Character/Sword+Aim+Throw/idle/", 139, 164, 6);
	Load("player_run", "Asset/Main Character/Sword+Aim+Throw/run/", 124, 164, 8);
	Load("player_idle_to_jump", "Asset/Main Character/Sword+Aim+Throw/idle_to_jump/", 124, 164, 12);
	Load("player_die", "Asset/Main Character/Sword+Aim+Throw/die/", 124, 164, 11);
	

	/** ͼ�� **/
	//Environment
	Load("bg0", "Asset/Surroundings/Medieval_Castle/background/layer_1.png", WIN_WIDTH + 50, WIN_HEIGHT + 75);
	Load("bg1", "Asset/Surroundings/Medieval_Castle/background/layer_2.png", WIN_WIDTH + 50, WIN_HEIGHT + 75);
	Load("bg2", "Asset/Surroundings/Medieval_Castle/background/layer_3.png", WIN_WIDTH + 50, WIN_HEIGHT + 75);


}

//*********                             **********
//************************************************




IMAGE* ResourceManager::Fetch(std::string name)
{
	return imagePool[name];
}

ArtyEngine::FAnimationResource ResourceManager::FetchAnimation(std::string name)
{
	return animationPool[name];
}

std::wstring ResourceManager::FetchVideo(std::string name)
{
	return videoPool[name];
}

// ���ص���ͼƬ
void ResourceManager::Load(std::string name, std::string path, int wid, int hei)
{
	IMAGE* img = new IMAGE;
	loadimage(img, LPCTSTR(path.c_str()),wid,hei);
	imagePool.insert({name, img});
}
// ����һϵ�ж���
void ResourceManager::Load(std::string name, std::string path, int wid, int hei, int num)
{
	IMAGE**images = new IMAGE*[num];
	for (int i = 0; i < num; i++)
	{
		images[i] = new IMAGE;
		loadimage(images[i], LPCTSTR((path + "/" + std::to_string(i) + ".png").c_str()), wid, hei);
	}
	animationPool.insert({ name, {images,num } });
}
// �����Զ���ߴ��ϵ�ж���
void ResourceManager::Load(std::string name, std::string path, const std::vector<FIntVector2>& arr)
{
	int num = int(arr.size());
	IMAGE** images = new IMAGE * [num];
	for (int i = 0; i < num; i++)
	{
		images[i] = new IMAGE;
		loadimage(images[i], LPCTSTR((path + "/" + std::to_string(i) + ".png").c_str()), arr[i].x, arr[i].y);
	}
	animationPool.insert({ name, {images,int(arr.size())} });
}

// ���طָ��֡����
void ResourceManager::Load(std::string name, std::string path, int wid, int hei, int num, int row, int col)
{
	IMAGE** images = new IMAGE * [num];
	IMAGE img;
	loadimage(&img, LPCTSTR(path.c_str()), wid, hei);
	DWORD* src = GetImageBuffer(&img);

	int width = wid / col;
	int height = hei / row;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int x = j * width;
			int y = i * height;
			int index = i * col + j;
			if (index >= num)break;
			images[index] = new IMAGE(width, height);
			DWORD* dst = GetImageBuffer(images[index]);

			for (int x1 = 0; x1 < width; ++x1)
			{
				for (int y1 = 0; y1 < height; ++y1)
				{
					dst[x1 + y1 * width] = src[x + x1 + (y + y1) * wid];
				}
			}
		}
	}
	animationPool.insert({ name, {images,num } });
}

// ������Ƶ�ļ�
void ResourceManager::Load(std::string name, std::string path)
{
	std::string file = std::string("open ") + path + std::string(" alias ") + name;
	mciSendString(file.c_str(), NULL, 0, NULL);
}
//������Ƶ�ļ�·��
void ResourceManager::Load(std::string name, std::wstring pszFileName)
{
	videoPool[name] = pszFileName;
}

void ResourceManager::LoadText(std::string path)
{
	AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL);
}

void ResourceManager::LoadCustomCursor(std::string path)
{
	// ���ع���ļ�
	HCURSOR hcur = (HCURSOR)LoadImage(NULL, path.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	if (hcur == NULL)
	{
		return;
	}

	ICONINFO iconInfo;
	if (GetIconInfo(hcur, &iconInfo))
	{
		// ��ȡ���ͼ��Ŀ�Ⱥ͸߶�
		BITMAP bm;
		GetObject(iconInfo.hbmColor, sizeof(BITMAP), &bm);
		int cursorWidth = bm.bmWidth;
		int cursorHeight = bm.bmHeight;

		// �����µ��ȵ�λ��
		ICONINFO newIconInfo = iconInfo;
		newIconInfo.xHotspot = cursorWidth / 2; 
		newIconInfo.yHotspot = cursorHeight / 2; 

		// �����µĹ��
		HCURSOR newHcur = CreateIconIndirect(&newIconInfo);
		if (newHcur == NULL)
		{
			DeleteObject(iconInfo.hbmColor);
			DeleteObject(iconInfo.hbmMask);
			return;
		}

		DeleteObject(iconInfo.hbmColor);
		DeleteObject(iconInfo.hbmMask);

		// �����µĹ��
		SetClassLongPtr(GetHWnd(), GCLP_HCURSOR, (LONG_PTR)newHcur);
	}
	else
	{
		DeleteObject(hcur);
	}
}
