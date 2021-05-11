#include "LTGenericGraphAssetEditor/AssetEditorToolbar_LTGenericGraph.h"
#include "LTGenericGraphAssetEditor/AssetEditor_LTGenericGraph.h"
#include "LTGenericGraphAssetEditor/EditorCommands_LTGenericGraph.h"
#include "LTGenericGraphAssetEditor/LTGenericGraphEditorStyle.h"

#include "LTGenericGraphEditorStrings.h"

#define LOCTEXT_NAMESPACE "AssetEditorToolbar_LTGenericGraph"

void FAssetEditorToolbar_LTGenericGraph::AddLTGenericGraphToolbar(TSharedPtr<FExtender> Extender)
{
	check(LTGenericGraphEditor.IsValid());
	TSharedPtr<FAssetEditor_LTGenericGraph> LTGenericGraphEditorPtr = LTGenericGraphEditor.Pin();

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension("Asset", EExtensionHook::After, LTGenericGraphEditorPtr->GetToolkitCommands(), FToolBarExtensionDelegate::CreateSP( this, &FAssetEditorToolbar_LTGenericGraph::FillLTGenericGraphToolbar ));
	LTGenericGraphEditorPtr->AddToolbarExtender(ToolbarExtender);
}

void FAssetEditorToolbar_LTGenericGraph::FillLTGenericGraphToolbar(FToolBarBuilder& ToolbarBuilder)
{
	check(LTGenericGraphEditor.IsValid());
	TSharedPtr<FAssetEditor_LTGenericGraph> LTGenericGraphEditorPtr = LTGenericGraphEditor.Pin();

	ToolbarBuilder.BeginSection(GGS_TOOLBAR_SECTION);
	{
		ToolbarBuilder.AddToolBarButton(FEditorCommands_LTGenericGraph::Get().GraphSettings,
			NAME_None,
			LOCTEXT("GraphSettings_Label", "Graph Settings"),
			LOCTEXT("GraphSettings_ToolTip", "Show the Graph Settings"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.GameSettings"));
	}
	ToolbarBuilder.EndSection();

	ToolbarBuilder.BeginSection("Util");
	{
		ToolbarBuilder.AddToolBarButton(FEditorCommands_LTGenericGraph::Get().AutoArrange,
			NAME_None,
			LOCTEXT("AutoArrange_Label", "Auto Arrange"),
			LOCTEXT("AutoArrange_ToolTip", "Auto arrange nodes, not perfect, but still handy"),
			FSlateIcon(FLTGenericGraphEditorStyle::GetStyleSetName(), "LTGenericGraphEditor.AutoArrange"));
	}
	ToolbarBuilder.EndSection();

}


#undef LOCTEXT_NAMESPACE
