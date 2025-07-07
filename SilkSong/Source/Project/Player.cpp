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
    //      PlayerAnimator    
    ani = ConstructComponent<PlayerAnimator>();
    ////    PlayerAnimator     Ⱦ      
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

    lastJumpTime = 0.0f; //   ʼ   ϴ   Ծʱ   .
	lastDashTime = 0.0f; //   ʼ   ϴγ  ʱ   .
	lastAttackTime = 0.0f; //   ʼ   ϴι   ʱ   .
	isDashing = false; //   ʼ     ״̬Ϊ false
	isonGround = false;
	isAttacking = false; //   ʼ      ״̬Ϊ false

    blinkTimes = 0; // ޵ ֡ʱ  


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
    //   ѡ              һЩ ٶ    ƻ򶯻         
    ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);
    if (GameplayStatics::GetTimeSeconds() - lastAttackTime > 0.3f)
    {
		isAttacking = false; //  ָ     ״̬
    }

    if (isonGround && walkLock == 0 && !isDashing && GetHealth() > 0 && !isAttacking)
    {
		ani->SetNode("idle");
    }

    if (isDashing)
    {
		SetMaxWalkingSpeed(1600.f); //    ʱ            ٶ 
        AddInputX(GetWorldScale().x * 10000 * deltaTime, false);
        //       ڳ ̣     Ƿ   Ҫ       
        if (GameplayStatics::GetTimeSeconds() - lastDashTime > 0.2f)
        {
            isDashing = false; //        ״̬
            SetMaxWalkingSpeed(400.f); //  ָ         ٶ 
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
			return; //     Ѿ        ߣ             
        }
        walkLock = 1; 
        SetMaxWalkingSpeed(400.f);
        ani->SetFloat("walkingSpeed", 400.f);
        AddInputX(-3.f, true);
        if((curDirection != AttackDirection::Up) && (curDirection != AttackDirection::Down)) 
        {            
            //      ǰ         ϻ     
            //  л      ҵĹ       
            curDirection = AttackDirection::Left; //    õ ǰ    Ϊ  
		}
        else
        {
			//  ǰ         ϻ     
			lastDirection = AttackDirection::Left; //   ¼  ǰ    
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
            return; //     Ѿ        ߣ             
        }
        walkLock = 2;
        SetMaxWalkingSpeed(400.f);
        ani->SetFloat("walkingSpeed", 400.f);
        AddInputX(3.f, true);
        if ((curDirection != AttackDirection::Up) && (curDirection != AttackDirection::Down))
        {
            //      ǰ         ϻ     
            //  л      ҵĹ       
            curDirection = AttackDirection::Right; //    õ ǰ    Ϊ  
        }
        else
        {
			lastDirection = AttackDirection::Right; //   ¼  ǰ    
        }
        });
    inputComponent->BindAction("WalkRightEnd", EInputType::Released, [this]() {
        if (walkLock == 2) 
            walkLock = 0;
        ani->SetFloat("walkingSpeed", 0.f);

        });

    inputComponent->BindAction("HoldUp", EInputType::Holding, [this]()
        {
			curDirection = AttackDirection::Up; //    õ ǰ    Ϊ    
            
		});

    inputComponent->BindAction("HoldUpEnd", EInputType::Released, [this]()
        {
            if (curDirection == AttackDirection::Up)
            {
                curDirection = lastDirection; //  ָ    ϴεķ   
            }
            else return;
        });

    inputComponent->BindAction("HoldDown", EInputType::Holding, [this]()
		{
			if (!isonGround)//      Ҳ  ڵ    ϣ          ¹   
			    curDirection = AttackDirection::Down; //    õ ǰ    Ϊ    
		});

    inputComponent->BindAction("HoldDownEnd", EInputType::Released, [this]()
        {
            if (curDirection == AttackDirection::Down)
            {
                curDirection = lastDirection; //  ָ    ϴεķ   
            }
			else return; //      ǰ         £      κβ   
		});

    inputComponent->BindAction("JumpStart", EInputType::Pressed, [this]()
        {
            if ((isonGround && (jumpLock == 0)) || (jumpLock == 1))
            {
                //        ڵ     
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, -400.f)); //       Ծ
                isonGround = false; //   Ծ   ǲ  ڵ     

                //  л     Ծ    
                //ani->SetFloat("jumpSpeed", -1.f);
                //ani->PlayMontage("jump1");
                //
                //
                lastJumpTime = GameplayStatics::GetTimeSeconds(); //   ¼  Ծʱ  
                jumpLock ++; //       Ծ      ֹ      Ծ,jumpLock = 1      Ѿ   ʼ  Ծ     ǻ û      Ծ
            }  
			else return; //       ڵ    ϣ         Ծ
        });

    inputComponent->BindAction("Jumping", EInputType::Holding, [this]()
        {
            if ((jumpLock == 1 && GameplayStatics::GetTimeSeconds() - lastJumpTime < 0.5f)
                || (jumpLock == 2) && GameplayStatics::GetTimeSeconds() - lastJumpTime < 0.5f)
            {
				isonGround = false; //      Ҳ  ڵ     
                //        Ծ״̬    Ծʱ  С  0.5  
				rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, -400.f)); //       һ     ϵ  ٶ 
                //   Ծ    
                //ani->SetFloat("jumpSpeed", -1.f);
                //
                //
                ///*
                if (jumpLock == 1)
                {
                    ani->SetNode("player_jump_1"); //  л     Ծ    
                }
                else if (jumpLock == 2)
                {
                    ani->SetNode("player_jump_2"); //  л     Ծ    
                }
                //*/
            }
		});

    inputComponent->BindAction("JumpEnd", EInputType::Released, [this]()
        {
            if (jumpLock == 1)
            {
                //      Ծ    
                isonGround = false; //      Ҳ  ڵ     
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); //    ô ֱ ٶ 
                //  л   վ      
                //ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);
				ani->SetNode("player_jump_falling"); //  л     Ծ   �? 
                //
                //
            }
            else if (jumpLock == 2)
            {
                //      Ծ    
                isonGround = false; //      Ҳ  ڵ     
                jumpLock = 0; //       Ծ  
                rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); //    ô ֱ ٶ 
                //  л   վ      
                //ani->SetFloat("fallingSpeed", rigid->GetVelocity().y);
            }
			else return; //    û    Ծ       κβ   
		});

    inputComponent->BindAction("Attack", EInputType::Pressed, [this]()
        {
            if (lastAttackTime == 0 || GameplayStatics::GetTimeSeconds() - lastAttackTime > 0.3f)
            {
                //     ϴι   ʱ �? 0.5  
                lastAttackTime = GameplayStatics::GetTimeSeconds(); //      ϴι   ʱ  
				isAttacking = true; //       ڹ   
                // ִ й    ߼ 
                //
                //
                //
				AttackBox* attackBox = GameplayStatics::CreateObject<AttackBox>();
                attackBox->AttachTo(this);
                switch (curDirection)
                {
                    case AttackDirection::Left:
                        attackBox->Init(AttackDirection::Left);
                        attackBox->SetLocalPosition(FVector2D(25, 0));
						ani->SetNode("player_attack1");
						break;
                    case AttackDirection::Right:
                        attackBox->Init(AttackDirection::Right);
						attackBox->SetLocalPosition(FVector2D(25, 0));
						ani->SetNode("player_attack1");
                        break;
                    case AttackDirection::Up:
						attackBox->Init(AttackDirection::Up);
                        if (lastDirection == AttackDirection::Left)
                        {
                            attackBox->SetLocalPosition(FVector2D(-15, 0));
                        }
                        else if (lastDirection == AttackDirection::Right)
                        {
                            attackBox->SetLocalPosition(FVector2D(-15, 0));
						}
                        else
                        {
                            attackBox->SetLocalPosition(FVector2D(0, 0));
						}

						ani->SetNode("player_attack2");
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
				lastDashTime = GameplayStatics::GetTimeSeconds(); //      ϴγ  ʱ  
				isDashing = true; //       ڳ  
				rigid->SetVelocity({ rigid->GetVelocity().x, 0}); //    ʱ    ˮƽ ٶ 
				rigid->SetGravityEnabled(false); //         
            }
        }
    );

    inputComponent->BindAction("Heal", EInputType::Pressed, [this]()
        {
            if (playerProperty && playerProperty->GetHealth() < playerProperty->GetMaxHealth())
            {
                AddHealth(5); //  ָ 5      ֵ
                //              ӻָ         Ч    Ч
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

	//      ײ  ʼ   ߼ 
    if (normalImpulse.y < 0 && rigid && rigid->GetVelocity().y > 0)
    {
        //      ײ Ǵ  Ϸ      ģ                 ƶ 
		isonGround = true; //        ڵ     
        rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); //    ô ֱ ٶ 
        // ˴     վ      

    }
    else if (normalImpulse.y > 0 && rigid && rigid->GetVelocity().y < 0)
    {
        //      ײ Ǵ  ·      ģ                 ƶ 
		isonGround = false; //      Ҳ  ڵ     
        rigid->SetVelocity(FVector2D(rigid->GetVelocity().x, 0)); //    ô ֱ ٶ 
	}
    
}

void Player::StayCollision(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult)
{
    //      �?       ײ   ߼ 
    if (GetHealth() <= 0)
    {
        return;
    }
    //    �?  Լ    ײ     Ͳ ִ    Ӧ Ĳ   
    if (normalImpulse.y < 0)
    {
        isonGround = true; //        ڵ     
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
    int32 currentHealth = playerProperty->GetHealth();
    int32 maxHealth = playerProperty->GetMaxHealth();
    ui->Update(currentHealth, maxHealth);

}

void Player::DieStart()
{
    EnableInput(false);
    rigid->SetMoveable(false);
    rigid->SetGravityEnabled(false);
    DieTimer.Bind(3.0f, this, &Player::Recover);
    hurtBox->SetCollisonMode(CollisionMode::None);
    ani->SetNode("player_die");
	//ani->SetNode("player_dead");
}


void Player::Recover()
{
    EnableInput(true);
    GameplayStatics::OpenLevel("Menu");
    SetLocalPosition({ 0,0 });
    rigid->SetMoveable(true);
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
        DieStart(); 
        return;
    }

    blinkTimes = 2;
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