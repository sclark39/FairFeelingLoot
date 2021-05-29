﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "RepeatLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

URepeatLTNode::URepeatLTNode()
{
	RepeatRange = FVector2D(1, 1);

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("RepeatNode", "Repeat Multiple");
	ContextMenuCategory = LTCATEGORY_FLOW;
	ChildrenLimitType = ELTGenericGraphNodeLimit::Limited;
	ChildrenLimit = 1;
#endif // #if WITH_EDITORONLY_DATA
}


const void URepeatLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	int Times = FMath::RoundToInt( State.RNG->FRandRange(RepeatRange.X, RepeatRange.Y) );

	for ( int i = 0; i < Times; i++ )	
		Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR

FText URepeatLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Range"), RangeToText(RepeatRange.X, RepeatRange.Y));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", "Repeat {Range}"), Args); 
}

const FSlateBrush*  URepeatLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.Loop.Icon"));
}

FLinearColor URepeatLTNode::GetBackgroundColor() const
{
	return FLinearColor::White;
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

