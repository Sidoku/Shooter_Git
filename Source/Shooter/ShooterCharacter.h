// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AmmoType.h"
#include "ShooterCharacter.generated.h"

UENUM(BlueprintType)
enum class ECombatState: uint8
{
	ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECS_FireTimerInProgress UMETA(DisplayName = "FireTimerInProgress"),
	ECS_Reloading UMETA(DisplayName = "Reloading"),

	ECS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called for forward/backward input
	void MoveForward( float Value);

	// Called for side to side input
	void MoveRight( float Value);

	/*
	 * Called via Input to turn at a given rate
	 * @param Rate This is a normalized rate, i.e, 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/*
	 * Called via Input to look up/down at a given rate
	 *  @param Rate This is a normalized rate, i.e, 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/*Rotate controller based on mouse X movement
	 * @param Value The input value from mouse movement
	 */
	void Turn(float Value);

	/*Rotate controller based on mouse Y movement
	 * @param Value The input value from mouse movement
	 */
	void LookUp(float Value);

	// Called when the fire button is pressed.
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	void AimingButtonPressed();

	void AimingButtonReleased();

	void SetCameraFOV(float DeltaTime);

	// Set base turn rate and base look up rate based on aiming
	void SetLookRates();

	void CalculateCrosshairSpread(float DeltaTime);

	void StartCrosshairBulletFire();
	
	UFUNCTION()
	void FinishCrosshairBulletFire();

	void FireButtonPressed();

	void FireButtonReleased();

	void StartFireTimer();

	UFUNCTION()
	void AutoFireReset();

	// Line trace for items under the crosshairs
	bool TraceUnderCrosshairs(FHitResult& OutHitResult, FVector& OutHitLocation);

	// Trace for items if OverlappedItemCount > 0
	void TraceForItems();

	// Spawns a default weapon
	class AWeapon* SpawnDefaultWeapon();

	// Takes a weapon and attaches it to the mesh
	void EquipWeapon(AWeapon* WeaponToEquip);

	// Detach weapon and let it fall to the ground
	void DropWeapon();

	void SelectButtonPressed();

	void SelectButtonReleased();

	// Drops currently equipped weapon and equips TraceHitItem
	void SwapWeapon(AWeapon* WeaponToSwap);

	// Initialize the ammo map with ammo values
	void InitializeAmmoMap();

	// Check to make sure our weapon has ammo
	bool WeaponHasAmmo();

	// Fire weapon functions
	void PlayFireSound();

	void SendBullet();

	void PlayGunFireMontage();

	// Bound to the R key and the Gamepad face button left
	void ReloadButtonPressed();

	// Handle realoding of the weapon
	void ReloadWeapon();

	UFUNCTION(BlueprintCallable)
	void FinishReloading();

	// Checks to see if we have ammo of the equipped weapons ammo type
	bool CarryingAmmo();

	// Called from animation blueprint with Grab clip notify
	UFUNCTION(BlueprintCallable)
	void GrabClip();

	// Called from animation blueprint with Release clip notify
	UFUNCTION(BlueprintCallable)
	void ReleaseClip();

	void CrouchButtonPressed();

	virtual void Jump() override;

	// Interps capsule half height when crouching / standing
	void InterpCapsuleHalfHeight(float DeltaTime);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Camera that follows the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Base turn rate, in deg./sec. Other scaling may affect final turn rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	// Base look up/down rate in deg./sec. Other scaling may affect final rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"))
	float BaseLookUpRate;

	// Turn rate while not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"))
	float HipTurnRate;
	
	// Look up rate when not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"))
	float HipLookUpRate;

	// Turn rate when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"))
	float AimingTurnRate;

	// Look up rate when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"))
	float AimingLookUpRate;

	// Scale factor for mouse look sensitivity. Turn rate when not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"), meta=(ClampMin= "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipTurnRate;

	// Scale factor for mouse look sensitivity. Turn rate when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"), meta=(ClampMin= "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingTurnRate;

	// Scale factor for mouse look sensitivity. Look up rate when not aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"), meta=(ClampMin= "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipLookUpRate;

	// Scale factor for mouse look sensitivity. Look up rate when aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"), meta=(ClampMin= "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingLookUpRate;
	

