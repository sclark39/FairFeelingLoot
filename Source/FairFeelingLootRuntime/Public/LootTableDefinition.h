// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LTGenericGraph.h"
#include "LTGenericGraphEdge.h"
#include "LTGenericGraphNode.h"
#include "LootTable.h"

#include "LootTableDefinition.generated.h"

class ULTGraphNode;

#define LTCATEGORY_LOOT		LOCTEXT("LootCategory", "1. Loot Building")
#define LTCATEGORY_RANDOM	LOCTEXT("RandomCategory", "2. Random Selection")
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

	virtual const ULTGenericGraphNode* PickChild(FLootTableData &LootTable, const FMakeLootState &State) const;
	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const;
	
	virtual bool ShouldPickChildren() const { return true; }

#if WITH_EDITOR
	FText RangeToText(float Min, float Max, bool bCanReorder = true) const;
	virtual FText GetNodeTitle() const override;
	virtual FText GetContextMenuDescription() const override;
	virtual bool IsNameEditable() const override;
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
	virtual bool SupportsImplicitSequence() const { return false; }

	virtual void GetChildrenLimit(ELTGenericGraphNodeLimit &LimitType, int32 &LimitCount) const override;
#endif
};

UCLASS(NotBlueprintable, NotBlueprintType, Abstract, hideCategories = ("LTGenericGraphNode", "LTGenericGraphEdge", "LTGenericGraphNode_Editor"))
class FAIRFEELINGLOOTRUNTIME_API ULTGraphEdge : public ULTGenericGraphEdge
{
	GENERATED_BODY()
public:

};


// Node that has no effect, can be used if you don't always want loot to be generated
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


// The start of loot generation in this loot table
UCLASS()
class FAIRFEELINGLOOTRUNTIME_API URootLTGraphNode : public ULTGraphNode
{
	GENERATED_BODY()
public:
	URootLTGraphNode();

	virtual const void TraverseNodesAndCollectLoot(FLootTableData &LootTable, FMakeLootState State, TArray<FLootRecipe> &Loot) const;

	virtual bool ShouldPickChildren() const override { return false; }

#if WITH_EDITOR
	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const override;
	virtual FLinearColor GetBackgroundColor() const override;
	virtual const FSlateBrush* GetNodeIcon() const override;
	virtual bool SupportsImplicitSequence() const override { return true; }
#endif
};


UCLASS(NotBlueprintable, BlueprintType, hideCategories = ("LTGenericGraph", "LTGenericGraph_Editor"))
class FAIRFEELINGLOOTRUNTIME_API ULootTableDefinition : public ULTGenericGraph
{
	GENERATED_BODY()
public:

	// When enabled, this allows for some node types to have multiple children which will be unconditionally followed.
	UPROPERTY(EditDefaultsOnly, Category = "Loot Table")
	bool bAllowImplicitSequenceNodes = false;

	// Should this loot table use its own random stream
	UPROPERTY(EditDefaultsOnly, Category = "Random")
	bool bTracksOwnRandomStream = false;

	// If true, ignore InitialSeed and randomize the seed for the random number stream
	UPROPERTY(EditDefaultsOnly, Category = "Random", meta = (EditCondition = "bTracksOwnRandomStream"))
	bool bShouldRandomizeSeed = true;

	// If not randomizing the seed, this is what will be used to initialize the random number stream
	UPROPERTY(EditDefaultsOnly, Category = "Random", meta = (EditCondition = "bTracksOwnRandomStream && !bShouldRandomizeSeed"))
	float InitialSeed = 0;

	// Should this loot table track its own time?
	UPROPERTY(EditDefaultsOnly, Category = "Time")
	bool bTracksOwnTime = true;

	ULootTableDefinition();

	const URootLTGraphNode* GetRootNode() const;
};

