// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MIVIAnimInstance.h"
#include "MIVIAnimInstanceFP.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class MIVIBRIDGE_API UMIVIAnimInstanceFP : public UMIVIAnimInstance
{
	GENERATED_BODY()
	
public:
	/**
	 * Key: ThirdPersonMontage
	 * Value: FirstPersonMontage that is played corresponding to the ThirdPersonMontage
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Vault)
	TMap<UAnimMontage*, UAnimMontage*> MontageLinkMap;

protected:
	UPROPERTY()
	UAnimMontage* MontageToPlay;

	UPROPERTY()
	float VaultBlendOutTime;

protected:
	bool CanPlayFPMontage() const;

public:
	virtual void OnStartVault() override;
	virtual void OnStopVault() override;
};
