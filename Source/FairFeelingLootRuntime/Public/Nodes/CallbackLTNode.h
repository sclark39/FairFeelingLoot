// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "CallbackLTNode.generated.h"

// When this node is reached, an event will be sent to the LootTableComponent
// along with the given Specifier value. This allows for more custom logic mid-generation.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UCallbackLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UCallbackLTNode();

	// The value to send through to the callback to help identify which node is triggering the blueprint event
	UPROPERTY(EditDefaultsOnly, Category = "Blueprint Callback")
	FName Specifier;

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif // #if WITH_EDITOR
};
