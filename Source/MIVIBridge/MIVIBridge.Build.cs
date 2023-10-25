// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MIVIBridge : ModuleRules
{
	public MIVIBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"MoveIt",
                "VaultIt",
                "GameplayAbilities",
                "MotionWarping",
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine", 
			}
			);
	}
}
