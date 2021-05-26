﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootTableDefinition.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

ULTGraphNode::ULTGraphNode()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = ULootTableDefinition::StaticClass();
	ContextMenuName = FText::FromString("");
	ContextMenuCategory = LOCTEXT("MiscCategory", "Miscellaneous");
#endif // #if WITH_EDITORONLY_DATA
}


const ULTGenericGraphNode* ULTGraphNode::PickChild(FLootTable &LootTable, const FEntropyState &State) const
{
	// Follow first child
	if (0 < ChildrenNodes.Num())
		return ChildrenNodes[0];

	return nullptr;
}

const ULTGraphNode* ULTGraphNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot ) const
{
	if (ShouldPickChildren())
	{
		if (const ULTGraphNode *Child = Cast<ULTGraphNode>(PickChild(LootTable, State)))
		{
			return Child->TraverseNodesAndCollectLoot(LootTable, State, Loot);
		}
	}
	else
	{
		for (const auto *Node : ChildrenNodes)
		{
			if (const ULTGraphNode *LTNode = Cast<const ULTGraphNode>(Node))
			{
				LTNode->TraverseNodesAndCollectLoot(LootTable, State, Loot);
			}
		}
	}

	return this;
}



#if WITH_EDITOR

FText ULTGraphNode::RangeToText(float Min, float Max) const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Min"), FText::FromString(FString::SanitizeFloat(Min, 0)));
	Args.Add(TEXT("Max"), FText::FromString(FString::SanitizeFloat(Max, 0)));
	
	if (Min == Max)
		return FText::Format(LOCTEXT("RangeOne","[{Min}]"), Args);
	else if (Max < Min)
		return FText::Format(LOCTEXT("RangeTwoReversed", "[{Max},{Min}]"), Args);

	return FText::Format(LOCTEXT("RangeTwo", "[{Min},{Max}]"), Args);
}

FText ULTGraphNode::GetNodeTitle() const
{
	return ContextMenuName;
}

FText ULTGraphNode::GetContextMenuDescription() const
{
	return GetNodeTooltip();
}

bool ULTGraphNode::IsNameEditable() const
{
	return false;
}

TSubclassOf<ULTGenericGraphEdge> ULTGraphNode::GetEdgeType() const 
{
	return nullptr;
}

void ULTGraphNode::GetChildrenLimit(ELTGenericGraphNodeLimit &LimitType, int32 &LimitCount) const
{
	if (SupportsImplicitSequence())
	{
		ensure(!ShouldPickChildren());
		if (ULootTableDefinition *LT = Cast<ULootTableDefinition>(Graph))
		{
			if (!LT->bAllowImplicitSequenceNodes)
			{
				LimitType = ELTGenericGraphNodeLimit::Limited;
				LimitCount = 1;
				return;
			}
		}
	}

	Super::GetChildrenLimit(LimitType, LimitCount);
}

#endif // #if WITH_EDITOR


UNoopLTGraphNode::UNoopLTGraphNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("NoopNode", "No-Op");
	ContextMenuCategory = LTCATEGORY_MISC;
	ChildrenLimitType = ELTGenericGraphNodeLimit::Forbidden;
#endif // #if WITH_EDITORONLY_DATA
}


#if WITH_EDITOR

const FSlateBrush*  UNoopLTGraphNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Wait.Icon"));
}

#endif // #if WITH_EDITOR


URootLTGraphNode::URootLTGraphNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("RootNode", "Start");
	ParentLimitType = ELTGenericGraphNodeLimit::Forbidden;
#endif // #if WITH_EDITORONLY_DATA
}


#if WITH_EDITOR

TSubclassOf<ULTGenericGraphEdge> URootLTGraphNode::GetEdgeType() const
{
	return nullptr;
}

FLinearColor URootLTGraphNode::GetBackgroundColor() const
{
	return FLinearColor::White;
}

const FSlateBrush*  URootLTGraphNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Index"));
}

#endif // #if WITH_EDITOR



ULootTableDefinition::ULootTableDefinition()
{
	NodeType = ULTGraphNode::StaticClass();	
	RootNodeType = URootLTGraphNode::StaticClass();
}


const URootLTGraphNode* ULootTableDefinition::GetRootNode() const
{
	for (auto *Node : RootNodes)
	{
		if (const URootLTGraphNode *RootNode = Cast<URootLTGraphNode>(Node))
			return RootNode;
	}

	return nullptr;
}

#undef LOCTEXT_NAMESPACE 


