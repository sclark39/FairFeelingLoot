// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "LootTable.generated.h"

class ULTGraphNode;
class ULootTableDefinition;
class ULootGenerationComponent;

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
	TMap<const ULootTableDefinition*, TMap<FName, FName>> LocalNameParams;
	TMap <const ULootTableDefinition*, TMap<FName, float>> LocalFloatParams;

	TSet<const ULootTableDefinition*> VisitedGraphs;

	// Global State stream
	FRandomStream RNG;
	float LastTime = 0;

	UWorld *World = 0;
	ULootGenerationComponent *Component = 0;

	bool bRequiresInitialization = true;

	virtual float GetTime();
	
	float GetFloatParam(FName ParamName, float DefaultValue = 0.0f) const
	{
		if (FloatParams.Contains(ParamName))
			return FloatParams[ParamName];

		return DefaultValue;
	}

	FName GetNameParam(FName ParamName, FName DefaultValue = NAME_None) const
	{
		if (NameParams.Contains(ParamName))
			return NameParams[ParamName];

		return DefaultValue;
	}

	float GetFloatParamFromLT(const ULootTableDefinition *LootTable, FName ParamName, float DefaultValue = 0) const
	{
		if (LocalFloatParams.Contains(LootTable))
			if (LocalFloatParams[LootTable].Contains(ParamName))
				return LocalFloatParams[LootTable][ParamName];

		return GetFloatParam(ParamName, DefaultValue);
	}

	FName GetNameParamFromLT(const ULootTableDefinition *LootTable, FName ParamName, FName DefaultValue = NAME_None) const
	{
		if (LocalNameParams.Contains(LootTable))
			if (LocalNameParams[LootTable].Contains(ParamName))
				return LocalNameParams[LootTable][ParamName];

		return GetNameParam(ParamName, DefaultValue);
	}


	void SetFloatParam(FName ParamName, float ParamValue)
	{
		FloatParams.Emplace(ParamName, ParamValue);
	}

	void SetNameParam(FName ParamName, FName ParamValue)
	{
		NameParams.Emplace(ParamName, ParamValue);
	}

	void SetFloatParamForLT(const ULootTableDefinition *LootTable, FName ParamName, float ParamValue)
	{
		ensure(LootTable);
		auto FloatParamsForLT = LocalFloatParams.FindOrAdd(LootTable);
		FloatParamsForLT.Emplace(ParamName, ParamValue);
	}

	void SetNameParamForLT(const ULootTableDefinition *LootTable, FName ParamName, FName ParamValue)
	{
		ensure(LootTable);

		auto NameParamsForLT = LocalNameParams.FindOrAdd(LootTable);
		NameParamsForLT.Emplace(ParamName, ParamValue);
	}




	virtual ~FLootTableData() {};
};
