// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "FairFeelingLootEditor.h"
#include "EdGraphUtilities.h"
#include "AssetTypeActions_LootTableDefinition.h"
#include "Modules/ModuleManager.h"

class FFairFeelingLootEditor : public IModuleInterface
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;

	EAssetTypeCategories::Type FairRandomGraphAssetCategoryBit;
};

IMPLEMENT_MODULE(FFairFeelingLootEditor, FairFeelingLootEditor)


#define LOCTEXT_NAMESPACE "CodeTestEditorModule"

void FFairFeelingLootEditor::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	FairRandomGraphAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(
		FName(TEXT("FairFeelingLootAssetCategory")), 
		LOCTEXT("FairFeelingLootAssetCategory", "Fair Feeling Loot"));
	
	RegisterAssetTypeAction(
		AssetTools, 
		MakeShareable(
			new FAssetTypeActions_LootTableDefinition(FairRandomGraphAssetCategoryBit)
		));

			
}
void FFairFeelingLootEditor::ShutdownModule()
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