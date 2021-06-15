// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "LTGenericGraph.h"
#include "LTGenericGraphAssetEditor/EdGraph_LTGenericGraph.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphEdge.h"
#include "LTGenericGraphAssetEditor/Settings_LTGenericGraphEditor.h"
#include "LTAutoLayoutStrategy.generated.h"

UCLASS(abstract)
class LTGENERICGRAPHEDITOR_API ULTAutoLayoutStrategy : public UObject
{
	GENERATED_BODY()
public:
	ULTAutoLayoutStrategy();
	virtual ~ULTAutoLayoutStrategy();

	virtual void Layout(UEdGraph* G) {};

	class ULTGenericGraphEditorSettings* Settings;

protected:
	int32 GetNodeWidth(UEdNode_LTGenericGraphNode* EdNode);

	int32 GetNodeHeight(UEdNode_LTGenericGraphNode* EdNode);

	FBox2D GetNodeBound(UEdGraphNode* EdNode);

	FBox2D GetActualBounds(ULTGenericGraphNode* RootNode);

	virtual void RandomLayoutOneTree(ULTGenericGraphNode* RootNode, const FBox2D& Bound);

protected:
	ULTGenericGraph* Graph;
	UEdGraph_LTGenericGraph* EdGraph;
	int32 MaxIteration;
	int32 OptimalDistance;
};
