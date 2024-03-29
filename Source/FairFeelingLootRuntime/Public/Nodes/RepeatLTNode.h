﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "RepeatLTNode.generated.h"

// Loops its children to generate multiple drops of Loot. Will repeat a random number of times between the specified Min and Max values.
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API URepeatLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	URepeatLTNode();

	// How many times to repeat? Will repeat between [Min, Max] times.
	UPROPERTY()
	FVector2D RepeatRange_DEPRECATED = FVector2D::ZeroVector;

	// How many times to repeat, minimum?
	UPROPERTY(EditDefaultsOnly, Category = "Repeat")
	int MinRepeats = 1;

	// Maximum number of times to repeat
	UPROPERTY(EditDefaultsOnly, Category = "Repeat")
	int MaxRepeats = 1;

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const override;

	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif
};
