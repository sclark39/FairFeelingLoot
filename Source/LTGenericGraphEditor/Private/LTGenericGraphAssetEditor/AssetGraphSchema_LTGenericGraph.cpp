// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGenericGraphAssetEditor/AssetGraphSchema_LTGenericGraph.h"
#include "ToolMenus.h"
#include "LTGenericGraphEditorPCH.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphEdge.h"
#include "LTGenericGraphAssetEditor/ConnectionDrawingPolicy_LTGenericGraph.h"
#include "GraphEditorActions.h"
#include "Framework/Commands/GenericCommands.h"
#include "AutoLayout/LTForceDirectedLayoutStrategy.h"
#include "AutoLayout/LTTreeLayoutStrategy.h"

#include "LTGenericGraphEditorStrings.h"

#define LOCTEXT_NAMESPACE "AssetSchema_LTGenericGraph"

int32 UAssetGraphSchema_LTGenericGraph::CurrentCacheRefreshID = 0;


class FNodeVisitorCycleChecker
{
public:
	/** Check whether a loop in the graph would be caused by linking the passed-in nodes */
	bool CheckForLoop(UEdGraphNode* StartNode, UEdGraphNode* EndNode)
	{

		VisitedNodes.Add(StartNode);

		return TraverseNodes(EndNode);
	}

private:
	bool TraverseNodes(UEdGraphNode* Node)
	{
		VisitedNodes.Add(Node);

		for (auto MyPin : Node->Pins)
		{
			if (MyPin->Direction == EGPD_Output)
			{
				for (auto OtherPin : MyPin->LinkedTo)
				{
					UEdGraphNode* OtherNode = OtherPin->GetOwningNode();
					if (VisitedNodes.Contains(OtherNode))
					{
						// Only  an issue if this is a back-edge
						return false;
					}
					else if (!FinishedNodes.Contains(OtherNode))
					{
						// Only should traverse if this node hasn't been traversed
						if (!TraverseNodes(OtherNode))
							return false;
					}
				}
			}
		}

		VisitedNodes.Remove(Node);
		FinishedNodes.Add(Node);
		return true;
	};


	TSet<UEdGraphNode*> VisitedNodes;
	TSet<UEdGraphNode*> FinishedNodes;
};




UEdGraphNode* FAssetSchemaAction_LTGenericGraph_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	UEdGraphNode* ResultNode = nullptr;

	if (NodeTemplate != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("LTGenericGraphEditorNewNode", GGS_NEW_NODE));
		ParentGraph->Modify();
		if (FromPin != nullptr)
			FromPin->Modify();

		NodeTemplate->Rename(nullptr, ParentGraph);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;

		NodeTemplate->LTGenericGraphNode->SetFlags(RF_Transactional);
		NodeTemplate->SetFlags(RF_Transactional);

		ResultNode = NodeTemplate;
	}

	return ResultNode;
}

void FAssetSchemaAction_LTGenericGraph_NewNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

UEdGraphNode* FAssetSchemaAction_LTGenericGraph_NewEdge::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	UEdGraphNode* ResultNode = nullptr;

	if (NodeTemplate != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("LTGenericGraphEditorNewEdge", GGS_NEW_EDGE));
		ParentGraph->Modify();
		if (FromPin != nullptr)
			FromPin->Modify();

		NodeTemplate->Rename(nullptr, ParentGraph);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;

		NodeTemplate->LTGenericGraphEdge->SetFlags(RF_Transactional);
		NodeTemplate->SetFlags(RF_Transactional);

		ResultNode = NodeTemplate;
	}
	
	return ResultNode;
}

void FAssetSchemaAction_LTGenericGraph_NewEdge::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

