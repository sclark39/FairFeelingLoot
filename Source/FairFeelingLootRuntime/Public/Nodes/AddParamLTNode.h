// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "AddParamLTNode.generated.h"

UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UAddParamLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UAddParamLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FName LootParamName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	EAddParamLTType WriteMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FVector2D LootParamRange;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif
};
