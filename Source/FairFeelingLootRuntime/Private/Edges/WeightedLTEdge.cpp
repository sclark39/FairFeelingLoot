// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "WeightedLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UWeightedLTEdge::UWeightedLTEdge()
{
	Weight = 1;
#if WITH_EDITORONLY_DATA
	bShouldDrawTitle = true;
#endif // #if WITH_EDITORONLY_DATA
}

float UWeightedLTEdge::GetWeight(FLootTableData &LootTable) const
{
	if (bUseDynamicWeight)
	{
		return LootTable.GetFloatParam(WeightParamName);
	}

	return Weight;
}

#if WITH_EDITOR

FText UWeightedLTEdge::GetNodeTitle() const
{
	if (bUseDynamicWeight)
		return FText::FromName(WeightParamName);
	else
		return FText::FromString( FString::SanitizeFloat(Weight, 0) );
}

void UWeightedLTEdge::SetNodeTitle(const FText& NewTitle)
{
	if (bUseDynamicWeight)
		WeightParamName = *NewTitle.ToString();
	else
		Weight = FCString::Atof(*NewTitle.ToString());
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