void UAssetGraphSchema_LTGenericGraph::GetBreakLinkToSubMenuActions(UToolMenu* Menu, UEdGraphPin* InGraphPin)
{
	// Make sure we have a unique name for every entry in the list
	TMap< FString, uint32 > LinkTitleCount;

	FToolMenuSection& Section = Menu->FindOrAddSection("LTGenericGraphAssetGraphSchemaPinActions");

	// Add all the links we could break from
	for (TArray<class UEdGraphPin*>::TConstIterator Links(InGraphPin->LinkedTo); Links; ++Links)
	{
		UEdGraphPin* Pin = *Links;
		FString TitleString = Pin->GetOwningNode()->GetNodeTitle(ENodeTitleType::ListView).ToString();
		FText Title = FText::FromString(TitleString);
		if (Pin->PinName != TEXT(""))
		{
			TitleString = FString::Printf(TEXT("%s (%s)"), *TitleString, *Pin->PinName.ToString());

			// Add name of connection if possible
			FFormatNamedArguments Args;
			Args.Add(TEXT("NodeTitle"), Title);
			Args.Add(TEXT("PinName"), Pin->GetDisplayName());
			Title = FText::Format(LOCTEXT("BreakDescPin", "{NodeTitle} ({PinName})"), Args);
		}

		uint32& Count = LinkTitleCount.FindOrAdd(TitleString);

		FText Description;
		FFormatNamedArguments Args;
		Args.Add(TEXT("NodeTitle"), Title);
		Args.Add(TEXT("NumberOfNodes"), Count);

		if (Count == 0)
		{
			Description = FText::Format(LOCTEXT("BreakDesc", "Break link to {NodeTitle}"), Args);
		}
		else
		{
			Description = FText::Format(LOCTEXT("BreakDescMulti", "Break link to {NodeTitle} ({NumberOfNodes})"), Args);
		}
		++Count;

		Section.AddMenuEntry(NAME_None, Description, Description, FSlateIcon(), FUIAction(
			FExecuteAction::CreateUObject(this, &UAssetGraphSchema_LTGenericGraph::BreakSinglePinLink, const_cast<UEdGraphPin*>(InGraphPin), *Links)));
	}
}

EGraphType UAssetGraphSchema_LTGenericGraph::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_StateMachine;
}

void UAssetGraphSchema_LTGenericGraph::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	ULTGenericGraph *LTGenericGraph = CastChecked<UEdGraph_LTGenericGraph>(&Graph)->GetLTGenericGraph();
	TSubclassOf<ULTGenericGraphNode> RootNodeType = LTGenericGraph->RootNodeType;

	if (RootNodeType)
	{
		FGraphNodeCreator< UEdNode_LTGenericGraphNode> NodeCreator(Graph);
		UEdNode_LTGenericGraphNode *RootNode = NodeCreator.CreateNode(false);
		RootNode->LTGenericGraphNode = NewObject<ULTGenericGraphNode>(RootNode, RootNodeType);
		RootNode->LTGenericGraphNode->Graph = LTGenericGraph;
		NodeCreator.Finalize();
		SetNodeMetaData(RootNode, FNodeMetadata::DefaultGraphNode);
	}

}

