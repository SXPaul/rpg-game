#include "ResourceManager.h"
#include <easyx.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")


//************************************************
//*********       用户需编辑部分          **********

void ResourceManager::Initialize()
{
	/*************
	 * 图像资源加载 
	 *************/

	/** 动画 **/
	//Player
	Load("player_idle", "Asset/Main Character/Sword+Aim+Throw/idle/", 138, 88, 6);
	Load("player_runstart", "Asset/Main Character/Sword+Aim+Throw/idle_to_runstart/", 138, 88, 4);
	Load("player_run", "Asset/Main Character/Sword+Aim+Throw/run/", 138, 88, 4);
	Load("player_idle_to_jump", "Asset/Main Character/Sword+Aim+Throw/idle_to_jump/", 138, 88, 12);
	Load("player_die", "Asset/Main Character/Sword+Aim+Throw/die/", 138, 88, 30);
	Load("player_dead", "Asset/Main Character/Sword+Aim+Throw/dead/", 138, 88, 1);
	Load("player_attack1", "Asset/Main Character/Sword+Aim+Throw/light_attack_1/", 138, 88, 7);
	Load("player_attack2", "Asset/Main Character/Sword+Aim+Throw/light_attack_2/", 138, 88, 5);
	Load("player_jump_1", "Asset/Main Character/Sword+Aim+Throw/jump_up_1/", 138, 88, 4);
	Load("player_jump_2", "Asset/Main Character/Sword+Aim+Throw/jump_up_2/", 138, 88, 8);
	Load("player_jump_falling", "Asset/Main Character/Sword+Aim+Throw/jump_falling/", 138, 88, 4);
	/* life */
	Load("bar", "Asset/Surroundings/Medieval_Castle/HUD/bar.png", 118*2, 13*2);
	Load("bar_background", "Asset/Surroundings/Medieval_Castle/HUD/bar_background.png", 100*2, 7*2);
	Load("health_bar", "Asset/Surroundings/Medieval_Castle/HUD/health_bar.png", 100*2, 7*2);

	/** 图像 **/
	//Environment
	Load("forest_1", "Asset/Surroundings/Forest_Bg/background_layer_1.png", WIN_WIDTH + 0, WIN_HEIGHT + 0);
	Load("forest_2", "Asset/Surroundings/Forest_Bg/background_layer_2.png", WIN_WIDTH + 0, WIN_HEIGHT + 0);
	Load("forest_3", "Asset/Surroundings/Forest_Bg/background_layer_3.png", WIN_WIDTH + 0, WIN_HEIGHT + 0);
	Load("forest_1_max", "Asset/Surroundings/Forest_Bg/background_layer_1.png", WIN_WIDTH + 2000, WIN_HEIGHT + 2000);
	Load("forest_2_max", "Asset/Surroundings/Forest_Bg/background_layer_2.png", WIN_WIDTH + 2000, WIN_HEIGHT + 2000);
	Load("forest_3_max", "Asset/Surroundings/Forest_Bg/background_layer_3.png", WIN_WIDTH + 2000, WIN_HEIGHT + 2000);
	Load("bg0", "Asset/Surroundings/Medieval_Castle/background/layer_1.png", WIN_WIDTH + 2800, WIN_HEIGHT + 2800);
	Load("bg1", "Asset/Surroundings/Medieval_Castle/background/layer_2.png", WIN_WIDTH + 2800, WIN_HEIGHT + 2800);
	Load("bg2", "Asset/Surroundings/Medieval_Castle/background/layer_3.png", WIN_WIDTH + 2800, WIN_HEIGHT + 2800);
	Load("bg0_pro", "Asset/Surroundings/Medieval_Castle/background/layer_1.png", WIN_WIDTH + 500, WIN_HEIGHT + 500);
	Load("bg1_pro", "Asset/Surroundings/Medieval_Castle/background/layer_2.png", WIN_WIDTH + 500, WIN_HEIGHT + 500);
	Load("bg2_pro", "Asset/Surroundings/Medieval_Castle/background/layer_3.png", WIN_WIDTH + 500, WIN_HEIGHT + 500);

	// tiles
	/* brick */
	Load("brick_1", "Asset/Surroundings/Medieval_Castle/Tiles/brick_1.png", 50, 50);
	Load("brick_2", "Asset/Surroundings/Medieval_Castle/Tiles/brick_2.png", 50, 50);
	Load("brick_3", "Asset/Surroundings/Medieval_Castle/Tiles/brick_3.png", 50, 50);
	Load("brick_4", "Asset/Surroundings/Medieval_Castle/Tiles/brick_4.png", 50, 50);
	Load("brick_5", "Asset/Surroundings/Medieval_Castle/Tiles/brick_5.png", 50, 50);
	Load("brick_6", "Asset/Surroundings/Medieval_Castle/Tiles/brick_6.png", 50, 50);
	Load("brick_7", "Asset/Surroundings/Medieval_Castle/Tiles/brick_7.png", 50, 50);
	Load("brick_8", "Asset/Surroundings/Medieval_Castle/Tiles/brick_8.png", 50, 50);
	Load("brick_9", "Asset/Surroundings/Medieval_Castle/Tiles/brick_9.png", 50, 50);
	Load("brick_10", "Asset/Surroundings/Medieval_Castle/Tiles/brick_10.png", 50, 50);
	Load("brick_11", "Asset/Surroundings/Medieval_Castle/Tiles/brick_11.png", 50, 50);
	Load("brick_12", "Asset/Surroundings/Medieval_Castle/Tiles/brick_12.png", 50, 50);
	Load("brick_13", "Asset/Surroundings/Medieval_Castle/Tiles/brick_13.png", 50, 50);
	Load("brick_14", "Asset/Surroundings/Medieval_Castle/Tiles/brick_14.png", 50, 50);
	Load("brick_15", "Asset/Surroundings/Medieval_Castle/Tiles/brick_15.png", 50, 50);
	Load("brick_16", "Asset/Surroundings/Medieval_Castle/Tiles/brick_16.png", 50, 50);
	Load("brick_side_left_1", "Asset/Surroundings/Medieval_Castle/Tiles/brick_side_left_1.png", 50, 50);
	Load("brick_side_left_2", "Asset/Surroundings/Medieval_Castle/Tiles/brick_side_left_2.png", 50, 50);
	Load("brick_side_right_1", "Asset/Surroundings/Medieval_Castle/Tiles/brick_side_right_1.png", 50, 50);
	Load("brick_side_right_2", "Asset/Surroundings/Medieval_Castle/Tiles/brick_side_right_2.png", 50, 50);
	/* floor */
	Load("floor_tile_1", "Asset/Surroundings/Medieval_Castle/Tiles/floor_tile_1.png",30,30);
	Load("floor_tile_2", "Asset/Surroundings/Medieval_Castle/Tiles/floor_tile_2.png", 30, 30);
	Load("floor_tile_3", "Asset/Surroundings/Medieval_Castle/Tiles/floor_tile_3.png", 30, 30);
	Load("floor_tile_4", "Asset/Surroundings/Medieval_Castle/Tiles/floor_tile_4.png", 30, 30);

	/* enemies */
	// Enemy1
	Load("Enemy1_walk", "Asset/Enemies/Skeleton/Skeleton_Walk", 44, 66,13);
	Load("Enemy1_react", "Asset/Enemies/Skeleton/Skeleton_React", 44, 66,4);
	Load("Enemy1_idle", "Asset/Enemies/Skeleton/Skeleton_Idle", 44, 66,11);
	Load("Enemy1_hit", "Asset/Enemies/Skeleton/Skeleton_Hit", 44, 66,8);
	Load("Enemy1_dead", "Asset/Enemies/Skeleton/Skeleton_Dead", 44, 66,15);
	Load("Enemy1_attack", "Asset/Enemies/Skeleton/Skeleton_Attack", 86, 66,18);
	// NightBorne
	Load("NightBorne_idle", "Asset/Enemies/Night_Borne/NightBorne_idle", 280,280 ,9);
	Load("NightBorne_run", "Asset/Enemies/Night_Borne/NightBorne_run", 280,280 ,6);
	Load("NightBorne_attack", "Asset/Enemies/Night_Borne/NightBorne_attack", 280,280 ,12);
	Load("NightBorne_hurt", "Asset/Enemies/Night_Borne/NightBorne_hurt", 280,280 ,5);
	Load("NightBorne_die", "Asset/Enemies/Night_Borne/NightBorne_die", 280,280 ,23);


	/* carpet */
	Load("carpet_1", "Asset/Surroundings/Medieval_Castle/Tiles/floor_tile_carpet_1.png", 30, 30);
	Load("carpet_2", "Asset/Surroundings/Medieval_Castle/Tiles/floor_tile_carpet_2.png", 30, 30);
	Load("carpet_3", "Asset/Surroundings/Medieval_Castle/Tiles/floor_tile_carpet_3.png", 30, 30);
	Load("carpet_4", "Asset/Surroundings/Medieval_Castle/Tiles/floor_tile_carpet_4.png", 30, 30);
	/* arch */
	Load("arch_1", "Asset/Surroundings/Medieval_Castle/Tiles/arch_1.png", 30, 30);
	Load("arch_2", "Asset/Surroundings/Medieval_Castle/Tiles/arch_2.png", 30, 20);
	Load("arch_3", "Asset/Surroundings/Medieval_Castle/Tiles/arch_3.png", 30, 30);
	Load("arch_4", "Asset/Surroundings/Medieval_Castle/Tiles/arch_4.png", 20, 30);
	Load("arch_5", "Asset/Surroundings/Medieval_Castle/Tiles/arch_5.png", 20, 30);
	Load("arch_6", "Asset/Surroundings/Medieval_Castle/Tiles/arch_6.png", 20, 30);
	Load("arch_7", "Asset/Surroundings/Medieval_Castle/Tiles/arch_7.png", 20, 30);
	/* lion_column */
	Load("lion_1", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_1.png", 30, 30);
	Load("lion_2", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_2.png", 30, 30);
	Load("lion_3", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_3.png", 30, 30);
	Load("lion_4", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_4.png", 30, 30);
	Load("lion_5", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_5.png", 30, 30);
	Load("lion_6", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_6.png", 30, 30);
	Load("lion_7", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_7.png", 30, 30);
	Load("lion_8", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_8.png", 30, 30);
	Load("lion_9", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_9.png", 30, 30);
	Load("lion_10", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_10.png", 30, 30);
	Load("lion_11", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_11.png", 30, 30);
	Load("lion_12", "Asset/Surroundings/Medieval_Castle/Tiles/lion_column_12.png", 30, 30);
	/* platform */
	Load("platform_1", "Asset/Surroundings/Medieval_Castle/Tiles/platform_1.png", 30, 15);
	Load("platform_2", "Asset/Surroundings/Medieval_Castle/Tiles/platform_2.png", 30, 15);
	Load("platform_3", "Asset/Surroundings/Medieval_Castle/Tiles/platform_3.png", 30, 15);
	Load("platform_4", "Asset/Surroundings/Medieval_Castle/Tiles/platform_4.png", 30, 15);
	Load("platform_shadow", "Asset/Surroundings/Medieval_Castle/Tiles/platform_shadow.png", 30, 5);
	/* stair */
	Load("stairs_1", "Asset/Surroundings/Medieval_Castle/Tiles/stairs_tile_1.png", 30, 30);
	Load("stairs_2", "Asset/Surroundings/Medieval_Castle/Tiles/stairs_tile_2.png", 30, 30);
	Load("stairs_3", "Asset/Surroundings/Medieval_Castle/Tiles/stairs_tile_3.png", 30, 30);
	Load("stairs_4", "Asset/Surroundings/Medieval_Castle/Tiles/stairs_tile_4.png", 30, 30);
	Load("stairs_carpet_1", "Asset/Surroundings/Medieval_Castle/Tiles/stairs_tile_carpet_1.png", 30, 30);
	Load("stairs_carpet_2", "Asset/Surroundings/Medieval_Castle/Tiles/stairs_tile_carpet_2.png", 30, 30);
	Load("stairs_carpet_3", "Asset/Surroundings/Medieval_Castle/Tiles/stairs_tile_carpet_3.png", 30, 30);
	Load("stairs_carpet_4", "Asset/Surroundings/Medieval_Castle/Tiles/stairs_tile_carpet_4.png", 30, 30);
	/* blank */
	Load("blank", "Asset/Surroundings/Medieval_Castle/Tiles/blank.png", 30, 30);
	/* Decorations */
	Load("door", "Asset/Surroundings/Medieval_Castle/Decorations/door.png", 40, 60);
	Load("door_pro", "Asset/Surroundings/Medieval_Castle/Decorations/door.png", 80, 120);
	Load("curtain_blue_left", "Asset/Surroundings/Medieval_Castle/Decorations/curtain_blue_1.png", 70, 160);
	Load("curtain_blue_right", "Asset/Surroundings/Medieval_Castle/Decorations/curtain_blue_2.png", 70, 160);
	Load("curtain_red_left", "Asset/Surroundings/Medieval_Castle/Decorations/curtain_red_1.png", 122, 280);
	Load("curtain_red_right", "Asset/Surroundings/Medieval_Castle/Decorations/curtain_red_2.png", 122, 280);
	Load("bookshelf_1", "Asset/Surroundings/Medieval_Castle/Decorations/bookshelf_1.png", 64, 77);
	Load("bookshelf_2", "Asset/Surroundings/Medieval_Castle/Decorations/bookshelf_2.png", 64, 77);
	Load("flag_blue", "Asset/Surroundings/Medieval_Castle/Decorations/flag_blue.png", 38, 67);
	/* UI */
	Load("UI_background", "Asset/UI/UI_background.png", 50, 50);
	Load("red_1", "Asset/UI/red_1.png", 380, 162);

	/* particle*/
	Load("particle", "Asset/FX/Hit/Hits_0/SP103_01.png", 98, 87, 1, 1, 1);
	Load("chest", "Asset/Surroundings/Medieval_Castle/Decorations/crate_1.png", 50, 45);
	Load("chest_", "Asset/Surroundings/Medieval_Castle/Decorations/crate_1_damaged.png", 50, 45);

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

// 加载单张图片
void ResourceManager::Load(std::string name, std::string path, int wid, int hei)
{
	IMAGE* img = new IMAGE;
	loadimage(img, LPCTSTR(path.c_str()),wid,hei);
	imagePool.insert({name, img});
}
// 加载一系列动画
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
// 加载自定义尺寸的系列动画
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

// 加载分割的帧动画
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

// 加载音频文件
void ResourceManager::Load(std::string name, std::string path)
{
	std::string file = std::string("open ") + path + std::string(" alias ") + name;
	mciSendString(file.c_str(), NULL, 0, NULL);
}
//加载视频文件路径
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
	// 加载光标文件
	HCURSOR hcur = (HCURSOR)LoadImage(NULL, path.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	if (hcur == NULL)
	{
		return;
	}

	ICONINFO iconInfo;
	if (GetIconInfo(hcur, &iconInfo))
	{
		// 获取光标图像的宽度和高度
		BITMAP bm;
		GetObject(iconInfo.hbmColor, sizeof(BITMAP), &bm);
		int cursorWidth = bm.bmWidth;
		int cursorHeight = bm.bmHeight;

		// 设置新的热点位置
		ICONINFO newIconInfo = iconInfo;
		newIconInfo.xHotspot = cursorWidth / 2; 
		newIconInfo.yHotspot = cursorHeight / 2; 

		// 创建新的光标
		HCURSOR newHcur = CreateIconIndirect(&newIconInfo);
		if (newHcur == NULL)
		{
			DeleteObject(iconInfo.hbmColor);
			DeleteObject(iconInfo.hbmMask);
			return;
		}

		DeleteObject(iconInfo.hbmColor);
		DeleteObject(iconInfo.hbmMask);

		// 设置新的光标
		SetClassLongPtr(GetHWnd(), GCLP_HCURSOR, (LONG_PTR)newHcur);
	}
	else
	{
		DeleteObject(hcur);
	}
}
