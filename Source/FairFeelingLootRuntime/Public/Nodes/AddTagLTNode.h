// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "AddTagLTNode.generated.h"


// Adds a Tag to the last generated Loot
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UAddTagLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UAddTagLTNode();

	// What Tag should be applied?
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	FGameplayTag LootTag { FGameplayTag::EmptyTag };

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; } 

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif
};
