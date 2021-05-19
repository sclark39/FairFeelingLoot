// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "BranchParamLTNode.generated.h"

// Test a Loot Table Float Param to determine which edge to follow. The ranges
// to test against should be set on the edges.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UBranchParamLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UBranchParamLTNode();

	// Param to Test
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Float Param")
	FName ParamName = NAME_None;

	// If the param hasn't been set yet, what should it be set to?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Float Param")
	float DefaultValue;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
#endif // #if WITH_EDITOR
};
