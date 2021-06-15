// Copyright 2021 Skyler Clark. All Rights Reserved.

using UnrealBuildTool;

public class FairFeelingLootEditor : ModuleRules
{
	public FairFeelingLootEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {
			"UnrealEd",
			"LTGenericGraphRuntime",
			"LTGenericGraphEditor",
			"FairFeelingLootRuntime"
		});

		bLegacyPublicIncludePaths = false;
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				
			}
			);

		PrivateIncludePaths.AddRange(
			new string[] {
				"FairFeelingLootEditor/Public",
				"FairFeelingLootEditor/Private"
			}
		);


	}
}
