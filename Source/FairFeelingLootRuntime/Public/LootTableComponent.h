// Copyright 2021 Skyler Clark. All Rights Reserved.

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLootTable LootTable;

	UPROPERTY(BlueprintAssignable)
	FOnLootTableCallback OnLootTableCallback;

	UFUNCTION(BlueprintCallable, Category = "Loot Table")
	TArray<FLootRecipe> MakeRandomLoot();

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

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"), Category = "Math|Random")
		static TArray<FLootRecipe> MakeRandomLoot(UPARAM(ref) FLootTable &LootTable, UObject *WorldContext);

	UFUNCTION(BlueprintCallable, Category = "Loot Table")
		static void SetLootTableNameParam(UPARAM(ref) FLootTable &LootTable, FName ParamName, FName ParamValue);

	UFUNCTION(BlueprintCallable, Category = "Loot Table")
		static void SetLootTableFloatParam(UPARAM(ref) FLootTable &LootTable, FName ParamName, float ParamValue);

	// Change sigma to change how clustered around the mean the value is. Lower values may be more performance heavy
	UFUNCTION(BlueprintCallable, Category = "Loot Table")
		static float NextGaussian(const FRandomStream &RNG, float Min, float Max, float Sigma = 2.5f);


};
