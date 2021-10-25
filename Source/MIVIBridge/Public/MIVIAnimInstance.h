// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MIAnimInstance.h"
#include "VITypes.h"
#include "Animation/VIAnimationInterface.h"
#include "MIVIAnimInstance.generated.h"

class AMIVICharacterBase;

/**
 * 
 */
UCLASS()
class MIVIBRIDGE_API UMIVIAnimInstance : public UMIAnimInstance, public IVIAnimationInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FBIK)
	FName RHandName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FBIK)
	FName LHandName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FBIK)
	TArray<FVIBoneFBIKData> FBIK;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FBIK, meta = (DisplayName = "R Hand"))
	bool bRHand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FBIK, meta = (DisplayName = "L Hand"))
	bool bLHand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FBIK)
	bool bBothHand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FBIK, meta = (DisplayName = "R Hand Loc"))
	FVector RHandLoc;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FBIK, meta = (DisplayName = "L Hand Loc"))
	FVector LHandLoc;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Vault)
	bool bIsVaulting;

protected:
	UPROPERTY(BlueprintReadWrite, Category = References)
	AMIVICharacterBase* VaultCharacter;

public:
	UMIVIAnimInstance()
		: RHandName(TEXT("hand_r"))
		, LHandName(TEXT("hand_l"))
		, FBIK( { FVIBoneFBIKData(RHandName), FVIBoneFBIKData(LHandName) } )
	{}

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	virtual void OnStartVault() {}
	virtual void OnStopVault();

public:
	/**
	 * Called by anim notify when a bone has its location updated for FBIK
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Vault)
	void SetBoneFBIK(const FName& BoneName, const FVector& BoneLocation, bool bEnabled);
};
