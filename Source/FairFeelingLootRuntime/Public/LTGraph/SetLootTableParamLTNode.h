// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "SetLootTableParamLTNode.generated.h"


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API USetLootTableParamLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	USetLootTableParamLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot Table")
	FName ParamName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot Table")
	EAddParamLTType WriteMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot Table")
	FVector2D ValueRange = FVector2D::ZeroVector;

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif // #if WITH_EDITOR
};
