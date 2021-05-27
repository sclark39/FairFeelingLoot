// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "CallbackLTNode.h"
#include "LootTableComponent.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UCallbackLTNode::UCallbackLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("CallbackLTNode", "Blueprint Callback");
	ContextMenuCategory = LTCATEGORY_MISC;
#endif // #if WITH_EDITORONLY_DATA
}


const void UCallbackLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	if (LootTable.Component)
	{
		LootTable.Component->OnLootTableCallback.Broadcast( Specifier );
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Callback node requires Loot Table Component."));
	}

	Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR

FText UCallbackLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Spec"), FText::FromName(Specifier));
	return FText::Format(LOCTEXT("CallbackNodeTitle", "Callback: {Spec}"), Args);
}

const FSlateBrush*  UCallbackLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.RunEQSQuery.Icon"));
}

FLinearColor UCallbackLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.5f, 0.01f, 0.01f);
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
