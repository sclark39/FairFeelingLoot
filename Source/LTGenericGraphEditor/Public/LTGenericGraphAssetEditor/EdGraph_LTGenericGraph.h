#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_LTGenericGraph.generated.h"

class ULTGenericGraph;
class ULTGenericGraphNode;
class ULTGenericGraphEdge;
class UEdNode_LTGenericGraphNode;
class UEdNode_LTGenericGraphEdge;

UCLASS()
class LTGENERICGRAPHEDITOR_API UEdGraph_LTGenericGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UEdGraph_LTGenericGraph();
	virtual ~UEdGraph_LTGenericGraph();

	virtual void RebuildLTGenericGraphIncremental();
	virtual void RebuildLTGenericGraph();

	ULTGenericGraph* GetLTGenericGraph() const;

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;
	virtual void PostEditUndo() override;

	UPROPERTY(Transient)
	TMap<ULTGenericGraphNode*, UEdNode_LTGenericGraphNode*> NodeMap;

	UPROPERTY(Transient)
	TMap<ULTGenericGraphEdge*, UEdNode_LTGenericGraphEdge*> EdgeMap;

protected:
	void Clear();

	void SortNodes(ULTGenericGraphNode* RootNode);
};
