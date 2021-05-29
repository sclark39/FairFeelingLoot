// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "SequenceLTNode.generated.h"

// Calls all of it's children, optionally in an order you specify, accumulating any Loot
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API USequenceLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	USequenceLTNode();

	// Should the sequence connections be ordered?
	UPROPERTY(EditDefaultsOnly, Category = "Sequence")
	bool bOrderedSequence = false;

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const override;	

#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
#endif
};
