// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "WeightedLTEdge.generated.h"


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UWeightedLTEdge : public ULTGraphEdge
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot", meta = (ClampMin = "0", EditCondition = "!bUseDynamicWeight"))
	float Weight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot", meta = (EditCondition = "bUseDynamicWeight"))
	FName WeightParamName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	bool bUseDynamicWeight = false;

	UWeightedLTEdge();

	float GetWeight(FLootTableData &LootTable) const;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual void SetNodeTitle(const FText& NewTitle) override;
#endif // #if WITH_EDITOR
};