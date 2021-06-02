// Copyright 2021 Skyler Clark. All Rights Reserved.

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


const ULTGenericGraphNode* ULTGraphNode::PickChild(FLootTableData &LootTable, const FMakeLootState &State) const
{
	// Follow first child
	if (0 < ChildrenNodes.Num())
		return ChildrenNodes[0];

	return nullptr;
}

const void ULTGraphNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot ) const
{
	if (ShouldPickChildren())
	{
		if (const ULTGraphNode *Child = Cast<ULTGraphNode>(PickChild(LootTable, State)))
		{
			Child->TraverseNodesAndCollectLoot(LootTable, State, Loot);
			return;
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
}



#if WITH_EDITOR

FText ULTGraphNode::RangeToText(float Min, float Max, bool bCanReorder) const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Min"), FText::FromString(FString::SanitizeFloat(Min, 0)));
	Args.Add(TEXT("Max"), FText::FromString(FString::SanitizeFloat(Max, 0)));
	
	if (Min == Max)
		return FText::Format(LOCTEXT("RangeOne","[{Min}]"), Args);
	else if (bCanReorder && Max < Min)
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

const void URootLTGraphNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	ULootTableDefinition *Definition = Cast<ULootTableDefinition>(GetGraph());
	ensure(Definition);
	
	// Implicit Entropy Control Node...

	RETRIEVE_LTNODE_PAYLOAD(sizeof(FRandomStream) + sizeof(float));
	DECLARE_LTNODE_ELEMENT(FRandomStream, MyRNG);
	DECLARE_LTNODE_ELEMENT(float, LastTime);

	if (*RequiresInitialization)
	{
		*RequiresInitialization = false;

		// Initialize State Stream
		if (Definition->bTracksOwnRandomStream)
		{
			new (&MyRNG) FRandomStream(Definition->InitialSeed);
			if (Definition->bShouldRandomizeSeed)
				MyRNG.GenerateNewSeed();
		}
	}

	if (Definition->bTracksOwnRandomStream)
		State.RNG = &MyRNG;

	if (Definition->bTracksOwnTime)
		State.LastTime = LastTime;

	Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);

	if (Definition->bTracksOwnTime)
		LastTime = LootTable.GetTime();	
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

bool ULootTableDefinition::ShouldAllowIncrementalRebuild()
{
	// TODO: Don't let rebuild during gameplay
	return true;
}


#undef LOCTEXT_NAMESPACE 


