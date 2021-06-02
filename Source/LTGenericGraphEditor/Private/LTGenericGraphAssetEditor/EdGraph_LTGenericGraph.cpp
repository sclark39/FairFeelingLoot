#include "LTGenericGraphAssetEditor/EdGraph_LTGenericGraph.h"
#include "LTGenericGraphEditorPCH.h"
#include "LTGenericGraph.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphEdge.h"

#include "LTGenericGraphEditorStrings.h"

UEdGraph_LTGenericGraph::UEdGraph_LTGenericGraph()
{

}

UEdGraph_LTGenericGraph::~UEdGraph_LTGenericGraph()
{

}

void UEdGraph_LTGenericGraph::RebuildLTGenericGraphIncremental()
{
	ULTGenericGraph* Graph = GetLTGenericGraph();
	if (Graph->ShouldAllowIncrementalRebuild())
	{
		RebuildLTGenericGraph();
	}
}

void UEdGraph_LTGenericGraph::RebuildLTGenericGraph()
{
	UE_LOG(LogLTGenericGraph, Verbose, TEXT(GGS_REBUILD_GRAPH_LOG));

	ULTGenericGraph* Graph = GetLTGenericGraph();

	Clear();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UEdNode_LTGenericGraphNode* EdNode = Cast<UEdNode_LTGenericGraphNode>(Nodes[i]))
		{
			if (EdNode->LTGenericGraphNode == nullptr)
				continue;

			ULTGenericGraphNode* LTGenericGraphNode = EdNode->LTGenericGraphNode;

			NodeMap.Add(LTGenericGraphNode, EdNode);

			Graph->AllNodes.Add(LTGenericGraphNode);

			for (int PinIdx = 0; PinIdx < EdNode->Pins.Num(); ++PinIdx)
			{
				UEdGraphPin* Pin = EdNode->Pins[PinIdx];

				if (Pin->Direction != EEdGraphPinDirection::EGPD_Output)
					continue;

				for (int LinkToIdx = 0; LinkToIdx < Pin->LinkedTo.Num(); ++LinkToIdx)
				{
					ULTGenericGraphNode* ChildNode = nullptr;
					if (UEdNode_LTGenericGraphNode* EdNode_Child = Cast<UEdNode_LTGenericGraphNode>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						ChildNode = EdNode_Child->LTGenericGraphNode;
					}
					else if (UEdNode_LTGenericGraphEdge* EdNode_Edge = Cast<UEdNode_LTGenericGraphEdge>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						UEdNode_LTGenericGraphNode* Child = EdNode_Edge->GetEndNode();;
						if (Child != nullptr)
						{
							ChildNode = Child->LTGenericGraphNode;
						}
					}

					if (ChildNode != nullptr)
					{
						LTGenericGraphNode->ChildrenNodes.Add(ChildNode);

						ChildNode->ParentNodes.Add(LTGenericGraphNode);
					}
					else
					{
						LOG_ERROR(TEXT(GGS_REBUILD_GRAPH_ERR_NO_NODE));
					}
				}
			}
		}
		else if (UEdNode_LTGenericGraphEdge* EdgeNode = Cast<UEdNode_LTGenericGraphEdge>(Nodes[i]))
		{
			UEdNode_LTGenericGraphNode* StartNode = EdgeNode->GetStartNode();
			UEdNode_LTGenericGraphNode* EndNode = EdgeNode->GetEndNode();
			ULTGenericGraphEdge* Edge = EdgeNode->LTGenericGraphEdge;

			if (StartNode == nullptr || EndNode == nullptr || Edge == nullptr 
				|| StartNode->LTGenericGraphNode == nullptr 
				|| EndNode->LTGenericGraphNode == nullptr)
			{
				LOG_ERROR(TEXT(GGS_REBUILD_GRAPH_ERR_BAD_EDGE));
				continue;
			}

			EdgeMap.Add(Edge, EdgeNode);

			Edge->Graph = Graph;
			Edge->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
			Edge->StartNode = StartNode->LTGenericGraphNode;
			Edge->EndNode = EndNode->LTGenericGraphNode;
			Edge->StartNode->Edges.Add(Edge->EndNode, Edge);
		}
	}

	for (int i = 0; i < Graph->AllNodes.Num(); ++i)
	{
		ULTGenericGraphNode* Node = Graph->AllNodes[i];
		if (Node->ParentNodes.Num() == 0)
		{
			Graph->RootNodes.Add(Node);

			SortNodes(Node);
		}

		Node->Graph = Graph;
		Node->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
	}

	Graph->RootNodes.Sort([&](const ULTGenericGraphNode& L, const ULTGenericGraphNode& R)
	{
		UEdNode_LTGenericGraphNode* EdNode_LNode = NodeMap[&L];
		UEdNode_LTGenericGraphNode* EdNode_RNode = NodeMap[&R];
		return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
	});

	ULTGenericGraph::OnGraphChanged.Broadcast(Graph);
}

ULTGenericGraph* UEdGraph_LTGenericGraph::GetLTGenericGraph() const
{
	return CastChecked<ULTGenericGraph>(GetOuter());
}

bool UEdGraph_LTGenericGraph::Modify(bool bAlwaysMarkDirty /*= true*/)
{
	bool Rtn = Super::Modify(bAlwaysMarkDirty);

	GetLTGenericGraph()->Modify();

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		Nodes[i]->Modify();
	}

	RebuildLTGenericGraphIncremental();

	return Rtn;
}

void UEdGraph_LTGenericGraph::Clear()
{
	ULTGenericGraph* Graph = GetLTGenericGraph();

	Graph->ClearGraph();
	NodeMap.Reset();
	EdgeMap.Reset();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UEdNode_LTGenericGraphNode* EdNode = Cast<UEdNode_LTGenericGraphNode>(Nodes[i]))
		{
			ULTGenericGraphNode* LTGenericGraphNode = EdNode->LTGenericGraphNode;
			if (LTGenericGraphNode)
			{
				LTGenericGraphNode->ParentNodes.Reset();
				LTGenericGraphNode->ChildrenNodes.Reset();
				LTGenericGraphNode->Edges.Reset();
			}
		}
	}
}

void UEdGraph_LTGenericGraph::SortNodes(ULTGenericGraphNode* RootNode)
{
	int Level = 0;
	TArray<ULTGenericGraphNode*> CurrLevelNodes = { RootNode };
	TArray<ULTGenericGraphNode*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		int32 LevelWidth = 0;
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			ULTGenericGraphNode* Node = CurrLevelNodes[i];

			auto Comp = [&](const ULTGenericGraphNode& L, const ULTGenericGraphNode& R)
			{
				UEdNode_LTGenericGraphNode* EdNode_LNode = NodeMap[&L];
				UEdNode_LTGenericGraphNode* EdNode_RNode = NodeMap[&R];
				return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
			};

			Node->ChildrenNodes.Sort(Comp);
			Node->ParentNodes.Sort(Comp);

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

void UEdGraph_LTGenericGraph::PostEditUndo()
{
	Super::PostEditUndo();

	NotifyGraphChanged();
}

