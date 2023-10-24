// Copyright (c) 2019-2021 Drowning Dragons Limited. All Rights Reserved.


#include "MIVIAnimInstance.h"
#include "MIVICharacterBase.h"
#include "VIBlueprintFunctionLibrary.h"

void UMIVIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	VaultCharacter = (TryGetPawnOwner()) ? Cast<AMIVICharacterBase>(TryGetPawnOwner()) : nullptr;
}

void UMIVIAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (VaultCharacter)
	{
		const bool bWasVaulting = bIsVaulting;
		bIsVaulting = VaultCharacter->IsVaulting();
		if (bIsVaulting)
		{
			// Resetting these while vaulting leads to better blending out
			bIsFalling = false;
			bOnGround = true;
			bIsIdle = true;
			bIsMoving = false;
			Speed = 0.f;
			RawSpeed = 0.f;

			// Interp FBIK
			UVIBlueprintFunctionLibrary::InterpolateFBIK(DeltaTime, FBIK);

			// Right Hand
			{
				const FVIBoneFBIKData* BoneData = UVIBlueprintFunctionLibrary::GetBoneForFBIK(RHandName, FBIK);
				bRHand = BoneData->bEnabled;
				RHandLoc = BoneData->Location;
			}
			// Left Hand
			{
				const FVIBoneFBIKData* BoneData = UVIBlueprintFunctionLibrary::GetBoneForFBIK(LHandName, FBIK);
				bLHand = BoneData->bEnabled;
				LHandLoc = BoneData->Location;
			}
			// Both Hands
			{
				bBothHand = (bRHand && bLHand);
				if (bBothHand)
				{
					// Use only control rig with both IK
					// Only ever uses one control rig at a time
					bRHand = false;
					bLHand = false;
				}
			}
		}

		if (bIsVaulting && !bWasVaulting)
		{
			OnStartVault();
		}
		else if (bWasVaulting && !bIsVaulting)
		{
			OnStopVault();
		}
	}
}

void UMIVIAnimInstance::OnStopVault()
{
	// Stopped vaulting
	bRHand = false;
	bLHand = false;
	bBothHand = false;
}

void UMIVIAnimInstance::SetBoneFBIK_Implementation(const FName& BoneName, const FVector& BoneLocation, bool bEnabled)
{
	UVIBlueprintFunctionLibrary::ToggleBoneFBIK(BoneName, BoneLocation, bEnabled, FBIK);
}
