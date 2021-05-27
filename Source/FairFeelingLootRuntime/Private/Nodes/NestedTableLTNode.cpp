// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "NestedTableLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UNestedTableLTNode::UNestedTableLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("NestedLTNode", "Nested Loot Table");
	ContextMenuCategory = LTCATEGORY_MISC;
	ChildrenLimitType = ELTGenericGraphNodeLimit::Forbidden;
#endif // #if WITH_EDITORONLY_DATA
}


const ULTGraphNode* UNestedTableLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	if (LootTableDefinition)
	{
		if (LootTable.VisitedGraphs.Contains(LootTableDefinition))
		{
			UE_LOG(LogTemp, Error, TEXT("Can't enter nested loot table %s. Would create a cycle."), *LootTableDefinition->GetName() );
			return nullptr;
		}
		for (const auto *Node : LootTableDefinition->RootNodes)
		{
			if (const URootLTGraphNode *RootNode = Cast<URootLTGraphNode>(Node))
			{
				LootTable.VisitedGraphs.Add(LootTableDefinition);
				const ULTGenericGraphNode *Child = TraverseNodesAndCollectLoot(LootTable, State, Loot);
				LootTable.VisitedGraphs.Remove(LootTableDefinition);
				return Cast<ULTGraphNode>(Child);
			}
		}
	}
	return nullptr;
}

#if WITH_EDITOR

FText UNestedTableLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	if (LootTableDefinition)
	{
		Args.Add(TEXT("Name"), FText::FromString(LootTableDefinition->GetName()));
		return FText::Format(LOCTEXT("NestedTableNodeTitle", "[{Name}]"), Args);
	}

	return ContextMenuName;
}

const FSlateBrush*  UNestedTableLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.Optional.Icon"));
}

FLinearColor UNestedTableLTNode::GetBackgroundColor() const
{
	return FLinearColor::White;
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
