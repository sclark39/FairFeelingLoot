// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "RandomLTNode.generated.h"

// Randomly picks a child based on the weighted values
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API URandomLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	URandomLTNode();

	virtual const ULTGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const override;
	
#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
#endif
};
