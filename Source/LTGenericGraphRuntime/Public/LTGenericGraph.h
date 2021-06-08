// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LTGenericGraphNode.h"
#include "LTGenericGraphEdge.h"
#include "GameplayTagContainer.h"
#include "LTGenericGraph.generated.h"

UCLASS()
class LTGENERICGRAPHRUNTIME_API ULTGenericGraph : public UObject
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FGenericGraphSimpleDelegate, const ULTGenericGraph*)
	DECLARE_MULTICAST_DELEGATE_OneParam(FGenericGraphNodeSimpleDelegate, const ULTGenericGraphNode*)
	DECLARE_MULTICAST_DELEGATE_OneParam(FGenericGraphEdgeSimpleDelegate, const ULTGenericGraphEdge*)

public:
	ULTGenericGraph();
	virtual ~ULTGenericGraph();

#if WITH_EDITOR
	static FGenericGraphSimpleDelegate OnGraphChanged;
	static FGenericGraphNodeSimpleDelegate OnNodeChanged;
	static FGenericGraphEdgeSimpleDelegate OnEdgeChanged;
#endif // #if WITH_EDITOR

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph")
	TSubclassOf<ULTGenericGraphNode> NodeType;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph")
	TSubclassOf<ULTGenericGraphNode> RootNodeType;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph")
	TSubclassOf<ULTGenericGraphEdge> EdgeType;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraph")
	TArray<ULTGenericGraphNode*> RootNodes;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraph")
	TArray<ULTGenericGraphNode*> AllNodes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LTGenericGraph")
	bool bEdgeEnabled;

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraph")
	void Print(bool ToConsole = true, bool ToScreen = true);

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraph")
	int GetLevelNum() const;

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraph")
	void GetNodesByLevel(int Level, TArray<ULTGenericGraphNode*>& Nodes);

	void ClearGraph();

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UEdGraph* EdGraph;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph_Editor")
	bool bCanRenameNode;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph_Editor")
	bool bCanBeCyclical;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph_Editor")
	bool bRebuildAfterEveryChange;

	virtual bool ShouldAllowIncrementalRebuild()
	{
		return bRebuildAfterEveryChange;
	}
#endif
};
