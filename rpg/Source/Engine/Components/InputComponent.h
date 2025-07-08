/**
 * @file	InputComponent.h
 * @brief	��������������߼�����
 * @author	Arty
 **/


#pragma once
#include "ActorComponent.h"
#include <easyx.h>


/* �����ź����� */
enum class EInputType :uint8
{
	Pressed,
	Released,
	Holding,
	DoubleClick
};

/* ���� */
enum class EKeyCode :int32
{
	VK_LButton = 1,
	VK_RButton,
	VK_MButton = 4,
	VK_Tab = 9,
	VK_Enter = 13,
	VK_Shift = 16,
	VK_Ctrl,
	VK_Esc = 27,
	VK_Space = 32,
	VK_A = 0x41,
	VK_B,VK_C,VK_D,
	VK_E,VK_F,VK_G,
	VK_H,VK_I,VK_J,
	VK_K,VK_L,VK_M,
	VK_N,VK_O,VK_P,
	VK_Q,VK_R,VK_S,
	VK_T,VK_U,VK_V,
	VK_W,VK_X,VK_Y,
	VK_Z,
};

/* ����ӳ����Ϣ */
struct FKeyBindInfo
{
	std::function<void()> func;
	EInputType type = EInputType::Pressed;
	int32 pressFlag = 0;
	float lastTime = 0;
};


/*----------------------------------
			  ���뽻�����
  ----------------------------------*/
class InputComponent final: public ActorComponent
{
public:
	/**
	 * @brief ���ð���ӳ��
	 * @param[in] mappingName			  �¼���
	 * @param[in] value                   ����
	 **/
	void SetMapping(std::string mappingName, EKeyCode value);

	/**
	 * @brief �󶨰����¼�ӳ��
	 * @param[in] actionName		      �¼���
	 * @param[in] type                    ������������
	 * @param[in] obj	                  �ຯ����������ָ��
	 * @param[in] function                �ຯ��ָ��
	 **/
	template<typename T>
	void BindAction(std::string actionName, EInputType type, T* obj, void(T::* func)())
	{
		if (mappings.find(actionName) != mappings.end())
		{
			actionCallbacks.insert({ actionName, { std::bind(func, obj),type,false } });
		}
	}

	/**
     * @brief �󶨰����¼�ӳ��
     * @param[in] actionName		      �¼���
     * @param[in] type                    ������������
     * @param[in] function                ������װ
     **/
	void BindAction(std::string actionName, EInputType type, std::function<void()>func);

	//�Ƿ����κΰ���������
	static bool IsAnyKeyPressed();

	//ĳ�����Ƿ񱻰���
	static bool IsKeyPressed(EKeyCode keycode);

	//��ȡ�����Ļ����
	static FVector2D GetMousePosition();
	
	//�������Ƿ���
	static bool IsMouseButtonPressed();

	//�����������
	static void EnableInput(bool enable);

	//Action(��Ϊ�¼���˲ʱ����������Ƶ����֡��Ӱ��)
	void PeekInfo();
	
	//Axis(���¼�����������������Ƶ�ʺ㶨)
	void PeekInfo_();

	void MouseTick();

private:
	std::unordered_map<std::string, EKeyCode>mappings;
	std::unordered_map<std::string, FKeyBindInfo>actionCallbacks;
	std::unordered_map<std::string, FKeyBindInfo>axisCallbacks;

	static FVector2D mousePos;//����ڻ�ͼ��������
	static bool bActive;//�Ƿ����ý���
	ExMessage msg;
};
