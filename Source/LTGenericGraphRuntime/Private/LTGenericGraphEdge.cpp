// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGenericGraphEdge.h"
#include "LTGenericGraph.h"

ULTGenericGraphEdge::ULTGenericGraphEdge()
{

}

ULTGenericGraphEdge::~ULTGenericGraphEdge()
{

}

ULTGenericGraph* ULTGenericGraphEdge::GetGraph() const
{
	return Graph;
}

#if WITH_EDITOR
void ULTGenericGraphEdge::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ULTGenericGraph::OnEdgeChanged.Broadcast(this);
}

void ULTGenericGraphEdge::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}
#endif // #if WITH_EDITOR