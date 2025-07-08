/**
 * @file	World.h
 * @brief	��Ϸ�����ඨ�壬�������л���Gameplay�����߼�
 * @author	Arty
 **/



#pragma once
#include"CoreMinimal.h"
#include"Objects/Actor.h"
#include"UI/UserInterface.h"
#include <mutex>


class Engine;
class LevelManager;
class ResourceManager;
class CollisionManager;
class GameplayStatics;
class Actor;
class Timer;
class LayerInterface;
class ImageInterface;
class UserInterface;
class Widget;
class Button;
class Bar;
class Sector;
class Camera;
class SpriteRenderer;
class Animation;
class ParticleSystem;
class Collider;
class CircleCollider;
class BoxCollider;
class Controller;
class AudioPlayer;
class VideoPlayer;
class TimerHandler;
class Level;
class RigidBody;


namespace ArtyEngine
{
	/* ��Ⱦͼ��������� */
	struct LayerSort
	{
		bool operator()(const LayerInterface* a, const LayerInterface* b) const;
	};

	/* ��ײͼ��������� */
	struct ColliderSort
	{
		bool operator()(const Collider* a, const Collider* b) const;
	};
}

/*----------------------------------
			   ��Ϸ����
  ----------------------------------*/
class World final
{
	/** ��Ԫ���� **/
	friend Engine;
	friend GameplayStatics;
	friend GameInstance;
	friend Timer;
	friend LayerInterface;
	friend void Actor::Destroy();
	friend void Actor::DrawDebugPosition()const;
	friend ImageInterface;
	friend Camera;
	friend SpriteRenderer;
	friend Animation;
	friend ParticleSystem;
	friend Collider;
	friend RigidBody;
	friend CircleCollider;
	friend BoxCollider;
	friend Controller;
	friend void UserInterface::RemoveFromViewport();
	friend void UserInterface::RegisterDontDestroy();
	friend Widget;
	friend Button;
	friend Bar;
	friend Sector;
	friend LevelManager;
	friend AudioPlayer;
	friend VideoPlayer;
	friend TimerHandler;
	friend Level;

	std::mutex updateMutex;//������

	bool videoLock = false;//��Ƶ��

	ResourceManager* resourcePool = nullptr;//��Դ��

	CollisionManager* collisionManager = nullptr;//��ײ������

	LevelManager* levelManager = nullptr;//��ͼ������

	Timer* FPSClock = nullptr;//֡��ʱ��

	Timer* OverallClock = nullptr;//ȫ�ּ�ʱ��

	float deltaTime = 0;//֡���ʱ��

	float pauseDelay = 0.f;//�����߼���ͣʱ��
	float lastPauseTime = 0.f;//���ڼ�¼�ϴ���ͣʱ��

	/** ��������UI���� **/

	std::unordered_set<Actor*>GameActors;
	std::list<Actor*>GameActors_to_add;
	std::unordered_set<Actor*>GameActors_to_delete;
	std::unordered_set<UserInterface*>GameUIs;
	std::deque<UserInterface*>GameUIs_to_add;
	std::unordered_set<UserInterface*>GameUIs_to_delete;

	/** ��������UI����ʱ��������ȫ�֣� **/

	std::unordered_set<Actor*>OverallGameActors;
	std::list<Actor*>OverallGameActors_to_add;
	std::unordered_set<UserInterface*>OverallGameUIs;
	std::deque<UserInterface*>OverallGameUIs_to_add;

	std::unordered_set<LayerInterface*>OverallRenders;
	std::unordered_set<Collider*>OverallColliders;
	std::unordered_set<RigidBody*>OverallRigids;
	std::unordered_set<Timer*>GameTimers;

	/**  ��Ⱦ����ײ���㡢UI��������� **/

	std::set<LayerInterface*, ArtyEngine::LayerSort>GameRenderers;
	std::unordered_set<Collider*>GameColliders;
	std::unordered_set<Collider*>GameColliders_to_clear;
	std::unordered_set<RigidBody*>GameRigids;
	std::set<Collider*, ArtyEngine::ColliderSort>ColliderZones[10][6];
	std::set<LayerInterface*, ArtyEngine::LayerSort>UIDetectZones[6][4];

	/** ��Ϸ�������� **/

	GameInstance* gameInstance = nullptr;
	Level* currentLevel = nullptr;
	Camera* mainCamera = nullptr;


	/** �����߼����� **/

	//�߼�����
	void Update(float deltaTime);

	//�߾��ȼ���
	void Update_();

	//�����������룩
	void Input();

	//��Ⱦ
	void Render();

	//��ײ����
	void ProcessColliders();

	//������ײ�¼�
	void ProcessCollisions(float deltaTime);

	//Debugģʽ 
	void Debug();

	//������� 
	void WipeData();
};

//��Ϸ����Ψһʵ�����κ������Ӧ����ֱ��ʹ��
extern World mainWorld;