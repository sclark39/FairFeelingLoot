// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "ComparisonLTEdge.generated.h"


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UComparisonLTEdge : public ULTGraphEdge
{
	GENERATED_BODY()
public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Comparison Edge")
	bool bHasMinValue = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge")
	bool bInclusiveMin = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge", meta = (EditCondition = "bHasMinValue"))
	bool bUseDynamicMin = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge", meta = (EditCondition = "bHasMinValue && !bUseDynamicMin"))
	float MinValue = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge", meta = (EditCondition = "bHasMinValue && bUseDynamicMin"))
	FName MinParamName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge")
	bool bHasMaxValue = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge")
	bool bInclusiveMax = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge", meta = (EditCondition = "bHasMaxValue"))
	bool bUseDynamicMax = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge", meta = (EditCondition = "bHasMaxValue && !bUseDynamicMax"))
	float MaxValue = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Comparison Edge", meta = (EditCondition = "bHasMaxValue && bUseDynamicMax"))
	FName MaxParamName = NAME_None;

	UComparisonLTEdge();

	bool AllowTraversal(FLootTableData &LootTable, float TestValue) const;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual void SetNodeTitle(const FText& NewTitle) override;
#endif // #if WITH_EDITOR
};