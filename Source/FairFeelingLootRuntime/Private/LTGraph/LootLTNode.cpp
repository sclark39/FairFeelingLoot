// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGraph/LootLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

ULootLTNode::ULootLTNode()
{
	LootColor = FLinearColor(1.0f, 0.7f, 0.0f);
	LootType = FName(TEXT("Loot"));

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("LootNode", "Make Loot");
	ContextMenuCategory = LTCATEGORY_LOOT;
#endif // #if WITH_EDITORONLY_DATA
}


const ULTGraphNode* ULootLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	FLootRecipe NewLoot;

	NewLoot.LootType = LootType;
	Loot.Push(NewLoot);

	return Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR

FText ULootLTNode::GetNodeTitle() const
{
	return FText::FromName(LootType);
}

void ULootLTNode::SetNodeTitle(const FText& NewTitle)
{
	LootType = FName(NewTitle.ToString());
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

