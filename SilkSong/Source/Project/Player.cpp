#include "Player.h"
#include "Components/Collider.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "Components/Camera.h"
#include "PlayerAnimator.h"
#include "GameplayStatics.h"
#include <cstdlib>
#include "AttackBox.h"
#include "PlayerPropertyComponent.h" 
#include "DamageResponseComponent.h"
#include "DefaultDamageStrategy.h"


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

    hurtBox = ConstructComponent<BoxCollider>();
    hurtBox->AttachTo(root);
    hurtBox->SetSize({ 30, 70 });
    hurtBox->SetLocalPosition({ -15, 10 });
    hurtBox->SetType(CollisionType::HurtBox);

    rigid = GetComponentByClass<RigidBody>();
    if (rigid) {
        rigid->SetLinearDrag(0.07f);
        rigid->SetGravity(1960);
    }


    box->OnComponentHit.AddDynamic(this, &Player::StartCollision);
    box->OnComponentStay.AddDynamic(this, &Player::StayCollision);

    damageResponse = ConstructComponent<DamageResponseComponent>();
    playerProperty = ConstructComponent<PlayerPropertyComponent>();
    ui = GameplayStatics::CreateUI<GameUI>();
    ui->AddToViewport();

    curDirection = AttackDirection::Right;
	lastDirection = curDirection;
    walkLock = 0;
	jumpLock = 0;

    lastJumpTime = 0.0f; // 初始化上次跳跃时间戳.
	lastDashTime = 0.0f; // 初始化上次冲刺时间戳.
	lastAttackTime = 0.0f; // 初始化上次攻击时间戳.
	isDashing = false; // 初始化冲刺状态为 false
	isonGround = false;

    blinkTimes = 0; //无敌帧时间


}

void Player::BeginPlay()
{
    Super::BeginPlay();
    if (ani) {
        ani->SetNode("idle");
    }

    BlinkTimer.Bind(0.2f, [this]()
        {
            if (blinkTimes > 0)
            {
                render->Blink(0.1f, BLACK);
                if (--blinkTimes == 0 )
                {
                    hurtBox->SetCollisonMode(CollisionMode::Trigger);
                    box->SetCollisionResponseToType(CollisionType::Bullet, true);
                    //GameModeHelper::GetInstance()->RefreshVolume();
                    //if (playerProperty->GetHealth() != 1)particle->SetIsLoop(false);
                }
            }
        }, true);

    box->OnComponentHit.AddDynamic(this, &Player::StartCollision);
    box->OnComponentStay.AddDynamic(this, &Player::StayCollision);
}

