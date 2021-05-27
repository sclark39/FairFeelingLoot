// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "LootTable.h"
#include "LootTableBlueprintLibrary.generated.h"

UCLASS()
class FAIRFEELINGLOOTRUNTIME_API ULootTableBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	// Get Name for this piece of Loot
	UFUNCTION(BlueprintPure, Category = "Loot")
	static FName GetLootName(UPARAM(ref) const FLootRecipe &Loot)
	{
		return Loot.Name;
	}

	// Get Type for this piece of Loot
	UFUNCTION(BlueprintPure, Category = "Loot")
	static FGameplayTag GetLootType(UPARAM(ref) const FLootRecipe &Loot)
	{
		return Loot.Type;
	}

	// Get Array of Tags for this piece of Loot
	UFUNCTION(BlueprintPure, Category = "Loot")
	static void GetLootTags(UPARAM(ref) const FLootRecipe &Loot, TArray<FGameplayTag>& Tags) 
	{
		Loot.Tags.GetGameplayTagArray(Tags);
	}

	// Check if this Loot has a specific tag
	UFUNCTION(BlueprintPure, Category = "Loot")
	static bool LootHasTag(UPARAM(ref) const FLootRecipe &Loot, FGameplayTag Tag)
	{
		return Loot.Tags.HasTag(Tag);
	}

	// Get Array of Stats for this piece of loot
	UFUNCTION(BlueprintPure, Category = "Loot")
	static void GetLootStats(UPARAM(ref) const FLootRecipe &Loot, TArray<FLootRecipeStat>& Stats)
	{
		Stats = Loot.Stats;
	}

	// Check if this Loot has a specific stat
	UFUNCTION(BlueprintPure, Category = "Loot")
	static bool LootHasStat(UPARAM(ref) const FLootRecipe &Loot, FGameplayTag StatType)
	{
		return Loot.StatLookup.Contains(StatType);
	}

	// Set name for this Loot
	UFUNCTION(BlueprintCallable, Category = "Loot")
	static void SetLootName(UPARAM(ref) FLootRecipe &Loot, FName Name)
	{
		Loot.Name = Name;
	}

	// Set type for this Loot
	UFUNCTION(BlueprintCallable, Category = "Loot")
	static void SetLootType(UPARAM(ref) FLootRecipe &Loot, FGameplayTag Type)
	{
		Loot.Type = Type;
	}

	// Add a tag to this Loot
	UFUNCTION(BlueprintCallable, Category = "Loot")
	static void AddLootTag(UPARAM(ref) FLootRecipe &Loot, FGameplayTag Tag)
	{
		Loot.Tags.AddTag(Tag);
	}

	// Remove a tag from this Loot
	UFUNCTION(BlueprintCallable, Category = "Loot")
	static void RemoveLootTag(UPARAM(ref) FLootRecipe &Loot, FGameplayTag Tag)
	{
		Loot.Tags.RemoveTag(Tag);
	}

	// Get type for a specific loot stat 
	UFUNCTION(BlueprintPure, Category = "Loot", meta = (AdvancedDisplay = "DefaultValue"))
	static FGameplayTag GetLootStatType(UPARAM(ref) const FLootRecipeStat &LootStat)
	{
		return LootStat.StatType;
	}


	// Get value for a specific loot stat
	UFUNCTION(BlueprintPure, Category = "Loot", meta = (AdvancedDisplay = "DefaultValue"))
	static float GetLootStatValue(UPARAM(ref) const FLootRecipeStat &LootStat)
	{
		return LootStat.StatValue;
	}


	// Get value for a specific stat for this Loot
	UFUNCTION(BlueprintPure, Category = "Loot", meta = (AdvancedDisplay = "DefaultValue"))
	static float GetLootStat(UPARAM(ref) const FLootRecipe &Loot, FGameplayTag StatType, float DefaultValue = 0);

	// Set a specific stat on this Loot
	UFUNCTION(BlueprintCallable, Category = "Loot")
	static void SetLootStat(UPARAM(ref) FLootRecipe &Loot, FGameplayTag StatType, float StatValue);

	// Remove a stat from this Loot
	UFUNCTION(BlueprintCallable, Category = "Loot")
	static void RemoveLootStat(UPARAM(ref) FLootRecipe &Loot, FGameplayTag StatType);

	// Change sigma to change how clustered around the mean the value is. Lower values may be more performance heavy
	//UFUNCTION(BlueprintCallable, Category = "Loot Table")
	//static float NextGaussian(const FRandomStream &RNG, float Min, float Max, float Sigma = 2.5f);


};