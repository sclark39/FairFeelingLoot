// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "AddStatLTNode.h"
#include "LootTableBlueprintLibrary.h"
#include "FairFeelingLootRuntime.h"

#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif // #if WITH_EDITOR

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UAddStatLTNode::UAddStatLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("AddStatNode", "Make Loot - Add Stat");
	ContextMenuCategory = LTCATEGORY_LOOT;
#endif // #if WITH_EDITORONLY_DATA
}



const void UAddStatLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const
{
	if (State.ActiveLoot)
	{
		FLootRecipe &NewLoot = *State.ActiveLoot;

		float CurrentValue = ULootTableBlueprintLibrary::GetLootStat(NewLoot, StatType, StatDefaultValue);

		float rand = State.RNG->FRandRange(StatValueRange.X, StatValueRange.Y);

		if (StatWriteMode == EAddParamLTType::Add)
			CurrentValue += rand;
		else if (StatWriteMode == EAddParamLTType::Subtract)
			CurrentValue -= rand;
		else
			CurrentValue = rand;

		ULootTableBlueprintLibrary::SetLootStat(NewLoot, StatType, CurrentValue);
	}
	else
	{
		UE_LOG(LogFairFeelingLoot, Error, TEXT("No loot found to Add Stat. Add a Make Loot node first."));
	}

	Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR

FText UAddStatLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Name"), FText::FromName(StatType.GetTagName()));

	if (StatWriteMode == EAddParamLTType::Add)
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("+")));
	else if (StatWriteMode == EAddParamLTType::Subtract)
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("-")));
	else
		Args.Add(TEXT("Mode"), FText::FromString(TEXT("")));
	Args.Add(TEXT("Range"), RangeToText(StatValueRange.X, StatValueRange.Y));
	return FText::Format(LOCTEXT("NestedTableNodeTitle", ">{Name}{Mode} {Range}"), Args);
}

const FSlateBrush*  UAddStatLTNode::GetNodeIcon() const
{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Icon"));
#else // #if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Icon"));
#endif // #else ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
}

FLinearColor UAddStatLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.0f, 0.354f, 0.578f);
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

