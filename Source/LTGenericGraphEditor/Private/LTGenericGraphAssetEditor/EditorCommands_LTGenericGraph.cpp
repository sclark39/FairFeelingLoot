#include "LTGenericGraphAssetEditor/EditorCommands_LTGenericGraph.h"

#define LOCTEXT_NAMESPACE "EditorCommands_LTGenericGraph"

void FEditorCommands_LTGenericGraph::RegisterCommands()
{
	UI_COMMAND(GraphSettings, "Graph Settings", "Graph Settings", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AutoArrange, "Auto Arrange", "Auto Arrange", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
