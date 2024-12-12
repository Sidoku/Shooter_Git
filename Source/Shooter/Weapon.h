// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoType.h"
#include "Item.h"
#include "Engine/DataTable.h"
#include "WeaponType.h"
#include "Weapon.generated.h"

USTRUCT()
struct FWeaponDataTable : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundCue* PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* EquipSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* AmmoIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* MaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaterialIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ClipBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ReloadMontageSection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> AnimBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairMiddle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AutoFireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* FireSound;
};
/**
 * 
 */
UCLASS()
class SHOOTER_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	
protected:
	
	void StopFalling();

	virtual void OnConstruction(const FTransform& Transform) override;
	
private:
	FTimerHandle ThrowWeaponTimer;
	float ThrowWeaponTime;
	bool bFalling;

	// Ammo count for this weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon Properties", meta=(AllowPrivateAccess = "True"))
	int32 Ammo;

	// Maximum Ammo that our weapon can hold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon Properties", meta=(AllowPrivateAccess = "True"))
	int32 MagazineCapacity;

	// The type of Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon Properties", meta=(AllowPrivateAccess = "True"))
	EWeaponType WeaponType;

	// The type of Ammo for this Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon Properties", meta=(AllowPrivateAccess = "True"))
	EAmmoType AmmoType;

	// FName for the reload montage section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon Properties", meta=(AllowPrivateAccess = "True"))
	FName ReloadMontageSection;

	// True when moving the clip while reloading
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Weapon Properties", meta=(AllowPrivateAccess = "True"))
	bool bMovingClip;

	// name for the clip bone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon Properties", meta=(AllowPrivateAccess = "True"))
	FName ClipBoneName;

	// Data table for weapon properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	UDataTable* WeaponDataTable;

	int32 PreviousMaterialIndex;
	
	// Textures for the weapon crosshair
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	UTexture2D* CrosshairMiddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	UTexture2D* CrosshairRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	UTexture2D* CrosshairLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	UTexture2D* CrosshairTop;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	UTexture2D* CrosshairBottom;

	// The speed at which automatic fire happens
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	float AutoFireRate;

	// Particle system spawned at BarrelSocket 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	class UParticleSystem* MuzzleFlash;

	// Sound played when the weapon is fired
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= DataTable, meta=(AllowPrivateAccess = "True"))
	USoundCue* FireSound;
	
public:
	// Adds an impulse to the weapon
	void ThrowWeapon();

	FORCEINLINE int32 GetAmmo() const { return Ammo;}

	FORCEINLINE int32 GetMagazineCapacity() const { return MagazineCapacity;}
	
	// Called from Character class when firing weapon
	void DecrementAmmo();

	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType;}

	FORCEINLINE EAmmoType GetAmmoType() const { return AmmoType;}

	FORCEINLINE FName GetReloadMontageSection() const { return ReloadMontageSection;}

	FORCEINLINE void SetReloadMontageSection(FName Name) { ReloadMontageSection = Name;}

	void ReloadAmmo(int32 Amount);

	FORCEINLINE FName GetClipBoneName() const { return ClipBoneName;}

	FORCEINLINE void SetClipBoneName(FName Name) { ClipBoneName = Name;}

	FORCEINLINE void SetMovingClip(bool Move) { bMovingClip = Move;}

	FORCEINLINE float GetAutoFireRate() const { return AutoFireRate;}

	FORCEINLINE UParticleSystem* GetMuzzleFlash() const { return MuzzleFlash;}

	FORCEINLINE USoundCue* GetFireSound() const { return FireSound;}

	bool ClipIsFull();
};
