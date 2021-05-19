// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "RepeatLTNode.generated.h"

// Loops its children to generate multiple drops of Loot
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API URepeatLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	URepeatLTNode();

	// How many times to repeat? Will repeat between [Min, Max] times.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FVector2D RepeatRange;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif
};
