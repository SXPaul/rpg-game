/**
 * @file	SceneComponent.h
 * @brief	���а����������Ե�����ĸ��࣬��������󳡾�����
 * @author	Arty
 **/


#pragma once
#include"Components/ActorComponent.h"



/*----------------------------------
			  �����������
  ----------------------------------*/
class SceneComponent : public ActorComponent
{
	FTransform transform_local;
	std::unordered_set<SceneComponent*>children;
	SceneComponent* parent = nullptr;//���������Թ�ϵ��������ɾ

	void process_Destruct();

public:
	//�����������
	void AttachTo(SceneComponent* par);

	//����������
	void DetachFrom(SceneComponent* par);

	//�������
	virtual void Destruct() override;

	/** ��ȡ�������ԣ���Ը���������ϵ��**/
	const FVector2D& GetLocalPosition() const { return transform_local.position; }
	float GetLocalRotation() const { return transform_local.rotation; }
	const FVector2D& GetLocalScale() const { return transform_local.scale; }
	const FTransform& GetLocalTransform() const { return transform_local; }

	/** ��ȡ�������ԣ������������ϵ��**/
	FVector2D GetWorldPosition() const;
	float GetWorldRotation() const;
	FVector2D GetWorldScale() const;

	/** ���ó������ԣ���Ը���������ϵ��**/
	void SetLocalPosition(const FVector2D& pos) { transform_local.position = pos; }
	void SetLocalRotation(float angle) { transform_local.rotation = angle; }
	void SetLocalScale(const FVector2D& scale) { transform_local.scale = scale; }
	void SetLocalTransform(const FTransform& transform) { transform_local = transform; }

	/** ���ӳ�������ƫ���� **/
	void AddPosition(FVector2D pos) { transform_local.position += pos; }
	void AddRotation(float rot) { transform_local.rotation += rot; }
};
