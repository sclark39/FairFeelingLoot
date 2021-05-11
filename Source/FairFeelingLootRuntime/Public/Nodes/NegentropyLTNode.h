// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "NegentropyLTNode.generated.h"

UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UNegentropyLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UNegentropyLTNode();

	// The amount of time in seconds without checking for a new value that must pass before the entropy values are reset
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Negentropy")
	float TimeUntilEntropyReset = 30;

	virtual const ULTGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const override;

#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
#endif
};
