#include "LTGenericGraph.h"
#include "LTGenericGraphRuntimePCH.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "LTGenericGraph"

#if WITH_EDITOR
ULTGenericGraph::FGenericGraphSimpleDelegate ULTGenericGraph::OnGraphChanged;
ULTGenericGraph::FGenericGraphEdgeSimpleDelegate ULTGenericGraph::OnEdgeChanged;
ULTGenericGraph::FGenericGraphNodeSimpleDelegate ULTGenericGraph::OnNodeChanged;
#endif // #if WITH_EDITOR

ULTGenericGraph::ULTGenericGraph()
{
	NodeType = ULTGenericGraphNode::StaticClass();
	EdgeType = ULTGenericGraphEdge::StaticClass();

	bEdgeEnabled = true;

#if WITH_EDITORONLY_DATA
	EdGraph = nullptr;

	bCanRenameNode = true;

	bRebuildAfterEveryChange = false;
#endif
}

ULTGenericGraph::~ULTGenericGraph()
{

}

void ULTGenericGraph::Print(bool ToConsole /*= true*/, bool ToScreen /*= true*/)
{
	int Level = 0;
	TArray<ULTGenericGraphNode*> CurrLevelNodes = RootNodes;
	TArray<ULTGenericGraphNode*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			ULTGenericGraphNode* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			FString Message = FString::Printf(TEXT("%s, Level %d"), *Node->GetDescription().ToString(), Level);

			if (ToConsole)
			{
				LOG_INFO(TEXT("%s"), *Message);
			}

			if (ToScreen && GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, Message);
			}

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

int ULTGenericGraph::GetLevelNum() const
{
	int Level = 0;
	TArray<ULTGenericGraphNode*> CurrLevelNodes = RootNodes;
	TArray<ULTGenericGraphNode*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			ULTGenericGraphNode* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}

	return Level;
}

void ULTGenericGraph::GetNodesByLevel(int Level, TArray<ULTGenericGraphNode*>& Nodes)
{
	int CurrLEvel = 0;
	TArray<ULTGenericGraphNode*> NextLevelNodes;

	Nodes = RootNodes;

	while (Nodes.Num() != 0)
	{
		if (CurrLEvel == Level)
			break;

		for (int i = 0; i < Nodes.Num(); ++i)
		{
			ULTGenericGraphNode* Node = Nodes[i];
			check(Node != nullptr);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}

		Nodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++CurrLEvel;
	}
}

void ULTGenericGraph::ClearGraph()
{
	for (int i = 0; i < AllNodes.Num(); ++i)
	{
		ULTGenericGraphNode* Node = AllNodes[i];
		if (Node)
		{
			Node->ParentNodes.Empty();
			Node->ChildrenNodes.Empty();
			Node->Edges.Empty();
		}
	}

	AllNodes.Empty();
	RootNodes.Empty();
}

#undef LOCTEXT_NAMESPACE
