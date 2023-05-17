// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "NestedTableLTNode.h"
#include "FairFeelingLootRuntime.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // #if WITH_EDITOR

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UNestedTableLTNode::UNestedTableLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("NestedLTNode", "Nested Loot Table");
	ContextMenuCategory = LTCATEGORY_MISC;
	ChildrenLimitType = ELTGenericGraphNodeLimit::Forbidden;
#endif // #if WITH_EDITORONLY_DATA
}


const void UNestedTableLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	if (LootTableDefinition)
	{
		if (LootTable.VisitedGraphs.Contains(LootTableDefinition))
		{
			UE_LOG(LogFairFeelingLoot, Error, TEXT("Can't enter nested loot table %s. Would create a cycle."), *LootTableDefinition->GetName());
			return;
		}

		const URootLTGraphNode *RootNode = LootTableDefinition->GetRootNode();
		if (!RootNode)
		{
			UE_LOG(LogFairFeelingLoot, Error, TEXT("Loot Table Definition is missing Root Node."));
			return;
		}

		LootTable.VisitedGraphs.Add(LootTableDefinition);
		RootNode->TraverseNodesAndCollectLoot(LootTable, State, Loot);
		LootTable.VisitedGraphs.Remove(LootTableDefinition);		
	}
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
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.Optional.Icon"));
#else // #if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.Optional.Icon"));
#endif // #else ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
}

FLinearColor UNestedTableLTNode::GetBackgroundColor() const
{
	return FLinearColor::White;
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
