// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGraph/RandomLTNode.h"
#include "LTGraph/WeightedLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

URandomLTNode::URandomLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("PickRandom", "Random Choice");
	ContextMenuCategory = LTCATEGORY_RANDOM;
#endif // #if WITH_EDITORONLY_DATA
}


const ULTGenericGraphNode* URandomLTNode::PickChild(FLootTable &LootTable, const FEntropyState &State) const
{
	RETRIEVE_LTNODE_PAYLOAD(sizeof(bool) + sizeof(float));
	DECLARE_LTNODE_ELEMENT(bool, bDynamicWeights);
	DECLARE_LTNODE_ELEMENT(float, SumOfWeights);

	bool bNeedSumAccum = false;

	if (*RequiresInitialization)
	{
		*RequiresInitialization = false;
		bNeedSumAccum = true;
	
		for (const ULTGenericGraphNode *Node : ChildrenNodes)
		{
			const ULTGenericGraphEdge *EdgeUncast = GetEdge(Node);
			if (const UWeightedLTEdge *Edge = Cast<const UWeightedLTEdge>(GetEdge(Node)))
			{
				if (Edge->bUseDynamicWeight)
				{
					bDynamicWeights = true;
					break;
				}
			}
		}
 	}
	else
	{
		bNeedSumAccum = bDynamicWeights;
	}
	
	if (bNeedSumAccum)
	{
		SumOfWeights = 0;
		for (const ULTGenericGraphNode *Node : ChildrenNodes)
		{
			if (const UWeightedLTEdge *Edge = Cast<const UWeightedLTEdge>(GetEdge(Node)))
			{
				SumOfWeights += Edge->GetWeight(LootTable);
			}
		}
	}

	float RandNum = State.RNG->FRandRange(0, SumOfWeights);
	for (const ULTGenericGraphNode *Node : ChildrenNodes)
	{
		if (const UWeightedLTEdge *Edge = Cast<const UWeightedLTEdge>(GetEdge(Node)))
		{
			RandNum -= Edge->GetWeight(LootTable);
			if (RandNum <= 0)
				return Node;
		}
	}
	
	return nullptr;
}

#if WITH_EDITOR
TSubclassOf<ULTGenericGraphEdge> URandomLTNode::GetEdgeType() const
{
	return UWeightedLTEdge::StaticClass();
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
