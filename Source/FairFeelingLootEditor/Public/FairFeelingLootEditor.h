// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAssetTools.h"

class UFairFeelingLootEditorConfig;

class FFairFeelingLootEditor : public IModuleInterface
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
public:
	static const UFairFeelingLootEditorConfig* GetConfig();

private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	
	void RegisterSettings();
	void UnregisterSettings();
	bool HandleSettingsSaved();

	void RegisterNewAssets();
	void UnregisterNewAssets();

private:
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
};
