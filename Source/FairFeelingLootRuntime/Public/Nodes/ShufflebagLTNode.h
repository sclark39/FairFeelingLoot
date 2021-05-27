// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "ShufflebagLTNode.generated.h"

// Picks from Children by putting all children into a bag (cloning if weights are 
// greater than 1), and then randomly draws until the bag is empty. Once bag is empty,
// all children are put back into the bag.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UShufflebagLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UShufflebagLTNode();
	
	virtual const ULTGenericGraphNode* PickChild(FLootTableData &LootTable, const FMakeLootState &State) const override;

#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
#endif // #if WITH_EDITOR
};

