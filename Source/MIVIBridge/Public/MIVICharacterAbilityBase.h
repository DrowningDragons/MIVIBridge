// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MIVICharacterBase.h"
#include "AbilitySystemInterface.h"
#include "MIVICharacterAbilityBase.generated.h"

class UVIAbilitySystemComponent;

/**
 * Adds a UVIAbilitySystemComponent to your character base
 * Allows switching replication mode in Blueprint for the sake of AI using Minimal instead of Mixed
 */
UCLASS()
class MIVIBRIDGE_API AMIVICharacterAbilityBase : public AMIVICharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = Abilities)
	UVIAbilitySystemComponent* AbilitySystem;

protected:
	/**
	 * Used by blueprints to allow changing replication mode which is usually
	 * only accessible via C++
	 * 
	 * Recommended as follows:
	 * For player characters use Mixed
	 * For AI characters use Minimal
	 */
	UPROPERTY(EditDefaultsOnly, Category = Abilities)
	EVIGameplayEffectReplicationMode AbilitySystemReplicationMode;

public:
	AMIVICharacterAbilityBase(const FObjectInitializer& OI);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif  // WITH_EDITOR

protected:
	// *********************************************** //
	// ******** Begin IAbilitySystemInterface ******** //
	// *********************************************** //

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// *********************************************** //
	// ********* End IAbilitySystemInterface ********* //
	// *********************************************** //
};
