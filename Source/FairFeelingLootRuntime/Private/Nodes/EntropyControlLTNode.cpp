// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "EntropyControlLTNode.h"

#define LOCTEXT_NAMESPACE "LootTableDefinition"


UEntropyControlLTNode::UEntropyControlLTNode()
{
#if WITH_EDITORONLY_DATA
	ContextMenuName = LOCTEXT("EntropyControlNode", "Entropy Control");
	ContextMenuCategory = LTCATEGORY_MISC;
	ChildrenLimitType = ELTGenericGraphNodeLimit::Limited;
	ChildrenLimit = 1;
#endif // #if WITH_EDITORONLY_DATA
}

const ULTGraphNode* UEntropyControlLTNode::TraverseNodesAndCollectLoot(FLootTable &LootTable, const FEntropyState &State, TArray<FLootRecipe> &Loot) const
{
	RETRIEVE_LTNODE_PAYLOAD(sizeof(FRandomStream) + sizeof(float));
	DECLARE_LTNODE_ELEMENT(FRandomStream, MyRNG);
	DECLARE_LTNODE_ELEMENT(float, LastTime);

	if (*RequiresInitialization)
	{
		*RequiresInitialization = false;

		// Initialize State Stream
		if (bTracksOwnRandomStream)
		{
			new (&MyRNG) FRandomStream(InitialSeed);
			if (bShouldRandomizeSeed)
				MyRNG.GenerateNewSeed();
		}
	}

	FEntropyState MyEntropyState;
	MyEntropyState.RNG = bTracksOwnRandomStream ? &MyRNG : State.RNG; 
	MyEntropyState.LastTime = bTracksOwnTime ? LastTime : State.LastTime;

	const ULTGraphNode *Node = Super::TraverseNodesAndCollectLoot(LootTable, MyEntropyState, Loot);

	if (bTracksOwnTime)
		LastTime = LootTable.GetTime();

	return Node;
}


#if WITH_EDITOR
FLinearColor UEntropyControlLTNode::GetBackgroundColor() const
{
	return FLinearColor(0.5f, 0.01f, 0.01f);
}

const FSlateBrush*  UEntropyControlLTNode::GetNodeIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Composite.Selector.Icon"));
}

#endif

#undef LOCTEXT_NAMESPACE 
