// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "ComparisonLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UComparisonLTEdge::UComparisonLTEdge()
{
#if WITH_EDITORONLY_DATA
	bShouldDrawTitle = true;
#endif // #if WITH_EDITORONLY_DATA
}

bool UComparisonLTEdge::AllowTraversal(FLootTable &LootTable, float TestValue) const
{
	if (bHasMinValue)
	{
		float Min = MinValue;
		if (bUseDynamicMin)
			Min = LootTable.GetFloatParam(MinParamName);
		if (TestValue <= Min)
		{
			if (!bInclusiveMin || TestValue < Min)
				return false;
		}
	}

	if (bHasMaxValue)
	{
		float Max = MaxValue;
		if (bUseDynamicMax)
			Max = LootTable.GetFloatParam(MaxParamName);
		if (Max <= TestValue)
		{
			if (!bInclusiveMax || Max < TestValue)
				return false;
		}
	}

	return true;
}

#if WITH_EDITOR

FText UComparisonLTEdge::GetNodeTitle() const
{
	FFormatNamedArguments Args;
	if (bHasMinValue)
	{
		if (bUseDynamicMin)
			Args.Add(TEXT("Min"), FText::FromName(MinParamName));
		else
			Args.Add(TEXT("Min"), FText::FromString( FString::SanitizeFloat(MinValue, 0.0f)));

		if (!bHasMaxValue)
		{
			Args.Add(TEXT("Mode"), FText::FromString(bInclusiveMin ? TEXT(">=") : TEXT(">")));
			return FText::Format(LOCTEXT("CompEdgeTitleGreater", "{Mode}{Min}"), Args);
		}
		else
		{
			Args.Add(TEXT("LoMode"), FText::FromString(bInclusiveMin ? TEXT("[") : TEXT("(")));
		}
	}

	if (bHasMaxValue)
	{
		if (bUseDynamicMax)
			Args.Add(TEXT("Max"), FText::FromName(MaxParamName));
		else
			Args.Add(TEXT("Max"), FText::FromString(FString::SanitizeFloat(MaxValue, 0.0f)));

		if (!bHasMinValue)
		{
			Args.Add(TEXT("Mode"), FText::FromString(bInclusiveMax ? TEXT("<=") : TEXT("<")));
			return FText::Format(LOCTEXT("CompEdgeTitleLessor", "{Mode}{Max}"), Args);
		}
		else
		{
			Args.Add(TEXT("HiMode"), FText::FromString(bInclusiveMax ? TEXT("]") : TEXT(")")));
		}
	}

	if (bHasMinValue && bHasMaxValue)
	{
		if (bUseDynamicMin || bUseDynamicMax || MinValue != MaxValue)
			return FText::Format(LOCTEXT("CompEdgeTitleRange", "{LoMode}{Min},{Max}{HiMode}"), Args);
		else
			return FText::Format(LOCTEXT("CompEdgeTitleOne", "{Min}"), Args);
	}

	return FText::FromString(TEXT("?"));
}

void UComparisonLTEdge::SetNodeTitle(const FText& NewTitle)
{

}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