	// Randomized gunshot sound cure
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta=(AllowPrivateAccess = "True"))
	class USoundCue* FireSound;

	// Flash spawned at Barrel socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta=(AllowPrivateAccess = "True"))
	class UParticleSystem* MuzzleFlash;

	// Montage for firing the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta=(AllowPrivateAccess = "True"))
	class UAnimMontage* HipFireMontage;

	// Particles spawned upon bullet impact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta=(AllowPrivateAccess = "True"))
	UParticleSystem* ImpactParticles;

	// Smoke trail for bullets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta=(AllowPrivateAccess = "True"))
	UParticleSystem* BeamParticles;

	// True when aiming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta=(AllowPrivateAccess = "True"))
	bool bAiming;

	// Default Camera field of view value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Combat, meta=(AllowPrivateAccess = "True"))
	float CameraDefaultFOV;

	// Field of view value for when zoomed in.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Combat, meta=(AllowPrivateAccess = "True"))
	float CameraZoomedFOV;

	// Current field of view this frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Combat, meta=(AllowPrivateAccess = "True"))
	float CameraCurrentFOV;

	// Interp speed for zooming when aiming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Combat, meta=(AllowPrivateAccess = "True"))
	float ZoomInterpSpeed;

	// Determines the spread of the Crosshairs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Crosshairs, meta=(AllowPrivateAccess= "True"))
	float CrosshairSpreadMultiplier;

	// Velocity component for Crosshair spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Crosshairs, meta=(AllowPrivateAccess= "True"))
	float CrosshairVelocityFactor;

	// In air component for Crosshair spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Crosshairs, meta=(AllowPrivateAccess= "True"))
	float CrosshairInAirFactor;

	// Aim component for Crosshair spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Crosshairs, meta=(AllowPrivateAccess= "True"))
	float CrosshairAimFactor;

	// Shooting component for Crosshair spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Crosshairs, meta=(AllowPrivateAccess= "True"))
	float CrosshairShootingFactor;

	float ShootTimeDuration;

	bool bFiringBullet;

	FTimerHandle CrosshairShootTimer;

	// Left mouse button / Right console trigger pressed
	bool bFireButtonPressed;

	// True when we can fire, false when waiting for timer
	bool bShouldFire;

	// Rate of automatic gun fire
	float AutomaticFireRate;

	// Sets a timer between gunshots
	FTimerHandle AutoFireTimer;

	// True if we should trace every frame for items
	bool bShouldTraceForItems;

	// Number of overlapped AItems
	int8 OverlappedItemCount;

	// The AItem we hit last frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta=(AllowPrivateAccess = "True") )
	class AItem* TraceHitItemLastFrame;

	// Currently equipped weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Combat, meta=(AllowPrivateAccess = "True"))
	AWeapon* EquippedWeapon;

	// Set this in Blueprints for the default weapon class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Combat, meta=(AllowPrivateAccess = "True"))
	TSubclassOf<AWeapon> DefaultWeaponClass;

	// The item currently hit by our trace in TraceForItems ( Could be null)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Combat, meta=(AllowPrivateAccess = "True"))
	AItem* TraceHitItem;

	// Distance outward from the camera for the interp destination
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Item, meta=(AllowPrivateAccess = "True"))
	float CameraInterpDistance;

	// Distance upward from the camera for the interp destination
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Item, meta=(AllowPrivateAccess = "True"))
	float CameraInterpElevation;

	// Map to keep track of ammo of different ammo types
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Item, meta=(AllowPrivateAccess = "True"))
	TMap<EAmmoType, int32> AmmoMap;

	// Starting Amount of 9mm ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Item, meta=(AllowPrivateAccess = "True"))
	int32 Starting9mmAmmo;

	// Starting amount of AR ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Item, meta=(AllowPrivateAccess = "True"))
	int32 StartingARAmmo;

	// Combat State, can only fire or reload if Unoccupied
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta=(AllowPrivateAccess = "True"))
	ECombatState CombatState;

	// Montage for reload animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta=(AllowPrivateAccess = "True"))
	UAnimMontage* ReloadMontage;

	// Transform of the clip when we first grab the clip when reloading
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta=(AllowPrivateAccess = "True"))
	FTransform ClipTransform;

	// Scene component to attach to the Character's hand during reloading
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta=(AllowPrivateAccess = "True"))
	USceneComponent* HandSceneComponent;

	// True when crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Movement, meta=(AllowPrivateAccess = "True"))
	bool bCrouching;

	// Regular Movement speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Movement, meta=(AllowPrivateAccess = "True"))
	float BaseMovementSpeed;

	// Crouch Movement speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Movement, meta=(AllowPrivateAccess = "True"))
	float CrouchMovementSpeed;

	// Current half height of the capsule
	float CurrentCapsuleHalfHeight;

	// Half height of the capsule when not crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= Movement, meta=(AllowPrivateAccess = "True"))
	float StandingCapsuleHalfHeight;

	// Half Height of the capsule when crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= Movement, meta=(AllowPrivateAccess = "True"))
	float CrouchingCapsuleHalfHeight;

	// Ground friction while not crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= Movement, meta=(AllowPrivateAccess = "True"))
	float BaseGroundFriction;

	// Ground friction while crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= Movement, meta=(AllowPrivateAccess = "True"))
	float CrouchingGroundFriction;
	
public:
	// Returns CameraBoom subobject
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool GetAiming() const { return bAiming; }

	UFUNCTION(BlueprintCallable)
	float GetCrosshairSpreadMultiplier() const;

	FORCEINLINE int8 GetOverlappedItemCount() const { return OverlappedItemCount; }

	// Adds / Subtracts to / from OverlappedItemCount and updates bShouldTraceForItems
	void IncrememntOverlappedItemCount(int8 Amount);

	FVector GetCameraInterpLocation();

	void GetPickupItem(AItem* Item);

	FORCEINLINE ECombatState GetCombatState() const { return CombatState; }
	
	FORCEINLINE bool GetCrouching() const { return bCrouching;}
};
