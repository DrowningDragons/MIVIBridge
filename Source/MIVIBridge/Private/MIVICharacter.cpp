// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.


#include "MIVICharacter.h"

#include "MotionWarpingComponent.h"
#include "GAS/VIAbilitySystemComponent.h"
#include "Pawn/VIPawnVaultComponent.h"

AMIVICharacter::AMIVICharacter(const FObjectInitializer& OI)
	: Super(OI)
{
	VaultComponent = CreateDefaultSubobject<UVIPawnVaultComponent>(TEXT("PawnVaulting"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));
}

void AMIVICharacter::BeginPlay()
{
	Super::BeginPlay();

	// Init simulated proxy
	if (AbilitySystem && GetLocalRole() == ROLE_SimulatedProxy)
	{
		// Will never have a valid controller
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

void AMIVICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init authority/standalone
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

void AMIVICharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	// Init local client
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}