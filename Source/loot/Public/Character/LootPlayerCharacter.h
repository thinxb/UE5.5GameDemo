#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LootCharacterEnums/LootCharacterEnums.h"

#include "LootPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);



UCLASS(config=Game)
class LOOT_API ALootPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ALootPlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
public:	
	// 当前移动状态变量
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|State")
	EMovementState CurrentMovementState  = EMovementState::Walk;
	
	//当前角色姿态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stance|State")
	EStance CurrentStance  = EStance::Idle;
	
	//速度配置
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Movement|Speed")
	float SneakSpeed = 150.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Movement|Speed")
	float WalkSpeed = 300.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Speed")
	float SprintSpeed = 700.f;
	
	//鼠标移动
	UPROPERTY(BlueprintReadOnly, Category = "MouseInput")
	float MouseRight = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "MouseInput")
	float MouseUp = 0.f;
	 
	// === 触发模式（后续会移到 GameInstance，这里先简单放这）===
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Movement|Settings")
	bool bSneakIsToggle = true;//静步 false按住 true切换

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Settings")
	bool bSprintIsToggle = false;//奔跑 false按住 true切换
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Settings")
	bool bCrouchToggle = true;//蹲下 false按住 true切换
	
	//设置切换移动状态
	UFUNCTION(BlueprintCallable,Category = "Movement")
	void SetMovementState(EMovementState NewGait);
	
	//获取移动状态
	UFUNCTION(BlueprintCallable, Category = "Movement")
	EMovementState GetMovementState() const { return CurrentMovementState; }
	
	//设置角色姿态
	UFUNCTION(BlueprintCallable,Category = "Movement")
	void SetStance(EStance NewStance);
	
	//获取角色姿态
	UFUNCTION(BlueprintCallable,Category = "Stance")
	EStance GetStance() const { return CurrentStance;};
	
	
	/** 返回摄像机伸缩臂子对象 **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	/** 返回跟随摄像机子对象 **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	

protected:
	// 当游戏开始或角色被生成时调用
	virtual void BeginPlay() override;
	
	/** 摄像机臂组件，用于将摄像机定位在角色后面 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** 跟随摄像机组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** 输入映射上下文 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** 跳跃输入动作 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	/** 移动输入动作 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** 视角输入动作 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	//静步输入动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SneakAction;
	
	//冲刺输入动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	
	//蹲下输入动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	
protected:
	//移动
	void Input_Move(const FInputActionValue& Value);
	
	//视角
	void Input_Look(const FInputActionValue& Value);
	
	//静步
	void Input_Sneak_Started(const FInputActionValue& Value);
	void Input_Sneak_Completed(const FInputActionValue& Value);
	
	//冲刺
	void Input_Sprint_Started(const FInputActionValue& Value);
	void Input_Sprint_Completed(const FInputActionValue& Value);
	
	//蹲下
	void Input_Crouch_Started(const FInputActionValue& Value);
	void Input_Crouch_Completed(const FInputActionValue& Value);

	
	virtual void NotifyControllerChanged() override;//增强输入

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:
	// 状态追踪
	bool bSneakActive = false;
	bool bSprintActive = false;
	bool bCrouchActive = false;
	
};