void UAssetGraphSchema_LTGenericGraph::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	ULTGenericGraph* Graph = CastChecked<ULTGenericGraph>(ContextMenuBuilder.CurrentGraph->GetOuter());

	if (Graph->NodeType == nullptr)
	{
		return;
	}

	const bool bNoParent = (ContextMenuBuilder.FromPin == NULL);

	const FText AddToolTip = LOCTEXT("NewLTGenericGraphNodeTooltip", "Add node here");

	TSet<TSubclassOf<ULTGenericGraphNode> > Visited;

	TSubclassOf<ULTGenericGraphNode> RootNodeType = Graph->RootNodeType;
	if (RootNodeType && RootNodeType != Graph->NodeType)
	{
		// Don't include root node type
		Visited.Add(RootNodeType);
	}

	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(Graph->NodeType) && !It->HasAnyClassFlags(CLASS_Abstract) && !Visited.Contains(*It))
		{
			TSubclassOf<ULTGenericGraphNode> NodeType = *It;

			if (It->GetName().StartsWith("REINST") || It->GetName().StartsWith("SKEL"))
				continue;
				
			if (!Graph->GetClass()->IsChildOf(NodeType.GetDefaultObject()->CompatibleGraphType))
				continue;

			ULTGenericGraphNode *DefaultObject = NodeType.GetDefaultObject();

			FText Name = DefaultObject->GetContextMenuName();
			if (Name.IsEmpty())
			{
				FString Title = NodeType->GetName();
				Title.RemoveFromEnd("_C");
				Name = FText::FromString(Title);
			}		

			FText Category = DefaultObject->GetContextMenuCategory();
			if (Category.IsEmpty())
				Category = LOCTEXT("LTGenericGraphNodeAction", GGS_NODE_CONTEXTMENU_CAT);

			FText Description = DefaultObject->GetContextMenuDescription();
			if (Description.IsEmpty())
				Description = AddToolTip;

			TSharedPtr<FAssetSchemaAction_LTGenericGraph_NewNode> Action(new FAssetSchemaAction_LTGenericGraph_NewNode(Category, Name, Description, 0));
			Action->NodeTemplate = NewObject<UEdNode_LTGenericGraphNode>(ContextMenuBuilder.OwnerOfTemporaries);			
			Action->NodeTemplate->LTGenericGraphNode = NewObject<ULTGenericGraphNode>(Action->NodeTemplate, NodeType);
			Action->NodeTemplate->LTGenericGraphNode->Graph = Graph;
			ContextMenuBuilder.AddAction(Action);

			Visited.Add(NodeType);
		}
	}
}

void UAssetGraphSchema_LTGenericGraph::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (Context->Pin)
	{
		{
			FToolMenuSection& Section = Menu->AddSection("LTGenericGraphAssetGraphSchemaNodeActions", LOCTEXT("PinActionsMenuHeader", "Pin Actions"));
			// Only display the 'Break Links' option if there is a link to break!
			if (Context->Pin->LinkedTo.Num() > 0)
			{
				Section.AddMenuEntry(FGraphEditorCommands::Get().BreakPinLinks);

				// add sub menu for break link to
				if (Context->Pin->LinkedTo.Num() > 1)
				{
					Section.AddSubMenu(
						"BreakLinkTo",
						LOCTEXT("BreakLinkTo", "Break Link To..."),
						LOCTEXT("BreakSpecificLinks", "Break a specific link..."),
						FNewToolMenuDelegate::CreateUObject((UAssetGraphSchema_LTGenericGraph* const)this, &UAssetGraphSchema_LTGenericGraph::GetBreakLinkToSubMenuActions, const_cast<UEdGraphPin*>(Context->Pin)));
				}
				else
				{
					((UAssetGraphSchema_LTGenericGraph* const)this)->GetBreakLinkToSubMenuActions(Menu, const_cast<UEdGraphPin*>(Context->Pin));
				}
			}
		}
	}
	else if (Context->Node)
	{
		{
			FToolMenuSection& Section = Menu->AddSection("LTGenericGraphAssetGraphSchemaNodeActions", LOCTEXT("ClassActionsMenuHeader", "Node Actions"));
			Section.AddMenuEntry(FGenericCommands::Get().Delete);
			Section.AddMenuEntry(FGenericCommands::Get().Cut);
			Section.AddMenuEntry(FGenericCommands::Get().Copy);
			Section.AddMenuEntry(FGenericCommands::Get().Duplicate);

			Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
		}
	}

	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UAssetGraphSchema_LTGenericGraph::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorSameNode", "Can't connect node to itself"));
	}

	const UEdGraphPin *Out = A;
	const UEdGraphPin *In = B;

	UEdNode_LTGenericGraphNode* EdNode_Out = Cast<UEdNode_LTGenericGraphNode>(Out->GetOwningNode());
	UEdNode_LTGenericGraphNode* EdNode_In = Cast<UEdNode_LTGenericGraphNode>(In->GetOwningNode());

	if (EdNode_Out == nullptr || EdNode_In == nullptr || EdNode_Out->LTGenericGraphNode == nullptr || EdNode_In->LTGenericGraphNode == nullptr )
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinError", "Not a valid Node"));
	}
		
	//Determine if we can have cycles or not
	bool bAllowCycles = false;
	auto EdGraph = Cast<UEdGraph_LTGenericGraph>(Out->GetOwningNode()->GetGraph());
	if (EdGraph != nullptr)
	{
		bAllowCycles = EdGraph->GetLTGenericGraph()->bCanBeCyclical;
	}

	// check for cycles
	FNodeVisitorCycleChecker CycleChecker;
	if (!bAllowCycles && !CycleChecker.CheckForLoop(Out->GetOwningNode(), In->GetOwningNode()))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorCycle", "Can't create a graph cycle"));
	}

	FText ErrorMessage;
	if (!EdNode_Out->LTGenericGraphNode->CanCreateConnectionTo(EdNode_In->LTGenericGraphNode, EdNode_Out->GetOutputPin()->LinkedTo.Num(), ErrorMessage))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ErrorMessage);
	}
	if (!EdNode_In->LTGenericGraphNode->CanCreateConnectionFrom(EdNode_Out->LTGenericGraphNode, EdNode_In->GetInputPin()->LinkedTo.Num(), ErrorMessage))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ErrorMessage);
	}


	if (EdNode_Out->LTGenericGraphNode->GetEdgeType() && EdNode_Out->LTGenericGraphNode->GetGraph()->bEdgeEnabled)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, LOCTEXT("PinConnect", "Connect nodes with edge"));
	}
	else
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, LOCTEXT("PinConnect", "Connect nodes"));
	}
}

