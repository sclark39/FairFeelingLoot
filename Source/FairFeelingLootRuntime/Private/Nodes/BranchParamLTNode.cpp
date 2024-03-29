﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "BranchParamLTNode.h"
#include "ComparisonLTEdge.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // #if WITH_EDITOR

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UBranchParamLTNode::UBranchParamLTNode()
{

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("BranchNode", "Test Float Param");
	ContextMenuCategory = LTCATEGORY_FLOW;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGenericGraphNode* UBranchParamLTNode::PickChild(FLootTableData &LootTable, const FMakeLootState &State) const
{
	float TestValue = LootTable.GetFloatParamFromLT(Cast<ULootTableDefinition>(GetGraph()), ParamName, DefaultValue);

	for (const auto *Node : ChildrenNodes)
	{
		if (const UComparisonLTEdge* Edge = Cast<UComparisonLTEdge>(GetEdge(Node)))
		{
			if (Edge->AllowTraversal(LootTable, TestValue))
			{
				if (const ULTGraphNode *LTNode = Cast<ULTGraphNode>(Node))
				{
					return LTNode;
				}
			}
		}
	}

	return nullptr;
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
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.DoesPathExist.Icon"));;
#else // #if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.DoesPathExist.Icon"));
#endif // #else ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

