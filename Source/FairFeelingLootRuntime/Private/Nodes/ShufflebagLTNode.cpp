﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "ShufflebagLTNode.h"
#include "IntWeightLTEdge.h"
#include <utility>

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UShufflebagLTNode::UShufflebagLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("ShuffleBag", "Shufflebag Choice");
	ContextMenuCategory = LTCATEGORY_RANDOM;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGenericGraphNode* UShufflebagLTNode::PickChild(FLootTableData &LootTable, const FMakeLootState &State) const
{
	int NumChildren = ChildrenNodes.Num();
	RETRIEVE_LTNODE_PAYLOAD(sizeof(float) + sizeof(int) + sizeof(int) * NumChildren);
	DECLARE_LTNODE_ELEMENT(float, SumOfWeights);
	DECLARE_LTNODE_ELEMENT(int, CachedNumChildren);
	int *CardStack = (int*)Payload;
	Payload += sizeof(int)*NumChildren;

	if (*RequiresInitialization)
	{
		*RequiresInitialization = false;

		CachedNumChildren = NumChildren;
		SumOfWeights = 0.0f;
	}

	ensure(CachedNumChildren == NumChildren);
	if ((int)SumOfWeights <= 0.0f)
	{
		SumOfWeights = 0.0f;
		for (int i = 0; i < NumChildren; i++)
		{
			float Weight = 1;
			if (const UIntWeightLTEdge *Edge = Cast<UIntWeightLTEdge>(GetEdge(ChildrenNodes[i])))
				Weight = Edge->Weight;
			SumOfWeights += Weight;
			CardStack[i] = Weight;
		}
	}


	float RandNum = State.RNG->FRandRange(0, SumOfWeights);
	for (int i = 0; i < NumChildren; i++)
	{
		RandNum -= CardStack[i];
		if (RandNum <= 0)
		{
			CardStack[i]--;
			SumOfWeights -= 1.0f;
			return ChildrenNodes[i];
		}
	}

	return nullptr;
}


#if WITH_EDITOR
TSubclassOf<ULTGenericGraphEdge> UShufflebagLTNode::GetEdgeType() const
{
	return UIntWeightLTEdge::StaticClass();
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
