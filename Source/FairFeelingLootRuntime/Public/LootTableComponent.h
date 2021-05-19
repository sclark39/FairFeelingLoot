﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LootTable.h"

#include "LootTableComponent.generated.h"



UCLASS(ClassGroup = ("Custom"), meta = (BlueprintSpawnableComponent))
class FAIRFEELINGLOOTRUNTIME_API ULootTableComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLootTableCallback, FName, Specifier);

public:
	UPROPERTY(EditAnywhere)
	FLootTable LootTable;

	UPROPERTY(BlueprintAssignable)
	FOnLootTableCallback OnLootTableCallback;

	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	TArray<FLootRecipe> MakeRandomLoot();

	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	FName GetNameParam(FName ParamName, FName DefaultName = NAME_None);

	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	float GetFloatParam(FName ParamName, float DefaultValue = 0);

	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	void SetNameParam(FName ParamName, FName ParamValue);

	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	void SetFloatParam(FName ParamName, float ParamValue);
};


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API ULootTableBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	// Change sigma to change how clustered around the mean the value is. Lower values may be more performance heavy
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
		static float NextGaussian(const FRandomStream &RNG, float Min, float Max, float Sigma = 2.5f);


};
