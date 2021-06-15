// Copyright 2021 Skyler Clark. All Rights Reserved.

using UnrealBuildTool;

public class LTGenericGraphEditor : ModuleRules
{
	public LTGenericGraphEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;
		ShadowVariableWarningLevel = WarningLevel.Error;

		PrivateDefinitions.AddRange(
			new string[]
			{
				"GGS_BASE_NAME=\"Loot Table\"",
				"GGS_GRAPH_CORNERTEXT=\"Loot Table\"",
				"GGS_RESOURCES_DIRECTORY=\"FairFeelingLoot/Resources\"",

				"GG_SHOULD_REGISTER_ASSET_TYPE=0"
			}
		);


		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);

		PrivateIncludePaths.AddRange(
			new string[] {
                // ... add other private include paths required here ...
                "LTGenericGraphEditor/Private",
				"LTGenericGraphEditor/Public",
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
                "Engine",
                "UnrealEd",
				"Documentation",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "LTGenericGraphRuntime",
                "AssetTools",
                "Slate",
                "SlateCore",
                "GraphEditor",
                "PropertyEditor",
                "EditorStyle",
                "Kismet",
                "KismetWidgets",
                "ApplicationCore",
				"ToolMenus",
				// ... add private dependencies that you statically link with here ...
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