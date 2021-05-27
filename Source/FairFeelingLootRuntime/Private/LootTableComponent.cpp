// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootTableComponent.h"
#include "LootTableDefinition.h"


TArray<FLootRecipe> ULootTableComponent::MakeRandomLootFromLootTable( const ULootTableDefinition *LootTableDefinition )
{
	TArray<FLootRecipe> Loot;

	LootTableDefinition = LootTableDefinition ? LootTableDefinition : DefaultLootTable;

	if (LootTableDefinition == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Loot Table has no definition specified."));
		return Loot;
	}

	// Initialize
	if (LootTableData.bRequiresInitialization)
	{
		LootTableData.RNG.Initialize(LootTableData.InitialSeed);
		if (LootTableData.bShouldRandomizeSeed)
			LootTableData.RNG.GenerateNewSeed();

		LootTableData.EntropyState.RNG = &LootTableData.RNG;
		LootTableData.World = GetWorld();

		LootTableData.bRequiresInitialization = false;
	}

	// Make Loot
	const URootLTGraphNode *RootNode = LootTableDefinition->GetRootNode();
	if (!RootNode)
	{
		UE_LOG(LogTemp, Error, TEXT("Loot Table Definition is missing Root Node."));
		return Loot;
	}

	LootTableData.VisitedGraphs.Add(LootTableDefinition);

	RootNode->TraverseNodesAndCollectLoot(LootTableData, LootTableData.EntropyState, Loot);

	LootTableData.EntropyState.LastTime = LootTableData.GetTime();

	return Loot;
}

TArray<FLootRecipe> ULootTableComponent::MakeRandomLootFromActor(AActor *Actor)
{
	if (Actor && Actor->Implements<ULootTableSpecifier>())
	{
		const ULootTableDefinition *LootTable = ILootTableSpecifier::Execute_GetLootTable(Actor);
		return MakeRandomLootFromLootTable(LootTable);
	}
	return TArray<FLootRecipe>();
}

FName ULootTableComponent::GetNameParam(FName ParamName, FName DefaultName)
{
	return LootTableData.GetNameParam(ParamName, DefaultName);
}

float ULootTableComponent::GetFloatParam(FName ParamName, float DefaultValue)
{
	return LootTableData.GetFloatParam(ParamName, DefaultValue);
}

void ULootTableComponent::SetNameParam(FName ParamName, FName ParamValue)
{
	FName &Value = LootTableData.NameParams.FindOrAdd(ParamName);
	Value = ParamValue;
}

void ULootTableComponent::SetFloatParam(FName ParamName, float ParamValue)
{
	float &Value = LootTableData.FloatParams.FindOrAdd(ParamName);
	Value = ParamValue;
}
