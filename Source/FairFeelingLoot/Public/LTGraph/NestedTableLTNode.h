// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "NestedTableLTNode.generated.h"


UCLASS()
class UNestedTableLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UNestedTableLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Nested Loot Table")
	ULootTableDefinition *LootTableDefinition;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif // #if WITH_EDITOR
};
