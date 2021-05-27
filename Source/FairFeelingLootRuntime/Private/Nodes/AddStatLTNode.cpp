// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "AddStatLTNode.h"
#include "LootTableBlueprintLibrary.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UAddStatLTNode::UAddStatLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("AddStatNode", "Make Loot - Add Stat");
	ContextMenuCategory = LTCATEGORY_LOOT;
#endif // #if WITH_EDITORONLY_DATA
}



const ULTGraphNode* UAddStatLTNode::TraverseNodesAndCollectLoot(FLootTableData &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	if (0 < Loot.Num())
	{
		FLootRecipe &NewLoot = Loot.Last();

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
		UE_LOG(LogTemp, Error, TEXT("No loot found to Add Stat. Add a Make Loot node first."));
	}

	return Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
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
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Icon"));
}

FLinearColor UAddStatLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.0f, 0.354f, 0.578f);
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

