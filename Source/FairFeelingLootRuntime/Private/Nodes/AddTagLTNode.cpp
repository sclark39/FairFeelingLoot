// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "AddTagLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UAddTagLTNode::UAddTagLTNode()
{
//	LootTagName = NAME_None;

#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("AddTagNode", "Make Loot - Add Tag / Stat");
	ContextMenuCategory = LTCATEGORY_LOOT;
#endif // #if WITH_EDITORONLY_DATA
}



const ULTGraphNode* UAddTagLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	if (0 < Loot.Num())
	{
		FLootRecipe &NewLoot = Loot.Last();
		NewLoot.Tags.AddTag(GameplayTag);

		if (bTagHasStatValue)
		{
			float rand = State.RNG->FRandRange(StatValueRange.X, StatValueRange.Y);

			float &Stat = NewLoot.Stats.FindOrAdd(GameplayTag, StatDefaultValue);

			if (StatWriteMode == EAddParamLTType::Add)
				rand = Stat + rand;
			else if (StatWriteMode == EAddParamLTType::Subtract)
				rand = Stat - rand;

			Stat = rand;
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No loot found to Add Tag / Stat. Add a Make Loot node first."));
	}

	return Super::TraverseNodesAndCollectLoot(LootTable, State, Loot);
}

#if WITH_EDITOR

FText UAddTagLTNode::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Name"), FText::FromName(GameplayTag.GetTagName()));

	if (bTagHasStatValue)
	{
		if (StatWriteMode == EAddParamLTType::Add)
			Args.Add(TEXT("Mode"), FText::FromString(TEXT("+")));
		else if (StatWriteMode == EAddParamLTType::Subtract)
			Args.Add(TEXT("Mode"), FText::FromString(TEXT("-")));
		else
			Args.Add(TEXT("Mode"), FText::FromString(TEXT("")));
		Args.Add(TEXT("Range"), RangeToText(StatValueRange.X, StatValueRange.Y));
		return FText::Format(LOCTEXT("NestedTableNodeTitle", ">{Name}{Mode} {Range}"), Args);
	}
	else
	{
		return FText::Format(LOCTEXT("NestedTableNodeTitle", "<{Name}>"), Args);
	}
}

const FSlateBrush*  UAddTagLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Task.Icon"));
}

FLinearColor UAddTagLTNode::GetBackgroundColor() const
{
	if ( bTagHasStatValue )
		return FLinearColor(0.0f, 0.354f, 0.578f);
	else
		return FLinearColor(0.682f, 0.044f, 0.412f);
}
#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 

