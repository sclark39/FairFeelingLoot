﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

ULootLTNode::ULootLTNode()
{
	LootColor = FLinearColor(1.0f, 0.7f, 0.0f);
	LootName = FName(TEXT("Loot"));

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("LootNode", "Make Loot");
	ContextMenuCategory = LTCATEGORY_LOOT;
#endif // #if WITH_EDITORONLY_DATA
}


const void ULootLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	FLootRecipe NewLoot;

	NewLoot.Name = LootName;
	NewLoot.Type = LootType;

	Loot.Push(NewLoot);

	State.ActiveLoot = &Loot.Last();

	Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR

FText ULootLTNode::GetNodeTitle() const
{
	return FText::FromName(LootName);
}

void ULootLTNode::SetNodeTitle(const FText& NewTitle)
{
	LootName = FName(NewTitle.ToString());
}

const FSlateBrush*  ULootLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.ForceSuccess.Icon"));
}

bool ULootLTNode::IsNameEditable() const
{
	return true;
}

FLinearColor ULootLTNode::GetBackgroundColor() const
{
	return LootColor;
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

