﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "SwitchLTNode.h"
#include "NamedLTEdge.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // #if WITH_EDITOR

#define LOCTEXT_NAMESPACE "LootTableDefinition"

static const FName DefaultName(TEXT("Default"));

USwitchLTNode::USwitchLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("SwitchNode", "Switch on Name Param");
	ContextMenuCategory = LTCATEGORY_FLOW;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGenericGraphNode* USwitchLTNode::PickChild(FLootTableData &LootTable, const FMakeLootState &State) const
{
	FName NameParam = LootTable.GetNameParamFromLT(Cast<ULootTableDefinition>(GetGraph()), ParamName, DefaultValue);
	const ULTGenericGraphNode *DefaultNode = nullptr;

	for (const auto *Node : ChildrenNodes)
	{
		if (const UNamedLTEdge *Edge = Cast<const UNamedLTEdge>(GetEdge(Node)))
		{
			if (Edge->Value == NameParam)
				return Node;
			else if (Edge->Value == DefaultName)
				DefaultNode = Node;
		}
	}

	return DefaultNode;
}




#if WITH_EDITOR	
FText USwitchLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Name"), FText::FromName(ParamName));
	return FText::Format(LOCTEXT("SwitchNodeTitle", "Switch on {Name}"), Args);
}

const FSlateBrush*  USwitchLTNode::GetNodeIcon() const
{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.DoesPathExist.Icon"));
#else // #if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.DoesPathExist.Icon"));
#endif // #else ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
}

TSubclassOf<ULTGenericGraphEdge> USwitchLTNode::GetEdgeType() const
{
	return UNamedLTEdge::StaticClass();
}
#endif // #if WITH_EDITOR	


#undef LOCTEXT_NAMESPACE 
