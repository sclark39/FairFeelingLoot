// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "SequenceLTNode.generated.h"

UCLASS()
class FAIRFEELINGLOOTRUNTIME_API USequenceLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	USequenceLTNode();
	
	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;	

#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
#endif
};
