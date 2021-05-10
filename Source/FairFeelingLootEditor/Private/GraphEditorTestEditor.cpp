// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "GraphEditorTestEditor.h"
#include "EdGraphUtilities.h"
#include "AssetTypeActions_LootTableDefinition.h"
#include "Modules/ModuleManager.h"

class FGraphEditorTestEditor : public IModuleInterface
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;

	EAssetTypeCategories::Type FairRandomGraphAssetCategoryBit;
};

IMPLEMENT_MODULE(FGraphEditorTestEditor, GraphEditorTestEditor)


#define LOCTEXT_NAMESPACE "CodeTestEditorModule"

void FGraphEditorTestEditor::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	//FairRandomGraphAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(
	//	FName(TEXT("FairRandomAssetCategory")), 
	//	LOCTEXT("FairRandomGraphAssetCategory", "FairRandom"));
	
	RegisterAssetTypeAction(
		AssetTools, 
		MakeShareable(
			new FAssetTypeActions_LootTableDefinition(EAssetTypeCategories::Misc)
		));

			
}
void FGraphEditorTestEditor::ShutdownModule()
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

void FGraphEditorTestEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE