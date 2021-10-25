// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.


#include "MIVICharacterAbilityBase.h"
#include "GAS/VIAbilitySystemComponent.h"

AMIVICharacterAbilityBase::AMIVICharacterAbilityBase(const FObjectInitializer& OI)
	: Super(OI)
{
	AbilitySystem = CreateDefaultSubobject<UVIAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AbilitySystemReplicationMode = (EVIGameplayEffectReplicationMode)(uint8)AbilitySystem->ReplicationMode;
}

#if WITH_EDITOR
void AMIVICharacterAbilityBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName().IsEqual(GET_MEMBER_NAME_CHECKED(AMIVICharacterAbilityBase, AbilitySystemReplicationMode)))
	{
		AbilitySystem->SetReplicationMode((EGameplayEffectReplicationMode)(uint8)AbilitySystemReplicationMode);
	}
}
#endif  // WITH_EDITOR

UAbilitySystemComponent* AMIVICharacterAbilityBase::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}
