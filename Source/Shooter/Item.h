// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum  class EItemRarity : uint8
{
	EIR_Damaged UMETA(DisplayName = "Damaged"),
	EIR_Common UMETA(DisplayName = "Common"),
	EIR_Uncommon UMETA(DisplayName = "Uncommon"),
	EIR_Rare UMETA(DisplayName = "Rare"),
	EIR_Legendary UMETA(DisplayName = "Legendary"),

	EIR_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum  class EItemState : uint8
{
	EIS_Pickup UMETA(DisplayName = "Pickup"),
	EIS_EquipInterping UMETA(DisplayName = "EquipInterping"),
	EIS_PickedUp UMETA(DisplayName = "PickedUp"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_Falling UMETA(DisplayName = "Falling"),

	EIS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum  class EItemType : uint8
{
	EIT_Ammo UMETA(DisplayName = "Ammo"),
	EIT_Weapon UMETA(DisplayName = "Weapon"),

	EIT_MAX UMETA(DisplayName = "DefaultMAX"),
};

UCLASS()
class SHOOTER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when overlapping AreaSphere
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when end overlapping AreaSphere
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Sets the ActiveStars array of bools based on rarity
	void SetActiveStars();

	// Sets properties of the items components based on item state
	virtual void SetItemProperties(EItemState State);

	// Called when ItemInterpTimer is finished
	void FinishInterping();

	// Handles item interpolation when in the EquipInterping state
	void ItemInterp(float DeltaTime);

	// Get interp location based on the Item type
	FVector GetInterpLocation();

	void PlayPickupSound();

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called in AShooterCharacter::GetPickupItem
	void PlayEquipSound();

private:
	// Skeletal mesh for the item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	USkeletalMeshComponent* ItemMesh;
	
	// Line trace collides with box to show HUD widgets
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	class UBoxComponent* CollisionBox;

	// Pop up widget for when the player looks at the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	class UWidgetComponent* PickupWidget;

	// Enables item tracing when overlapped
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	class USphereComponent* AreaSphere;

	// Name which appears on the pickup widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	FString ItemName;

	// Item count (Ammo, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Item Properties", meta=(AllowPrivateAccess= "True"))
	int32 ItemCount;

	// Item rarity - determines number of stars in pickup widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess= "True"))
	EItemRarity ItemRarity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess= "True"))
	TArray<bool> ActiveStars;

	// State of the Item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	EItemState ItemState;

	// The curve asset to use for the item's Z location when interping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	class UCurveFloat* ItemZCurve;

	// Starting location when interping begins
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	FVector ItemInterpStartLocation;

	// Target interp location in front of camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	FVector CameraTargetLocation;

	// True when interping
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	bool bInterping;

	// Plays when we start interping
	FTimerHandle ItemInterpTimer;

	// Pointer to the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	class AShooterCharacter* Character;

	// Duration of the curve and timer
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	float ZCurveTime;

	// X and Y for Item while interping in the EquipInterping state
	float ItemInterpX;
	float ItemInterpY;

	// Initial Yaw offset between the Camera and the inerping item
	float InterpInitialYawOffset;

	// Curve used to scale the item when interping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	UCurveFloat* ItemScaleCurve;

	// Sound played when Item is picked up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	class USoundCue* PickupSound;

	// Sound played when the Item is Equipped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	USoundCue* EquipSound;

	// Enum for the type of item this Item is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	EItemType ItemType;

	// Index of the interp location this item is interping to
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item Properties", meta=(AllowPrivateAccess = "True"))
	int32 InterpLocationIndex;

public:
	FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget;}
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere;}
	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox;}
	FORCEINLINE EItemState GetItemState() const { return ItemState;}
	void SetItemState(EItemState State);
	FORCEINLINE USkeletalMeshComponent* GetItemMesh() const { return ItemMesh;}
	FORCEINLINE USoundCue* GetPickupSound() const { return PickupSound;}
	FORCEINLINE USoundCue* GetEquipSound() const { return EquipSound;}
	FORCEINLINE int32 GetItemCount() const { return ItemCount; }

	// Called from AShooterCharacter class
	void StartItemCurve(AShooterCharacter* Char);
};
