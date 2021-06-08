// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootTable.h"
#include "LootTableDefinition.h"
#include "Engine/World.h"

float FLootTableData::GetTime()
{
	return World->GetTimeSeconds();
}
