// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "SwitchLTNode.generated.h"


UCLASS()
class USwitchLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	USwitchLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Switch")
	FName ParamName;


	virtual const UGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const override;
	
#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual TSubclassOf<UGenericGraphEdge> GetEdgeType() const override;
#endif
};
