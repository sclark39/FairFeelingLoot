// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootTableComponent.h"
#include "LootTableDefinition.h"


TArray<FLootRecipe> ULootTableComponent::MakeRandomLoot()
{
	TArray<FLootRecipe> Loot;

	if (LootTable.Definition == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Loot Table has no definition specified."));
		return Loot;
	}

	// Initialize
	if (LootTable.bRequiresInitialization)
	{
		LootTable.RNG.Initialize(LootTable.InitialSeed);
		if (LootTable.bShouldRandomizeSeed)
			LootTable.RNG.GenerateNewSeed();

		LootTable.EntropyState.RNG = &LootTable.RNG;
		LootTable.World = GetWorld();

		LootTable.bRequiresInitialization = false;
	}

	// Make Loot
	const URootLTGraphNode *RootNode = LootTable.Definition->GetRootNode();
	if (!RootNode)
	{
		UE_LOG(LogTemp, Error, TEXT("Loot Table Definition is missing Root Node."));
		return Loot;
	}

	LootTable.VisitedGraphs.Add(LootTable.Definition);

	RootNode->TraverseNodesAndCollectLoot(LootTable, LootTable.EntropyState, Loot);

	LootTable.EntropyState.LastTime = LootTable.GetTime();

	return Loot;
}

FName ULootTableComponent::GetNameParam(FName ParamName, FName DefaultName)
{
	return LootTable.GetNameParam(ParamName, DefaultName);
}

float ULootTableComponent::GetFloatParam(FName ParamName, float DefaultValue)
{
	return LootTable.GetFloatParam(ParamName, DefaultValue);
}

void ULootTableComponent::SetNameParam(FName ParamName, FName ParamValue)
{
	FName &Value = LootTable.NameParams.FindOrAdd(ParamName);
	Value = ParamValue;
}

void ULootTableComponent::SetFloatParam(FName ParamName, float ParamValue)
{
	float &Value = LootTable.FloatParams.FindOrAdd(ParamName);
	Value = ParamValue;
}
