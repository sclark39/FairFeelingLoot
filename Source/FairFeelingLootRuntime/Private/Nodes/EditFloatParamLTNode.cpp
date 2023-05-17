// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "EditFloatParamLTNode.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // #if WITH_EDITOR

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UEditFloatParamLTNode::UEditFloatParamLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("SetParam", "Edit Float Param");
	ContextMenuCategory = LTCATEGORY_FLOW;
#endif // #if WITH_EDITORONLY_DATA
}

const void UEditFloatParamLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	const ULootTableDefinition *Definition = Cast<ULootTableDefinition>(GetGraph());
	ensure(Definition);

	float CurrentValue = LootTable.GetFloatParamFromLT(Definition, ParamName, DefaultValue);

	float rand = State.RNG->FRandRange(ValueRange.X, ValueRange.Y);

	if (WriteMode == EAddParamLTType::Add)
		CurrentValue += rand;
	else if (WriteMode == EAddParamLTType::Subtract)
		CurrentValue -= rand;
	else
		CurrentValue = rand;

	const bool bLocalParamExists =
		LootTable.LocalFloatParams.Contains(Definition)
		&& LootTable.LocalFloatParams[Definition].Contains(ParamName);

	if (bLocalParamExists || bShouldCreateLocalScopeOnly )
		LootTable.SetFloatParamForLT(Definition, ParamName, CurrentValue);
	else if ( !bLocalParamExists && !bShouldModifyLocalScopeOnly )
		LootTable.SetFloatParam(ParamName, CurrentValue);

	Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR
FText UEditFloatParamLTNode::GetNodeTitle() const
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

const FSlateBrush*  UEditFloatParamLTNode::GetNodeIcon() const
{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.NonConditional.Icon"));
#else // #if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Decorator.NonConditional.Icon"));
#endif // #else ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
}

FLinearColor UEditFloatParamLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.5f, 0.01f, 0.01f);
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
