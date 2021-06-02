// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "FairFeelingLootEditor.h"
#include "EdGraphUtilities.h"
#include "AssetTypeActions_LootTableDefinition.h"
#include "Modules/ModuleManager.h"
#include "FFLConfig.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"

IMPLEMENT_MODULE(FFairFeelingLootEditor, FairFeelingLootEditor)


#define LOCTEXT_NAMESPACE "FairFeelingLootEditor"

void FFairFeelingLootEditor::StartupModule()
{
	RegisterSettings();
	RegisterNewAssets();			
}

void FFairFeelingLootEditor::ShutdownModule()
{
	if (UObjectInitialized())
	{
		UnregisterSettings();
		UnregisterNewAssets();
	}
}

const UFairFeelingLootEditorConfig* FFairFeelingLootEditor::GetConfig()
{
	return GetDefault<UFairFeelingLootEditorConfig>();
}

void FFairFeelingLootEditor::RegisterSettings()
{
	if (auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Register the settings
		auto SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "Fair Feeling Loot",
			LOCTEXT("RuntimeGeneralSettingsName", "Fair Feeling Loot"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Configuration for the Fair Feeling Loot plugin"),
			GetMutableDefault<UFairFeelingLootEditorConfig>()
		);

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FFairFeelingLootEditor::HandleSettingsSaved);
		}
	}
		
}

void FFairFeelingLootEditor::UnregisterSettings()
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Fair Feeling Loot");
	}
}

bool FFairFeelingLootEditor::HandleSettingsSaved()
{
	auto Settings = GetMutableDefault<UFairFeelingLootEditorConfig>();
	bool bResaveSettings = false;

	// Add validation code here

	if (bResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

void FFairFeelingLootEditor::RegisterNewAssets()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	
	EAssetTypeCategories::Type AssetCategory;

	switch (GetConfig()->ContextMenuLocation)
	{
	case FFFLConfigNewAsset::Basic:
	{
		AssetCategory = EAssetTypeCategories::Basic;
		break;
	}
	case FFFLConfigNewAsset::Miscellaneous:
	{
		AssetCategory = EAssetTypeCategories::Misc;
		break;
	}
	case FFFLConfigNewAsset::FairFeelingLoot:
	default:
	{
		AssetCategory = AssetTools.RegisterAdvancedAssetCategory(
			FName(TEXT("FairFeelingLootAssetCategory")),
			LOCTEXT("FairFeelingLootAssetCategory", "Fair Feeling Loot"));
		break;
	}
	}

	RegisterAssetTypeAction(
		AssetTools,
		MakeShareable(
			new FAssetTypeActions_LootTableDefinition(AssetCategory)
		));
}

void FFairFeelingLootEditor::UnregisterNewAssets()
{
	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}
}

void FFairFeelingLootEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}


#undef LOCTEXT_NAMESPACE