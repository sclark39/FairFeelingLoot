#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphEdge.h"
#include "LTGenericGraphEdge.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"

#define LOCTEXT_NAMESPACE "EdNode_LTGenericGraphEdge"

UEdNode_LTGenericGraphEdge::UEdNode_LTGenericGraphEdge()
{
	bCanRenameNode = true;
}

void UEdNode_LTGenericGraphEdge::SetEdge(ULTGenericGraphEdge* Edge)
{
	LTGenericGraphEdge = Edge;
}

void UEdNode_LTGenericGraphEdge::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Edge"), FName(), TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Edge"), FName(), TEXT("Out"));
	Outputs->bHidden = true;
}

FText UEdNode_LTGenericGraphEdge::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (LTGenericGraphEdge)
	{
		return LTGenericGraphEdge->GetNodeTitle();
	}
	return FText();
}

void UEdNode_LTGenericGraphEdge::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() == 0)
	{
		// Commit suicide; transitions must always have an input and output connection
		Modify();

		// Our parent graph will have our graph in SubGraphs so needs to be modified to record that.
		if (UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}

		DestroyNode();
	}
}

void UEdNode_LTGenericGraphEdge::PrepareForCopying()
{
	LTGenericGraphEdge->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}

void UEdNode_LTGenericGraphEdge::CreateConnections(UEdNode_LTGenericGraphNode* Start, UEdNode_LTGenericGraphNode* End)
{
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	Start->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(Start->GetOutputPin());

	// This to next
	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	End->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(End->GetInputPin());
}

UEdNode_LTGenericGraphNode* UEdNode_LTGenericGraphEdge::GetStartNode()
{
	if (Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UEdNode_LTGenericGraphNode>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

UEdNode_LTGenericGraphNode* UEdNode_LTGenericGraphEdge::GetEndNode()
{
	if (Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UEdNode_LTGenericGraphNode>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

#undef LOCTEXT_NAMESPACE

