// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "BranchParamLTNode.h"
#include "ComparisonLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UBranchParamLTNode::UBranchParamLTNode()
{

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("BranchNode", "Branch on Param");
	ContextMenuCategory = LTCATEGORY_FLOW;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGraphNode* UBranchParamLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	float TestValue = LootTable.GetFloatParam(ParamName);

	for (const UGenericGraphNode *Node : ChildrenNodes)
	{
		if (const UComparisonLTEdge* Edge = Cast<UComparisonLTEdge>(GetEdge(Node)))
		{
			if (Edge->AllowTraversal(LootTable,TestValue))
			{
				if (const ULTGraphNode *LTNode = Cast<ULTGraphNode>(Node))
				{
					return LTNode->TraverseNodesAndCollectLoot(LootTable, State, Loot);
				}
			}
		}
	}

	return this;
}


#if WITH_EDITOR

TSubclassOf<UGenericGraphEdge> UBranchParamLTNode::GetEdgeType() const
{
	return UComparisonLTEdge::StaticClass();
}

FText UBranchParamLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Param"), FText::FromName(ParamName));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", "Test: {Param}"), Args);
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

