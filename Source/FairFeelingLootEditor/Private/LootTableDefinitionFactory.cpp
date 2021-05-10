// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootTableDefinitionFactory.h"
#include "LootTableDefinition.h"

#define LOCTEXT_NAMESPACE "FairRandomGraphFactory"

ULootTableDefinitionFactory::ULootTableDefinitionFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = ULootTableDefinition::StaticClass();
}

UObject* ULootTableDefinitionFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
}

FText ULootTableDefinitionFactory::GetDisplayName() const
{
	return LOCTEXT("FactoryName", "Loot Table Definition");
}

FString ULootTableDefinitionFactory::GetDefaultNewAssetName() const
{
	return "NewLootTableDefinition";
}
#undef LOCTEXT_NAMESPACE