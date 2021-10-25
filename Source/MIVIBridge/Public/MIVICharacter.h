// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MIVICharacterAbilityBase.h"
#include "MIVICharacter.generated.h"

/**
 * 
 */
UCLASS()
class MIVIBRIDGE_API AMIVICharacter : public AMIVICharacterAbilityBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = Vault)
	FVIAnimSet VaultAnimSet;

	UPROPERTY(EditDefaultsOnly, Category = Vault)
	FVITraceSettings VaultTraceSettings;

public:
	AMIVICharacter(const FObjectInitializer& OI);

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;

	virtual UVIPawnVaultComponent* GetPawnVaultComponent_Implementation() const override { return VaultComponent; }
	virtual UVIMotionWarpingComponent* GetMotionWarpingComponent_Implementation() const override { return MotionWarping; }

	virtual FVIAnimSet GetVaultAnimSet_Implementation() const override { return VaultAnimSet; }
	virtual FVITraceSettings GetVaultTraceSettings_Implementation() const override { return VaultTraceSettings; }
};
