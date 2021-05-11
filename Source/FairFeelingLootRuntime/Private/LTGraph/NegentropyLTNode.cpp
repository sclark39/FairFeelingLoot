// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGraph/NegentropyLTNode.h"
#include "LTGraph/WeightedLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"


UNegentropyLTNode::UNegentropyLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("Negentropy", "Negentropy Branch");
	ContextMenuCategory = LTCATEGORY_RANDOM;
	ChildrenLimitType = ELTGenericGraphNodeLimit::Limited;
	ChildrenLimit = 2;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGenericGraphNode* UNegentropyLTNode::PickChild(FLootTable &LootTable, const FEntropyState &State) const
{
	if (ChildrenNodes.Num() < 2)
		return Super::PickChild(LootTable, State);

	RETRIEVE_LTNODE_PAYLOAD(sizeof(float) + sizeof(bool) + sizeof(float));
	DECLARE_LTNODE_ELEMENT(float, Entropy);
	DECLARE_LTNODE_ELEMENT(bool, bDynamicWeights);
 	DECLARE_LTNODE_ELEMENT(float, Probability);

	bool bNeedProbabilityCalc = false;

	if (*RequiresInitialization)
	{
		const UWeightedLTEdge *Edge0 = Cast<UWeightedLTEdge>(Edges[ChildrenNodes[0]]);
		const UWeightedLTEdge *Edge1 = Cast<UWeightedLTEdge>(Edges[ChildrenNodes[1]]);
		if (!Edge0 || !Edge1)
		{
			UE_LOG(LogTemp, Error, TEXT("Negentropy node requires two edges."));
			return nullptr;
		}

		*RequiresInitialization = false;
		
		Entropy = State.RNG->FRand();
		bDynamicWeights = ( Edge0->bUseDynamicWeight || Edge1->bUseDynamicWeight );
		bNeedProbabilityCalc = true;
	}
	else
	{
		bNeedProbabilityCalc = bDynamicWeights;
	}

	if (bNeedProbabilityCalc)
	{
		float EdgeWeight[] = {0,0};

		for ( int i = 0; i < 2; i++ )
		{
			const UWeightedLTEdge *Edge = Cast<UWeightedLTEdge>(Edges[ChildrenNodes[i]]);
			EdgeWeight[i] = Edge->GetWeight(LootTable);
		}

		const float denom = (EdgeWeight[0] + EdgeWeight[1]);
		if (denom <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Negentropy node edge weights must be greater than 0."));		
			return nullptr;
		}
		Probability = EdgeWeight[1] / denom;
	}

	float Time = LootTable.GetTime();
	if (State.LastTime + TimeUntilEntropyReset < Time)
	{
		Entropy = State.RNG->FRand();
	}

	Entropy += Probability;
	if (1.0f - SMALL_NUMBER < Entropy)
	{
		Entropy -= FMath::Floor(Entropy);
		return ChildrenNodes[1];
	}

	return ChildrenNodes[0];
}

#if WITH_EDITOR
TSubclassOf<ULTGenericGraphEdge> UNegentropyLTNode::GetEdgeType() const
{
	return UWeightedLTEdge::StaticClass();
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
