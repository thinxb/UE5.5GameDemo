#include "Character/LootPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);
ALootPlayerCharacter::ALootPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//pawn属性设置 当控制器旋转时，不要进行旋转操作。让控制器的旋转只影响摄像机即可。
	// bUseControllerRotationPitch = false;
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;
	
	//胶囊体设置
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);//胶囊大小
	//GetCharacterMovement()->bOrientRotationToMovement = true; // 让角色的朝向（Yaw） 自动跟随其移动方向旋转。
	
	// 设置角色跟随移动方向旋转的速度。这里的 Yaw（偏航）轴为 500 度/秒，Pitch 和 Roll 为 0
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;//跳跃初始速度
	GetCharacterMovement()->AirControl = 0.35f;//控制角色在空中时对水平方向输入的响应程度
	GetCharacterMovement()->MaxWalkSpeed = 300.f;//最大行走速度
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;//最小输入行走速度
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;//移动减速速率
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;//下落减速速率
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));//创建摄像机弹簧臂组件
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // 弹簧臂距离	
	CameraBoom->bUsePawnControlRotation = true; //根据控制器转动弹
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);//绑定到指定插槽
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ALootPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALootPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALootPlayerCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	
	//添加输入映射上下文
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext,0);
			}
		}
	}
}

// Called to bind functionality to input
void ALootPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//设置绑定操作
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jump
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&ACharacter::StopJumping);
		}

		//Move
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ALootPlayerCharacter::Input_Move);
		}
		
		//Look
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ALootPlayerCharacter::Input_Look);
		}
		
		//Sneak
		if (SneakAction)
		{
			EnhancedInputComponent->BindAction(SneakAction,ETriggerEvent::Started,this,&ALootPlayerCharacter::Input_Sneak_Started);
			EnhancedInputComponent->BindAction(SneakAction,ETriggerEvent::Completed,this,&ALootPlayerCharacter::Input_Sneak_Completed);
		}
		
		//sprint
		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Started,this,&ALootPlayerCharacter::Input_Sprint_Started);
			EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Completed,this,&ALootPlayerCharacter::Input_Sprint_Completed);
		}
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' 未能找到增强型输入组件."), *GetNameSafe(this));
	}
	
	
}



void ALootPlayerCharacter::Input_Move(const FInputActionValue& Value)
{
	//从 Value 中提取二维向量
	FVector2D MovementVector = Value.Get<FVector2D>(); 
	
	if (Controller!=nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();//获取控制器的旋转角度
		const FRotator YawRotation(0,Rotation.Yaw,0);
		
		//获取前后向量
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		//获取左右向量
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); 
		
		//根据输入值添加移动
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		
	}
}

void ALootPlayerCharacter::Input_Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//添加旋转量
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALootPlayerCharacter::Input_Sneak_Started(const FInputActionValue& Value)
{
	if (bSneakIsToggle)
	{
		//切换模式
		bSneakActive = !bSneakActive;
		SetGaitState(bSneakActive ? EGaitState::Sneak : EGaitState::Walk);//静步与行走来回切换
		if (bSprintActive)
		{
			bSprintActive = false;
		}
	}
	else
	{
		//按住模式
		bSneakActive = true;
		SetGaitState(EGaitState::Sneak);

	}
}

void ALootPlayerCharacter::Input_Sneak_Completed(const FInputActionValue& Value)
{
	//只有是按住模式 松开按键时关闭
	if (!bSneakIsToggle)
	{
		bSneakActive = false;
		SetGaitState(EGaitState::Walk);
		if (bSprintActive)
		{
			bSprintActive = false;
		}
	}
}

void ALootPlayerCharacter::Input_Sprint_Started(const FInputActionValue& Value)
{
	if (bSprintIsToggle)
	{
		//切换模式
		bSprintActive = !bSprintActive;
		SetGaitState(bSprintActive ? EGaitState::Sprint : EGaitState::Walk);//冲刺与行走来回切换
		if (bSneakActive)
		{
			bSneakActive = false;
		}
	}
	else
	{
		//按住模式
		bSprintActive = true;
		SetGaitState(EGaitState::Sprint);

	}
}

void ALootPlayerCharacter::Input_Sprint_Completed(const FInputActionValue& Value)
{
	if (!bSprintIsToggle)
	{
		bSprintActive = false;
		SetGaitState(EGaitState::Walk);
		if (bSneakActive)//重置其他状态
		{
			bSneakActive = false;
		}
	}
}
void ALootPlayerCharacter::SetGaitState(EGaitState NewGait)
{
	if (CurrentGaitState  == NewGait) return;;
	
	CurrentGaitState = NewGait;
	
	float TargetSpeed = WalkSpeed;

	// 状态名称  调试
	FString StateName;
	
	switch (CurrentGaitState) {
	case EGaitState::Sneak: TargetSpeed = SneakSpeed;
		StateName = TEXT("静步");
		break;
	case EGaitState::Walk:TargetSpeed = WalkSpeed;
		StateName = TEXT("步行");
		break;
	case EGaitState::Sprint:TargetSpeed = SprintSpeed;
		StateName = TEXT("冲刺");
		break;
	}
	GetCharacterMovement()->MaxWalkSpeed = TargetSpeed;
	//GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,FString::Printf(TEXT("状态: %s"),*StateName));
	//GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Cyan,FString::Printf(TEXT("速度: %f"),TargetSpeed));
}
