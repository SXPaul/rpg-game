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
    // 创建 PlayerAnimator 组件
    ani = ConstructComponent<PlayerAnimator>();
    //// 将 PlayerAnimator 与渲染器关联
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

    lastJumpTime = 0.0f; // 初始化上次跳跃时间戳
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
    // 可选：可以在这里做一些速度限制或动画参数设置
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
			return; // 如果已经在向右走，则不允许向左走
        }
        walkLock = 1; 
        SetMaxWalkingSpeed(400.f);
        ani->SetFloat("walkingSpeed", 400.f);
        AddInputX(-3.f, true);
        if((curDirection != AttackDirection::Up) && (curDirection != AttackDirection::Down)) 
        {            
            // 如果当前方向不是向上或向下
            // 切换到向右的攻击方向
            curDirection = AttackDirection::Left; // 设置当前方向为左
		}
        else
        {
			//当前方向是向上或向下
			lastDirection = AttackDirection::Left; // 记录当前方向
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
            return; // 如果已经在向左走，则不允许向右走
        }
        walkLock = 2;
        SetMaxWalkingSpeed(400.f);
        ani->SetFloat("walkingSpeed", 400.f);
        AddInputX(3.f, true);
        if ((curDirection != AttackDirection::Up) && (curDirection != AttackDirection::Down))
        {
            // 如果当前方向不是向上或向下
            // 切换到向右的攻击方向
            curDirection = AttackDirection::Right; // 设置当前方向为右
        }
        else
        {
			lastDirection = AttackDirection::Right; // 记录当前方向
        }
        });
    inputComponent->BindAction("WalkRightEnd", EInputType::Released, [this]() {
        if (walkLock == 2) 
            walkLock = 0;
        ani->SetFloat("walkingSpeed", 0.f);

        });

    inputComponent->BindAction("HoldUp", EInputType::Holding, [this]()
        {
			curDirection = AttackDirection::Up; // 设置当前方向为向上
            
		});

    inputComponent->BindAction("HoldUpEnd", EInputType::Released, [this]()
        {
            if (curDirection == AttackDirection::Up)
            {
                curDirection = lastDirection; // 恢复到上次的方向
            }
            else return;
        });

    inputComponent->BindAction("HoldDown", EInputType::Holding, [this]()
		{
			if (!isonGround)// 如果玩家不在地面上，则允许向下攻击
			    curDirection = AttackDirection::Down; // 设置当前方向为向下
		});

    inputComponent->BindAction("HoldDownEnd", EInputType::Released, [this]()
        {
            if (curDirection == AttackDirection::Down)
            {
                curDirection = lastDirection; // 恢复到上次的方向
            }
			else return; // 如果当前方向不是向下，则不做任何操作
		});

    inputComponent->BindAction("JumpStart", EInputType::Pressed, [this]()
        {
            if (isonGround)
            {
                // 如果玩家在地面上
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, -400.f)); // 向上跳跃
                isonGround = false; // 跳跃后标记不在地面上
                // 切换到跳跃动画
                //ani->SetFloat("jumpSpeed", -1.f);
                //ani->PlayMontage("jump1");
                //
                //
                lastJumpTime = GameplayStatics::GetTimeSeconds(); // 记录跳跃时间
                jumpLock = 1; // 设置跳跃锁，防止连续跳跃,jumpLock = 1 代表已经开始跳跃，但是还没结束跳跃
            }  
			else return; // 如果不在地面上，则不允许跳跃
        });

    inputComponent->BindAction("Jumping", EInputType::Holding, [this]()
        {
            if (jumpLock == 1 && GameplayStatics::GetTimeSeconds() - lastJumpTime < 0.5f)
            {
				isonGround = false; // 标记玩家不在地面上
                // 如果在跳跃状态且跳跃时间小于0.2秒
				rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, -400.f)); // 持续给一个向上的速度
                // 跳跃动画
                //ani->SetFloat("jumpSpeed", -1.f);
                //
                //
            }
		});

    inputComponent->BindAction("JumpEnd", EInputType::Released, [this]()
        {
            if (jumpLock == 1)
            {
                // 如果跳跃结束
                jumpLock = 0; // 重置跳跃锁
                isonGround = false; // 标记玩家不在地面上
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); // 重置垂直速度
                // 切换到站立动画
                //ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);

                //
                //
            }
		});

    inputComponent->BindAction("Attack", EInputType::Pressed, [this]()
        {
            if (lastAttackTime == 0 || GameplayStatics::GetTimeSeconds() - lastAttackTime > 0.1f)
            {
                // 如果上次攻击时间超过0.5秒
                lastAttackTime = GameplayStatics::GetTimeSeconds(); // 更新上次攻击时间
                // 执行攻击逻辑
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
	//处理碰撞开始的逻辑
    if (normalImpulse.y < 0 && rigid && rigid->GetVelocity().y > 0)
    {
        // 如果碰撞是从上方发生的，并且玩家正在向下移动
		isonGround = true; // 标记玩家在地面上
        rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); // 重置垂直速度
        //此处插入站立动画

    }
    else if (normalImpulse.y > 0 && rigid && rigid->GetVelocity().y < 0)
    {
        // 如果碰撞是从下方发生的，并且玩家正在向上移动
		isonGround = false; // 标记玩家不在地面上
        rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); // 重置垂直速度
	}
    
}

void Player::StayCollision(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult)
{
    // 在这里处理持续碰撞的逻辑
    // 例如，可以检查碰撞的类型并执行相应的操作
    if (normalImpulse.y < 0)
    {
        isonGround = true; // 标记玩家在地面上
    }
}