bool UAssetGraphSchema_LTGenericGraph::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	// We don't actually care about the pin, we want the node that is being dragged between
	UEdNode_LTGenericGraphNode* NodeA = Cast<UEdNode_LTGenericGraphNode>(A->GetOwningNode());
	UEdNode_LTGenericGraphNode* NodeB = Cast<UEdNode_LTGenericGraphNode>(B->GetOwningNode());
	if (!NodeA || !NodeB)
		return false;

	// Check that this edge doesn't already exist
	for (UEdGraphPin *TestPin : NodeA->GetOutputPin()->LinkedTo)
	{
		UEdGraphNode* ChildNode = TestPin->GetOwningNode();
		if (UEdNode_LTGenericGraphEdge* EdNode_Edge = Cast<UEdNode_LTGenericGraphEdge>(ChildNode))
		{
			ChildNode = EdNode_Edge->GetEndNode();
		}

		if (ChildNode == NodeB)
			return false;
	}

	if (NodeA && NodeB)
	{
		// Always create connections from node A to B, don't allow adding in reverse
		Super::TryCreateConnection(NodeA->GetOutputPin(), NodeB->GetInputPin());

		if (auto Graph = NodeA->GetLTGenericGraphEdGraph())
		{
			Graph->RebuildLTGenericGraphIncremental();
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool UAssetGraphSchema_LTGenericGraph::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const
{
	UEdNode_LTGenericGraphNode* NodeA = Cast<UEdNode_LTGenericGraphNode>(A->GetOwningNode());
	UEdNode_LTGenericGraphNode* NodeB = Cast<UEdNode_LTGenericGraphNode>(B->GetOwningNode());

	// Are nodes and pins all valid?
	if (!NodeA || !NodeA->GetOutputPin() || !NodeB || !NodeB->GetInputPin())
		return false;
	
	ULTGenericGraph* Graph = NodeA->LTGenericGraphNode->GetGraph();

	FVector2D InitPos((NodeA->NodePosX + NodeB->NodePosX) / 2, (NodeA->NodePosY + NodeB->NodePosY) / 2);

	TSubclassOf<ULTGenericGraphEdge> EdgeType = NodeA->LTGenericGraphNode->GetEdgeType();
	if (!EdgeType)
		return false;

	FAssetSchemaAction_LTGenericGraph_NewEdge Action;
	Action.NodeTemplate = NewObject<UEdNode_LTGenericGraphEdge>(NodeA->GetGraph());
	Action.NodeTemplate->SetEdge(NewObject<ULTGenericGraphEdge>(Action.NodeTemplate, EdgeType));
	UEdNode_LTGenericGraphEdge* EdgeNode = Cast<UEdNode_LTGenericGraphEdge>(Action.PerformAction(NodeA->GetGraph(), nullptr, InitPos, false));

	// Always create connections from node A to B, don't allow adding in reverse
	EdgeNode->CreateConnections(NodeA, NodeB);

	return true;
}

class FConnectionDrawingPolicy* UAssetGraphSchema_LTGenericGraph::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
	return new FConnectionDrawingPolicy_LTGenericGraph(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

FLinearColor UAssetGraphSchema_LTGenericGraph::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FColor::White;
}

void UAssetGraphSchema_LTGenericGraph::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakNodeLinks", "Break Node Links"));

	Super::BreakNodeLinks(TargetNode);

	if (auto GenericEdNode = Cast<UEdNode_LTGenericGraphNode>(&TargetNode))
	{
		if (auto Graph = GenericEdNode->GetLTGenericGraphEdGraph())
		{
			Graph->RebuildLTGenericGraphIncremental();
		}
	}
}

void UAssetGraphSchema_LTGenericGraph::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakPinLinks", "Break Pin Links"));

	Super::BreakPinLinks(TargetPin, bSendsNodeNotifcation);

	if (auto TargetNode = TargetPin.GetOwningNode())
	{
		if (auto GenericEdNode = Cast<UEdNode_LTGenericGraphNode>(TargetNode))
		{
			if (auto Graph = GenericEdNode->GetLTGenericGraphEdGraph())
			{
				Graph->RebuildLTGenericGraphIncremental();
			}
		}
	}
}

