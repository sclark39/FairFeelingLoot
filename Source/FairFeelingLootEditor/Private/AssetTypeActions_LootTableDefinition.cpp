#include "AssetTypeActions_LootTableDefinition.h"
#include "LootTableDefinition.h"
#include "GenericGraphAssetEditor/AssetEditor_GenericGraph.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_FairRandom"

FAssetTypeActions_LootTableDefinition::FAssetTypeActions_LootTableDefinition(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FAssetTypeActions_LootTableDefinition::GetName() const
{
	return LOCTEXT("FFairRandomGraphAssetTypeActionsName", "Loot Table Definition");
}

FColor FAssetTypeActions_LootTableDefinition::GetTypeColor() const
{
	return FColor(129, 196, 115);
}

UClass* FAssetTypeActions_LootTableDefinition::GetSupportedClass() const
{
	return ULootTableDefinition::StaticClass();
}

void FAssetTypeActions_LootTableDefinition::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (ULootTableDefinition* Graph = Cast<ULootTableDefinition>(*ObjIt))
		{
			TSharedRef<FAssetEditor_GenericGraph> NewGraphEditor(new FAssetEditor_GenericGraph());
			NewGraphEditor->InitGenericGraphAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

uint32 FAssetTypeActions_LootTableDefinition::GetCategories()
{
	return MyAssetCategory;
}



#undef LOCTEXT_NAMESPACE
