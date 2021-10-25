// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MICharacter.h"
#include "VITypes.h"
#include "Pawn/VIPawnInterface.h"
#include "MIVICharacterBase.generated.h"

class UVIMotionWarpingComponent;
class UVIPawnVaultComponent;

/**
 * An incomplete character base class
 * Needs to inherit from IAbilitySystemInterface and implement a UVIAbilitySystemComponent
 * @see: AVICharacterAbilityBase where this is done for you
 *
 * Requires multiple overrides which will cause errors if not correctly performed
 */
UCLASS(abstract)
class MIVIBRIDGE_API AMIVICharacterBase : public AMICharacter, public IVIPawnInterface
{
	GENERATED_BODY()
	
public:
	/**
	 * Motion Warping Component used for vaulting
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	UVIMotionWarpingComponent* MotionWarping;

	/**
	 * Pawn Vault Component used for core vaulting logic
	 * 
	 * This is added in Blueprint and must be returned via
	 * the IVIPawnInterface::GetPawnVaultComponent function
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	UVIPawnVaultComponent* VaultComponent;

protected:
	/** Simulated proxies use this to update their vaulting state based on server values */
	UPROPERTY(Replicated, BlueprintReadWrite, Category = Vault)
	bool bRepIsVaulting;

	/** Used to detect changes in vaulting state and call StopVaultAbility() */
	UPROPERTY()
	bool bWasVaulting;

	/** 
	 * Simulated proxies use this to reproduce motion matching results provided
	 * by server in the GA_Vault gameplay ability
	 *
	 * Local players use this as a cache for FBIK testing (returned via GetVaultLocationAndDirection)
	 * 
	 * Net Serialized to one decimal point of precision
	 */
	UPROPERTY(ReplicatedUsing="OnRep_MotionMatch", BlueprintReadWrite, Category = Vault)
	FVIRepMotionMatch RepMotionMatch;

public:
	virtual void BeginPlay() override;

	virtual void CheckJumpInput(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void Jump() override;
	virtual void StopJumping() override;

	/** Called from gameplay ability when vault stops */
	UFUNCTION(BlueprintCallable, Category = Vault)
	void StopVaultAbility();

	UFUNCTION(BlueprintImplementableEvent, Category = Vault)
	void OnStopVaultAbility();

protected:
	UFUNCTION()
	void OnRep_MotionMatch();

public:
	/**
	 * @return True if vaulting
	 * Correct value must be returned based on net role here
	 * Simulated proxies return bRepIsVaulting
	 * Server & Authority must return CMC bIsVaulting
	 */
	UFUNCTION(BlueprintPure, Category = Vault)
	virtual bool IsVaulting() const;

	virtual bool CanHitCharacter_Implementation() const override { return !IsVaulting(); }
	virtual bool CanHitWall_Implementation() const override { return !IsVaulting(); }

	// *********************************************** //
	// *********** Begin IVIPawnInterface ************ //
	// *********************************************** //

	// Read VIPawnInterface.h for detailed descriptions of these functions or look
	// inside their functions themselves

	virtual UVIPawnVaultComponent* GetPawnVaultComponent_Implementation() const override;
	virtual UVIMotionWarpingComponent* GetMotionWarpingComponent_Implementation() const override;
	virtual USkeletalMeshComponent* GetMeshForVaultMontage_Implementation() const override { return GetMesh(); }
	virtual FVIAnimSet GetVaultAnimSet_Implementation() const override;
	virtual FVITraceSettings GetVaultTraceSettings_Implementation() const override;
	virtual FVector GetVaultDirection_Implementation() const override;
	virtual bool CanVault_Implementation() const override;
	virtual void StartVaultAbility_Implementation() override;
	virtual void OnLocalPlayerVault_Implementation(const FVector& Location, const FVector& Direction) override;
	virtual void GetVaultLocationAndDirection_Implementation(FVector& OutLocation, FVector& OutDirection) const override;
	virtual void ReplicateMotionMatch_Implementation(const FVIRepMotionMatch& MotionMatch) override;
	virtual bool IsWalkable_Implementation(const FHitResult& HitResult) const override;
	virtual bool CanAutoVaultInCustomMovementMode_Implementation() const override;

	// *********************************************** //
	// ************* End IVIPawnInterface ************ //
	// *********************************************** //
};
