// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraph.h"
#include "GenericGraphEdge.h"
#include "GenericGraphNode.h"
#include "LootTable.h"

#include "LootTableDefinition.generated.h"

class ULTGraphNode;

#define LTCATEGORY_RANDOM	LOCTEXT("RandomCategory", "1. Random Selection")
#define LTCATEGORY_LOOT		LOCTEXT("LootCategory", "2. Loot Building")
#define LTCATEGORY_FLOW		LOCTEXT("FlowControlCategory", "3. Flow Control")
#define LTCATEGORY_MISC		LOCTEXT("MiscCategory", "4. Miscellaneous")

#define DECLARE_LTNODE_ELEMENT(Type,Name)													\
	Type& Name = *((Type*)(Payload));														\
	Payload += sizeof(Type);

#define DECLARE_LTNODE_ELEMENT_PTR(Type,Name)												\
	Type* Name = (Type*)(Payload);															\
	Payload += sizeof(Type);

#define	RETRIEVE_LTNODE_PAYLOAD( Size )														\
	uint8*	Payload					= NULL;													\
	uint32*	RequiresInitialization	= NULL;													\
	{																						\
		uint32* TempOffset = LootTable.NodeOffsetMap.Find(this);							\
		uint32 Offset;																		\
		if( !TempOffset )																	\
		{																					\
			Offset = LootTable.NodeData.AddZeroed( Size + sizeof(uint32));				\
			LootTable.NodeOffsetMap.Add( this, Offset );									\
			RequiresInitialization = (uint32*) &LootTable.NodeData[Offset];				\
			*RequiresInitialization = 1;													\
			Offset += sizeof(uint32);														\
		}																					\
		else																				\
		{																					\
			RequiresInitialization = (uint32*) &LootTable.NodeData[*TempOffset];			\
			Offset = *TempOffset + sizeof(uint32);											\
		}																					\
		Payload = &LootTable.NodeData[Offset];											\
	}


UENUM()
enum class EAddParamLTType : uint8
{
	Overwrite,
	Add,
	Subtract
};


UCLASS(NotBlueprintable, NotBlueprintType, Abstract, hideCategories = ("GenericGraphNode", "GenericGraphNode_Editor"))
class ULTGraphNode : public UGenericGraphNode
{
	GENERATED_BODY()
public:

	ULTGraphNode();

	virtual const UGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const;
	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const;
	
	virtual bool ShouldPickChildren() const { return true; }

#if WITH_EDITOR
	FText RangeToText(float Min, float Max) const;
	virtual FText GetNodeTitle() const override;
	virtual bool IsNameEditable() const override;
	virtual TSubclassOf<UGenericGraphEdge> GetEdgeType() const override;
#endif
};

UCLASS(NotBlueprintable, NotBlueprintType, Abstract, hideCategories = ("GenericGraphNode", "GenericGraphEdge", "GenericGraphNode_Editor"))
class ULTGraphEdge : public UGenericGraphEdge
{
	GENERATED_BODY()
public:

};



UCLASS()
class UNoopLTGraphNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UNoopLTGraphNode();
};


UCLASS()
class URootLTGraphNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	URootLTGraphNode();

	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual TSubclassOf<UGenericGraphEdge> GetEdgeType() const override;
	virtual FLinearColor GetBackgroundColor() const override;
#endif
};


UCLASS(Blueprintable, hideCategories = ("GenericGraph", "GenericGraph_Editor"))
class GRAPHEDITORTEST_API ULootTableDefinition : public UGenericGraph
{
	GENERATED_BODY()
public:

	ULootTableDefinition();

	const URootLTGraphNode* GetRootNode() const;
};

