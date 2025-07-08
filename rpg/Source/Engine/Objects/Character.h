/**
 * @file	Character.h
 * @brief   ��ɫ�ඨ�壬��ҿ��������ܵ����꣬�ʺϴ����ƶ��Խ�ǿ����ҲٿصĽ�ɫ
 * @author	Arty
 **/



#pragma once
#include "Objects/Controller.h"


 /* ��ɫ״̬ */
enum class ECharacterMovementState : uint8
{
	Standing,
	Running,
	Flying
};

class Collider;

 /*----------------------------------
			    ��ɫ��
   ----------------------------------*/
class Character : public Controller
{
	DEFINE_SUPER(Controller)

public:
	Character();

	virtual void BeginPlay()override;

	virtual void Update(float deltaTime)override;

	
	/**
	 * @brief ����ˮƽ�ƶ�����
	 * @param[in] inputValue			  �ƶ�ֵ������Ϊ��
	 * @param[in] bControlScale           ��ɫ�����Ƿ�������ֵ���ƣ�Ĭ��Ϊ��
	 **/
	void AddInputX(float inputValue,bool bControlScale = true);

	//��ȡ��ɫ״̬
	ECharacterMovementState GetMovementState()const { return movementState; }

	//��������ƶ��ٶ�
	void SetMaxWalkingSpeed(float maxSpeed) { maxWalkingSpeed = (maxSpeed > 0 ? maxSpeed : 0); }

protected:
	void OnTouching(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult);

private:
	class SpriteRenderer* render;
	class BoxCollider* box;
	class RigidBody* rigid;
	
	ECharacterMovementState movementState;
	float maxWalkingSpeed;//����ƶ��ٶ�
	bool bAddMoving;//�Ƿ����������ƶ�����
	int32 MoveFlag;//������
};