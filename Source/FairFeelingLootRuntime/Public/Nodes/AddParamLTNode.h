// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "AddParamLTNode.generated.h"

// Modifies a Param for the last generated Loot, with options to 
// apply a random number within a range either via Set, Add, or Subtract.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UAddParamLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UAddParamLTNode();

	// The Param Name on the Loot to Modify
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FName LootParamName;

	// How will the value be manipulated?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	EAddParamLTType WriteMode;

	// Random range for the number to apply using the specified WriteMode
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FVector2D LootParamRange;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif
};
