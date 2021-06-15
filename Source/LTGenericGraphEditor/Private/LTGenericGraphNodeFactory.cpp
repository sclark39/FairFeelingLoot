// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGenericGraphNodeFactory.h"
#include <EdGraph/EdGraphNode.h>
#include "LTGenericGraphAssetEditor/SEdNode_LTGenericGraphEdge.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/SEdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphEdge.h"

TSharedPtr<class SGraphNode> FGraphPanelNodeFactory_LTGenericGraph::CreateNode(UEdGraphNode* Node) const
{
	if (UEdNode_LTGenericGraphNode* EdNode_GraphNode = Cast<UEdNode_LTGenericGraphNode>(Node))
	{
		return SNew(SEdNode_LTGenericGraphNode, EdNode_GraphNode);
	}
	else if (UEdNode_LTGenericGraphEdge* EdNode_Edge = Cast<UEdNode_LTGenericGraphEdge>(Node))
	{
		return SNew(SEdNode_LTGenericGraphEdge, EdNode_Edge);
	}
	return nullptr;
}

