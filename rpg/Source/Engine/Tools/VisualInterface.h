/**
 * @file	VisualInterface.h
 * @brief	����һ����2Dͼ��������Ⱦ�йصĽӿ�
 * @author	Arty
 **/


#pragma once
#include"Core/Struct.h"
#include<easyx.h>
#include<set>



/*----------------------------------
			   ͼ��ӿ�
  ----------------------------------*/
class LayerInterface
{
	int32 layer = 0;
public:
	LayerInterface();
	virtual ~LayerInterface();

	//���ò㼶�������ڹ����BeginPlay������ʹ�ã���ֹ�󶨵�����ӳ��
	void SetLayer(int layer);
	
	int GetLayer()const;

	virtual void Render() = 0;
};

namespace ArtyEngine
{
	/* ��Ⱦ������Ϣ */
	struct FSpriteInfo
	{
		FVector2D offset{};
		FIntVector2 size{};
		FIntVector2 startLoc{};
		FIntVector2 endLoc{};
	};


	/* �˾���Ϣ */
	struct FilterInfo
	{
		COLORREF color = BLACK;//�˾���ɫ
		int32 level = 50;//��ɫ���ɲ㼶��1~100��
		int32 layer = 0;//�˾��㼶��0��1��
	};


	/* �˾�ͼ��������� */
	struct FFilterSort
	{
		bool operator()(const FilterInfo& a, const FilterInfo& b) const
		{
			return a.layer < b.layer;
		}
	};
}

class Animator;

/*----------------------------------
			   ͼ��ӿ�
  ----------------------------------*/
class ImageInterface
{
	friend Animator;

protected:
	IMAGE* sprite{};
	ArtyEngine::FSpriteInfo spriteInfo;
	BYTE alpha = 255;

	IMAGE* copy{};
	float angle = 0;
	void RotateImage(float degree);

	IMAGE* filter{};
	std::set<ArtyEngine::FilterInfo, ArtyEngine::FFilterSort>filterLayers;
	void FilterImage();
	void AddFilter(ArtyEngine::FilterInfo filterInfo);
	void RemoveFilter();

	IMAGE* blur{};

	Animator* animatorAttached = nullptr;//���ŵĶ���������
	virtual void DealImage() = 0;

public:
	virtual ~ImageInterface();

	BYTE GetTransparency()const { return alpha; }
	void SetTransparency(BYTE tranparency) { alpha = tranparency; }


	/**
	 * @brief �����˾�
	 * @param[in] enable			�Ƿ����˾�
	 * @param[in] color	            �˾���ɫ
	 * @param[in] level             �˾�ʩ�ӳ̶ȣ����Ϊ100����СΪ0��
	 **/
	void SetFilter(bool enable, COLORREF col = BLACK, int32 level = 60);

	/**
	 * @brief ��ֵģ����������Gameplay��ʼǰԤ����ʹ�ã�
	 * @param[in] level			    ģ���̶ȣ����С������������Ӱ��
	 **/
	void MeanBlur(unsigned level);

	/**
	 * @brief ��˹ģ������ͬʱ����ݡ���Ϊ�ĕr��������Gameplay��ʼǰԤ����ʹ�ã�
	 * @param[in] level			    ģ���̶ȣ�Խ��ͬʱ�����Ч��Խ�ã����������ľ͸���
	 **/
	void GaussianBlur(unsigned level);

	//���طǶ�����Դ 
	IMAGE* LoadSprite(std::string name);

	/**
	 * @brief ��ȡ�Ƕ�����Դָ������ 
	 * @param[in] start			    ��ȡͼ����ʼλ������
	 * @param[in] end               ��ȡͼ���βλ������
	 **/
	void SetStartAndEndLoc(FIntVector2 start, FIntVector2 end);
};



/*----------------------------------
			  ͼ������
  ----------------------------------*/
class ImageToolkit final
{
	friend class World;
	friend class GameplayStatics;

public:
	//��ȡ��ά���괦����ֵ
	static DWORD GetPixel(IMAGE* img, int32 i, int32 j);

	//��ȡ��ǰ��Ϸ��ͼ����ֹ���lʹ�ã���
	static void GetScreenShot();

	/** �任 **/

	//����ת�任
	static void FlipImage(IMAGE* srcImg, IMAGE* dstImg, bool bIsHorizontal = true);

	//��ȡ�нǲ��ֵ�ͼ��
	static void GetSectorImage(IMAGE* srcImg, IMAGE* dstImg, float start, float end);

	//��תͼ��
	static FIntVector2 RotateImage(IMAGE* srcImg, IMAGE* dstImg, float degree);

	/** �˲� **/

	//���پ�ֵ�˲�(ģ��)
	static void MeanFilter(IMAGE* srcImg, IMAGE* dstImg, int32 radius);

	//��˹�˲�(ģ���ҿ���ݡ�����Ϊ�ĕr������)
	static void GaussianFilter(IMAGE* srcImg, IMAGE* dstImg, int32 radius);

	/** ���� **/
	
	//����͸������
	static void OutText(int x, int y, LPCTSTR str, BYTE alpha, COLORREF color, int size, LPCTSTR style);

private:
	//��������Ļʩ�Ӹ�˹�˲�
	static void ApplyGaussianFilterOnScreen();

	static bool bIsGaussianFilterOn;

	static int GaussianFilterLevel;
};