﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"
#include "UObject/Interface.h"
#include "Components/ActorComponent.h"

#include "LootTableComponent.generated.h"

class ULTGenericGraph;
class ULTGenericGraphNode;
class ULTGenericGraphEdge;

UINTERFACE(Blueprintable)
class FAIRFEELINGLOOTRUNTIME_API ULootSourceInterface : public UInterface
{
	GENERATED_BODY()
};

class FAIRFEELINGLOOTRUNTIME_API ILootSourceInterface
{
	GENERATED_BODY()
public:

	// What Loot Table should be used for generating Loot from this Actor?
	UFUNCTION(BlueprintImplementableEvent, CallInEditor)
	ULootTableDefinition *GetLootTable();
};


UCLASS(ClassGroup = ("Custom"), meta = (BlueprintSpawnableComponent))
class FAIRFEELINGLOOTRUNTIME_API ULootGenerationComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// The Loot Table Definition to use for generating Loot
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Table")
	ULootTableDefinition *DefaultLootTable = 0;

	// If true, ignore InitialSeed and randomize the seed for the random number stream
	UPROPERTY(EditDefaultsOnly, Category = "Loot Table", meta = (EditCondition = "bTracksOwnRandomStream"))
	bool bShouldRandomizeSeed = true;

	// If not randomizing the seed, this is what will be used to initialize the random number stream
	UPROPERTY(EditDefaultsOnly, Category = "Loot Table", meta = (EditCondition = "bTracksOwnRandomStream && !bShouldRandomizeSeed"))
	float InitialSeed = 0;

	// Generates an array of Loot Recipes based upon the Loot Table Definition
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	TArray<FLootRecipe> MakeRandomLootFromLootTable( const ULootTableDefinition *LootTable );

	// Generates an array of Loot Recipes based upon an Actor implementing LootSourceInterface
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	TArray<FLootRecipe> MakeRandomLootFromActor(AActor *Actor);

	// Generates an array of Loot Recipes based upon an object implementing LootSourceInterface
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	TArray<FLootRecipe> MakeRandomLootFromLootSource(TScriptInterface<ILootSourceInterface> LootSource);

	// Gets the value of a global loot table name param (specific to this component)
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	FName GetGlobalNameParam(FName ParamName, FName DefaultValue = NAME_None) const;

	// Gets the value of a global loot table float param (specific to this component)
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	float GetGlobalFloatParam(FName ParamName, float DefaultValue = 0) const;

	// Sets the value of a global loot table name param (specific to this component)
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	void SetGlobalNameParam(FName ParamName, FName ParamValue);

	// Sets the value of a global loot table float param (specific to this component)
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	void SetGlobalFloatParam(FName ParamName, float ParamValue);

	// Gets the value of a local loot table name param (specific to this component and loot table)
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	FName GetNameParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, FName DefaultValue = NAME_None) const;

	// Gets the value of a local loot table float param (specific to this component and loot table)
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	float GetFloatParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, float DefaultValue = 0) const;

	// Sets the value of a local loot table name param (specific to this component and loot table)
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	void SetNameParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, FName ParamValue);

	// Sets the value of a local loot table float param (specific to this component and loot table)
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	void SetFloatParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, float ParamValue);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;
protected:

	void OnLootTableNodeChanged(const ULTGenericGraphNode *Node);
	void OnLootTableEdgeChanged(const ULTGenericGraphEdge *Edge);
	void OnLootTableDefinitionRebuilt(const ULTGenericGraph *Graph);

	FLootTableData LootTableData;
};


