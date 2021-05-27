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
	const ULootTableDefinition *Definition = Cast<ULootTableDefinition>(GetGraph());
	ensure(Definition);

	if (!bShouldBeLocalScope
		&& LootTable.LocalFloatParams.Contains(Definition)
		&& LootTable.LocalFloatParams[Definition].Contains(ParamName))
	{
		UE_LOG(LogTemp, Error, TEXT("Edit Float Param operating on Global Scope while there is already a Local Scope Param."));
	}

	float CurrentValue = LootTable.GetFloatParamFromLT(Cast<ULootTableDefinition>(GetGraph()), ParamName, DefaultValue);

	float rand = State.RNG->FRandRange(ValueRange.X, ValueRange.Y);

	if (WriteMode == EAddParamLTType::Add)
		CurrentValue += rand;
	else if (WriteMode == EAddParamLTType::Subtract)
		CurrentValue -= rand;
	else
		CurrentValue = rand;

	if (!bShouldBeLocalScope)
		LootTable.SetFloatParam(ParamName, CurrentValue);
	else
		LootTable.SetFloatParamForLT(Definition, ParamName, CurrentValue);

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
