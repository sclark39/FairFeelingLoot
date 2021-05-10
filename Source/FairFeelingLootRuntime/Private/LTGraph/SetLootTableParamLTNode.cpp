// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGraph/SetLootTableParamLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

USetLootTableParamLTNode::USetLootTableParamLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("SetParam", "Edit LootTable Param");
	ContextMenuCategory = LTCATEGORY_MISC;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGraphNode* USetLootTableParamLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	float rand = State.RNG->FRandRange(ValueRange.X, ValueRange.Y);
	
	float &Param = LootTable.FloatParams.FindOrAdd(ParamName);

	if (WriteMode == EAddParamLTType::Add)
		rand = Param + rand;
	else if (WriteMode == EAddParamLTType::Subtract)
		rand = Param - rand;

	Param = rand;

	return Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR
FText USetLootTableParamLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	if (WriteMode == EAddParamLTType::Add)
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("+")));
	else if (WriteMode == EAddParamLTType::Subtract)
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("-")));
	else
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("")));
	Args.Add(TEXT("Name"), FText::FromName(ParamName));
	Args.Add(TEXT("Range"), RangeToText(ValueRange.X, ValueRange.Y));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", "{Name}{Mode} {Range}"), Args);
}


FLinearColor USetLootTableParamLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.5f, 0.01f, 0.01f);
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
