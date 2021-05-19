// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "SequenceLTNode.h"
#include "PriorityLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

USequenceLTNode::USequenceLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("SequenceNode", "Sequence");
	ContextMenuCategory = LTCATEGORY_FLOW;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGraphNode* USequenceLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	int NumChildren = ChildrenNodes.Num();
	RETRIEVE_LTNODE_PAYLOAD(sizeof(int) + sizeof(int) * NumChildren);
	DECLARE_LTNODE_ELEMENT(int, CachedNumChildren);
	int *CallOrder = (int*)Payload;
	Payload += sizeof(int)*NumChildren;

	if (*RequiresInitialization)
	{
		*RequiresInitialization = false;

		TArray<int> ToSort;
		CachedNumChildren = NumChildren;
		for (int i = 0; i < NumChildren; i++)
			ToSort.Push(i);

		ToSort.Sort( [&](int A, int B)
		{
			UPriorityLTEdge *EdgeA = Cast<UPriorityLTEdge>( GetEdge(ChildrenNodes[A]) );
			UPriorityLTEdge *EdgeB = Cast<UPriorityLTEdge>( GetEdge(ChildrenNodes[B]) );

			int AWeight = EdgeA ? EdgeA->Priority : 1;
			int BWeight = EdgeB ? EdgeB->Priority : 1;

			return AWeight < BWeight;
		});

		for (int i = 0; i < NumChildren; i++)
			CallOrder[i] = ToSort[i];
	}

	ensure(CachedNumChildren == NumChildren);

	for (int i = 0; i < NumChildren; i++)
	{
		int NodeId = CallOrder[i];
		if (const ULTGraphNode *LTNode = Cast<const ULTGraphNode>(ChildrenNodes[NodeId]))
		{
			LTNode->TraverseNodesAndCollectLoot(LootTable, State, Loot);
		}
	}

	return this;
}

#if WITH_EDITOR

TSubclassOf<ULTGenericGraphEdge> USequenceLTNode::GetEdgeType() const
{
	return bOrderedSequence ? UPriorityLTEdge::StaticClass() : nullptr;
}

const FSlateBrush*  USequenceLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Composite.Sequence.Icon"));
}

#endif

#undef LOCTEXT_NAMESPACE 

