// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootTableComponent.h"
#include "LootTableDefinition.h"


TArray<FLootRecipe> ULootGenerationComponent::MakeRandomLootFromLootTable( const ULootTableDefinition *LootTableDefinition )
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

TArray<FLootRecipe> ULootGenerationComponent::MakeRandomLootFromActor(AActor *Actor)
{
	if (Actor && Actor->Implements<ULootSourceInterface>())
	{
		const ULootTableDefinition *LootTable = ILootSourceInterface::Execute_GetLootTable(Actor);
		return MakeRandomLootFromLootTable(LootTable);
	}
	return TArray<FLootRecipe>();
}

TArray<FLootRecipe> ULootGenerationComponent::MakeRandomLootFromLootSource(TScriptInterface<ILootSourceInterface> LootSource)
{
	return  MakeRandomLootFromLootTable(LootSource->GetLootTable());
}

FName ULootGenerationComponent::GetGlobalNameParam(FName ParamName, FName DefaultValue) const
{
	return LootTableData.GetNameParam(ParamName, DefaultValue);
}

float ULootGenerationComponent::GetGlobalFloatParam(FName ParamName, float DefaultValue) const
{
	return LootTableData.GetFloatParam(ParamName, DefaultValue);
}

void ULootGenerationComponent::SetGlobalNameParam(FName ParamName, FName ParamValue)
{
	LootTableData.SetNameParam(ParamName, ParamValue);
}

void ULootGenerationComponent::SetGlobalFloatParam(FName ParamName, float ParamValue)
{
	LootTableData.SetFloatParam(ParamName, ParamValue);
}

FName ULootGenerationComponent::GetNameParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, FName DefaultValue) const
{
	return LootTableData.GetNameParamFromLT(LootTable, ParamName, DefaultValue);
}

float ULootGenerationComponent::GetFloatParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, float DefaultValue) const
{
	return LootTableData.GetFloatParamFromLT(LootTable, ParamName, DefaultValue);
}

void ULootGenerationComponent::SetNameParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, FName ParamValue)
{
	if (LootTable)
		LootTableData.SetNameParamForLT(LootTable, ParamName, ParamValue);
}

void ULootGenerationComponent::SetFloatParamForLootTable(const ULootTableDefinition *LootTable, FName ParamName, float ParamValue)
{
	if (LootTable)
		LootTableData.SetFloatParamForLT(LootTable, ParamName, ParamValue);
}
