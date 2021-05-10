#include "LTGenericGraphNode.h"
#include "LTGenericGraph.h"

#define LOCTEXT_NAMESPACE "LTGenericGraphNode"

ULTGenericGraphNode::ULTGenericGraphNode()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = ULTGenericGraph::StaticClass();

	BackgroundColor = FLinearColor(0.01f,0.01,0.01f);
#endif
}

ULTGenericGraphNode::~ULTGenericGraphNode()
{
}

ULTGenericGraphEdge* ULTGenericGraphNode::GetEdge(const ULTGenericGraphNode* ChildNode) const
{
	return Edges.Contains(ChildNode) ? Edges.FindChecked(ChildNode) : nullptr;
}

FText ULTGenericGraphNode::GetDescription_Implementation() const
{
	return LOCTEXT("NodeDesc", "Generic Graph Node");
}

#if WITH_EDITOR
TSubclassOf<ULTGenericGraphEdge> ULTGenericGraphNode::GetEdgeType() const
{
	if (Graph->bEdgeEnabled)
		return Graph->EdgeType;
	return nullptr;
}

bool ULTGenericGraphNode::IsNameEditable() const
{
	return true;
}

FLinearColor ULTGenericGraphNode::GetBackgroundColor() const
{
	return BackgroundColor;
}

FText ULTGenericGraphNode::GetNodeTitle() const
{
	return NodeTitle.IsEmpty() ? GetDescription() : NodeTitle;
}

void ULTGenericGraphNode::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}

bool ULTGenericGraphNode::CanCreateConnection(ULTGenericGraphNode* Other, FText& ErrorMessage)
{	
	return true;
}

bool ULTGenericGraphNode::CanCreateConnectionTo(ULTGenericGraphNode* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage)
{
	if (ChildrenLimitType == ENodeLimit::Forbidden || (ChildrenLimitType == ENodeLimit::Limited && ChildrenLimit <= 0))
	{
		ErrorMessage = FText::FromString("Node can not have children");
		return false;
	}

	if (ChildrenLimitType == ENodeLimit::Limited && NumberOfChildrenNodes >= ChildrenLimit)
	{
		ErrorMessage = FText::FromString("Children limit exceeded");
		return false;
	}

	return CanCreateConnection(Other, ErrorMessage);
}

bool ULTGenericGraphNode::CanCreateConnectionFrom(ULTGenericGraphNode* Other, int32 NumberOfParentNodes, FText& ErrorMessage)
{
	if (ParentLimitType == ENodeLimit::Forbidden || (ParentLimitType == ENodeLimit::Limited && ParentLimit <= 0))
	{
		ErrorMessage = FText::FromString("Node can not have parents");
		return false;
	}

	if (ParentLimitType == ENodeLimit::Limited && NumberOfParentNodes >= ParentLimit)
	{
		ErrorMessage = FText::FromString("Parent limit exceeded");
		return false;
	}

	return true;
}


#endif

bool ULTGenericGraphNode::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

ULTGenericGraph* ULTGenericGraphNode::GetGraph() const
{
	return Graph;
}

#undef LOCTEXT_NAMESPACE
