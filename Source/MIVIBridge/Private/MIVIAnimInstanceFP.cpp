// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.


#include "MIVIAnimInstanceFP.h"
#include "MIVICharacterBase.h"
#include "VIBlueprintFunctionLibrary.h"
#include "Animation/AnimMontage.h"


bool UMIVIAnimInstanceFP::CanPlayFPMontage() const
{
	return Character && Character->IsLocallyControlled() && !Character->IsBotControlled();
}

void UMIVIAnimInstanceFP::OnStartVault()
{
	Super::OnStartVault();

	if (CanPlayFPMontage())
	{
		if (MontageLinkMap.Contains(Character->GetCurrentMontage()))
		{
			MontageToPlay = MontageLinkMap.FindChecked(Character->GetCurrentMontage());
		}

		if (MontageToPlay)
		{
			VaultBlendOutTime = Character->GetCurrentMontage()->GetDefaultBlendOutTime();
			const float PlayLength = Character->GetCurrentMontage()->GetPlayLength();
			const float PlayRate = UVIBlueprintFunctionLibrary::ComputeAnimationPlayRateFromDuration(MontageToPlay, PlayLength);
			Montage_Play(MontageToPlay, PlayRate);
		}
		else
		{
			UVIBlueprintFunctionLibrary::MessageLogError(FString::Printf(TEXT("{ %s} No FP Vault Animation found for { %s }"), *Character->GetName(), *Character->GetCurrentMontage()->GetName()));
		}
	}
}

void UMIVIAnimInstanceFP::OnStopVault()
{
	Super::OnStopVault();

	if (MontageToPlay)
	{
		Montage_Stop(VaultBlendOutTime, MontageToPlay);
		MontageToPlay = nullptr;
	}
}
