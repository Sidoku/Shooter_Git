// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EOffsetState : uint8
{
	EOS_Aiming UMETA(DisplayName = "Aiming"),
	EOS_Hip UMETA(DisplayName = "Hip"),
	EOS_Reloading UMETA(DisplayName = "Reloading"),
	EOS_InAir UMETA(DisplayName = "InAir"),
	
	EOS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class SHOOTER_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UShooterAnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);
	
	virtual void NativeInitializeAnimation() override;

protected:
	
	// Handle Turning in place variables
	void TurnInPlace();

	// Handle calculations for leaning while running
	void Lean(float DeltaTime);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Movement, meta=(AllowPrivateAccess = "True"))
	class AShooterCharacter* ShooterCharacter;

	// Speed of the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Movement, meta=(AllowPrivateAccess= "True"))
	float Speed;

	// Is the character in the air
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Movement, meta=(AllowPrivateAccess= "True"))
	bool bIsInAir;

	// Is the character moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Movement, meta=(AllowPrivateAccess= "True"))
	bool bIsAccelerating;

	// Offset yaw used for strafing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Movement, meta=(AllowPrivateAccess= "True"))
	float MovementOffsetYaw;
	
	// Offset yaw the frame before we stopped moving used for strafing
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Movement, meta=(AllowPrivateAccess= "True"))
	float LastMovementOffsetYaw;

	// Is the character aiming downsight?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Movement, meta=(AllowPrivateAccess= "True"))
	bool bAiming;

	// Yaw of the character this frame, only updated when standing still and not in air
	float TIPCharacterYaw;

	// Yaw of the Character the previous frame, only updated when standing still and not in air
	float TIPCharacterYawLastFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Turn In Place", meta=(AllowPrivateAccess = "True"))
	float RootYawOffset;

	// Rotation curve value this frame
	float RotationCurve;

	// Rotation curve value last frame
	float RotationCurveLastFrame;

	// Pitch of the aim rotation used for aim offset
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Turn In Place", meta=(AllowPrivateAccess = "True"))
	float Pitch;

	// True when reloading, used to prevent aim offset while reloading
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Turn In Place", meta=(AllowPrivateAccess = "True"))
	bool bReloading;

	// Offset state used to determine which offset state to use
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Turn In Place", meta=(AllowPrivateAccess = "True"))
	EOffsetState OffsetState;

	// Character Rotation this frame
	FRotator CharacterRotation;

	// Character Rotation last frame
	FRotator CharacterRotationLastFrame;

	// Yaw delta used for leaning in the running blend space
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Lean, meta=(AllowPrivateAccess = "True"))
	float YawDelta;

	// True when crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Crouching, meta=(AllowPrivateAccess = "True"))
	bool bCrouching;

	// Change the recoil weight based on turning in place and aiming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Combat, meta=(AllowPrivateAccess = "True"))
	float RecoilWeight;

	// True when turning in place
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Crouching, meta=(AllowPrivateAccess = "True"))
	bool bTurningInPlace;
};
