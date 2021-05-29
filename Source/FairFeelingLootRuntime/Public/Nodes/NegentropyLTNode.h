// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "NegentropyLTNode.generated.h"

// Picks between two children based upon the edge weights. The distribution will be the same
// as if using a Pick Random node, but the sequence will be totally predictable. This can help
// make loot drops feel more fair. Reseting the entropy after a specified amount of time can help
// to hide the predictability of the sequence.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UNegentropyLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UNegentropyLTNode();

	// If enough time passes, should the entropy value be reset (breaking the sequence)
	UPROPERTY(EditDefaultsOnly, Category = "Negentropy")
	bool bShouldResetEntropyAfterTimeout = true;

	// The amount of time in seconds without checking for a new value that must pass before the entropy values are reset
	UPROPERTY(EditDefaultsOnly, Category = "Negentropy", meta = (EditCondition = "bShouldResetEntropyAfterTimeout"))
	float TimeUntilEntropyReset = 30;

	virtual const ULTGenericGraphNode* PickChild(FLootTableData &LootTable, const FMakeLootState &State) const override;

#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
#endif
};
