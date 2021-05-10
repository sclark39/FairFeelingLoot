// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "PriorityLTEdge.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UPriorityLTEdge::UPriorityLTEdge()
{
#if WITH_EDITORONLY_DATA
	bShouldDrawTitle = true;
#endif // #if WITH_EDITORONLY_DATA
}

#if WITH_EDITOR

FText UPriorityLTEdge::GetNodeTitle() const
{
	return FText::FromString( FString::SanitizeFloat(Priority, 0) );
}

void UPriorityLTEdge::SetNodeTitle(const FText& NewTitle)
{
	Priority = FCString::Atof(*NewTitle.ToString());
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 
