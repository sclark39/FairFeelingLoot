#pragma once
#include "Modules/ModuleManager.h"
#include "LTGenericGraphEditorModule.h"
#include <IAssetTools.h>
#include <EdGraphUtilities.h>

class FLTGenericGraphEditor : public ILTGenericGraphEditor
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;

	EAssetTypeCategories::Type LTGenericGraphAssetCategoryBit;

	TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory_LTGenericGraph;
};

IMPLEMENT_MODULE(FLTGenericGraphEditor, LTGenericGraphEditor)