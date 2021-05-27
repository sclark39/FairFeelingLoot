// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"

#include "LootTableComponent.generated.h"


UINTERFACE()
class FAIRFEELINGLOOTRUNTIME_API ULootTableSpecifier : public UInterface
{
	GENERATED_BODY()
};

class FAIRFEELINGLOOTRUNTIME_API ILootTableSpecifier
{
	GENERATED_BODY()
public:

	// What Loot Table should be used for generating Loot from this Actor?
	UFUNCTION(BlueprintImplementableEvent, CallInEditor)
	ULootTableDefinition *GetLootTable();
};


UCLASS(ClassGroup = ("Custom"), meta = (BlueprintSpawnableComponent))
class FAIRFEELINGLOOTRUNTIME_API ULootTableComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLootTableCallback, FName, Specifier);

public:

	UPROPERTY(BlueprintAssignable)
	FOnLootTableCallback OnLootTableCallback;

	// The Loot Table Definition to use for generating Loot
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULootTableDefinition *DefaultLootTable = 0;

	// Generates an array of Loot Recipes based upon the Loot Table Definition
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	TArray<FLootRecipe> MakeRandomLootFromLootTable( const ULootTableDefinition *LootTable );

	// Generates an array of Loot Recipes based upon an Actor implementing the LootInterface
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	TArray<FLootRecipe> MakeRandomLootFromActor( AActor *Actor );

	// Gets the value of a global loot table name param
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	FName GetNameParam(FName ParamName, FName DefaultName = NAME_None);

	// Gets the value of a global loot table float param
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	float GetFloatParam(FName ParamName, float DefaultValue = 0);

	// Sets the value of a global loot table name param
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	void SetNameParam(FName ParamName, FName ParamValue);

	// Sets the value of a global loot table float param
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	void SetFloatParam(FName ParamName, float ParamValue);

protected:
	FLootTableData LootTableData;
};


