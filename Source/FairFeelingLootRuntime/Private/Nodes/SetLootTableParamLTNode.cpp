﻿// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "SetLootTableParamLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

USetLootTableParamLTNode::USetLootTableParamLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("SetParam", "Edit Float Param");
	ContextMenuCategory = LTCATEGORY_FLOW;
#endif // #if WITH_EDITORONLY_DATA
}

const void USetLootTableParamLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	float rand = State.RNG->FRandRange(ValueRange.X, ValueRange.Y);
	
	float &Param = LootTable.FloatParams.FindOrAdd(ParamName, DefaultValue);

	if (WriteMode == EAddParamLTType::Add)
		rand = Param + rand;
	else if (WriteMode == EAddParamLTType::Subtract)
		rand = Param - rand;

	Param = rand;

	Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
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

const FSlateBrush*  USetLootTableParamLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.NonConditional.Icon"));
}

FLinearColor USetLootTableParamLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.5f, 0.01f, 0.01f);
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
