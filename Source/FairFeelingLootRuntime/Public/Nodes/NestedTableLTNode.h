// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "NestedTableLTNode.generated.h"

// Calls into another Loot Table Definition, as if it is part of the same graph.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UNestedTableLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UNestedTableLTNode();

	// The Loot Table Definition to call in to
	UPROPERTY(EditDefaultsOnly, Category = "Nested Loot Table")
	ULootTableDefinition *LootTableDefinition;

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif // #if WITH_EDITOR
};
