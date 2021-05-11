// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "BranchParamLTNode.generated.h"

UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UBranchParamLTNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UBranchParamLTNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot Table")
	FName ParamName = NAME_None;
	
	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const override;
#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
	virtual FText GetNodeTitle() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
#endif // #if WITH_EDITOR
};
