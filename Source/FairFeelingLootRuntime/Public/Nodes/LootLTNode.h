// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "LootLTNode.generated.h"

UCLASS()
class FAIRFEELINGLOOTRUNTIME_API ULootLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	ULootLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FName LootType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FLinearColor LootColor;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual void SetNodeTitle(const FText& NewTitle) override;
	virtual bool IsNameEditable() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif
};
