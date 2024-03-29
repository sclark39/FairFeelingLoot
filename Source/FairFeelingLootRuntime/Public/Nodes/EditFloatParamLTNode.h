﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "EditFloatParamLTNode.generated.h"

// Modifies a global Param of the Loot Table, with options to 
// apply a random number within a range either via Set, Add, or Subtract.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UEditFloatParamLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UEditFloatParamLTNode();

	// Loot Table Param to Modify
	UPROPERTY(EditDefaultsOnly, Category = "Edit Float Param")
	FName ParamName;

	// If the param doesn't exist, should it be created in local or global scope?
	UPROPERTY(EditDefaultsOnly, Category = "Edit Float Param")
	bool bShouldCreateLocalScopeOnly = false;

	// Should this param only change for this Loot Table Definition?
	UPROPERTY(EditDefaultsOnly, Category = "Edit Float Param")
	bool bShouldModifyLocalScopeOnly = false;

	// If the param hasn't been set yet, what should it be set to?
	UPROPERTY(EditDefaultsOnly, Category = "Edit Float Param")
	float DefaultValue = 0;

	// How will the value be manipulated?
	UPROPERTY(EditDefaultsOnly, Category = "Edit Float Param")
	EAddParamLTType WriteMode;

	// Random range for the number to apply using the specified WriteMode
	UPROPERTY(EditDefaultsOnly, Category = "Edit Float Param")
	FVector2D ValueRange = FVector2D::ZeroVector;

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif // #if WITH_EDITOR
};
