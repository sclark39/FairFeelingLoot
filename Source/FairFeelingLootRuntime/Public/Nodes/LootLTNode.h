// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "LootLTNode.generated.h"

// Creates a Loot Recipe and adds it to the returned array
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API ULootLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	ULootLTNode();

	// Name for the Loot
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	FName LootName;

	// Gameplay Tag Loot Type Identifier
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	FGameplayTag LootType;

	// Color of Loot in the Graph (dev only)
	UPROPERTY(EditDefaultsOnly, Category = "Loot")
	FLinearColor LootColor;

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const override;
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
