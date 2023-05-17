﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "AddTagLTNode.h"
#include "LootTableBlueprintLibrary.h"
#include "FairFeelingLootRuntime.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // #if WITH_EDITOR

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UAddTagLTNode::UAddTagLTNode()
{
//	LootTagName = NAME_None;

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("AddTagNode", "Make Loot - Add Tag");
	ContextMenuCategory = LTCATEGORY_LOOT;
#endif // #if WITH_EDITORONLY_DATA
}



const void UAddTagLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	if (State.ActiveLoot)
	{
		FLootRecipe &NewLoot = *State.ActiveLoot;
		
		ULootTableBlueprintLibrary::AddLootTag(NewLoot, LootTag);
	}
	else
	{
		UE_LOG(LogFairFeelingLoot, Error, TEXT("No loot found to Add Tag / Stat. Add a Make Loot node first."));
	}

	Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR

FText UAddTagLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Name"), FText::FromName(LootTag.GetTagName()));

	return FText::Format(LOCTEXT("NestedTableNodeTitle", "<{Name}>"), Args);
}

const FSlateBrush*  UAddTagLTNode::GetNodeIcon() const
{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Icon"));
#else // #if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Icon"));
#endif // #else ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
}

FLinearColor UAddTagLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.682f, 0.044f, 0.412f);
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

