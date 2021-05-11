// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "SwitchLTNode.generated.h"


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API USwitchLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	USwitchLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Switch")
	FName ParamName;


	virtual const ULTGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const override;
	
#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
#endif
};
