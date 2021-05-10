// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "AddTagLTNode.generated.h"


UCLASS()
class UAddTagLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UAddTagLTNode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot")
	FGameplayTag GameplayTag;
	
	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; } 

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif
};
