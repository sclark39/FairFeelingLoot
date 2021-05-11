// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGraph/AddTagLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UAddTagLTNode::UAddTagLTNode()
{
//	LootTagName = NAME_None;

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("AddTagNode", "Add Loot Tag");
	ContextMenuCategory = LTCATEGORY_LOOT;
#endif // #if WITH_EDITORONLY_DATA
}



const ULTGraphNode* UAddTagLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	if (0 < Loot.Num())
	{
		FLootRecipe &NewLoot = Loot.Last();
		NewLoot.GameplayTags.AddTag(GameplayTag);
	}

	return Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR

FText UAddTagLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Name"), FText::FromName(GameplayTag.GetTagName()));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", "<{Name}>"), Args);
}

const FSlateBrush*  UAddTagLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Icon"));
}

FLinearColor UAddTagLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.682f, 0.044f, 0.412f);
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

