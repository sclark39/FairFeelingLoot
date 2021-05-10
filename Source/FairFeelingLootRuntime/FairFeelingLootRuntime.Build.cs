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
				"FairFeelingLootRuntime/Private"
				// ... add other private include paths required here ...
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
                "Engine",
				"GameplayTags"
			}
			);

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