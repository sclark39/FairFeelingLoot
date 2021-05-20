// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "SwitchLTNode.generated.h"


// Picks Child based on Global Param match to Edge name. 
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API USwitchLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	USwitchLTNode();

	// Global Loot Table Param to Match
	UPROPERTY(EditDefaultsOnly, Category = "Switch")
	FName ParamName;

	// If the param hasn't been set yet, what should it be set to?
	UPROPERTY(EditDefaultsOnly, Category = "Switch")
	FName DefaultValue;

	virtual const ULTGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const override;
	
#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
#endif
};
