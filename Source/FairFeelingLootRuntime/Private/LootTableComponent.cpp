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
		LootTableData.RNG.Initialize(InitialSeed);
		if (bShouldRandomizeSeed)
			LootTableData.RNG.GenerateNewSeed();

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

	FMakeLootState LootState;
	LootState.RNG = &LootTableData.RNG;
	LootState.LastTime = LootTableData.LastTime;
	RootNode->TraverseNodesAndCollectLoot(LootTableData, LootState, Loot);

	LootTableData.LastTime = LootTableData.GetTime();

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

TArray<FLootRecipe> ULootTableComponent::MakeRandomLootFromLootSource(TScriptInterface<ILootTableSpecifier> LootSource)
{
	return  MakeRandomLootFromLootTable(LootSource->GetLootTable());
}

FName ULootTableComponent::GetGlobalNameParam(FName ParamName, FName DefaultValue) const
{
	return LootTableData.GetNameParam(ParamName, DefaultValue);
}

float ULootTableComponent::GetGlobalFloatParam(FName ParamName, float DefaultValue) const
{
	return LootTableData.GetFloatParam(ParamName, DefaultValue);
}

void ULootTableComponent::SetGlobalNameParam(FName ParamName, FName ParamValue)
{
	LootTableData.SetNameParam(ParamName, ParamValue);
}

void ULootTableComponent::SetGlobalFloatParam(FName ParamName, float ParamValue)
{
	LootTableData.SetFloatParam(ParamName, ParamValue);
}

FName ULootTableComponent::GetNameParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, FName DefaultValue) const
{
	return LootTableData.GetNameParamFromLT(LootTable, ParamName, DefaultValue);
}

float ULootTableComponent::GetFloatParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, float DefaultValue) const
{
	return LootTableData.GetFloatParamFromLT(LootTable, ParamName, DefaultValue);
}

void ULootTableComponent::SetNameParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, FName ParamValue)
{
	if (LootTable)
		LootTableData.SetNameParamForLT(LootTable, ParamName, ParamValue);
}

void ULootTableComponent::SetFloatParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, float ParamValue)
{
	if (LootTable)
		LootTableData.SetFloatParamForLT(LootTable, ParamName, ParamValue);
}
