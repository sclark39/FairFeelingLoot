// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGenericGraphNode.h"
#include "LTGenericGraph.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // #if WITH_EDITOR

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
void ULTGenericGraphNode::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ULTGenericGraph::OnNodeChanged.Broadcast(this);
}

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

FText ULTGenericGraphNode::GetNodeTooltip() const
{
	return NodeTooltip.IsEmpty() ? GetClass()->GetToolTipText() : NodeTooltip;
}

FText ULTGenericGraphNode::GetContextMenuName() const
{
	return ContextMenuName;
}

FText ULTGenericGraphNode::GetContextMenuCategory() const
{
	return ContextMenuCategory;
}

FText ULTGenericGraphNode::GetContextMenuDescription() const
{
	return ContextMenuDescription;
}

bool ULTGenericGraphNode::CanCreateConnection(ULTGenericGraphNode* Other, FText& ErrorMessage)
{	
	return true;
}

bool ULTGenericGraphNode::CanCreateConnectionTo(ULTGenericGraphNode* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage)
{
	ELTGenericGraphNodeLimit LimitType;
	int LimitCount;
	GetChildrenLimit(LimitType, LimitCount);

	if (LimitType == ELTGenericGraphNodeLimit::Forbidden || (LimitType == ELTGenericGraphNodeLimit::Limited && ChildrenLimit <= 0))
	{
		ErrorMessage = FText::FromString("Node can not have children");
		return false;
	}

	if (LimitType == ELTGenericGraphNodeLimit::Limited && NumberOfChildrenNodes >= LimitCount)
	{
		ErrorMessage = FText::FromString("Children limit exceeded");
		return false;
	}

	return CanCreateConnection(Other, ErrorMessage);
}

bool ULTGenericGraphNode::CanCreateConnectionFrom(ULTGenericGraphNode* Other, int32 NumberOfParentNodes, FText& ErrorMessage)
{
	ELTGenericGraphNodeLimit LimitType;
	int LimitCount;
	GetParentLimit(LimitType, LimitCount);

	if (LimitType == ELTGenericGraphNodeLimit::Forbidden || (LimitType == ELTGenericGraphNodeLimit::Limited && LimitCount <= 0))
	{
		ErrorMessage = FText::FromString("Node can not have parents");
		return false;
	}

	if (LimitType == ELTGenericGraphNodeLimit::Limited && NumberOfParentNodes >= LimitCount)
	{
		ErrorMessage = FText::FromString("Parent limit exceeded");
		return false;
	}

	return true;
}

const FSlateBrush* ULTGenericGraphNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
}

void ULTGenericGraphNode::GetChildrenLimit(ELTGenericGraphNodeLimit &LimitType, int32 &LimitCount) const
{
	LimitType = ChildrenLimitType;
	LimitCount = ChildrenLimit;
}

void ULTGenericGraphNode::GetParentLimit(ELTGenericGraphNodeLimit &LimitType, int32 &LimitCount) const
{
	LimitType = ParentLimitType;
	LimitCount = ParentLimit;
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
