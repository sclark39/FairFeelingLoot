// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LTGenericGraph.h"
#include "LTGenericGraphEdge.h"
#include "LTGenericGraphNode.h"
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


UCLASS(NotBlueprintable, NotBlueprintType, Abstract, hideCategories = ("LTGenericGraphNode", "LTGenericGraphNode_Editor"))
class FAIRFEELINGLOOTRUNTIME_API ULTGraphNode : public ULTGenericGraphNode
{
	GENERATED_BODY()
public:

	ULTGraphNode();

	virtual const ULTGenericGraphNode* PickChild(FLootTable &LootTable, const FEntropyState &State) const;
	virtual const ULTGraphNode* TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const;
	
	virtual bool ShouldPickChildren() const { return true; }

#if WITH_EDITOR
	FText RangeToText(float Min, float Max) const;
	virtual FText GetNodeTitle() const override;
	virtual bool IsNameEditable() const override;
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
#endif
};

UCLASS(NotBlueprintable, NotBlueprintType, Abstract, hideCategories = ("LTGenericGraphNode", "LTGenericGraphEdge", "LTGenericGraphNode_Editor"))
class FAIRFEELINGLOOTRUNTIME_API ULTGraphEdge : public ULTGenericGraphEdge
{
	GENERATED_BODY()
public:

};



UCLASS()
class FAIRFEELINGLOOTRUNTIME_API UNoopLTGraphNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	UNoopLTGraphNode();

#if WITH_EDITOR
	virtual const FSlateBrush* GetNodeIcon() const override;
#endif // #if WITH_EDITOR
};


UCLASS()
class FAIRFEELINGLOOTRUNTIME_API URootLTGraphNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	URootLTGraphNode();

	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
#endif
};


UCLASS(NotBlueprintable, hideCategories = ("LTGenericGraph", "LTGenericGraph_Editor"))
class FAIRFEELINGLOOTRUNTIME_API ULootTableDefinition : public ULTGenericGraph
{
	GENERATED_BODY()
public:

	ULootTableDefinition();

	const URootLTGraphNode* GetRootNode() const;
};

