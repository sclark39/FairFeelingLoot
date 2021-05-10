
using UnrealBuildTool;

public class GraphEditorTestEditor : ModuleRules
{
	public GraphEditorTestEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {
			"GraphEditorTest",
			"UnrealEd",
			"GenericGraphRuntime",
			"GenericGraphEditor"
		});

		bLegacyPublicIncludePaths = false;
		PublicIncludePaths.AddRange(
			new string[] {
				"GraphEditorTest"
				// ... add public include paths required here ...
				
			}
			);

		PrivateIncludePaths.AddRange(
			new string[] {
                // ... add other private include paths required here ...
				"GraphEditorTestEditor"
			}
			);
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
