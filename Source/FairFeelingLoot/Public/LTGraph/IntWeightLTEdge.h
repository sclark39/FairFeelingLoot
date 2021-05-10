// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "IntWeightLTEdge.generated.h"


UCLASS()
class GRAPHEDITORTEST_API UIntWeightLTEdge : public ULTGraphEdge
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Weight = 1;

	UIntWeightLTEdge();

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual void SetNodeTitle(const FText& NewTitle) override;
#endif // #if WITH_EDITOR
};