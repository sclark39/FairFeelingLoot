// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTableDefinition.h"

#include "NamedLTEdge.generated.h"

UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UNamedLTEdge : public ULTGraphEdge
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Named Edge")
	FName Value;

	UNamedLTEdge();

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual void SetNodeTitle(const FText& NewTitle) override;
#endif // #if WITH_EDITOR
};
