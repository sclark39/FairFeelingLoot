#include "LTGenericGraphEdge.h"

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
void ULTGenericGraphEdge::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}
#endif // #if WITH_EDITOR