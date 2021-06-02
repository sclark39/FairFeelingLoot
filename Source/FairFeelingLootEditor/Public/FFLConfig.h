// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FFLConfig.generated.h"

UENUM()
enum class FFFLConfigNewAsset : uint8
{
	Basic,
	FairFeelingLoot,
	Miscellaneous
};

UCLASS(config = EditorSettings)
class UFairFeelingLootEditorConfig : public UObject
{
	GENERATED_BODY()
public:

	UFairFeelingLootEditorConfig(const FObjectInitializer& ObjectInitializer);

	// Where should the Loot Table Definition be shown in the Add New Asset context menu?
	UPROPERTY(EditAnywhere, config, Category = Default, meta = (ConfigRestartRequired = true))
	FFFLConfigNewAsset ContextMenuLocation = FFFLConfigNewAsset::Basic;


};