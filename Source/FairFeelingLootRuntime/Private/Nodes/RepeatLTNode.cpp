﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "RepeatLTNode.h"
#include "FairFeelingLootRuntime.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // #if WITH_EDITOR

#define LOCTEXT_NAMESPACE "LootTableDefinition"

URepeatLTNode::URepeatLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("RepeatNode", "Repeat Multiple");
	ContextMenuCategory = LTCATEGORY_FLOW;
	ChildrenLimitType = ELTGenericGraphNodeLimit::Limited;
	ChildrenLimit = 1;
#endif // #if WITH_EDITORONLY_DATA
}


const void URepeatLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	if (MaxRepeats < MinRepeats)
	{
		UE_LOG(LogFairFeelingLoot, Warning, TEXT("Repeat node MinRepeats > MaxRepeats"));
	}
	int Times = State.RNG->RandRange(MinRepeats, MaxRepeats);

	for ( int i = 0; i < Times; i++ )	
		Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

void URepeatLTNode::PostLoad()
{
	Super::PostLoad(); 
	
	if (RepeatRange_DEPRECATED != FVector2D::ZeroVector)
	{
		MinRepeats = RepeatRange_DEPRECATED.X;
		MaxRepeats = RepeatRange_DEPRECATED.Y;
		RepeatRange_DEPRECATED = FVector2D::ZeroVector;
	}	
}


#if WITH_EDITOR

FText URepeatLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Range"), RangeToText(MinRepeats, MaxRepeats, false));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", "Repeat {Range}"), Args); 
}

const FSlateBrush*  URepeatLTNode::GetNodeIcon() const
{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.Loop.Icon"));
#else // #if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.Loop.Icon"));
#endif // #else ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
}

FLinearColor URepeatLTNode::GetBackgroundColor() const
{
	return FLinearColor::White;
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

