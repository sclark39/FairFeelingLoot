// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "AddParamLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UAddParamLTNode::UAddParamLTNode()
{
	LootParamName = NAME_None;
	LootParamRange = FVector2D::ZeroVector;

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("AddParamNode", "Make Loot - Add Named Param");
	ContextMenuCategory = LTCATEGORY_LOOT;
#endif // #if WITH_EDITORONLY_DATA
}


const ULTGraphNode* UAddParamLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	if (0 < Loot.Num())
	{
		FLootRecipe &NewLoot = Loot.Last();
		
		float rand = State.RNG->FRandRange(LootParamRange.X, LootParamRange.Y);

		float &Param = NewLoot.Params.FindOrAdd(LootParamName);

		if (WriteMode == EAddParamLTType::Add)
			rand = Param + rand; 
		else if (WriteMode == EAddParamLTType::Subtract)
			rand = Param - rand;

		Param = rand;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No loot found to Add Named Param. Add a Make Loot node first."));
	}

	return Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}


#if WITH_EDITOR

FText UAddParamLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	if (WriteMode == EAddParamLTType::Add)
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("+")));
	else if (WriteMode == EAddParamLTType::Subtract)
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("-")));
	else
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("")));
	Args.Add(TEXT("Name"), FText::FromName(LootParamName));
	Args.Add(TEXT("Range"), RangeToText(LootParamRange.X, LootParamRange.Y));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", "{Name}{Mode} {Range}"), Args);
}

const FSlateBrush*  UAddParamLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Icon"));
}

FLinearColor UAddParamLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.0f, 0.354f, 0.578f);
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

