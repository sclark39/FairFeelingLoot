#include "LTGenericGraphEditor.h"
#include "LTGenericGraphNodeFactory.h"
#include "AssetTypeActions_LTGenericGraph.h"
#include "LTGenericGraphAssetEditor/LTGenericGraphEditorStyle.h"

DEFINE_LOG_CATEGORY(LTGenericGraphEditor)

#define LOCTEXT_NAMESPACE "Editor_LTGenericGraph"

void FLTGenericGraphEditor::StartupModule()
{
	FLTGenericGraphEditorStyle::Initialize();

	// Make Node Factory
	GraphPanelNodeFactory_LTGenericGraph = MakeShareable(new FGraphPanelNodeFactory_LTGenericGraph());
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory_LTGenericGraph);

	// Add to New Asset Context Menu
#if GG_SHOULD_REGISTER_ASSET_TYPE
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	LTGenericGraphAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("LTGenericGraph")), LOCTEXT("LTGenericGraphAssetCategory", "LTGenericGraph"));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_LTGenericGraph(LTGenericGraphAssetCategoryBit)));
#endif // #if GG_SHOULD_ADD_TO_CONTEXTMENU
}


void FLTGenericGraphEditor::ShutdownModule()
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

	if (GraphPanelNodeFactory_LTGenericGraph.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(GraphPanelNodeFactory_LTGenericGraph);
		GraphPanelNodeFactory_LTGenericGraph.Reset();
	}

	FLTGenericGraphEditorStyle::Shutdown();
}

void FLTGenericGraphEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE

