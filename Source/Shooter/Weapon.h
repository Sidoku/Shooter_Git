// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoType.h"
#include "Item.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType: uint8
{
	EWT_SubmachineGun UMETA(DisplayName = "SubmachineGun"),
	EWT_AssaultRifle UMETA(DisplayName = "AssaultRifle"),
	
	EWT_MAX UMETA(DisplayName = "DefaultMAX")
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

	void ReloadAmmo(int32 Amount);

	FORCEINLINE FName GetClipBoneName() const { return ClipBoneName;}

	FORCEINLINE void SetMovingClip(bool Move) { bMovingClip = Move;}

	bool ClipIsFull();
};
