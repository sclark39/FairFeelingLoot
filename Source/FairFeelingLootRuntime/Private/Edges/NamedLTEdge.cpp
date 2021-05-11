// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "NamedLTEdge.h"
#include "LootTableDefinition.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"

UNamedLTEdge::UNamedLTEdge()
{
	Value = NAME_None;
#if WITH_EDITORONLY_DATA
	bShouldDrawTitle = true;
#endif // #if WITH_EDITORONLY_DATA
}

#if WITH_EDITOR

FText UNamedLTEdge::GetNodeTitle() const
{
	return FText::FromName(Value);
}

void UNamedLTEdge::SetNodeTitle(const FText& NewTitle)
{
	Value = *NewTitle.ToString();
}

#endif // #if WITH_EDITOR

#undef LOCTEXT_NAMESPACE 



