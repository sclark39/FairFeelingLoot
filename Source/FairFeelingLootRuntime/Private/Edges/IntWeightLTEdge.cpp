// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "IntWeightLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UIntWeightLTEdge::UIntWeightLTEdge()
{
#if WITH_EDITORONLY_DATA
	bShouldDrawTitle = true;
#endif // #if WITH_EDITORONLY_DATA
}

#if WITH_EDITOR

FText UIntWeightLTEdge::GetNodeTitle() const
{
	return FText::FromString( FString::FromInt(Weight) );
}

void UIntWeightLTEdge::SetNodeTitle(const FText& NewTitle)
{
	Weight = FCString::Atoi(*NewTitle.ToString());
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
