// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/EdGraph_LTGenericGraph.h"
#include "Kismet2/Kismet2NameValidators.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "LTGenericGraph.h"

#define LOCTEXT_NAMESPACE "EdNode_LTGenericGraph"

UEdNode_LTGenericGraphNode::UEdNode_LTGenericGraphNode()
{
	bCanRenameNode = true;
}

UEdNode_LTGenericGraphNode::~UEdNode_LTGenericGraphNode()
{

}

FString UEdNode_LTGenericGraphNode::GetDocumentationExcerptName() const
{
	UClass* MyClass = GetClass();
	if (LTGenericGraphNode)
		MyClass = LTGenericGraphNode->GetClass();

	// Default the node to searching for an excerpt named for the C++ node class name, including the U prefix.
	// This is done so that the excerpt name in the doc file can be found by find-in-files when searching for the full class name.
	return FString::Printf(TEXT("%s%s"), MyClass->GetPrefixCPP(), *MyClass->GetName());
}

FText UEdNode_LTGenericGraphNode::GetTooltipText() const
{
	if (LTGenericGraphNode)
		return LTGenericGraphNode->GetNodeTooltip();

	UClass* MyClass = GetClass();
	return MyClass->GetToolTipText();
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
	return LTGenericGraphNode? LTGenericGraphNode->GetBackgroundColor() : FLinearColor::Black;
}

const FSlateBrush *UEdNode_LTGenericGraphNode::GetNodeIcon() const
{
	return LTGenericGraphNode? LTGenericGraphNode->GetNodeIcon() : FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
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
	Super::PostEditUndo();
}

bool UEdNode_LTGenericGraphNode::Modify(bool bAlwaysMarkDirty)
{
	return Super::Modify(bAlwaysMarkDirty);
}

#undef LOCTEXT_NAMESPACE
