// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "LootTable.generated.h"

class ULTGraphNode;
class ULootTableDefinition;
class ULootTableComponent;

USTRUCT(BlueprintType)
struct FLootRecipe
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName LootType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, float> Params;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer GameplayTags;
};


struct FEntropyState
{
	FRandomStream *RNG = nullptr;
	float LastTime = 0;
};


USTRUCT(BlueprintType)
struct FLootTable
{
	GENERATED_BODY()
	
public:

	// Node Storage Block
	TArray<uint8> NodeData;
	TMap<const ULTGraphNode*, uint32> NodeOffsetMap;

	// Dynamic Param Lookup
	TMap<FName, FName> NameParams;
	TMap<FName, float> FloatParams;

	TSet<ULootTableDefinition*> VisitedGraphs;

	// Global State stream
	FRandomStream RNG;
	FEntropyState EntropyState;

	UWorld *World = 0;
	ULootTableComponent *Component = 0;

	bool bRequiresInitialization = true;

	// If true, ignore InitialSeed and randomize the seed for the random number stream
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bShouldRandomizeSeed = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!bShouldRandomizeSeed"))
	int InitialSeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULootTableDefinition *Definition = 0;

	virtual float GetTime();
	
	float GetFloatParam(FName ParamName, float DefaultValue = 0.0f)
	{
		float *Lookup = FloatParams.Find(ParamName);
		return Lookup ? *Lookup : DefaultValue;
	}

	FName GetNameParam(FName ParamName, FName DefaultName = NAME_None)
	{
		FName *Lookup = NameParams.Find(ParamName);
		return Lookup ? *Lookup : DefaultName;
	}

	virtual ~FLootTable() {};
};
