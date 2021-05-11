// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "LootTableDefinition.h"

#include "PriorityLTEdge.generated.h"


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UPriorityLTEdge : public ULTGraphEdge
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Priority = 1;

	UPriorityLTEdge();

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual void SetNodeTitle(const FText& NewTitle) override;
#endif // #if WITH_EDITOR
};