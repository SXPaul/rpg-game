/**
 * @file	Actor.h
 * @brief	����������ඨ�壬�䱾����������������Ϸ�����е�Ψһ������ʽ
 * @author	Arty
 **/



#pragma once
#include"CoreMinimal.h"
#include"Tools/Timer.h"

class ActorComponent;
class SceneComponent;


/*----------------------------------
			 �����������
  ----------------------------------*/
class Actor :public Object, public TimerHandler
{
	friend class RigidBody;

	std::unordered_set<Actor*>children;
	Actor* parent = nullptr;//���������Թ�ϵ ���� ������ɾ

	std::unordered_set<ActorComponent*>components;
	std::unordered_set<ActorComponent*>::iterator components_iter;//��������ı����Լ���ɾ

	bool bDestroyFlag = false;

protected:
	SceneComponent* const root = nullptr;//��������������賡������

public:
	Actor();

	virtual ~Actor();

	virtual void Update(float deltaTime)override;

	virtual void BeginPlay()override;

	virtual void EndPlay()override;

	//��ȡ������������
	Actor* GetOwner()const { return parent; }

	//���ó��������(���������ײ��ϵ��������ʹ�ã��������׳���)
	void SetRootComponent(SceneComponent* newRoot);

	//������������
	void AttachTo(Actor* par);

	//�����������
	void DetachFrom(Actor* par);


	//�����ע�ᵽ��������
	void RegisterComponent(ActorComponent* pCom);

	//�Ӷ���������ע�����
	void UnregisterComponent(ActorComponent* pCom);

	//������Ϸ����
	void Destroy();

	/** ��ȡ�������ԣ���Ը���������ϵ��**/
	const FVector2D& GetLocalPosition() const;
	float GetLocalRotation() const;
	const FVector2D& GetLocalScale() const;
	const FTransform& GetLocalTransform() const;

	/** ��ȡ�������ԣ������������ϵ��**/
	FVector2D GetWorldPosition()const;
	float GetWorldRotation()const;
	FVector2D GetWorldScale()const;

	/** ���ó������ԣ���Ը���������ϵ��**/
	void SetLocalPosition(const FVector2D& pos);
	void SetLocalRotation(float angle);
	void SetLocalScale(const FVector2D& scale);
	void SetPositionAndRotation(const FVector2D& pos, float angle);
	void SetLocalTransform(const FTransform& transform);

	/** ���ӳ�������ƫ���� **/
	void AddPosition(FVector2D pos);
	void AddRotation(float rot);

	//����λ����Ϣ
	void DrawDebugPosition() const;

	//�������,�󶨵�����,��ע�ᵽ��������
	template<typename T>
	T* ConstructComponent()
	{
		T* pCom = new T;
		if (pCom && static_cast<ActorComponent*>(pCom))
		{
			pCom->SetOwner(this);
			RegisterComponent(pCom);
			return pCom;
		}
		delete pCom;
		return nullptr;
	}

	//ͨ��������ȡ���
	template<typename T>
	T* GetComponentByClass()
	{
		for (auto& com : components)
		{
			if (T* pCom = Cast<T>(com))return pCom;
		}
		return nullptr;
	}

	//ͨ��������ȡ���
	template<typename T>
	std::vector<T*> GetComponentsByClass()
	{
		std::vector<T*> result;
		result.reserve(components.size());
		for (auto& obj : components)
		{
			if (T* pObj = Cast<T>(obj))result.push_back(pObj);
		}
		return result;
	}

	//ͨ����ǩ����ȡ���
	ActorComponent* GetComponentByName(std::string tagName);

	//ȫ�ֶ���ע��
	void RegisterDontDestroy();
};