void Player::Update(float deltaTime)
{
    Super::Update(deltaTime);
    // 可选：可以在这里做一些速度限制或动画参数设置
    ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);

    if (isDashing)
    {
		SetMaxWalkingSpeed(1600.f); // 冲刺时增加最大行走速度
        AddInputX(GetWorldScale().x * 10000 * deltaTime, false);
        // 如果正在冲刺，检查是否需要结束冲刺
        if (GameplayStatics::GetTimeSeconds() - lastDashTime > 0.2f)
        {
            isDashing = false; // 结束冲刺状态
            SetMaxWalkingSpeed(400.f); // 恢复最大行走速度
            rigid->SetGravityEnabled(true);
            rigid->SetVelocity({ rigid->GetVelocity().x,0 });
		}
    }
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
	inputComponent->SetMapping("Dash", EKeyCode::VK_K);
	inputComponent->SetMapping("Heal", EKeyCode::VK_H);


    inputComponent->BindAction("WalkLeft", EInputType::Holding, [this]() {
        if (walkLock == 2 || isDashing)
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
        if (walkLock == 1 ||isDashing)
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
            if ((isonGround && (jumpLock == 0)) || (jumpLock == 1))
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
                jumpLock ++; // 设置跳跃锁，防止连续跳跃,jumpLock = 1 代表已经开始跳跃，但是还没结束跳跃
            }  
			else return; // 如果不在地面上，则不允许跳跃
        });

    inputComponent->BindAction("Jumping", EInputType::Holding, [this]()
        {
            if ((jumpLock == 1 && GameplayStatics::GetTimeSeconds() - lastJumpTime < 0.5f)
                || (jumpLock == 2) && GameplayStatics::GetTimeSeconds() - lastJumpTime < 0.5f)
            {
				isonGround = false; // 标记玩家不在地面上
                // 如果在跳跃状态且跳跃时间小于0.5秒
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
                isonGround = false; // 标记玩家不在地面上
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); // 重置垂直速度
                // 切换到站立动画
                //ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);

                //
                //
            }
            else if (jumpLock == 2)
            {
                // 如果跳跃结束
                isonGround = false; // 标记玩家不在地面上
                jumpLock = 0; // 重置跳跃锁
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); // 重置垂直速度
                // 切换到站立动画
                //ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);
            }
			else return; // 如果没有跳跃，则不做任何操作
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

    inputComponent->BindAction("Dash", EInputType::Pressed, [this]()
        {
            if (GameplayStatics::GetTimeSeconds() - lastDashTime > 0.5f)
            {
				lastDashTime = GameplayStatics::GetTimeSeconds(); // 更新上次冲刺时间
				isDashing = true; // 标记正在冲刺
				rigid->SetVelocity({ rigid->GetVelocity().x, 0}); // 冲刺时增加水平速度
				rigid->SetGravityEnabled(false); // 禁用重力
            }
        }
    );

    inputComponent->BindAction("Heal", EInputType::Pressed, [this]()
        {
            if (playerProperty && playerProperty->GetHealth() < playerProperty->GetMaxHealth())
            {
                AddHealth(5); // 恢复5点生命值
                // 可以在这里添加恢复生命的特效或音效
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
    if (GetHealth() <= 0)
    {
        return;
    }

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
    if (GetHealth() <= 0)
    {
        return;
    }
    // 例如，可以检查碰撞的类型并执行相应的操作
    if (normalImpulse.y < 0)
    {
        isonGround = true; // 标记玩家在地面上
    }
}

int32 Player::GetHealth() const
{
    return playerProperty->GetHealth();
}

void Player::AddHealth(int32 delta)
{
    int32 initHealth = playerProperty->GetHealth();
    int32 realDelta = playerProperty->AddHealth(delta);

}

void Player::DieStart()
{
    EnableInput(false);
    rigid->SetMoveable(false);
    rigid->SetGravityEnabled(false);
    DieTimer.Bind(3.f, this, &Player::DieEnd);
    hurtBox->SetCollisonMode(CollisionMode::None);
}

void Player::DieEnd()
{
    rigid->SetMoveable(true);
    RecoverTimer.Bind(2.f, this, &Player::Recover);
}

void Player::Recover()
{
    EnableInput(true);
    GameplayStatics::OpenLevel("LevelB");
    SetLocalPosition({ 0,0 });
    rigid->SetVelocity({});
    AddHealth(5);
}

FDamageCauseInfo Player::TakeDamage(IDamagable* damageCauser, float baseValue, EDamageType damageType)
{
    if (blinkTimes > 0)
    {
        return {};
    }
    FDamageCauseInfo damageInfo = damageResponse->TakeDamage(damageCauser, baseValue, damageType);
    AddHealth(-baseValue);
    return damageInfo;
}

void Player::ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)
{
    if (!extraInfo.bIsValid)
    {
        return;
    }

    if (GetHealth() <= 0)
    {
        DieStart(); return;
    }

    blinkTimes = 10;
    isDashing = false;

    rigid->SetGravityEnabled(true);
    rigid->SetVelocity({0,0});
    Actor* causer = Cast<Actor>(extraInfo.damageCauser);
    CHECK_PTR(causer)
    rigid->AddImpulse({ (GetWorldPosition() - causer->GetWorldPosition()).GetSafeNormal().x * 200,-200 });
    hurtBox->SetCollisonMode(CollisionMode::None);
    box->SetCollisionResponseToType(CollisionType::Bullet, false);
}

PropertyComponent* Player::GetProperty()
{
    if (!playerProperty)
    {
        playerProperty = ConstructComponent<PlayerPropertyComponent>();
    }
    return Cast<PropertyComponent>(playerProperty);
}

void Player::ExecuteDamageDealtEvent(FDamageCauseInfo extraInfo)
{
    
}