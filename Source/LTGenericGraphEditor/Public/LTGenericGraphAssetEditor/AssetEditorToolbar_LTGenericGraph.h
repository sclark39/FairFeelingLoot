
#pragma once

#include "CoreMinimal.h"

class FAssetEditor_LTGenericGraph;
class FExtender;
class FToolBarBuilder;

class LTGENERICGRAPHEDITOR_API FAssetEditorToolbar_LTGenericGraph : public TSharedFromThis<FAssetEditorToolbar_LTGenericGraph>
{
public:
	FAssetEditorToolbar_LTGenericGraph(TSharedPtr<FAssetEditor_LTGenericGraph> InLTGenericGraphEditor)
		: LTGenericGraphEditor(InLTGenericGraphEditor) {}

	void AddLTGenericGraphToolbar(TSharedPtr<FExtender> Extender);

private:
	void FillLTGenericGraphToolbar(FToolBarBuilder& ToolbarBuilder);

protected:
	/** Pointer back to the blueprint editor tool that owns us */
	TWeakPtr<FAssetEditor_LTGenericGraph> LTGenericGraphEditor;
};
