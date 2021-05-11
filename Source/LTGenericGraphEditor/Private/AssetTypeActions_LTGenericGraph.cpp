#include "AssetTypeActions_LTGenericGraph.h"
#include "LTGenericGraphEditorPCH.h"
#include "LTGenericGraphAssetEditor/AssetEditor_LTGenericGraph.h"
#include "LTGenericGraphEditorStrings.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_LTGenericGraph"

FAssetTypeActions_LTGenericGraph::FAssetTypeActions_LTGenericGraph(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FAssetTypeActions_LTGenericGraph::GetName() const
{
	return LOCTEXT("FLTGenericGraphAssetTypeActionsName", GGS_GRAPH_ASSET_TYPE);
}

FColor FAssetTypeActions_LTGenericGraph::GetTypeColor() const
{
	return FColor(129, 196, 115);
}

UClass* FAssetTypeActions_LTGenericGraph::GetSupportedClass() const
{
	return ULTGenericGraph::StaticClass();
}

void FAssetTypeActions_LTGenericGraph::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (ULTGenericGraph* Graph = Cast<ULTGenericGraph>(*ObjIt))
		{
			TSharedRef<FAssetEditor_LTGenericGraph> NewGraphEditor(new FAssetEditor_LTGenericGraph());
			NewGraphEditor->InitLTGenericGraphAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

uint32 FAssetTypeActions_LTGenericGraph::GetCategories()
{
	return MyAssetCategory;
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE