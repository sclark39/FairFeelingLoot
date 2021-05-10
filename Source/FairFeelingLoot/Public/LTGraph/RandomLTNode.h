// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "RandomLTNode.generated.h"


UCLASS()
class URandomLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	URandomLTNode();

	virtual const UGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const override;
	
#if WITH_EDITOR
	virtual TSubclassOf<UGenericGraphEdge> GetEdgeType() const override;
#endif
};
