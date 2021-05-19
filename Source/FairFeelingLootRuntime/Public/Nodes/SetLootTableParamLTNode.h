﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "SetLootTableParamLTNode.generated.h"

// Modifies a global Param of the Loot Table, with options to 
// apply a random number within a range either via Set, Add, or Subtract.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API USetLootTableParamLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	USetLootTableParamLTNode();

	// Loot Table Param to Modify
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot Table")
	FName ParamName;

	// If the param hasn't been set yet, what should it be set to?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot Table")
	float DefaultValue = 0;

	// How will the value be manipulated?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot Table")
	EAddParamLTType WriteMode;

	// Random range for the number to apply using the specified WriteMode
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot Table")
	FVector2D ValueRange = FVector2D::ZeroVector;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif // #if WITH_EDITOR
};
