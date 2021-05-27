// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "AddStatLTNode.generated.h"


// Adds a Stat to the last generated Loot
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UAddStatLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UAddStatLTNode();

	// What Stat should be applied?
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	FGameplayTag StatType { FGameplayTag::EmptyTag };

	// How will the stat value be manipulated?
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	EAddParamLTType StatWriteMode { EAddParamLTType::Overwrite	};

	// Random range for the number to apply to this stat using the specified WriteMode
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	FVector2D StatValueRange {0.0f, 0.0f};

	// Initial Value of stat if not already set, while using Add or Subtract write modes
	UPROPERTY(EditDefaultsOnly, Category = "Loot", meta =
		(EditCondition = "StatWriteMode != EAddParamLTType::Overwrite"))
	float StatDefaultValue{ 0.0f };

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; } 

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif
};
