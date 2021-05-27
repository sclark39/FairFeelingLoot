// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "LootTable.generated.h"

class ULTGraphNode;
class ULootTableDefinition;
class ULootTableComponent;

USTRUCT(BlueprintType)
struct FAIRFEELINGLOOTRUNTIME_API FLootRecipeStat
{
	GENERATED_BODY()

public:
	// Type Specifier for this Stat
	UPROPERTY(BlueprintReadWrite, Category="Loot")
	FGameplayTag StatType;

	// Value for this Stat
	UPROPERTY(BlueprintReadWrite, Category = "Loot")
	float StatValue;
};

USTRUCT(BlueprintType)
struct FAIRFEELINGLOOTRUNTIME_API FLootRecipe
{
	GENERATED_BODY()

public:

	FName Name;

	FGameplayTag Type;

	FGameplayTagContainer Tags;

	TArray<FLootRecipeStat> Stats;
	TMap<FGameplayTag, int32> StatLookup;
};


struct FAIRFEELINGLOOTRUNTIME_API FMakeLootState
{
	FLootRecipe *ActiveLoot = nullptr;
	FRandomStream *RNG = nullptr;
	float LastTime = 0;
};


USTRUCT(BlueprintInternalUseOnly)
struct FAIRFEELINGLOOTRUNTIME_API FLootTableData
{
	GENERATED_BODY()
	
public:

	// Node Storage Block
	TArray<uint8> NodeData;
	TMap<const ULTGraphNode*, uint32> NodeOffsetMap;

	// Dynamic Param Lookup
	TMap<FName, FName> NameParams;
	TMap<FName, float> FloatParams;

	TSet<const ULootTableDefinition*> VisitedGraphs;

	// Global State stream
	FRandomStream RNG;
	float LastTime = 0;

	UWorld *World = 0;
	ULootTableComponent *Component = 0;

	bool bRequiresInitialization = true;

	virtual float GetTime();
	
	float GetFloatParam(FName ParamName, float DefaultValue = 0.0f)
	{
		float &Lookup = FloatParams.FindOrAdd(ParamName, DefaultValue);
		return Lookup;
	}

	FName GetNameParam(FName ParamName, FName DefaultName = NAME_None)
	{
		FName &Lookup = NameParams.FindOrAdd(ParamName, DefaultName);
		return Lookup;
	}

	virtual ~FLootTableData() {};
};
