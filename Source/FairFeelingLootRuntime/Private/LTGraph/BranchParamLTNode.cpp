// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGraph/BranchParamLTNode.h"
#include "LTGraph/ComparisonLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UBranchParamLTNode::UBranchParamLTNode()
{

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("BranchNode", "Test Float Param");
	ContextMenuCategory = LTCATEGORY_FLOW;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGraphNode* UBranchParamLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	float TestValue = LootTable.GetFloatParam(ParamName, DefaultValue);

	for (const auto *Node : ChildrenNodes)
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

TSubclassOf<ULTGenericGraphEdge> UBranchParamLTNode::GetEdgeType() const
{
	return UComparisonLTEdge::StaticClass();
}

FText UBranchParamLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Param"), FText::FromName(ParamName));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", "Test: {Param}"), Args);
}

const FSlateBrush*  UBranchParamLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.DoesPathExist.Icon"));
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

