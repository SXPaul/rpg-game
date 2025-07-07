#include "Player.h"
#include "Components/Collider.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "Components/Camera.h"
#include "PlayerAnimator.h"
#include "GameplayStatics.h"
#include <cstdlib>
#include "AttackBox.h"
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

    ui = GameplayStatics::CreateUI<GameUI>();
    ui->AddToViewport();

    curDirection = AttackDirection::Right;
	lastDirection = curDirection;
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
    ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);
}

void Player::SetupInputComponent(InputComponent* inputComponent)
{
    inputComponent->SetMapping("WalkLeft", EKeyCode::VK_A);
    inputComponent->SetMapping("WalkRight", EKeyCode::VK_D);
    inputComponent->SetMapping("WalkLeftEnd", EKeyCode::VK_A);
    inputComponent->SetMapping("WalkRightEnd", EKeyCode::VK_D);
    inputComponent->SetMapping("HoldUp", EKeyCode::VK_W);
	inputComponent->SetMapping("HoldUpEnd", EKeyCode::VK_W);
	inputComponent->SetMapping("HoldDown", EKeyCode::VK_S);
	inputComponent->SetMapping("HoldDownEnd", EKeyCode::VK_S);
	inputComponent->SetMapping("JumpStart", EKeyCode::VK_Space);
	inputComponent->SetMapping("Jumping", EKeyCode::VK_Space);
	inputComponent->SetMapping("JumpEnd", EKeyCode::VK_Space);
	inputComponent->SetMapping("Attack", EKeyCode::VK_J);


    inputComponent->BindAction("WalkLeft", EInputType::Holding, [this]() {
        if (walkLock == 2)
        {
			return; // ����Ѿ��������ߣ�������������
        }
        walkLock = 1; 
        SetMaxWalkingSpeed(400.f);
        ani->SetFloat("walkingSpeed", 400.f);
        AddInputX(-3.f, true);
        if((curDirection != AttackDirection::Up) && (curDirection != AttackDirection::Down)) 
        {            
            // �����ǰ���������ϻ�����
            // �л������ҵĹ�������
            curDirection = AttackDirection::Left; // ���õ�ǰ����Ϊ��
		}
        else
        {
			//��ǰ���������ϻ�����
			lastDirection = AttackDirection::Left; // ��¼��ǰ����
        }

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
        if ((curDirection != AttackDirection::Up) && (curDirection != AttackDirection::Down))
        {
            // �����ǰ���������ϻ�����
            // �л������ҵĹ�������
            curDirection = AttackDirection::Right; // ���õ�ǰ����Ϊ��
        }
        else
        {
			lastDirection = AttackDirection::Right; // ��¼��ǰ����
        }
        });
    inputComponent->BindAction("WalkRightEnd", EInputType::Released, [this]() {
        if (walkLock == 2) 
            walkLock = 0;
        ani->SetFloat("walkingSpeed", 0.f);

        });

    inputComponent->BindAction("HoldUp", EInputType::Holding, [this]()
        {
			curDirection = AttackDirection::Up; // ���õ�ǰ����Ϊ����
            
		});

    inputComponent->BindAction("HoldUpEnd", EInputType::Released, [this]()
        {
            if (curDirection == AttackDirection::Up)
            {
                curDirection = lastDirection; // �ָ����ϴεķ���
            }
            else return;
        });

    inputComponent->BindAction("HoldDown", EInputType::Holding, [this]()
		{
			if (!isonGround)// �����Ҳ��ڵ����ϣ����������¹���
			    curDirection = AttackDirection::Down; // ���õ�ǰ����Ϊ����
		});

    inputComponent->BindAction("HoldDownEnd", EInputType::Released, [this]()
        {
            if (curDirection == AttackDirection::Down)
            {
                curDirection = lastDirection; // �ָ����ϴεķ���
            }
			else return; // �����ǰ���������£������κβ���
		});

    inputComponent->BindAction("JumpStart", EInputType::Pressed, [this]()
        {
            if (isonGround)
            {
                // �������ڵ�����
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, -400.f)); // ������Ծ
                isonGround = false; // ��Ծ���ǲ��ڵ�����
                // �л�����Ծ����
                //ani->SetFloat("jumpSpeed", -1.f);
                //ani->PlayMontage("jump1");
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
                //ani->SetFloat("jumpSpeed", -1.f);
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
                //ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);

                //
                //
            }
		});

    inputComponent->BindAction("Attack", EInputType::Pressed, [this]()
        {
            if (lastAttackTime == 0 || GameplayStatics::GetTimeSeconds() - lastAttackTime > 0.1f)
            {
                // ����ϴι���ʱ�䳬��0.5��
                lastAttackTime = GameplayStatics::GetTimeSeconds(); // �����ϴι���ʱ��
                // ִ�й����߼�
                //
                //
                //
				AttackBox* attackBox = GameplayStatics::CreateObject<AttackBox>();
                attackBox->AttachTo(this);
                switch (curDirection)
                {
                    case AttackDirection::Left:
                        attackBox->Init(AttackDirection::Left);
                        attackBox->SetLocalPosition(FVector2D(110, 0));
						break;
                    case AttackDirection::Right:
                        attackBox->Init(AttackDirection::Right);
						attackBox->SetLocalPosition(FVector2D(110, 0));
                        break;
                    case AttackDirection::Up:
						attackBox->Init(AttackDirection::Up);
                        attackBox->SetLocalPosition(FVector2D(-0, -70));
                        break;
					case AttackDirection::Down:
						attackBox->Init(AttackDirection::Down);
                        attackBox->SetLocalPosition(FVector2D( 0, 100));
						break;
                    default:
						break;
                }
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

