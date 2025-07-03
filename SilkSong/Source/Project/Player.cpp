#include "Player.h"
#include "Components/Collider.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "Components/Camera.h"
#include "PlayerAnimator.h"
#include "GameplayStatics.h"
#include <cstdlib>
Player::Player()
{
    render = GetComponentByClass<SpriteRenderer>();
    // ���� PlayerAnimator ���
    ani = ConstructComponent<PlayerAnimator>();
    //// �� PlayerAnimator ����Ⱦ������
    ani->SetupAttachment(render);
    if (render) render->SetLayer(1);
	walkLock = 0;

    box = GetComponentByClass<BoxCollider>();
    if (box) {
        box->SetSize({ 30, 70 });
        box->SetLocalPosition({ -15, 10 });
        box->SetCollisonMode(CollisionMode::Collision);
        box->SetType(CollisionType::Player);
        box->SetPhysicsMaterial(FPhysicsMaterial(0.1f, 0));
    }

    rigid = GetComponentByClass<RigidBody>();
    if (rigid) {
        rigid->SetLinearDrag(0.07f);
        rigid->SetGravity(1960);
    }


    box->OnComponentHit.AddDynamic(this, &Player::StartCollision);
    box->OnComponentStay.AddDynamic(this, &Player::StayCollision);

    walkLock = 0;
	jumpLock = 0;
    lastJumpTime = 0.0f; // ��ʼ���ϴ���Ծʱ���
	isonGround = false;
}

void Player::BeginPlay()
{
    Super::BeginPlay();
    if (ani) {
        ani->SetNode("idle");
    }
}

void Player::Update(float deltaTime)
{
    Super::Update(deltaTime);
    // ��ѡ��������������һЩ�ٶ����ƻ򶯻���������
}

void Player::SetupInputComponent(InputComponent* inputComponent)
{
    inputComponent->SetMapping("WalkLeft", EKeyCode::VK_A);
    inputComponent->SetMapping("WalkRight", EKeyCode::VK_D);
    inputComponent->SetMapping("WalkLeftEnd", EKeyCode::VK_A);
    inputComponent->SetMapping("WalkRightEnd", EKeyCode::VK_D);
	inputComponent->SetMapping("JumpStart", EKeyCode::VK_Space);
	inputComponent->SetMapping("Jumping", EKeyCode::VK_Space);
	inputComponent->SetMapping("JumpEnd", EKeyCode::VK_Space);



    inputComponent->BindAction("WalkLeft", EInputType::Holding, [this]() {
        if (walkLock == 2)
        {
			return; // ����Ѿ��������ߣ�������������
        }
        walkLock = 1; 
        SetMaxWalkingSpeed(400.f);
        ani->SetFloat("walkingSpeed", 400.f);
        AddInputX(-3.f, true);
        });
    inputComponent->BindAction("WalkLeftEnd", EInputType::Released, [this]() {
        if (walkLock == 1) 
            walkLock = 0;
        ani->SetFloat("walkingSpeed", 0.f);
        });
    inputComponent->BindAction("WalkRight", EInputType::Holding, [this]() {
        if (walkLock == 1)
		{
			return; // ����Ѿ��������ߣ�������������
		}
        walkLock = 2;
        SetMaxWalkingSpeed(400.f);
        ani->SetFloat("walkingSpeed", 400.f);
        AddInputX(3.f, true);
        });
    inputComponent->BindAction("WalkRightEnd", EInputType::Released, [this]() {
        if (walkLock == 2) 
            walkLock = 0;
        ani->SetFloat("walkingSpeed", 0.f);

        });

    inputComponent->BindAction("JumpStart", EInputType::Pressed, [this]()
        {
            if (isonGround)
            {
                // �������ڵ�����
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, -400.f)); // ������Ծ
                isonGround = false; // ��Ծ���ǲ��ڵ�����
                // �л�����Ծ����
                //
                //
                //
                lastJumpTime = GameplayStatics::GetTimeSeconds(); // ��¼��Ծʱ��
                jumpLock = 1; // ������Ծ������ֹ������Ծ,jumpLock = 1 �����Ѿ���ʼ��Ծ�����ǻ�û������Ծ
            }
			else return; // ������ڵ����ϣ���������Ծ
        });

    inputComponent->BindAction("Jumping", EInputType::Holding, [this]()
        {
            if (jumpLock == 1 && GameplayStatics::GetTimeSeconds() - lastJumpTime < 0.5f)
            {
				isonGround = false; // �����Ҳ��ڵ�����
                // �������Ծ״̬����Ծʱ��С��0.2��
				rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, -400.f)); // ������һ�����ϵ��ٶ�
                // ��Ծ����
                //
                //
                //
            }
		});

    inputComponent->BindAction("JumpEnd", EInputType::Released, [this]()
        {
            if (jumpLock == 1)
            {
                // �����Ծ����
                jumpLock = 0; // ������Ծ��
                isonGround = false; // �����Ҳ��ڵ�����
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); // ���ô�ֱ�ٶ�
                // �л���վ������
                //
                //
                //
            }
		});
}

FVector2D Player::GetCameraPos()
{
    if (camera)return camera->GetVirtualPosition();
    return FVector2D();
}

void Player::StartCollision(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult)
{
	//������ײ��ʼ���߼�
    if (normalImpulse.y < 0 && rigid && rigid->GetVelocity().y > 0)
    {
        // �����ײ�Ǵ��Ϸ������ģ�����������������ƶ�
		isonGround = true; // �������ڵ�����
        rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); // ���ô�ֱ�ٶ�
        //�˴�����վ������

    }
    else if (normalImpulse.y > 0 && rigid && rigid->GetVelocity().y < 0)
    {
        // �����ײ�Ǵ��·������ģ�����������������ƶ�
		isonGround = false; // �����Ҳ��ڵ�����
        rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); // ���ô�ֱ�ٶ�
	}
    
}

void Player::StayCollision(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult)
{
    // �����ﴦ�������ײ���߼�
    // ���磬���Լ����ײ�����Ͳ�ִ����Ӧ�Ĳ���
    if (normalImpulse.y < 0)
    {
        isonGround = true; // �������ڵ�����
    }
}

