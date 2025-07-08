/**
 * @file	RigidBody.h
 * @brief	����������壬��Ҫģ��2D��Ϸ�����е������˶�����
 * @author	Arty
 **/

#pragma once
#include"Components/ActorComponent.h"



/*----------------------------------
			  �������
  ----------------------------------*/
class RigidBody final :public ActorComponent
{
	friend class Collider;

public:
	RigidBody();
	virtual ~RigidBody();
	virtual void Update(float deltaTime) override;
	void PreciseUpdate(float deltaTime);

	//��������
	void SetGravity(float gravity) { this->gravity = gravity; }
	
	//�����ٶ�
	void SetVelocity(FVector2D velocity) { this->velocity = velocity; }
	
	//�����ٶ����ֵ
	void SetMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; }
	
	//���ý��ٶ�
	void SetAngularVelocity(float angularVelocity) { this->angularVelocity = angularVelocity; }
	
	//��������
	void SetMass(float mass) { this->mass = mass; }
	
	//��ӳ���
	void AddImpulse(FVector2D pulse) { if (bMoveable) { velocity += pulse / mass; } }

	//�Ƿ���ƶ�
	void SetMoveable(bool moveable) { this->bMoveable = moveable; if (!moveable)velocity = FVector2D::ZeroVector; }
	
	//�Ƿ���������
	void SetGravityEnabled(bool enabled) { this->bGravityEnabled = enabled; }
	
	//�Ƿ����ת
	void SetRotatable(bool rotatable) { this->bRotatable = rotatable; if (!rotatable)angularVelocity = 0; }

	//������������
	void SetLinearDrag(float linearDrag) { this->linearDrag = linearDrag; }

	//���ý�����
	void SetAngularDrag(float angularDrag) { this->angularDrag = angularDrag; }

	//��ȡ�ٶ�
	FVector2D GetVelocity()const { return velocity; }

	virtual void RegisterDontDestroy()override;

private:
	FVector2D velocity{};
	float maxSpeed = 5000.0f;
	bool bMoveable = true;
	
	float gravity = 980.f;
	bool bGravityEnabled = true;

	float angularVelocity = 0;
	bool bRotatable = true;
	float mass = 1.0f;

	float linearDrag = 0.05f;
	float angularDrag = 0.f;

	std::unordered_set<Collider*> colliders;

	//�˶�ģ��
	void RestrictVelocity(FVector2D impactNormal, const FPhysicsMaterial& material, RigidBody* another = nullptr, bool isStay = false);
};