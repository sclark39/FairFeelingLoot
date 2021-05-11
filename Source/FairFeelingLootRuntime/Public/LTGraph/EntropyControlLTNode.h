// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "EntropyControlLTNode.generated.h"

UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UEntropyControlLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UEntropyControlLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Random")
	bool bTracksOwnRandomStream = true;

	// If true, ignore InitialSeed and randomize the seed for the random number stream
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Random", meta = (EditCondition = "bTracksOwnRandomStream"))
	bool bShouldRandomizeSeed = false;

	// If not randomizing the seed, this is what will be used to initialize the random number stream
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Random", meta = (EditCondition = "bTracksOwnRandomStream"))
	float InitialSeed = 0;
	
	// Should this node time be tracked from the graph-scope or from this node? This impacts if Negentropy nodes g
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Time")
	bool bTracksOwnTime = true;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;

#if WITH_EDITOR
	virtual FLinearColor GetBackgroundColor() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
#endif
};
