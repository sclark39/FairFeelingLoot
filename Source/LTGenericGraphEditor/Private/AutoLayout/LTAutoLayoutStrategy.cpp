// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "AutoLayout/LTAutoLayoutStrategy.h"
#include "Kismet/KismetMathLibrary.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/SEdNode_LTGenericGraphNode.h"

ULTAutoLayoutStrategy::ULTAutoLayoutStrategy()
{
	Settings = nullptr;
	MaxIteration = 50;
	OptimalDistance = 150;
}

ULTAutoLayoutStrategy::~ULTAutoLayoutStrategy()
{

}

FBox2D ULTAutoLayoutStrategy::GetNodeBound(UEdGraphNode* EdNode)
{
	int32 NodeWidth = GetNodeWidth(Cast<UEdNode_LTGenericGraphNode>(EdNode));
	int32 NodeHeight = GetNodeHeight(Cast<UEdNode_LTGenericGraphNode>(EdNode));
	FVector2D Min(EdNode->NodePosX, EdNode->NodePosY);
	FVector2D Max(EdNode->NodePosX + NodeWidth, EdNode->NodePosY + NodeHeight);
	return FBox2D(Min, Max);
}

FBox2D ULTAutoLayoutStrategy::GetActualBounds(ULTGenericGraphNode* RootNode)
{
	int Level = 0;
	TArray<ULTGenericGraphNode*> CurrLevelNodes = { RootNode };
	TArray<ULTGenericGraphNode*> NextLevelNodes;

	FBox2D Rtn = GetNodeBound(EdGraph->NodeMap[RootNode]);

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			ULTGenericGraphNode* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			Rtn += GetNodeBound(EdGraph->NodeMap[Node]);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
	return Rtn;
}

void ULTAutoLayoutStrategy::RandomLayoutOneTree(ULTGenericGraphNode* RootNode, const FBox2D& Bound)
{
	int Level = 0;
	TArray<ULTGenericGraphNode*> CurrLevelNodes = { RootNode };
	TArray<ULTGenericGraphNode*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			ULTGenericGraphNode* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			UEdNode_LTGenericGraphNode* EdNode_Node = EdGraph->NodeMap[Node];

			EdNode_Node->NodePosX = UKismetMathLibrary::RandomFloatInRange(Bound.Min.X, Bound.Max.X);
			EdNode_Node->NodePosY = UKismetMathLibrary::RandomFloatInRange(Bound.Min.Y, Bound.Max.Y);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
}

int32 ULTAutoLayoutStrategy::GetNodeWidth(UEdNode_LTGenericGraphNode* EdNode)
{
	return EdNode->SEdNode->GetCachedGeometry().GetLocalSize().X;
}

int32 ULTAutoLayoutStrategy::GetNodeHeight(UEdNode_LTGenericGraphNode* EdNode)
{
	return EdNode->SEdNode->GetCachedGeometry().GetLocalSize().Y;
}

