// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootTableComponent.h"
#include "LootTableDefinition.h"
#include "FairFeelingLootRuntime.h"
#include "GameFramework/Actor.h"


void ULootGenerationComponent::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	ULootTableDefinition::OnGraphChanged.AddUObject(this, &ULootGenerationComponent::OnLootTableDefinitionRebuilt);
	ULootTableDefinition::OnNodeChanged.AddUObject(this, &ULootGenerationComponent::OnLootTableNodeChanged);
	ULootTableDefinition::OnEdgeChanged.AddUObject(this, &ULootGenerationComponent::OnLootTableEdgeChanged);
#endif // #if WITH_EDITOR
}


void ULootGenerationComponent::EndPlay(const EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);

#if WITH_EDITOR
	ULootTableDefinition::OnGraphChanged.RemoveAll(this);
	ULootTableDefinition::OnNodeChanged.RemoveAll(this);
	ULootTableDefinition::OnEdgeChanged.RemoveAll(this);
#endif // #if WITH_EDITOR
}


#if WITH_EDITOR

void ULootGenerationComponent::OnLootTableNodeChanged(const ULTGenericGraphNode *Node)
{
	if (Node)
	{
		if (auto LTNode = Cast<ULTGraphNode>(Node))
		{
			LTNode->ResetPayloadInitialization(LootTableData);
		}
	}
}


void ULootGenerationComponent::OnLootTableEdgeChanged(const ULTGenericGraphEdge *Edge)
{
	if (Edge)
	{
		if (auto LTNode = Cast<ULTGraphNode>(Edge->StartNode))
		{
			LTNode->ResetPayloadInitialization(LootTableData);
		}
	}
}


void ULootGenerationComponent::OnLootTableDefinitionRebuilt(const ULTGenericGraph *Graph)
{
	if (Graph)
	{
		for (auto Node : Graph->AllNodes)
		{
			if (auto LTNode = Cast<ULTGraphNode>(Node))
			{
				LTNode->ResetPayloadInitialization(LootTableData);
			}
		}
	}
}

#endif // #if WITH_EDITOR

TArray<FLootRecipe> ULootGenerationComponent::MakeRandomLootFromLootTable( const ULootTableDefinition *LootTableDefinition )
{
	TArray<FLootRecipe> Loot;

	LootTableDefinition = LootTableDefinition ? LootTableDefinition : DefaultLootTable;

	if (LootTableDefinition == nullptr)
	{
		UE_LOG(LogFairFeelingLoot, Error, TEXT("Loot Table has no definition specified."));
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
		UE_LOG(LogFairFeelingLoot, Error, TEXT("Loot Table Definition is missing Root Node."));
		return Loot;
	}

	LootTableData.VisitedGraphs.Add(LootTableDefinition);	

	FMakeLootState LootState;
	LootState.RNG = &LootTableData.RNG;
	LootState.LastTime = LootTableData.LastTime;
	RootNode->TraverseNodesAndCollectLoot(LootTableData, LootState, Loot);

	LootTableData.LastTime = LootTableData.GetTime();

	LootTableData.VisitedGraphs.Remove(LootTableDefinition);

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
