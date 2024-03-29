// Copyright 2021 Skyler Clark. All Rights Reserved.

using UnrealBuildTool;

public class LTGenericGraphRuntime : ModuleRules
{
	public LTGenericGraphRuntime(ReadOnlyTargetRules Target) : base(Target)
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
				"LTGenericGraphRuntime/Private",
				// ... add other private include paths required here ...
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
                "Engine",
				// ... add other public dependencies that you statically link with here ...
			}
			);

		if (Target.Type == TargetRules.TargetType.Editor)
		{
			PublicDependencyModuleNames.Add("EditorStyle");
		}

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...
                "Slate",
                "SlateCore",
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