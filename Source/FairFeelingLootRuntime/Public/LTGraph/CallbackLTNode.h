// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "CallbackLTNode.generated.h"


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UCallbackLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UCallbackLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blueprint Callback")
	FName Specifier;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif // #if WITH_EDITOR
};
