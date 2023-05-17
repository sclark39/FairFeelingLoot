// Copyright 2021 Skyler Clark. All Rights Reserved.

using UnrealBuildTool;

public class FairFeelingLootRuntime : ModuleRules
{
	public FairFeelingLootRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;
		ShadowVariableWarningLevel = WarningLevel.Error;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);

		PrivateIncludePaths.AddRange(
			new string[] {
				"FairFeelingLootRuntime/Public",
				"FairFeelingLootRuntime/Public/Edges",
				"FairFeelingLootRuntime/Public/Nodes",
				"FairFeelingLootRuntime/Private",
				"FairFeelingLootRuntime/Private/Edges",
				"FairFeelingLootRuntime/Private/Nodes",
				// ... add other private include paths required here ...
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
                "Engine",
				"GameplayTags",
			}
			);

		if (Target.Type == TargetRules.TargetType.Editor)
        {
#if UE_5_1_OR_LATER
            PrivateDependencyModuleNames.Add("SlateCore");
#else
            PrivateDependencyModuleNames.Add("EditorStyle");
#endif
        }

        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"LTGenericGraphRuntime",
			}
			);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}