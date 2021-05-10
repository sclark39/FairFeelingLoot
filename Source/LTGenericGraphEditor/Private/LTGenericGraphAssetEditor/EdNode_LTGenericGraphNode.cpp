#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/EdGraph_LTGenericGraph.h"
#include "Kismet2/Kismet2NameValidators.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "EdNode_LTGenericGraph"

UEdNode_LTGenericGraphNode::UEdNode_LTGenericGraphNode()
{
	bCanRenameNode = true;
}

UEdNode_LTGenericGraphNode::~UEdNode_LTGenericGraphNode()
{

}

void UEdNode_LTGenericGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName(), TEXT("In"));
	CreatePin(EGPD_Output, "MultipleNodes", FName(), TEXT("Out"));
}

UEdGraph_LTGenericGraph* UEdNode_LTGenericGraphNode::GetLTGenericGraphEdGraph()
{
	return Cast<UEdGraph_LTGenericGraph>(GetGraph());
}

FText UEdNode_LTGenericGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (LTGenericGraphNode == nullptr)
	{
		return Super::GetNodeTitle(TitleType);
	}
	else
	{
		return LTGenericGraphNode->GetNodeTitle();
	}
}

void UEdNode_LTGenericGraphNode::PrepareForCopying()
{
	LTGenericGraphNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}

void UEdNode_LTGenericGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin != nullptr)
	{
		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}

void UEdNode_LTGenericGraphNode::SetLTGenericGraphNode(ULTGenericGraphNode* InNode)
{
	LTGenericGraphNode = InNode;
}

FLinearColor UEdNode_LTGenericGraphNode::GetBackgroundColor() const
{
	return LTGenericGraphNode == nullptr ? FLinearColor::Black : LTGenericGraphNode->GetBackgroundColor();
}

UEdGraphPin* UEdNode_LTGenericGraphNode::GetInputPin() const
{
	return Pins[0];
}

UEdGraphPin* UEdNode_LTGenericGraphNode::GetOutputPin() const
{
	return Pins[1];
}

bool UEdNode_LTGenericGraphNode::CanDuplicateNode() const
{
	bool bIsUniqueRoot = LTGenericGraphNode &&
		LTGenericGraphNode->Graph->NodeType != LTGenericGraphNode->Graph->RootNodeType &&
		LTGenericGraphNode->GetClass() == LTGenericGraphNode->Graph->RootNodeType;
	return !bIsUniqueRoot;
}

bool UEdNode_LTGenericGraphNode::CanUserDeleteNode() const
{
	bool bIsUniqueRoot = LTGenericGraphNode &&
		LTGenericGraphNode->Graph->NodeType != LTGenericGraphNode->Graph->RootNodeType &&
		LTGenericGraphNode->GetClass() == LTGenericGraphNode->Graph->RootNodeType;
	return !bIsUniqueRoot;
}


void UEdNode_LTGenericGraphNode::PostEditUndo()
{
	UEdGraphNode::PostEditUndo();
}

#undef LOCTEXT_NAMESPACE
