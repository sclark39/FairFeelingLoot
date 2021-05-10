// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGraph/RepeatLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

URepeatLTNode::URepeatLTNode()
{
	RepeatRange = FVector2D(1, 1);

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("RepeatNode", "Repeat Multiple");
	ContextMenuCategory = LTCATEGORY_FLOW;
	ChildrenLimitType = ENodeLimit::Limited;
	ChildrenLimit = 1;
#endif // #if WITH_EDITORONLY_DATA
}


const ULTGraphNode* URepeatLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	int Times = FMath::RoundToInt( State.RNG->FRandRange(RepeatRange.X, RepeatRange.Y) );

	for ( int i = 0; i < Times; i++ )	
		Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);

	return this;
}

#if WITH_EDITOR

FText URepeatLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Range"), RangeToText(RepeatRange.X, RepeatRange.Y));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", "Repeat {Range}"), Args); 
}

FLinearColor URepeatLTNode::GetBackgroundColor() const
{
	return FLinearColor::White;
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

