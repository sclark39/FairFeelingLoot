// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "AddTagLTNode.generated.h"


// Adds a GameplayTag to the last generated Loot
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UAddTagLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UAddTagLTNode();

	// What GameplayTag should be applied?
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	FGameplayTag GameplayTag { FGameplayTag::EmptyTag };

	// Is there a stat value associated with this tag?
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	bool bTagHasStatValue { true };

	// How will the stat value be manipulated?
	UPROPERTY(EditDefaultsOnly, Category = "Loot", meta = (EditCondition = "bTagHasStatValue"))
	EAddParamLTType StatWriteMode { EAddParamLTType::Overwrite	};

	// Random range for the number to apply to this stat using the specified WriteMode
	UPROPERTY(EditDefaultsOnly, Category = "Loot", meta = (EditCondition = "bTagHasStatValue"))
	FVector2D StatValueRange {0.0f, 0.0f};

	// Initial Value of stat if not already set, while using Add or Subtract write modes
	UPROPERTY(EditDefaultsOnly, Category = "Loot", meta =
		(EditCondition = "bTagHasStatValue && StatWriteMode != EAddParamLTType::Overwrite"))
	float StatDefaultValue{ 0.0f };

	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
	virtual bool ShouldPickChildren() const override { return false; } 

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif
};