void UAssetGraphSchema_LTGenericGraph::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakSinglePinLink", "Break Pin Link"));

	Super::BreakSinglePinLink(SourcePin, TargetPin);

	if (auto TargetNode = TargetPin->GetOwningNode())
	{
		if (auto GenericEdNode = Cast<UEdNode_LTGenericGraphNode>(TargetNode))
		{
			if (auto Graph = GenericEdNode->GetLTGenericGraphEdGraph())
			{
				Graph->RebuildLTGenericGraphIncremental();
			}
		}
	}
}

UEdGraphPin* UAssetGraphSchema_LTGenericGraph::DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const
{
	UEdNode_LTGenericGraphNode* EdNode = Cast<UEdNode_LTGenericGraphNode>(InTargetNode);
	switch (InSourcePinDirection)
	{
	case EGPD_Input:
		return EdNode->GetOutputPin();
	case EGPD_Output:
		return EdNode->GetInputPin();
	default:
		return nullptr;
	}
}

bool UAssetGraphSchema_LTGenericGraph::SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const
{
	return Cast<UEdNode_LTGenericGraphNode>(InTargetNode) != nullptr;
}

bool UAssetGraphSchema_LTGenericGraph::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return CurrentCacheRefreshID != InVisualizationCacheID;
}

int32 UAssetGraphSchema_LTGenericGraph::GetCurrentVisualizationCacheID() const
{
	return CurrentCacheRefreshID;
}

void UAssetGraphSchema_LTGenericGraph::ForceVisualizationCacheClear() const
{
	++CurrentCacheRefreshID;
}

#undef LOCTEXT_NAMESPACE
