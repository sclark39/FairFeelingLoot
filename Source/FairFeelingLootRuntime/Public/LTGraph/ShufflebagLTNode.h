// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "ShufflebagLTNode.generated.h"


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UShufflebagLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UShufflebagLTNode();
	
	virtual const ULTGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const override;

#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
#endif // #if WITH_EDITOR
};

